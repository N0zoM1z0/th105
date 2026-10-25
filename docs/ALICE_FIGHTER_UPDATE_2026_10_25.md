# Alice Fighter update: complete source and early comparison

Target: original Japanese TH10.5 v1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Bounded root: **0x004E9F50**, Alice primary vtable slot28 at6C4C04.
The complete manual compiling hypothesis now has its first whole-function
comparison and a bounded callback-epoch correction. It remains identified and
unselected: no source-present or exact credit is added.

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

The following source checkpoint supersedes that target-only planning step.
Original source spelling and full nominal layout remain unknown. No exactness
or standalone/LTCG impossibility has been established.


## Complete manual hypothesis and first comparison

`src/characters/AliceFighterActionState.cpp/.hpp` now provides the entire
pre-dispatch prefix, low/mid/high and five special action paths, plus the real
shared Fighter default. The pointer-only primary view uses the accepted
AnimationSequenceObjectView virtual prefix; it is never constructed or
embedded. Numeric states, typed offsets and declaration-only callees remain.
The existing partial scaffold guided reviewed low/mid hypotheses; it is not
called, renamed into the root, or substituted for the complete body. Saved
decompiler output guided investigation only; the new paths were written
manually against the raw instructions and operand-width literal observations.

The first complete3165-line draft compiled and was compared immediately,
before source-shape trials:43428 bytes, canonical SHA256
`0d7bfb04cd363ef3436e53c2156915431bacd6b5674fcb0066b7a446c803c477`.
The complete target is44080 bytes;41945 unmasked positions differ, including
size, with the first mismatch4E9F58 (frame408 versus410). All16 table lengths
and three remap bounds already agree. This is a nonexact baseline, not a
matching percentage or behavioral equivalence result.

The configured ordinary VC8 O2/GS-off unit is
`exact-first-alice-fighter-update`. The public complete audit replays every
section relocation and compares all emitted bytes, including every tail byte;
it never masks fields, ignores extra emitted bytes or rebases destinations.
The three primary remap byte arrays also compare directly.

```sh
scripts/repo-python scripts/build.py --unit exact-first-alice-fighter-update --compare --json
scripts/repo-python scripts/audit-alice-fighter-update.py
# Independent already-built object:
scripts/repo-python scripts/audit-alice-fighter-update.py --object build/exact-first-alice-fighter-update-20261025/cold.obj
```

All three comparisons intentionally return1 for the nonexact hypothesis.
The mandatory local CI gate is separate and must pass before commit/push.
Fifteen new literal names are isolated aliases selected only by this new unit;
all predecessor relocation rows are unchanged. No accepted unit selects or
emits these new names and no accepted source/header/flags change. The target
floating relocation audit passes. This is not an aggregate cold replay claim.

## Callback epochs exposed by the first whole comparison

A per-action static reachable-call census narrowed the first complete source
to400 plus virtual-call-group differences in214/542/547/548. It ignores branch
predicates, so these counts alone establish neither path equivalence nor
missing behavior. Raw instruction review then found unsupported400/401 shapes
in the retained scaffold:

- Native400 selects sequence4 and emits effect62 before reloading facing for
  the802 request. For example4ED35B calls the effect and4ED38E reloads byte104.
  The draft cached facing before the sequence/effect calls. The complete source
  now reads the live field after each actual callback and keeps the802/801
  requests separate, including their ordinary parameter arrays.
- Native400's ordinary801 request continues at4ED47C after the scaled counter;
  native401 continues at4ED5BF. The draft returned immediately after both
  request suffixes. The complete source now retains the subsequent action and
  sequence/timer gates. The802 branch keeps its separate returning suffix.
- The >=25 timer gate is sequence4, not0:400 writes EBX=4 at4ED484 before the
  shared4EDBE5 comparison;401 writes EBX=4 at4ED5C7 before4ED605. The register
  value is checked from actual predecessor paths, not inferred from a shared
  decompiler label. Native401 also publishes DWORD180=1 at4ED5AB before the
  counter call4ED5B1; the source now preserves that order.

These are target-backed read/write/edge corrections. They do not prove that
an ordinary game effect flips facing or that an existing game path exposes
every possible callback mutation. No fabricated callback or injected helper
result is used as gameplay evidence.

The final3135-line retained hypothesis emits43572 bytes, canonical SHA256
`8dd4473aad05d259763114f8ce440b69cd5b6e24a9cd9656699a911a082bd506`.
Formal and independent fresh-object full audits agree. It remains nonexact+8,
41815 unmasked differences including the508-byte size gap. Frame418 versus410,
121 versus128 RETs,665 versus674 physical direct calls and157 versus163
register-indirect calls remain. All16 table lengths and all685 primary remap
bytes agree. Other than214/542/547/548 indirect-call memberships, the mapped
primary action groups now agree in their per-action direct and indirect call
counts. The five special direct-dispatch cases are outside that mapped-case
census and need their own instruction review. Inventory agreement is not exact
acceptance and does not waive any byte difference.

Remaining questions include the physical callback groups and lifetimes,
case730's partially defined upper facing-argument bits, and the fourth word
transmitted by570/571 count4 requests. The draft leaves the fourth array
member ordinarily uninitialized rather than inventing a zero store; complete
predecessor/write/consumer analysis is still required. The complete source
must remain unselected until its instruction, ABI and default-domain review
supports selection. Do not infer LTCG impossibility or try padding the frame.

Current receipts in the existing build scope: `first-complete-*`,
`callback-epochs-*`, `formal-build.log`, `formal-full-audit.json`,
`cold-build.log`, `cold-full-audit.json`, `native-inventory.json`, and
`literal-impact.json`. First/control source and focused call-ownership recipes
remain in the matching private analysis scope. The public source/unit/audit
are the reproducible current state; generated reports/objects stay out of Git.
