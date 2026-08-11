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

## 10. Measurement and evidence

Use the strictest truthful status:

- `matching`: fail-closed byte comparison is 100%, with command and source path recorded;
- `implemented`: semantics/layout are reconstructed and a standalone probe builds, but it is not yet included in the target build;
- `compiles`: the source is included in the target build, but exactness is blocked or measured below 100%;
- `identified`: role/signature/layout evidence exists but no faithful compiling implementation yet.

Evidence should state target size, object size, comparison result, compiler flags, and the concrete remaining mismatch. Keep semantic proof separate from byte-match proof. Update the function ledger, Ghidra name/signature, inventory, and evidence together so later agents do not repeat discovery.
