---
name: th105-library
description: Classify and reproducibly recover compiler/runtime or third-party library islands in the original Japanese TH10.5 v1.06a executable. Use for positive library identification, exact upstream-release provenance, VC8 library member extraction, third-party source compilation, or strict exclusion from authored progress.
---

# TH105 library classification

Use `$th105-re` preflight first. Library work changes origin accounting; it does
not create authored reconstruction progress.

## Establish provenance

1. Bound the candidate from exact target control flow and reconcile IDA chunks.
2. Collect independent evidence: recognizable API/algorithm, strings/constants,
   import neighbors, compiler helper conventions, public symbol/signature,
   binary/library member similarity, and surrounding call ownership.
3. Identify an exact upstream/compiler release when possible. A decompiler/FID
   label or contiguous address island alone is insufficient.
4. Record `origin`, `disposition=exclude`, confidence, and an evidence ID in
   `function-origins.csv`; use a `library`/compiler category in
   `reccmp-functions.csv` only when a durable mapping is useful.

## Reproduce when valuable

- Prefer pinned public source or an exact VC8 library member with recorded
  archive/member provenance.
- Build the smallest natural object using the relevant VC8 profile and compare
  complete bytes/relocations through a dedicated unit.
- Keep third-party/compiler sources separate from authored `src/` modules and
  never add them to `implemented.csv` or authored `matches.csv`.
- Do not edit public upstream sources merely to mimic a target unless the
  resulting fork/provenance is explicit and still useful.

## Stop conditions

Leave the row in review when evidence cannot distinguish authored code from a
library, the upstream release is uncertain, the boundary is not accepted, or
LTCG has merged ownership. Report the exact blocker instead of broad range
classification.

Old 1.06 library islands and TH08 library inventories are search hints only;
re-attest every byte, release, and boundary against 1.06a.
