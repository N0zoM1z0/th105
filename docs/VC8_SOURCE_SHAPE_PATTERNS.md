# VC8 source-shape patterns from target residuals

Short findings from the 2026-11-14 session. Each entry names the target
signature, the source shape that reproduces it and the function where it was proven.

## Patterns that produced exact matches

**Late branch into the entry `return false` epilogue.** If a final test branches
back into an earlier `xor al, al; ret` while the fall-through returns true, write
one trailing `return true` reached from several paths. An adjacent
`if (x) return false; return true;` pair folds into `setne`.
Proven on `CProfileKeyConfig::capture_key_input` 0x44B540
([note](PROFILE_KEY_CAPTURE_SOURCE_2026_11_03.md)).

**Clamp with a repeated upper-bound test.** The signature is
`cmp v, hi; jg → hi; cmp v, lo; jge → (cmp v, hi; jle → v; else hi); else lo`,
with the operand re-read from memory each time. That is a macro clamp,
`max(min(v, hi), lo)`, written with the `std::min`/`std::max` comparison order. Use
`TH105_CLAMP` from `src/engine/MinMax.hpp`. The CRT `__min`/`__max` macros give `jge` instead of
`jg`, and the `std::` templates bind temporaries and grow the code.
Proven on `CMenuConfig` constructor 0x441520
([note](CONFIG_MENU_CONSTRUCTOR_2026_10_31.md)).

**AND of arithmetic sign masks.** Four `sar r, 31` results ANDed together come
from `(a >> 31) & (b >> 31) & ...` on `int`. An unsigned
`(a & b & ... & 0x80000000) != 0 ? -1 : 0` lowers to `neg`/`sbb` instead.
Proven on `test_descriptor_point_inside` 0x46B8B0
([note](COLLISION_SEMANTICS_2026_11_07.md)).

**Char local at the bottom of its slot.** When a single `char` whose address is
taken lives at offset 0 of a 4-byte slot, it is a by-value `char` parameter of an
inlined helper. Scalar `char` locals and `char[1]` arrays go at offset 3. Proven on
`CFileList::go_parent_directory` 0x4398B0 ([note](FILE_LIST_PARENT_SOURCE_2026_11_01.md)).

**Typed fields instead of `char *` offset views.** A load hoisted above a byte
store in the target, such as a vtable load before `++state`, needs a typed member.
Access through `reinterpret_cast<unsigned char *>(this)[offset]` may alias
anything, so VC8 keeps the original order. Proven on the Arcade post pipeline
0x472F80 ([note](BATTLE_ARCADE_POST_PIPELINE_2026_11_04.md)). Offset-macro
sources such as the character input policies are candidates for the same fix.

**Member stores through a materialized subobject pointer.** If the target writes
an embedded object's fields through a register that holds its address, use an
inline member on that object instead of `owner.member.field = value`.
**Loop induction base.** The array referenced first inside the loop body becomes
the loop's pointer induction variable. A local such as `row = items[i]` can
move that choice. Both were proven on `CTitle::render` 0x425740
([note](TITLE_RENDER_2026_11_04.md)).

**Extra checked-iterator range test after `begin()`.** A `+=` range check
directly after the `begin()` check means `begin() + n`. Look for a seek or
index helper called with 0. Proven on `CScenarioData::select_label` 0x455490
([note](SCENARIO_LABEL_SOURCE_2026_11_03.md)), which also needed its search loop
written as `for (;;)` with the null exit first.

**`compare(0, size, ptr, 0)` means `== ""`.** An explicit compare call with
those arguments schedules differently from the inlined `std::string == ""`.
Map the `""` literal symbol in the unit's `dir32_targets`. Proven on 0x4317A0
([note](PROFILE_WRITER_CHECKED_DECK_2026_10_29.md)).

**Rebuild before trusting a nonexact ledger entry.** Three functions were
already exact in their units but had never been accepted
([note](PENDING_EXACT_ACCEPTANCE_2026_11_14.md)). After a shared header change,
rebuild the units that hold nonexact functions, not just the exact ones.

## Parked residuals (tried, still nonexact)

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
- **Clash resolver tail merging.** `resolve_group_b_object_clash` 0x46CA80 is
  557 bytes against 542. The target merges the equal case into the final
  `8/8` block with the result in EAX, and stores slot-first only there. All 24
  store orders for those two blocks, an inline `set_clash_result` helper (521 and
  534 bytes) and an `if/else` single-exit form (557 bytes, now the selected
  source) fail.
- **`movzx` + `movsx cx` for a deferred health amount.** `BattleCollisionPhase_run`
  0x46DFF0 is exact to +1369. Inline helpers taking `short` or `int`, a `short`
  local, and `unsigned` field types all keep the folded `movsx r32, word`.
- **Final `return 0` laid out before a cancel block.** In both
  `update_profile_message` 0x43F6E0 and `CMenuConnect_update_history_selection`
  0x443030, the target puts its own `xor eax, eax; ret` straight after the
  `cancel == 1 || is_menu_initial_press(...)` test. VC8 instead tail-merges it
  into an earlier identical return. An inverted early return, a nested `if`,
  an `else` arm and a result variable all fail. A `bool` local stops VC8 from
  inlining the two-caller `static hide_message()`.
- **Two-value switch lowered to a select.** In `CBattleSV_update` 0x426180 and
  `CBattleCL_update` 0x426380 the target branches into a shared `return 8`
  epilogue. Putting `default` first or using an `if` return does not reproduce it.
- **Marisa input policy `||` layout.** `Marisa_dispatch_input_policy` 0x4B9FA0 is
  exact to +6901. In the target, the action-412 body follows the first clause of
  `(UP && FORWARD && ...) || (UP && ...)` and the second clause jumps back into
  it. Splitting into two `if` blocks with identical bodies reproduces the first
  clause, but VC8 merges only the tail of the duplicate body (object grows 20
  bytes). An `else if` behaves the same, and a `goto` into the first body compiles
  exactly like the original `||`.
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
- **RTM compiler control.** Building 0x431390, 0x427390, 0x46C5B0 and 0x414E40
  with the local VC8 RTM toolchain (`TH105_MSVC8_ROOT=.tools/msvc80-rtm`) fixes
  none of these residuals, and it makes GameConfig_save worse (+233). The SP1
  pin stays.
