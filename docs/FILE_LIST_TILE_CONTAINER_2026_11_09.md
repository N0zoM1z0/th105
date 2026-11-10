# File-list tiles and the two deque access contracts

CFileList now owns a real `std::deque<CTile>`. Page construction inserts into
that declared container directly, rather than treating a deque of opaque
FileListTile objects as another template specialization.

Following the actual access provider exposed a second error hidden by an exact
wrapper. FileList rendering called `at()` in source, but its manifest assigned
that call to the native `operator[]` entry. Both helpers happen to occupy 94
bytes, yet they have different range-failure behavior. Rendering now uses the
actual operator, while Youmu's history reader supplies its real checked `at()`
provider through the same record deque already used by construction and writes.

## Original receiver and provider evidence

The raw Japanese 1.06a PE has SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.

- Page preparation takes `this+40` at `43A77C`, allocates A4 bytes at `43A8F2`,
  and calls the actual CTile copy at `43A914`. Copy `4396A0` installs CTile's
  table `6C0718` at `4396CD`. The complete copy is 164 bytes.
- Rendering takes the same `this+40` at `439A43`, calls access `4399C0` at
  `439A4A`, then CTile::render at `439A51`. The new emitted `operator[]` matches
  all 94 bytes of `4399C0`, including its invalid-parameter checks.
- The old emitted `at()` instead matches `53CD90`, whose initial range failure
  calls the out-of-range path `431610`. It is not the provider at `4399C0`.
  Existing row-count guards remain; the change restores the actual operation
  on the separate page container.
- Youmu construction `53B330`, history writes `539B70` and record application
  `53CDF0` identify a deque of 2C-byte YoumuObjectRecord values at owner +7D0.
  The reader now uses that same declared deque and its real reference-returning
  `at()` instead of an undefined pointer-returning facade. Its emitted helper
  matches all 94 bytes at `53CD90`.
- Ordinary GS is enabled for the Youmu reader's newly emitted range-error
  machinery. Its 175-byte application body is unchanged, and the full emitted
  range-error body, handler and metadata remain identical to the former
  FileList witness, apart from the template-owner symbol.

CTile's complete 247-byte RTTI graph, four-slot table, 31-byte scalar cleanup
and 164-byte copy pass the existing owner checks. Native deque teardown
`420AF0` dispatches scalar destruction with flag zero, matching the real
polymorphic element lifetime.

## Verification and retained limits

All 21 affected units were rebuilt. Their 44 exact comparisons retain complete
canonical equality, and both actual 94-byte access providers now also compare
in their correct native contexts. FileList's complete destructor EH matches all
120 bytes. There are 2,800 unchanged non-debug sections across the scope.
Changed support consists of the corrected access/range-error dependency chain,
newly emitted real Youmu STL support, and coalesced duplicate page allocator
and block-size definitions.

The prior mismatches remain unchanged: replay browsing 559/native511, page
preparation 1155/native1106, and parent navigation 91/native91 with its known
stack-byte difference. This work adds no authored exact count.

The FileList generated proof now covers 23 existing candidates. Five existing
exclusions, `at()` and four range-error clones, move to the real Youmu reader's
proof. Both retain the original full-inventory, relocation, coverage and tail
requirements. Growmap and replay-delete proofs, the affected implicit copy and
all five affected scalar-wrapper proofs also pass. Only FileListFinalize's
changed reviewed-source pin is renewed, preserving its declared CRLF checkout.
Unrelated classifications and pending input-migration pins are unchanged.

The original at()-to-operator[] mismatch is retained in the verification rather than
hidden by the wrapper's exact bytes.
