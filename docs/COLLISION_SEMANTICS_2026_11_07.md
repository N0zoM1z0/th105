# Collision intersection accumulator

This is a semantic reading of the existing TH105 1.06a collision code, not a claim about the original source names. The four integers at `CollisionContext+0x1c..0x28` are now named `overlap_left`, `overlap_top`, `overlap_right`, and `overlap_bottom`.

The target's reset at `0x46B6C0` initializes the lower bounds to -10000 and upper bounds to 10000. The integer accumulator at `0x46B3B0` raises the left bound to the maximum of the lesser X endpoints and lowers the right bound to the minimum of the greater X endpoints. It also raises the top bound and lowers the bottom bound using the two boxes' Y endpoints. `0x46B440` applies the same bounding idea to floating-point boxes, converting selected values to integers. The effect emitter at `0x46B650` uses the midpoint of these accumulated bounds, negating Y for the effect position. These uses support interpreting the fields as a running intersection in collision coordinates; they do not establish a historical type name or prove that every intermediate intersection is nonempty.

The float broad-phase function `0x46B740` subtracts endpoints and tests the resulting sign bits. This is intentionally not described as an ordinary inclusive AABB comparison: negative zero and NaN bit patterns can affect its result. Existing x87 rounding and conversion behavior remains relevant.

Four forced `volatile` reads in the integer accumulator were removed in favor of ordinary indexed reads at the same points. A fresh pinned VC8 build still matches all four selected functions in `cross-v106a-collision`, including `0x46B3B0`; the separate float accumulator and effect-center units also remain exact. The exact body of `0x46CCA0` and the four already-exact entries in the hit-geometry unit also replayed. Other collision group roots in those comparison units were already nonexact in the ledger; this change does not promote them. These checks do not assert that arbitrary concurrent mutations or unverified callers are supported.

## EFZ comparison

