# AyaObject evidence index

Start with the [current handoff](RE_HANDOFF.md). Update root `0x61A290` uses
[AyaObjectActionState.cpp](../src/characters/AyaObjectActionState.cpp), selected
at game-source checkpoint `e24fb73`, SHA256
`4272f7f5d30499822931f9a70f7b52e179e6d99732e7d21962f58a6cfdef0472`.
The callable ledger remains 19,522 bytes; the full canonical emitted payload is
20,132 bytes with metadata at 19,664, SHA256
`a5dc22f5c6f0e93a3fc81592510327c5708c8c4d41938f2bd96eaf7947523ede`.
Fresh configured comparison remains **nonexact at +0x22**, target `0F` / source
`9B`. This is the initial JA displacement, not a metadata-pointer difference.
No local window or behavioral audit accepts the whole root.

## Selected source and scoped audits

| Record | Result and limit |
| --- | --- |
| [826 owner-Y lifetime](AYA_OBJECT_826_OWNER_Y_LIFETIME_2026_10_23.md) | A used double Y spans alpha and restores the target 37-byte interval. 2,584 strict native cases agree; 13 canonical bytes change within 19 bytes. 4,438 outside-action graph nodes and 807's 26-byte window are preserved. |
| [807/854 read lifetimes](AYA_OBJECT_807_854_READ_LIFETIMES_2026_10_23.md) | 3,968/3,840 actual-code cases agree; outside-action graphs preserve 4,464/4,481 nodes. |
| [807 angle lifetime](AYA_OBJECT_807_ANGLE_LIFETIME_2026_10_23.md) | Exact local 26-byte interval and live angle across alpha. The later read-lifetime report supersedes its historical sequence-read deficit. |
| [861 phase scope](AYA_OBJECT_861_PHASE_SCOPE_2026_10_23.md) | Phase/count advance only in initial sequence 0, eliminating 2,304 predecessor state differences. Its 768 alpha/X write-order differences remain an explicit scoped limit. |
| [903 paths and frame transitions](AYA_OBJECT_903_PATHS_AND_FRAME_TRANSITIONS_2026_10_23.md) | 13,596 paired cases cover all ten sequences, actual frame/block calls and twelve masked x87 control words. Effects and alpha/gate/timer read epochs agree. Scoped non-spawning evidence, not complete gameplay or whole-root equality. |
| [801 fade snapshots](AYA_OBJECT_801_FADE_SNAPSHOTS_2026_10_22.md) | Selected alpha correction; 3,012 sequence-read differences remain. |

Earlier selected 804/810 sequence, 821 counter and 903 fade corrections remain
in source. Their dated records and other action/initializer history are linked
from the [preceding handoff](RE_HANDOFF_HISTORY_2026_10_23.md).

## Unselected context and source controls

| Record | Result and limit |
| --- | --- |
| [Size profiles](AYA_OBJECT_SIZE_PROFILES_2026_10_23.md) | Current-source `/O2 /Os` and `/O1` produce the same 18,180-byte payload, but lose stack alignment and differ at +0x4. Keep configured `/O2`. |
| [Joint CIL replay](AYA_OBJECT_JOINT_CIL_REPLAY_2026_10_23.md) | Consistent update/init owner plus twelve native providers. Full update replay consumes 362 HIGHLOW fields and seven switches; selected and shared CIL payloads equal their native counterparts. Three math providers remain nonexact. Not DLL execution or original TU proof. |
| [861 shared tails](AYA_OBJECT_861_SHARED_TAIL_CONTROLS_2026_10_23.md) | Target 861 joins 826 phase/fade blocks. Candidates pass 5,168 position and 3,072 phase cases but lose 807's second zero-sequence read in 2,456 cases. A replayed CIL example preserves that rejection. |
| [852 RTM/fenv](AYA_OBJECT_852_RTM_AND_FENV_CONTROLS_2026_10_23.md) | RTM keeps unresolved conversion shapes. Its two objects pass 6,528 scoped native cases but change other-action instructions. Local fenv retains FIMUL; explicit if/else is byte-neutral to the int control. |
| [801/852 controls](AYA_OBJECT_801_CONTEXT_852_FACING_CONTROLS_2026_10_23.md) | Caching loses 807's recovered interval, including a retry after 826's fix. 852 early promotion and branch-local conversions remain open. |
| [Runtime owner context](AYA_OBJECT_RUNTIME_CONTEXT_2026_10_23.md) | Four layered/direct/typed/virtual controls were byte-neutral in the earlier `17585ff8...` payload epoch. Nominal class and lifecycle remain open. |

The old joint-CIL eight-byte change belongs to an earlier source epoch. The
current complete replay is byte-neutral against the current native caller.
Likewise, old reports' “current” hashes and suggested next steps do not override
live selection. Negative controls exclude their tested context, not all possible
source or compiler contexts.

## Resume and recover

Use unit `gpt-web-aya-object-vslot28-full-root` for a fresh strict comparison.
Keep 807's repeated read when trying shared 826/861 source. New 852 trials need
independent visibility/lifetime evidence; the tested RTM/fenv/branch spellings
do not establish an LTCG impossibility. Rebase every trial onto selected source.

Latest completed private scope: `build/aya-size-profile-20261023/`; preceding
scope: `build/aya-joint-cil-20261023/`. Their frozen inputs and receipts remain
loose. Older reports may need restoration from gzip or per-scope archives;
consult [artifact recovery](ARTIFACTS.md). Private flow-alignment diagnostics
remain incomplete and are not acceptance evidence.
