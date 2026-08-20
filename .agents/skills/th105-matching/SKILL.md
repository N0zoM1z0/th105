---
name: th105-matching
description: Compile and tune Touhou 10.5 v1.06a Visual C++ 2005 x86 functions for strict canonical byte equality. Use for focused VC8 COFF builds, comparator failures, REL32/DIR32 replay, ABI/layout codegen, COMDAT/EH analysis, or determining that LTCG prevents a truthful standalone-object match.
---

# TH105 exact matching

Use together with `$th105-re`. Exact acceptance is defined by
`docs/BUILD_MATCHING.md`, not visual similarity or an old report.

## Focused loop

1. Verify the target and ledgers, then confirm an accepted function boundary,
   authored mapping, and source-present entry.
2. Add the smallest reproducible VC8 unit to `config/match-units.toml`.
3. Run:

   ```bash
   python3 scripts/build.py --check
   python3 scripts/build.py --unit UNIT --compare --json
   ```

4. Classify the first failure: target/boundary, COFF owner/extent, relocation,
   ABI/layout, missing behavior, compiler profile, or LTCG/TU ownership.
5. Change one evidence-backed source property and recompare the whole accepted
   extent. Do not optimize against an isolated first mismatch while later
   relocation or control-flow differences remain unexplained.
6. Record exactness only at zero differences with complete relocation replay;
   update `matches.csv` and the function ledger together.

## VC8 rules

- Preserve x86 calling conventions, `this` placement, return cleanup, scalar
  widths, class/vtable layout, constructor/destructor/EH behavior, and static
  initialization.
- Resolve REL32 and DIR32 using durable symbol/relocation ledgers. An address
  equality without correct COFF symbol ownership/addend is not sufficient.
- Prove comparison extents from target control flow and COFF records. IDA tail
  chunks, jump tables, funclets, and adjacent data are not automatic members.
- Prefer natural C++ expressions and lifetimes that explain the target. Never
  use inline/native assembly, copied bytes, padding, fake returns, dead shaping
  code, or calling-convention lies.
- The target contains 42 C++ LTCG inputs. If independent compilation cannot
  truthfully reproduce a function because its boundary/profile was link-time
  transformed, document that concrete stop condition and seek a larger honest
  unit or later link-stage comparison.

## Shared-change safety

After a shared header/layout/flag/TU/global/relocation change, replay every
affected unit. Aggregate results require:

```bash
python3 scripts/verify-exact-units.py --all
```

Do not add a reusable pattern to this skill until a clean 1.06a unit, command,
and exact result make it reproducible.
