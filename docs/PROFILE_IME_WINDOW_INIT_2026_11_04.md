# Profile IME candidate-window initialization

`initialize_ime_window_state` at `0x0040E780` is reached from application
bootstrap at `0x00407ED1` when the IME option is enabled. It obtains the window's
IME context, stores it in the profile controller and sets the candidate form's
exclusion rectangle to the current window dimensions. The source uses the
existing controller and bootstrap window, ordinary Windows-compatible layout,
and the native direct IMM32 thunk boundaries.

The complete native and source bodies are each 111 bytes, but the first mismatch
is the stack frame size at +2 (`0x34` versus `0x30`). The relocated candidate
SHA-256 is `f4e320163f2f4f9ac534337564f8008d1755e992f951e76e9082e6c9a6acc504`.
This is not exact, and no exact or exception-handling credit is claimed.

The bounded observer compares five successful mocked rectangle/context cases
across native instructions, source instructions and an independent model,
including negative coordinates, empty dimensions and a null context. A modified
candidate style is a negative control. The unused position words are not
asserted, matching the observed writes. Actual Win32/IME behavior, provider
failure and full-game execution were not tested.
