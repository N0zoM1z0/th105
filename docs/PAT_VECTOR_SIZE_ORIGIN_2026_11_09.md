# The PAT record count is a vector size provider

`0x45C090` is the 31-byte VC8 `std::vector<PatRecord88>::size() const`
provider, not an authored game method. The previous byte-stride implementation
matched the instructions but assigned them to the wrong owner. Replace it with
the actual standard-library member and remove one authored function and 31
bytes from the source/exact ledgers.

## Actual source and receiver

A fresh build of `FighterPatResourceLoading.cpp` emits this member automatically
from the real `PatGroup::records_00` vector. The source uses the existing
0x88-byte `PatRecord88`, including its FrameData base and three owned vectors.
It does not introduce a record-size surrogate or force compiler options.

The native loader calls the record-vector assignment at `0x4621A2 -> 0x461A30`.
Assignment calls insertion at `0x461AC2 -> 0x461640`, which calls size at
`0x461740 -> 0x45C090`. The actual generated insertion member has the same size
call at +0x100, and its first 261 bytes match the native non-relocation bytes.
The insertion section is 775 bytes versus the 768-byte native candidate, so
this caller evidence is not an exact insertion claim. The unchanged loader
also remains nonexact: 3885 bytes, first mismatch +866.

## Complete local verification

- Both the normal loader emission and the explicit public provider reproduce
  all 31 canonical bytes with no relocations or alignment tail. Both returns
  and all 13 instructions are reachable; there is no EH or switch payload.
- The existing generated-origin validator rebuilds the real loader under the
  pinned VC8 SP1 compiler. All 31 bytes identify only `0x45C090` across the full
  4,027-candidate inventory. Its rule also checks the native insertion call.
- `cross-v106a-hit-quantities` remains exact at 31/37/37. The two authored
  scaling roots retain their entire COFF sections and relocation roles.
- Shared headers and the pending 18-file input migration are unchanged. The
  match-unit edit selects only the new provider symbol.

Canonical provider SHA-256:
`1b52d9bdc5d0c414653cfef5c2021e378dda72c8dffec05e66f763a86cdf7f8d`.
Replay the public unit with `scripts/repo-python scripts/build.py --unit
cross-v106a-hit-quantities --compare --json`. The private scoped driver is
`.analysis/frontier-pat-vector-size-20261109/verify.py`; its results and baseline
reports are under `build/frontier-pat-vector-size-20261109/`.

This checkpoint corrects local ownership and accounting. It does not add a
Factory-authoritative accepted claim.
