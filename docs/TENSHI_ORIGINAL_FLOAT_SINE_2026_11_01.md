# Tenshi action606: original float sine, not a custom double facade

The actual Tenshi action606 call now uses std::sin(p[0]) from the selected
original VC8 cmath/math.h headers. The old descriptive double-return
tenshi_sine_radians declaration is removed. No hand-written implementation or
new wrapper replaces it.

## Independent source/type and native evidence

Native63D3C0 is an18-byte float adapter: it loads the float argument, calls the
original CRT CIsin68B670, rounds the result back to the float argument slot,
reloads that float and returns. Both original
math.h entries, sinf(float) and the C++ sin(float) overload, naturally emit these
same complete18 bytes in the actual Tenshi TU. The source caller references the
C++ overload; this does not claim a uniquely recovered original spelling.

Whole canonical helper SHA-256:
9e008d740e1b185cbc9a37ad9c9ad72e34f4e15e20a8ce869efc92bd38afef1c.
Only the original E8 field5 is relocated to independently classified CIsin.
All other bytes, the complete RET0 boundary and full-inventory uniqueness pass.
There are no data-reference masks, private-register declarations or dummy uses.

Native646930 passes the actual float at stack top. Its646935 instruction
compares the returned value with DWORD zero at readonly6D6EA8, then performs
the ordinary four-byte caller cleanup. The source's corresponding6469A3 call
has the same argument/result/cleanup contract. The full native47784-byte
callable hash protects the owning function/site; the source whole candidate
and its sole original-overload relocation protect the actual source edge.

The previous double-return facade made VC8 use a QWORD zero comparison at a
different literal address. Replacing that facade with the original float
overload changes only four bytes of the entire49032-byte canonical candidate:
the comparison opcode and three bytes of its literal address. No array extent,
frame, helper flag, branch layout or extra operation was changed. The new
four-byte zero binding is backed by the actual native FCOMP operand.

Input angles are passed unchanged. In particular, action606's30-step values
are not converted from degrees to radians as a supposed gameplay correction.
The original CIsin call and shipped behavior are retained.

## Provenance and limits

Raw original header pins:
- math.h:3cdf840fdb5db5a4c98fb849b6247f0f74dbd3071620ab218634d2c9ab58b791.
- cmath:66f7a7e9da038ec07760f9aef087ef107311ed8474b36e7a64ae924f3d6e874e.

The narrow origin validator checks both unmodified vendor headers, original
tool/library pins, Git-normalized actual caller-source hashes and the existing
ordinary/O2/GS-off unit profile before recompiling. It rejects the old custom
facade, a different overload/intrinsic, changed call/cmp/cleanup fields, partial
bodies or another compiler profile. The ordinary minimum-byte origin gate is
unchanged; acceptance here uses full source/header/caller proof, not a lowered
masked threshold. The original C adapter and C++ overload count once.

The giant remains NONEXACT:49032/native48968, frame328/native320, first+8,
new complete candidate SHA
9f6b6d5f77a995480b94d5557661de6a14ccbee9b1eb67a7e5408dfb4747ed7e.
No full-root semantic or authored exact credit is implied. Existing low-owner
merges and all other residuals remain open. This corrects a source/type boundary,
not a claim that a gameplay defect was fixed.

Only helper63D3C0 moves review to compiler-generated exclusion.
Excluded2006/review366; authored exact1431/443916 bytes, source1635/
authored1655/mapped1820 and777 units stay. The existing Tenshi unit now contains
the full exact18-byte library helper alongside its nonexact giant. Mixed-unit
comparison_failed remains expected and is not described as a full unit pass.

## Checks

- scripts/repo-python scripts/build.py --unit exact-first-tenshi-action-state --compare --json
- scripts/repo-python scripts/audit-tenshi-action-state.py
- scripts/repo-python scripts/vc8_float_sine_origins.py
- Narrow vc8-original-float-sine-106a origin replay.
- Eight tests protect source/header pins, LF/CRLF handling, typed scope and
  actual float stack argument/result/cleanup; three real-byte mutations fail.
- scripts/repo-python scripts/ci.py and git diff --check pass.

TenshiActionState.hpp has only this source consumer. No unrelated accepted unit,
shared layout or compiler flag was changed; no cold corpus build or generated
executable run occurred. Evidence is raw-PE based, not new IDA semantics.
