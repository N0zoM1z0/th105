# Actual sprites in long battle info records, 2026-11-02

Target SHA-256: 56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.

The two 0x94-byte members at +0x004 and +0x098 of the 0x154-byte
InfoLongRecord154Runtime now use actual CSprite. The incomplete eight-slot
InfoLongSprite94 interface is removed. Rendering uses the real render method
and named scale fields. Resource binding directly uses the actual member's
set_texture method, removing the UiSprite94 receiver cast.

A serial before/after control rebuilt the complete actual quoted-include closure:
two units, three accepted roots. No manifest, profile, relocation binding or
ledger changes were needed. All three complete bodies remain canonical:

- 0x432550 resource binding: 107 bytes, SHA-256
  1650d4b1fb2d5af3e53307d1f6e2cc5b743260d95f04640271d8abdd11d0cd5d.
- 0x4325C0 render: 323 bytes, SHA-256
  452492b2d9c8bbcc3480f56e4c0c7cce8f2be1377dc3ed9133761f831385344c.
- 0x4327C0 update: 310 bytes, SHA-256
  7609629aef56d321596581137b5dc62a416c8236463e3ad5bbffeda1fee20cd2.

The caller-facing byte-side binding declaration is unchanged. No lifetime
implementation, extra emitted RTTI ownership or new exact credit is claimed.
The existing real sprite layout assertions cover size and scale offsets; the
record size assertion remains 0x154. No manual vptr, copied body, inert local,
ABI change or compiler barrier was introduced.

Private before/after results: build/frontier-info-long-real-sprites-20261102/.
Final adopted replays pass. CI passed all 962 tests in 115.679 seconds.
Both diff checks gate the local checkpoint.
Totals remain 1426 exact functions / 443399 bytes, 1636 source-present,
1655 authored, 1826 mapped, 2075 excluded, 297 review and 813 units.
