# Alice Fighter update: complete target closure

Target: original Japanese TH10.5 v1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Bounded root: **0x004E9F50**, Alice primary vtable slot28 at6C4C04.
This checkpoint identifies the complete raw target; it adds no source-present
or exact credit. A complete compiling implementation and first whole-function
comparison remain the next step.

## Exact observations

The main callable is `[4E9F50,4F4631)`,42721 bytes, SHA256
`588194779ec2bba363702ac150979a064ce8bf77553bfa727b34951fc8788a89`.
The complete code/alignment/table payload ends at4F4B80,44080 bytes, SHA256
`2bd6bb53be12d74e98f1fee7dfcedf2b1adcf71597fd89a9ce8185f4d0e1f823`.
The next independent candidate is Alice CPU policy4F4B80.

A fresh instruction-start CFG traversal closes11169 of11170 decoded
instructions. The sole unreachable instruction is the three-byte alignment
`8D4900` at4F28ED; no edge escapes the callable or lands inside an instruction.
This is conservative static reachability, not proof that each branch can
execute for a feasible game state. There are128 RET0 sites,674 direct calls to
27 entries, and163 register-indirect calls. Entry aligns ESP to8 and allocates
0x410 bytes, saves EBX/EBP/ESI/EDI and uses ESI as receiver. Original C++ owner
layout, packet lifetimes and TU partition remain unknown.

All16 instruction-owned destination tables are closed, not just the three
primary action tables. They contain165 DWORDs, each pointing at an instruction
start in this callable. The three primary byte remaps contain685 bytes.

| Action region | Destination table / entries | Remap / bytes |
| --- | --- | --- |
| 0..226 |4F4634 /31 |4F46B0 /227 |
| 301..508 |4F4794 /34 |4F481C /208 |
| 521..770 |4F4914 /40 |4F49B4 /250 |

The pre-existing giant mapper independently retains103 unique primary
physical destinations, including one shared default4F44A5. Special actions
300/520/795/797/798 are direct branches outside those primary remaps.
The other13 nested tables have lengths5,5,5,5,5,5,5,5,4,4,4,4,4.
Every byte in the1359-byte metadata tail is accounted for:660 destination
bytes,685 remap bytes and14 pinned alignment bytes. The alignment ranges are
4F4631+3,4F4793+1,4F4AAE+2 and4F4B78+8.

The public raw audit checks the full target hashes, candidate size, vtable
cell, complete instruction decoding, all edges, RET cleanup, all table
operands/destinations, remap indices, metadata coverage and alignment pins:

```sh
scripts/repo-python scripts/audit-alice-fighter-update-target.py
scripts/repo-python scripts/map-giant-action-switches.py alice-vslot28 --json
```

The audit reports evidence only. No masked comparison, local matching window,
source selection or original nominal identity follows from these checks.

## Dependencies and retained source

The27 direct entries are the existing Fighter landing/motion, animation,
effect/event, object-spawn, counter, RNG and orientation families. Current
ledgers mark23 canonical exact. The two quantized lookups406360/4063D0 and
shared Fighter update4740C0 remain source-present/nonexact;68A1A0 is compiler
float-to-integer support. This round did not cold replay accepted callees.
The raw report retains each call count and the current declaration/status;
callee evidence must still be checked when choosing the complete source view.

`src/characters/AliceActionStateScaffold.cpp` is an existing partial semantic
staging helper returning whether it handled a selected action. It is not this
root and must not be called or renamed into a purported complete native body.
`src/characters/Vslot28ActionStateRoots.hpp` is declaration-only. Neither
justifies selecting Alice in implemented.csv. The retained scaffold and the
Youmu Fighter implementation may guide hypotheses; all Alice differences,
call epochs, argument widths and continuations require its actual instructions.

The source-missing report initially suggested Sakuya4CADB0 because its main
span is41511 bytes. Its ownership ledger already records ten remote chunks
and74941 owned code bytes. Alice's complete contiguous callable and payload
are therefore the chosen next bounded representative; no Sakuya ownership is
changed or lost by this selection.

## Read-only analysis receipt and remaining work

IDA preflight still rejects the GUI's wrong executable SHA10350095... . Raw
PE work is valid independently. One serial Ghidra process used384MiB heap,
CPU0/nice10, read-only/noanalysis and the existing primary project. Before
using its output, the script checked the exact executable hash, image base,
x86 Windows analysis target, entry68B9D2 and every imported section's mapped
bytes against resources/th105.exe. Temporary root and dependency views were
read back, then rolled back; root removal was read back and all nine primary
project file hashes were unchanged.

The saved5213-line decompiler output is a hypothesis with a stack-spacebase
warning and removed-block warnings, including unsigned conversion-correction
branches. It does not replace the raw CFG or recover original source locals.
Do not paste it mechanically or launch another database process just to reread
it. No analysis database state is the durable record.

Receipts are under `build/exact-first-alice-fighter-update-20261025/`:
`initial-map.json`, `raw-facts.json`, `target.asm`, `literals.json`,
`public-target-audit.json`, `ghidra-receipt.json`, `ghidra.log`, `decompile.txt`,
and `primary-db-before.json`/`primary-db-after.json`. Private recipes are in the
corresponding `.analysis/` directory. All are local and excluded from Git.

Continue by recovering the real pre-dispatch gates, complete low/mid/high and
special action bodies, default continuation, virtual call contracts and84
object-request sites. Preserve ordinary consumed arrays/locals and the native
widths. Compile the first complete body and compare every emitted byte,
including the switch metadata, before source-shape controls. Keep this root
identified/unselected until that complete instruction/source review supports
selection. Original source spelling and full nominal layout need not be solved
first. No exactness or standalone/LTCG impossibility has been established.
