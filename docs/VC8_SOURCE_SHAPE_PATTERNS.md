# VC8 source-shape patterns from target residuals

Each entry names a target signature, the source shape that reproduces it and
the function where it was proven.

## Patterns that produced exact matches

**Integer comparisons can retain the written cutoff.** VC8 may emit
`x < 1` as `cmp x, 1; jge` and `x <= 0` as `cmp x, 0; jg`. A register
operand can also share its value with later instructions, as in
[Sakuya's object update](SAKUYA_OBJECT_UPDATE_2026_10_25.md#the-805-literal-groups-before-folding).
Off-by-one spellings are a large share of the residual in the giant
character functions. A greedy search fixed many at once. For each distinct
(operator, constant) pair, rewrite every matching integer field comparison to
its alternative (`< k` and `<= k-1`, `> k` and `>= k+1`), rebuild, and keep
the change only if the function's instruction diff shrinks and every other
function in the unit stays exact. It took the Alice CPU policy
0x4F4B80 from 91 to 40 differing instructions, Iku's object update 0x632C30
from 722 to 541 and Komachi's 0x5F9420 from 1064 to 949. Leave float
comparisons alone; see the next entry.

**Float comparisons: `!(a > b)` is not `a <= b`.** The two differ when a value
is NaN, and VC8 keeps the difference: after `fcomp`/`fnstsw`, a
`test ah, 41h; jp` or `test ah, 5; jp` sequence shows which ordered test the
source wrote. Komachi's action 214 0x5E3D97 needs `!(peer_x > self_x)`, Yukari's
object facing 0x593222/0x594B8F needs `dx > 0 ? 1 : -1`, and Yuyuko's action 720
guard needs an ordered `counter <= 100` test rather than an early return on
`counter > 100`. Also keep float temporaries as `float` when the target stores
and reloads them as m32 (Alice object actions 834/855, 0x502D4E/0x506CBD).

**One trailing return reached by an else-if chain, not repeated returns.** When
the target has several separate copies of a small return (`xor eax, eax; pop
ebx; ret`), including one right after the last test, write
`if (a) {...} else if (b) {...; return x;} else if (c) {...} return 0;`. VC8
duplicates the single trailing return into each predecessor. Separate
`return 0;` statements instead let the last one cross-jump into an earlier copy.
Proven on `update_profile_message` 0x43F6E0. The battle menu update 0x4407E0
needed the switch version of the same idea (cases ending in `break`).

**Switch lowering counts distinct case bodies, not distinct addresses.** VC8
decides between one jump table and a split decision tree before it merges
identical case blocks. `EffectObject::update` 0x659AA0 has 79 case values in
1..300, mapped to 62 distinct addresses. Written with shared labels
(`case 126: case 127: ...`, giving 62 bodies), VC8 splits off case 300. Each case
written separately, with duplicated bodies, gives the target's single 300-entry
table. Indexing that table through `ecx` also restores every
`mov ecx, esi` before the case calls. A greedy search shows only some groups were
duplicated in the original (126, 131, 135, 150, 151 and 162; 58, 102, 60 and 112
stay shared). This took the function from 55 regions to 24.

**Update a global in place, not through a local copy.** A global short that is
read before a branch and then updated in both arms
(`mov ax, [g]; ...; sub ax, cx` / `add ax, 1`) comes from
`g -= (flag & 1); if (g <= 0) ...` and `++g; if (g >= 499) ...`.
`short timer = g; timer = ...; g = timer;` narrows the arithmetic to 8 bits and
reloads `g` in each arm, and so does casting the flag to `unsigned char`. Proven
on `CBattleManager::update_event_timer` 0x472A70 (172 bytes).

**Late branch into the entry `return false` epilogue.** If a final test branches
back into an earlier `xor al, al; ret` while the fall-through returns true, write
one trailing `return true` reached from several paths. An adjacent
`if (x) return false; return true;` pair folds into `setne`.
Proven on `CProfileKeyConfig::capture_key_input` 0x44B540.

**Clamp with a repeated upper-bound test.** The signature is
`cmp v, hi; jg → hi; cmp v, lo; jge → (cmp v, hi; jle → v; else hi); else lo`,
with the operand re-read from memory each time. That is a macro clamp,
`max(min(v, hi), lo)`, written with the `std::min`/`std::max` comparison order. Use
`TH105_CLAMP` from `src/engine/MinMax.hpp`. The CRT `__min`/`__max` macros give `jge` instead of
`jg`, and the `std::` templates bind temporaries and grow the code.
Proven on `CMenuConfig` constructor 0x441520.

**AND of arithmetic sign masks.** Four `sar r, 31` results ANDed together come
from `(a >> 31) & (b >> 31) & ...` on `int`. An unsigned
`(a & b & ... & 0x80000000) != 0 ? -1 : 0` lowers to `neg`/`sbb` instead.
Proven on `test_descriptor_point_inside` 0x46B8B0
([note](COLLISION_SEMANTICS_2026_11_07.md)).

**Char local at the bottom of its slot.** When a single `char` whose address is
taken lives at offset 0 of a 4-byte slot, it is a by-value `char` parameter of an
inlined helper. Scalar `char` locals and `char[1]` arrays go at offset 3. Proven on
`CFileList::go_parent_directory` 0x4398B0.

**Typed fields instead of `char *` offset views.** A load hoisted above a byte
store in the target, such as a vtable load before `++state`, needs a typed member.
Access through `reinterpret_cast<unsigned char *>(this)[offset]` may alias
anything, so VC8 keeps the original order. Proven on the Arcade post pipeline
0x472F80. Offset-macro
sources such as the character input policies are candidates for the same fix.

**Offset macros, not an inline accessor template.** For typed offset fields, an
inline `template<class T> T &at(void *p, unsigned off)` hides the base from VC8's
memory disambiguation, so stores and x87 loads stay in source order. The macro
`*reinterpret_cast<T *>(reinterpret_cast<unsigned char *>(this) + off)` lets
the scheduler interleave them the way the target does (`fld [f4]; xor ebx, ebx;
fld c; mov [180], ebx; fmul ...`). It also changes which duplicate tails merge.
Switching `Reimu_initialize_action_entry` 0x491C40 to the macro cut its diff
from 25 regions to 7. The exact sibling initializers already use the macro.
The giant action-state roots use a member `__forceinline` `at<T>()` template
that behaves the same way. Switching Tenshi's (0x63D3E0) to the macro removed
about 35 diff regions out of 1637. The other eight roots measured unchanged.
With the macro, VC8 also reorders independent stores, so a case whose stores
come out permuted needs a brute-force search over statement order, not reasoning
from the target order. The search made `Suika_initialize_action_entry`
0x5AD4A0 exact: case 402 became `I(0x180)=0; B(0x184)=1; ...` and case 542
became `I(0x180)=0; B(0x17c)=2; B(0x184)=1; B(0x750)=0;`.

**A bare tail case that the target places inside another case is a
fallthrough.** In 0x491C40, case 321 (`B(0x184)=1; ...; return;`) is only
`xor ebx, ebx; jmp tail`, and the target places it at the end of case 408. Writing
`case 408: ...; case 321: ...; return;` reproduces that layout. It also freed
case 304's merge into case 302's `B(0x750)=1` join, which our separate case 321
had been taking.

**Member stores through a materialized subobject pointer.** If the target writes
an embedded object's fields through a register that holds its address, use an
inline member on that object instead of `owner.member.field = value`.
**Loop induction base.** The array referenced first inside the loop body becomes
the loop's pointer induction variable. A local such as `row = items[i]` can
move that choice. Both were proven on `CTitle::render` 0x425740.

**Post-switch `advance_frame_and_dispatch()` places the shared `fstp st(0); call advance; ret` tail in `case 9` (or a later `break` case).**
Across the 15 roster Fighter `+0x28` roots (14 on `case 9`, and Iku on `case 781`), `case 0` never owns `fstp st(0); mov ecx, esi; call 0x4351c0; ret` and `case 9` does not hoist `mov ecx, esi` above `je`. Putting `advance_frame_and_dispatch();` immediately after the `switch` and exiting `case 0, 2, 4, 5, 9` with `break;` causes `c2.dll:0x10B281E0` to place the shared `advance` block right after `case 9` *before* x87 lowering (`0x10C28970`), which inserts `fstp st(0)` at `0x47973A`, blocks `mov ecx, esi` hoisting in `case 9`, and automatically keeps `6/7/8/9/306` distinct from `208..223`. Proven on `Reimu_dispatch_action_state_vslot28` `0x00478FA0` (81,550 / 82,924 bytes) and confirmed across all 15 Fighter `+0x28` roots.

**`c2.dll:0x10B30B97` tail-merge `saved_bytes` accumulator separates `case 214` from `case 404`.**
Under `/O2`, `0x10B307E0` rejects merging a 2-byte `call eax; jmp L_ret` tail (`2 <= 20`) unless the retained branch's `[branch + 0x1c]` (`saved_bytes`, capped at 20) was already raised by an earlier >20-byte merge. An artificial shared label placed right after `case 201` raises `case 201`'s `saved_bytes` to 20 before `case 214` is scanned, pulling both `214` and `404` onto `case 201`'s label where `0x10B30D90(214)` then swaps `214` into `404`. Inlining the landing statements in `case 226` and `case 414` raises `case 201`'s `saved_bytes` *after* `case 214` and *before* `case 404`, leaving `214` on `L_ret` while pulling `404`/`414` onto `case 201`'s label. Proven on `Reimu_dispatch_action_state_vslot28` `0x00478FA0`.

**`signed char` direction parameter enables `push ebx` (`-1`) reuse.**
Declaring `spawn_owned_object_via_manager`'s direction parameter as `signed char` (matching `facing_104`) lets VC8 emit 1-byte `push ebx` (reusing prologue `or ebx, -1`) instead of 5-byte `push 0xff` in Reimu action `730` (`0x0048C37A`). Proven on `Reimu_dispatch_action_state_vslot28` `0x00478FA0` and `Iku_dispatch_action_state_vslot28` `0x00620920`.

**Early `return;` inside `__forceinline` helpers reorders `L_ret` predecessors in `c2.dll:0x10B307E0`.**
In `TailMerge`, when two matching tails both satisfy `0x10B30D90` (`CanFoldBranch`), the first predecessor on the target label's list stays inline while later ones jump into it. Moving `case 214` and `cases 400..406` out of `__forceinline` helpers that contained early `return;` statements restored the original `L_ret` predecessor order, fixing four simultaneous tail-merge swaps (`214 -> 309`, `650 -> 201`, `406/416/417 -> 404`, and `414 -> 9`) in `Iku_dispatch_action_state_vslot28` `0x00620920`.

**`c2.dll:0x10C56F50` (`WidenBranches`) widens forward branches with `disp = 116..121` via phantom alignment slack.**
VC8 starts all branches as 2-byte short (`0x1c6`/`0x1c8`) and widens them to 6-byte near (`0xf`/`0x10`) in a fixpoint loop (`0x10B24EE0`). For a forward branch whose target label has not yet been visited in the current pass, `0x10C56F75` adds the pass's cumulative widening delta (`[esp+0x1c]`) to the label's previous-pass offset, while loop 16-byte alignment (`0x10B25058`) adjusts `current_offset` without updating that delta. Earlier 1–2 byte size deltas change modulo-16 alignment padding upstream, which changes the phantom slack added to later forward spans (`603` `+121`, `740` `+119`, `797` `+116`). Restoring upstream exact sizes (here, nested `if (frame_timer_142 == 0) { if (frame_index_140 == 14) ... }` in `404`/`406` so `emit_fighter_effect_433cc0` emits `push 1`) automatically restores all three 6-byte `0F 85` encodings. Proven on `Iku_dispatch_action_state_vslot28` `0x00620920`.

**Small x87 / integer idioms proven on `Iku_dispatch_action_state_vslot28` `0x00620920`:**
- `if (cond) spawn(..., 1, ...); else spawn(..., -1, ...);` tail-merges `call 0x465190` instead of a ternary `int` local.
- `+ static_cast<float>(word_738 + 100)` emits `fiadd dword ptr [esp+0x14]` without spilling (action `780`).
- `static_cast<signed char>(1 - 2 * (static_cast<unsigned>(selector_random_roll(100)) < 50))` emits `cmp eax, 0x32; setb al; mov ecx, 1; add al, al; sub cl, al` (action `781`).
- `double step_y = field_73c; field_740 = static_cast<float>(step_y + field_740);` preserves `fld [esi+0x73c]; fadd [esi+0x740]` even when `field_740` appeared earlier in the function (action `781`).
- Calling `static_cast<unsigned>(selector_random_roll(...))` directly inside outer call arguments (not through a `__forceinline` wrapper) preserves right-to-left stack argument evaluation order (actions `602`, `781`).
- `switch (g_match_identifier) { case 1: ... case 2: ... case 3: ... }` emits the reverse-ordered `sub eax, 1; je` chain (action `730`).

**LIFO weight-sorted stack-slot packing (`esp+0x10` vs `esp+0x20`) proven on `Aya_dispatch_action_state_vslot28` `0x00602250`:**
Inspecting VC8 `/FA` listings shows `c2.dll` sorts non-address-taken stack temps and spilled locals by descending reference count and assigns them to a LIFO list of 8-byte-aligned stack slots (`-984` = `esp+0x20` first, prepending `-1000` = `esp+0x10` to the list head on the first live-range collision). Every lower-weight symbol scanned afterward hits the new head slot (`esp+0x10`). In Aya actions `720`/`721`, hoisting `float base;` before `switch (g_aya_action_match)` (13 uses -> placed in `esp+0x20`) and writing per-loop `for (float counter = 0.0f; ...)` (5 uses -> collides with `base`, prepending `esp+0x10` right between use-count 6 and 4) simultaneously resolved all 168 `esp+0x10` vs `esp+0x20` differences across 14 cases (`201`, `224`, `307`, `418`, `505..508`, `530`, `532`, `560`, `561`, `720`, `721`).

**Additional source shapes proven on `Aya_dispatch_action_state_vslot28` `0x00602250` (65,601 / 66,704 bytes):**
- Passing `aya_cosine(...) * radius * facing_104 + x_ec` and `aya_sine(...) * radius + (y_f0 + 100.0)` inline as `spawn(...)` arguments (without `double baseX`/`baseY`/`cosine` locals) prevents `mov al, [esi+0x104]` CSE across `movsx`/`movzx` and recovers all 13 `ORBIT_SPAWN` call sites (`case 740`).
- Declaring button hold counters (`0x6bc`, `0x6c0`, `0x6c4`) as `unsigned int` and testing `> 0` emits unsigned `ja`/`jbe` (`cases 525..529`, `550..553`).
- `int count; if (sbyte_608 >= 4) count = 4; if (sbyte_608 <= 3) count = 3; if (sbyte_608 <= 1) count = 2; for (int i = 0; i < count; ++i) { packet[0] = i * -20 + 20.0; ... }` emits the exact guard chain and VC8's synthesized induction variable (`sub dword ptr [esp+0x10], 0x14`) in `505..508`.
- Writing `packet[0..2]` assignments inside both `if` and `else` branches lets VC8 head-merge the common stores above `jne` (`case 606`), and keeping `float dx = ...; aya_atan(related_170->y_f0 - y_f0, dx);` in `AIM_SHORT()` preserves target `fld [esp+0x70]; fadd [esi+0xf0]` ordering in `case 529`.

**Extra checked-iterator range test after `begin()`.** A `+=` range check
directly after the `begin()` check means `begin() + n`. Look for a seek or
index helper called with 0. Proven on `CScenarioData::select_label` 0x455490, which also needed its search loop
written as `for (;;)` with the null exit first.

**`compare(0, size, ptr, 0)` means `== ""`.** An explicit compare call with
those arguments schedules differently from the inlined `std::string == ""`.
Map the `""` literal symbol in the unit's `dir32_targets`. Proven on 0x4317A0
([note](PROFILE_WRITER_CHECKED_DECK_2026_10_29.md)).

**Checked container comparisons kept under LTCG need `const_iterator`.** When
the target compares an iterator's container against a global list address on every
step, declare the loop iterators as `const_iterator`. Plain iterators let LTCG fold
those checks. Proven on 0x4194D0.
Linked units declare in-function alignment filler with `alignment_sites`.

**Compare in memory, then reload: two access paths.** A field tested directly
and then used inside an inline member of the object that contains it (or the
other way round) is not merged by VC8. The target then compares in memory and
reloads. Look for an embedded object whose inline members do the work. Proven on
0x4038D0 and 0x403840. The 0x45D040
deque rewrite showed the same effect.

**Rebuild before trusting a nonexact ledger entry.** Three functions were
already exact in their units but had never been accepted
([note](PENDING_EXACT_ACCEPTANCE_2026_11_14.md)). After a shared header change,
rebuild the units that hold nonexact functions, not just the exact ones.

**Grouped x87 stores mean a small unrolled loop.** When VC8 interleaves x87
stores with nearby integer stores but the target keeps them grouped, look for
array fields cleared in a short loop. `Yukari_reset_character_state` 0x58A470
stores its four portal floats in x/y/x/y order ahead of the counters. Four scalar
assignments in any order, chained assignment or a zero local all interleave.
`float portal_x_7ac[2], portal_y_7b4[2]` cleared by `for (portal = 0; portal < 2;
++portal)` is exact 125/125. The override also returns `int` like its slot-17
siblings, which is byte-neutral. The same holds for `import_ack_info_tail`
0x44E6D0: its two side-tail copies are `for (side = 0; side < 2; ++side)` over
`NetworkStateRecord4C::sides_008`, now a real `NetworkStateSide20[2]`. The
scalar copies scheduled the second store after the `leave` receiver load.

**A cap written as `__min` re-evaluates its operand.** `adjust_capped_counter_558`
0x45CED0 recomputes `counter_558 + amount` on the in-range path, with the merged
amount in EAX. The CRT macro `__min(counter_558 + amount, 500)` from `<stdlib.h>`
is exact. A named `capped` local, with an `if` or a ternary, lands the amount in
EDX, and `TH105_MIN` gives `jle` for `jl`.

**Texture handles are a 4-byte class, and the release has two overloads.**
`TitleResourceManager::release_title_resource_handle` 0x404D70 serves both
`release(unsigned)` and `release(DesignTextureHandle)`. The bodies are
identical, so the linker folds them into one function.

The evidence:
- All 81 target call sites push the value directly.
- With a class-only parameter, `unsigned` arguments build a temporary in place
  and regress about 30 callers. The background vectors provably stay
  `vector<unsigned>`: class-typed vectors break the BG constructors through the
  shared scalar `_Assign_n` 0x40C2E0.
- With class-typed handle fields and the class overload, the parked
  in-memory handle tests become exact: `Character_dtor` 0x462CE0 (905),
  `GuideOverlay::~GuideOverlay` 0x43F330, `ProfileEditor168::update_selection`
  0x427C60 (dead `push ecx` included), `ProfileMenuBaseData::cleanup` 0x431390,
  and `FighterCutinLifetime` 0x465420.

What changed:
- `TextureHandleResult` is now an alias of `DesignTextureHandle`.
- `release_texture` takes `DesignTextureHandle &`.
- `ConnectTextureHandle` is unified into `DesignTextureHandle`.
- About twenty handle fields and four profile globals are
  `DesignTextureHandle`, with the globals renamed in `reccmp-relocations.csv`.

`NetworkResultFinalize`'s view of `texture_278` stays `unsigned`: its
virtual `CSprite::set_texture(unsigned, ...)` call schedules differently with
a class argument. A matched impacted-unit replay (811 results) shows no
regressions.

**The virtual sprite setters take the handle class too.**
`CSprite::set_texture` and `set_texture_options` take `DesignTextureHandle`.
`CProfileDeckEdit::show_record` 0x448B40 tests `card_texture_handle_44` in
memory and reloads it for the call; that is exact once the record field is the
class (0x45DC90 as well). Two of the callers needed a change in the same pass:
- `CSelect` character binding 0x41FB80 loads the handle into its member
  before passing it;
- the spell CSV parser 0x4343A0 needs a plain `SpellRecordView` local (the
  members zero themselves) and a handle copy, not `.value`.

**The texture binder takes a `DesignTextureHandle` by value.** Its call sites
show the parameter's type:
- on-device-lost 0x401610 builds the argument in place (`push 0; push ecx;
  mov eax, esp; mov [eax], 0`), which is `bind_texture(0, 0)` through the
  converting constructor;
- the line and rectangle primitives push a zeroed register twice, which is
  `bind_texture(DesignTextureHandle(), 0)`;
- the render tail and textured-primitive callers push the stored value, so
  their handles are `DesignTextureHandle` objects.

With `TitleResourceManager::bind_texture(DesignTextureHandle, int)`, a
`DesignTextureHandle` parameter for `submit_textured_primitive`,
`SecondaryAnimationRender::texture_handle_20` and `BattleObjectManager`'s two
handles, `draw_line` 0x401180 and `on_device_lost` 0x401610 are exact. 0x401130,
0x4666A0 and 0x4302A0 stay exact.

`BattleObjectManager`'s constructor 0x4678F0 lost exact credit: its old match
relied on `unsigned` members contradicted by the render tail. With class
members it is 279/279, nonexact only on the EH-state scheduling seen elsewhere
(the target keeps the two zero stores after `state = 5`). Assigning the members
in the body, initializer-list forms, an anonymous-struct grouping and a
vertex constructor all fail. The binder 0x404DF0 itself is still nonexact.

`CSprite::render_rectangle` 0x4070C0 binds a copy of its handle: the target
loads `value_04` only after the vertex stores. Passing `value_04` directly lets
VC8 hoist the load. `DesignTextureHandle texture = value_04;
bind_texture(texture, 0);` is exact, as is a by-value getter. The same local
makes `CSpriteEx::finalize_render` 0x407AD0 exact (219/219; its new unit is
`exact-first-sprite-ex-finalize-render`). A
reference-taking vertex helper is not.

**Statement order picks the association of a commutative sum.** In
`draw_font_glyph` 0x411B80 the target computes `ascent - origin.y + cursor_y +
height` from `ascent` onward. With `bottom` computed first, VC8 reassociates
it to start from the `cursor_y` it already loaded. Operand order and
parentheses inside the expression are canonicalized away. Computing `right`
before `bottom`, two independent statements, is exact 624/624.

**A copy-through local can rotate registers.** `CNetworkClient::import_snapshot`
0x44F200 was 399/399 with AL and CL swapped through the rest of the body. The
source loaded `packet->sequence_03c` into an `unsigned char` local, cleared two
pacing values, then stored the local. Storing `sequence_6b8 =
packet->sequence_03c` first, then clearing the values, is exact. Dropping the
local alone or chaining the clears is not.

**A late store into a shared slot means a fresh, non-escaped local.**
`parse_scenario_event_row` 0x45A7A0 reuses one stack slot for two values. The
first value's address goes to `ShortDeque8::push_back`; the second goes to
`std::list<int>::push_back`, and the target stores it only after loading the
list head. Reusing one variable (formerly an int/short union) makes VC8 store
it early, because the escaped address may alias the list nodes. A fresh `int`
would take a new slot (frame +4). Exact 543/543: give the selected column value
its own block scope, then declare `int source_value` after the block.

**Clear a released handle through a reference.** When the target stores
`handle = 0` before loading an unrelated field of the same object, VC8 has not
reordered them, so the store went through a pointer. The inline member
`TitleResourceManager::release_texture(unsigned &handle)` (release, then clear)
makes `refresh_character_preview` 0x4484F0 and `refresh_selected_character`
0x447080 exact. The spelled-out pair lets VC8 hoist the next load above the
store. The helper is byte-neutral in the exact 0x4245D0. It moves
`ProfileEditor168::update_selection` 0x427C60 to 332/333: its first guarded
release now compares in memory and reloads as the target does, but the second
still loads into EAX, and the dead `push ecx` slot remains. The guarded 29-byte
`ProfileMenuBaseData::cleanup` 0x431390 is unchanged.

**Dereference a lookup result at the call.** `CSprite::render` 0x406BE0 and
`render_fvf4142` 0x406E50 bind their texture through
`void **texture = lookup_token(handle); device->SetTexture(0, *texture);`.
Dereferencing into a `void *` local first loads the COM slot into EAX instead
of ECX, 610/610 nonexact at +541. Passing the lookup inline loads the device
before the lookup. The same spelling is byte-neutral in `CTile::render`
0x4099F0, whose only residual is a dead 4-byte frame slot.

**Same-shape LTCG trial for `release_all_tracked`.** The three 122-byte list
releases (0x46EEB0, 0x56DA90; 0x436E60 is similar) differ only in EAX/EDX for the
handle token. Six source spellings change nothing. A manual `/GL` build with
`release_handle` visible gives that callee a private EAX `this` ABI, which the
target lacks, so LTCG does not explain the register.

- **Literal map keys reuse a dead parameter slot.**
  `Fighter_try_dispatch_front_word_actions_690_696` 0x494450 stores the second
  and later `find` keys into its own parameter's stack slot, once the parameter
  lives in EBX. That only happens when `find(691)` takes a literal, so the key
  is an unnamed temporary. A named `command_key` or a reassigned parameter gets
  its own slot or forces an extra register copy. The same function needed its
  150..157 range test written against the field (`action_id_13c >= 150 &&
  action_id_13c <= 157`). Through a `short` local, VC8 folds the test into
  `lea; cmp; ja` instead of the target's two signed compares.

- **Duplicate-body merging stops for a branching `ACTION` body after a plain
  pair.** VC8 merges `if (a) S; if (b) S;` with identical `S` into `a`, `S`,
  then `b` jumping back into `S`. In `Marisa_dispatch_input_policy` 0x4B9FA0
  the target does this for the 308, 402 and 412 pairs. A 412 body written as
  `if (S(0x7A6) > 0) ACTION(431); ACTION(412);` (two macro returns) stops
  merging once an earlier plain `ACTION` pair has merged; the `||` and `goto`
  forms lay out `a`, `b`, `S` instead. Writing the body as `if (...)
  set_action(431); else set_action(412);` followed by one reset and `return`
  emits identical code (VC8 duplicates the tail) and still merges. A minimal
  repro is a plain `ACTION` pair followed by the branching pair; a `__forceinline`
  helper behaves like the macro.

- **`fimul` needs a float literal.** `CProfileDeckEdit_render` 0x448F60 computes
  `16.0f * row + y` with `fimul dword [row]`. `16.0 * row` (a double literal)
  emits `fild; fmulp`, and its register pressure also flipped a later inlined
  deque `[+0x10] + [+0xc]` operand order. One literal fixed both. Before
  treating a commutative deque sum as an LTCG residual, check nearby x87
  expressions for literal types.

- **A duplicated GS epilogue can mean a missing branch `return`.** In the
  replay browser 0x446860 the target jumps from every path to one epilogue
  that loads `mov al, 1`. With a single trailing `return 1;`, VC8 kept 1 in
  BL (it was also the `== 1` compare operand) and duplicated the epilogue on
  three paths. Adding `return 1;` at the end of the first `if` arm of the
  `if / else if` chain, while keeping the trailing return, gave the shared
  epilogue.

- **Repeated `cmp eax, ebx` on one loaded value means the source re-read the
  member.** `CSelect::update` 0x421430 tests the same input pointer once per
  cursor, with no jump threading between the tests. Writing each publication as
  `if (inputs_010[i]) cursor.input_counter = &inputs_010[i]->counters[n]; else
  ... = 0;` gives that shape, because the reload is folded only after VC8 has
  threaded jumps. A static helper taking the pointer by value threads the tests
  together; a ternary or a per-cursor helper is worse. The same function also
  needed its assignment flags read as `fields_7f8[n]` bytes rather than through
  a struct pointer view, which moved an `add esp, 4` back next to its call.

- **A branch that jumps back into the other branch's tail can come from duplicated
  source.** When the target lays out `if (a) { A; T } else { B; jmp T }`, with
  `B` placed after `T`, the source repeats the tail statements `T` in both
  branches and VC8 cross-jumps them. A shared tail after the `if/else` puts
  `B` inline instead. This made the scenario list fade 0x455850 exact, where
  `T` is the colour publication plus `++it`. The battle menu update 0x4407E0
  needed the same thing: its auto-save branch repeats the outer
  `end_pending_84` stores and `return true`, so the session check jumps into
  that copy and the message branch follows it.
  Komachi's initializer 0x5F6700 needed it for two cases that differ in one
  float constant: the second case repeats the whole body, with its first two
  stores swapped, and VC8 cross-jumps it after `fld1`. A `goto` into the first
  case's body lays the stub out before the shared code. Youmu's initializer
  `0x0053A1D0` also needs distinct copies. The state clear comes first
  in both publishing cases and the reset-only cases follow them. The first
  successful late comparison supplies a saved length to the second.
  [Youmu case note](YOUMU_FIGHTER_ACTION_INITIALIZATION_2026_10_25.md#case-order-preserves-both-tail-merges)

- **Write sibling cases' branches in the same direction.** The common fighter
  initializer 0x477830 has cases 6, 7 and 8 that either call `set_action` or
  run the stop tail that conditionally calls `zero_motion()` and clears
  `acceleration_y_100`.
  Cases 7 and 8 test the `set_action` condition first. Case 6 was written with
  the stop tail inside nested negated tests. Its block was then identical to
  case 7's and became the shared retarget for the bare returns, so VC8 could
  not schedule `pop edi` into it. Writing case 6 like its siblings, as
  `if (set) { set_action(208); return; }` followed by the stop tail, made the
  4849-byte function exact. Cases 150–166 keep the store order for
  `field_730`, horizontal velocity, vertical velocity, and `phase_state_180`.
  Direct accesses to the typed `skill_levels_624` array preserve the complete
  match, including the three jump tables.

- **A "remote chunk" reached only by `jmp` after an epilogue is a tail call.**
  The scene frame update 0x43B4A0 pops its registers and jumps to 0x4400D0,
  which ledgers recorded as a remote chunk. It is a separate `void` function
  with its own returns. VC8 emits a call to it at the end of the caller as
  `pop ...; jmp`. Check other `function-byte-ownership.toml` chunks for this
  shape: a chunk with its own `ret`, no use of the caller's saved registers,
  and a location among unrelated functions.

- **A hoisted field local can change zero-register placement.** In
  `CSelect::on_scene_enter` 0x421120 the search loop compares
  `setup_00c->sides_08[side].character_key_00` directly. A named `character`
  local before the loop added a `jmp`, moved `xor ebx, ebx` out of both arms
  of an earlier select and changed the setup register. Before reordering
  statements, try removing locals that only cache a field.

- **`cmp [mem], reg; je; mov r, [mem]` comes from a reference parameter.** The
  watch-input setup 0x42BC40 tests a token pointer in memory and reloads it
  in the branch. A small inline helper taking the token as
  `SetupTokenInput *&` reproduces this; a direct field test or a reference
  local loads it once into a register. Pass any other destination the helper
  writes (here a tag byte) by reference too: a struct pointer or reference
  parameter hoists its address computation above the branch.

- **Keep a fade helper's frame test separate from the next frame read.**
  InfoEffectObject update `0x0065CB40` compares the signed frame in memory
  above the alpha subtraction and loads it again before the motion check.
  Inlining just the fade with the frame, alpha and lifecycle state passed
  by reference preserves both reads. Direct member tests share one register
  value. The same root recovers the low retirement tail by moving the case 10
  return below case 100 in source. VC8 then offers the case 10 copy first
  during its late tail comparison. The emit calls retain their positions.
  [Info effect update](INFO_EFFECT_UPDATE_2026_10_27.md#the-retirement-order-and-frame-references-that-match)

- **`mov ecx, [global]; ...; mov edi, ecx` is an inlined member's `this`.**
  In the round reset 0x471180 the target loads the phase-block global into
  ECX, derives addresses from it and copies it to EDI for later member calls.
  A local pointer gets EDI directly. Wrapping the statements in a small inline
  member called on the global reproduces the copy. The same function needed
  `dst = src` (`list::operator=`) rather than a hand-written self-check and
  `assign`; `operator=` uses the `_Const_iterator` `_Assign` instantiation,
  which needs its own rel32 mapping.

## Parked residuals (tried, still nonexact)

- **Menu cursor update 0x41FA20 `idiv` by 6 (2026-11-14).** The target computes
  `input % 6` as `mov edi, 6; cdq; idiv edi` inside otherwise `/O2` code.
  - These do not reproduce it: `/O1` or `/Os` (`push 6; pop edi` and `inc eax`),
    builds without `/Og` (unoptimized frame), and a manual LTCG link with the
    divisor as a never-written global from another TU (LTCG propagates it and
    then uses a magic multiply).
  - Confirmed in a scratch LTCG link: `bool MenuCursorState::update(int period)`
    using `input % period`, linked `/LTCG` with callers that pass 6, emits the
    target's `mov edi, 6; cdq; idiv edi` and a `this`-only ABI.
  - Computing the new selection into a local and then assigning
    `selection = next;` before the window checks matches the rest, except one
    `lea` operand order (`[esi+eax-1]` vs ours `[eax+esi-1]`) that no expression
    order changes.
  - The target has 35 call sites across the menu TUs, so a linked unit must
    contain them. Several of those callers are themselves one-to-three-region
    near misses and may be LTCG effects too.
  - The angle lookups' `idiv` by 3600 (0x406360/0x4063D0) is likely the same
    parameter propagation.
- **Background set_transition 0x4654F0 and Fighter sequence advance 0x45D040.**
  The first swaps the stack slots of two compiler temporaries: the inline
  `fnstcw` control word and the spilled element-offset counter. Alpha cast forms
  and loop declaration styles did not change it. In the second, the target uses
  immediate zeros in the inline `deque::pop_front`, and ours keeps zero in `ecx`.
  `empty()` and `!= 0` forms and LTCG did not change it.

- **Scenario character install 0x456EB0 initial EH state (2026-11-14).** After
  writing `entry.value_0bc = 480 + y;` before the colour bytes, only one store
  differs. The target sets the EH state to 0 before the `ScenarioTextEntryDC`
  constructor call; ours sets 1. Both unwind maps are identical (0 = `text`,
  1 = `name`, 2 = entry, 3 and 4 = the pair temporaries). So the target treats
  the by-value `name` parameter as not yet live at that call. Moving the entry
  declaration, dropping the `s` alias and using a named pair local did not
  change it.

- **Compiler settings ruled out for the merge and scheduling residuals
  (2026-11-14).** These left the residuals of Reimu 0x491C40, Komachi 0x5F6700,
  the CSV reader 0x40F580 and Udonge 0x5D0E60 unchanged:
  - VC8 RTM instead of SP1;
  - a manual `/GL` + `/LTCG` link;
  - `/Z7`;
  - adding another large function to the same TU.

  `/fp:fast` and `/fp:strict` are much worse. `/O1` and `/Os` turn the ack
  packet constructor's (0x44DAC0) zero store into `and [esi+4], 0` rather than
  the target's `xor eax, eax; mov [esi+4], eax`. Treat these residuals as
  source-structure questions.

- **One-region near misses checked on 2026-11-14.**
  - `CsvReader::next_string` 0x40F580: the target merges its two
    `return out = "";` blocks into the later copy, placed right after the second
    test. Separate `if`s, `||`, `else if`, nested and early-return forms all keep
    the earlier copy, or move the shared block to the end.
  - Network client pacing 0x44EAD0: `[+0x88] + [+0x84]` follows neither source
    operand order nor declaration order. Only swapping the if/else that
    increments the two counters flips it, and that breaks the layout.
  - Yukari event bridge 0x5983B0 case 156 ends with an extra `cmp ax, ax; jne`.
    `short const action = state_13c; return action == 794 && sequence_13e != 1
    && action == 794;` reproduces everything except that compare.
  - Object responses 0x46C930 loads `candidate_output_2a` with `movzx`, while
    the general hit resolver's identical store uses `mov ax`. `short`, `int` and
    local-variable conversions do not change it.
  - The animation, fighter and select transforms (0x435360, 0x435740,
    0x45E6E0, 0x41FAD0) differ only in where `push edi` or `lea edi, [esi+4]`
    sits relative to the first `fild`. Pivot declaration order, constness and a
    sprite reference do not move it.

- **Udonge action entry 0x5D0E60 (2026-11-14).** The target is one plain switch
  in case order: the `jg 0x12d / jge 0x12c` and `0x230/0x231` splits are VC8's
  own decomposition. The old `if (action <= 301)` partition and its gotos were
  replaced by ordinary cases. That, Reimu's 71/73 statement order and full bodies
  for 408/409 and 726 took the diff from 27 regions to 7. Changing only the
  integer-store order leaves the wrong EDI restore and the jump from 650
  into 404/406's tail. The 2026-11-23 match moves the first x87 operation
  before the last flag store in 404/406. Both arms then restore EDI after
  the initial x87 store and keep their own scaling code.
  [Udonge scaling tails](UDONGE_ACTION_ENTRY_2026_10_24.md#ordering-the-horizontal-multiply-in-cases-404-and-406)

- **Reimu action initialization 0x491C40 cross-jumps.** The November 14
  baseline had two cross-jump differences.
  - Cases 404 and 414 share the tail `fmul st(1), st(0); mov [180], ebx; ...;
    jmp`. In the target, 404 jumps forward into 414's copy; ours makes 414 jump
    back into 404's.
  - Case 322's `if (B(0x47e) == 0) zero_motion();` uses a near `jne` straight
    into case 305's `mov [738], bx; jmp` tail. The call path keeps its own copy.
    Ours branches to its local join. The address-normalized diff hides this, so
    compare instruction lengths too.

  A manual `/GL` + `/LTCG` link with out-of-line callee stubs gives the same two
  residuals. That source keeps the 404 copy. Moving 404 after 414 changes
  the merge direction and the switch layout. Small sub-switches sometimes
  merge the target's way (for example,
  only 400/404/408/321/414 without the `default:` tail call). Removing any one or
  two of the large cases 76, 78, 89, 609, 610, 696 or 760 does not. The following
  made no difference: every order of the five 404 statements, the 414 store order,
  `0.25f`, chained versus separate zero stores, label order inside a group,
  splitting 404/406, 414/416 or 410/412 into separate cases, cast spellings and
  loop spellings. The target also has fallthroughs 307→306 and 710–740→797,
  which are now written that way (neutral). The next lead is some other
  difference in earlier IR size (helpers inlined in the original, for example)
  rather than in these cases.

  The exact build retains distinct case 322 reset arms and puts the first
  flag reset reachable from 404/406 and 414/416 after the switch. This keeps
  the two lowered x87 tails separate until the late join pass, which now
  keeps 414's copy. Expanding the shared reset to action 400 changes the
  layout. See the [whole-function trace](REIMU_ACTION_INITIALIZATION_2026_10_25.md#shared-reset-after-the-switch).

- **Background runtime 0x466F40 zero register (2026-11-14).** The target
  computes `effect_level_f8 + effect_level_delta_fc` once, so an `int const level`
  local is right; the current source repeats the sum. With that local, VC8
  keeps 0 in EDI and tail-merges the three `effect_level_delta_fc = 0; push 16`
  branch tails. The target uses immediate stores, keeps each tail separate up to
  the shared call, and pushes EDI later. A single trailing call taking a
  `pattern` local gives the target size (1074) but still uses EDI. A mini TU
  shows the same merging under `/O2` and LTCG, so link mode is not the cause.

- **`interpolate_scene_byte` 0x4501B0 register roles (2026-11-14).** The target
  keeps `entry->start_04` in EDI for both subtractions and reuses EBX for the
  `current` pointer and `base`. The current source reloads `start_04`
  (214 bytes). A named `unsigned const start` in the interpolation branch gives
  211 bytes with identical instructions, but `entry` and `start` swap ESI/EDI.
  Declaring `start` at function scope gets the roles right but hoists its load
  above the `elapsed >= end` test. Neither a reference nor an assignment inside
  the condition keeps both.

- **Marisa CPU policy 0x4B4070: `goto policy_dispatch` hides a helper boundary
  (2026-11-14, not committed).** The target merges the four `approach` bodies
  into the first site, with the later sites jumping back. That is the
  duplicate-merge shape for bodies ending in `return`, not `goto`. Moving the
  `if (S(0x766)==0)` proposal block into a separate member function
  (`goto policy_dispatch` becomes `return`, each approach site gets its own
  body), forced inline at its single call site, fixes those first two residual
  regions. LTCG would inline such a single-caller function the same way.
  What remains is in the dispatch switch. The target keeps separate full tails
  for `DURATION(0x11,20,..)` and `DURATION(0x10,20,..)`, which ours tail-merges,
  and two block placements follow from that. The probe uses `__forceinline` only
  to emulate that inlining, so it was not kept.


- **Checked-deque bound operand order.** `GameConfig_save` 0x427390 (2 bytes) and
  the filtered spell CSV parser 0x433B30 (2 bytes) swap `[_Myoff]` and `[_Mysize]`
  in one `_Myoff + _Mysize` sum. Neutral: passing `c_str()` directly to `write`,
  `begin()[i]`, `(begin() + i)->`, `data()`, three equivalent forms of the length
  cap, and `size_t` or `size_type` loop indices. The `<` and `int` index forms
  break earlier code.
  The same unexplained commutative-operand swap appears in
  `CNetworkClient_advance_frame` 0x44EAD0 (`[+0x88] + [+0x84]`; both source
  orders and a split `=`/`+=` are neutral), `PlayerSlotRecord_load_profile`
  0x431AC0 (deque `[+0xC] + [+0x10]`) and `ScoreData_load_42f6f0` 0x42F6F0
  (`[eax + ecx]` addressing). An open lead is LTCG code generation: these
  units compile with plain `/O2`. A linked trial needs real callee definitions,
  which LTCG would inline where the target keeps the call.
  `Fighter_load_pat_data_and_palette_resources` 0x461B70 (exact to +866 of 3885)
  has the same residual in an inlined `back()`, and `Character_dtor` 0x462CE0 a
  related SIB operand swap. Probe results:
  - inlined VC8 deque derefs are emitted size-first;
  - the out-of-line `back()` instantiation is off-first, like the target;
  - the PAT loader's surrounding code matches the target instruction for
    instruction.

  So the choice comes from outside the function. One trial TU combined the PAT
  loader with the neighbouring `Character` constructor and destructor sources (in
  address order). It changes neither function, so that partial TU composition does
  not explain it.

  **LTCG explains the `back()` case.** In a minimal probe built with `/GL` and
  `/LTCG`, the inlined `deque::back()` deref is emitted off-first
  (`mov edx, [q+off]; add edx, [q+size]`), exactly as in the target. The same
  probe under plain `/O2` is size-first. Under LTCG the inlinee keeps its
  out-of-line operand order. `operator[]` stays size-first under LTCG too, so the
  `GameConfig_save` and spell-parser cases need another explanation. The PAT
  loader therefore needs a linked LTCG unit. That is blocked on missing real
  definitions: `PatFileReaderOwner` construction, destruction and `open`, and
  `PatPaletteService::load_palette`, are views with no source body yet. The other
  dependencies (`PatRecord88`, `FrameData`, `load_texture`,
  `character_key_to_name`, globals and `wsprintfA`) exist.

  **Integration attempt (2026-11-14, reverted).** The PAT source was moved onto
  the real `FileReaderOwner` and `PaletteDecodeMode`; the palette call matches the
  exact `CSelect` form on `&g_bootstrap_mode` with `select_palette_6fa258`. A
  combined linked source (`ScriptFileLoading.cpp`, `PatRecordLifetime.cpp`,
  `TitleResourceLoad.cpp`, `ScenarioEventNameResolver.cpp`, then the PAT loader)
  compiles cleanly. Linking still needs three data globals (title resource
  manager, scenario event name map, `select_palette_6fa258`) and three functions
  that `TitleResourceLoad.cpp` reaches only through views:
  `TitleResourceAcquireView::acquire` (native private-EDI 0x405090), the shared
  release 0x405200 and `TextureLoader_load_bitmap_to_resource_cell`. These views
  must be replaced by real definitions first.

  The target calls the trivial `FileReaderOwner` constructor 0x40CF10 out of line
  at only seven sites, including this 3885-byte loader, and inlines it everywhere
  else. That fits LTCG's per-caller inlining budget running out in very large
  callers. A real linked build of the loader should therefore make the same choice,
  but plain `/O2` with the header's inline constructor cannot.
- **Clash resolver tail merging.** `resolve_group_b_object_clash` 0x46CA80 is
  557 bytes against 542. The target merges the equal case into the final
  `8/8` block with the result in EAX, and stores slot-first only there. All 24
  store orders for those two blocks, an inline `set_clash_result` helper (521 and
  534 bytes) and an `if/else` single-exit form (557 bytes, now the selected
  source) fail.
- **`movzx` + `movsx cx` for a deferred health amount.** `BattleCollisionPhase_run`
  0x46DFF0 is exact to +1369. Inline helpers taking `short` or `int`, a `short`
  local, and `unsigned` field types all keep the folded `movsx r32, word`.
- **Two-value switch lowered to a select.** In `CBattleSV_update` 0x426180 and
  `CBattleCL_update` 0x426380 the target branches into a shared `return 8`
  epilogue. Putting `default` first or using an `if` return does not reproduce it.
  In 0x426380 the target keeps the final `default: return 14` as its own
  epilogue, while VC8 jumps into the earlier `flush(); return 14;` tail. A
  result variable, `break` forms, an inverted outer `if` and an
  `if (phase != 1) return 14;` early return all keep the jump.
- **List erase register rotation.** The three `update_and_prune` members
  (0x58BE10, 0x422D30, 0x456D70) differ only in the EAX/ECX/EDX names of the
  inlined `list::erase` unlink. `erase(it++)` and a separate dead iterator both
  remove the 12-byte frame's iterator temporary and break the prologue.
- **Dead 4-byte stack slot (`push ecx` / `pop ecx`).** Seen in
  `TitleResourceManager::bind_texture` 0x404DF0 and the UDP send-thread entry
  0x416D90. A local texture pointer is neutral. The same function loads the device
  vtable into EBP before the lookup call. No source shape reproduced either.
  `CNumber::initialize` 0x414E40 shows the same slot. Rewriting `int glyph_width =
  right - left` as `right -= left` moves its int-to-float conversion into the
  `right` parameter slot as in the target, so the dead `push ecx` is now its only
  difference (102 against 104 bytes).
- **Selected-scenario transition tails.** `CSelectScenario_update_selection`
  0x4248A0: in the target the `+1` arm owns the shared stores and epilogue and
  the `-1` arm jumps into them. Swapping the arms only flips the condition. A
  hoisted common tail (400 bytes), an early-return arm (437) and a ternary (406)
  are all worse.
- **Handle test in memory, then reload.** `GuideOverlay` destructor 0x43F330,
  `FighterSpriteResource_cleanup` 0x465420 and `ProfileMenuBaseData_cleanup`
  0x431390 emit `cmp [obj+h], 0`, then the EH state store, then reload the handle
  for the release call. Ours loads it once and reuses the register. Typing the
  GuideOverlay handle as `DesignTextureHandle` is neutral. No accepted exact
  function contains this sequence. On the 29-byte `ProfileMenuBaseData_cleanup`,
  these are all neutral:
  - an `int` test with an `unsigned` argument;
  - a `const unsigned &` inline wrapper;
  - an unsigned `> 0` test;
  - a `void *` view with a cast argument;
  - a real LTCG link with the release function kept public (28 bytes, same as `/O2`).

  Without preserving the public release ABI, LTCG passes the handle in EBX
  (24 bytes). So LTCG does not explain this cluster. The same pattern also
  appears in 0x42BC40, 0x448B40 and 0x45DC90.
- **Register-preference residuals.** `Fighter_initialize_battle_state` 0x460200
  uses CL where ours uses AL for the `state_55b` copy; reading the pointer value
  instead of a `char` view is neutral. `BattlePhaseBlock_parse_scenario_event_row`
  0x45A7A0 sinks the `push_back` value store; passing `next_int()` directly
  breaks the shared stack slot.
- **Dead `movzx` before the `movsx` of a 16-bit value.** In
  `CollisionContext_apply_forwarded_quantity_to_pair` 0x46C5B0, the target
  zero-extends AX (dead) and then sign-extends it for the health sum. The deferred
  health amount in 0x46DFF0 has the same pair. Neutral: an `unsigned short` local,
  a double cast, an `int` holding the `unsigned short` result, and an inline
  helper returning `short`.
- **EH state store sunk past the first load after a lock guard.** In four
  functions (0x404330, 0x415340, 0x415B90, 0x417800) the target stores EH state 0
  straight after `call [EnterCriticalSection]`. VC8 sinks it below the next
  `this` load and test. A reference-holding guard, or a guard calling
  `CriticalSectionWrapper::enter/leave`, changes nothing. `/EHs` changes
  nothing either. `/EHa` keeps the store in place, but it adds `-1` state stores
  before each destructor that the target lacks, so the profile is not `/EHa`.
  The same placement explains the offset-0 handle tests in
  `FighterSpriteResource_cleanup` 0x465420 and `ProfileMenuBaseData::cleanup`
  0x431390. The target compares `[esi]` in memory, stores state 0, and then
  reloads. VC8 loads, tests and stores the state afterwards. `release_texture`
  splits the paths only when the handle is not at offset 0. `/Ox`, `/Oy-` and
  the spelled-out `/O2` components do not help.
- **Commutative sum order in `advance_frame` 0x44EAD0.** The target loads +0x88
  before adding +0x84. The operand order in source, `+=`, a local, an `int` type,
  a two-element array and a manual LTCG build all emit +0x84 first.
- **Unmerged `return 0` epilogues.** `ConnectDigitEditor::update_port` 0x441BD0
  (and 0x441E10, 0x43F6E0, 0x443030) keeps every `xor eax, eax; pop; ret`
  separate, and lays out the final `return 0` as the fall-through of the
  `cancel == 1 || is_menu_initial_press(...)` test. VC8 jumps back to an earlier
  identical epilogue instead. This also happens under a manual LTCG build. An
  `&&`/`!` early return and an `else` arm are neutral; a result variable changes
  the layout (565 bytes).
- **Stack slot order in `EventEffectState_initialize_resources` 0x46A260.** The
  target places the CSV reader below the texture path buffer; VC8 places them
  in declaration order. Hoisting `path` or `width`/`height`, a block around the
  reader, and declaring `row` before `key` all fail.
- **No PGO in the target.** Its Rich header lists `Utc1400_LTCG_CPP` (0x72,
  42 records) and no POGO product IDs. The unmerged epilogues and block order
  are not profile-guided layout.
- **`update_and_prune` erase rotation, more trials.** For 0x422D30, both
  `erase(it++)` and swapping the `state_158` test arms make it worse.
- **Callee-save placement in `draw_rect` 0x4012A0.** The target pushes EDI
  before the `filled` test, though only the outline branch uses it; VC8 saves
  EDI inside that branch (394/395). Filled-first order, an `else` arm and
  `filled == 0` are neutral; `#pragma optimize("y", off)` is far worse.
- **`consume_spell_sequence_entry` 0x45D230.** The target loads `value_1e`
  into AX and stores it to +0x176 after setting up the next call; VC8 uses CX and
  stores at once. Inlining the record pointer and swapping the final flag
  stores are neutral.
- **`release_all_tracked` EAX/EDX, fourth member.** The system-effect release
  0x436E60 has the same single difference (EDX for the handle token). A range
  `erase(begin(), end())` becomes an out-of-line call, and a `std::list &`
  local shrinks the body to 101 bytes.
- **`CGage::render` 0x41B3F0 case 1.** The `fraction * height` product still
  loads `height` first. Removing the `const float &height` binding regresses to
  +346, swapping the factors is neutral, and computing `top` earlier regresses.
- **`CsvReader::next_string` 0x40F580 return layout.** The target places the
  row-end `return out = ""` block last and keeps the field-end one inline.
  Nesting the field test under `row_it_14 != rows_00.end()` fixes the first
  block, but VC8 then merges the two empty returns (249/245). An `else` arm, a
  doubly nested form, swapped `==` operands and `!(... != ...)` all fail.
- **Binder 0x404DF0 device reads.** In the lookup branch the target loads the
  device's vtable before `lookup_token` and reloads the device for `this`.
  Calling through an explicit vtable slot does not reproduce it, because VC8
  still evaluates the slot after the arguments.
- **LTCG `this` in ESI.** `PackageFileIndexNode_ctor` 0x41B7F0 receives `this`
  in ESI and returns it from there. Only a linked unit can match it.
- **RTM compiler control.** Building 0x431390, 0x427390, 0x46C5B0 and 0x414E40
  with the local VC8 RTM toolchain (`TH105_MSVC8_ROOT=.tools/msvc80-rtm`) fixes
  none of these residuals, and it makes GameConfig_save worse (+233). The SP1
  pin stays.
- **8-byte-aligned frames (`push ebp; mov ebp, esp; and esp, -8`).**
  `InputStateTableStorage::add_tracked_key` 0x40A6C0 and `WaveService_load_wave`
  0x401AF0 align their frames although neither has a visible 8-byte local. The
  first one was compiled with each of these added to `/O2`:
  - `/Z7`: no change;
  - `/arch:SSE`, `/arch:SSE2`, `/Ox`, `/fp:fast`, `/G7`: no change;
  - `/Oy-`: matches the EBP frame setup but not the alignment;
  - `/Zi`: still fails under Wine with C1902.

  `operator[]` instead of `at()` is worse (153 bytes).

  **The cause is LTCG.** A trial `vc8-sp1-ltcg-o2` linked build of the unchanged
  `InputStateTableUpdate.cpp` reproduces the target prologue exactly (`push ebp;
  mov ebp, esp; and esp, -8; sub esp, 0xc`) and the whole lookup loop. The existing
  linked audio-scheduler unit also reproduces the aligned prologue of 0x419400.
  What still differs is that the target calls `vector<unsigned char>::insert`
  0x40A7F0 out of line with a private EAX receiver, while the small LTCG context
  inlines it. 0x40A7F0 has no other caller in the executable, so the inlining
  difference has another cause. These four functions need a linked unit, not
  `/O2` source changes. For the dead `push ecx` slot, a linked LTCG build of
  `bind_texture` with the real `TextureHandleRuntime.cpp` lookup still emits 102
  bytes without the slot, so LTCG alone does not explain that pattern.
- **`CsvReader_advance_row` register roles.** 0x40F680 swaps ESI and EDI between
  `this` and `&row_it_14`. A local `CsvRows::iterator &` reference moves the first
  mismatch to +15, and `rows_00.end() == row_it_14` to +22 (163 bytes, against 167).
  Neither matches.
- **Aligned-frame chain through `linear_gain_to_ds_volume` 0x418990.** The callee
  runs on a 64-byte-aligned frame (`and esp, -64; sub esp, 0x40`) and stores and
  reloads its float log10 result through `[esp+0x3c]` twice. Its LTCG caller
  `WaveService_load_wave` 0x401AF0 has an 8-byte-aligned EBP frame and spills the
  gain product into a local. The existing linked unit instead emits `push ecx`
  and reuses the dead `path` parameter slot, with the rest nearly identical. Lead:
  recover the callee's real aligned local and float casts first, then rebuild its
  callers in one LTCG context. Adding invented alignment is not acceptable.
  The same aligned prologue (`push ebp; mov ebp, esp; and esp, -8; push ecx`) is
  now the only residual of `WaveService_set_handle_gain` 0x401CE0: its linked body
  otherwise matches instruction for instruction, including the compare-then-reload
  through `buffer->set_volume`. It also blocks `BgmStream_transition_gain`
  0x402B70, which now reproduces the reload through the inline buffer
  `set_volume`. Probably more of the linear-gain callers are affected, so solving
  0x418990 is the highest-value open audio item.
- **Sequence pop as a real `std::deque`.** `Fighter_advance_fighter_sequence_55c`
  0x45D040 pops a `std::deque<FighterSequenceSlot>`: `front()` (its two range
  checks), then `pop_front()`, whose element destructor resets only the `CSprite`
  member's vptr non-virtually. The old hand-written pop called the `CSprite`
  destructor virtually. With the real deque, read through a `sequence_queue(this)`
  helper, the first 18 instructions now match (190 bytes against 198). The
  remaining difference is that ours keeps zero in ECX for the offset resets and the
  first `entry_at_checked(0)` push.
- **Battle setup slot load: payload LEA base/index order.**
  `BattleInputGate_load_battle_setup_slot` 0x42BAF0 is exact to +146, where the
  target forms the payload address as `[offset + selected + 8]` and ours as
  `[selected + offset + 8]`. The target really does test the token mask twice
  (a `neg`/`sbb` select inside the taken branch). Neutral: swapping the `&`
  operands and putting the offset first in the sum. Worse: `>> side & 1` (337
  bytes) and the typed `payload_08[side]` (334).
- **The 64-byte-frame island looks globally unoptimized.** The quantized angle
  lookups 0x406360/0x4063D0 share 0x418990's `and esp, -64; sub esp, 0x40`
  frame and float store/reload chain. They also compute `index % 3600` with
  `cdq; mov ecx, 0xe10; idiv ecx`. At `/O2`, with or without `/GL`, VC8 always
  turns that into a magic multiply, even when 3600 comes from an extern const
  or a never-written global in another `/GL` object. The `idiv` appears only
  with global optimization off: `/O1`, `/Od`, or `#pragma optimize("g", off)`.
  - `/Od /Ob1` with the C++ `fabs(float)` overload (`magnitude =
    fabs(magnitude)`, no `#pragma function`) reproduces the call shape, the
    inlined overload's store/reload, and the `idiv` epilogue.
  - Two differences remain under `/Od /Ob1`: the target's frame is
    64-byte-aligned and uses ESP-based locals, and the target does not spill
    `index` to the stack.
  - `/fp:fast` reproduces the target's single-precision constants (`fmul
    dword`); `/fp:precise` emits `qword`.
  - `#pragma optimize("", off)` inside a `/GL` file stops the overload from
    inlining.
  So the island is probably a separately built object, or a region with
  different optimization settings. The flags that produce the 64-byte
  alignment are still unknown.
- **0x418990 call shape, 2026-11-14.** The target's `sub esp, 8; fstp qword
  [esp]; call _log10` is the non-intrinsic double `log10` call. `/Oi-` or
  `#pragma function(log10)` reproduces it, with or without `/GL`; the default
  intrinsic emits `call _CIlog10` instead. With the C++ float overload and
  extern constants, the scale order `fld units; fmul scale; fmul [gain]`
  also matches. No combination of `/GL`, `/fp:precise`, `/arch:SSE`/`SSE2` or
  `#pragma fenv_access(on)` (which stops `log10f` inlining) produced the
  `and esp, -64` frame. The intrinsic setting is therefore a second unexplained
  property of this island, alongside the frame.
- **0x418990 frame is reproduced; two float round-trips remain (2026-11-14).**
  The current `exact-first-bgm-stream-runtime` LTCG build of the existing source
  (`static_cast<float>(log10(static_cast<double>(gain)))` under the file's
  `#pragma function(log10)`) already emits `push ebp; mov ebp, esp; and esp, -64;
  sub esp, 0x40`, the `_log10` call and the float store at `[esp+0x3c]`. It is
  87 bytes against 103. The only difference is that the target follows that
  store with `fld; fstp [esp+0x3c]` twice before the scale multiply. That matches
  the CRT chain `log10(float)` -> `log10f` -> `(float)log10((double)x)` with a
  non-intrinsic inner call. Trials:
  - `log10(gain)` (C++ overload): inner call becomes `_CIlog10`, because the
    pragma does not reach `math.h`'s inline bodies; no frame.
  - same with `/Oi-`, or with `#pragma function(log10)` declared before any
    include: `_log10`, one round-trip, the value lives in the parameter slot,
    no aligned frame (81 bytes).
  - `double logarithm = log10(gain); float g = static_cast<float>(logarithm);`
    with `/Oi-`: aligned frame and one round-trip, matching to +39 (95 bytes).
  - `/fp:strict` switches to `__ftol2_sse_excpt`; `/fp:fast` (67) and `/Ob1`
    (81) are worse; `#pragma optimize("g", off)` deoptimizes the whole body.
- **Out-of-line tiny helpers under LTCG follow the callee module's `/Ob`.**
  A manual two-TU LTCG link shows a helper defined in an `/Ob1` module stays out
  of line at every call site and gets a private register argument; defined in
  an `/Ob2` module it is inlined everywhere, even into an `/Ob1` caller module.
  For `report_direct_input_error` 0x40D540, building the mouse unit with `/Ob1`
  makes `initialize_mouse_device` 0x40D810 identical except one instruction:
  LTCG propagates the single call site's constant message into the helper, so
  the 5-byte `mov eax, message` disappears. With a second, different-message
  caller the helper bytes match the target exactly (`mov ecx, window; ...; push
  eax; push ecx; call MessageBoxA`). The target has no second call site, so what
  blocks the constant propagation is still unknown. Routing all nine sibling
  error sites through the helper under default `/Ob2` inlines all of them.
- **Audio initializer flag composition (2026-11-14).** `initialize_audio`
  0x418670 builds the primary-buffer flags with `add ecx, 9` after the
  `neg/sbb/and` select, so the source is `9 + (listener ? 16 : 0)`, not `9 | ...`.
  With that change its mnemonic sequence differs only by the stack load of
  `flags`. The remaining residual is the private ABI: the target passes `window`
  in ECX and `flags` on the stack (RET 4, one extra 4-byte local), while plain
  `/O2` puts `flags` in ECX and `window` in EDI. The root 0x407DA0 also carries
  an LTCG-style `and esp, -8` frame, so this cluster needs one linked context.

## Pinned C2 x87 liveness investigation (2026-11-26)

The fixed SP1 `c2.dll` has SHA-256
`497d1ffe57f75db8b458167bdea475f3962829e139b355a2672a4ef51c716413`.
Its [Microsoft public PDB](https://msdl.microsoft.com/download/symbols/c2.pdb/8E3C6AD714BE4E55B528B0DBEB3BABD81/c2.pdb)
has SHA-256 `5895796d070abb17862735845eff3a4d30d19248c461bc199a32d05629fb48d8`.
The GUID matches `8e3c6ad7-14be-4e55-b528-b0dbeb3babd8`. The PE and PDB DBI
ages are one; the PDB Info age is two. All section RVAs agree and there is no
OMAP. Four section headers match byte-for-byte; `.rsrc` differs only in virtual
size, 1,008 versus 1,408 bytes. The public names provide external corroboration
for these addresses; the instruction observations below use the pinned DLL.

| Address | Public name | Relevant operation |
| --- | --- | --- |
| `10C28970` | `LoFinalLower` | Final instruction lowering |
| `10C2EB00` | `X87MapGFxToSTx` | Calls liveness construction, lifetime marking and stack mapping |
| `10C2EFB0` | `BuildLiveOnEntryAndExitSets` | Computes block masks to a fixed point |
| `10C32630` | `SetGFxLifeAndDeath` | Marks operand lifetime boundaries |
| `10C2EC80` | `AppendFldZeroToBlock` | Builds a zero load for a required stack entry |
| `10C33550` | `FPColor` | Floating register allocation |
| `10C34C20` | `FPSpillWorthless` | Removes unprotected regions with non-positive cost |
| `10C33F00` | `TryToReverseFCOMP` | Can reverse a comparison and its conditional branch |
| `10C38E40` | `CanExtendLifetime` | Checks whether a lifetime can cross intervening instructions |

Raw instructions at `10C2F330..10C2F357` OR linked blocks' `+B4` masks into
`+124`, then compute `+B4 = (+124 & ~+38) | +34`. This is the standard backward
liveness equation: the outgoing set is the union of successor incoming sets.
`10C2EC80` constructs a zero operand using the object at `10D188A0`, corroborated
by the public name `Flzero`. An unused-looking zero/pop sequence therefore
needs its predecessor constraints and register lifetime reviewed before choosing
a source explanation.

GDB hardware breakpoints through WineDbg's `--gdb --no-start` proxy provide
working execution control without modifying code or data. Root-name conditions
distinguish the dispatcher from earlier inline-helper compilations. (Note:
WineDbg commands issued at its DLL-load stop are unreliable; also, GDB's Python
`Breakpoint.stop()` callback can fire even when `.condition` is false, so filter
inside the callback before logging.)

Under this profile (`/O2 /GS- /GR /EHsc /MT`), module flags `+44C = 0805C100`
at `10B0D0BF` route floating-point intervals through general `Color`
(`10B0CF40`, register class 1) rather than `FPColor` / `FPSpillWorthless`.
Follow general `Spillcosts` (`10B10420`, subtract sites `10B10957`/`10B10F85`,
add sites `10B109C5`/`10B11007`), `SpillObvious` (`10B11560`) and
`SpillOrDefer` (`10B0D690`).

**Resolution (Patchouli `0x0050F200`, 54,452/55,610 canonical exact):**
On the pre-exact Patchouli candidate, the prefix `0.0f` interval had 16
`Enterload` deductions (`-2` each) and 16 use credits (`+2` each), leaving
spill cost `0` so general `Color` discarded it before `X87MapGFxToSTx`.
Separating the two `if (sequence_index_13e == 2)` checks in cases `201` and
`224` (instead of nesting the velocity update inside the `landing()` guard)
allowed the prefix `0.0f` live range to flow across the false edge into both
cases, adding two `+2` net intervals (`+4` total) so general `Color` kept
`0.0f` in `st(0)` across the switch. Writing `case 209:`, `case 212:` and
`case 221:` as separate switch cases also matched VC8's 17-iteration
`FgDoLateFlowOpts` (`0x10B2C950`) merge order, merging `209`/`212`/`221` while
leaving `210` and `222` distinct.

**Nested `if` vs flat `&&` reorders merge predecessors in `InsertAdditionalSplits`.**
When a long-lived constant (`imm == 1`) loses its last free register across a
switch dispatch header, VC8's `InsertAdditionalSplits` (`0x10B15D50`) greedily
groups blocks into regions in layout order by scanning each block's predecessor
list for the first compatible region. If a case starts with non-call guards
followed by a call guard, flat `if (a && b && call())` places the non-call
guard edges (which still belong to the switch header's near-saturated region)
ahead of the call block's fresh region in the merge block's predecessor list,
pulling the merge block back into the switch header's region and severing the
case's local constant interval. Nesting `if (a) { if (b) { if (call()) ... } }`
reorders the merge block's predecessors so the call block's region comes first,
keeping the post-guard constant uses in one region. Proven on Yuyuko `0x0055D850`
cases `502`/`503`/`507`/`508` (`mov ebx, 1`) and `512`/`513` (`mov edi, 1`),
closing the 58,619/59,672-byte root to 109/109 canonical exact
([note](YUYUKO_ACTION_STATE_2026_10_28.md)). Confirmed on Komachi `0x005E20E0`
case `405`: nesting `if (sequence_index_13e < 2) { if (crossed()) { ... return;
} }` restored the local `mov ebx, 1` hoist at `+0x47FB`, closing the
63,993/65,176-byte root to 107/107 canonical exact
([note](KOMACHI_ACTION_STATE_2026_10_28.md)).

**Avoid intermediate `double` locals in x87 trig rings when VC8 LICM spills
`jitter + 180.0`.** In Komachi `0x005E20E0` case `730`, writing `double angle =
n * 45.0 + base_angle; packet[0] = static_cast<float>(angle + jitter + 180.0);`
caused VC8 LICM to hoist `jitter + 180.0` into an 8-byte `qword` frame spill
(expanding the frame from `0x490` to `0x498`), whereas writing `coord =
static_cast<float>(n * 45.0 + base_angle); packet[0] = static_cast<float>(n *
45.0 + base_angle + jitter + 180.0);` kept `n * 45.0 + base_angle` in x87
`st(0)` (`fst; fadd; fadd`) with no `qword` spill. Hoisting `float coord;`
before `switch (g_match_identifier)` with per-loop `for (float n = 0.0f; ...)`
simultaneously restored LIFO stack-slot packing (`esp+0x10` vs `esp+0x28`)
across 15 owners.

**Global constant priority (`CONST(0) -> EBP` vs `CONST(1) -> EBX`) in
`c2.dll:0x10B14E2A` (Yukari `0x0057B030`, 57,042/58,248 canonical exact):**
When high-priority local constants (`CONST(6) -> EBP`, `CONST(4) -> EBX`) split
both `CONST(0)` and `CONST(1)` in general `Color` (`0x10B0CF40`), the post-split
priority scores computed by `0x10B14E2A` decide which constant claims `EBP`
versus `EBX` across the entire dispatcher.
- Writing `case 2:` and `case 1:` separately in a difficulty switch (`action 720`,
  before `TailMerge` merges them) gave `CONST(70)` `score = 1` (`lea ebp,
  [eax+0xa]`), shifting `CONST(0)`'s post-split priority deficit against
  `CONST(1)` from 93 points down to 6 (`-1458` vs `-1452`).
- Unnesting repeated `!frame_timer_142` frame guards into sequential
  `if (!frame_timer_142 && frame_index_140 == ...)` checks added `+8` priority
  to `CONST(0)` with zero extra code bytes, flipping `CONST(0)` ahead of
  `CONST(1)` so `0 -> EBP` and `1 -> EBX` across all 122 owners.
- Writing `for (int i = 0; i < count; ++i)` instead of `do { ... } while (--count)`
  in `burst910` scheduled `word_738 = 1` before loop-counter setup; splitting
  `if (entry(1))` and `if (entry(2))` in `action 404` restored its shared
  `0x57F6B5` `set_action_and_finalize(9)` tail.

**Float loop limits, prelude rounding and subobject dispatch (Udonge
`0x005BFD50`, Suika `0x00598990`, Remilia `0x00545090`):**
- In Udonge's `word_174 > 0` prelude, writing `float scale = field_7a8; float
  alpha = scale * word_7a6; byte_113 = static_cast<unsigned char>(alpha);`
  simultaneously reproduces `fld [esi+0x7a8]; fild; fmulp` at entry, `fld
  [esi+0x7b0]; fadd [esi+0x73c]` in `expand_cone`, and `fld [esi+0x73c]; fadd
  [esi+0x740]` in `565..568`.
- In Suika `525`/`526`, writing `float limit = static_cast<float>(byte_609 +
  5.0); float m = 0.0f; double count = limit; if (0.0 < limit) do { ... } while
  (m < count);` keeps `double count` at `[esp+0x18..0x1f]` (stabilizing global
  stack slots) and schedules `fstp dword ptr [esp+0x20]` at the exact target
  slot.
- In Remilia, calling `0x00435160` (`oriented_components`) through a `+0x04`
  subobject emits `lea ecx, [esi+4]`, calling `0x0045C030` through `owner_168`
  in `607`/`710` emits `mov ecx, [esi+0x168]`, and `double step = field_73c *
  90.0;` in `710` mode 1 preserves the target x87 schedule and `0x4f0` frame.

**`TailMerge` 20-byte threshold (`c2.dll:0x10B30B74`) and `Color` `G_owner`/`G_act`
priority (`c2.dll:0x10B104B0..0x10B114EA`) in `AliceObject` `0x004FCAB0`
(63,218/63,248 nonexact checkpoint, 2026-11-28):**
- Under `/O2`, `TryTailMerge` (`0x10B307E0..0x10B30B76`) sums exact instruction
  sizes via `0x10C21010` and merges whenever the matching suffix exceeds 20 bytes
  (`cmp ebp, 20; jg`). `TuplesEqual` (`0x10B29EDD`) and `SingleOperandEqual`
  (`0x10BF7012` -> `0x10BF7B50`) reject merging if operand types differ (`I1` vs
  `U1`), even when the lowered x86 bytes (`mov al, 0xf6; add [esi+0x111], al;
  add [esi+0x110], al`) are identical.
- In `AliceObject` `case 849` `c1..3` and `c19..20`, `G_owner` (`[esi+0x348]`)
  and `G_act` (`[owner+0x13c]`) differ by `prio(G_owner) - prio(G_act) = +2` and
  `+3`, respectively (`6*N_15 - 3*N_1 - 3*N_3 - sum(N_4..N_14)` with `W_B = 1`).
  Spilled rematerializable constants live-in to `Block 1` (such as `CONST(150)`
  in a `848..998` sub-switch) raise `N_1` by 1 and drop the gap by `-3` in both
  arms with zero emitted instructions, though the full 800..999 dispatcher still
  leaves those 26 bytes swapped under VC8 SP1, RTM, and `/GL` + `/LTCG`.
  See [AliceObject update note](ALICE_OBJECT_UPDATE_2026_10_28.md).

**`char *` aliasing, `TryTailMerge` host polarity, and `0x10B321E8` `0x64` cap
in `AyaObject` `0x0061A290` (18/34 exact owners, 28/34 `+0` owners, 2026-11-28):**
- Accessing BGRA color channels through `reinterpret_cast<unsigned char *>(this)[0x113]`
  acts as a `char *` aliasing barrier on `this` in VC8, blocking CSE of
  `sequence_index_13e` into `cx` across `801`/`807`/`820`/`821`/`853`/`854` and
  preventing `mov al, [esi+0x113]` from scheduling ahead of `fstp [esi+0x120]`
  in `903`. Switching to typed `AnimationSpriteState::color_b_10c..color_a_10f`
  and reading `sequence_index_13e` directly (without `short const sequence`,
  which triggers unwanted jump-threading) closed those owners immediately.
- Declaring `emit_fighter_effect_433cc0` (`0x00435240`) with `unsigned char
  direction` emits `movzx edx, [esi+0x104]; neg dl; push edx` without extra
  zero-extension (`850`/`851`), and avoiding `static_cast<double>` on
  `object_x_0e8` in `851` recovers `fisub dword ptr [esp+0x24]`.
- In `903` `case 2/3/8`, flipping `if (color_a_10f < 20) { --lifetime; return; }`
  to `if (color_a_10f >= 20) { ... } else { --lifetime; return; }` makes `case 2`
  host the shared `sub al, 0x14` tail so `case 3` and `case 8` tail-merge into
  `case 2`. In `851`, a single `if (sequence_index_13e == 1)` stops `mov ecx,
  esi` from hoisting above `jle 0x61a41d`, which simultaneously prevents `903
  case 7`'s `next_sequence_block(); return;` from merging into `851`.
- Pre-regalloc `TryTailMerge` (`c2.dll:0x10B321E0`) checks
  `cmp dword ptr [eax+0x3b], 0x64; jg` (`0x10B321E8`), skipping any label with
  `> 100` references. In `AyaObject`, `actions:861` cleanly cascades all 196
  bytes into `actions:826` (`0x61c27e` + `0x61c2a7`) in the 12-case subset
  `800..817 + 826 + 861`, but remains unmerged (`+196 B`) in the full 34-case
  switch once `820`'s `sequence 4/6` block (`aya_stage_surface_height_at_x` +
  `double object_y`) or `821` is present.
  See [Aya evidence](AYA_EVIDENCE.md) and
  [Playbook Section 7](GIANT_ACTION_ROOT_PLAYBOOK.md#7-roster-object-0x28-update-roots-reusable-workflow--lessons).

**Roster CPU `+0x58` policy exact pattern (`Alice_update_cpu_action_policy`
`0x004F4B80`, 16,354/17,009 canonical exact, 2026-11-28):**
- Standalone `/O2 /GS- /GR /EHsc /MT` matches the full 17,009-byte root without
  `/LTCG` once synthetic `goto` labels are replaced by natural C++ control flow:
  - Removing `float aim_x` and `goto air_against_ground`/`air_aim`/`air_tail`
    in favor of ordinary `if (PEER(0xF0) == 0.0f) { ... } else { ... }` with
    inline `atan2_degrees` restores the prologue's `[esp+0x10]` temp slot and
    native air-branch tail merges.
  - Inlining the `S(0x766) = 100; S(0x768) = roll(20) + 10;` body instead of
    `goto approach_policy;` lets `TailMerge` emit `jne; jmp` at the first site.
  - Removing `goto expire_policy`/`wait60`/`check214` and using per-case `break;`
    in `switch (S(0x766))` cases `1..100` prevents `case 0`'s seven
    `DURATION(..., 30, 0)` arms from over-merging into `WAIT(30)` while merging
    `case 3..8`, `9`, `10`, and `100` cleanly into `case 11..18`'s expire tail.
  - In `case 200`, writing `if (S(0x764) < 50) break;` inside the facing guard
    (rather than `&& S(0x764) >= 50`) both emits `cmp word, 0x32; jl` and keeps
    the `switch (S(0x13C))` break label above `c2.dll`'s 100-reference
    `TryTailMerge` cap so cases `300..416` do not over-merge.
  - See [Alice CPU note](ALICE_CPU_TARGET_2026_10_24.md).

**Remaining four Fighter CPU `+0x58` roots (Marisa `0x004B4070`, Reimu
`0x0048D390`, Default `0x005F1F80`, Aya `0x006126E0` — all 5/5 exact,
2026-11-28):**
- **Missing-`break;` fallthrough in nested `switch (FRONT)`:** Original source
  frequently omitted the trailing `break;` after `if (cond) { I(0x6D0)=2; break; }`
  before the next `case`. When the next case also writes `I(0x6D0)=2; break;`,
  VC8 folds both arms into one basic block and leaves a dead float compare
  (`fld; mov [esi+6d0], 2; fcomp; fnstsw ax; jmp`) without `test ah, 0x41`
  (Reimu `case 302` `204->205` and `206->209->210`; Default/Aya `case 302`/`322`/`410`
  `200->201->202` and `205->212`, `case 307` `211->212`, `case 400` `205->211`).
- **Switch dispatch threshold (`movzx` remap vs direct jump table):** Grouping
  identical `I(0x6D0)=2` cases under shared labels (`case 200: case 201: ...`)
  can drop distinct pre-merge targets below 6 and cause VC8 to emit a byte-remap
  `movzx` table instead of a direct `jmp dword ptr [eax*4 + table]` (Reimu
  `case 302` needed separate `case 200..212` bodies).
- **Phase 2 tail-merge host polarity (`GG` vs `GA`):** In Reimu (`0x0048D390`),
  `switch (S(0x766)) { case 0: ... break; }` and `if (S(0x766)==0) ... goto`
  both let `GA` host `approach` and two `0x6BC` control tails, whereas wrapping
  the facing-check body in `if (...) do { ... break; } while (0);` reversed
  predecessor order into Phase 3 so `GG` hosted all three tails cleanly.
- **Outer-switch tail-merge interaction in Default/Aya `case 414`:** In
  `0x005F1F80` and `0x006126E0`, writing `case 414`'s `switch (FRONT)` as
  `if (RANGE(95,100) && C(0x55A)>0) { switch (FRONT) { case 211: I(0x6D0)=2; break; case 212: if (v<150.0f) { I(0x6D0)=2; break; } } break; }`
  kept `case 402`/`307`/`321` late-hosted while letting `case 414` host the
  shared `jne; mov [esi+6d0], 2; jmp` tail (`0x5f37af`/`0x5f37b5`) for `case 302`,
  `304`, `307`, `308`, `322`, `400`, `404`, and `410` simultaneously (clearing
  the spurious `test ah, 0x41` in `case 400` as well).
- **Nested `if` for live-register jump threading:** In Default/Aya Phase 2 `GG`,
  `if (h<=600.0f) { if (RNG(1000)<=5) { ... } }` instead of `&&` threads the
  false branch directly to `movsx eax, [esi+0x766]` (`0x5f3de1`), skipping the
  redundant `mov edi, 2` (`0x5f3ddc`).
- **Default vs Aya delta:** `Aya_update_cpu_action_policy` (`0x006126E0`,
  16,032/16,661 bytes) is identical to `Fighter_update_default_cpu_action_policy`
  (`0x005F1F80`, 15,910/16,541 bytes) across all of Phase 1 and Phase 3, differing
  only by two 61-byte Phase 2 branches (`U(0x728)=0x400` in `GG`, `U(0x728)=0x200`
  in `GA`).
