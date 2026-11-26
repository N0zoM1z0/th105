# Tenshi action 606: original float sine, not a custom double facade

The actual Tenshi action 606 call now uses std::sin(p[0]) from the selected
original VC8 cmath/math.h headers. The old descriptive double-return
tenshi_sine_radians declaration is removed. No hand-written implementation or
new wrapper replaces it.

## Independent source/type and native evidence

Native 63D3C0 is an 18-byte float adapter: it loads the float argument, calls the
original CRT CIsin68B670, rounds the result back to the float argument slot,
reloads that float and returns. Both original
math.h entries, sinf(float) and the C++ sin(float) overload, naturally emit these
same complete 18 bytes in the actual Tenshi TU. The source caller references the
C++ overload; this does not claim a uniquely recovered original spelling.

Whole canonical helper SHA-256:
9e008d740e1b185cbc9a37ad9c9ad72e34f4e15e20a8ce869efc92bd38afef1c.
Only the original E8 field 5 is relocated to independently classified CIsin.
All other bytes, the complete RET 0 boundary and full-inventory uniqueness pass.
There are no data-reference masks, private-register declarations or dummy uses.

Native 646930 passes the actual float at stack top. Its 646935 instruction
compares the returned value with DWORD zero at readonly 6D6EA8, then performs
the ordinary four-byte caller cleanup. The source's corresponding 646930 call
has the same argument/result/cleanup contract. The full native 47784-byte
callable hash protects the owning function/site; the source whole candidate
and its sole original-overload relocation protect the actual source edge.

The previous double-return facade made VC8 use a QWORD zero comparison at a
different literal address. Replacing that facade with the original float
overload changes only four bytes of the entire 49032-byte canonical candidate:
the comparison opcode and three bytes of its literal address. No array extent,
frame, helper flag, branch layout or extra operation was changed. The new
four-byte zero binding is backed by the actual native FCOMP operand.

Input angles are passed unchanged. In particular, action 606's30-step values
are not converted from degrees to radians as a supposed gameplay correction.
The original CIsin call and shipped behavior are retained.

## Current qualification

The original math.h/cmath header hashes and compiler profile remain pinned by
`scripts/vc8_float_sine_origins.py`. It rebuilds the actual caller unit, checks
both original aliases, the sole named CRT relocation, inventory uniqueness and
the real float argument/result/cleanup window. Build receipts capture the
executable source inputs.

The complete parent root is now canonical exact over all 47,784 code bytes and
its 48,968-byte payload. Its source call is therefore at native `0x00646930`.
See [the root result](TENSHI_ACTION_STATE_2026_10_27.md) for whole-root acceptance.
This helper remains compiler-generated and excluded from authored progress.

Reproduce with `scripts/repo-python scripts/vc8_float_sine_origins.py` and
`scripts/repo-python scripts/build.py --unit exact-first-tenshi-action-state --compare --json`.
