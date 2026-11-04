# BGM buffer set-volume wrapper

In Japanese TH105 1.06a, the complete 19-byte body at `0x00401830` checks
whether a DirectSound buffer resource exists and forwards the volume to its
virtual method if so. Three sites in BGM stream update pass the buffer at
stream offset `0x24`. The native internal boundary receives the buffer in EAX
and volume in EDX and returns without popping explicit arguments. Its body
SHA-256 is `3a36996783e794ec7971e821df5362286f4d769105569e1e7ccfaeb64f177669`.

The existing ordinary `BgmBufferRuntime::set_volume(long)` source expresses the
same resource check and method call without declaring a private register ABI.
A fresh pinned VC8 ordinary COFF build emits 25 bytes, whose full SHA-256 is
`a4a0681fda29eccba8403a2a9b0e399ea705a599f3038542f992e05f51cff81f`;
it differs at +1 and uses a different calling convention and stack cleanup.
It is source-present and authored game glue, not an exact match.

A bounded x86 observer executes each actual body under its own observed ABI for
six combinations: null/present resource and volumes -10000, -1 and 0. The
DirectSound method is mocked. Both make the expected call or skip it, and each
returns with its own expected stack cleanup. A negative test changes the source
receiver offset and detects the changed trace. No real DirectSound device,
thread scheduling, error handling or full-game behavior is exercised; the
observer does not establish binary or ABI equivalence.
