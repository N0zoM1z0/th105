"""Direct member constructors from freshly exact, fully witnessed global constructors."""
import re


def constructor_vtable(symbol):
    import linked_pe as core
    if not isinstance(symbol, str) or not symbol.startswith("??0") or not symbol.endswith("@@QAE@XZ"):
        return None
    table = "??_7" + symbol[3:-6] + "6B@"
    return table if core.single_destructor_vtable_owner(table) is not None else None


def validate(function, caller, unit):
    contract = function.get("private_from")
    parent = caller.get("private_global")
    if (not isinstance(contract, dict)
            or set(contract) != {"caller", "site", "through_exact_caller"}
            or contract.get("through_exact_caller") is not True
            or contract.get("caller") != caller.get("address")
            or not re.fullmatch(r"0x[0-9A-Fa-f]{8}", str(contract.get("site", "")))
            or function.get("address") == caller.get("address")
            or any(k in function for k in ("export_name", "private_global", "vtable_entry", "private_static_leaf"))
            or not isinstance(parent, dict) or set(parent) != {"object", "role"}
            or parent.get("role") != "constructor"
            or "private_from" in caller or "export_name" in caller
            or "eh_cleanup" not in caller or "eh_cleanup" not in function):
        raise ValueError("global member entry requires direct exact constructor and complete cleanup proofs")
    for node in (function, caller):
        eh = node["eh_cleanup"]
        if (not isinstance(eh, dict) or set(eh) != {"handler", "info"}
                or any(not re.fullmatch(r"0x[0-9A-Fa-f]{8}", str(v)) for v in eh.values())):
            raise ValueError("global member entry needs exact handler and FuncInfo identities")
    table = constructor_vtable(function.get("symbol_base"))
    if (table is None
            or sum(isinstance(t, dict) and t.get("symbol") == table for t in unit.get("link_vtables", [])) != 1):
        raise ValueError("global member constructor needs its actual typed polymorphic class")
    objects = [o for o in unit.get("link_objects", [])
               if isinstance(o, dict) and o.get("symbol") == parent.get("object")]
    if len(objects) != 1:
        raise ValueError("global member entry lacks its uniquely owned global object")
    return objects[0]


def observe(function, caller, unit, report, fresh_globals):
    obj = validate(function, caller, unit)
    fresh = (fresh_globals or {}).get(obj["symbol"])
    retained = report.get("global_lifecycle_witness")
    eh = report.get("validated_cleanup_eh")
    if (not isinstance(fresh, dict) or retained != fresh
            or fresh.get("symbol") != obj["symbol"] or fresh.get("size") != obj["size"]
            or fresh.get("target_initializer") != int(obj["initializer"], 0)
            or fresh.get("target_initializer_slot") != int(obj["initializer_table"], 0)
            or fresh.get("target_callback") != int(obj["destructor_callback"], 0)
            or type(fresh.get("source_address")) is not int
            or type(fresh.get("target_address")) is not int
            or not isinstance(eh, list) or not eh):
        raise ValueError("global member entry lacks current exact global storage/startup/EH evidence")
    regions = fresh.get("regions", [])
    if (not isinstance(regions, list)
            or any(not isinstance(r, dict) for r in regions)
            or [(r.get("kind"), r.get("size")) for r in regions]
               != [("initializer", 17), ("atexit callback", 5)]
            or any(not isinstance(r, dict)
                   or not re.fullmatch(r"[0-9a-f]{64}", str(r.get("canonical_sha256", "")))
                   or r.get("canonical_sha256") != r.get("target_sha256")
                   for r in [*regions, *eh])):
        raise ValueError("global member entry has incomplete or mismatching startup/cleanup regions")
    count = len(eh) - 3
    kinds = [r["kind"] for r in eh]
    if (count < 1 or kinds != ["cleanup handler"]
            + [f"cleanup funclet {i}" for i in range(count)] + ["FuncInfo", "unwind map"]
            or eh[0].get("target_address") != int(caller["eh_cleanup"]["handler"], 0)
            or eh[-2].get("target_address") != int(caller["eh_cleanup"]["info"], 0)
            or eh[-2].get("size") != 36 or eh[-1].get("size") != count * 8):
        raise ValueError("global member entry needs every configured parent cleanup region")
    return {"global_lifecycle_witness": fresh, "validated_cleanup_eh": eh}
