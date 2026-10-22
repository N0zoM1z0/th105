# Glyph integer-window proof and pen storage, 2026-10-22

Glyph411B80 remains nonexact624 bytes/+89. Fresh layout controls do not change
any of12 font bodies. A new instruction-level proof closes the integer
window's endpoint state for arbitrary32-bit inputs under an explicit memory
disjointness condition. This establishes neither intermediate instruction
identity nor canonical acceptance; all14 differing bytes remain significant.

The exact target is original Japanese1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
IDA again rejects its unrelated open executable. Raw target bytes, actual
native COFF and a pinned optional SMT solver provide the new evidence.

## Fresh compilation and caller census

The unchanged selected CPP SHA256 is
`76e86737670ca41893c2b1940ae77e9f4254e863ae2424971a273634be3f66ca`.
A private baseline and two storage controls compile the complete TU with the
configured O2/Ob1 profile. One control groups X/Y into a two-LONG point-shaped
member; the other uses a two-int array. Offset134/138, eight-byte storage and
owner size194h are checked. They test nominal aggregation without changing
the arithmetic expression, copying instructions, adding storage or claiming
original field ownership. All12 compared function hashes/extents are unchanged.

An independent scan of all2,879,488 raw `.text` bytes, including padding, finds
only the already-reviewed E8 at412756 directly naming glyph. No E9 directly
names it. Scanning the eight font entry addresses yields the nine known
E8 hits. This closes that raw relative-call/jump surface, not computed calls
or function-pointer ownership. It supplies no additional actual glyph caller
to justify a new compilation context.

The fresh public10-function unit replay retains native glyph624/a1f0b4e5,
markup1728/a3c2e09c and the accepted45-byte hex,45-byte surface and289-byte
blend. The33-byte checked character operation is byte-equal but remains
excluded from authored credit. Native color/caller alternatives stay332/324
in the private12-function comparison; the selected linked color acceptance
is unaffected. No whole-unit runtime sweep is repeated for identical payloads.

## Exact window and symbolic observation

Target full-body SHA256 is
`3e67460ec4d76b1bdf2e30566a9dc74d44c3d34116e847e49ea78667bfb93630`;
candidate full-body SHA256 is
`a1f0b4e58a76926fa837cdd852256122752fea9e5c9226332fc02139a8ac7806`.
Every byte outside+88..103 agrees. Extend that window through the common
final ADD at+104, giving18 bytes at411BD8..411BEA, exclusive end:

| Target | Candidate |
| --- | --- |
| MOV EDI,[ESI+13C] | MOV EDI,EDX |
| SUB EDI,[ESP+30] | SUB EDI,[ESP+30] |
| MOV [ESP+10],ECX | MOV [ESP+10],ECX |
| ADD EDI,EDX | ADD EDI,[ESI+13C] |
| ADD EDI,ECX | ADD EDI,ECX |

The shared prefix has loaded cursorY into EDX and height into ECX.
`scripts/prove-text-font-glyph-window.py` canonicalizes the entire624-byte
COFF body using existing bindings and rejects any outside-window difference.
It decodes both windows and symbolically executes actual MOV/SUB/ADD operands
over32-bit registers and a byte-addressed memory array. It compares all eight
general registers, final byte memory, the ordered DWORD write and the six
arithmetic flags CF/PF/AF/ZF/SF/OF. It does not compare intermediate registers,
flags or read order, which differ.

Z3 reports UNSAT for a final-state mismatch when the four ascent bytes at
ESI+13C are disjoint from the four temporary bytes at ESP+10. Inputs otherwise
remain arbitrary32-bit values and memory, including arithmetic overflow and
unaligned/wrapping addresses in the bit-vector model. Instruction bytes are
immutable, accesses must be valid, and asynchronous observers are excluded.
For valid C++ owner/local lifetimes, that specific storage is separate; this
does not authorize a general arbitrary-alias or fault-equivalence claim.

The condition is necessary for this proof. A sensitivity query aliases those
two words: ESI=1000, ESP=112C, ascent16, originY0, cachedY3 and height1. Target
EDI becomes20 while candidate EDI becomes5: the candidate reloads ascent after
the height store. The solver returns SAT for that counterexample. This is an
isolated window state, not a demonstrated valid whole-root object lifetime.

## Independent native cross-check and limits

An independent private Unicorn run executes both immutable18-byte windows.
512 disjoint cases cross boundary/pattern values for ascent, origin and
cachedY with varying height; a513th checks the overlapping sensitivity case.
Every native register and six-flag result agrees with the symbolic model.
Disjoint native endpoint memory agrees, and both write the actual height
temporary. The overlap produces the same20/5 result. Digest:
`25a2f548857eb15fb1d1aedd4d01623dbfd3f1f620df64afcc7565b4827370aa`.

The universal result applies only to the straight-line endpoint abstraction.
Neither proof nor cross-check executes GDI, allocation, callbacks, the full
glyph or RET ABI. They establish no unwind, fault, read-trace, asynchronous
mutation or arbitrary-owner/stack alias equivalence. They do not weaken the
full-byte comparator. The remaining discrepancy is compiler scheduling in
this window; the tested pen aggregation does not explain it.

## Reproduction and next work

```bash
python3 -m pip install -r scripts/requirements-smt.txt
taskset -c 0 nice -n 10 python3 scripts/build.py --unit gpt-web-text-font-render --compare --json > build/font-glyph-build.json
taskset -c 0 nice -n 10 python3 scripts/prove-text-font-glyph-window.py build/match-units/GptWeb_TextFontRender.obj > build/font-glyph-proof.json
```

The full build intentionally exits1 for nonexact candidates. The proof uses
Z3-solver4.13.0.0, separate from the mandatory CI dependency set; its output
records actual solver version and hashes of target/object/tool/config inputs.
Object source/build provenance is supplied by the build receipt, not inferred
from this proof. Selected source and public headers/profile remain unchanged.

Private `build.py`, `census.py` and `native_check.py` are in
`.analysis/font-glyph-pen-20261022/`. Reports/objects are in
`build/font-glyph-pen-20261022/`, including `comparisons.json`,
`raw-rel32-census.json`, `selected-build.json`, `selected-window-proof.json`
and `native-window-check.json`. Keep the selected and baseline COFFs available;
completed duplicate pen controls may be restored from their hash-verified
`completed-pen-controls.tar.gz`; `retention.json` records the readback hashes.
No origin, selection or exact rows change.

Next inspect the actual linked begin/end/reset bodies for their shared EDI
save-scope residual, using the existing genuine font owner/provider image.
Do not repeat neutral glyph field/expression controls without a new lead.
Strict totals stay1,379 functions/234,584 bytes,10.98% of the current authored
denominator. This is scoped font replay, not a new all-unit cold claim.
