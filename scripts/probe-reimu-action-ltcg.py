#!/usr/bin/env python3
"""Link the generated Reimu root with genuine source implementations and VC8 CRT.

Diagnostic only: no root exactness, original TU, or gameplay-equivalence claim.
The checked deque provider stays ordinary COFF, preserving its verified ABI.
"""
from __future__ import annotations

import argparse
import importlib.util
import json
import os
from pathlib import Path
import re
import struct
import subprocess
import sys
import tomllib

import capstone
import pefile

import linked_pe
from workflow_manifest import unit_input_digest

ROOT = Path(__file__).resolve().parents[1]
UNIT = "private-reimu-root-ltcg"
SYMBOL = "?run_action_dispatch_root@ReimuActionStatePreludeView@th105@@QAEXXZ"
DEPENDENCIES = (
    0x401D50, 0x406360, 0x4063D0, 0x406540, 0x4066B0, 0x4067D0, 0x417800,
    0x427280, 0x42CF70, 0x432D20, 0x432DE0, 0x434E90, 0x435110, 0x4351A0,
    0x4351C0, 0x435240, 0x435910, 0x4359D0, 0x4359F0, 0x435CE0, 0x435D60,
    0x435DC0, 0x43AC40, 0x43AF20, 0x43B070, 0x43B1A0, 0x43C150, 0x45AF40,
    0x45B250, 0x45C030, 0x45D110, 0x45DEB0, 0x45F560, 0x465190, 0x4652B0,
    0x469D50, 0x469DF0, 0x46BF30, 0x46E9D0, 0x473DD0, 0x473F90, 0x4740C0,
    0x4776C0, 0x478DD0, 0x478DF0, 0x478E60, 0x478EE0, 0x5F9310,
)
# The handle lookup's EH/private vector boundary is already source-present,
# deliberately nonexact. Do not silently admit another nonexact dependency.
NONEXACT_DEPENDENCIES = {0x417800, 0x406360, 0x4063D0, 0x4740C0, 0x42CF70}


# Keep the actual required method bodies, declarations, types and globals.
# This is a diagnostic source partition, not recovered original TU ownership.
METHOD_SELECTIONS = {
    "cross-v106a-animation-sequence-dispatch": ({"dispatch_character_wave_handle"}, {"forward_hit_quantity"}),
    "cross-v106a-character-object-runtime": (
        {"advance_frame_and_dispatch"},
        {"set_oriented_components_f0_f4", "advance_state_six_counter_conditional",
         "advance_phase_counter_conditional"}),
    "cross-v106a-shared-battle-phase": (
        {"emit_fighter_effect_433cc0"},
        {"run_shared_battle_phase_sequence", "run_battle_phase_and_info_callback"}),
    "cross-v106a-battle-background-layout": (
        {"set_runtime_scalar"}, {"place_sprite"}),
    "cross-v106a-event-effect-state": (
        {"set_event_id", "emit_effect"},
        {"dispatch_emitter_state", "render_background_effects"}),
    "gpt-web-event-effect-state-runtime": (
        {"publish_stage_state_469d50"},
        {"prepare_shutdown_469ec0", "reset_runtime_state_469f40"}),
}


_shared_spec = importlib.util.spec_from_file_location("reimu_link_shared", ROOT / "scripts/probe-common-fighter-ltcg.py")
_shared = importlib.util.module_from_spec(_shared_spec)
_shared_spec.loader.exec_module(_shared)
load_inspector = _shared.load_inspector
select_methods = _shared.select_methods
coff_symbols = _shared.coff_symbols
unresolved_names = _shared.unresolved_names
attest_data = _shared.attest_data


_iku_spec = importlib.util.spec_from_file_location("reimu_existing_iku_link", ROOT / "scripts/probe-iku-action-ltcg.py")
_iku = importlib.util.module_from_spec(_iku_spec)
_iku_spec.loader.exec_module(_iku)
FREE_SELECTIONS = _iku.FREE_SELECTIONS
select_free = _iku.select_free


