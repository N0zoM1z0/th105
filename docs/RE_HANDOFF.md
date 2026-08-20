# Current reconstruction handoff

## Phase

Corrected-target baseline and workflow reset for original Japanese TH10.5
1.06a.

## Verified state

- Canonical SHA-256:
  `56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
- `resources/th105.exe` is byte-identical to the executable extracted from the
  official `th105_update_106a.exe` payload.
- IDA metadata, entry `0x0068B9D2`, five separated mapped-byte samples, required
  read tools, and a function query pass `scripts/check-ida-mcp.py`.
- Fresh IDA inventory: 4,001 provisional candidates from
  `0x00401000` through `0x006BF300`.
- All candidates are unclassified with unreviewed boundaries. Authored,
  source-present, exact, and excluded totals are zero.
- `config/claims.csv` is header-only. No match units are accepted yet.
- IDA Pro is the only semantic backend. A briefly started fresh Ghidra import
  was cancelled and removed from the workspace when the backend policy was
  clarified; no Ghidra output entered any ledger.

## Invalidation decision

The previous repository targeted 1.06 (`3,039,232` bytes), not 1.06a. Its
addresses, Ghidra inventory, names, origin classifications, match units,
matching reports, character tables, and subsystem documents were removed from
the current authority set. Existing source remains available only as an
unverified hypothesis corpus. Git history preserves all former tracked work.

## Next bounded work

Choose a small high-confidence 1.06a leaf outside obvious import/runtime code.
Reconcile its exact boundary and origin, recover ABI/callers, then test whether
a retained source implementation is semantically applicable. The first
canonical exact unit should establish the real VC8 profile before broad source
migration.

Do not start with character-wide dispatchers, network stacks, or LTCG-heavy
class families. Do not populate aggregate architecture notes from old 1.06
addresses.

## Routine checkpoint

```bash
python3 scripts/verify-target.py
python3 scripts/check-ida-mcp.py
python3 scripts/validate-tracking.py --require-target
python3 scripts/build.py --check
python3 scripts/progress.py --check
python3 scripts/ci.py
git diff --check
```
