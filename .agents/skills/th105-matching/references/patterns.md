# TH105 exact-match patterns

## Contents

1. Baseline and translation-unit isolation
2. ABI and C++ symbol selection
3. Relocation-aware comparison
4. Constructors, destructors, `/GS`, and EH
5. VC8 containers and library shapes
6. Branch, register, and expression shaping
7. Floating point and x87
8. LTCG and private-ABI stop conditions
9. Comparator diagnostics
10. Measurement and evidence

## 1. Baseline and translation-unit isolation

Start from the smallest translation unit that can express the function honestly. Include the real shared declarations; do not clone a convenient but incompatible class layout. Compile and compare before tuning so the initial size and first divergence are preserved as evidence.

Check known exact functions that share any edited header. A local improvement is a regression if it changes an accepted vtable, class size, member offset, or inline accessor elsewhere.

Useful loop:

```bash
scripts/compile-unit.sh src/path/Unit.cpp build/probes/Unit.obj
python3 scripts/compare-function.py 0x00400000 build/probes/Unit.obj
```

Use a separate object path for each experiment. Keep the final evidence command reproducible from a clean tree.

## 2. ABI and C++ symbol selection

Resolve these before changing algorithms:

- calling convention and whether `this` is in `ECX`;
- stack argument order and callee cleanup;
- object size, base offset, vptr placement, and virtual order;
- exact integer width and signedness;
- return width and whether a boolean is normalized;
- ownership and destructor responsibility.

VC8 emits multiple symbols for special members. Semantic ledger names such as `Class_ctor`, `Class_dtor`, and `Class_scalar_deleting_destructor` must select `??0`, `??1`, and `??_G` respectively. Ordinary qualified aliases should resolve to their decorated member symbol, not to the first similarly named COMDAT.

Decorated ordinary members are not limited to public `Q...` access codes.
Private/protected members may begin their post-scope decoration with `A`, `I`,
or `U`; class-qualified comparator aliases must accept the full proven set.
This was required to resolve `CMenuSelect_update_player_assignment` and
`CMenuSelect_update_primary_selection` without falling back to an ambiguous
unqualified name.

When object length differs unexpectedly, inspect the COFF symbol table before reshaping source. The comparator may have selected an adjacent thunk, scalar deleting destructor, cold fragment, or helper.

An otherwise-unused `ECX` at a call site can prove member ownership even when
the callee body never reads `this`. In the TH10.5 body-collision path, callers
push three geometry arguments and load the collision context into `ECX` before
calling the 91-byte AABB transform. Declaring that transform as a
`CollisionContext` member keeps its already-exact body unchanged while also
reproducing the caller's `ECX=this` setup. Check every direct caller before
classifying such a helper as a free `__stdcall` function merely from its
callee cleanup and unused register.

For a thin virtual forwarding member, model the vtable slot and every stack
argument with a typed `__thiscall` function pointer instead of introducing a
convenient direct helper. At `0x004FC350`, keeping the null parent, related
object pointer, two floats, and five scalar arguments in the observed order
made VC8 naturally reproduce the target's x87 float stores, repeated `ESI`
push schedule, owner/manager dereferences, and indirect vslot-one call for an
exact 78/78 match. This pattern is especially useful for shared roster object
adapters because one exact wrapper can validate thousands of call sites.

## 3. Relocation-aware comparison

`REL32` calls and tail jumps can be linked in a standalone probe when the external symbol maps uniquely to a known target address. A symbol collision or unknown target is a naming/inventory problem, not a byte-tuning problem.

`DIR32` references require an exact allowlist entry in `config/reccmp-relocations.csv`. Choose validation deliberately:

- `literal`: the final four-byte value and allowed addends are known and PE bytes can be revalidated;
- `address`: a compiler-generated vtable, EH anchor, security-cookie object, or similar address is known even though raw object bytes remain relocatable;
- import/IAT: require the exact `__imp__` symbol and validate the target slot.

Typical entries include vtables, globals, floating constants, strings, EH handlers, the security cookie, and imported API slots. Never accept a broad symbol pattern or unverified addend to get past an error.

## 4. Constructors, destructors, `/GS`, and EH

Compile with `TH105_ENABLE_GS=1` only when the target has a security-cookie prologue/epilogue or compiler EH metadata consistent with it. Enabling `/GS` globally can regress small exact probes.