def prepare_units(out):
    spec = importlib.util.spec_from_file_location("reimu_link_shape", ROOT / "scripts/probe-reimu-action-source-shape.py")
    shape = importlib.util.module_from_spec(spec)
    sys.modules[spec.name] = shape
    spec.loader.exec_module(shape)
    _, _, _, inputs = shape.generate(out / "root-input", void_root=True)
    header = "ReimuActionStateStaging.hpp"
    (out / header).write_bytes((out / "root-input" / header).read_bytes())
    word_source = out / "Word48a.cpp"
    word_source.write_bytes((
        '#include <stddef.h>\nnamespace th105 {\n'
        'struct FighterWord48aLinkView {\n'
        '    unsigned char reserved_000[0x48a];\n'
        '    short word_48a;\n'
        '    void set_word_48a(short value);\n};\n'
        'typedef char Word48a_offset[(offsetof(FighterWord48aLinkView, word_48a)==0x48a)?1:-1];\n'
        'void FighterWord48aLinkView::set_word_48a(short value) { word_48a=value; }\n'
        '}\n').replace('\n', '\r\n').encode())
    units = tomllib.loads((ROOT / "config/match-units.toml").read_text())["units"]
    binding = tomllib.loads((ROOT / "config/reimu-root-probe-bindings.toml").read_text())
    unit = {"kind":"probe", "profile":"vc8-sp1-probe-o2", "enable_gs":False,
            "source":str((out / "root-input/ReimuActionStateDispatch.cpp").relative_to(ROOT)),
            "object":str((out / "root.obj").relative_to(ROOT)),
            "functions":[{"address":"0x00478FA0", "size":81550, "symbol_base":SYMBOL,
                "rel32_targets":[name+"="+address for name,address in binding["rel32"].items()],
                "dir32_targets":["?g_match_identifier@th105@@3HA=?g_match_identifier@th105@@3HA"]}]}
    units[UNIT] = unit
    units["private-reimu-word48a"] = {"kind":"probe", "profile":unit["profile"], "enable_gs":False,
        "source":str(word_source.relative_to(ROOT)), "object":str((out / "Word48a.obj").relative_to(ROOT)),
        "functions":[{"address":"0x004776C0", "size":15,
            "symbol_base":"?set_word_48a@FighterWord48aLinkView@th105@@QAEXF@Z",
            "rel32_targets":[], "dir32_targets":[]}]}
    return units, inputs


def linked_provider_witnesses(pe, map_path, canonical, actuals):
    """Check the actual selected SDK COMDATs and the WORD48A leaf after linking."""
    symbols = {}
    for address, names in linked_pe.parse_map(map_path.read_text()).items():
        for name, _ in names:
            symbols.setdefault(name, set()).add(address)
    invalid, = symbols['__invalid_parameter_noinfo']
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    decoder.detail = True
    result = {}
    for target, size in ((0x4399C0, 94), (0x42D1B0, 100), (0x4776C0, 15)):
        start, = symbols[actuals[target]]
        if any(entry.type and start <= pe.OPTIONAL_HEADER.ImageBase + entry.rva < start + size
               for block in pe.DIRECTORY_ENTRY_BASERELOC for entry in block.entries):
            raise ValueError('provider witness unexpectedly needs pointer relocation')
        body = bytearray(pe.get_data(start - pe.OPTIONAL_HEADER.ImageBase, size))
        rows = list(decoder.disasm(body, start))
        if sum(row.size for row in rows) != size:
            raise ValueError('truncated linked provider witness')
        for row in rows:
            if row.mnemonic == 'call':
                if bytes(row.bytes[:1]) != b'\xe8' or row.size != 5 or row.operands[0].imm != invalid:
                    raise ValueError('linked SDK witness has an unexpected callee')
                offset = row.address - start + 1
                struct.pack_into('<I', body, offset, (0x68A143 - (target + offset + 4)) & 0xFFFFFFFF)
        if bytes(body) != canonical.target_bytes(target, size):
            raise ValueError('selected linked provider differs from its complete target witness')
        result[hex(target)] = {'size': size, 'linked_address': hex(start), 'target_equal': True,
                               'scope': 'provider witness only; no new authored credit'}
    return result


