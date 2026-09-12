# Natural integer-angle ratio and shared angle probes

## Accepted result

Original Japanese TH105 1.06a, executable SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
`lookup_orientation_ratio_quantized_abs @ 0x004064D0` is **107/107 canonical
exact**, including both return paths through `0x0040653A`. The ordinary C++
implementation is in `src/engine/AngleRatio.cpp`, with its declaration in
`AngleRatio.hpp`. There is no assembly, volatile storage, artificial alignment,
self-assignment or register forcing.

```bash
python3 scripts/check-ida-mcp.py
python3 scripts/typed-re.py 0x004064D0 --json
python3 scripts/build.py --unit gpt-web-angle-ratio-natural --compare --json
```

Local report: `build/angle-ratio-natural-formal.json`. Complete target and
relocated object comparison hashes both equal
`a5e44470d5614abc8207579229c1f2210c18d9ebe26cd1b05b000ebfbce8c847`.
This adds one accepted function / 107 bytes, not a completed large root.
Only the affected angle lookup object was additionally rebuilt after removing
the ratio definition: `0x00406480` and `0x004064B0` remain 34/34 and 30/30 exact.
No unrelated units or aggregate cold replay were run.

## Observed instructions and recovered source contract

The function reads a signed integer argument, computes the absolute tenfold
angle modulo 3600, and loads its denominator from the existing game-owned
float table at `0x006FE8B0`. It takes the zero-return path only on ordered
equality with zero; unordered values proceed to division. The nonzero path
uses the shifted sine index. Both the numerator and result have explicit m32
materialization. The complete flow has two RETs and no external code tail.

An ordinary nonzero branch with separate `float const` numerator and
denominator reproduces those lifetimes under the existing strict-FP profile.
`#pragma float_control(except, off, push)` locally disables exception-sensitive
scheduling and is paired with `pop`. Plain `/fp:strict` without this local
setting gives 107 bytes but first differs at +0x0E: CDQ and PUSH ESI are
scheduled in the opposite order. Command-line `/fp:strict /fp:except-` and
the retained pragma version independently reproduce the exact body.

The `float(int)` return contract is a coherent reconstruction, not proof of
unique original spelling. IDA's inferred `double` was not such proof either.
The float prototype was written to IDA and read back; the durable signature
and source selection are in `config/functions.csv`.

IDA lists one direct caller at `0x005264DF`, in PatchouliObject root
`0x00520890`. Its return-consumer window multiplies ST0 by an m32 field and
later materializes the expression as m32; this is compatible with the
recovered contract but does not uniquely distinguish float from double.
There is no retained source consumer to update or compile. The caller root
is not credited as implemented or exact by this work.

`scripts/audit-x87-return-sites.py 0x004064D0` reproduces the caller window.
This exposed and fixed its singleton MCP-result handling: one caller can be
one JSON object, not an array. Malformed results still fail closed; every
reported CALL is checked against the pinned executable. Tests cover both
transport shapes and malformed rows.

## External compiler corroboration

The pinned [Microsoft VS2005 C++ manual](https://download.microsoft.com/download/1/6/d/16d24ada-5317-4de1-b2b2-890b51813d6e/VS2005_CPP_en-us.pdf)
documents strict FP and independently disabling exception semantics on
physical pages 1627–1628. Pages 27035–27037 document the function-local
floating-point pragmas and their push/pop state. These describe available
compiler behavior; they do not prove the game's original command line.

```bash
python3 scripts/reference-vc8.py --pages 1627:1628
python3 scripts/reference-vc8.py --pages 27035:27037
python3 scripts/reference-vc8.py --pages 26805:26808
python3 scripts/reference-vc8.py --extract-topics
```

The last page range documents explicit data alignment and is now indexed in
`config/reference-documents.toml`. The full PDF/text and regenerated Markdown
excerpts remain local under `build/references/vc8`; URLs, hashes, page indexes,
the extraction script and this interpretation are tracked in Git.

## Still nonexact: quantized sine/cosine and aligned abs

The ROI census finds 295 sine calls and 205 cosine calls, each spanning all
15 roster Object roots. These are the next shared dependencies, not a mandate
to reconstruct every character. Fresh packets are
`build/angle-sine-current-typed.json` and `build/angle-abs-current-typed.json`.

The sine target `0x00406360` is 100 bytes. A private probe using strict FP,
exceptions off, SDK `abs(float)`, float return and a genuinely used aligned
integer index gives a **121-byte nonexact** body. Its first mismatch is
at +0x51, after the float-to-int call. The compiler chooses a 29-byte magic
constant remainder sequence instead of the target's 8-byte CDQ/MOV/IDIV.
The first 81 canonical bytes are diagnostic evidence only, not exact credit.

The tested expression was:

```cpp
__declspec(align(64)) int const index =
    static_cast<int>(abs(phase * 10.0f - 900.0f) + 0.5f);
return g_orientation_cosine_table[index % 3600];
```

In the pinned SDK, float `abs` delegates through float `fabsf` to double
`fabs`. Their real return conversions explain the repeated strict-FP stores;
explicit inert round-trip assignments are unnecessary. The aligned index is
used in the actual lookup, but its alignment is only a candidate source
explanation. No such declaration was retained in production source.

Rejected private trials, all reverted:

- Aligning the actual float magnitude under strict FP gives the wrong home
  at ESP+0 rather than the target's ESP+0x3C. Double return also introduces
  a non-target qword return materialization.
- A real inline quantization helper, generic inline modulo helper, in-place
  remainder and `long` index all retain the magic remainder. LTCG with an
  exported float caller likewise retains the 121-byte body.
- Adding integer abs to a generic index wrapper leaves extra integer abs
  instructions; it is not part of the accepted source.
- `/Os` changes argument allocation and inline decisions; `/Og-` loses the
  required optimized rounding/stack sharing. Neither profile matches.
- The adjacent `0x00406330` target is the SDK float-abs 35-byte shape plus
  11 bytes of aligned frame machinery. An aligned real float result instead
  pins the wrong home. Aligning only a return typedef does not align that
  frame. This independent witness still prevents treating the common
  64-byte-frame cause as solved.

Useful private reports: `build/angle-aligned-index-float-strict-noexcept-compare.json`
and `build/angle-mod-helper-compare.json`; the latter is a reproducible
121-byte / +0x51 diagnostic checkpoint. The tracked sine and cosine sources
remain the previous unverified hypotheses (94 and 88 bytes), with no new
match rows. Their old ledger assertion that x87 proves a double return has
been corrected: the type remains unresolved.

The older handoff/knowledge-base statements that strict FP is ruled out for
the ratio are superseded by this complete result. They tested different
source contracts, so their negative conclusions must not be generalized.