For a destructor, write only the explicit source-level work. Let C++ generate reverse-order member and base destruction. Recover declaration order and exact member types so these implicit calls appear naturally. Repeated vptr stores can indicate embedded polymorphic members whose destructors reset their own vtables.

Make exception specifications visible at the call site. In the exact
`CSelectScenario` destructor probe, custom source-faithful container cleanup
was 15 bytes too long until `<new>` supplied VC8's `operator delete(void *)
throw()` declaration. Without it, VC8 emitted two otherwise unnecessary EH
state stores around the inlined vector/string releases. The resulting probe
matched 271/271 bytes without manual EH manipulation.

For constructors, distinguish explicit body work from implicit base/member construction, zeroing, vptr installation, and EH unwind state. A correct object layout usually removes more mismatches than rearranging assignments.

Case pattern: `CTitle::~CTitle` proved that a source-faithful special member plus real embedded types and `/GS` can reproduce compiler-generated cleanup; it should not be rewritten as a manual sequence of destructor calls.

## 5. VC8 containers and library shapes

Use the repository's VC8 declarations, not a modern STL mental model.

- A VC8 `vector` commonly includes allocator state plus three pointers; repository layouts may therefore occupy 16 bytes rather than the modern 12-byte intuition.
- A VC8 `deque` uses a map, map size, offset, and size. Checked access can introduce repeated map/block arithmetic and library calls.
- `string`, container bounds checks, and allocator code can be inlined or reshaped by LTCG.

An explicit VC8 template instantiation can prove that an apparently authored
container helper is library code. `template class std::list<unsigned>;` emits
both `erase` overloads; selecting the fully decorated single-iterator overload
reproduces `0x00402A50` exactly at 94/94 bytes, including the hidden iterator
result, checked owner/sentinel validation, unlink/free sequence, and count
decrement. Keep the decorated overload in the evidence command because the
short name `erase` is intentionally ambiguous in the probe object.

Confirmed checked-string case: `0x004463E0` uses a 28-byte local made from a
four-byte allocator state followed by VC8's 24-byte SSO string. Its inline
`c_str()` first loads the heap-pointer union member, then overwrites the result
with the inline-buffer address when capacity is below 16. Expressing that as a
pointer initialization plus conditional assignment, rather than a ternary,
produced the target branch order and completed the 400/400-byte exact match.

Checked iterators can change both layout and calling convention. In the
scenario-select `vector<int>` cluster, an iterator is the 8-byte pair
`{ owner, current }`; range erase returns that pair through a hidden result
pointer. The resulting `__thiscall` has five stack dwords after `this`, not two
raw element pointers. Recover the callee cleanup and caller push order before
writing a convenient `clear()` facade.

An address-taking reference call can also reveal the original scalar type. If
`push_back(const int&)` receives an `int` loop counter, VC8 may home the counter
on the stack because its address escapes. A distinct but same-width source type
such as 32-bit `long` requires an `int` conversion temporary; VC8 can then keep
the induction variable in a register and pass only the temporary by address.
Use this only when target signed comparisons and the temporary store both
support the type distinction.

If the target repeats `deque::at(i)` arithmetic, caching a reference may be semantically equivalent but produce irreconcilable code. Conversely, a standalone object may repeat work that LTCG removed. Prefer the form supported by the decompilation and call structure, then classify the remaining optimizer difference honestly.

For mixed scalar/floating member calls, recover parameter order from stack
construction before trusting decompiler prototypes. In the result-menu render
path, the callee receives `(float x, float y, unsigned index)`: VC8 pushes the
integer first, then reserves eight bytes and stores the two x87 float results.
An index-first declaration preserved behavior but produced a different
three-byte-longer call sequence; the corrected declaration made the entire
267-byte caller exact.

## 6. Branch, register, and expression shaping

Change source shape only after ABI and relocations are correct.

- Match signedness first. It determines `jl`/`jb`, sign extension, high-bit tests, and unsigned max comparisons.
- Match field width. Access through an honest byte or word view can generate the target `test byte ptr` instead of a widened load.
- Preserve source order. VC8 often schedules stores, tests, and calls according to expression and statement order.
- Compare pointer/count loops, index loops, and unrolling. The target's induction variable and end condition usually reveal the likely source form.
- A local alias may inhibit common-subexpression elimination. Use it only when aliasing is valid for the real object and behavior.
- Reusing a temporary can improve or worsen register allocation. First match memory access count and branch graph; register names alone are weak evidence.

For fixed-size table clears, do not assume that a run of scalar stores came
from hand-written assignments. At `0x0045F140`, replacing eight explicit
32-bit `-1` stores and eight explicit zero stores with two source-level
`memset` calls recovered VC8's fully unrolled sequence: `EDI=-1`, copy to
`EAX`, eight stores, `XOR EAX,EAX`, then eight zero stores. It also restored
the surrounding x87 and virtual-call schedule and moved the exact prefix from
`+0x1D7` to `+0x2C8`. Use this pattern only when the destination is genuinely
contiguous and the immediate byte fill matches the target words.

Confirmed case: `0x00409AD0` (`CInputManagerEx` logical-mask builder) matched 378/378 bytes after preserving the unrolled injected-input order, caching only the initial axis/button portion of the mask, accessing later bits through a legitimate byte alias to prevent VC8 CSE, and loading the final result through that alias. The hardware branch already matched. This is a precise example of source-plausible aliasing, not a general instruction to add volatile or arbitrary casts.

Top-bit keyboard tests often match when written as `(state[key] & 0x80) != 0`; this preserves boolean semantics and can produce the observed VC8 `movzx` sequence.

## 7. Floating point and x87

On 32-bit VC8, expression grouping affects x87 load/store order, stack depth, comparisons, and rounding points. Recover float versus double fields and constants before rearranging arithmetic. Do not replace an observed `double` timing conversion with float intermediates merely because the result is close.

Confirmed collision-geometry pattern: source such as
`static_cast<int>(static_cast<float>(ceil(value)))` preserves the target's
double-argument call, explicit single-precision spill, and subsequent
`_ftol2_sse` truncation. Do not cache this result when the target repeats the
call for each coordinate. In an unrolled sign-quadrant function, also keep
width and height differences inside the individual descriptor assignments
when the target recomputes them. Hoisting those differences before the branch
made VC8 reserve a larger frame and retain different x87 values; restoring the
branch-local expressions changed `0x0045A4A0` from 1311 bytes to an exact
1386/1386 match.

For unsigned 32-bit to double conversion, VC8 may emit a high-bit correction path using a `4294967296.0` constant. Allowlist the exact constant relocation rather than changing the source to signed arithmetic.

CRT math names may select a compiler-private x87 intrinsic convention instead
of the ordinary C stack ABI. The exact `0x00406710` atan2-to-degrees helper
needed a narrow source-facing `runtime_atan2(double,double)` alias mapped to
the verified target bridge; calling `atan2` directly made VC8 pass operands on
the x87 stack instead of materializing the target's two qword arguments. A
volatile alias of the real float parameter reproduced the observed rounding
stores, while verified volatile float constants kept the target `fmul`/`fdiv`
memory operands. Use this only when the callee instructions and caller ABI
prove the ordinary double-argument bridge.

For bounded heading updates, preserve precision transitions explicitly. At
`0x004FC3A0`, rounding the negated atan2 result to the float argument slot,
then keeping the biased desired heading as `double`, then separately rounding
the desired-minus-current delta to float before `_ftol2_sse` produced the
target x87 stack schedule. Writing the final gate as
`absolute_delta <= max_step` rather than the equivalent reversed comparison
also reproduced the target operand order and unordered-value branch mask,
completing an exact 314/314 match.

In compound x87 comparisons, algebraically equivalent relational spellings can
select different unordered handling. The `0x0046C290` body-collision probe
reproduces the target's `TEST AH,41h; JE` center-order branches with negated
strict forms such as `!(left > right)` and `!(right < left)`. The latter also
changed VC8's surrounding AABB-local coloring in the full function, so retain
it only when the complete stack map improves. Its motion guards
use negated inclusive forms such as `!(left <= right)` to reproduce
`TEST AH,41h; JP`, while the opposite guard uses `!(left <= right)` with the
operands in target load order to produce `TEST AH,1; JNE`. Treat operand order,
negation, and the exact status-word mask as one unit; finite-value equivalence
does not prove matching NaN behavior.

For a vector of descriptor pointers, do not automatically cache the selected
pointer or the destination pointer-to-pointer. At `0x0045AEC0`, the mirrored
family-0 path re-evaluates checked `vector::operator[]` separately for all four
descriptor words, while the oriented family-0, family-1, and extension paths
re-dereference their destination pointer slot for each word. Writing those
assignments explicitly increased the integrated function from 1902 to 2162
bytes against a 2156-byte target and recovered the target's major branch and
reload sequence. The remaining `0x34` versus `0x3c` frame gap shows that a
near-equal size is diagnostic only: preserve the target's loop locals and
strict COMDAT boundary before claiming byte progress.

## 8. LTCG and private-ABI stop conditions

Small action-state helpers can require a shared false epilogue even when an
early return is clearer. At `0x004FC4E0`, spelling both false cases as `goto`
to one final `return 0` keeps VC8's `push esi` before the initial state branch
and reproduces the target 66/66 bytes. The analogous state-4-or-8 helper at
`0x005203B0` instead needs an outer conditional and one shared final return to
produce its 73/73-byte register lifetime. Preserve the target control-flow
merge when shrink-wrapping changes prologue placement.

For a vtable forwarding wrapper, whether the function pointer is cached can
change argument scheduling. The exact parented spawn adapter at `0x00520360`
must keep the vslot cast inline in the returned call; caching the slot hoists
its load and loses the target's late `mov eax, [edx+4]`. Its unparented sibling
at `0x004FC350` has a different faithful register schedule and does cache the
typed function pointer. Treat sibling wrappers independently.

The exact Alice target-vector helper at `0x004FC0B0` depends on repeating the
target coordinate subtractions in source. Caching `dx` or `dy` reshapes the
x87 stack and register schedule. Direct expressions reproduce both facing
branches, the two squared deltas, `__CIsqrt`, and the final 1/256 scale at
319/319 bytes after the target double literals are independently mapped.

For the exact Youmu record adapter at `0x0053CAA0`, the identifier update must
remain a chained assignment: `field_150 = record_identifier_158 = id`.
Separate stores make VC8 reload the record identifier and lose the target
175/175-byte register schedule. Preserve the shared value flow when adjacent
fields intentionally receive the same source word.

VC8 deque block selection uses the complete padded element size. The known
Youmu record fields occupy 42 bytes, but natural tail padding makes
`sizeof(YoumuObjectRecord) == 44`; explicitly instantiating
`std::deque<YoumuObjectRecord>` therefore selects one element per block and
emits the exact 94-byte mutable checked `at` specialization at `0x0053CA40`.
Select the fully decorated mutable overload when comparing an explicit-template
object, because it also contains the const overload. Its `_Xran` dependency at
`0x0053C9C0` has an instruction-identical 117-byte VC8 probe, but an unregistered
absolute EH-handler relocation keeps strict comparison fail-closed; classify
that helper as verified library code without claiming an exact match.

At `0x0053C7F0`, a natural VC8 switch reproduces the signed `movsx; sub 0;
sub 1` mode dispatch and all floating-point/payload operations, but emits 446
bytes against the 450-byte target. The target places the reverse-phase
`phase < 4` lifetime-decrement block after the motion return; VC8 standalone
source keeps it inline before motion. Record this as a cold-block placement
delta unless a source-faithful structured form reproduces the target layout.

Stop standalone-object tuning when evidence indicates that the remaining difference depends on:

- cross-function inlining or whole-program commoning;
- a private register-passed contract created by LTCG;
- eliminated container checks or constructors;
- merged constants, string pooling, or reordered cold blocks;
- EH state or helper ownership that only the linked unit establishes.

At that point preserve the faithful implementation, mark the standalone probe `implemented`, record the target/object sizes and mismatch class, and defer final acceptance to a linked executable/reccmp probe. Promote it to `compiles` only after it is included in the target build. Do not encode a private optimized calling convention into public source types without broader call-site proof.

Examples include the menu-input deque merge at `0x00409C50` and `.sfl` loop metadata loader at `0x00418520`: both have strong semantic/layout evidence but are plausible LTCG or private-ABI candidates.

## 9. Comparator diagnostics

Map the first failure to an action:

- `unknown REL32 target`: add or correct a unique known function symbol after proving its address.
- `unknown DIR32 symbol`: inspect relocation and PE target; add a narrow validation row only with proof.
- `unexpected addend`: recover the correct field/constant offset; do not widen the allowlist reflexively.
- object body too long/short: verify symbol boundaries, `/GS`, implicit special-member work, and inlining before editing control flow.
- same length, early opcode divergence: inspect ABI, signedness, field width, and statement order.
- late divergence around calls/cleanup: inspect ownership, destructor order, EH state, and calling convention.

Comparator support should stay fail-closed. Extending decorated-name resolution or a well-defined relocation category is appropriate; ignoring bytes or accepting arbitrary externals is not.

VC8 switch tables inside a function COMDAT use `DIR32` relocations both for
the table address and for its local case labels. Resolve these only when the
target symbol belongs to the same `.text` section as the function: preserve
the symbol's offset from the function entry and apply the signed addend, just
as the image linker would. This is narrower than a data allowlist and keeps
unknown external `DIR32` relocations fail-closed. The profile-menu state-six
and update probes also show that source case order controls the physical order
of tail-call blocks even when the jump-table indices remain numeric.

The same 28-byte SSO ABI may need two source views in different translation
units. A local type containing `char[16]` is a vulnerable buffer to `/GS`,
while an ABI-equivalent four-dword view is not. `CMenuSelect` needs the former
to reproduce its additional security cookie; `CProfileMenu` state six needs a
non-vulnerable return-temporary view to reproduce its single EH cookie. Keep
the persistent string type honest and use a narrowly named temporary facade
only when both layout and target prologue prove this compiler distinction.

A call that appears global in a decompile may actually be a member call. In
`CProfileMenu::render`, declaring the footer renderer as a member kept `this`
live in `ESI`, forced the guide loop to use `EDI/EBX`, and reproduced the final
`mov ecx,esi` tail jump, completing a 223-byte exact match. Check ECX setup at
the call site before tuning loop registers.

A generated scalar deleting destructor may call a source destructor that is
defined in another COMDAT section of the same COFF object. Such a `REL32`
target is local rather than undefined, but it is still safe to relocate when
its class-qualified short name has a unique address in `known-symbols.csv`.
Treat unknown local calls exactly like unknown externals and fail closed; do
not reject all section-defined call targets before attempting the proven name
mapping.

The global `CEffectSprite -> CSpriteEx -> CSpriteBase -> IColor` recovery is a
matching stop-condition fixture. Empty out-of-line endpoint destructors
reproduce `IColor::~IColor` at
`0x0041EAA0` and the derived scalar deleting destructor at `0x0041EB30`
exactly, while the 79-byte constructor differs only by the order of its derived
vptr store and EH-state store. Natural non-throwing specifications and inherited
virtual declarations do not change that order. Preserve the exact destructor
evidence and defer the constructor to a linked LTCG island rather than writing
the vptr explicitly.

For the exact `0x0045E3A0` AttackObject constructor, RTTI base offsets explain
vptr timing: `AnimationObjectBase+0x04` owns the CEffectSprite member and
`Environment` begins at `+0x130`; the primary `AnimationObject` is `0x158`
bytes. The target derived-vptr store separates base initialization from a
post-vptr state block. Representing that block as one force-inlined owned
subobject preserves the exact 193-byte schedule. Require both RTTI offsets and
the vptr boundary before using this constructor-ownership pattern.

RTTI may list a non-primary base before the primary polymorphic base even when
its physical offset is higher. `CharacterObject` constructs `CObjectBase` at
`+0x330` before `AttackObject` at `+0`; this explains its two pre-base-call
stores and yields an exact 78-byte constructor. Do not reorder base declarations
by physical address when target construction order and RTTI base order agree.

A derived object's post-primary state may likewise be a non-polymorphic second
base rather than an owned member.  In the roster pool acquire family, a member
causes standalone VC8 to install the derived vptr before initializing
`+0x34C/+0x354..+0x360`; a second base causes `CharacterObject` construction,
tail initialization, then the derived vptr store, matching both target paths.
Require the RTTI/layout offsets and both fresh/reuse instruction sequences
before applying this shape; never write a raw vptr assignment to force it.

When multiple VC8 template specializations collapse to one short COFF name,
such as two `std::vector<...>::push_back` calls, resolve an explicitly supplied
decorated symbol before the legacy short alias.  This preserves fail-closed
relocation replay without pretending distinct targets share one address.

## 10. Measurement and evidence

Use the strictest truthful status:

- `matching`: fail-closed byte comparison is 100%, with command and source path recorded;
- `implemented`: semantics/layout are reconstructed and a standalone probe builds, but it is not yet included in the target build;
- `compiles`: the source is included in the target build, but exactness is blocked or measured below 100%;
- `identified`: role/signature/layout evidence exists but no faithful compiling implementation yet.

Evidence should state target size, object size, comparison result, compiler flags, and the concrete remaining mismatch. Keep semantic proof separate from byte-match proof. Update the function ledger, Ghidra name/signature, inventory, and evidence together so later agents do not repeat discovery.