def probe(output):
    canonical = linked_pe.comparator()
    target_sha = canonical.verify_target()
    tools, pins = linked_pe.pinned_tools()
    inspector = load_inspector()
    out = output.resolve()
    if not out.is_relative_to(ROOT / "build") or out == ROOT / "build":
        raise ValueError("link products must occupy a subdirectory of build/")
    out.mkdir(parents=True, exist_ok=True)
    units, root_input = prepare_units(out)
    root_unit = units[UNIT]
    root_function, = root_unit["functions"]
    index = {}
    for name, unit in units.items():
        for function in unit.get("functions", []):
            index.setdefault(int(function["address"], 0), []).append((name, function))
    selected = {}
    for address in DEPENDENCIES:
        name, function = index[address][0]
        if len(index[address]) != 1:
            raise ValueError("ambiguous dependency source selection")
        selected[address] = (name, function)

    environment = os.environ.copy()
    environment.update(WINEPREFIX=str(ROOT / ".tools/wine-msvc8"),
                       WINEARCH="win32", WINEDEBUG="-all")
    for key in ("CL", "_CL_", "LINK", "_LINK_", "INCLUDE", "LIB", "LIBPATH"):
        environment[key] = ""

    def win(path):
        return "Z:" + str(path).replace("/", "\\")

    def compile_source(source, obj, unit, extra=(), source_directory=None):
        flags = ["/nologo", "/c", "/O2", "/GS" if unit["enable_gs"] else "/GS-",
                 "/GR", "/EHsc", "/MT", *extra]
        if unit["profile"] == "vc8-sp1-probe-o2-fp-strict":
            flags.append("/fp:strict")
        includes = [ROOT / "src", tools / "include", tools / "PlatformSDK/Include"]
        if source_directory:
            includes.append(source_directory)
        includes.extend(ROOT / path for path in unit.get("include_dirs", []))
        command = ["wine", str(tools / "bin/cl.exe"), *flags,
                   *("/I" + win(path) for path in includes), "/Fo" + win(obj), win(source)]
        shadow = dict(unit)
        shadow["source"] = str(source.relative_to(ROOT))
        shadow["include_dirs"] = [*unit.get("include_dirs", []),
            *([str(source_directory.relative_to(ROOT))] if source_directory else [])]
        digest = unit_input_digest("private-reimu-provider", shadow)[0]
        cache_path = obj.with_suffix(".compile-receipt.json")
        inputs = {"command":command,"input_digest":digest,"source_sha256":linked_pe.sha(source),
                  "compiler_sha256":linked_pe.sha(tools / "bin/cl.exe"), "tool_pins":pins}
        if cache_path.exists() and obj.exists():
            cached = json.loads(cache_path.read_text())
            if cached.get("inputs")==inputs and cached.get("object_sha256")==linked_pe.sha(obj):
                print("reuse pinned", obj.name, flush=True)
                return command
        print("compile", source.name, flush=True)
        inspector.run(command, environment, obj.with_suffix(".compile.log"))
        cache_path.write_text(json.dumps({"inputs":inputs,"object_sha256":linked_pe.sha(obj)},indent=2)+"\n")
        return command

    objects, dependencies, definitions, undefined = {}, {}, {}, set()
    targets = {key: {value} for key, value in canonical.known_targets().items()}
    data_keys = {key: {key} for key in canonical.known_data_targets()}

    def add_contract(function):
        for item in function.get("rel32_targets", []):
            key, value = item.split("=", 1)
            targets.setdefault(key, set()).add(int(value, 0))
        for item in function.get("dir32_targets", []):
            key, value = item.split("=", 1)
            data_keys.setdefault(key, set()).add(value)

    add_contract(root_function)
    for name in dict.fromkeys(name for name, _ in selected.values()):
        unit = units[name]
        original = ROOT / unit["source"]
        source = original
        selection = METHOD_SELECTIONS.get(name)
        if selection:
            source = out / (name + ".cpp")
            source.write_bytes(select_methods(original.read_text(), *selection)
                               .replace("\n", "\r\n").encode())
        if name in FREE_SELECTIONS:
            source = out / (name + ".cpp")
            source.write_bytes(select_free(original.read_text(), *FREE_SELECTIONS[name]).replace("\n", "\r\n").encode())
        obj = out / (name + ".obj")
        command = compile_source(source, obj, unit, ("/Gy",), original.parent)
        objects[name] = obj
        dependencies[name] = {
            "source": unit["source"], "source_sha256": linked_pe.sha(original),
            "provider_source":str(source.relative_to(ROOT)),
            "provider_sha256": linked_pe.sha(source), "object_sha256": linked_pe.sha(obj),
            "unit_input_digest": unit_input_digest(name, unit)[0], "command": command,
            "retained_methods": sorted(selection[0]) if selection else None,
        }
        definitions[name], missing = coff_symbols(obj)
        undefined.update(missing)
        for function in unit["functions"]:
            add_contract(function)

    actuals, comparisons = {}, {}
    for address, (name, function) in selected.items():
        candidates = [symbol for symbol in definitions[name]
                      if canonical.is_function_symbol(symbol, function["symbol_base"])]
        if len(candidates) != 1:
            raise ValueError("required source provider does not define a unique function")
        actuals[address] = candidates[0]
        if address == 0x4776C0:
            body = canonical.coff_symbol_bytes(objects[name], candidates[0], address, 15, {}, canonical.known_data_targets(), {})
            if body != canonical.target_bytes(address, 15):
                raise ValueError("private WORD48A provider is not the exact original 15-byte body")
            comparisons[hex(address)] = {"private_provider": True, "bytes": 15, "result": "exact", "credit": False}
            continue
        command = [sys.executable, str(ROOT / "scripts/compare-unit-object.py"), name,
                   str(objects[name].relative_to(ROOT)), "--address", hex(address), "--json"]
        result = subprocess.run(command, cwd=ROOT, env=environment, capture_output=True, text=True)
        report = json.loads(result.stdout)
        if result.returncode not in (0, 1) or (result.returncode and address not in NONEXACT_DEPENDENCIES):
            raise ValueError(f"dependency comparison rejected at {address:#x}: {result.stdout}")
        if any(item["result"] == "error" for item in report["comparisons"]):
            raise ValueError("dependency comparison failed before byte comparison")
        comparisons[hex(address)] = report

    actuals[0x4399C0] = inspector.DEQUE_SYMBOL
    actuals[0x42D1B0] = '??A?$deque@IV?$allocator@I@std@@@std@@QAEAAII@Z'
    undefined.update(item.split("=", 1)[0] for item in root_function["rel32_targets"])
    aliases = {}
    for symbol in sorted(undefined):
        addresses = targets.get(symbol, set())
        if len(addresses) == 1:
            actual = actuals.get(next(iter(addresses)))
            if actual and actual != symbol:
                aliases[symbol] = actual

    instance = inspector.DEQUE_INSTANCE
    source = out / "ReimuRoot.cpp"
    text = (ROOT / root_unit["source"]).read_text()
    if text.count("namespace th105 {") != 1:
        raise ValueError("unexpected root source namespace")
    source.write_bytes(text.replace("\n", "\r\n").encode())
    provider = out / "NativeDeque.cpp"
    provider.write_text('#include "battle/SpellRuntime.hpp"\n#include <deque>\n' + instance + "\ntemplate unsigned& std::deque<unsigned>::operator[](size_type);\n")
    root_obj, provider_obj, ordinary_obj = out / "root.obj", out / "provider.obj", out / "ordinary.obj"
    commands = [compile_source(provider, provider_obj, root_unit),
                compile_source(ROOT / root_unit["source"], ordinary_obj, root_unit),
                compile_source(source, root_obj, root_unit, ("/GL",))]
    witness = canonical.coff_symbol_bytes(
        provider_obj, inspector.DEQUE_SYMBOL, 0x4399C0, 94,
        {"__invalid_parameter_noinfo": 0x68A143}, canonical.known_data_targets(), {})
    if witness != canonical.target_bytes(0x4399C0, 94):
        raise ValueError("SDK provider no longer reproduces the target deque ABI/body")

    texture_witness = canonical.coff_symbol_bytes(provider_obj,
        "??A?$deque@IV?$allocator@I@std@@@std@@QAEAAII@Z", 0x42D1B0, 100,
        {"__invalid_parameter_noinfo": 0x68A143}, canonical.known_data_targets(), {})
    if texture_witness != canonical.target_bytes(0x42D1B0, 100):
        raise ValueError("SDK texture-deque provider does not reproduce the entire 100-byte target")
    print("SDK witnesses exact: slot deque94/94 and texture deque100/100; private WORD48A15/15", flush=True)
    (out / "prelink-receipt.json").write_text(json.dumps({
        "target_sha256":target_sha,"tool_pins":pins,"dependencies":dependencies,
        "comparisons":comparisons,"same_target_symbol_aliases":aliases,
        "root_object_sha256":linked_pe.sha(root_obj),"provider_object_sha256":linked_pe.sha(provider_obj),
        "compile_commands":commands,"sdk_witnesses":{"0x4399c0":94,"0x42d1b0":100},
        "scope":"genuine pre-link inputs; no linked-image or root exactness claim"},indent=2)+"\n")

    libraries = [tools / path for path in (
        "lib/libcmt.lib", "lib/libcpmt.lib", "lib/oldnames.lib",
        "PlatformSDK/Lib/Kernel32.Lib", "PlatformSDK/Lib/User32.Lib",
        "PlatformSDK/Lib/AdvAPI32.Lib")]
    image, map_path = out / "ReimuRoot.dll", out / "ReimuRoot.map"
    data_obj, bindings = out / "data-bindings.obj", {}
    target_pe = pefile.PE(str(ROOT / "resources/th105.exe"))
    # One initial link discovers data references; one retry binds only those
    # attested data symbols. Any missing function remains a hard failure.
    link_commands = []
    for attempt in range(2):
        data_obj.write_bytes(linked_pe.absolute_data_object(list(bindings.values())))
        command = ["wine", str(tools / "bin/link.exe"), "/nologo", "/DLL", "/LTCG",
                   "/NODEFAULTLIB", "/OPT:REF", "/OPT:NOICF", "/INCREMENTAL:NO",
                   "/BASE:0x10000000", "/EXPORT:" + SYMBOL,
                   "/MAP:" + win(map_path), "/OUT:" + win(image)]
        command.extend("/alternatename:" + name + "=" + actual
                       for name, actual in sorted(aliases.items()))
        command.extend(win(path) for path in
                       [provider_obj, root_obj, *objects.values(), data_obj, *libraries])
        link_commands.append(command)
        result = subprocess.run(command, env=environment, capture_output=True, text=True)
        log = result.stdout + result.stderr
        (out / f"link-{attempt}.log").write_text(log)
        if result.returncode == 0 and not re.search(r"warning LNK|error LNK", log):
            break
        missing = unresolved_names(log)
        if attempt or not missing:
            raise ValueError("genuine link failed: " + log)
        for symbol in missing:
            keys = data_keys.get(symbol, set())
            if len(keys) != 1 or symbol in targets:
                raise ValueError("unresolved input is not unambiguous target data: " + symbol)
            bindings[symbol] = attest_data(canonical, target_pe, symbol, next(iter(keys)))
    else:
        raise ValueError("genuine link did not close")

    inspection = {}
    pe = pefile.PE(str(image))
    linked_witnesses = linked_provider_witnesses(pe, map_path, canonical, actuals)
    exported, = (entry for entry in pe.DIRECTORY_ENTRY_EXPORT.symbols if entry.name == SYMBOL.encode())
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    inspection["entry"] = [
        {"address": hex(item.address), "encoding": item.bytes.hex(),
         "instruction": item.mnemonic + " " + item.op_str}
        for item in decoder.disasm(pe.get_data(exported.address, 100),
                                   pe.OPTIONAL_HEADER.ImageBase + exported.address)][:20]
    entry = pe.get_data(exported.address, 32)
    entry_rows = list(decoder.disasm(entry, pe.OPTIONAL_HEADER.ImageBase + exported.address))
    if any(row.mnemonic=="call" for row in entry_rows) or any(
        item.type==3 and exported.address<=item.rva<exported.address+len(entry)
        for block in pe.DIRECTORY_ENTRY_BASERELOC for item in block.entries):
        raise ValueError("entry witness unexpectedly needs relocation")
    target_entry = canonical.target_bytes(0x478FA0,len(entry))
    first = next((n for n,(a,b) in enumerate(zip(target_entry,entry)) if a!=b),None)
    inspection["relocation_free_entry_comparison"]={"bytes":len(entry),"first_mismatch":first,
        "target_address":hex(0x478FA0+first) if first is not None else None,"scope":"entry witness only"}
    receipt = {
        "schema": "th105-reimu-real-link-v2", "diagnostic_only": True,
        "target_sha256": target_sha, "tool_pins": pins,
        "probe_sha256": linked_pe.sha(Path(__file__)),
        "support_sha256": {name: linked_pe.sha(ROOT / "scripts" / name) for name in
                           ("probe-aya-cpu-ltcg.py", "linked_pe.py", "workflow_manifest.py",
                            "probe-common-fighter-ltcg.py", "probe-iku-action-ltcg.py",
                            "probe-reimu-action-source-shape.py", "audit-reimu-root-relocations.py",
                            "audit-reimu-root-stack.py", "reimu_740_mode_facts.py",
                            "audit-reimu-linked-coff.py")},
        "parser_versions": linked_pe.parser_versions(),
        "root_input":root_input,
        "ordinary_object_sha256":linked_pe.sha(ordinary_obj),
        "address_providers":{hex(address):name for address,(name,_) in selected.items()},
        "callee_symbols":{**{hex(address):name for address,name in actuals.items()}, "0x68a1a0":"__ftol2_sse"},
        "nonexact_dependencies":[hex(address) for address in sorted(NONEXACT_DEPENDENCIES)],
        "linked_provider_witnesses": linked_witnesses,
        "root_source_sha256": linked_pe.sha(ROOT / root_unit["source"]),
        "generated_source_sha256": linked_pe.sha(source),
        "root_object_sha256": linked_pe.sha(root_obj),
        "provider_source_sha256": linked_pe.sha(provider),
        "provider_object_sha256": linked_pe.sha(provider_obj),
        "data_object_sha256": linked_pe.sha(data_obj),
        "image_sha256": linked_pe.sha(image), "map_sha256": linked_pe.sha(map_path),
        "libraries": {str(path.relative_to(tools)): linked_pe.sha(path) for path in libraries},
        "compile_commands": commands, "link_commands": link_commands,
        "dependencies": dependencies, "comparisons": comparisons,
        "same_target_symbol_aliases": aliases, "data_bindings": bindings,
        "inspection": inspection,
        "scope": "real source/CRT link; no stubs, code ABS symbols or unresolved-link overrides; "
                 "same-target bounded-view aliases do not establish original C++ declarations; "
                 "the five listed providers remain nonexact; linked image is not executed or accepted as exact",
    }
    (out / "receipt.json").write_text(json.dumps(receipt, indent=2) + "\n")
    replay_spec = importlib.util.spec_from_file_location("reimu_link_correspondence", ROOT / "scripts/audit-reimu-linked-coff.py")
    replay = importlib.util.module_from_spec(replay_spec)
    sys.modules[replay_spec.name] = replay
    replay_spec.loader.exec_module(replay)
    report = replay.audit(out / "receipt.json")
    (out / "coff-replay.json").write_text(json.dumps(report, indent=2)+"\n")
    return report


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--output-dir", type=Path, default=ROOT / "build/reimu-ltcg")
    args = parser.parse_args()
    try:
        result = probe(args.output_dir)
        print(json.dumps(result, indent=2))
    except (KeyError, OSError, ValueError, RuntimeError) as error:
        print(f"Reimu genuine link failed: {error}", file=sys.stderr)
        raise SystemExit(2)
