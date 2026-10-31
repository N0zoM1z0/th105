# Shared front-card action gate: complete source, nonexact

The existing CommandGates.cpp implementation at494450 is now explicitly tracked
as authored/source-present. No source rewrite is made. The950-byte native body
closes all305 decoded instructions and eight RET4 exits, SHA-256
48bf68351997deff88cd0dced8ffd5884cb99b38a056d59eba3ea4a273f4e140.
Fourteen exact roster input-policy roots directly call it. All14 edges are
independently replayed and pinned by the origin rule; a fresh Reimu caller
rebuild passes6952 callable bytes and the entire7008-byte switch payload.

## Complete policy

The helper first checks the action-window entries for690,691 and695 through
the checked command tree, preserving iterator owner/end checks. Front-card
ids100..199,0 and1 respectively select those actions when the window and current
state permit. It then checks696 for id2 and the signed state150..157 range,
followed by692/693/694 for ids3/4/5. Eligible paths pack the current fighter
phase and call virtual set_action, returning1. The exhausted policy returns0.
The initial window argument is retained for every command comparison.

The current source is already a complete950-byte candidate but is not exact.
Fresh canonical replay fails first at494498 (+72), on register ownership in
the first command-value/window comparison. The earlier signed-range and
saved-window lifetime controls documented in KNOWLEDGE_BASE.md remain closed
negative evidence. No new range spelling, dummy lifetime, register constraint,
assembly or flag search is attempted; equal size does not confer byte credit.

## Validation and scope

The root is added to the existing cross-v106a-command-gates-family unit, which
now intentionally has a mixed result. Its eight existing selected peers freshly
pass117/258/164/50/504/333/226/226 bytes. Their source and compiler settings are
unchanged. Reimu's full caller/payload replay and target-backed direct edges
establish application ownership independently of the nonexact callee.

Receipts under build/frontier-front-card-gate-20261031: formal.json,
ownership.json, reimu.json and reimu-payload.json. No global corpus rebuild.

Only source/ownership totals change: source1779, authored1799, mapped1806,
excluded1783, review445 and units762. Exact1580/448995 remains unchanged.
