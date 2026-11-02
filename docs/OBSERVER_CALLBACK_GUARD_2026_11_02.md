# Fail-closed observer callbacks

A deliberately wrong cursor receiver in the new private character-update
observer exposed a Python/Unicorn boundary issue: this installed ctypes bridge
prints and suppresses exceptions raised directly inside hooks. Raising there
alone does not reliably reject an observation or stop guest instructions.
The initial negative control failed; it was not accepted as passing evidence.

The existing native_callbacks.guarded_callback helper already provides the
right mechanism. The Select renderer and adjacent profile-deck renderer now
use it and check its captured errors immediately after emu_start, before any
result can be accepted. The private character observer uses the same helper.
No replacement helper, binary/source matching relaxation or game-code change
is introduced.

A real target-independent ctypes-bridge test raises in a hook immediately
before a test-only MOV to a mapped cell. The error survives and the guest write
does not execute. ValueError and AssertionError behavior are covered; all four
native-callback tests are now part of routine CI.

The Select audit adds an actual unknown-helper negative control: redirecting
its first call to an unobserved valid helper entry must stop and report the
captured failure. All four original positive cases and the existing corrupted
random-table control still pass. The profile-deck native fixture still records
32 observations and three zero missing counts. The private character fixture's
12 positive cases and wrong-cursor negative control now pass with no suppressed
callback exceptions.

This is bounded hardening of the two public observers used in this continuation,
not a claim that every historical emulator has been reviewed. Other existing
observers have their own guards or need separate review before reuse. Byte
comparison remains independent of observer outcomes; no exact/source/origin
counts change and no new universal behavior claim is made.
