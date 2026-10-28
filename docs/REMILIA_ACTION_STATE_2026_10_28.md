# Remilia action-state candidate, JP 1.06a

## Status

Address 0x00545090 now has a complete 107-action C++ candidate and a focused
VC8 replay unit. It is **unselected and nonexact**. No implemented.csv,
matches.csv, function status, or accepted byte total is changed.

The first complete candidate emitted 63,444 bytes. Reviewed packet ownership,
difficulty fallthrough, zero-offset coordinates, and packet extents produce
63,004 bytes versus the target's full 63,316 bytes. First mismatch is +8:
the emitted stack allocation is 0x4F8, target 0x4F0. Size proximity is not
an exactness percentage.

## Target and boundary evidence

The hash-attested original Japanese 1.06a executable is
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.
Factory-native IDA metadata, entry, function inventory, and five mapped-byte
probes were independently checked at 03:27–03:28 UTC on October 28.
Factory discovery reattested its metadata at 04:04 UTC. The local legacy
check-ida-mcp.py cannot load mcp==1.26.0; this is not a successful legacy
preflight and is not evidence that Factory IDA is disconnected. No dependency
installation was used. Decompiler output is only a semantic hypothesis.

Raw target CFG closure covers 0x545090..0x55429A:
- 61,962-byte callable span; 15,973 decoded instructions.
- 15,972 reachable instructions / 61,959 reachable instruction bytes.
- Only three unreachable alignment bytes at 0x551DAD..0x551DB0.
- 146 RET instructions and 967 direct call sites to 31 targets.
- No unresolved indirect exit after closing all sixteen tables.
- Three sparse action tables: low 32, mid 42, high 30 destinations.
- Four five-entry skill tables and nine four-entry difficulty tables.
- Direct action 300 and shared 560/561 are outside those sparse tables.
- Complete payload ends at 0x5547E4, size 63,316.

Callable SHA-256:
cffbd3c34e8a10be85f5236a16afad7e035227df15bf420b9eb30599fce0092b

Full payload SHA-256:
1c631b6ff3b591e2f96c1ad5de0957213a71855231e79d3768726acd1752c5a3

## Recovered source and ABI

The pointer-only view is not a complete recovered Fighter layout. It keeps
VC8 field widths and virtual sequence slots. initialize_fighter_phase_631e0
uses the previously established fastcall ABI; oriented motion uses the
established two-float thiscall at 0x435160.

All 63 native crossed-surface consumers test AL, including two that first
load a vtable pointer. The generic immediate-consumer diagnostic reports
false for those two; raw instructions establish the actual width. The
candidate has 62 physical crossed calls because native low owners 209 and
212/221 merge. This is not a reason to reinterpret the result as full EAX.

The 101 native and 101 candidate spawn-payload homes resolve without unknown
payload pointers. This proves pointer provenance, not initialization or
dynamic equivalence. Two unusual native extents are intentionally exposed:
- Action 408 passes count three with only one written scalar. Its next
  native payload home is four bytes later.
- Four action 530/531 packets pass count four, while only three scalar cells
  belong to each recovered packet extent and are initialized.

The extra values are **not recovered**. The candidate does not invent zero
initializers or reserve inert cells to repair this mismatch. These paths
need callee/use and original allocation ownership review before source
selection; this is not a portable runtime-safety claim.

Other independently reviewed details include:
- Flight 214 is a burst with entry/frame-specific angle processing, not
  another character's continuous flight loop.
- 525/526 timeout compares signed time with signed-char skill level.
- 565/566 and 720 retain the native unsigned direction in the second
  mirrored X coordinate; do not silently normalize it to signed facing.
- 730/731 difficulty one falls through to difficulty zero's second emission.
- Floating-point arithmetic operation counts agree for every mapped action
  after correcting negative flash offsets and avoiding X+0 in charge effects.

Physical call-site diagnostics differ for action 710 (native/candidate
spawn sites 8/5 and virtual sites 2/3). Shared tails are not dynamic call
counts; trace the exact call arguments and incoming edges before changing
behavior. Native/candidate stack frames are 1264/1272 bytes, return sites
146/144, virtual call sites 179/180. Stack coloring and physical ownership
remain open, not solved by the count agreement.

## Focused replay

Only the new unit was compiled; no shared accepted source was changed and
no cold full-corpus run was performed.

    taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py --unit exact-first-remilia-action-state --compare --json
    scripts/repo-python scripts/audit-remilia-action-state.py
    scripts/repo-python scripts/ci.py
    git diff --check

Both comparator commands correctly report mismatch. The full-payload audit
rechecks target hash, all table destinations, complete reachability, exact
unmasked bytes and payload length.

Final candidate SHA-256:
de07c135c223e31405fd1e3af39d86fea4602e8005ed87bd0052a1007df73be1

Full positional differences including absent trailing bytes: 60,051.
That count is diagnostic, not a semantic similarity or completion metric.

Receipts: build/frontier-545090-20261028/formal.json and formal-audit.json.
Private raw and source diagnostics are in the same frontier build directory;
draft recovery is under .analysis/frontier-545090-20261028/. The checked-in
source is authoritative. Existing exact receipts remain incremental.
