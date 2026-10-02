# Iku vslot +0x28 boundary and action map, 2026-10-02

## Exact target observations

`Iku_dispatch_action_state_vslot28 @ 0x00620920` is an RTTI-owned Iku Fighter primary-vtable target. The only analyzed executable is the original Japanese TH10.5 v1.06a, SHA-256 `56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`. Its candidate callable `[620920,62EFBE)` has **59,038 bytes** and SHA-256 `abc831c6ccd95986bed811694f532ad8c8b92cb49702a7f6ce4de100b8a73dea`.

A recursive raw-PE decode from `620920`, following all direct edges and three validated indirect tables, reaches **15,132 instructions and every one of the 59,038 bytes**. It finds 131 return sites, zero unreached ranges and zero direct jumps outside the callable. The final `RET` is at `62EFBD`; a two-byte `8B FF` alignment precedes table data at `62EFC0`. This reconciles the recorded main-span boundary as a complete executable control-flow unit. It does not establish original translation-unit or linker ownership.

| Dispatch jump | Target table | Distinct table entries | Compressed action range | Lookup byte array |
| --- | --- | ---: | --- | --- |
| `620B1B` | `62EFC0` | 33 | 0–226 | `62F044`, 227 bytes |
| `62374C` | `62F128` | 42 | 301–547 | `62F1D0`, 247 bytes |
| `6290B3` | `62F2C8` | 35 | 561–798 | `62F354`, 238 bytes |

Each table's final entry points to the common default at `62EFA5`. Within the listed ranges, the byte maps send 194, 206 and 204 action numbers to that default, respectively. The other map values resolve **108 distinct nondefault action IDs**; action 209 and 221 share one low-region entry. Two special comparisons dispatch action 300 directly to `62360E` and action 560 directly to `628EAD`, bringing the directly observed nondefault action IDs to **110**. The first region includes actions 0–10 and selected actions 197–226; the middle region includes selected actions in the 301–547 range; the high region includes selected actions in the 561–798 range. These are byte-derived selector mappings, not reconstructed case semantics. The complete action-to-entry list is in `build/iku-vslot28-action-map-20261002.json`.

The raw boundary checker `.analysis/iku-vslot28-20261002/audit-boundary.py` and compressed-selector checker `.analysis/iku-vslot28-20261002/map-actions.py` are hash-bound and reproduce the private JSON reports under `build/`. The existing origin rule remains the positive authored-identity evidence; the raw decode alone does not classify authored versus compiler bytes.

The same complete decode contains **4,676 x87 instructions**. It contains no `fsincos`, `frndint`, `fsin`, `fcos`, `fptan`, `fpatan`, `fyl2x`, `fscale`, `fprem`, `fprem1`, or `f2xm1` instruction. This is a bounded instruction inventory, not a claim that ordinary C++ will reproduce every x87 load, store, status test, or rounding boundary. The current target evidence does not show the special-instruction case illustrated by TH08's retained inline `fsincos` and `frndint` islands (`src/ZunMath.hpp` and `src/AnmManager.cpp` in that separate repository). TH08 uses VC7, whereas this target is VC8; its implementation cannot establish a TH105 source requirement. TH105's own `AGENTS.md` forbids assembly for forced comparisons.

## Attested Ghidra working state

A single direct Ghidra headless import, with no factory adapter, independently verified the imported executable SHA-256, PE entry `0068B9D2`, x86 Windows program identity, full mapped `.text` SHA-256 `f5cb09ff0a54362356d8c4cce853cbcb14552499cce12cf7390d0868db9ebe97`, and the bounded callable SHA-256 above. It disassembled the three sets of table destinations and saved one 59,038-byte working function. A second, sequential headless process reopened the project and read back the same target identity, mapped `.text`, entry, function extent, `__thiscall` and void return metadata. A later sequential process applied five existing exact-backed helper ABI declarations at `473DD0`, `45AF40`, `4351C0`, `4359F0` and `465190`; another fresh process read back all five names, extents, calling conventions, returns, explicit parameters and stack purges. The project, original 376,196-byte decompiler hypothesis and typed 280,472-byte hypothesis stay private under `.analysis/iku-vslot28-20261002/`. Reproduction logs are under `build/iku-ghidra-*-20261002.log`.

The Ghidra root signature is a working hypothesis consistent with the vtable declaration; its decompiler output is not source or exact evidence. The typed output still warns that it removed some blocks, despite the raw traversal reaching every body byte. No class field types, case semantics, original TU partition or numerical exception behavior have been accepted from it. The attached IDA GUI still has the wrong target hash and was not used.

## State and next work

`config/functions.csv` advances this reviewed target candidate to **identified**; `config/implemented.csv` remains unchanged: this bounded work proves the candidate's target bytes, action dispatch and extent, but does not reconstruct the 110 action bodies into complete supported source. There is no configured VC8 object or canonical comparison for this root, and **no exact byte credit** is added. `config/claims.csv` remains header-only.

Recover coherent action families against raw instructions and exact-backed Fighter helpers, using the attested Ghidra output only to generate hypotheses. Before selecting source, resolve cross-case tails, helper ABI, field widths, x87 lifetimes and the original compiler/TU context. A source-present or exact ledger promotion requires the normal complete-source and canonical comparator evidence.
