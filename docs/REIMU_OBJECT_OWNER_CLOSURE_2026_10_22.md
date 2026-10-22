# Resolved ReimuObject owner contexts, 2026-10-22

The complete-owner graph now resolves with real source providers in **two
48-object images**. The root is retained by the actual pool and 17-slot
vtable, without a root export. Both images reproduce the target's eight base
type names/PMD offsets and close all 22 source switches. Neither root is
exact: root-CIL differs at +0; the ordinary native root differs at +31.
The existing public source selection is preserved.

## Real provider closure

This continues the [first failed 36-object owner link](REIMU_OBJECT_COMPLETE_OWNER_2026_10_22.md),
using only original Japanese 1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
IDA was preflighted and again rejected for its `10350095...` image.

The new [auxiliary renderer434F30](ANIMATION_AUXILIARY_RENDER_2026_10_22.md)
and [luma/alpha renderer6656E0](SPRITE_LUMA_ALPHA_2026_10_22.md) supply the two
unselected authored bodies. Existing real implementations supply the other
render adapters, draw publisher, render mode/blend, texture binding, action980
continuation and pool locking. Eleven newly compiled native provider inputs
reduce the first 16 unresolved names to four in an actual 47-object link.

Two of those four are references from the unused device-reset method in the
full RenderModeManager TU. A separate private native provider uses the
unaltered actual `apply_render_mode` definition needed by the owner graph.
Its accepted callable is **482/482**; the following 18 bytes of local switch
data/alignment also reproduce the target, **500/500** for the full section.
No missing reset behavior, stub or code-address binding is introduced. This
is a diagnostic native provider partition, not an original-TU claim. The
full-TU failed link remains retained with its separate inputs and diagnostics.

The actual checked map lookup is emitted by the pinned VC8 header through
the existing accepted auxiliary-sprite construction source:
`std::map<int,AuxiliarySpriteSequenceBlockView *>::find`. Its full body
reproduces **105/105** at `45C320`, canonical SHA256
`3be84050d552bc5febe06a6be1b509ce5db9dd0cc3a4d6ea9b57ade5bde24229`.
This address was already positively excluded as compiler-generated. Its
hidden iterator-result ABI matches the existing explicit-result lookup view;
the private link binds that view directly to the actual header-generated
body. No authored progress is assigned to this library code.

## Consistent lookup and receiver views

The remaining two unresolved names are double-facing quantized sine/cosine
lookups requested by sprite rotation and Reimu initialization. The selected
root and native CharacterObjectRuntime instead use float-facing declarations.
The private resolved context does not alias one return declaration to another:

- Keep the existing real float-return lookup definitions for the root/runtime.
- Compile the actual public double-return source algorithms with distinct
  `owner_double_...` names and the same external float table. Rename only
  the corresponding declarations/calls in private rotation and initializer
  source copies. Both return declarations have their own real source body.
- Give the private transform receiver its own `OwnerAnimationTransformView`
  name, avoiding a conflicting same-name definition with the polymorphic
  main/color renderer view.

The float and double lookup bodies have pairwise identical canonical source
payloads: sine **94 bytes**, cosine **88 bytes**, with hashes respectively
`19eae118ce85c153290d34b3a5f6dbb076329050e307a609e6d838492fc6994d`
and `5b6df9d7d1f0e57603ee537c2b68a34df31260026fc9ab29326695ea5c0c1c0d`.
Both remain **nonexact at +0** against target sizes100/94; they are existing
source hypotheses, not newly accepted helpers. Raw target suffixes load a
float table element into x87 ST0 and use RET0. These observations do not
uniquely identify the original nominal return types or compiler profile.

Each resolved image uses48 actual objects,29 physical-ABI source-view aliases,
nine attested data-only bindings and the pinned real CRT/SDK libraries. There
are no ABS executable providers, fake callbacks, copied instruction bodies,
return-value facades or target-byte patches. Private native providers remain
separate ABI views; this is not recovery of the original complete program's
nominal declarations or TU graph.

## Linked retention, hierarchy and normal CFG

