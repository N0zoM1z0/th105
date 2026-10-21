# Font text entry: source and provider evidence

This checkpoint recovers complete source for the normal ECX/RET12 font text
entry `0x00412670`, including both optional output pointers. It is
**source-present, nonexact**: ordinary COFF is326/326 bytes and117 instructions,
while the target has120. No exact function, byte or remote chunk is added.

Only original Japanese TH10.5 v1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. Target/status/tracking checks pass. IDA preflight rejects its wrong
open executable; no IDA semantics or metadata writes are used. Raw PE facts
and the pinned VC8 compiler provide the new evidence.

## Observed entry and complete policy

Raw CFG traversal reaches all326 bytes/120 instructions and closes at RET12
`0x004127B3`. Complete target SHA256:
`5609c1c997c0d979f17f0c9e529e3df3d6d36c52456280dfc6dd04da877c3e36`.
The candidate-ledger direct-call census finds4097A0 at409883 and markup411FA0
at41243B. Both supply normal ECX font plus text/width-output/height-output stack
words. This census does not claim complete indirect or remote-chunk coverage.

The actual sequence is:

1. Capture signed-int text length from `strlen` and initialize temporary null.
2. If font flag11D is nonzero, allocate an unsigned array with element count
   `height148 * pitch150`, clear four times that count and publish base140.
   The count has target32-bit multiplication and the generated array-new
   overflow gate. No synthetic buffer or fixed-size allocation is used.
3. Zero each nonnull output pointer in width-then-height order, then begin.
4. Decode lead bytes81..9F or E0..FE as two-byte codes. A0..DF and FF are
   signed single-byte codes, not double-byte leads. Advance by one/two first.
   Character0 clears the captured length; '<' calls markup and adds its signed
   consumed count. Other characters reach glyph only when the advanced offset
   does not exceed the captured length, skipping a truncated terminal pair.
5. End rendering. Reload flag11D; if set, blend the temporary into freshly
   reloaded destination144 and delete the array. There is no source-added RAII
   cleanup or exception path around the native GDI work.

The target's double-byte path at412726 performs a DWORD read before swapping
AL/AH. The natural source constructs the code from two byte accesses. Logical
code/consumption agreement does not establish identical physical read footprints
at protected-page boundaries. That issue and arbitrary aliasing remain open.

The source includes the actual VC8 `<new>` declarations. Without them the
initial private probe emitted scalar new/delete symbols; the declared array
operators emit the correct native symbols. Target665B8A is the independently
classified E9 alias to scalar allocation689DCB, and68AA26 is the separate E9
alias to6898EA/free. Both alias boundaries remain compiler exclusions, with no
new origin or exact credit.

## Rejected retained assumptions and bounded layout

The retained `CompositeTextureText.cpp` omits both output parameters and treats
all81..FE as double-byte leads. It is not selected as the new font provider.
Raw begin291 bytes/83 instructions and end168/49 close independently, with
native list front/pop cleanup. Their accesses establish a checked native color
list at15C, its sentinel at160 and count164. Glyph411D3F and color/reset code
4118E2/41198B independently read/write the fallback color at168. Begin also
writes16C/16D. Thus the old facade's `fallback_color_164` label and any inference
that168 is the full font size are wrong.

`TextFontRuntime.hpp` models only the fields used by the two selected source
functions: flag11D and surface140/144/148/14C/150. It neither inherits the old
labels nor claims a complete font size. Its member declarations retain normal
source ABIs. The target's private lowering is separately observed:

| Provider | Target receiver / arguments |
| --- | --- |
| begin4119A0 / end411AD0 | ESI receiver, no stack arguments |
| glyph411B80 | EAX receiver, code/two outputs on stack, RET12 |
| markup411FA0 | EDX receiver, ECX height output, cursor/width output on stack, RET8 |
| blend4127C0 | EAX receiver, source/destination on stack, RET8 |

