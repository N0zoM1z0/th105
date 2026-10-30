"""Source-owned VC8 IEEE literals, restricted to complete x87 memory reads."""
import hashlib
import re

READS = {"fld", "fadd", "fsub", "fsubr", "fmul", "fdiv", "fdivr", "fcom", "fcomp"}


def encoded_bytes(symbol):
    match = re.fullmatch(r"__real@([0-9a-f]{8}|[0-9a-f]{16})", str(symbol))
    if not match:
        raise ValueError("numeric literal must have a complete VC8 IEEE symbol")
    return bytes.fromhex(match[1])[::-1]


def validate(unit, data_keys):
    entries = unit.get("link_numeric_literals", [])
    if not isinstance(entries, list):
        raise ValueError("numeric literals require an explicit list")
    seen = set()
    for entry in entries:
        if (not isinstance(entry, dict) or set(entry) != {"symbol", "target"}
                or not isinstance(entry["symbol"], str)
                or entry["target"] != entry["symbol"]
                or entry["target"] not in data_keys or entry["symbol"] in seen):
            raise ValueError("numeric literal needs its unique existing target identity")
        encoded_bytes(entry["symbol"])
        seen.add(entry["symbol"])


def witnesses(unit, source, target, symbols, known):
    import linked_pe as core
    validate(unit, set(known))
    refs = []
    for entry in unit.get("link_numeric_literals", []):
        symbol = entry["symbol"]
        raw = encoded_bytes(symbol)
        address, expected, addends, kind = known[entry["target"]]
        found = symbols.get(symbol, [])
        if (len(found) != 1
                or found[0][1].split()[-4:] != ["CIL", "library:", "CIL", "module"]
                or expected != raw or addends != frozenset({0}) or kind != "literal"):
            raise ValueError("numeric literal ownership, IEEE bytes or target extent disagree")
        start = found[0][0]
        if (core.readonly_data(source, start, len(raw)) != raw
                or core.readonly_data(target, address, len(raw)) != raw):
            raise ValueError("complete readonly numeric literal bytes differ")
        refs.append({"kind": "number", "symbol": symbol, "source_address": start,
                     "address": address, "size": len(raw),
                     "literal_sha256": hashlib.sha256(raw).hexdigest()})
    return refs
