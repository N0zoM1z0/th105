# CDesignNumber rendering and private value dispatch

Three complete functions are newly canonical exact: CDesignNumber render at
**40AF80, 55/55**, offset render at **40AFC0, 63/63**, and CNumber bound-value
dispatch at **414EB0, 95/95**. This adds three functions and 213 exact bytes.
The complete floating-render source at 415050 remains **547/581 nonexact**,
first difference **415053/+3**. No floating-body exact credit is recorded.

## Observed target facts

All instruction, vtable and field facts come from the original Japanese 1.06a
PE, SHA256 `56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
IDA attestation still rejects the attached database; it was not used.

The preceding [lifetime recovery](DESIGN_NUMBER_LIFETIME_2026_10_21.md) proves
CDesignNumber's E4-byte object, CNumber member at +18 and tile at whole+40.
RTTI-owned vtable 6D6AC0, COL 6DCAB0, places offset/render in slots +10/+14,
cells 6D6AD0/6D6AD4. Their complete 18-instruction bodies gate on byte+14,
add local floats +0C/+10 to base floats +4/+8, and optionally add two incoming
float offsets. The resulting arguments have real dword spill/reload boundaries.
Both pass the member pointer in EAX and call 414EB0 at 40AFB0/40AFF7. Their
returns consume zero/eight bytes respectively.

414EB0 has 37 instructions and two complete RET8 paths. It retains its EAX
receiver in ESI, loads mode byte+20 and the value-interface pointer+24, and
selects by fraction count+1C. The integer path calls adapter slot 0 and the
ordinary thiscall integer renderer 414F10. The fractional path calls adapter
slot 4 and the private floating renderer 415050. Integer digit count is +18.
The two actual adapter getters are independently
[complete exact](NUMBER_VALUE_INTERFACE_2026_10_21.md). Getter calls consume no
stack arguments: the already prepared stack words belong to the later render
call. The floating getter returns ST0, stored as a four-byte value argument.

415050 has 207 instructions through RET24 at 415292..415294, followed by
eleven INT3 bytes. The receiver arrives in ESI, with six stack words: value,
x, y, integer count, fractional count and sign mode. EBP is retained and ESP
is aligned down to 64 bytes, with a 38h-byte allocation. Its complete behavior
is covered in source:

- Negative magnitude selects suffix 2; otherwise suffix is the sign-mode
  boolean. The integer part uses the target-backed ftol helper.
- Positive fractional count builds an integer power of ten, obtains the
  fractional value through fmod(value,1.0), and renders its digits from right
  to left. Decimal glyph is 12.
- The decimal adjustment preserves `(1.0f - 0.33f) * step`; the float at
  6D6EFC is exactly `c3f5a83e`. Step is `(width+spacing)*scale`.
- Positive integer count renders a fixed number of digits. Otherwise the
  loop uses the last digit and -1 sentinel. The suffix glyph is suffix+9.
- All five glyph-call sites target the already reviewed tile renderer
  4099F0, using the tile at member+28 and quotient/remainder by columns+14.

The new authored-origin rule for the nonexact floating function pins its
complete body hash, incoming edge from exact 414EB0, outer vtable cells,
decimal literal and all five tile-call sites. This is game UI ownership,
independent of whether its compiler frame matches.

## Source visibility and compiler evidence

`src/ui/DesignNumberRender.cpp` defines both file-local helpers with ordinary
typed static stdcall source. The complete definitions remain visible to the
compiler with both outer callers. VC8 privately generates EAX/RET8 at 414EB0
and ESI/RET24 at 415050; there is no external declaration pretending that the
private entries use a standard receiver register.

The selected unit uses SP1 O2, strict FP, exceptions off, and retains EBP only
in the floating helper with a local FPO setting. This follows the observed
real frame and six stack arguments. Without the retained frame, VC8 uses EBP
as a general register and promotes fractional count to EAX; its floating
callee returns RET20 and the dispatcher becomes a different 81-byte body.
Retaining EBP naturally restores stack counts and the entire exact 95-byte
dispatcher, including virtual argument evaluation and both return paths.

The floating source has a normal EBP frame without the target's 64-byte
alignment. Its entry protocol now agrees with the target, but the complete
body differs. Original flags, local types and TU/LTCG ownership remain open;
the FPO setting is a reproducible source view, not unique original provenance.
No aligned dummy, padding, assembly or inert local is introduced.

Private controls also tested default FP, strict FP with exception delivery,
strict FP with exceptions off, a real double result temporary, internal member
visibility, local fenv access, and RTM instead of SP1. Strict FP preserves the
0.33f subtraction and regular fmod call; disabling exception delivery restores
the observed ftol helper. A double temporary adds a real qword spill, internal
members retain ECX, and RTM retains the same unaligned frame/count promotion.
None explains the 64-byte frame. These are compiler diagnostics, without new
exact credit or a claim that every historical alignment hypothesis is closed.

## Reproduction and state

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py --unit gpt-web-design-number-render --compare --json
python3 scripts/check-match-literals.py --require-target
python3 scripts/validate-tracking.py --require-target
```

The build intentionally exits 1 for the pending floating body while reporting
the three complete exact comparisons. Its literal audit checks source value,
target bytes and relocation addend; no initializer mismatch is waived.

| Artifact | SHA256 |
| --- | --- |
|Selected CPP|`49d44f0e7bb236da792120d1d50347a4ab4be9d69a54270b5b1adf26ee5d0f04`|
|Formal COFF|`861e6d58d4bba244fe63e220732c8f6cc1df2cf3fcee134884938b03078a900c`|
|Canonical render55|`10521bf1de0d48694c5cb77607cb6ab155cc56b560a70f506f9e13acf96d4e57`|
|Canonical offset63|`17133ed6590650cd0a633da2e40869be5944da304225071a602b856ce51beacd`|
|Canonical dispatch95|`cd9a23a4f8e69c74c03fce8ba3b1996ebcc287feb47ee038996d8f1a375a8405`|
|Target floating581|`11ddf568e6f2fd9607a1f317b4d11db4f8ec16756e76b59f1cb540003221d40a`|
|Canonicalized source floating547|`f4b12bbc469037ef54173ae36023048b0c054c5788814abb9bdd915bd053a343`|

Receipts reside in `build/design-number-render-20261021/`, especially
`target.json`, `render-final.json` and `render-acceptance.json`. All 196 old
origin-rule selections remain unchanged and disjoint; the one new floating
rule's target witnesses pass. The existing relocation ledger is an unchanged
prefix plus one new literal alias, used solely by this unit. No previous
header, profile, source partition or binding changes, unrelated replay or cold
aggregate claim is involved. Future changes to CNumberRuntime.hpp must include
this new consumer in their affected replay set.

Unselected private COFF/assembly controls are gzip-compressed after verified
round trips; `control-compression.json` retains original and compressed hashes.
The formal match-unit objects and comparison receipts remain available.

The preceding getter checkpoint retains its constructor728, renderer312 and
two getter6/6 results. Initializer414E40 retains its known102/104 mismatch.
ReimuObject496540 remains nonexact at49655F/+31; this work changes no Reimu
source or accepted state.
