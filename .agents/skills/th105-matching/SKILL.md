---
name: th105-matching
description: Reconstruct and tune Touhou 10.5 (TH105) Visual C++ 2005 functions to exact target bytes. Use for compare-function failures, ABI/layout recovery, COFF REL32 or DIR32 relocation mapping, compiler-generated constructors/destructors/EH, VC8 STL codegen, instruction-order tuning, or deciding when LTCG/private ABI prevents a truthful standalone-object match.
---

# TH105 Exact Matching

Use this skill after the semantic role of a function is understood and the task is to turn that understanding into reproducible matching evidence. Follow the repository's `th105-re` workflow for claims, verified IDA-first/Ghidra-fallback coordination, ledger updates, and evidence ownership.

## Workflow

1. Confirm the target, claim, current ledger row, callers, callees, and relevant object/global layout.
2. Recover semantics and ABI before tuning code shape. Record calling convention, parameter placement, field widths, signedness, and ownership behavior.
3. Put the probe in the smallest plausible translation unit. Prefer a declared
   `config/match-units.toml` unit and `scripts/build.py --unit UNIT --compare
   --json`; otherwise compile with `scripts/compile-unit.sh`. Enable
   `TH105_ENABLE_GS=1` only when the target proves stack-cookie use. A `probe`
   unit does not claim an original translation-unit boundary.
4. Run `scripts/compare-function.py --json ADDRESS OBJECT`. Treat `exact`,
   `mismatch`, `blocked`, and `error` plus their relocation categories as
   evidence, not as permission to weaken validation.
5. Classify the first mismatch before editing:
   - wrong ABI, layout, field width, signedness, or calling convention;
   - wrong COFF symbol or function selection;
   - unresolved `REL32` call/jump or `DIR32` data/EH/vtable reference;
   - correct semantics but different source order, aliasing, loop form, or temporary lifetime;
   - `/GS`, EH, STL implementation, LTCG, or private compiler ABI difference.
6. Make one source-plausible change at a time and remeasure. Preserve semantics and repository style.
7. Mark `matching` only after a 100% fail-closed comparison. A standalone probe that builds but is not part of the target build is `implemented`, not `compiles`; record exact size, mismatch class, command, and remaining blocker. Use `compiles` only after integration into the target build.

## Guardrails

- Do not use naked assembly, byte arrays, manual NOP/padding, fake types, or ABI lies solely to force bytes.
- Do not add a relocation allowlist row without proving the exact symbol, address, addend, and PE bytes or compiler-generated address anchor.
- Do not infer a final executable match from a standalone object when LTCG can inline, merge, reorder, or change calling convention.
- Do not infer source equality from a normalized clone-family hash. The known
  roster manifests authorize controlled fan-out experiments, not ledger status
  changes.
- Do not treat a PE-derived synthetic COFF island as recovered original COFF,
  translation-unit, or LTCG-boundary evidence. It is a relocation-aware objdiff
  diagnostic and cannot independently grant ledger status.
- Do not use an IDA chunk owner, decompiler body, or reported size as an accepted comparison boundary; reconcile it with the ledger and target instructions first.
- Do not perturb already matching shared layouts merely to improve one probe; isolate the experiment first.
- Prefer source expressions the original programmer could reasonably have written. A code-shaping cast, alias, or loop is acceptable only when it preserves the recovered interface and behavior.

## Reference Routing

Read [references/patterns.md](references/patterns.md) before tuning a nontrivial mismatch. Its sections cover symbol selection, relocation validation, special members and EH, VC8 containers, branch/register shaping, x87 behavior, LTCG stop conditions, and evidence/status rules.

When a new repeatable pattern is confirmed by an exact match, append a compact case study there: target address, observed mismatch, source-level lever, why it is semantically legitimate, and the validating command.
