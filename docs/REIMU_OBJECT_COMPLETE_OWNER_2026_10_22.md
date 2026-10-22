# ReimuObject complete-owner context, 2026-10-22

The private complete-owner draft now compiles a genuine 17-slot ReimuObject
vtable and real pool/lifetime/root source. Twelve existing callback bodies
remain fully canonical under a coherent void-return declaration chain. The
first actual 36-object owner link fails with 16 unresolved symbols; there is
no linked root comparison from this context and no new giant-root acceptance.
The separately completed [335-byte frame provider](ANIMATION_SPRITE_FRAME_2026_10_22.md)
is accepted in commit `6a0e81a`.

## Scope and target evidence

Only the original Japanese 1.06a target is used, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The IDA preflight again rejects the open `10350095...` image. Target facts
come from hash-attested raw PE inspection and the previous
[vtable/RTTI audit](REIMU_OBJECT_VIRTUAL_SURFACE_2026_10_22.md), not IDA semantics.

That audit locates the actual ReimuObject vtable at `6C40A4`, with 17 entries
through +40, the root at +28 (`496540`), and initialization at +3C (`4A1CE0`).
AnimationObject's parent table has 15 slots, with pure callbacks at +C..+28;
AttackObject extends it to 17, with pure +28/+3C. The actual hierarchy includes
`CharacterObjectEx<Reimu,ReimuObject>` between CharacterObject and ReimuObject.
The existing root and pool construction views are partial source hypotheses.

The private draft retains the actual source pool algorithm, base construction
and ownership/destruction logic. It declares the full hierarchy and callback
surface, checks size `388` and the observed parent/children/state/phase offsets,
and compiles the existing root algorithm as a real ReimuObject virtual member.
Its data accesses use a nonconstructing overlay of the existing staging view;
the root's virtual calls use the actual complete class. No dummy callbacks,
code-address ABS bindings, assembly, copied instructions or fabricated return
values fill unresolved behavior.

## Native declaration and vtable witnesses

The existing selected sequence views use int-return forwarding declarations,
but the newly recovered `436760` ultimately tail-calls a void transform
publisher. A separate private `OwnerAnimationSequenceView` avoids changing
the public views or asserting an unobserved integer result. Its selectors,
reset, previous-frame/block, set-frame and apply-frame methods form a void
chain. The next-frame/block methods retain their observed byte results.

All ten actual bodies remain fully canonical, with the complete ledger sizes:

| Target | Bytes | Role |
| --- | ---: | --- |
| `435200`, `435220` | 22 / 27 | base action setters |
| `45C110` | 111 | apply sequence frame |
| `45C180`, `45C1A0`, `45C1F0` | 20 / 67 / 35 | set / next / previous frame |
| `45C220`, `45C2B0` | 138 / 112 | next / previous block |
| `45C390`, `45C460` | 202 / 154 | select / reset sequence |

The real derived action setters call the base setter followed by virtual
initialization, returning void. Their native bodies are likewise exact:
`45BFE0` **26/26**, `45C000` **33/33**. This establishes compatible codegen for
the private declaration hypothesis, not the original nominal return types.
The already observed one-byte void idle callback at `41F890` also compiles
to the full target C3; it receives no added acceptance.

A fresh native build of the actual private pool source emits
`??_7ReimuObject@@6B@`: 68 bytes of entries plus its 4-byte complete-object
locator. The COFF relocations have exactly the observed 17-slot topology:
the two action setters, seven sequence methods, root, four render methods,
initializer, idle and deleting destructor. Slot +28 references the real
`ReimuObject::dispatch_action_state`, not an exported stand-in. The native
slot-0 symbol is `??_EReimuObject@@UAEPAXI@Z`; no original destructor spelling
or linker-folding relationship is inferred from that generated symbol name.
This witness proves the draft's emitted layout, not equality of linked
vtable pointers, RTTI data or destructor implementation.

The private recipes are retained under
`.analysis/reimu-object-owner-cil-20261022/` (`prepare.py`,
`prepare_callbacks.py`, `compile.py`, `providers.py`, `vtable_witness.py`,
`link.py`). Serial pinned VC8 runs use CPU0 and nice10. Receipts under
`build/reimu-object-owner-cil-20261022/` include:

- `void-sequence-comparisons.json`, `finalize-comparison.json`,
  `idle-comparison.json`;
- `native-vtable-witness.json` and `vtable-witness.log`;
- actual compiler commands/tool identities in the `*-build.json` and
  `*-provider.json` files;
- `context-input-pins.json`, covering 170 current source/header/config inputs.

## Actual owner link and remaining closure

The link uses 19 hash-read-back real native inputs from the earlier resolved
root context, 13 freshly compiled real providers, the native finalize body,
and three CIL inputs for the real pool, lifetime and root: **36 objects**.
The ordinary pool entry and actual counter helper are exported; the root is
not exported. Intended retention is pool -> construction -> real vtable ->
root. The link uses the pinned real static CRT/SDK libraries, eight attested
data bindings and 25 source-view aliases with the same physical contracts.
No successful retention/map or entry-frame result is claimed before linking.

The linker reports these 16 unresolved names:

| Group | Count | Actual next dependency |
| --- | ---: | --- |
| sprite effect draws | 4 | RGB, alpha/RGB, luma, luma/alpha |
| sprite draw publisher | 1 | `CSpriteEx::finalize_render` |
| render mode / blend | 2 | real RenderModeManager bodies |
| auxiliary sprite render | 1 | `434F30`, candidate 441 bytes |
| battle sprite adapters | 2 | real background and render-manager bodies |
| quantized trigonometry | 2 | consistent float/double source-facing declarations |
| checked sequence map lookup | 1 | compiler-generated `45C320`, excluded already |
| common action 980 continuation | 1 | real accepted `596370` body |
| pool locking | 2 | real CriticalSectionWrapper enter/leave |

The compiler exit is 96 (`LNK1120`, 16 unresolved externals). There is no
`owner.dll` from this attempt. `owner-link.json`, `owner-link.log` and
`link-run.log` preserve the exact inputs, hashes, commands and diagnostics.
The existing resolved root-only image is a different context and cannot
stand in for this failed owner link.

Two render dependencies have no selected source body: auxiliary rendering
`434F30` (provisional 441 bytes), and luma/alpha rendering `6656E0`
(provisional 248 bytes). Their complete boundaries and behavior still need
independent review. Other unresolved names have existing real implementation
or compiler-identity leads; absence from this link is not evidence that their
behavior is missing from the target or unrecoverable.

The quantized lookup declarations need particular care: the selected root
and CharacterObjectRuntime use float-facing declarations, while the render
and initializer providers request double-facing declarations. Do not combine
inconsistent same-name C++ declarations or alias away an unproved return
contract merely to close the link. Existing public source and aliases remain
unchanged by this private failed attempt.

Next recover the bounded auxiliary renderer, then close the remaining real
provider graph before drawing any conclusion about the complete owner's LTCG
effect. The selected native root remains pending at its prior +31 comparison;
this failed link neither improves that result nor establishes an LTCG blocker.
