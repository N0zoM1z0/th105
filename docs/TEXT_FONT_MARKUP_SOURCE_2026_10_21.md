# Native font markup: complete parent source, nonexact

`TextFont_parse_text_markup @ 0x00411FA0` now has genuine native C++ source in
the actual font/text TU. Complete target1744/463 instructions versus source
1682/459 remains **nonexact+16**, full-source canonical065cb3b3. All8,640 bounded
actual-parent instruction cases pass, with focused negative controls. No exact
function, byte, compiler helper or EH metadata credit is added.

Only original Japanese TH10.5 v1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. Target/status/tracking preflights pass; IDA rejects its wrong open
executable. Raw PE and pinned native compiler products supply the evidence.

## Source and complete comparison

The implementation uses actual deque<string>, native temporary strings, a
char array and the shared194-byte owner/128-byte config. It finds '>', copies/
terminates the token buffer, splits on space/equals/tab/newline, and performs
the observed br/ruby/accent/color policy. There is no pasted decompiler syntax,
manual STL layout, fake provider definition, forced register or frame filler.
The existing [native-class audit](TEXT_FONT_NATIVE_CLASS_2026_10_21.md) pins the
full1744-byte target CFG and actual41276A caller edge.

Source full canonical SHA256:
`065cb3b39390e041cfcb8bdf3d21063ca71f62d8ee31c69fb92bb0bec8d65982`.
Target main-body SHA256:
`6343d2d6639459aaeadb9de2acd74ecbb0be02f8a908e4b84af385f1daeccebb`.
The first mismatch is411FB0/+16: source reserves788 local bytes; target796.
The ordinary source member receives ECX this and returns RET12. Target receives
font in EDX and height output in ECX, with cursor/width output on stack, RET8.
The comparator records the full1682-byte source extent; it is not cropped to
manufacture target size or partial credit.

A genuine file-local stdcall parser in the same actual caller context is1665/
454, canonical87810ee0, RET4. VC8 shares the caller's ESI owner and privately
passes other arguments, differing from the target's EDX+ECX/RET8 contract.
This is a phase-scoped negative result, not a fabricated external ABI or proof
that standalone recovery is universally impossible. The normal member source
is retained until genuine provider/TU/link evidence resolves the boundary.

All six configured functions compare without resolver failures. The five prior
complete runtime programs remain byte-identical: begin291/728a7bf3, end168/
e1daa198, text322/7087f023, glyph645/51eb276d and accent433/d0a47cc5. Their previous
large regressions are not unnecessarily replayed. Existing actual native owner
and config exact roots are unaffected because their source/header inputs stay
unchanged.

## Ruby and token policy verified

Missing '>' returns the remaining strlen. An empty token deque and short hex
parameter retain their observed checked-access boundaries; no input guard is
added. Token strings cover both SSO and heap storage. Ruby start saves18C/190,
copies token1 into native string170 and sets16D. Ruby end uses a real automatic
owner/config, signed height/3, face copy and flat start colors, then observes
the saved-baseline gate and configures/renders/destroys the local object.

For positive span, counting uses lead ranges81..9F/E0..FE. The width estimate
uses **byte length**, with gap
`(span - byteLength*rubyHeight/2)/(characterCount+1)`.
Both originX and spacingX receive it; Y values remain0. The same optional
width/height outputs reach recursive rendering, including null and alias cases.
No spacing clamp, added GDI failure gate or changed exception policy is added.

Private Unicorn runs execute complete target and source parent instructions.
Explicit abstract CRT/STL/font/color observers handle each actual native/source
calling contract. Comparisons include token operations, visible allocations/
releases, saved text/flags/cursor stores, normalized local-font/config and
recursive arguments, optional output flow, final bytes, return count, ESP and
saved registers on normal return. Cases vary all tags/unknown/missing terminator,
empty/long tokens, invalid hex positions, saved ASCII/SJIS/nonlead/embedded-NUL
strings, signed height and spacing, ruby state and optional output aliases.

All **8,640/8,640** pass. A separate72-case actual ruby-close sensitivity run
keeps the selected source72/72; genuine compiled controls fail:

| Wrong policy | Failures |
| --- | --- |
| treat every81..FE byte as a SJIS lead | 12 |
| use character count instead of byte width estimate | 12 |

These are parent-instruction/callee-observer results, not actual CRT/STL/GDI/
recursive-font execution, arbitrary aliasing, allocation-failure or protected-
page coverage. Invalid-index cases stop at the first observer boundary; they
do not execute the platform failure handler or C++ unwind runtime. The harness
explicitly catches callback errors outside ctypes before evaluating a result.

## EH facts remain distinct from acceptance

Target handler6BE2A8 is46 bytes and names FuncInfo6E49EC, a36-byte VC8 record
with four states and32-byte unwind map. Source native COFF emits the same
four-state graph `[-1,0,1,0]` and cleanup roles:

| State | Cleanup role | Target action |
| --- | --- | --- |
| 0 | deque<string> | 6BE270 ->40F8E0 |
| 1 | temporary string | 6BE27B ->401E00 |
| 2 | placement delete during construction | 6BE286 ->402810 |
| 3 | local font owner | 6BE29D ->4114C0 |

This supports the natural C++ lifetime interpretation. It does **not** prove
byte equality: source funclet stack offsets differ by4, handler frame slots
by8, and complete source/target metadata/ownership are still unqualified.
No helper boundary or EH exclusion is inferred from that role similarity.

The new handler data role attests the target's complete46 bytes for the parent's
DIR32 address identity only. It does not waive handler/FuncInfo/funclet checking.
Exact acceptance remains unavailable until complete code, ABI and EH ownership
are validated. The source also retains ordinary typed declarations for real
color/reset/hex/setter/blend providers; no fake linker stubs are supplied.

## Operand provenance and scope

Ten new data keys are unit-local aliases. Exact source literal-pool bytes and
actual target addresses are checked independently. The five-byte delimiter
copy uses one initialized final NUL read at addend4; that reference has a
one-byte literal role and exact allowed addend4, rather than padding the source
section or weakening the comparator's initialized-section bound check. Existing
data rows and all accepted-unit definitions remain unchanged.

Only the nonaccepted font source/unit is affected. Dependency and explicit
mapping audits find no accepted consumer of the new aliases; shared headers,
profiles and matches.csv are unchanged. No unrelated or aggregate replay is
claimed. The source-present count advances by one; exact totals and SVG ratio
remain ledger snapshots, unchanged by this checkpoint.

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-text-font-render --compare --json
# Expected comparison_failed: six complete nonexact extents, no resolver failure.
python3 scripts/validate-tracking.py --require-target
taskset -c 0 nice -n 10 python3 scripts/ci.py
git diff --check
```

Full native/target disassembly, raw and canonical contexts, static EH packet,
source/COFF snapshots and regression receipts are under
`build/font-markup-20261021/`; private recipes are under
`.analysis/font-markup-20261021/`. Completed controls are compressed after
per-file SHA256 readback. Next: real color/reset/hex/setter/blend definitions
and genuine closed-TU/link evidence; Reimu496540 remains nonexact at+31.
