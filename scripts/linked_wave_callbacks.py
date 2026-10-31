"""Four complete exact-backed wave array lifetimes, restricted to code-pointer PUSH."""
from dataclasses import dataclass
import hashlib
import re


GLOBAL = "?g_wave_service_lifetime@th105@@3UWaveServiceLifetime@1@A"
SOURCE = "src/audio/DirectSoundResourceLifetime.cpp"


@dataclass(frozen=True)
class Callback:
    symbol: str
    address: int
    size: int
    sha256: str
    eh: tuple[str, str] | None = None


CALLBACKS = (
    Callback("??0DirectSoundResourceBaseLifetime@th105@@QAE@XZ", 0x418280, 17,
             "bff36e59a71d7dd1450cda961ab291c0caffeb89f80260c5a98618d211df5af4"),
    Callback("??0DirectSoundResourceLifetime@th105@@QAE@XZ", 0x4180B0, 20,
             "ee5e9151bd871bc355eb388a082600b05b8ad6f419d325853d9b05aeb1f45819"),
    Callback("??1DirectSoundResourceBaseLifetime@th105@@UAE@XZ", 0x4182E0, 33,
             "41fe59632cf07de55e1779fd0e96001b76e79db8121272f3d6c8397047199eb9"),
    Callback("??1DirectSoundResourceLifetime@th105@@UAE@XZ", 0x4180F0, 139,
             "8f3d9a872923a79faa1ee3516b93ac370d61e5059a09ca603fc948400ae3a08a",
             ("0x006BD658", "0x006E3C30")),
)
TARGETS = {
    "??1DirectSoundResourceBaseLifetime@th105@@UAE@XZ": 0x4182E0,
    "@__security_check_cookie@4": 0x689D25,
    "___CxxFrameHandler3": 0x6899E7,
}


def validate(unit):
    enabled = unit.get("link_wave_lifetime_callbacks", False)
    if type(enabled) is not bool:
        raise ValueError("wave lifetime callback proof requires an explicit boolean")
    if not enabled:
        return
    objects = unit.get("link_objects", [])
    owned = [o for o in objects if isinstance(o, dict) and o.get("symbol") == GLOBAL]
    if (unit.get("link_runtime") != "static"
            or unit.get("link_runtime_data") != ["___security_cookie"]
            or len(owned) != 1 or owned[0].get("size") != 0x458
            or owned[0].get("target") != "wave_service_lifetime_object"):
        raise ValueError("wave callbacks require the complete source-owned wave service")
    expected = {
        ("0x00401880", "??0WaveServiceLifetime@th105@@QAE@XZ", "constructor"),
        ("0x00401910", "??1WaveServiceLifetime@th105@@QAE@XZ", "destructor"),
    }
    actual = {(f.get("address"), f.get("symbol_base"), f["private_global"].get("role"))
              for f in unit.get("functions", []) if isinstance(f, dict)
              and isinstance(f.get("private_global"), dict)
              and f["private_global"].get("object") == GLOBAL}
    if actual != expected:
        raise ValueError("wave callbacks require the real global constructor/destructor pair")


def typed_push_allowed(ref):
    """No caller-supplied target, prefix-only proof, alternate size or code read."""
    return any(ref.get("kind") == "wave_lifetime_callback"
               and ref.get("symbol") == c.symbol and ref.get("address") == c.address
               and ref.get("size") == c.size and ref.get("callback_exact") is True
               and ref.get("canonical_sha256") == c.sha256
               and ref.get("target_sha256") == c.sha256 for c in CALLBACKS)


