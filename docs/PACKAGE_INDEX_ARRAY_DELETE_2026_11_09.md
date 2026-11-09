# Package-index path array ownership

PackageFileIndexNode allocates its filename with `new char[length]` and must
release it with `delete[]`. The earlier `free` source and relocation binding
misidentified the native array-delete thunk, even though that binding produced
the same relocated bytes. The child-node chain still uses scalar delete.

## Runtime evidence

The original Japanese 1.06a target has SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Its three five-byte runtime entries match complete functions extracted from
the SHA-pinned VC8 SP1 `libcmt.lib`, including their named jump relocations:

- Array new `??_U@YAPAXI@Z` at `0x665B8A` jumps to scalar new `0x689DCB`.
- Array delete `??_V@YAXPAX@Z` at `0x68AA26` jumps to scalar delete `0x6898EA`.
- Scalar delete `??3@YAXPAX@Z` at `0x6898EA` jumps to CRT free `0x68C686`.

The node constructor at `0x41B7F0` calls the first entry, while the normal
destructor at `0x41B850` calls the second. Sharing the eventual CRT free
implementation does not make those allocation-family interfaces interchangeable.
The source now uses array delete, and the two package comparison units bind
the emitted array-delete symbol to its actual native entry.

## Affected comparisons

All thirteen source-consuming units were built before and after the change.
The 43 individual comparisons preserve 24 exact results, ten existing
mismatches and nine existing blockers, including the same compared hashes,
extent sizes, mismatch locations and normalized failure reasons. The complete
node destructor remains 43/43 with SHA-256
`5a2ca00614fc813935d1cf1f0ee40bf61d480b9cbae5f1201ca955f5c7eede82`.
No new authored exact credit is added.

The four dependent BGM-list, CSV-deque, wave-pointer-deque and package-map
origin proofs pass after updating only this source's four input hashes.
The input migration and its separate source pins are preserved.

Before/after reports, runtime objects and origin results are retained under
`build/frontier-package-array-delete-20261109/`; the bounded drivers and
protected pre-existing diff are under
`.analysis/frontier-package-array-delete-20261109/`.
