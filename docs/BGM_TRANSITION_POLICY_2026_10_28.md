# Scenario BGM transition43D030

Canonical JP1.06a SHA-256:
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.

The scenario interpreter458440 calls this complete208-byte body at4594A2,
passing the command's path, signed duration and linked flag. It ignores the
residual result. This is game-authored playback policy, not a generated wrapper.

The function stores the source path, fades the old handle using duration and
signed duration/2, allocates a new handle and prepares it at zero gain. The
linked branch links new to old; the other branch schedules immediate start.
It then sets the new handle's gain transition with the literal1000 scale,
publishes the path to score data, and only then replaces the global BGM handle.
There is no null-path or failed-allocation guard in the target.

Ordinary source added to src/audio/BgmPlayback.cpp preserves the real four-byte
BgmHandleResult lifetime. First complete focused build is canonical208/208;
all three accepted siblings stay exact:43CF00123,43CF80168,43BB9036 bytes.
No shared header, compiler profile or global relocation change was needed.

Unit: cross-v106a-bgm-playback.
Receipts: build/frontier-43d030-20261028/{formal-build,boundary,callers}.json.
Boundary traversal covers the whole body through RET43D0FF, including the
native strlen loop and both link/schedule paths. Only208 authored bytes are
credited; called service implementations remain independently evaluated.
