#!/usr/bin/env python3
"""Link the complete Iku root with genuine source providers and pinned SDK/CRT.

Diagnostic only. Nonexact providers and the provisional float adapter remain
explicit; no original TU, whole-game behavior or exact root claim is made.
"""

from __future__ import annotations

import argparse
import hashlib
import importlib.util
import json
import os
from pathlib import Path
import re
import subprocess
import sys
import tomllib

import capstone
import pefile

import linked_pe
from workflow_manifest import unit_input_digest

ROOT = Path(__file__).resolve().parents[1]
UNIT = "gpt-web-iku-action-state"
SYMBOL = "?dispatch_action_state_vslot28@IkuActionStateView@th105@@QAEXXZ"
DEPENDENCIES = (
    0x401D50,
    0x406360,
    0x4063D0,
    0x406540,
    0x4066B0,
    0x4067D0,
    0x417800,
    0x427280,
    0x427290,
    0x4272B0,
    0x4272D0,
    0x42CF70,
    0x432D20,
    0x432DE0,
    0x434E10,
    0x434E90,
    0x435110,
    0x4351C0,
    0x435240,
    0x435910,
    0x4359D0,
    0x4359F0,
    0x435CE0,
    0x435D60,
    0x435DC0,
    0x43AC40,
    0x43AF20,
    0x43B070,
    0x43B1A0,
    0x43C150,
    0x45AF40,
    0x45B250,
    0x45C030,
    0x45D110,
    0x45DEB0,
    0x45F560,
    0x465190,
    0x4652B0,
    0x469D50,
    0x469DF0,
    0x46BF30,
    0x46E9D0,
    0x473DD0,
    0x473F90,
    0x4740C0,
    0x476AB0,
    0x476AD0,
    0x476AF0,
    0x478DF0,
    0x478E60,
    0x478EE0,
    0x5F9310,
)
# The handle lookup's EH/private vector boundary is already source-present,
# deliberately nonexact. Do not silently admit another nonexact dependency.
NONEXACT_DEPENDENCIES = {0x417800, 0x406360, 0x4063D0, 0x4740C0, 0x42CF70}

# Keep the actual required method bodies, declarations, types and globals.
# This is a diagnostic source partition, not recovered original TU ownership.
METHOD_SELECTIONS = {
    "cross-v106a-character-object-runtime": (
        {"advance_frame_and_dispatch"},
        {
            "set_oriented_components_f0_f4",
            "advance_state_six_counter_conditional",
            "advance_phase_counter_conditional",
        },
    ),
    "cross-v106a-shared-battle-phase": (
        {"emit_fighter_effect_433cc0"},
        {"run_shared_battle_phase_sequence", "run_battle_phase_and_info_callback"},
    ),
    "cross-v106a-battle-background-layout": ({"set_runtime_scalar"}, {"place_sprite"}),
    "cross-v106a-event-effect-state": (
        {"set_event_id", "emit_effect"},
        {"dispatch_emitter_state", "render_background_effects"},
    ),
    "gpt-web-event-effect-state-runtime": (
        {"publish_stage_state_469d50"},
        {"prepare_shutdown_469ec0", "reset_runtime_state_469f40"},
    ),
}


METHOD_SELECTIONS["cross-v106a-shared-event-state"] = (
    {
        "set_target_20_enabled_2c",
        "set_target_24_enabled_2d",
        "set_target_28_enabled_2e",
    },
    {"synchronize_targets"},
)
METHOD_SELECTIONS["cross-v106a-animation-sequence-dispatch"] = (
    {"dispatch_character_wave_handle"},
    {"forward_hit_quantity"},
)

_shared_spec = importlib.util.spec_from_file_location(
    "iku_link_shared", ROOT / "scripts/probe-common-fighter-ltcg.py"
)
_shared = importlib.util.module_from_spec(_shared_spec)
_shared_spec.loader.exec_module(_shared)
load_inspector = _shared.load_inspector
select_methods = _shared.select_methods
coff_symbols = _shared.coff_symbols
unresolved_names = _shared.unresolved_names
attest_data = _shared.attest_data


