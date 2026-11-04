# Resource handle manager acquisition

The native `0x00405090` is the game resource manager's token-acquisition
policy. The wave loader, title texture loader and text texture wrapper call the
same body. It locks the manager, selects a fresh or recycled slot, advances a
16-bit generation (wrapping to one), publishes the token, updates the checked
container structures and returns the stable slot. The existing ordinary source
is `WaveLoadManager64::acquire` in `src/audio/WaveServiceLoad.cpp`.

The native body is 364 bytes and uses a private EDI receiver. The genuine linked
wave source graph previously emitted a 454-byte acquisition body, with a
normal source member declaration. It remains nonexact; the helper ABI is not
fabricated and no exact or EH credit is added. The original template/type name
and translation unit are not established. A separate text-texture source
models the same shared target and does not prove an original nominal type.

`linked_wave_pointer_back_origins.py` validates the actual source and native
wave-root/acquisition/deque-back call graph and pins the full native acquisition
hash. It proves the deque helper's origin independently; it does not establish
full acquisition equality, actual concurrent execution, allocation failures
or exception behavior. See `WAVE_SERVICE_LOAD_SOURCE_2026_10_31.md` for the
linked source graph and its earlier 454/364 comparison.
