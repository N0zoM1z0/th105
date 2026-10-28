# Suika action-state 0x00598990

Complete-label, unselected, nonexact C++ candidate: 115 top-level action labels,
shared prelude and default path. Compilation and coverage do not establish
semantic correctness. No implemented.csv, matches.csv or exact-byte credit.

## Native evidence

The Japanese 1.06a target is hash-attested. Factory IDA metadata, entry,
inventory and mapped-byte samples independently matched the target. The direct
local MCP preflight lacked its Python dependency, and whole-root native
decompilation failed; neither was repeatedly retried or repaired by installing
software. Independently attested Ghidra action slices were navigation aids only.
Their temporary functions and caller-interface views are not original ABIs.
Transactions rolled back, with all nine primary database hashes unchanged.
Raw instructions decide selector arguments, floating widths and packet stores.

Callable 598990..5ABFDB exclusive is 79435 bytes, SHA-256
a1006a208fb62813cec2081c250f5825e88011ce834cff9e49e5d15d0164feb9.
There are 20324 decoded instructions and 20321 reachable instructions.
The nine unreachable bytes are three LEA ECX,[ECX] alignment instructions at
5A09FD, 5A5A5D and 5A97CD, not missing actions. All twenty indirect switches
resolve. Decoded direct calls: 1081 sites, 37 targets. A raw E8 byte scan counts
1083 sites, including non-instruction matches; it is not the decoded census.
Full metadata ends at 5AC680: 81136 bytes, SHA-256
11eb3a1f3f5eef32dee111878375b1b0270c7a38b1be49161220adb548a49e45.
Native aligned frame is 0x578. Sparse regions have 33/50/31 destinations,
with direct actions 300 and 560 outside those tables.

## Source observations and unresolved work

The pointer-only receiver inherits the established animation virtual-slot view.
Declaration-only helpers confer no callee implementation credit.
Slot0C selects a sequence; slot08 changes an action; slot20 advances a frame.
Direction arithmetic uses signed byte values, while spawn carriers preserve
unsigned low bytes, including layer255. Shared helper435160 receives root+4.

The source retains callback-sensitive surface/selector ordering, narrowed
velocity followed by QWORD predicted-Y captures for547/562/708, unsigned
button-edge predicates, and duplicate native gravity passes in740. Spell605
runs the secondary cycle before its sequence window, unlike the usual cast
helper. Grab608 preserves peer action changes, live receiver reloads and
caller-owned packet reuse through repeated requests. Negative spawn offsets
use integer subtraction as the native FISUB operands require.
540 and541 have distinct random-result narrowing/integer arithmetic.
505..508 initialize fragment type once before their loops;402 initializes it
per iteration. No defensive behavior, invented packet initialization or
cleanup of seemingly redundant native behavior is intended.

Remaining uncertainties include:
- Candidate low table merges208/220, though native physical entries differ.
- Giant605/730 surface-check bodies still merge at compilation despite explicit
  individual sequence cases. Each has five fewer static surface/zero-motion
  call sites and five fewer addition sites; this is not exact ownership.
- 501 has one fewer virtual site;608 has four more. Grab608 also has five fewer
  additions and two more subtractions in the current per-action diagnostic.
  These differences need source/lifetime review, not padding or forced code.
- 740 has no established initialized turn/period fallback outside difficulty
  0..3. The draft does not invent a default. This remains an explicit semantic
  limitation, not a supported new behavior or accepted reconstruction.
- Packet extents, callback lifetimes, floating evaluation and TU/LTCG ownership
  remain under review. No complete payload-home equivalence is claimed.

Per-action call/arithmetic counts are omission diagnostics, not proof of
semantics. Integer x87 arithmetic and reversed/pop forms must be considered
when interpreting operation counts. No compiler-control assembly, copied
target bytes, fake ABI, inert locals or padding is used.

## Reproduction

    taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py --unit exact-first-suika-action-state --compare --json
    scripts/repo-python scripts/audit-suika-action-state.py
    scripts/repo-python scripts/compare-giant-action-switches.py suika-vslot28 build/match-units/ExactFirst_SuikaActionState.obj --json

Current complete candidate: 78976 bytes versus native81136, frame0x578 matches
the native frame. First mismatch is +17 / 5989A1. Full unmasked comparison:
77122 differing bytes including length difference. This positional comparison
is not a semantic-completion percentage. Candidate SHA-256:
b2468219f5e5b824f0355c83bf4d4639e30e436b549e081dd0a890507c1944b6.
Sparse candidate cardinalities32/50/31; no target group is split. Twenty absent
native-backed literal bindings were added without changing existing bindings
or shared headers. Only this unit was compiled; accepted receipts elsewhere
remain unchanged.

Receipts: build/frontier-598990-20261028/formal-build.json, formal-full.json,
trial-giant-owners-map.json and trial-giant-owners-action-review.json.
Private raw boundaries, all115 diagnostic slices and IDA/Ghidra attestation
receipts remain in that bounded build directory. Continue source-level
ownership/lifetime refinement against this complete baseline.