FREE_SELECTIONS = {
    "cross-v106a-game-mode-getters": ({"get_game_mode"}, {"get_match_setup"}),
    "cross-v106a-input-selection-accessors": (
        {"get_session_setup_option"},
        {
            "get_player_slot_record",
            "invalidate_selected_input",
            "get_selected_input",
            "get_combined_menu_input_counters",
            "get_selected_input_source",
            "set_session_setup_option",
            "get_network_session",
        },
    ),
}


def select_free(source, keep, remove):
    masked = re.sub(
        r'//[^\n]*|/\*[\s\S]*?\*/|"(?:\\.|[^"\\])*"',
        lambda m: re.sub(r"[^\n]", " ", m[0]),
        source,
    )
    spans, observed = [], []
    for match in re.finditer(
        r"^[A-Za-z_][\w \t:*&<>]*[ \t:*&]([A-Za-z_]\w*)[ \t]*\(", masked, re.MULTILINE
    ):
        brace = masked.find("{", match.end())
        semicolon = masked.find(";", match.end())
        if brace < 0 or 0 <= semicolon < brace:
            continue
        name = match[1]
        observed.append(name)
        depth = 1
        end = brace + 1
        while depth and end < len(masked):
            depth += (masked[end] == "{") - (masked[end] == "}")
            end += 1
        if depth:
            raise ValueError("unbalanced free provider body")
        if name in remove:
            spans.append((match.start(), end))
    if len(observed) != len(keep | remove) or set(observed) != keep | remove:
        raise ValueError("free provider inventory changed: " + repr(observed))
    for begin, end in reversed(spans):
        source = source[:begin] + "\n" * source[begin:end].count("\n") + source[end:]
    return source


def reusable_compile(path, obj, inputs):
    if not path.exists() or not obj.exists():
        return False
    try:
        packet = json.loads(path.read_text())
    except (OSError, ValueError):
        return False
    return packet.get("inputs") == inputs and packet.get(
        "object_sha256"
    ) == linked_pe.sha(obj)


