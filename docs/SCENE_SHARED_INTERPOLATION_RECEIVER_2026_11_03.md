# Shared scene update and interpolation receiver

This change replaces the separate method-only interpolation view with the same
0x94-byte `SceneRenderClusterUpdateView` already used by the actual scene update.
The shared declaration lives in `src/ui/SceneRenderClusterRuntime.hpp`; the old
interpolation header forwards to it. The body of each operation is unchanged.
No layout, field, calling convention, compiler flag, ABI trick or vtable is added.
This remains a target-backed update view, not a claim to know the complete
original class name or constructor/destructor translation-unit partition.

## Ownership evidence

The canonical 801-byte update at 0x451400 calls the byte interpolator at
0x451594, 0x4515BB, 0x4515E2 and 0x451635, and float interpolator at 0x451685.
Both native interpolators preserve their incoming ECX receiver into the easing
member calls at 0x45022B and 0x4502F7 respectively. See the independently
reviewed [receiver evidence](SCENE_INTERPOLATION_RECEIVER_2026_10_29.md).
The update's 0x94 layout and member offsets retain their existing assertions.
Using one declaration describes that ordinary owner relationship without
forcing source inlining or pretending that methods live in one original TU.

## Validation and scope

The quoted-include closure contains exactly three units. Fresh whole comparisons:

- Update 0x451400: exact 801 bytes; its full 848-byte COFF payload also contains
  switch metadata. Full payload canonical SHA256
  `1ebe917d1e0e45c77316d1c647f0a37ee203d62af71fc09d895e5b45b5f201c4`.
- Float interpolation 0x450290: exact160, SHA256
  `ae97f4dedacde0a2c994e4b7205286ca980de07376c29222a0ccb03032a8b80d`.
- Easing 0x450120: exact131, SHA256
  `5cefd98908e503a2128a0ed3abb9feb09bea3a17c92ee558eefaeb35cf6751dd`.
- Byte interpolation 0x4501B0: still214/native211, first mismatch +17. Its
  complete source body SHA256 remains
  `70809ebfdd29807d174d6fc300b0ea534ba9cd6e29d8f8f54669b12ec4c3be0d`.
  No byte interpolation exact credit and no attempt to force pointer registers.

The original unit selectors and function signatures now name the shared receiver;
no matching/source/origin count changes. A private combined-source context also
retained the three exact roots but does not prove original TU unity. The fresh
unit replay and actual include closure are in
`build/frontier-scene-interpolation-owner-20261103/`.
