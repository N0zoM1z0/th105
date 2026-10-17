# Reimu root: void ABI and complete default dispatch candidate

## Exact target observations

Target remains original Japanese TH10.5 v1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
`Reimu_dispatch_action_state_vslot28 @478FA0` is81550 callable bytes,
SHA256 `dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6`.
The Reimu primary vtable slot6C4154 points here. The existing void/noargs
thiscall model, saved registers and RET cleanup remain unchanged.

The complete root was decoded from its attested entry (20256 instructions).
Four selector/default ranges were pinned separately. Dispatch sign-extends
WORD13C at4791D4, separates direct300/560, and uses the three reviewed tables.
The high selector487A77 subtracts561 and unsigned-checks237; values above798
reach48CE1F. That default calls real4740C0 and returns through48CE2D.
Negative short actions and table holes use the same default after entry gates.
The prior source's action>798 pending return was an incomplete adapter boundary.

## Reproducible void compiler input

```bash
python3 scripts/probe-reimu-action-source-shape.py --void-root --output-dir build/reimu-void-root/expanded
python3 scripts/audit-reimu-void-root.py build/reimu-void-root/expanded/ReimuActionStateDispatch.obj
```

The new opt-in generator emits ordinary C++ with a real
`void ReimuActionStatePreludeView::run_action_dispatch_root()` member,
COFF symbol `?run_action_dispatch_root@ReimuActionStatePreludeView@th105@@QAEXXZ`.
It removes exactly the reviewed upper pending guard and changes391 completion
returns to bare returns. The lexer preserves strings/comments and rejects any
remaining pending return. A nonvirtual declaration is added only to the private
copied header; existing field assertions still compile. All output stays below
build/. The retained source/header and normal bool generation are unchanged;
a fresh bool re-emission is byte-identical to the preceding checkpoint.

This is a complete void/default compiler-input candidate, not selected source
or an exact match. The root's ledgers stay authored, unclassified and
declaration-only. No shared source header/layout/profile/relocation change or
implementation/exact credit was made.

VC8 SP1 `/O2 /GS- /GR /EHsc /MT`, default FP, produces object SHA256
`b9d920de863864d67d19c4c34610cb27eede74583eb327ebb57eaecd3cdb8a2b`.
The untouched mapper retains45/50/33 primary groups,126 destinations and0
target-group splits. All11 nested/primary switches remain. Source prefix is
81128 bytes, text with metadata82500,1167 decoded E8s and148 RETs versus
target81550/1188/153. Frame598h versus570h still first differs at478FA8.
Relative to bool staging, height and zero-velocity call-site counts each drop2;
no external relocation or register tail jumps appear. Counts/spans include
alignment and are diagnostic, not accepted compiler boundaries/equality.

## Native ABI and default evidence

The fixture now distinguishes bool and void return contracts. Both still
require a genuine RET to the supplied caller, correct ESP, saved registers
and empty x87 TOP. Bool retains strictAL0/1 and its pending interpretation.
Void gives EAX no result meaning; it does not write or synthesize EAX. The
requested contract must match the compiler's noargs thiscall symbol suffix.
Nine tests cover this distinction, source conversion and fail-closed inputs.

The current void object passes **0/1544 native differences**, input SHA256
`c61982a9ccc694e3b6667371b5a4882e896da92d11320dd4aa3784f464787b80`:

- 1010 integration cases include inputs for all128 nondefault source actions.
- 510 cases sample85 canonical default actions at boundaries, negative/upper
  values, both x87 precisions and both early entry gates.
- 16 upper-default cases execute the actual shared Fighter body through RET.
- 8 740 cases compare both genuine pre-read boundaries for indeterminate slots.

Stops are1246 genuine RETs,82 owned-object requests,30 effects,177 common
entries,1 set669 and8 pending indeterminate reads. No later-action handoff
remains. Ordered helpers/arguments, actual actor/MT/world state and first
pointed payload are compared. The observed return-byte histograms contain
values such as9,76 and255 and differ between target/source; those registers
are not void results. Returned world requests and arbitrary initial stack
contents remain outside this proof.

A compiled control restoring `if (selected_action > 798) return;` is detected
in **10/510** default cases. Entry-gated cases still return early as expected.
The previous bool object retains0/12 smoke and0/8 unknown-boundary checks;
its source and default return-byte checks were not relaxed.

The710/711 and720 loop contracts and all48 510 packets/12 level reloads pass
on the void symbol. Their `--symbol` selection is explicit; old defaults stay
unchanged. No full historical or aggregate cold replay was run.

## Remaining proof obligations

The generated candidate recovers the intended entry ABI and default domain,
but full canonical matching remains unproved: frame/layout, callable extent,
REL32/DIR32 ownership, returning world contexts and compiler/TU/LTCG provenance
still require work. A raw scan in the reviewed constant range finds160 x87
4/8-byte value/address groups with no duplicate addresses per value; this is
only literal-placement evidence, not a complete relocation contract. Decoded
call-count deltas identify remaining wave/counter/landing sharing differences.
Do not restore a bool result merely to improve layout or call counts.

Receipts, selector packets, native/static/control reports and structural
diagnostics are under build/reimu-void-root/. All9 primary Ghidra DB hashes
were checked unchanged against the reused direct-analysis identity. No new
process/clone or IDA semantics. Obsolete initial/control/bool copies and caches
are cleaned; current void source/object and bounded evidence remain. Next
recover truthful full relocation ownership and the remaining source/compiler
sharing before canonical root acceptance.
