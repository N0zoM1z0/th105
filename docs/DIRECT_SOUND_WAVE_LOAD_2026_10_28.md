# DirectSound resource wave load 4184B0

Canonical exact304/304, SHA
5184cea8847a5d2c17d6e6b80ebd98ab6b655d50774f37da459a247a953ec105.
Unit exact-first-direct-sound-wave-load; receipt
build/frontier-4184b0-20261028/formal-build.json.
The native boundary audit closes all114 instructions and both RET4 exits.

The wave service401AF0 calls this method at401B3D. It releases an existing COM
buffer, owns a real0x1C wave value with0x14 format/data pointer/size, dispatches
file decoding, records size, invokes virtual initialization, then locks the
whole DirectSound buffer with flag2. Negative HRESULT shows the target-owned
lock-failure message. Success copies the original byte count and unlocks the
returned regions. Every exit destroys the wave allocation through free.
The target does not add a second-region copy or clear size after failure;
neither defensive behavior is invented here.

The dispatch boundary408ED0 receives wave output in ECX and path in EDX, takes
no stack parameters and returns normally, consistent with ordinary __fastcall.
Its plain-WAV child has a different private scalar-replaced ABI, but that child
is not called directly or fabricated in this source. The resource receiver
uses normal __thiscall/RET4; DirectSound interfaces reuse the existing complete
COM declarations. The exact-backed initialize/destructor family independently
fixes the receiver's first virtual initialize slot and buffer04/size08 layout.

The local wave type uses natural struct alignment and a real RAII free guard.
No manual EH, register forcing, vtable recipe, assembly or copied bytes is used.
Only the new unit is built; existing shared headers and compile profiles are
unchanged. Canonical MessageBoxA IAT, error text and EH-prefix witnesses are
resolved without masking. No generated cleanup or downstream decoder credit.
