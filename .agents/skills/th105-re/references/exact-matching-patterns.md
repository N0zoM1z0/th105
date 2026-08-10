# TH105 exact-matching pattern catalog

This is the reusable source-shaping playbook for the original Japanese TH10.5
v1.06a target. It records patterns that have already worked in this repository
and failure modes that consumed meaningful investigation time.

Use it after behavior, ABI, and layout are supported by target evidence. A
byte-identical function with the wrong inferred meaning is still bad reverse
engineering; a semantically faithful function with different bytes is not
`matching`.

## Diagnose before editing

Classify the first failure before trying source variants:

| Symptom | First route |
| --- | --- |
| Unknown external `CALL` or `JMP` | P2: `REL32` mapping and TU boundary |
| Unknown absolute data relocation | P3: strict `DIR32` mapping |
| Target size differs from the ledger body size | P4: function boundary |
| Correct logic, different conditional jump | P5: width and signedness |
| Difference begins in x87 instructions | P6: floating expression shape |
| Difference begins at prologue or stack allocation | P7/P11: locals, inlining, checked paths |
| Calls are correct but use different direct/internal relocations | P8: TU and COMDAT shape |
| Repeated target loads became one cached register | P9: lifetime and reload shaping |
| Large target is much bigger than natural source | P11: checked STL/error paths |
| A shared header edit breaks unrelated exact functions | P12: ABI regression matrix |

Always save the exact compile command, comparator command, target/object sizes,
and first mismatch. Do not begin with random rewrites.

## Repeatable loop

1. Verify the target and claim the address.
2. Confirm entry, body set, contiguous span, calling convention, stack cleanup,
   return width, direct callers, callees, globals, and vtable slots.
3. Write the smallest semantically complete source in the likely module/TU.
4. Compile with `scripts/compile-unit.sh` and run
   `scripts/compare-function.py` on one function.
5. Classify the first mismatch using the table above.
6. Change one source-shaping variable at a time. Preserve a small log of failed
   variants when a compiler choice is stubborn.
7. Once exact, rerun the command from a clean object path and record that
   reproducible command in `config/functions.csv`.
8. Recompile affected exact neighbors whenever a shared ABI declaration or TU
   changes.

The normal focused commands are:

```bash
scripts/compile-unit.sh src/battle/Unit.cpp build/probes/Unit.obj
python3 scripts/compare-function.py 0x00400000 build/probes/Unit.obj
```

Use object size and the first mismatch for non-exact work. A percentage is only
useful when produced by an accepted comparison; never estimate one visually.

## P1: Start with ABI and data layout

Source shaping cannot repair the wrong ABI. Establish these first:

- `__cdecl`, `__stdcall`, `__fastcall`, or member `__thiscall` behavior;
- `RET`, `RET 4`, `RET 8`, and other callee stack cleanup;
- whether the caller consumes `AL`, `AX`, or `EAX`;
- field offsets, field widths, signedness, and vtable slot order;
- constructor/base-pointer adjustments such as `fighter + 4` overlays;
- global pointer versus direct global object semantics.

Repository examples:

- `0x00433B90` only became a stable exact method after modeling the object as a
  `Fighter + 4` overlay and preserving assignment order.
- `0x00433CC0` required the effect vslot to return `void *` and take the fighter
  context as its final pointer argument, even though the wrapper ignores the
  return value.
- `is_y_at_or_below_stage_surface` must remain declared and defined as `int`.
  Changing only the header to `bool` broke the VC8 build despite callers often
  consuming only its low byte.

Do not infer a C++ return type solely from how one caller tests it.

## P2: External `REL32` calls and tail jumps

The comparator accepts an external `CALL rel32` or tail `JMP rel32` only when
the short COFF symbol has a unique address in `config/known-symbols.csv`.

Checklist:

1. Prove the callee address and neutral name from target evidence.
2. Add the supported symbol mapping.
3. Keep the callee external to the comparison object when the target expects a
   link-time displacement.
4. Recompile; do not patch object bytes or use a raw target address in source.

This pattern enabled the collision-list allocation leaves, `_ftol2_sse` tail
jumps, fighter phase wrappers, and `selector_random_roll`.

If the comparator reports `REL32 target is not an undefined external symbol`,
the call resolved to a definition in the same object. Use P8 rather than
weakening the comparator.

## P3: Absolute `DIR32`, literals, BSS, and addends

Absolute data relocations are intentionally fail-closed. Add a row to
`config/reccmp-relocations.csv` only after verifying:

- the exact decorated COFF symbol;
- target virtual address;
- literal bytes at the object and target location;
- every addend actually emitted by VC8.

Important variants:

- Float and double constants are different symbols and usually generate
  different x87 code. Record their exact IEEE-754 bytes.
- Pointer globals and direct global objects have different loads and decorated
  symbols.