The independently reconstructed EFZ revision `43b64996c5f710406d8fbd2d3f974d319196784f` similarly narrows a hit intersection and uses its midpoint for an effect ([SceneBodyHit.cpp](https://github.com/N0zoM1z0/Eternal-Fighter-Zero/blob/43b64996c5f710406d8fbd2d3f974d319196784f/src/SceneBodyHit.cpp#L26-L83)). This is corroborating context, not evidence that the two games share an ABI or exact implementation. EFZ accepts integer edge contact, while TH105's float sign-bit path has different boundary and exceptional-value behavior. EFZ uses integer midpoint division; TH105 converts the summed integer bounds to float and multiplies by 0.5. Several separate hit pairs can also narrow these bounds into an inverted interval, so no validity or clamping invariant is inferred.

EFZ snapshots pose and frame data before collision; TH105's own `0x45C500` preparation similarly motivates distinguishing live animation state from prepared collision state, but does not prove identical lifecycle or ownership. EFZ's four attack/five hurt boxes do not establish TH105 array identities: TH105 preparation independently shows two five-entry groups, descriptors and a primary box. Common layouts do not alone prove common inheritance.

The shared header is pinned by the CSprite lifetime and implicit packet-cleanup origin proofs. Its updated source hash was recorded only with both existing proofs rebuilt and passing, including the CSprite owner and EH checks. No origin or exact classification changed.

## Live state and collision snapshot

The exact `0x45C500` preparation routine copies action `+0x13c`, sequence pointer `+0x15c`, state `+0x174`, result `+0x180`, result slot `+0x184`, and facing `+0x104` into a separate set of collision fields before processing boxes. The corresponding local view now names these live and snapshot roles instead of just `copied` and `prepared` offsets. The cached frame pointer guards refreshing counts and descriptor pointers when the frame changes; box coordinates are transformed on each preparation, not only on a frame change. These names describe observed roles, not a recovered original class hierarchy. Fresh complete comparisons of the 2,156-byte preparation body and its three geometry providers remain exact.

## Battle-frame collision order

The TH105 full pipeline at `0x471630` calls the action/owned-object phase, then `0x46DFF0` to prepare collision snapshots and dispatch attack/object interactions, then `0x46CCA0` for fighter body collision, followed by position/status/timer work and post-update callbacks. The BattleManager and Story views now call these two collision stages `run_attack_projectile_collision_phase` and `resolve_fighter_body_collision`; the original method names and declaring classes remain unknown. Other pipeline variants can conditionally omit the attack/object stage, so this sequence should not be treated as universal.

EFZ's [battle loop](https://github.com/N0zoM1z0/Eternal-Fighter-Zero/blob/43b64996c5f710406d8fbd2d3f974d319196784f/src/SceneBattleLoop.cpp) suggested checking this ordering, but the sequence above comes from TH105's own exact pipeline and independently reviewed callees. Fresh complete comparisons for the BattleManager virtual and Story core units remain exact after updating their relocation symbol names; no target addresses or behavior were changed.

## Fighter-phase passes

The exact `0x464630` action/owned-object phase runs five separate passes over the active-fighter vector: fighter virtual slot `+0x40`, owned-manager slot `+0x0c`, fighter action-state dispatch at `+0x28`, common character update, then owned-manager slot `+0x10`. This is not a single per-fighter loop: each pass finishes for all fighters before the next begins. Roster primary vtables and action dispatch maps support naming slot `+0x28` as action-state dispatch; the other two slots remain numbered because their full semantics have not been established here. RTTI identifies the shared fighter base as `CharacterEx`, so the local type is named as a narrow phase view rather than as a complete class. `0x464780` subsequently performs separate passes for position integration/clamping, transient status, and timer cleanup. Both complete bodies remain exact in the focused comparison.

## Typed integer collision rectangles

The integer accumulator `0x46B3B0` previously accepted pointers to four integers and addressed them by indices. Its selected source now accepts `const CollisionAabb *` and names the four coordinates, while descriptor callers construct actual rectangles instead of integer arrays and group callers pass rectangle pointers directly. This captures the layout already observed at these call sites and removes the need to treat the address of the first member as an array. It is an ABI-compatible source view of four signed 32-bit values, not a claim that the original source declared the same type. Coordinate normalization and access order remain explicit.

Five affected units were rebuilt: all eight functions already marked exact in those units still compare byte-for-byte; four other roots were already nonexact. The shared-header lifetime and generated fighter-input origin proofs also pass after the header change. The ledger signature records the new source view but its exact classification and byte counts are unchanged.

## Floating-point overlap bit interpretation

`0x46B740` intentionally combines the sign bits of four rounded floating-point endpoint differences; a conventional comparison would not preserve every signed-zero and NaN case. The source now copies each float's object representation into an unsigned integer with `memcpy`, instead of reading it through an incompatible `int *`. A compile-time size check records the required float/integer width relationship. This removes the incompatible pointer-aliasing expression while retaining the four explicit differences, their bit test and call order. Under the pinned VC8 target the complete function still compares exactly, as do the other collision-unit roots and its exact body-collision caller. A preliminary single bulk-copy form did not compile to the same body and was not retained; no claim is made that its discarded code was executed against the game.

## Integer broad-phase arithmetic

The broad phase in `0x46B7B0` subtracts four rectangle/descriptor endpoints as 32-bit machine values, ANDs the differences and tests bit 31. Its source now uses unsigned arithmetic for those four differences, making native modulo-2^32 wrapping explicit rather than relying on signed-overflow behavior. This does not replace the gate with ordinary ordered comparisons and does not change the later descriptor multiplication tests. The complete 248-byte function remains exact in the pinned build; the other already-exact entries of the same unit also compare exactly. The separate descriptor-pair root was already nonexact and is not promoted.

## Descriptor point-test arithmetic

The point test `0x46B8B0` returns -1 only when all four descriptor edge values are negative. An unsigned bit-mask rewrite of 2026-11-07 made it nonexact; the signed form is restored below.

A follow-up tried expanding each sign bit with `-static_cast<int>(q >> 31)`
before ANDing the four masks. This retains defined arithmetic but emits 150
bytes and differs from the 142-byte target at +98: VC8 uses a logical shift and
negation instead of the target's arithmetic shift. The clearer aggregate test
remains selected. The three exact peers in the unit still compared exactly;
`0x46BA10` remained nonexact.

A bounded 2026-11-08 control copied each wrapped result's representation into an
`int` with `memcpy`, then combined four `value < 0 ? -1 : 0` masks. This avoids both
a narrowing integer conversion and negative signed right shift on the pinned 32-bit
target, but VC8 emits 173/native142 bytes with its first difference at +1. The
representation change does not reproduce the target body. The selected aggregate
mask was restored and rebuilt: its 139-byte hash and both nonexact results are
unchanged, and the three accepted peers remain exact. No source or ledger change is
retained. Further mask spelling trials need new compiler or source evidence.

## Descriptor-pair broad phase, 2026-11-10

The second broad-phase gate, in `0x46BA10`, now also computes its four endpoint
expressions with unsigned 32-bit arithmetic. Raw pinned-PE instructions at
46BA38..46BA5E subtract/add the endpoints, AND the results, then use TEST/JNS.
They test the combined sign bit after modulo-2^32 arithmetic, not independent
ordered coordinate comparisons. The source no longer relies on signed overflow
for this gate. Later corner construction and narrow-phase expressions are
unchanged, so this is not a claim that all collision arithmetic is now defined
for every integer input.

A fresh complete-unit replay preserves every COFF section byte and relocation. The
248-byte single-descriptor root and the 67/110-byte accumulation helpers remain
exact. The point predicate and descriptor-pair root retain their prior nonexact
results.

A separate natural narrow-phase control used unsigned products/sums and a
four-byte memcpy to interpret their signed result. VC8 emitted four extra
stores and a larger frame, growing the otherwise exact single-descriptor root
from 248 to 260 bytes. That trial is not selected; its source and report are
retained privately. The original exact narrow phase was restored and replayed.
Resolving its remaining signed-overflow assumptions needs a source form that
preserves the complete native comparison, not forced stack or register state.

## 2026-11-14: descriptor point test exact

`test_descriptor_point_inside` at 0x46B8B0 is canonical exact, 142/142. The target
shifts each of the four edge values right by 31 (`sar`) and ANDs the masks, so the
function returns -1 when all four are negative and 0 otherwise. The previous
unsigned form, `(q0 & q1 & q2 & q3 & 0x80000000) != 0 ? -1 : 0`, lowers to one mask
and `neg`/`sbb`, which is 3 bytes shorter. Plain `int` arithmetic with
`(q0 >> 31) & (q1 >> 31) & (q2 >> 31) & (q3 >> 31)` reproduces the target.
