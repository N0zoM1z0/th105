# Reproducible source bytes for origin proofs

Several origin anchors hash exact source bytes. The repository's default Git attributes check out C++ files with CRLF, while 54 currently anchored source files were pinned with LF bytes. Four had already been checked out with CRLF even though their pinned, LF-normalized contents were unchanged. This caused three source-pin gates to reject before their native proofs ran.

The existing exact-byte pins are retained. Explicit Git attributes now preserve LF for those 54 source paths, while the five source paths pinned with CRLF retain the default. Four affected working files were converted back to their already-pinned LF byte representation; their Git source content did not change. A new CI test checks every source pin's actual SHA-256 and verifies that its configured checkout line ending reproduces that hash. It does not normalize or mask bytes during origin verification.

Separately, adding the BGM master-gain method changed `BgmServiceLoad.cpp` content, so its old linked-list origin pin was updated only after the full existing proof was rebuilt and passed. The float-sine, input-byte allocator, gamepad allocator and BGM list-growth origin rules were all replayed successfully, including their existing target, ownership and full-byte contracts. Receipt: `build/frontier-bgm-origin-revalidate-20261103/all-origins.log`. No origin classification or authored/exact totals changed.

## Follow-up: all source-pin formats

The first CI check only covered `source_pins` tables. A broader inventory also found `source_sha256` tables, unit-associated hashes, and `[[sources]]` entries. Thirteen additional LF-pinned source paths now have explicit LF checkout attributes. Two proofs had retained the old CRLF hash for `InputManager.hpp`, conflicting with other proofs that pin its LF bytes. Their anchors and the CSprite validator's corresponding constant now use the actual LF hash. The expanded CI check detects conflicting pins, checks actual bytes, and verifies checkout reproducibility across these anchor formats.

Both affected origin rules, `csprite-real-lifetimes-106a` and `implicit-input-packet-cleanup-106a`, were rebuilt and replayed successfully with their existing native evidence contracts. Receipt: `build/frontier-origin-eol-comprehensive-20261103/origins.log`. No source-level logic, origin classifications, or exact-byte totals changed.