The pool entry and real 66-byte counter helper are exported. The root is not.
In both images, the actual `??_7ReimuObject@@6B@` table has17 entries and +28
points to the source-owned `ReimuObject::dispatch_action_state`. Every other
entry resolves to its real provider. RTTI readback matches all eight target
type names and their PMD offsets, including CObjectBase330,
AnimationObjectBase4 and Environment130. This does not accept RTTI pointer
bytes, destructor folding, original member declarations or construction code.

| Property | Root-CIL | Ordinary native root |
| --- | ---: | ---: |
| Root VA | `801070` | `806140` |
| Vtable VA | `821C3C` | `821F7C` |
| Available root symbol span | 45,616 | 45,712 |
| Code prefix before metadata | 44,744 | 44,844 |
| Reachable instructions | 10,486 | 10,391 |
| Reachable instruction bytes | 44,736 | 44,830 |
| Guarded switches | 22 | 22 |
| Call instructions | 432 | 428 |
| Return instructions | 63 | 63 |
| First target prefix difference | +0 | +31 |
| Real counter helper | 66/66 | 66/66 |

The source switch audit validates unsigned bounds, unmodified indices/flags,
compressed index coverage, metadata ownership and every destination before
traversing normal-return control flow. Counts do not prove action semantics
or canonical matching; symbol span is not accepted authored-byte ownership.

The root-CIL entry is `PUSH EBP; MOV EBP,ESP; AND ESP,-8`, followed by the same
438h stack allocation. The ordinary root omits that alignment frame but still
fails at31, inside the primary default-branch displacement. Removing the root
export and supplying the real hierarchy therefore does not solve this byte
residual. This is not proof that all honest LTCG/original-source contexts fail.

Both linked counter bodies are fully66/66 with canonical SHA256
`ad12b782ed5fc99007456fc66a9615951cee34178850a308316409c5245bb156`.
The private ordinary root's complete canonical COFF payload is45,712 bytes,
SHA256 `85492a7eafaa3524982491875ef1eecf649c0370ee05918dcb45a0a6e6f854d0`.
It receives no acceptance.

## Public replay and next bounded lead

A fresh ordinary build of `gpt-web-reimu-object-action-state` reproduces the
public root's45,700-byte `d0ff3d32...` canonical payload and +31 mismatch, while
its accepted66-byte helper passes. The public source remains SHA256
`3b9e4896c3645bb1228db3b432a832154870c5639a80df6c02cb67ce2dba12cc`.
No private owner, lookup or compiler-profile edit is selected.

A coarse native-source instruction delta, normalizing branch destinations
and identifying metadata references by table offset, finds16 scheduling regions
between the public and private ordinary roots. Reachability associates them
with actions804,822,855,869,901,903,904 and908. This is a location diagnostic,
not semantic equivalence: it includes a changed804 velocity-value lifetime,
822 addition order, shared FSTP/store order and869 floating round trips.
The net one-instruction/twelve-byte difference hides multiple local changes.

Next inspect the actual action804 x87/velocity lifetime against the target
and current selected source, before changing root member access, declaration
or source shape. The complete-owner root still uses an existing nonconstructing
data overlay; matching RTTI and call membership alone cannot validate those
floating lifetimes. Keep the current source until a bounded target-backed
correction and its real execution/comparison evidence justify selection.

Recipes are under `.analysis/reimu-object-owner-closure-20261022/`; receipts
under `build/reimu-object-owner-closure-20261022/` retain the failed full/apply
links, both successful link commands/object hashes, `lookup-return-control.json`,
`map-provider-comparison.json`, `apply-provider-comparison.json`, both
`owner-*-inspection.json` reports, `native-root-control.json`,
`native-source-delta.json` and `public-native-replay.json`. Source/header/recipe
pins cover171 inputs. The linked-image SHA256 values are
`c394fbf679359d8a5e52c1c024c2907d987c94b16d95efc70c134df75a7e051d`
for root-CIL and
`7a859f1106cfc3edcf87057e69cd0bdd3f53a25d3a9b3193eaef14f808b01b96`
for the ordinary-root image. These private images are diagnostic and uncommitted.
