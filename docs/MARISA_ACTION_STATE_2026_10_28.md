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

Per-action reachable call diagnostics have no direct-call omissions except
565..568: the compiler merges two equivalent request branches into one static
spawn site. Virtual-site counts differ for 410/414, 562/563 and 733. FP-site
counts differ for 214 and the same merged 565..568 branches. These checks are
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
