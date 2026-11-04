# Raw input hold-counter update

The Japanese TH105 1.06a `CInputManager` vtable slot at `0x006C1678` points
to the complete 407-byte update body at `0x00409DA0` (SHA-256
`c24daf653f2aa593bc00ab6b851f9df8fc38d38cd9744ebd2056012ad5a86914`).
The canonical-exact logical-input update calls it at `0x0040A05D`; the gamepad
state accessor is also independently exact.

The selected ordinary C++ source uses actual binding and hold-counter fields,
without crossing distinct members by pointer arithmetic or introducing
zero/mask variables for code generation. It handles gamepad axis thresholds,
keyboard direction precedence, button holds, disabled bindings, missing
controllers and reset for other source IDs. Its complete ordinary VC8 body is
406 bytes, SHA-256
`01b9dbc90c2c4f22ed83d80632135b7412f9b287dae981a2410a4e94a75f5bea`,
and is nonexact from the entry due to register allocation. No exact bytes are
claimed.

A bounded x86 observer compares 35 native/source fixtures against an independent
counter model: missing controller, all 25 combinations of five axis threshold
values, selected keyboard combinations, disabled bindings and reset. The gamepad
accessor is mocked; a changed threshold is detected by a negative test. Only
finite valid binding indices and non-overflowing counter examples are covered.
This is not DirectInput device, overflow, invalid-index or full-game testing.

## Real-source CIL diagnostic

One additional `/GL` diagnostic compiles the same natural input body with the
real `InputManager.cpp` gamepad accessor as an ordinary COFF provider. It models
the existing backend definition in a separate translation unit via the
verified native data binding; no callable helper stub is supplied. The root is
exported only so the diagnostic can locate it. The linked body is still
406/native407 and has the same canonical SHA-256 and first mismatch as the
ordinary build. This is not the shipped whole-program link, and no additional
source or exact credit follows.
