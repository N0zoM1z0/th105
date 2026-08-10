# Build and byte-matching plan

## Current evidence

The PE uses Microsoft linker 8.0. Its Rich header is dominated by tool build
50727, placing the build in the Visual C++ 2005 family. The executable imports
Direct3D 9 and `d3dx9_33`, links a static C/C++ runtime, uses a fixed image base,
and retains an RSDS path for `th105.pdb`.

The decoded Rich header contains 279 `Utc1400_CPP`, 165 `Utc1400_C`, and 42
`Utc1400_LTCG_CPP` records. The LTCG records strongly indicate `/GL` inputs and
an `/LTCG` link for at least part of the C++ program. Consequently, executable-
level comparison is authoritative; object boundaries and object-level codegen
can be altered or erased by the linker.

Still unknown:

- exact VC8 service pack/hotfix;
- compiler options, runtime-library mode, LTCG use, and per-file overrides;
- original translation-unit names and link order;
- resource compiler and library versions beyond evidence in the PE;
- which routines are compiler/runtime/third-party library code.

These unknowns are why the initial repository does not claim a working matching
build.

## Matching stages

1. **Toolchain probe** — compile controlled VC8 functions and compare codegen,
   exception data, RTTI, string pooling, and section layout.
2. **Object partition** — group functions/vtables/statics using RTTI ownership,
   initializer clusters, strings, alignment, and link-order experiments.
3. **ABI skeleton** — recover shared types, calling conventions, class layouts,
   vtables, and global initialization.
4. **Function matching** — use small non-LTCG object probes for fast iteration,
   then confirm LTCG-sensitive functions in a linked executable.
5. **Executable comparison** — use reccmp as the acceptance report and retain
   explicit mappings for functions/globals/floats/strings.

## Agent exact-matching playbook

The reusable, symptom-driven VC8 source-shaping catalog lives at
[`../.agents/skills/th105-re/references/exact-matching-patterns.md`](../.agents/skills/th105-re/references/exact-matching-patterns.md).
It covers the repository's proven patterns for ABI/return-width recovery,
external `REL32`, strict `DIR32` and signed addends, non-contiguous Ghidra body
sets, x87 expression shaping, TU/COMDAT boundaries, BSS section placement,
register reloads, switch tail merging, checked STL paths, hard-function
handoffs, and regression testing after shared-layout changes.

Agents should start from its diagnosis table after the first failed comparison
and add genuinely reusable techniques as they are proven. Function-specific
semantics remain in module notes and `config/functions.csv`; the playbook is
for methods that transfer across address ranges.

## reccmp

After placing the exact original executable in `resources/`:

```bash
reccmp-project detect --search-path resources/
```

After a reconstructed executable exists:

```bash
cd build
reccmp-project detect --what recompiled
reccmp-reccmp --target th105 --html report.html
```

`reccmp-project.yml` refuses a target hash mismatch. The reccmp CSVs are
generated/maintained from the same supported-name inventory as the function
ledger.

## objdiff

`objdiff.json` is intentionally empty until an object boundary is supported by
evidence. Adding a unit requires both an extracted original object/slice and a
reproducible rebuilt object. Do not invent translation-unit boundaries merely
to populate the UI.

## First code-generation results

The pinned VC8 SP1 compiler (`14.00.50727.762`) compiles the initial accessor
source files to these exact target bytes:

```text
0x00439860 get_game_mode:   A1 EC 62 6E 00 C3
0x00439870 get_match_setup: B8 E8 6F 6E 00 C3
0x00439B30 get_game_config: B8 38 6B 6E 00 C3
0x00439C40 get_combined_menu_input: B8 20 75 6E 00 C3
0x00439C80 get_player2_input: B8 70 63 6E 00 C3
0x00439C00 get_player_slot_record: 8B 44 24 04 69 C0 3C 03 00 00 05 C0 64 6E 00 C3
0x00439C10 invalidate_selected_input: 8B 44 24 04 C7 04 85 DC 62 6E 00 00 00 00 00 C6 80 D8 62 6E 00 FE C3
0x00439C30 get_selected_input: 8B 44 24 04 8B 04 85 DC 62 6E 00 C3
0x00439C50 get_combined_menu_input_counters: B8 58 75 6E 00 C3
0x00439C60 get_selected_input_source: 8B 44 24 04 8A 80 D8 62 6E 00 C3
0x00439C90 get_session_setup_option: A1 E4 62 6E 00 C3
0x00439CA0 set_session_setup_option: 8B 44 24 04 A3 E4 62 6E 00 C3
0x00439CB0 get_network_session: A1 FC 62 6E 00 C3
0x00439B40 get_score_data: B8 38 72 6E 00 C3
0x0040A210 set_input_state_table_entry: 0F B6 44 24 08 0F B6 54 24 04 89 04 91 C2 08 00
0x0040D370 is_raw_key_down: 0F B6 44 24 04 0F B6 44 08 20 C1 E8 07 C2 04 00
0x004397B0 get_battle_setup_task: A1 E8 62 6E 00 C3
```

These source files compile to the listed standalone functions. Each has no code
relocation and is recorded as `matching`. They prove the probe path and source
expressions, but the six-byte accessors among them cannot distinguish VC8 RTM
from SP1 or prove the final `/GL`/`/LTCG` configuration.

`is_raw_key_down` uses the explicitly normalized top-bit test
`(raw_keyboard_state[scan_code] & 0x80) != 0`; this preserves the observed
boolean behavior and makes VC8 SP1 `/O2` emit the target's 16-byte `movzx`
sequence exactly.

The first core-battle probes also match exactly:

```text
0x00463270 get_slot_character: 11 / 11 bytes
0x00463280 is_slot_active: 11 / 11 bytes
0x0046A9A0 accumulate_collision_extents: 139 / 139 bytes
0x0046ACB0 reset_collision_extents: 23 / 23 bytes
0x0046ACD0 transform_local_aabb_to_world: 91 / 91 bytes
0x0046BE90 try_frame_flag_pair_outcome: 143 / 143 bytes
```

## Relocation-aware function probes

`scripts/compare-function.py` resolves i386 `REL32` on an external `CALL` or
tail `JMP` whose target has a unique address in `config/known-symbols.csv`. It
applies the link-time displacement using the target function address before
comparing bytes. This permits small battle and collision helpers with direct
calls to already identified functions to be checked without constructing a
fake executable layout.

Absolute `DIR32` data relocations are accepted only when the exact COFF symbol,
target address, literal bytes, and every used addend are allowlisted in
`config/reccmp-relocations.csv`. The comparator revalidates the bytes at each
offset in both the object and original PE, including specified PE zero-filled
virtual tails. It fails closed for unknown symbols, unlisted addends,
non-external `REL32` targets, other opcodes or relocation types, and
relocation-overflow sections. Those cases still require an appropriate
linked-slice or executable comparison. A successful object probe does not
replace final LTCG-sensitive executable-level reccmp acceptance.