- PE/BSS zero-filled data is allowed only with verified zero bytes.
- VC8 can emit an unsigned raw addend such as `0xfffffffc` for a signed `-4`
  displacement from a BSS array symbol. The raw value must be explicitly
  allowlisted. `scripts/compare-function.py` converts it to signed arithmetic
  only after that allowlist check and then revalidates the resolved target
  bytes.

`0x00406880` is the canonical signed-addend example. Its MT19937 indexed loops
use state-array addends `0`, `4`, `0x630`, `0x9bc`, and `0xfffffffc`.

Never add a broad wildcard, accept arbitrary BSS offsets, or skip target-byte
validation merely to make a probe pass.

## P4: Non-contiguous Ghidra bodies and alignment bytes

The ledger `size` is derived from Ghidra's function body set. Ghidra may omit
alignment NOPs or small internal ranges that still belong to the entry-to-span
machine-code region.

Use `--contiguous-span` only after disassembly proves every byte from the entry
through `span_end` belongs to the function:

```bash
python3 scripts/compare-function.py --contiguous-span \
  0x00406880 build/wave14/Mt19937.obj
```

Known examples include `0x00406880`, `0x00459C90`, `0x0046A610`, and
`0x0046A6A0`. Record both ledger body size and compared contiguous size so a
later agent does not mistake the difference for an object overrun.

Never use contiguous mode simply because the ordinary comparison fails.

## P5: Width, signedness, and branch opcode shaping

Equivalent-looking C++ often produces a different comparison width or jump.
Match what the target consumes:

- Use `signed char` when the target sign-extends a byte.
- Use `unsigned` for `JA/JAE`; signed types normally select `JG/JGE`.
- Force low-byte consumption with `static_cast<char>(call())` when the caller
  executes `TEST AL,AL` even though the callee returns an `int`.
- Preserve signed-byte list counts and sign-extend before pointer arithmetic.
- Write the same inclusive bound when immediate encoding matters.

Examples:

```cpp
// Produces CMP index, 0x7f; JA, as required by 0x00439DC0.
if (index <= 0x7f) { ... }

// Preserves TEST AL,AL in 0x00459860.
if (static_cast<char>(
        fighter->test_proposed_x_against_stage_height(delta_x)) == 0) { ... }

// The target branches on bit 0x80, not the sign of the whole flags word.
if ((flags & 0x80) != 0) { ... }
```

When only one branch opcode differs, inspect operand signedness and source
comparison direction before restructuring the whole function.

## P6: VC8 x87 expression shape

Do not algebraically simplify floating-point source. VC8 x87 code generation
depends on expression order, literal width, temporary precision, spill order,
and comparison direction.

Useful rules:

- `40.0` is a double literal; `40.0f` is a float literal. Choose from target
  loads, not preference.
- Preserve subtraction/addition form even when a direct comparison is
  mathematically equivalent.
- Preserve the order in which locals receive x87 results.
- Explicit single-precision spills may be necessary before `_ftol2_sse`.
- Repeated target conversions or loads may require repeated expressions rather
  than a cached source local.

For a branched x87 calculation with a shared multiply/convert suffix, the
temporary's source type can decide whether VC8 spills it. In `0x0046B570`, a
`float` temporary forced `FSTP/FLD` around the join, while a `double` temporary
kept the value on the x87 stack and reproduced the target's `FILD`, branch,
shared `FMUL`, and `_ftol2_sse` sequence. The target still stores the final
result as a short; the wider temporary is a code-generation fact, not evidence
that the surrounding object field is double.

The exact `0x00434390` source deliberately uses:

```cpp
if (x_ec - 40.0 <= 0.0) { ... }
if (x_ec + 40.0 >= 1280.0) { ... }
```

Replacing these with `x_ec <= 40.0f` and `x_ec >= 1240.0f` preserves ordinary
finite semantics but changes the target's x87 sequence.

For four-coordinate geometry, keep assignment and scratch order even when the
same extrema could be computed more compactly. `0x0046AD30` matched only after
the four float differences were materialized in the target's non-sequential
order before their sign words were combined.

## P7: Inlining, noinline, and statement order

VC8 makes aggressive local choices even without LTCG. Use source annotations
and statement shape narrowly:

- `__declspec(noinline)` preserves a required standalone call target.
- `__forceinline` can remove an integration-only wrapper while retaining the
  target call to its real helper.
- Assignment order can select `fldz`, `fld1`, reused x87 values, or immediate
  integer stores.
- Early returns, `do/while`, and explicit fallthrough can alter register
  lifetimes and suffix merging.

`0x00433B90` depends on the observed reset assignment order. Its callers use a
force-inlined adapter so they still emit `lea ecx,[fighter+4]` followed by the
real noinline call.