def _verify_callback(spec, pe, target, functions, exports, owner, imports,
                     bindings, vtables, refs, sdk_imports, ledger, read_target):
    import linked_pe as core
    from linked_lifecycle import private_entry, cleanup_eh
    key = f"0x{spec.address:08X}"
    row = ledger.get(key, {})
    if (row.get("status") != "matching" or row.get("source_file") != SOURCE
            or int(row.get("size", -1)) != spec.size):
        raise ValueError("wave callback lacks its existing complete exact source record")
    start = private_entry(functions, exports, spec.symbol, owner)
    raw = core.linked_body(pe, functions, start)
    native = read_target(spec.address, spec.size)
    if (len(raw) != spec.size or len(native) != spec.size
            or hashlib.sha256(native).hexdigest() != spec.sha256):
        raise ValueError("wave callback complete source/target extent or target hash differs")
    game_range = (target.OPTIONAL_HEADER.ImageBase,
                  target.OPTIONAL_HEADER.ImageBase + target.OPTIONAL_HEADER.SizeOfImage)
    image_range = (pe.OPTIONAL_HEADER.ImageBase,
                   pe.OPTIONAL_HEADER.ImageBase + pe.OPTIONAL_HEADER.SizeOfImage)
    def resolve(address):
        return core.resolve_linked_call(address, pe, functions, imports, TARGETS, sdk_imports)
    local, eh = refs, []
    if spec.eh:
        function = {"address": key, "symbol_base": spec.symbol,
                    "eh_cleanup": {"handler": spec.eh[0], "info": spec.eh[1]}}
        local, eh = cleanup_eh(function, pe, target, functions, exports, owner,
                              start, raw, native, refs, bindings, vtables, resolve,
                              game_range, read_target)
        if not eh:
            raise ValueError("wave destructor callback lacks complete cleanup EH")
    canonical, calls, data = core.canonicalize(raw, start, spec.address, bindings,
        resolve, image_range, game_range, vtables, internal_refs=local)
    core.validate_body_relocations(pe, start, len(raw), data)
    if canonical != native:
        raise ValueError("complete wave callback bytes differ")
    return {"kind": "wave_lifetime_callback", "source_address": start,
            "address": spec.address, "size": spec.size, "symbol": spec.symbol,
            "callback_exact": True, "canonical_sha256": hashlib.sha256(canonical).hexdigest(),
            "target_sha256": spec.sha256, "replayed_rel32": calls,
            "data_references": data, "validated_cleanup_eh": eh}


def _validate_global_witness(global_proof):
    expected = [("initializer", 17), ("atexit callback", 5)]
    regions = global_proof.get("regions", [])
    if (global_proof.get("target_address") != 0x702288
            or global_proof.get("size") != 0x458
            or global_proof.get("target_initializer") != 0x6BE6F0
            or global_proof.get("target_initializer_slot") != 0x6C035C
            or global_proof.get("target_callback") != 0x6BEDC0
            or not isinstance(regions, list) or len(regions) != len(expected)
            or any(not isinstance(r, dict) or (r.get("kind"), r.get("size")) != role
                   or not re.fullmatch(r"[0-9a-f]{64}", str(r.get("canonical_sha256", "")))
                   or r.get("canonical_sha256") != r.get("target_sha256")
                   for r, role in zip(regions, expected))):
        raise ValueError("wave callbacks lack a freshly exact global startup witness")


def witnesses(unit, pe, target, functions, exports, owner, imports, bindings,
              vtables, refs, sdk_imports, ledger, read_target, globals_witnesses):
    validate(unit)
    if not unit.get("link_wave_lifetime_callbacks"):
        return []
    from workflow_manifest import ROOT, source_dependencies
    if ROOT / SOURCE not in source_dependencies(unit):
        raise ValueError("wave callbacks need their actual reviewed provider source")
    _validate_global_witness(globals_witnesses.get(GLOBAL, {}))
    # Return no pointer bindings unless every complete callback has passed.
    result = [_verify_callback(c, pe, target, functions, exports, owner, imports,
                               bindings, vtables, refs, sdk_imports, ledger, read_target)
              for c in CALLBACKS]
    if len({r["source_address"] for r in result}) != len(CALLBACKS):
        raise ValueError("wave callback roles alias a source entry")
    return result
