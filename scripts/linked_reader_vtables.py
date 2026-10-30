"""Five-slot CFileReader family vptr witnesses; no general vtable waiver."""
import csv
import re
import struct

FAMILIES = ("CFileReader", "CPackageFileReader")


def slot_symbols(family):
    owner = family + "@th105"
    return ["??_G" + owner + "@@UAEPAXI@Z",
            "?read@" + owner + "@@UAE_NPAXK@Z",
            "?last_read_size@CFileReader@th105@@UBEKXZ",
            "?seek@" + owner + "@@UAEJJH@Z",
            "?size@" + owner + "@@UBEKXZ"]


def validate(unit, data_keys):
    tables = unit.get("link_reader_vtables", [])
    if not isinstance(tables, list):
        raise ValueError("reader vtables need an explicit list")
    seen = set()
    for table in tables:
        if not isinstance(table, dict) or set(table) != {"family", "target", "entries"}:
            raise ValueError("reader vtable needs family, target and five entries")
        family = table["family"]
        if not isinstance(family, str) or family not in FAMILIES or family in seen:
            raise ValueError("reader vtable family is invalid or duplicated")
        key = "??_7" + family + "@th105@@6B@"
        entries = table["entries"]
        if (table["target"] != key or key not in data_keys
                or not isinstance(entries, list) or len(entries) != 5
                or any(not isinstance(a, str) or not re.fullmatch(r"0x[0-9A-Fa-f]{8}", a) for a in entries)):
            raise ValueError("reader vtable requires its exact identity and five addresses")
        if any(t.get("symbol") == key for t in unit.get("link_vtables", [])):
            raise ValueError("reader vtable overlaps another contract")
        seen.add(family)


def inspect_table(pe, address, expected, type_name, candidates=None):
    import linked_pe as core
    raw = core.readonly_data(pe, address, 20)
    entries = list(struct.unpack("<5I", raw))
    if address % 4 or entries != expected or core.primary_type_name(pe, address) != type_name:
        raise ValueError("reader vtable entries or primary RTTI disagree")
    for entry in entries:
        section = pe.get_section_by_rva(entry - pe.OPTIONAL_HEADER.ImageBase)
        if (section is None or not section.Characteristics & 0x20000000
                or (candidates is not None and entry not in candidates)):
            raise ValueError("reader vtable slot is not an executable candidate")
    following, = struct.unpack("<I", core.readonly_data(pe, address + 20, 4))
    section = pe.get_section_by_rva(following - pe.OPTIONAL_HEADER.ImageBase)
    if section is not None and section.Characteristics & 0x20000000:
        raise ValueError("reader vtable has an unsupported sixth slot")
    # The fixed-base target has stripped relocations; its complete table bytes
    # above are pinned. The relocatable source must own all five HIGHLOW fields.
    if candidates is None:
        core.validate_body_relocations(pe, address, 20,
                                      [{"field_offset": 4 * i} for i in range(5)])
    return raw


def witnesses(unit, source, symbols, functions, cil_owner):
    import linked_pe as core
    import pefile
    c = core.comparator()
    known = c.known_data_targets()
    validate(unit, set(known))
    if not unit.get("link_reader_vtables"):
        return []
    c.verify_target()
    target = pefile.PE(str(c.TARGET))
    with (core.ROOT / "config/functions.csv").open(newline="") as stream:
        candidates = {int(r["address"], 0) for r in csv.DictReader(stream)}
    result = []
    for table in unit["link_reader_vtables"]:
        family, key = table["family"], table["target"]
        address, raw, offsets, kind = known[key]
        expected = [int(a, 0) for a in table["entries"]]
        if kind != "address" or offsets != frozenset({0}) or raw != struct.pack("<I", expected[0]):
            raise ValueError("reader vtable target ledger identity disagrees")
        target_raw = inspect_table(target, address, expected, ".?AV" + family + "@@", candidates)
        found = symbols.get(key, [])
        if len(found) != 1 or found[0][1].split()[-1:] != [cil_owner]:
            raise ValueError("reader vtable lacks unique source CIL ownership")
        start = found[0][0]
        actual = []
        for name in slot_symbols(family):
            slots = symbols.get(name, [])
            if len(slots) != 1 or slots[0][1].split()[-1:] != [cil_owner]:
                raise ValueError("reader slot lacks its actual source implementation")
            entry = slots[0][0]
            if len([1 for symbol, owner in functions.get(entry, [])
                    if symbol == name and owner.split()[-1:] == [cil_owner]]) != 1:
                raise ValueError("reader slot map ownership disagrees")
            actual.append(entry)
        inspect_table(source, start, actual, ".?AV" + family + "@th105@@")
        result.append({"symbol": key, "target_key": key, "source_address": start,
                       "target_address": address, "kind": "five-slot-reader",
                       "target_type_name": ".?AV" + family + "@@",
                       "slot_symbols": slot_symbols(family), "source_slots": actual,
                       "target_slots": expected, "target_bytes": target_raw.hex()})
    if len({v["source_address"] for v in result}) != len(result):
        raise ValueError("reader vtable source identities alias")
    return result