`0x00430D90` is a compact branch-layout example. Writing an early empty return
made VC8 place the `-1` suffix before the nonempty path and emitted 79 bytes.
Writing the same behavior as `if (count != 0) { ... return result; } return -1;`
placed the negative suffix at the target tail and produced the exact 78 bytes.

Do not add global compiler pragmas to fix one function. Keep shaping local and
record why it exists.

## P8: Translation-unit boundaries and COMDAT behavior

The same source produces different relocation and inlining behavior depending
on TU placement.

Common cases:

- A wrapper and callee in one TU create a defined/internal `REL32`, which the
  strict comparator rejects because it cannot assume final link placement.
- Keeping the callee in another TU produces an external relocation that can be
  resolved through `known-symbols.csv`.
- Multiple zero-filled globals in one section may turn later symbols into
  addends from the first symbol. Separate `#pragma bss_seg` sections can give
  each global a clean symbol-relative relocation.
- STL templates introduce COMDAT helper definitions such as `vector::at`
  failure paths. The main function may be semantically complete while standard
  comparison stops on an internal helper relocation.

`0x0046B420` matches in the integrated `SharedBattlePhase.cpp`; its adjacent
`0x0046B4F0` wrapper is source-complete and privately exact in a split TU, but
remains `implemented` because the durable integrated object has an internal
call to `0x0046B420`.

Use a private split-TU probe to learn source shape, but do not mark the
integrated function `matching` unless the repository's accepted command
reproduces it.

`0x00430D90` also shows why `noinline` alone is not a TU boundary. Defining its
`0x00430C30` checked-front callee in the same object produced a defined/internal
`REL32`, which the strict comparator correctly rejected. Moving the two source
bodies to `SpellDataRuntime.cpp` and `ShortDequeAccess.cpp` preserved the target
external call and allowed both functions to compare exactly.

Do not equate an object-local STL failure COMDAT with a target helper merely
because both throw the same message. At `0x0045AEC0`, the object-local
`vector<LocalAabb>::_Xran` is 106 bytes while the target failure helper at
`0x0040C140` is 123 bytes, and the anonymous-namespace hash in the decorated
COMDAT name changes with source variants. Keep such defined `REL32`
relocations fail-closed. A diagnostic may report the object section, symbol,
COMDAT status, and target-side branch, but only a proven external mapping or a
final executable-level comparison may accept it.

## P9: Register lifetimes, reloads, and volatile shaping

Once ABI, control flow, and relocations agree, remaining differences often come
from a value being cached where the target reloads it, or vice versa.

Bounded techniques:

- remove a convenience local so VC8 reloads a field;
- introduce a scoped local where the target keeps a register live;
- use a narrow `volatile` view only when instructions prove repeated loads;
- split one expression into ordered statements;
- reproduce a call between loads so the optimizer must respect aliasing;
- mirror loop form and declaration scope to influence register allocation.

`accumulate_collision_extents` uses deliberate volatile rereads. Several
nonmatching geometry functions remain smaller because natural VC8 source keeps
frame or descriptor pointers in registers while the target reloads them.

Do not scatter `volatile` through shared types. Apply it at the smallest view or
expression that explains target behavior.

## P10: Switches, tail merging, and duplicated suffixes

VC8 may merge equivalent case tails that the target keeps separate, or choose a
different switch table shape.

Try, in order:

1. Match signedness and case value type.
2. Preserve the original nesting and fallthrough direction.
3. Move repeated suffixes into or out of individual cases.
4. Use small noinline helpers only when the target actually calls one.
5. Check whether the target was LTCG-shaped before spending many local variants.

`0x0046CE20` and `0x0046C070` are current examples where semantically complete
source does not reproduce the target's unmerged suffix/branch layout. Their
ledger notes preserve the exact blocker instead of claiming completion.

## P11: Checked STL paths and large-function gaps

TH10.5 was built with VC8-era STL behavior. Large collision and fighter phases
often contain repeated checked iterator/index guards and calls to
`_invalid_parameter_noinfo` or exception helpers.

Distinguish:

- `operator[]`-style validation;
- `vector::at` and its out-of-range throw path;
- list sentinel checks before dereference and increment;
- iterator identity checks across repeated manager calls;
- allocator/count overflow helpers that are runtime/library code.

A natural range loop or cached sentinel can be semantically correct but much
smaller than the target. Preserve each observed check before tuning registers.

Current hard examples:

| Address | Integrated / target | Main shaping gap |
| --- | ---: | --- |
| `0x0045AEC0` | 2162 / 2156 | `0x34`/`0x3c` frame locals, entry `MOVZX`, `vector::at` COMDAT |
| `0x0046D160` | 527 / 525 | matched guards/frame/endpoint slots, register schedule |
| `0x0046D370` | 667 / 686 | owner identity and stack/register schedule |
| `0x0046D620` | 1398 / 1405 | matched guard count/frame, register allocation |