Full raw markup1744/463 CFG closes, but glyph624 and blend289 have internal
unreachable alignment instructions. Their provisional spans cannot be promoted
through the strict linked-body gate without separate boundary/ownership work.
The real full font owner, providers, native GDI declarations/global and TU
visibility still need recovery before an honest linked experiment. No fake
provider, exported private entry or register-ABI facade is supplied.

## Focused compiler results

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-text-font-render --compare --json
# Expected exit1: complete nonexact comparison, no blocked relocation.
```

Selected source SHA256:
`ab5fbbe9f2f0f76041a79e7f4165dc39c0ea75fedd9551c8a7c85c4e88bb5f06`.
Complete canonical source SHA256:
`f114c979bd2e32d275f9402d8ba58a350fc7aacaae8915eb7e748eb73cd01eb9`.
The first mismatch is412670/+0: source starts PUSH ECX and uses an ordinary
stack frame; target has the aligned EBP frame. Font/index registers, lead-range
branches and source-normal versus target-private call entries also differ.
Same size is diagnostic, not acceptance or proof that standalone recovery is
impossible. No padding, inert local, forced alignment or assembly is used.

`TextTextureRuntime.cpp` now includes the new shared prefix declaration. Its
complete110-byte wrapper and264-byte backend remain byte-identical to the
previous canonical candidates50731d79 and15555b85, nonexact+7/+0. Existing
`Title.hpp`, compiler settings, accepted sources and relocation ledgers are
unchanged. Transitive dependency scanning finds zero affected accepted units;
only these two nonaccepted focused units are rebuilt. No unrelated or aggregate
cold replay is claimed.

## Bounded logical regression

The private Unicorn harness executes actual complete target and freshly compiled
source instructions. At provider boundaries it supplies explicit abstract callee
observers, rather than executing GDI or claiming recovered provider semantics.
It checks target-private and ordinary source argument locations separately.

All **13,100 cases pass**: every lead byte with five representative trailing
bytes, intermediate on/off, null/separate/aliased dimension outputs, truncated
pairs, empty strings and markup. Selected strings additionally vary a destination
change at end, proving the wrapper's fresh144 reload. Comparisons include
ordered wrapper stores, allocation/clear/publication/deletion, logical helper
trace/arguments/consumed results, final bytes, ESP and callee-saved registers.
Height2/pitch12 and accessible trailing text padding are explicit bounds.

A separate100-case sensitivity run keeps selected source100/100. Restoring the
old broad lead range fails40; deleting output initialization fails80. Both
controls are genuine compiled C++ changes, retained privately and not selected.
This supports the loop/output recovery without substituting semantic agreement
for exactness or claiming GDI, overflow-allocation, arbitrary-alias or physical
read-footprint coverage.

Receipts, full raw facts/caller census and frozen controls are under
`build/font-render-20261021/`; corresponding recipes are in
`.analysis/font-render-20261021/`. Completed unselected controls are archived
31,936 ->5,789 bytes, with per-file SHA256 readback before loose-file deletion.
Selected source/object/binary and comparison/semantic receipts stay available.
The final gates are:

```bash
python3 scripts/validate-tracking.py --require-target
taskset -c 0 nice -n 10 python3 scripts/ci.py
git diff --check
```

Next: recover native font begin/end/color lifetimes and real glyph/markup/blend
providers, then measure the genuine closed TU/private-call context. Keep the
complete selected source nonexact until canonical zero-difference comparison.

## Native end provider follow-up

[The native end checkpoint](TEXT_FONT_END_2026_10_21.md) supplies a real
file-local end provider in this TU and extends the bounded prefix through its
actual native color list. The selected caller is now324/116, canonicalc23fa0a9,
still nonexact+0; the326-byte source/hash and receipts above describe the frozen
preceding checkpoint. VC8 naturally supplies ESI to the complete168-byte end,
which remains nonexact+7 solely on EDI save scope. Current caller13100 and
actual native-end576 bounded cases pass; all other providers remain open.
