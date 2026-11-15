# Aya root functions

| Function | Address, bytes | Source | Unit or note |
| --- | --- | --- | --- |
| Action state (vslot 0x28) | 0x602250, 65,601 | `AyaActionState.cpp` | [action state note](AYA_ACTION_STATE_2026_10_28.md) |
| Control mode | 0x616800, 1,726 | `AyaControlMode.cpp` | [control mode note](AYA_CONTROL_MODE_2026_10_24.md) |
| CPU policy | 0x6126E0, 16,032 | `AyaCpuActionPolicy.cpp` | `gpt-web-aya-cpu-action-policy` |
| Object action state | 0x61A290, 19,522 | `AyaObjectActionState.cpp` | `gpt-web-aya-object-vslot28-full-root` |
| Object initializer | 0x61F0B0, 4,531 | `AyaObjectActionEntry.cpp` | [entry ABI note](AYA_ENTRY_SEQUENCE_WORD_ABI_2026_10_19.md) |

All five are nonexact.

## Object action state 0x61A290

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

## CPU policy 0x6126E0

The function has 4,097 instructions. Its counter reads are signed, and the
last comparison differed at +0x12E, in the selector-tail sharing.

The per-checkpoint notes from September 12 to October 23 were removed in the
commit that added this note; Git history keeps them.
