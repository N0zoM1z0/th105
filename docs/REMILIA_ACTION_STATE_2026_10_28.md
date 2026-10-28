# Remilia action-state candidate, JP 1.06a

## Status

Address 0x00545090 now has a complete 107-action C++ candidate and a focused
VC8 replay unit. It is **unselected and nonexact**. No implemented.csv,
matches.csv, function status, or accepted byte total is changed.

The first complete candidate emitted 63,444 bytes. Reviewed packet ownership,
difficulty fallthrough, zero-offset coordinates, packet extents, native low-owner
ordering, and captured prelude direction produce
62,912 bytes versus the target's full 63,316 bytes. First mismatch is now +18:
the emitted stack allocation equals target 0x4F0, while zero-register choice differs. Size proximity is not
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
behavior. Native/candidate stack frames both equal 1264 bytes, return sites
146/145, virtual call sites 179/181. Stack coloring and physical ownership
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
629b1dfc49d0a7a2afcec1090b6715cbb892bbe76bb74cca44e8b20a3955e70b

Full positional differences including absent trailing bytes: 59,877.
That count is diagnostic, not a semantic similarity or completion metric.

Receipts: build/frontier-545090-20261028/formal-frame.json and formal-frame-audit.json.
Private raw and source diagnostics are in the same frontier build directory;
draft recovery is under .analysis/frontier-545090-20261028/. The checked-in
source is authoritative. Existing exact receipts remain incremental.

### Physical-owner refinement

The native low sequence places action 214 before 215. Restoring that source
order brings its physical owner span from 1010 to 810 bytes (native 811),
without changing action semantics or adding a padding/return workaround.
The native prelude captures unsigned direction once and then sign-extends
that captured byte for X. The candidate now expresses that flow explicitly.
Neither of those two changes solved the then-first +8 mismatch; no exact credit was awarded.


### Native-size frame from circular request preparation

The 730/731 circular 902 requests prepare count, pointer, layer and direction
before calling sine (for example 0x551DF2..0x551E22), then put the rounded Y
value on the outgoing stack before cosine. The former source instead named
both Y and X before preparing the request.

Only ring902 now expresses X/Y directly in the ordinary call arguments. It
preserves the same casts, packet writes, float loop, lookup order and field
loads. This restores the native call-preparation lifetime and reduces frame
0x4F8 to 0x4F0. The first strict mismatch advances from +8 to +18, at the
choice of EBX versus EBP for zero, not a newly accepted function.

All 101 payload homes still resolve; their native/candidate sorted offset
sets now coincide, including the unusual adjacent extents noted above.
Fresh mapped-action arithmetic counts still agree, and the same action710
physical-call residual remains. Final full payload is 62,912 versus 63,316.
This is an independent native instruction witness, not an automatic transfer
of Komachi's different scalar-angle cause. No packet padding, dummy locals,
register forcing, or compiler-flag change is used.
