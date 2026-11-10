# The result input accessor is a vector subscript

`0x43B300` is the 59-byte VC8 checked `std::vector::operator[]` for the
0x68-byte input records at `0x6FCA2C`. It is compiler-generated, not an authored
`at` method. The earlier hand-written accessor reproduced its instructions but
mistakenly received authored-function and exact-byte credit. This correction
removes one function and 59 bytes from those ledgers while retaining a complete
local comparison of the real standard-library provider.

## Provider and native ownership

The existing `SceneResourceBootstrap.cpp` defines the polymorphic
`SceneBootstrapInputEx` record, asserts its 0x68-byte size, and declares the
actual input vector. Its setup loop assigns profiles and publishes pointers to
that vector's elements. The separately proven static lifetime of the same
container is documented in `INPUT_TABLE_LIFETIME_2026_11_01.md`.

`ResultInputRecordAccess.cpp` now instantiates only the non-const subscript
member of that existing vector type. There is no new record-size surrogate,
hand-written guard, compiler flag change, or synthetic calling convention.
Under the pinned VC8 SP1 compiler it emits exactly 59 bytes, with a single
REL32 operand at +0x2A calling `_invalid_parameter_noinfo` at `0x68A143`.
All bytes through `ret 4` at `0x43B338` are reachable and belong to the function;
there is no EH block, switch payload, or alignment tail.

The original exact selected-input policy at `0x43B640` loads the real vector
address at `0x43B6B9` and calls the accessor at `0x43B6BE`. The larger match-mode
policy repeats this receiver at `0x43B974` and calls it at `0x43B979`. These
edges and the existing vector lifetime establish the container independently
of the accessor's byte pattern. In contrast to checked `vector::at`, this body
contains no range-exception call.

## Bounded verification

- The public provider compares 59/59, including its relocation. Canonical SHA-256:
  `4cef7972c3905e98b11cb617c89b13166fb239602f4ec189f8555b588ebfa7da`.
- The existing generated-origin validator rebuilds this source. All 55
  non-relocation bytes, the complete call destination, and the no-tail check
  identify exactly `0x43B300` across the full current candidate inventory.
  The new rule also checks the native selected-input call and receiver address.
- The unchanged selected-input caller remains exact 153/153.
- The unchanged match-mode caller remains 286/286 but nonexact, first differing
  at +3. It receives no new credit.

The public replay is `scripts/repo-python scripts/build.py --unit
gpt-web-result-input-record-access --compare --json`.

The two caller declarations still use the legacy `at` facade. Replacing their
input-owner contracts belongs with the pending input migration; this checkpoint
does not edit those files or their SHA pins. These are local comparisons and
an ownership correction, not a new Factory-authoritative accepted claim.
