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

**Checked container comparisons kept under LTCG need `const_iterator`.** When
the target compares an iterator's container against a global list address on every
step, declare the loop iterators as `const_iterator`. Plain iterators let LTCG fold
those checks. Proven on 0x4194D0 ([note](AUDIO_SCHEDULER_LISTENERS_LTCG_2026_10_29.md)).
Linked units declare in-function alignment filler with `alignment_sites`.

**Compare in memory, then reload: two access paths.** A field tested directly
and then used inside an inline member of the object that contains it (or the
other way round) is not merged by VC8. The target then compares in memory and
reloads. Look for an embedded object whose inline members do the work. Proven on
0x4038D0 and 0x403840 ([note](BGM_SERVICE_LTCG_2026_10_29.md)). The 0x45D040
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
- **0x418990 call shape, 2026-11-14.** The target's `sub esp, 8; fstp qword
  [esp]; call _log10` is the non-intrinsic double `log10` call. `/Oi-` or
  `#pragma function(log10)` reproduces it, with or without `/GL`; the default
  intrinsic emits `call _CIlog10` instead. With the C++ float overload and
  extern constants, the scale order `fld units; fmul scale; fmul [gain]`
  also matches. No combination of `/GL`, `/fp:precise`, `/arch:SSE`/`SSE2` or
  `#pragma fenv_access(on)` (which stops `log10f` inlining) produced the
  `and esp, -64` frame. The intrinsic setting is therefore a second unexplained
  property of this island, alongside the frame.
