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
