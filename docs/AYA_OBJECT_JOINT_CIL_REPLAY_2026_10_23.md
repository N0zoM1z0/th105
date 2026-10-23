# AyaObject joint CIL caller replay

The complete linked update-caller address replay is now closed for this
diagnostic context. Its emitted payload equals the selected nonexact native
payload. The shared 826/861 control also equals its rejected native counterpart
and still loses 807's second sequence read. No game source or exact credit changes.

## Target, source epoch and build

Only original Japanese 1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. Target/status/tracking checks pass. IDA rejects the open database's
different hash; evidence comes from the attested PE, native COFFs and fresh
serial VC8 SP1 builds at CPU0/nice10.

The current update body `0x61A290` and initializer `0x61F0B0` are placed in one
consistent owner model with the target-backed short selector contract. This
does not recover the original nominal class or TU. The ordinary native build
leaves both full payloads unchanged: update 20,132 / SHA256 `a5dc22f5...`,
initializer 4,859 / `6f70b6f3...`. The initializer still has its two register-byte
differences. Only the update root receives full linked replay in this report.

Both bodies are then compiled as one genuine `/GL` input. The DLL link uses
twelve actual native source-provider objects, pinned static CRT/SDK libraries
and attested external game data. No code-provider stubs or fabricated return
bodies are used. The two root methods are exported to retain them in this
diagnostic DLL; this is not a game executable or an owner-lifecycle witness.
Three requested math dependencies remain nonexact (`0x435160`, `0x406360`,
`0x4063D0`), and nominal aliases retain the earlier probe's type/ownership limits.
Native providers remain opaque to CIL optimization. No DLL-provider execution,
all-exact helper closure or original LTCG partition is claimed.

## Full update envelope

The linker export and map agree on root `0x10001000`; the next map owner starts
at `0x10005EB0`. This is only an initial envelope. Independent switch parsing
and CFG traversal then close all 19,662 reachable code bytes / 4,664 instructions,
two bytes of trailing code alignment, seven switch dispatches with their metadata and the remaining
linker alignment. No unknown direct exits, indirect jumps or internal calls
are silently accepted.

The previous replay helper supported byte-indexed switches only. Aya's linked
root has one such table and **six directly indexed dense tables**. The new
dense path requires adjacent `CMP r32,max / JA default / JMP [r32*4+table]`:
the complete index register, width, table count and default destination must
agree. It accepts no byte/word substitute, changed guard or dispatch re-entry.
Every switch pointer still needs its exact HIGHLOW field and instruction/table role.
The existing accepted-unit comparator is unchanged.

| Complete replay | Selected source | Shared phase/fade control |
| --- | ---: | ---: |
| Emitted payload bytes | 20132 | 19884 |
| Metadata offset | 19664 | 19416 |
| HIGHLOW fields | 362 | 361 |
| Destination pointers | 67 | 67 |
| Switch address fields | 8 | 8 |
| Literal references | 287 | 286 |
| Ordinary direct calls | 123 | 123 |
| Attested fixed game-data references | 3 | 3 |
| Separately verified trailing INT3 bytes | 12 | 4 |

All address fields are consumed; literals are checked against immutable source
PE storage, operand widths and exact target contracts. No opcode or ordinary
instruction byte is masked. Linker alignment remains in the normalized envelope
and its hash; it is not presented as native emitted payload or target equality.
The emitted portions are byte-identical to their respective native controls
both at the canonical address and at `0x800000`.

Selected payload SHA256 remains
`a5dc22f5c6f0e93a3fc81592510327c5708c8c4d41938f2bd96eaf7947523ede`;
the complete linked envelope including twelve INT3 bytes is
`b85f9304d487fbf5ba2e3a0b6b678e02647c9ad7c8f983f13789a073fb1398d8`.
The shared control retains payload `a9858165c48c3056...` and the known native
read deficit. It does not become selectable merely by entering this CIL context.

## Read trace and interpretation

A fresh representative 807 case executes each replayed caller with the original
target helpers through actual RET. Target reads WORD13E at `0x61A791`,
`0x61A7AE`, `0x61A853`; selected CIL has three corresponding reads. Shared CIL
has only two. Every other recorded observation agrees in that case. This is
caller replay with original helpers, not execution of the DLL's provider bodies.
The full earlier 3,968-case matrix was not rerun: complete mapped byte identity
to the prior controls is independently checked. See the
[shared-tail report](AYA_OBJECT_861_SHARED_TAIL_CONTROLS_2026_10_23.md).

The [older joint experiment](AYA_OBJECT_RETIREMENT_OWNER_READS_2026_10_22.md)
reported eight nonrelocation changes and incomplete linked replay for an older
source epoch. Current replay has zero ordinary-byte changes against current
native code. The old result must not be carried forward as a current difference.
These controls limit this specific visibility/profile/partition combination;
they do not prove standalone impossibility or rule out wider genuine CIL context.

Root remains nonexact at `+0x22`, target `0F` / selected `9B`; callable ledger
size stays 19,522. No shared game ABI/header/profile/partition/binding or accepted
unit changes, no aggregate replay claim. The diagnostic helper gains three
target-independent tests covering dense positive replay, malformed bounds and
guards, and missing address/destination relocations; compressed-table controls
continue to pass.

Private inputs/receipts are under `build/aya-joint-cil-20261023/`, with the second
context in `shared/`. Recipes are under `.analysis/aya-joint-cil-20261023/`.
`inspection.json`, `replay.json`, `mapped-identities.json` and `807-example.json`
retain the closure, address replay, complete byte identities and runtime sample.
Generated images, maps and reports stay outside Git.
