# Native markup color: source and specialization boundary

`TextFont_set_markup_color @ 0x00411790` has a complete352-byte,
111-instruction CFG ending in two RET16 paths. Genuine C++ in the actual font
markup TU produces332 bytes/105 instructions, canonical
`471012e5b779862c44eee35f952d99a7ac355e1b3d37e22f4ba0bfb7b68e5426`.
It remains **nonexact at+2**; no exact credit is added.

Only original Japanese TH10.5 v1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. Required target/status/tracking preflights pass. IDA and typed-re reject
the wrong open executable, so analysis uses the pinned raw PE. Full target hash:
`268b8440de095ca5a853314b6f4d2ba8a0b36469d9f7418f0e3cad81646e7e84`.
All352 bytes are reachable; there is no omitted tail or EH region in this root.

## Observed behavior and ownership

The reviewed main-instruction census finds one direct incoming edge, at4125DB
in markup411FA0. Font and three channel words are stack arguments; each channel
consumes only its low byte. Both paths pop16. This supports the ordinary typed
stdcall definition without an invented register convention. Original nominal
spelling and indirect/remote caller completeness remain unknown.

When base158 is nonzero, the function allocates `new unsigned[height]`, inserts
the pointer at the front of the native list15C, then fills the new front table.
Each RGB channel interpolates from config bytes10C/10E/110 to the supplied
endpoint using signed multiplication/division. It publishes the new pointer to
active154 only after filling. Existing temporary tables remain behind it.
The starting color comes from the config, even when a different active table
already exists. Flat mode writes only packed fallback168, retaining the list,
base and active fields.

Height0 allocates/inserts/publishes an empty table without entering the loop.
Height1 actually divides by zero after insertion. Source retains this behavior;
no defensive height gate is inferred. Extreme allocation sizes, failure and
integer-overflow behavior are outside the bounded execution evidence.

## Complete comparison and compiler context

The ordinary source has an8-byte frame versus target12, saves some registers
only inside the gradient branch, and reloads byte arguments inside the loop.
The target instead widens RGB once into full-word homes after the loop guard.
Meaningful promoted arithmetic locals were tested; VC8 removes them and emits
the same complete332 bytes. They are not retained as shaping code.

Two callee differences independently prevent a truthful standalone match.
Target Buynode4129E0 ignores incoming ECX, while the ordinary caller still sets
the native list receiver. Its complete51-byte body itself reproduces exactly
from the actual VC8 list source and is executed in the bounded test below;
its existing compiler exclusion earns no new credit.

Target Incsize40C6D0 uses ECX=list and has a constant1 increment with plain RET.
The actual native generic `_Incsize(count)` call passes a stack1 and pops4.
Replacing its declaration with a no-argument facade would misrepresent the
library ABI. Its154-byte target includes its own GS/EH overflow-throw path;
this checkpoint neither qualifies nor excludes that helper. Genuine remaining
font definitions and linked/LTCG context are the next route to its observed
specialization. LTCG is a supported explanation to test, not a proved exact
solution or permission to waive complete bytes.

## Bounded execution and affected replay

All **576/576** cases agree between complete actual target/source root
instructions and the byte-identical native Buynode51. Inputs cover valid lists
of0/1/3 nodes, heights0/1/2/3/4/17/64/127, flat/gradient mode, six RGB endpoint
pairs and two upper-word argument patterns. The independent specification
checks signed interpolation and untouched font bytes. Observations compare
allocation, list, table and active publication write order, full font/list/table
snapshots, and normal ESP/callee-saved registers. All36 height1 gradient cases
stop at the actual divide exception after insertion, before active publication.

Array/node allocation and Incsize remain explicit observers. Their source and
target stack conventions are handled separately. This is not actual CRT
allocation, helper overflow/EH, malformed-list, arbitrary-alias or real GDI
coverage. Back-insertion and previous-active-color controls fail192 and216
cases respectively, confirming sensitivity to the recovered ownership policy.

The eight-function font unit cold-builds after the source addition. All previous
seven complete candidate bodies remain unchanged, including accepted hex45,
markup1652 and the five runtime roots. Thus no parent semantic replay is needed
for unchanged instructions; the earlier8640-case parent evidence keeps its
original observer scope. The accepted hex function remains45/45 exact. No
shared header/profile/partition or existing relocation/data mapping changes;
only the affected accepted font unit replays, with no aggregate exact claim.

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-text-font-render --compare --json
python3 scripts/function-origins.py --check
python3 scripts/validate-tracking.py --require-target
taskset -c 0 nice -n 10 python3 scripts/ci.py
git diff --check
```

The focused command intentionally exits comparison_failed: seven candidates
remain nonexact and hex45 is exact. Reports and selected source/COFF evidence
are retained in `build/font-color-20261021/`; private recipes are in
`.analysis/font-color-20261021/`. Only source-present/authored classification is
added. Next bounded work is reset4118F0, then setter/blend closure before the
larger parent/TU/link/EH comparison. Reimu496540 remains nonexact49655F/+31.