Wave 16 confirmed a useful checked-container shaping rule: preserve the owner
container, begin/end aliases, and end sentinel as distinct source lifetimes.
For `0x0046D160`, this raised the emitted failure calls from 15 to the target's
19. For `0x0046D620`, guarding each observed payload dereference raised the
main function from 7 to the target's 21 calls and closed 195 of the 202 missing
bytes. Match the guard sites first; only then tune stack and registers.

Two narrower shaping results are also reusable. A non-volatile aggregate with
one four-byte padding member before each of three end sentinels reproduces
`0x0046D160`'s target `0x28` frame and endpoint slots `+0x24/+0x2C/+0x34`
without changing its 527-byte body or 19 guards. Making the aggregate volatile
instead bloats the function to 551 bytes by forcing reloads. A volatile view of
only `CollisionList::count` changed `0x0046D620` from a `0x24` to the target's
`0x2C` frame while preserving its body size and all guards.

For the eight-shorts-per-block deque front at `0x00430C30`, computing only the
block index let VC8 defer `absolute & 7`, reuse `EBX`, and emit 67/71 bytes.
Introducing a named `within_block` local before the range check kept it in
`EBP`, reproduced the target push/pop set and address expression, and yielded
an exact 71/71 match. The adjacent `0x00430C80` remains the complementary hard
case: its complete natural source is 226/257 bytes because the target retains a
0x10-byte checked-iterator frame, owner-identity check, and separate owner/block
lifetimes. Do not add a standalone semantic owner guard just to mimic the dead
`CMP owner,owner`; recover the iterator source lifetime instead.

For `0x0046D370`, the two apparent owner-identity sites belong to the enclosing
checked-iterator lifetimes. Adding explicit owner checks increases the guard
count from the target's 25 to 27 and grows the function to 720 bytes; do not
model dead `cmp owner,owner` shapes as new semantic checks. Preserve owner,
begin/end, and sentinel lifetimes, then relocate existing validation paths.
Likewise, exposing `0x0046D620`'s sentinel slot did recover the target-like
`ESI=this+0x30` and `EBX=this+0x7C`, but made VC8 use `EBP` as a zero register
and shrank the function to 1382 bytes. Keep diagnostic lifetime variants out
of shared source when they improve one register but worsen the whole function.

These functions are not dead ends. Their complete source and recorded first
mismatches make them good dedicated hard lanes. Do not abandon them merely
because a short leaf would increase the progress counter faster.

## P12: Shared ABI regression matrix

Any edit to a shared header, vtable, field width, array length, calling
convention, or return type can silently change unrelated exact objects.

Before editing, list affected source files with `rg`. After editing:

1. Recompile the new function.
2. Recompile exact functions that include the changed header and touch nearby
   fields or methods.
3. Compare each affected exact address again.
4. Compile at least one source that defines every changed declaration; a return
   type mismatch may not appear in the new unit itself.

The Wave14/15 collision layout changes were checked against fighter phases,
stage gates, hit scratch, collision geometry, candidate outcomes, hit effects,
and object responses. Independent review caught the `bool`/`int` declaration
mismatch described in P1 even though the new caller still emitted exact bytes.

## Hard-function strategy

Every reconstruction wave should include at least one function whose completion
improves a central call path, layout, or orchestration contract. Small leaves
are valuable when they unblock relocations, ABI, or source shaping, not merely
because they are easy to count.

For a hard function:

1. Recover the complete semantic body first.
2. Compile it even when it is far from exact.
3. Record target size, object size, first mismatch, unresolved internal
   relocation, and the most likely shaping class.
4. Split the remaining work into bounded blocks: prologue/locals, one loop,
   one checked path, one call cascade, or one suffix.
5. Keep the function `implemented` until the accepted exact comparison passes.

This turns a monolithic reverse-engineering problem into reusable compiler-
shaping tasks without inflating progress.

## Exact-match acceptance checklist

Before changing a ledger row to `matching`, verify all of the following:

- correct original Japanese target hash;
- correct function address and comparison boundary;
- source is in the repository and compiles with the pinned toolchain;
- accepted comparator reports exact bytes;
- relocations were resolved through strict supported mappings;
- `source_file`, `owner`, `match_percent`, evidence command, and notes agree;
- relevant shared-header regressions are exact;
- `validate-tracking.py`, `progress.py --check`, and `git diff --check` pass;
- the claim is released or updated.

For non-exact functions, record this instead:

```text
Target size: ...
Object size: ...
First mismatch: target ... vs object ...
Semantic status: complete/partial
Shaping class: ABI/REL32/DIR32/x87/TU/iterator/register/LTCG
Next bounded experiment: ...
```

That handoff is more useful than a long list of untracked source variants.
