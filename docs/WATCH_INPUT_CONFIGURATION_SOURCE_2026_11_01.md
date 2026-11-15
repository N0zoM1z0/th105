# Watch input configuration

`BattleInputGate::configure_watch_player_42bc40` (0x42BC40, 140 bytes) is
exact. The exact `LoadingWatch` 0x4268F0 calls it at 0x42697C.

The routine computes the two-side descriptor mask and saves the setup. It then
resets the low words 68/D0 and readiness bytes 6C/D4, copies the tags into the
owned metadata at D8/E0, and publishes those owned descriptor addresses to the
setup. The second side reads its tag through the already rebound first-side
descriptor, as the target does.

## What made it exact

Each side's rebind is a small inline helper,
`rebind_saved_token(token&, tag&, saved*, source)`. Taking the token by
reference makes VC8 test it in memory (`cmp [edi+0x24], ebx`) and reload it
for the tag read, and the tag reference stores straight to `[esi+0xDC]`. That
leaves AL free for the constant 1 used by both readiness stores.
- Writing the tests inline caches the token in EAX, which moves the constant
  to CL.
- A `SetupTokenInput *&` local caches it the same way.
- A helper taking the metadata by reference or pointer hoists
  `lea eax, [esi+0xD8]` above the branch.

The same unit keeps the selector 0x4284C0 and save 0x42B9B0 exact. The load
0x42BAF0 is still nonexact at +0x92.
