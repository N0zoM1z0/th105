# Marisa action-state 0x004A3710

Complete, unselected, nonexact C++ candidate covering 130 action labels and the
shared prelude/default path. Neither implemented.csv nor matches.csv gains
credit. A complete first candidate is not proof of recovered semantics.

## Native evidence

The original Japanese 1.06a executable was hash-attested. Factory's native IDA
session independently matched its hash, image base, entry and sampled mapped
bytes. The whole-root decompiler failed; read-only Ghidra action slices were
used only as navigation, with incoming registers, packet writes and floating
operands resolved against raw instructions. Slice functions are diagnostic
metadata, not original callable boundaries or ABIs. Transactions were rolled
back and the nine primary database file hashes remained unchanged.

Callable 4A3710..4B3B97 is 66695 bytes, SHA-256
98fd68e00763955f64d7489b2a5cb04b20f209031d739a7e9117273080a45aa5.
All 16999 decoded instructions are reachable; no unresolved indirect exits or
holes remain. Six indirect switches resolve. There are 138 RETs and 978 direct
call sites to 29 targets. Metadata ends at 4B4070, the next independent root.
The complete 67936-byte payload has SHA-256
58dd1936fc5db5341cbf3e08d9f19beaa7d106ffbf84d82b673644da542c6447.
Sparse regions 0..226, 301..531 and 541..770 have 32/45/48 destinations;
three four-way difficulty tables belong to 720/731/733. Direct arms include
300, 540, 795, 797 and 798.

## Source and remaining uncertainty

The pointer-only receiver inherits the established virtual-slot view. Helpers
are declaration-only caller interfaces. Direction arithmetic is signed byte;
effect/spawn carriers preserve unsigned byte values. Surface and crossed-floor
calls retain ST0/AL consumption and distinct ordering around virtual calls.
The prelude preserves its unusual threshold/clamp pairs: 4A38CD/38FF compare
against 3 but publish 12; 720 sequence6 compares against 12 and clamps to 11.
These are native observations, not corrections to presumed intended behavior.

307/308's second count-three requests initialize only the first two float
slots; no invented third value is supplied. 505/506 have four native float
stores despite a count-three request. These extents and downstream readers
remain under review. All 98 payload homes resolve in both CFGs, without unknown
spawn payload sites; candidate homes are uniformly eight bytes higher.

The initial candidate merged the equivalent 565..568 request branches. Native
4AD134/4AD3D7/4AD6F7/4AD9CC captures direction and Y before branching, then
computes X inside each branch. Restoring those scalar lifetimes preserves both
static spawn sites and their FP operations. Per-action reachable call
diagnostics now have no direct-call count differences. Virtual-site counts
still differ for 410/414, 562/563 and 733. The initial remaining FP-site
difference for 214 is resolved by the rate-branch refinement below. These checks are
omission diagnostics, not semantic acceptance or excuses for byte differences.
Callback-sensitive lifetimes, floating precision, unknown packet slots and
TU/LTCG ownership still require review. No compiler-control assembly, fake ABI,
forced registers, copied target bytes or padding is used.

## Reproduction and current comparison

    taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py --unit exact-first-marisa-action-state --compare --json
    scripts/repo-python scripts/audit-marisa-action-state.py
    scripts/repo-python scripts/compare-giant-action-switches.py marisa-vslot28 build/match-units/ExactFirst_MarisaActionState.obj --json

The first complete public candidate is 67988 bytes versus native67936, with
frame4C8 versus4C0. First mismatch is +14 / 4A371E. Canonical full-payload
comparison reports 63157 unmasked differing bytes including length difference;
this positional count is not a semantic-completion percentage. Candidate SHA:
87673809b70b5b9dce1b0e1e9b02a895f423f60267190b6fe4ea993ff12e43ee.
Candidate sparse tables have the same 32/45/48 cardinalities and no native group
splits. It has 141 epilogues and 216 receiver-qualified indirect call sites,
versus native138/211. All 63 crossed-floor and 10 on-surface sites test AL.

Receipts are build/frontier-4a3710-20261028/formal-build.json and
formal-full.json. Eleven absent native-backed literal bindings were added;
existing bindings and accepted consumers were not changed. Only this new unit
was compiled. Next work is source-level lifetime/branch ownership refinement
against this complete baseline, not whole-corpus rebuilding.

## Request-lifetime refinement

The target-backed 565..568 capture refinement is retained despite increasing
the complete candidate from 67988 to 68196 bytes: matching source ownership and
restoring the four missing static call sites is stronger evidence than mere
aggregate size proximity. Native remains 67936; first mismatch remains +14
and frame remains 4C8 versus 4C0. Full unmasked differences are 64190, SHA-256
5d74b71f4d842f9cb9d7a5472c11e415ea5471c47176d05fe44714e7ae985806.
All 98 payload homes remain resolved, without unknown payload sites; the
32/45/48 groups remain unsplit. Receipts: trial826-build.json,
trial826-full.json, trial826-calls.json, trial826-fp.json and
trial826-payload-homes.json in the same build directory. Existing accepted
units and exact ledgers remain unchanged.

## Action708 velocity precision

Raw 4B256B/4B256F explicitly narrows and reloads vertical velocity as float
before publishing it and adding Y. The sum is then captured as QWORD at
4B257F across surface435D60. The original candidate accidentally used the
unrounded double velocity for that sum. The corrected source now emits both
the float narrowing and QWORD capture; ordered surface>=prediction and the
post-call live negative-velocity check are unchanged.

Current complete candidate: 68204 bytes, frame4C8, first+14, 64185 unmasked
differing bytes; SHA-256
05e8856885e6a33b397c933b39e731874e08d044d3257c32d49163cc975a0882.
Receipts: trial708-build.json and trial708-full.json. No exact credit.

Two source-expression ownership controls (inline dust X expression and inline
squared-distance sum) produced the same complete payload hash. Expanding all
ten dust helper bodies at their callers did not fix frame ownership (still
4C8) and lacked independent evidence for retention; all three controls were
reverted. Their private receipts remain trialdust-*, trialsquare-* and
trialdustowner-*; no compiler padding or register forcing was introduced.

## Flight214 rate-branch refinement

Native 4A55C0..4A560C retains a separate add/subtract for each 1.5/0.5 rate.
Replacing the conditional rate operand with its native arithmetic branches
reproduces this region's instruction sequence (at a shifted address). Only
16 complete-payload bytes change; complete size remains 68204 and frame4C8.
Full comparison has 64184 unmasked differences, first+14, SHA-256
502819ce6e9f3ebccbdfeb5879f56836064e00f835d6950f0171e21cf6b0b8cb.

The private diagnostic now also covers direct300/540/795/797/798, qualified
from the actual dispatch comparisons, equality branches and fallthroughs.
Across all 130 nondefault action labels, direct-call and arithmetic-site counts
agree. Virtual-site differences remain at 410/414 (one fewer each), 562/563
and 733 (one extra each). Counts do not establish semantic equality, operand
precision, call order, stack ownership or exactness. Receipts: trial214-*.json,
including trial214-all-action-calls.json and trial214-all-action-fp-ops.json.
