# Fighter input snapshot

The scripted-input update at `0x463E40` saves horizontal and vertical input at
`+0x6D4/+0x6D8`, six button values at `+0x6DC..+0x6F0`, and a ten-frame timer
at `+0x70C`. The reset at `0x4633A0` clears those eight values and the timer;
it does not clear the live input fields or release edges. Reimu's input policy
calls this same reset after selecting certain actions.

The reset and Reimu caller now use one pointer-only receiver view instead of a
Reimu-specific method declaration. The complete 57-byte reset and Reimu's
6,952-byte callable plus owned data compared exactly against Japanese TH10.5
1.06a with the pinned VC8 profile. The signed interpretation of the timer in
scripted input remains distinct from the reset's byte store.

The same reset receiver is now used by the other fourteen roster input
policies. Thirteen of those complete policy payloads remained exact; Marisa's
previously nonexact candidate retained its original compared hash and first
mismatch. This is a shared call target, not a claim that the character input
policies themselves are identical.

The saved direction and six button values now share a `FighterInputSnapshotValues`
type between scripted-input update and reset. Their timer remains separate
because six edge fields lie between the values and timer. The 753-byte update
and 57-byte reset remained exact; the fourteen previously exact roster policies
also remained exact, and Marisa's candidate hash stayed unchanged.
