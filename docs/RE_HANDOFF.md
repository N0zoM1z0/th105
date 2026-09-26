# Current reconstruction handoff

This page is the current work queue. The former 1,811-line rolling handoff is
preserved in [the dated history](RE_HANDOFF_HISTORY_2026_09_26.md); its old
"active", "paused", and "next" instructions are historical checkpoints.
The tracking ledgers and fresh target comparisons override prose.

## Target and state

- Target: original Japanese TH10.5 v1.06a, SHA-256
  `56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
- Current ledger summary: 4,023 provisional candidates, 1,476 authored,
  1,388 source-present, 1,315 exact functions / 220,094 exact bytes in 494
  units. These are snapshot counts, not a substitute for
  `scripts/report-reconstruction-status.py --summary`.
- Bounded root: `YoumuObject_initialize_action_entry @ 0x00543670`, reviewed
  callable `[0x00543670, 0x00544A97)` (5,159 bytes). Source:
  `src/characters/YoumuObjectActionEntry.cpp`; probe unit:
  `gpt-web-youmu-object-action-entry`. Its source is present but the complete
  function remains canonically **nonexact**; `matches.csv` has no credit for it.
- The exact local target file passes `scripts/verify-target.py`. The attached
  IDA MCP currently exposes a different executable (SHA-256 beginning
  `10350095`), so its preflight fails. Do not use that database for target
  observations or writes. The current Youmu evidence comes from hash-checked
  PE bytes and a focused VC8 comparison. No Ghidra result was accepted.

## Current Youmu evidence

The target's 29-entry main action switch and four-entry action-901 sequence-6
switch are both validated by raw target bytes. The latter dispatches at
`0x0054464F` through table `0x00544BD4`; its case-0..3 destinations are
`0x00544692`, `0x0054467E`, `0x0054466A`, `0x00544656`. Target traversal
reaches **5,159/5,159 bytes** with no unresolved indirect exit. This is
control-flow closure, not a claim of original TU ownership. See
[the table and boundary evidence](YOUMU_OBJECT_ENTRY_SWITCH_CLOSURE_2026_09_26.md).

The latest single-core SP1 probe keeps all 29 destinations unsplit and
matches **6/30** instruction-and-internal-edge diagnostic owners including
entry. Reversing the four action-901 source arms to physical target order
3, 2, 1, 0 reduces that owner's difference blocks from **4 to 3** without
changing its 597-byte span. The 5,159-byte canonical window still first
differs at `+0x80` (`0x005436F0`); that operand points into the shifted
candidate main switch table. Its current compared-window SHA-256 is
`0b174356a268e762184a61f94774ae9af698df7af1ae230a548e055594de1acb`.
An RTM `/O2` object reproduces the prior SP1 window, and both tested `/GL`
visibility variants emit a prologue unlike the target. Those are negative
diagnostic probes, not proof that all LTCG contexts have been excluded.

The largest known local ownership inversion is action 820 versus 850:
target spans **12/57**, candidate spans **26/37**. Target action 820 writes
`+0x184 = 1` then jumps to the tail at `0x00543DA7`; action 850 writes two
2.0f scales immediately before that tail. The candidate places the tail in
action 820 and makes 850 jump backward. Source-order reversal and duplicated
tail probes regress; a natural virtual call is byte-neutral. The missing
source lifetime/TU condition is unknown. Other nonidentical owners and call
operand scheduling remain; the +0x80 mismatch does not imply only one fix.

## Next bounded step

Investigate a source-backed discriminator for the 820/850 tail placement or
another specific nonidentical owner. Compare target and candidate
instructions/edges before retaining a source change. Keep temporary probe
objects and private analysis under `build/` or `.analysis/`; preserve ordinary
C++ and the VC8 x86 ABI. Do not infer exact credit from owner scores, equal
sizes, or a different compiler profile.

Focused reproduction, with one compiler process pinned to one core:

```bash
python3 scripts/verify-target.py
python3 scripts/check-ida-mcp.py
python3 scripts/report-reconstruction-status.py --summary
python3 scripts/validate-tracking.py --require-target
taskset -c 2 python3 scripts/build.py --unit gpt-web-youmu-object-action-entry --compare --json
python3 scripts/audit-giant-action-owners.py youmu-object-action-entry \
  build/match-units/GptWeb_YoumuObjectActionEntry.obj \
  --unit gpt-web-youmu-object-action-entry --json
```

Before committing any finished edit, run `python3 scripts/ci.py` and
`git diff --check` in that worktree. Re-run both after further edits. Do not
run concurrent VC8 builds or launch multiple Ghidra processes. Accepted
shared-header/layout changes require replay of affected exact units; aggregate
exact totals require a cold `python3 scripts/verify-exact-units.py --all`.

For the earlier common Fighter `0x004740C0` root, consult
[the focused handoff](COMMON_FIGHTER_HANDOFF_2026_09_12.md) and
[the later sequence-join evidence](COMMON_FIGHTER_SEQUENCE_JOIN_EVIDENCE_2026_09_26.md).
Its latest tested source remains **53/66** diagnostic owners and whole-root
nonexact at `+0x14`; it is pending while Youmu is the selected bounded root.
