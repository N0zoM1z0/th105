# DirectInput error reporting

The game mouse initializer calls `0x0040D540` on its property-setting failure.
The helper forwards the game window, supplied message, `DInput-Error` title and
zero flags to `MessageBoxA`. The existing ordinary C++ reporter in
`DirectInputMouseBootstrap.cpp` is now tracked as source-present.

The complete native body is 22 bytes and takes the message in EAX. Ordinary
source emits 26 bytes with a stack argument, differing from +1; no private ABI
or noinline workaround is introduced. The first 22 relocated candidate bytes
hash to `1716053b3de014d5c73b03fc6d9e2be8118d226ab17ab6a03b70257ad6b0a6a5`.
This is not exact and has no exact-byte credit.

Three native/source execution fixtures and an independent model agree on the
forwarded arguments and return value; `MessageBoxA` is mocked. A changed dialog
type is detected as a negative control. Actual GUI interaction and DirectInput
hardware behavior are not tested. See `DIRECTINPUT_MOUSE_SOURCE_2026_10_30.md`
for the real mouse caller and linked-source scope.
