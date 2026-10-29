# Withdrawn volume-conversion acceptance

Review of the gain dependency exposed an unsupported old reconstruction at
418990. Although its emitted103 bytes matched, the source explicitly allocated
an otherwise unnecessary64-byte aligned volatile scratch array, placed one float
at offset60 and repeated two volatile self-stores. There was no independently
recovered source lifetime/type supporting that storage. These constructs imitate
the native frame and stores; byte equality alone does not make them acceptable
restoration. The old exact row is withdrawn, not renamed as a valid match.

`src/audio/DirectSound.cpp` now expresses the actual log/round/scale/clamp
algorithm using one ordinary float. The two observed read-only float addresses
remain declaration-only data views with isolated address bindings and exact
native bytes, without changing existing literal aliases. No volatile, alignment
attribute, dummy storage or redundant self-assignment remains in this function.
Original translation-unit visibility and the unusual native frame/store lifetime
remain unknown, as in the nearby quantized math island.

The canonical target is Japanese1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The complete103-byte native body hash is
`a27d362dcc7f3516132c59d2ead2e4d70816b9c02f88cfb7c2750bfbc35082b4`;
all103 bytes are CFG-reachable through RET4. Raw transition402B70 calls at402BB1
and supplies the result to DirectSound SetVolume. Authored ownership and source
presence remain; only exact acceptance changes.

Natural source emits73/native103, nonexact at+0, canonical candidate SHA256
`442224069180cb81c42bd67396da28ad739d26f2803abcfbd0801d4b8bcb3eb2`.
The same focused unit still reproduces shutdown4188C0 **82/82** and buffer
creation418920 **110/110**, with unchanged canonical hashes. No shared header or
helper ABI changed. Other callers retain their existing independent receipts.
The newly accepted BGM fade/level69/70 members use their separate genuine natural
gain provider, so their acceptance does not depend on the withdrawn construction.

Accounting removes one exact function and103 exact bytes. The function remains
source-present and authored under a separate raw-body/caller origin rule. This
correction supersedes historical103-byte acceptance claims; it is not target
patching, a new exclusion or a changed comparison boundary.

Focused evidence: `build/frontier-volume-source-integrity-20261029/` contains
`formal-build.json`, `boundary.json`, `withdrawn-match.csv` and `ci.log`.
The old source is retained in Git history and the private analysis scope, not
used as an accepted implementation. Restoring credit requires genuine source
context plus complete unmasked replay, not another aligned scratch surrogate.
