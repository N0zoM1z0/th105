# Aya root functions

One large Aya root is now 100% canonically exact; four remain nonexact.

| Function | Address, bytes | Status | Source | Unit / note |
| --- | --- | --- | --- | --- |
| Action state (vslot 0x28) | `0x00602250`, 65,601 (66,704 envelope) | **exact** | `AyaActionState.cpp` | `exact-first-aya-action-state` |
| Control mode | `0x00616800`, 1,726 | nonexact | `AyaControlMode.cpp` | [control mode note](AYA_CONTROL_MODE_2026_10_24.md) |
| CPU policy | `0x006126E0`, 16,032 | nonexact | `AyaCpuActionPolicy.cpp` | `gpt-web-aya-cpu-action-policy` |
| Object action state | `0x0061A290`, 19,522 | nonexact | `AyaObjectActionState.cpp` | `gpt-web-aya-object-vslot28-full-root` |
| Object initializer | `0x0061F0B0`, 4,531 | nonexact | `AyaObjectActionEntry.cpp` | [entry ABI note](AYA_ENTRY_SEQUENCE_WORD_ABI_2026_10_19.md) |

## Action state `0x00602250` (exact)

`Aya_dispatch_action_state_vslot28` matches the complete **65,601**-byte
callable (`[0x00602250, 0x00612291)`, 16,856 reachable instructions, 107/107
exact owners, 8-byte aligned frame `0x3E8`) and **66,704**-byte switch envelope
(`[0x00602250, 0x006126E0)`, 3 compact byte-index tables of 33/27/48 entries
with 584 index bytes, 4 direct jump tables of 4/4/4/8 entries, original
`8d4900`/`90`/`8bff` alignment padding, and 2,133 relocations across 33 direct
call targets) under VC8 SP1 `/O2 /GS- /GR /EHsc /MT` in
`exact-first-aya-action-state`
([AyaActionState.cpp](../src/characters/AyaActionState.cpp)):

- **Callable SHA-256**: `04c7620574e00d6f05bb615a095188ee2c60e94cc9d94dbad2eed56b92ab7fd5`
- **Envelope SHA-256**: `42401b4701e475fbaab7d19a542aec6edbe503082a2a0dc2a2e22407e71903a3`
- **Key VC8 shapes proven**: standalone typed `AyaActionStateView`/`AyaPeerView`
  with compile-time `offsetof` assertions; `unsigned int` button counters
  (`0x6bc`/`0x6c0`/`0x6c4` `> 0`); inline `ORBIT_SPAWN` args in `740` (preventing
  `mov al` CSE); hoisted `float base;` + per-loop `for (float counter = 0.0f; ...)`
  in `720`/`721` (matching VC8's LIFO weight-sorted `esp+0x20`/`esp+0x10` stack
  packing across 14 cases); and `float dx` in `AIM_SHORT()` (preserving `529`'s
  `fld [esp+0x70]; fadd [esi+0xf0]`). See
  [VC8_SOURCE_SHAPE_PATTERNS.md](VC8_SOURCE_SHAPE_PATTERNS.md) and
  [GIANT_ACTION_ROOT_PLAYBOOK.md](GIANT_ACTION_ROOT_PLAYBOOK.md).

The superseded nonexact checkpoint log `AYA_ACTION_STATE_2026_10_28.md` and
unused `AyaActionState.hpp` were removed; Git history retains them.

## Object action state `0x0061A290` (nonexact)

The emitted payload is 20,000 bytes, with metadata from offset 19,532. The
first difference is the initial `ja` displacement at +0x22 (target `0F`,
source `16`), not a metadata pointer.

Source shapes the target supports, already in the source:
- action 807's frame/sequence-2 exit joins the 817 tail, and 817/822 capture
  the float rotation before reading alpha;
- the two root-local quantized lookup returns use double views, and two float
  return views put four scale-read pairs in target order;
- 826 keeps a used double Y alive across the alpha update;
- 861 advances its phase and count only in initial sequence 0;
- the 804/810 sequence, 821 counter and 801/903 fade corrections.

Tried without effect or rejected:
- `/O1` and `/O2 /Os` give the same smaller payload but lose stack alignment
  and differ at +0x4. Keep `/O2`.
- Sharing the 826 and 861 tails in source loses 807's second zero-sequence
  read; keep that repeated read.
- RTM keeps the unresolved conversion shapes and changes other actions; a
  local `fenv_access` keeps the `fimul`.
- Layered, direct, typed and virtual runtime-owner views were byte-neutral.
- A joint update/initializer CIL context with twelve native providers is
  byte-neutral against the native caller.

Open: action 852's early promotion and branch-local `fild` duplication, and
scratch placement.

## CPU policy `0x006126E0` (nonexact)

The function has 4,097 instructions. Its counter reads are signed, and the
last comparison differed at +0x12E, in the selector-tail sharing.
