# Iku opening actions against Youmu target bytes, 2026-10-02

## Scope and method

This is a target-to-target comparison within the original Japanese TH10.5 v1.06a PE, SHA-256 `56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`. Iku `+0x28 @ 0x00620920` is the reviewed 59,038-byte Fighter root; Youmu `+0x28 @ 0x00530200` is a separate 37,692-byte source-present, nonexact root. The comparison does not use the retained Youmu C++ as truth.

The existing target-backed `youmu-vslot28` switch mapper and the hash-attested Iku selector map identify physical action entries 0–10. Private `.analysis/iku-vslot28-20261002/compare-youmu-opening.py` verifies the PE hash, decodes every byte between successive physical entries, and records instruction forms plus ordered absolute direct-call targets in `build/iku-youmu-opening-20261002.json`. For its *diagnostic* form count, an in-case branch destination is expressed relative to the case entry and an out-of-case edge is replaced by a marker. Those markers do **not** prove matching external destinations, case semantics or source provenance; the addresses below come from a separate raw-edge inspection.

| Action | Youmu bytes / instructions | Iku bytes / instructions | Equal normalized forms | Same ordered direct calls |
| ---: | ---: | ---: | ---: | --- |
| 0 | 211 / 66 | 213 / 65 | 58 | yes |
| 1 | 208 / 63 | 209 / 62 | 53 | yes |
| 2 | 28 / 7 | 27 / 6 | 5 | yes |
| 3 | 207 / 63 | 208 / 62 | 52 | yes |
| 4 | 36 / 14 | 34 / 13 | 12 | yes |
| 5 | 36 / 14 | 34 / 13 | 12 | yes |
| 6 | 188 / 44 | 188 / 43 | 28 | yes |
| 7 | 153 / 32 | 164 / 33 | 18 | yes |
| 8 | 149 / 32 | 164 / 33 | 18 | yes |
| 9 | 110 / 40 | 99 / 31 | 28 | no; physical Iku case 9 exits to a remote common return |
| 10 | 69 / 32 | 67 / 31 | 28 | yes |

## Observed differences that govern source reuse

Youmu loads x87 zero at `530246` and may store it to receiver `+0x4D0` with nonpopping `FST` at `530253` on the `+0x7EA/+0x7EC` countdown path. The zero remains live through its opening dispatch: actions 0–5 each begin with a `FSTP ST(0)` after preparing the receiver and before calling the exact-backed landing helper `473DD0`. Iku has no corresponding live zero at its `620B1B` dispatch, and its actions 0–5 omit those drops. A direct transplant of the retained Youmu case source would therefore import the wrong floating lifetime. The Iku root uses `EBP` as an integer zero carrier, while Youmu's corresponding comparisons use `EBX`; this is observed register coloring, not an instruction to force either register in source.

The target instruction skeleton and ordered helper calls support shared *behavioral* hypotheses for opening actions, but the character constants differ. Iku actions 4/5 load `2.5f/-3.0f` into receiver float `+0xF4`; Youmu loads `4.0f/-4.0f`. In action 6, Iku loads `12.0f` into vertical velocity `+0xF8` and `0.35f` into acceleration `+0x100`; Youmu uses `16.0f` and `0.8f`. Iku actions 7/8 set horizontal `+0xF4` to `+3.5f/-3.5f`, vertical `+0xF8` to `11.0f`, then jump into the action-6 acceleration/flag tail at `620E92`. Youmu's action 7/8 horizontal literals are `+6.5f/-6.5f`, and their branches join their own action-6 tail at `530678`. All literal values were decoded from the SHA-checked PE at the actual `FLD m32` addresses.

For Iku actions 6–8, the `+0x13E` sequence-zero path calls `473DD0`, optionally calls the exact-backed zero-velocity helper `45AF40` when byte `+0x47E` is zero, and on positive sequence subtracts acceleration `+0x100` from vertical velocity `+0xF8`. The exact-backed crossing predicate `5F9310` can enter the common action-9 transition at `621037`. After frame advance `4351C0`, the all-zero frame/timer checks at `+0x144/+0x142/+0x140` together with sequence 1 select the character-specific velocity/acceleration stores and clear `+0x47E`. Action 9 sets zero acceleration to `0.6f` before the same subtraction/predicate path; its crossing tail calls virtual slot `+0x08` with action 10, then exact-backed `stage_surface_height_at_x @ 435D60`, storing the returned x87 float at `+0xF0`, and zeroes velocity. Action 10 calls the landing, zero-velocity and frame helpers; after a successful frame result it chooses virtual action 0 or 2 using dword `+0x6B8`. These are target instruction/edge facts and existing exact-backed helper contracts, not decompiler source.

**Inference and unknowns:** actions 0–10 contain reusable Fighter state-machine behavior with Iku-specific scalar parameters and x87 lifetime. Exact original C++ spelling, branch treatment of unordered floats, all cross-case return ownership, original TU/LTCG context and the remaining 99 nondefault Iku actions are not recovered. No Iku source-present or exact claim is made. The declaration-only `src/characters/Vslot28ActionStateRoots.hpp`, `config/implemented.csv`, `config/matches.csv` and accepted units remain unchanged.
