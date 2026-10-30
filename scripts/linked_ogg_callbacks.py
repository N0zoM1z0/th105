"""Four actual Ogg callback slots; read-only code roles, not arbitrary data."""
import struct

SYMBOL = "?ogg_callbacks@th105@@3UOggCallbacks@1@A"
SLOTS = (
    ("?read_ogg_data_source@th105@@YAKPAXKK0@Z", 0x00418B40),
    ("?seek_ogg_data_source@th105@@YAHPAX_JH@Z", 0x00418C70),
    ("?close_ogg_data_source@th105@@YAHPAX@Z", 0x00418CD0),
    ("?tell_ogg_data_source@th105@@YAJPAX@Z", 0x00418CF0),
)
KEYS = ("_ogg_callbacks", "_ogg_callbacks_slot_04",
        "_ogg_callbacks_slot_08", "_ogg_callbacks_slot_0C")


def validate(unit, data_keys):
    enabled = unit.get("link_ogg_callbacks", False)
    if (type(enabled) is not bool
            or enabled and (unit.get("link_xiph_sdk") is not True
                            or not set(KEYS) <= data_keys)):
        raise ValueError("Ogg callback slots require their pinned SDK and existing four target anchors")


def data(pe, address, size):
    import linked_pe as core
    section = pe.get_section_by_rva(address - pe.OPTIONAL_HEADER.ImageBase)
    if (section is None or not section.Characteristics & 0x40000000
            or section.Characteristics & 0x20000000
            or address + size > pe.OPTIONAL_HEADER.ImageBase + section.VirtualAddress + section.Misc_VirtualSize):
        raise ValueError("Ogg callback table is not complete mapped non-code data")
    return core.pe_data(pe, address, size)


def witnesses(unit, source, target, symbols, functions, cil_owner, known):
    import linked_pe as core
    validate(unit, set(known))
    if not unit.get("link_ogg_callbacks"):
        return []
    found = symbols.get(SYMBOL, [])
    if len(found) != 1 or found[0][1].split()[-1:] != [cil_owner]:
        raise ValueError("Ogg callback table lacks unique source CIL ownership")
    start = found[0][0]
    dst = known[KEYS[0]][0]
    if start % 4 or dst % 4:
        raise ValueError("Ogg callback table is not dword-aligned")
    target_entries = [address for _, address in SLOTS]
    if data(target, dst, 16) != struct.pack("<4I", *target_entries):
        raise ValueError("complete native Ogg callback table differs")
    entries = list(struct.unpack("<4I", data(source, start, 16)))
    if len(set(entries)) != 4:
        raise ValueError("Ogg callback roles alias one source entry")
    refs = []
    for index, ((symbol, address), key, entry) in enumerate(zip(SLOTS, KEYS, entries)):
        base, raw, addends, kind = known[key]
        if (base != dst or raw != struct.pack("<I", address)
                or addends != frozenset({index * 4}) or kind != "address"):
            raise ValueError("Ogg callback slot contradicts its existing native anchor")
        hits = symbols.get(symbol, [])
        if (len(hits) != 1 or hits[0][0] != entry
                or hits[0][1].split()[-1:] != [cil_owner]
                or len(functions.get(entry, [])) != 1
                or len([1 for name, owner in functions.get(entry, [])
                        if name == symbol and owner.split()[-1:] == [cil_owner]]) != 1):
            raise ValueError("Ogg callback slot does not name its actual CIL function")
        for pe, at in ((source, entry), (target, address)):
            section = pe.get_section_by_rva(at - pe.OPTIONAL_HEADER.ImageBase)
            if section is None or not section.Characteristics & 0x20000000:
                raise ValueError("Ogg callback entry is not executable code")
        refs.append({"kind": "callback_slot", "source_address": start + index * 4,
                     "address": dst + index * 4, "size": 4, "symbol": SYMBOL,
                     "slot": index, "callback_symbol": symbol,
                     "source_callback": entry, "target_callback": address})
    core.validate_body_relocations(source, start, 16,
                                  [{"field_offset": i * 4} for i in range(4)])
    return refs
