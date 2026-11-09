# Event-effect lookup uses signed 32-bit keys

The lookup at `43C150` now shares `map<int, int>` and the same global declaration
with scene-resource initialization. Its previous `map<char, int>` declaration
reproduced the 72-byte wrapper but generated the wrong callee. Passing a stack
argument's address does not establish the width read through that address.

## Native evidence

The original Japanese 1.06a executable has SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
This pass used hash-attested raw PE bytes, not decompiler types.

- `43C15E` loads map receiver `6FBF14`; `43C163` calls `45C320`.
  The complete 72-byte wrapper reads the returned node's DWORD value at +10.
- The entire 105-byte find provider at `45C320` closes through RET8.
  `45C335` and `45C35A` read a DWORD from the key argument. `45C337`
  and `45C35C` compare it with the node's DWORD at +0C, followed by signed
  JGE and JL. The byte at +15 is the sentinel flag, not the key.
- Bootstrap `43E2E0` initializes that same receiver eighteen times. It writes
  keys 0..9 with values 100..190, then 17 with 200, then 10..16 with 210..270.
  These calls use the same insert provider `4606E0` as the stage/BGM maps.
  The full 3,722-byte bootstrap was decoded again: 821 reachable instructions
  and two preserved alignment instructions at `43F006` and `43F00D`.
- An executable-section E8 scan finds three direct lookup calls, all confirmed
  as instruction boundaries in complete callers: `434E69` in the secondary
  effect helper, `434EB6` in the primary helper, and `435D1C` in pair mode.
  Their existing source declarations already pass `int`.

This establishes signed 32-bit key operations. `int` is a compatible C++ type;
it is not proof of a unique original typedef or spelling.

## Source and verification

`EventEffectRecords.hpp` now owns the shared declaration of
`g_bootstrap_effect_frames`. Both the lookup and `SceneResourceBootstrap.cpp`
use it. The lookup manifest binds its actual int-key symbol and generated find
provider. The legacy char-map relocation alias remains unused and is explicitly
marked historical; its address is not evidence for a byte-key type.

The pinned VC8 build of the old source emitted a 114-byte find with byte key
loads/comparisons. The corrected source emits the complete 105-byte provider,
with no relocations and zero differences against `45C320`. The 72-byte wrapper
still has zero differences after all four relocations are resolved.

Four scoped units were rebuilt. All five previously exact roots remain exact:
`43C150` (72), `434E10` (34), `434E90` (74), `434E40` (67), and `435CE0` (119).
The bootstrap keeps the same complete nonexact result, first difference +863.
Its code/data/EH and both caller objects retain 363 non-debug sections unchanged.
The only other bootstrap difference is the 44-byte COFF SafeSEH symbol-index
list: the same eleven handlers remain, with the two map specializations swapping
positions. Their actual handler bodies and relocations are unchanged.

Private before/final objects, full comparisons, call census, target hashes and
verification are retained under `build/frontier-event-effect-key-20261109/` and
`.analysis/frontier-event-effect-key-20261109/`. Tracking and lightweight CI pass.
This fixes a real source contract without adding authored exact credit: the
wrapper was already counted and the newly matched find is compiler machinery.
The old byte-key claim in the knowledge base and bootstrap note is superseded.
