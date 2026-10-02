# TH10.5 reconstruction handoff

This is the short operational handoff as of 2026-10-02. The live ledgers and
fresh canonical comparisons override dated prose. Older checkpoints are in
[the October archive](RE_HANDOFF_HISTORY_2026_10_02.md),
[the September archive](RE_HANDOFF_HISTORY_2026_09_26.md), and the focused
evidence notes linked below. Their former "current" and "next" instructions
are historical.

## Target and live state

- Target: original Japanese TH10.5 v1.06a, SHA-256
  `56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
  Never substitute 1.06 or a localized executable.
- Last checked ledger census: **4,023 provisional candidates**, with
  **1,502 authored / 1,414 excluded / 1,107 in review**; **1,409 mapped**,
  **1,390 source-present**, **1,317 exact / 223,051 exact bytes**, and
  **495 match units**. These are ledger/status totals, not a fresh aggregate
  cold replay. Recompute before quoting them.
- `config/claims.csv` remains header-only. `implemented.csv` means source
  present, and only `matches.csv` plus a reproducible canonical 100% unit
  supports exact credit. Candidate size and disassembler analysis do not prove
  function ownership or a compiler boundary.
- The local target passed `scripts/verify-target.py`. The attached IDA MCP
  still reported SHA-256 beginning `10350095` at this handoff, so its data
  cannot be used. Hash-attested raw PE analysis remains available. Existing
  direct Ghidra working databases under `.analysis/` were independently
  checked for target identity, entry and mapped `.text`; re-attest each
  database before a new bounded analysis unit. Do not use the factory adapter.

Run the preflight in [AGENTS.md](../AGENTS.md) before changing reconstruction
state. The source tree predates the corrected target; retained source is a
hypothesis until 1.06a instruction, ABI and comparison evidence support it.

## Active reconstruction lead: Iku Fighter vslot +0x28

`Iku_dispatch_action_state_vslot28 @ 0x00620920` has a hash-attested complete
callable `[620920,62EFBE)`: **59,038 reachable bytes**, **15,132 instructions**,
131 returns, three compressed action switches, and no unreached bytes or
external direct jumps. The target body has 4,676 x87 instructions and no
`FSINCOS` or `FRNDINT`. The attested Ghidra decompilation drops some reachable
blocks and remains a private hypothesis. The root is **identified and
declaration-only**, with no source-present or exact claim. See
[the boundary and action map](IKU_VSLOT28_BOUNDARY_ACTION_MAP_2026_10_02.md).

Target-to-target comparison of Iku actions 0–10 against Youmu established
shared helper topology but different constants and x87 zero lifetime; see
[the opening comparison](IKU_OPENING_ACTION_TARGET_COMPARISON_2026_10_02.md).
Actions 565–568 occupy 8,390 consecutive physical bytes and each has 14
static object-818 spawn call sites. They share cross-case tails; 567/568 add a
descending stage-crossing path. See
[the object-818 family evidence](IKU_565_568_OBJECT_818_FAMILY_2026_10_02.md).
The tracked `scripts/audit-iku-object-818-family.py` reproduces its diagnostic
JSON from the exact PE without a cached action-map report:

```bash
python3 scripts/audit-iku-object-818-family.py
```

Next, recover the remaining action families, payload semantics, helper ABI,
x87 lifetimes and shared-tail conditions from target instructions. Select
natural VC8 C++ only after those facts support it, then configure and compare
the complete root. TH08's VC7 inline `FSINCOS` is only a technique reference;
it does not establish an assembly requirement here, and this repository
forbids assembly for forced comparisons.

## Other bounded nonexact leads

| Target | Current evidence and blocker |
| --- | --- |
| `Youmu_dispatch_action_state_vslot28 @ 0x00530200` | Source-present 37,692-byte root; latest canonical first mismatch `+0xCA`, 31/98 diagnostic owners. Physical return sharing, float lifetimes and TU context remain open. [Latest controls](YOUMU_SHARED_ZERO_RETURN_AND_CONTROLS_2026_10_02.md). |
| `AyaObject_update_action_state_vslot28 @ 0x0061A290` | Source-present 19,522-byte root; still nonexact at `+22`, with unresolved action-903 fade-tail/x87 scheduling and other cases. [Latest controls](AYA_OBJECT_903_FADE_TAIL_CONTROLS_2026_10_02.md). |
| `AyaObject_initialize_action_entry @ 0x0061F0B0` | Source-present 4,531-byte root; 11 target vslot+0x0C calls order `MOV ECX,ESI` before `PUSH EAX`, unlike the candidate. [Call scheduling](AYA_ENTRY_VSLOT0C_SCHEDULING_2026_10_02.md). |
| `YoumuObject_initialize_action_entry @ 0x00543670` | Source-present 5,159-byte root; nonexact at `+0x80`, with 6/30 diagnostic owners. [Load timing](YOUMU_OBJECT_ENTRY_LOAD_TIMING_2026_10_02.md). |
| `Fighter_update_common_action_state @ 0x004740C0` | Source-present 10,219-byte root; nonexact at `+0x14`, 53/66 diagnostic owners. [x87 and Ghidra audit](COMMON_FIGHTER_X87_AND_GHIDRA_2026_10_02.md). |
| `AnimationObject_prepare_render_transform @ 0x00435360` and `render_to_battle_scene @ 0x00435740` | Each candidate has the target size but differs in `FILD`/`PUSH EDI` scheduling; no exact claim. [Focused evidence](ANIMATION_RENDER_EDI_X87_SCHEDULING_2026_10_02.md). |
| `KomachiObject_emit_owner_gated_object_826_pair @ 0x005F9350` | Source-present 205-byte target, 203-byte candidate; call argument/register scheduling remains open. [Focused evidence](KOMACHI_PAIR_CALL_SCHEDULING_2026_10_02.md). |

Do not extrapolate a global VC8 flag, assembly need or LTCG explanation from
these local differences. Existing negative source/compiler probes are recorded
in the linked notes; repeat them only with new independent evidence. Recent
accepted exact anchors include
[fighter body collision](FIGHTER_BODY_COLLISION_2026_10_02.md) and
[three-axis sprite rotation](SPRITE_PIVOT_ROTATION_2026_10_02.md).
The separate origin/boundary review queue is documented in
[the focused review](ORIGIN_BOUNDARY_REVIEW_2026_09_26.md).

## Local state, artifacts and gate

The ignored `build/` directory was cleared for this handoff, including old
objects, reports, caches, a CI virtual environment, and downloaded reference
copies. Compiled object/link products and Python bytecode scattered in
`.analysis/` were also removed; private probe source and Ghidra databases
remain. Dated notes may name former `build/` report paths as reproduction
references; those files are absent until their commands are rerun. The pinned
official VC8 manual can be fetched and regenerated through
[the reference guide](VC8_REFERENCE.md). Private `.analysis/` Ghidra state and
`.tools/` compiler installations were preserved; neither is committed.
Do not treat an old ignored report as a current comparison. Use a fresh
focused build/comparison for any source change, and run affected accepted
units after shared contract changes. A reported aggregate exact percentage
requires a cold `python3 scripts/verify-exact-units.py --all` run.

Before committing any future source, ledger, script, test or generated-progress
change, run the mandatory local gate in the finished worktree:

```bash
python3 scripts/ci.py
git diff --check
```

CI is target-independent and may recreate disposable Python caches under
`build/`; remove them again if preparing a clean handoff. Inspect `git status`
before pushing: local commits were ahead of `origin/main` at this handoff.
