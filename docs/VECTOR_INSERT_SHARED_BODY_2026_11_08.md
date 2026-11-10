# Shared vector insertion body, 2026-11-08

The real BGM lifetime CIL emits a complete 143-byte `std::vector<unsigned>::insert`
body that matches native `0x40DEE0` after five named call relocations. The existing
exact score routine also calls that native entry through `std::vector<int>::insert`.
This is evidence for a shared 32-bit-element implementation, not a reason to
change either caller's element type.

## Evidence

The comparison uses the pinned Japanese 1.06a target and unchanged
`exact-first-bgm-stream-lifetime` unit. Its genuine source is
`src/audio/BgmStreamAllocation.cpp`; the emitted symbol has unique ownership in
`ExactFirst_BgmStreamLifetime.ltcg.obj`. The current linked-build provenance check
covers the source closure, compiler, libraries, input digest, image, MAP and
bindings. Four existing BGM roots replay exactly. A fresh ordinary build of
`gpt-web-score-story-progress` also preserves its 95- and 860-byte exact roots.

Both insertion bodies contain 59 instructions. Every byte is reachable; the
complete CFG closes at a return, with no external jump, data reference or PE
base relocation. Four calls resolve to the independently identified invalid-
parameter routine at `0x68A143`; the fifth resolves to `_Insert_n` at `0x40E060`.
All remaining bytes compare directly, and the result is unique across the
4,027-entry candidate inventory. The canonical body SHA-256 is
`87fb25b43616db229aa94c107902eed7799753c7fe7e32d944ec91232c995f8a`.

The target edges independently connect the two source types:

- Previously classified unsigned-vector `push_back` at `0x40DCF0` calls
  `0x40DEE0` at `0x40DD51`.
- Exact score refresh `0x42E3F0` supplies the signed-vector decorated identity
  at `0x42E5C5`, `0x42E61F`, `0x42E6AC` and `0x42E733`.
- The insertion body calls its growth child at `0x40DF36`.

The growth child's identity is supported by the actual VC8 header expansion,
these parent edges, and its complete sequence of twelve calls to independently
classified vector/allocator, fill/move, length-error and CRT helpers. That child
is not itself exact: current CIL emits 473 bytes against native 475. Both CFGs
close completely. Their first branch displacement difference is at +43, and the
first instruction-choice difference is the growth calculation's EAX/EBX use at
+152. This is a compiler-context boundary; do not alter the pinned vector header
or run a source-spelling grid to remove it.

## Retained work and next use

The preceding fresh BGM build and four-root replay are in
`build/origin-anchors/bgm-fill-linked.json`. These provide a concrete helper
identity for future consumer work without inventing a new matching framework. No
source, origin ledger or exact ledger is changed here; there is no Factory
acceptance receipt for this new local comparison.

The neighboring pointer-vector chain was also bounded: `0x404400` forwards to
`0x404470`, then `0x404530`; the latter uses `0x4027E0` and `0x404500`. The 35-byte
pointer `_Ufill` at `0x404500` already has a November 1 origin proof, so the new
BGM witness is not a new exclusion or match. Its other parent bodies remain
nonexact. Boundary observations are retained in the same private directory.
