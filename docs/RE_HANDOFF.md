# Current reconstruction handoff

## Phase

Two canonical 1.06a authored-exact waves are established. The active phase is
expanding authored classification and exact source recovery beyond raw-identity
seeds using current-target-backed structural remapping where appropriate.

## Verified state

- Canonical SHA-256:
  `56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
- `resources/th105.exe` is byte-identical to the executable extracted from the
  official `th105_update_106a.exe` payload.
- IDA metadata, entry `0x0068B9D2`, five separated mapped-byte samples, required
  read tools, and a function query pass `scripts/check-ida-mcp.py`.
- The IDA inventory has 4,001 provisional candidates. Current reviewed state is
  68 authored functions, 480 classified exclusions, and 3,453 still awaiting origin/boundary review.
- All 68 confirmed authored functions are source-present and canonical exact:
  7,599 exact authored bytes across 48 configured VC8 units.
- The structural-remap waves recovered twenty-one functions / 4,295 bytes by using normalized
  VC8 instruction structure only as a candidate-ranking signal, reconciling all
  current 1.06a REL32 destinations with target/IDA evidence, then requiring a
  fresh canonical zero-difference comparison.
- `config/claims.csv` remains header-only. IDA Pro remains the sole semantic
  backend.

## Cross-version seed decision

The former repository targeted 1.06 (`3,039,232` bytes), not 1.06a, so its
addresses, classifications, and exact claims remain invalid for the current
target. A raw-byte uniqueness survey may be used only to prioritize retained
source hypotheses.

The first migration wave intersected old authored/exact hypotheses with unique
raw-identical 1.06a candidates, then rebuilt every retained source with the
pinned VC8 toolchain and required a fresh canonical zero-difference compare.
That procedure promoted 47 functions; raw identity by itself promoted none.
REL32 destinations were checked against the current target. In particular, the
second loader called by `load_spell_data` is `0x00434300` in 1.06a; a guessed
cross-version delta produced a mismatch and was rejected before IDA confirmed
the current call target.

## Next bounded work

Continue origin/boundary review so the authored denominator becomes meaningful,
then expand exact recovery from the 68 accepted functions. Structural
fingerprinting is now validated as a prioritization method for retained-source
hypotheses, but ambiguous template/clone families must be disambiguated with
current xrefs/vtables/RTTI/relocations. Treat every old 1.06 address, callee,
name, and implementation as a hypothesis until independently reconciled
against 1.06a.

The 95% authored-function and authored-byte goals cannot be reported yet: 3,453
provisional candidates still need authored/excluded classification, so the
global authored denominator is not established. Do not use the current 68/68
exact subset as a substitute denominator.

## Routine checkpoint

```bash
python3 scripts/verify-target.py
python3 scripts/check-ida-mcp.py
python3 scripts/validate-tracking.py --require-target
python3 scripts/build.py --check
python3 scripts/progress.py --check
python3 scripts/verify-exact-units.py --all
python3 scripts/ci.py
git diff --check
```
