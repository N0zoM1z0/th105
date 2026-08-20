---
name: th105-re
description: Reconstruct bounded functions from the original Japanese TH10.5 v1.06a executable using hash-attested IDA evidence, provisional boundary/origin ledgers, and retained source only as a hypothesis. Use for TH105 disassembly, naming, ABI/layout recovery, source selection, implementation, or semantic review.
---

# TH105 reconstruction

Work only against `config/target.toml`: SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`,
image base `0x00400000`, entry `0x0068B9D2`, `.text`
`0x00401000..0x006BF33A`.

## Preflight

1. Read `AGENTS.md`, `docs/RE_HANDOFF.md`, `docs/ARCHITECTURE.md`,
   `docs/RE_WORKFLOW.md`, and the relevant source.
2. Run:

   ```bash
   python3 scripts/verify-target.py
   python3 scripts/check-ida-mcp.py
   python3 scripts/report-reconstruction-status.py --summary
   python3 scripts/validate-tracking.py --require-target
   ```

3. Keep `config/claims.csv` header-only and one bounded writable scope.
4. Confirm the candidate in `functions.csv` and its origin row. Reconcile IDA's
   complete control flow; its extent and auto-name are provisional.

## Recover and implement

1. Label evidence as **Observed**, **Inferred**, **External corroboration**, or
   **Unknown**. Target bytes/xrefs/accesses are observations; decompiler types
   and retained 1.06 source are hypotheses.
2. Inspect the full function, callers/callees, xrefs, strings, globals,
   RTTI/vtables, field widths, saved registers, stack cleanup, EH paths, and
   nearby compiler/runtime signatures.
3. Recover boundary, origin, calling convention, return behavior, class layout,
   ownership, and side effects before naming or source-shaping.
4. Record a supported mapping in `reccmp-functions.csv`. Add a retained/new
   implementation to `implemented.csv` only after semantic coverage is audited.
5. Preserve VC8 x86 ABI and natural C++ behavior. TH105 has 42 LTCG C++ Rich
   records; record a concrete LTCG/TU blocker instead of inventing a standalone
   object boundary.
6. Use `$th105-typed-re` for a target-pinned fact packet and `$th105-matching`
   for focused compilation/comparison.

Do not transfer TH08 gameplay structures or VC7 code-generation recipes. Do
not carry old TH105 1.06 addresses, names, matches, or pattern conclusions into
1.06a without new target evidence.

## Handoff

Report address/accepted size, observations, inferences, unknowns, origin
classification, files changed, target inspection calls, focused comparison,
and remaining ABI/LTCG risk. Run `python3 scripts/validate-tracking.py
--require-target`, `python3 scripts/ci.py`, and `git diff --check`.
