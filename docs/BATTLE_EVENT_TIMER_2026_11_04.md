# Battle event timer update

The native `0x00472A70` is a 172-byte virtual body in both the RTTI-identified
CBattleManager and Arcade tables. Its SHA-256 is
`744492ad5c29309680cba21f4271bdd559ae224fff1495cdb581576f5a3c6878`.
The complete reachable body checks phase 2, adjusts the signed 16-bit event
timer using the low bit of pair state, selects or triggers event effects at
0, 499 and 999, and tails to the independently recovered presentation body.
Its table slot, full native body, mode-change calls, RNG and event calls are
pinned by the focused origin rule.

The recovered natural C++ in `BattleManagerEventTimer.cpp` uses the existing
base layout and narrow helper views. Its source-facing method returns void,
as does the actual presentation tail; the original virtual return contract is
not established and no claims about incidental EAX values are made. Original
nominal type and translation-unit identity are unknown. The pinned VC8 build
emits 186 bytes versus the native 172 and is nonexact from +12, with section
SHA-256 `a69ff764791c2b1381defff4fe0f267f87ff07e2dbf9b6cac4648edff3fc2bbb`.
The 172-byte compared prefix hashes to
`9944d208416642f651a33b89f43fc2aac3011765b9a4e988da3ad59a087a0973`.
No code shaping, invented register ABI, exact bytes, or runtime equivalence is
claimed. Build receipt: `build/frontier-battle-event-timer-20261104/formal.json`.

Reproduce with `scripts/repo-python scripts/build.py --unit
exact-first-battle-event-timer --compare --json` (expected mismatch exit 1).

## Bounded execution comparison

A new observer executes the actual native body and the fully relocated
ordinary VC8 source body on 144 combinations of phase, event mode, effect,
low state bit and signed timer values, including threshold and overflow
boundaries. Both agree with an independent model through the presentation
entry; a changed phase condition is detected. Event, mode and RNG calls are
mocked, and execution stops before the presentation body. This does not test
the actual helpers, incidental EAX return, concurrency or whole-game behavior,
and it does not change the nonexact status. Focused tests pass; run with
`scripts/repo-python -m unittest discover -s tests -p
test_battle_event_timer_observer.py`.