def probe(reuse=False):
    canonical = linked_pe.comparator()
    target_sha = canonical.verify_target()
    tools, pins = linked_pe.pinned_tools()
    inspector = load_inspector()
    units = tomllib.loads((ROOT / "config/match-units.toml").read_text())["units"]
    root_unit = units[UNIT]
    (root_function,) = root_unit["functions"]
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

    out = ROOT / "build/iku-action-ltcg"
    out.mkdir(parents=True, exist_ok=True)
    environment = os.environ.copy()
    environment.update(
        WINEPREFIX=str(ROOT / ".tools/wine-msvc8"), WINEARCH="win32", WINEDEBUG="-all"
    )
    for key in ("CL", "_CL_", "LINK", "_LINK_", "INCLUDE", "LIB", "LIBPATH"):
        environment[key] = ""

    def win(path):
        return "Z:" + str(path).replace("/", "\\")

    compilation_steps = []

    def compile_source(
        source, obj, unit, extra=(), source_directory=None, unit_name=UNIT
    ):
        flags = [
            "/nologo",
            "/c",
            "/O2",
            "/GS" if unit["enable_gs"] else "/GS-",
            "/GR",
            "/EHsc",
            "/MT",
            *extra,
        ]
        if unit["profile"] == "vc8-sp1-probe-o2-fp-strict":
            flags.append("/fp:strict")
        includes = [ROOT / "src", tools / "include", tools / "PlatformSDK/Include"]
        if source_directory:
            includes.append(source_directory)
        includes.extend(ROOT / path for path in unit.get("include_dirs", []))
        command = [
            "wine",
            str(tools / "bin/cl.exe"),
            *flags,
            *("/I" + win(path) for path in includes),
            "/Fo" + win(obj),
            win(source),
        ]
        inputs = {
            "command": command,
            "source_sha256": linked_pe.sha(source),
            "unit_input_digest": unit_input_digest(unit_name, unit)[0],
            "tools": pins,
        }
        cache = obj.with_suffix(".compile.json")
        reused = reuse and reusable_compile(cache, obj, inputs)
        if not reused:
            inspector.run(command, environment, obj.with_suffix(".compile.log"))
            cache.write_text(
                json.dumps(
                    {"inputs": inputs, "object_sha256": linked_pe.sha(obj)}, indent=2
                )
                + "\n"
            )
        compilation_steps.append(
            {
                "object": str(obj.relative_to(ROOT)),
                "reused": reused,
                "cache_sha256": linked_pe.sha(cache),
            }
        )
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
        if selection or name in FREE_SELECTIONS:
            source = out / (name + ".cpp")
            selector = select_methods if selection else select_free
            selection = selection or FREE_SELECTIONS[name]
            source.write_bytes(
                selector(original.read_text(), *selection)
                .replace("\n", "\r\n")
                .encode()
            )
        obj = out / (name + ".obj")
        command = compile_source(
            source, obj, unit, ("/Gy",), original.parent, unit_name=name
        )
        objects[name] = obj
        dependencies[name] = {
            "source": unit["source"],
            "source_sha256": linked_pe.sha(original),
            "provider_sha256": linked_pe.sha(source),
            "object_sha256": linked_pe.sha(obj),
            "unit_input_digest": unit_input_digest(name, unit)[0],
            "command": command,
            "retained_methods": sorted(selection[0]) if selection else None,
        }
        definitions[name], missing = coff_symbols(obj)
        undefined.update(missing)
        for function in unit["functions"]:
            add_contract(function)

    abs_source, abs_object = out / "FloatAbs.cpp", out / "FloatAbs.obj"
    abs_source.write_bytes(
        b"#include <math.h>\r\n#pragma function(fabs)\r\nnamespace th105 { float absolute_scalar_float(float value) { return static_cast<float>(::fabs(static_cast<double>(value))); } }\r\n"
    )
    abs_command = compile_source(abs_source, abs_object, root_unit)
    objects["provisional-float-abs"] = abs_object
    abs_defined, abs_missing = coff_symbols(abs_object)
    undefined.update(abs_missing)
    abs_symbol = "?absolute_scalar_float@th105@@YAMM@Z"
    if abs_symbol not in abs_defined:
        raise ValueError("real float adapter definition missing")
    actuals, comparisons = {0x406330: abs_symbol}, {}

    for address, (name, function) in selected.items():
        candidates = [
            symbol
            for symbol in definitions[name]
            if canonical.is_function_symbol(symbol, function["symbol_base"])
        ]
        if len(candidates) != 1:
            raise ValueError(
                "required source provider does not define a unique function"
            )
        actuals[address] = candidates[0]
        command = [
            sys.executable,
            str(ROOT / "scripts/compare-unit-object.py"),
            name,
            str(objects[name].relative_to(ROOT)),
            "--address",
            hex(address),
            "--json",
        ]
        result = subprocess.run(
            command, cwd=ROOT, env=environment, capture_output=True, text=True
        )
        report = json.loads(result.stdout)
        if result.returncode not in (0, 1) or (
            result.returncode and address not in NONEXACT_DEPENDENCIES
        ):
            raise ValueError(
                f"dependency comparison rejected at {address:#x}: {result.stdout}"
            )
        if any(item["result"] == "error" for item in report["comparisons"]):
            raise ValueError("dependency comparison failed before byte comparison")
        comparisons[hex(address)] = report

    actuals[0x4399C0] = inspector.DEQUE_SYMBOL
    actuals[0x42D1B0] = "??A?$deque@IV?$allocator@I@std@@@std@@QAEAAII@Z"
    undefined.update(item.split("=", 1)[0] for item in root_function["rel32_targets"])
    aliases = {}
    for symbol in sorted(undefined):
        addresses = targets.get(symbol, set())
        if len(addresses) == 1:
            actual = actuals.get(next(iter(addresses)))
            if actual and actual != symbol:
                aliases[symbol] = actual

    instance = inspector.DEQUE_INSTANCE
    source = out / "IkuRoot.cpp"
    text = (ROOT / root_unit["source"]).read_text()
    if text.count("namespace th105 {") != 1:
        raise ValueError("unexpected root source namespace")
    source.write_bytes(text.replace("\n", "\r\n").encode())
    provider = out / "NativeDeque.cpp"
    provider.write_text(
        '#include "battle/SpellRuntime.hpp"\n#include <deque>\n' + instance + "\n"
    )
    provider.write_text(
        provider.read_text()
        + "template unsigned& std::deque<unsigned>::operator[](size_type);\n"
    )
    root_obj, provider_obj = out / "root.obj", out / "provider.obj"
    commands = [
        compile_source(provider, provider_obj, root_unit),
        compile_source(
            source, root_obj, root_unit, ("/GL",), (ROOT / root_unit["source"]).parent
        ),
    ]
    witness = canonical.coff_symbol_bytes(
        provider_obj,
        inspector.DEQUE_SYMBOL,
        0x4399C0,
        94,
        {"__invalid_parameter_noinfo": 0x68A143},
        canonical.known_data_targets(),
        {},
    )
    if witness != canonical.target_bytes(0x4399C0, 94):
        raise ValueError("SDK provider no longer reproduces the target deque ABI/body")

    texture_witness = canonical.coff_symbol_bytes(
        provider_obj,
        "??A?$deque@IV?$allocator@I@std@@@std@@QAEAAII@Z",
        0x42D1B0,
        100,
        {"__invalid_parameter_noinfo": 0x68A143},
        canonical.known_data_targets(),
        {},
    )
    if texture_witness != canonical.target_bytes(0x42D1B0, 100):
        raise ValueError("SDK texture deque differs")
    libraries = [
        tools / path
        for path in (
            "lib/libcmt.lib",
            "lib/libcpmt.lib",
            "lib/oldnames.lib",
            "PlatformSDK/Lib/Kernel32.Lib",
            "PlatformSDK/Lib/User32.Lib",
            "PlatformSDK/Lib/AdvAPI32.Lib",
        )
    ]
    image, map_path = out / "IkuRoot.dll", out / "IkuRoot.map"
    data_obj, bindings = out / "data-bindings.obj", {}
    target_pe = pefile.PE(str(ROOT / "resources/th105.exe"))
    # One initial link discovers data references; one retry binds only those
    # attested data symbols. Any missing function remains a hard failure.
    link_commands = []
    for attempt in range(2):
        data_obj.write_bytes(linked_pe.absolute_data_object(list(bindings.values())))
        command = [
            "wine",
            str(tools / "bin/link.exe"),
            "/nologo",
            "/DLL",
            "/LTCG",
            "/NODEFAULTLIB",
            "/OPT:REF",
            "/OPT:NOICF",
            "/INCREMENTAL:NO",
            "/BASE:0x10000000",
            "/EXPORT:" + SYMBOL,
            "/MAP:" + win(map_path),
            "/OUT:" + win(image),
        ]
        command.extend(
            "/alternatename:" + name + "=" + actual
            for name, actual in sorted(aliases.items())
        )
        command.extend(
            win(path)
            for path in [
                provider_obj,
                root_obj,
                *objects.values(),
                data_obj,
                *libraries,
            ]
        )
        link_commands.append(command)
        result = subprocess.run(
            command, env=environment, capture_output=True, text=True
        )
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
                raise ValueError(
                    "unresolved input is not unambiguous target data: " + symbol
                )
            bindings[symbol] = attest_data(
                canonical, target_pe, symbol, next(iter(keys))
            )
    else:
        raise ValueError("genuine link did not close")

    inspection = inspector.inspect_linked_root(
        image,
        map_path,
        canonical,
        symbol=SYMBOL,
        root_name="iku-vslot28",
        switch_count=3,
        aliases=aliases,
        allow_loop_alignment=True,
    )
    pe = pefile.PE(str(image))
    (exported,) = (
        entry
        for entry in pe.DIRECTORY_ENTRY_EXPORT.symbols
        if entry.name == SYMBOL.encode()
    )
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    decoder.detail = True
    inspection["entry"] = [
        {
            "address": hex(item.address),
            "encoding": item.bytes.hex(),
            "instruction": item.mnemonic + " " + item.op_str,
        }
        for item in decoder.disasm(
            pe.get_data(exported.address, 100),
            pe.OPTIONAL_HEADER.ImageBase + exported.address,
        )
    ][:20]
    prefix = pe.get_data(exported.address, 101)
    if any(
        entry.type == 3 and exported.address <= entry.rva < exported.address + 101
        for block in pe.DIRECTORY_ENTRY_BASERELOC
        for entry in block.entries
    ):
        raise ValueError("entry comparison unexpectedly needs pointer relocation")
    if any(
        item.group(capstone.CS_GRP_CALL)
        for item in decoder.disasm(
            prefix, pe.OPTIONAL_HEADER.ImageBase + exported.address
        )
    ):
        raise ValueError("entry comparison unexpectedly needs a call relocation")
    target_prefix = canonical.target_bytes(0x620920, len(prefix))
    first = next(
        (n for n, (a, b) in enumerate(zip(target_prefix, prefix)) if a != b), None
    )
    inspection["relocation_free_entry_comparison"] = {
        "bytes": len(prefix),
        "first_mismatch": first,
        "target_address": hex(0x620920 + first) if first is not None else None,
        "scope": "Entry witness only, not a canonical full-function comparison",
    }
    normalized_functions = inspector.normalize_map_aliases(
        linked_pe.parse_map(map_path.read_text()), aliases
    )
    (native_uint,) = [
        address
        for address, names in normalized_functions.items()
        if any(name == actuals[0x42D1B0] for name, _ in names)
    ]

    def resolve_invalid(address):
        if [name for name, _ in normalized_functions.get(address, [])] != [
            "__invalid_parameter_noinfo"
        ]:
            raise ValueError("texture deque runtime identity differs")
        return "__invalid_parameter_noinfo", 0x68A143

    uint_code = linked_pe.linked_body(pe, normalized_functions, native_uint)
    uint_replay, uint_calls, _ = linked_pe.canonicalize(
        uint_code,
        native_uint,
        0x42D1B0,
        [],
        resolve_invalid,
        (0x10000000, 0x20000000),
        (0x400000, 0x706000),
    )
    if uint_replay != canonical.target_bytes(0x42D1B0, 100):
        raise ValueError("linked texture deque no longer matches the target")
    inspection["texture_deque"] = {
        "target_standard_abi_exact": True,
        "callable_bytes": len(uint_code),
        "canonical_sha256": hashlib.sha256(uint_replay).hexdigest(),
        "replayed_calls": uint_calls,
    }
    receipt = {
        "schema": "th105-iku-real-link-v1",
        "diagnostic_only": True,
        "target_sha256": target_sha,
        "tool_pins": pins,
        "probe_sha256": linked_pe.sha(Path(__file__)),
        "support_sha256": {
            name: linked_pe.sha(ROOT / "scripts" / name)
            for name in (
                "probe-aya-cpu-ltcg.py",
                "probe-common-fighter-ltcg.py",
                "linked_pe.py",
            )
        },
        "parser_versions": linked_pe.parser_versions(),
        "root_source_sha256": linked_pe.sha(ROOT / root_unit["source"]),
        "generated_source_sha256": linked_pe.sha(source),
        "root_object_sha256": linked_pe.sha(root_obj),
        "provider_source_sha256": linked_pe.sha(provider),
        "provider_object_sha256": linked_pe.sha(provider_obj),
        "data_object_sha256": linked_pe.sha(data_obj),
        "image_sha256": linked_pe.sha(image),
        "map_sha256": linked_pe.sha(map_path),
        "libraries": {
            str(path.relative_to(tools)): linked_pe.sha(path) for path in libraries
        },
        "provisional_abs": {
            "target_address": "0x00406330",
            "ownership": "unclassified",
            "source_sha256": linked_pe.sha(abs_source),
            "object_sha256": linked_pe.sha(abs_object),
            "command": abs_command,
            "nonexact": True,
        },
        "compile_commands": commands,
        "compilation_steps": compilation_steps,
        "link_commands": link_commands,
        "dependencies": dependencies,
        "comparisons": comparisons,
        "same_target_symbol_aliases": aliases,
        "data_bindings": bindings,
        "inspection": inspection,
        "scope": "real source/CRT link; no stubs, code ABS symbols or unresolved-link overrides; "
        "same-target bounded-view aliases do not establish original C++ declarations; "
        "five registered dependency addresses and the provisional float adapter remain nonexact; "
        "linked image is not executed or accepted as exact",
    }
    (out / "receipt.json").write_text(json.dumps(receipt, indent=2) + "\n")
    return receipt


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--reuse",
        action="store_true",
        help="reuse objects only after source, command, full unit-input and tool/object hash checks",
    )
    args = parser.parse_args()
    try:
        print(json.dumps(probe(args.reuse), indent=2))
    except (KeyError, OSError, ValueError, RuntimeError) as error:
        print(f"Iku link probe failed: {error}", file=sys.stderr)
        raise SystemExit(2)
