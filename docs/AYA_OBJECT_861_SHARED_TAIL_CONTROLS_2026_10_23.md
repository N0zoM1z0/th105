# AyaObject 861 shared-tail controls, October 23, 2026

The target really shares phase/fade code between actions 826 and 861. Tested
shared-source controls fix 861's position-write observations, but lose a
previously recovered 807 sequence read. None is selected. Game source remains
`e24fb73`'s 826 owner-Y correction; root `0x61A290` remains nonexact.

## Observed target ownership

All observations use original Japanese 1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
IDA preflight rejects the open database's different hash. Evidence below uses
the attested PE, ordinary serial VC8 builds and original-code execution.

The primary switch entries are 826 at `0x61C0B7` and 861 at `0x61D5E4`.
861's nonzero-sequence JNE at `0x61D5F2` targets `0x61C2A7`, the common
sequence-1 check. Its sequence-0 exit JMP at `0x61D745` targets `0x61C27E`,
the 41-byte phase/count block immediately before that check. The phase block
clears DWORD `+0x180` before WORD `+0x364`; its SHA256 is
`d608b139dd6f1669fef8c698db0d55282beca03769065ca6e6bde819d506062f`.

The common position interval at `0x61C2BA` is the already pinned 37 bytes:
commit X, load owner Y, update alpha, add 100, commit Y. This is a physical
shared target path, not a similarity inferred from neighboring source cases.
`target-facts.json` retains bytes, instructions, entries and both incoming edges.
Original source labels, helper definitions and TU partition remain unknown.

## Compiler controls

Adding the same used double Y snapshot to 861 as to 826 does not reproduce the
target schedule in the current duplicated source. VC8 merges the tails but
sinks alpha between the scale-X and scale-Y stores. Both old and new objects
still have 2,072 ordered-write differences in the 861 scale matrix. A float
snapshot also changes the 826 path and loses the 37-byte interval.

A second control writes the common fade/frame tail once, reached from both
cases. A further control also writes the shared phase block once, preserving
the initial-sequence-0 gate. These are source hypotheses following the observed
target edges, not recovered original C++ spelling. Neither uses extra state,
assembly, padding or a different calling convention.

| Control | Full bytes / metadata start | Canonical SHA256 prefix | Result |
| --- | ---: | --- | --- |
| Selected source | 20132 / 19664 | `a5dc22f5c6f0e93` | Retained; 861 ordering still pending |
| Duplicate double snapshot | 20124 / 19656 | `f99517d05a974b8f` | Alpha sinks into scale stores |
| Duplicate float snapshot | 20132 / 19664 | `d884af74f6e345ae` | 826 changes too |
| One shared fade tail | 19880 / 19412 | `41ad07c7310de195` | Position cases agree; 807 reload lost |
| Shared phase and fade tails | 19884 / 19416 | `a9858165c48c3056` | Same 807 reload loss |
| Shared fade tail, single-case switch | 19880 / 19412 | `4459939a77a923b4` | Still hoists EBX=1 |
| Shared phase/fade, unsigned 807 snapshot | 19880 / 19412 | `1f3ccf3771fbca2a` | 807 strict audit fails |
| Shared phase/fade, tiny 807 getter | 19884 / 19416 | `a9858165c48c3056` | Byte-neutral to that control |
| Shared phase/fade, getter at second zero guard | 19884 / 19416 | `a9858165c48c3056` | Byte-neutral too |

The two getter controls emit no new call. In contrast, an ordinary inline
position-update method remains a local call and blocks canonical replay with
an unknown helper target. No target address is fabricated for it. This bounds
that ordinary compilation attempt; it does not prove LTCG is necessary.

SP1 `/Ob1` produces the same complete canonical and `0x800000`-rebased payload as the
shared-phase/fade control. Local compiler file versions are 14.0.50727.762
(SP1) and 14.0.50727.42 (RTM). Native RTM compilation succeeds and produces
19,888 bytes / metadata 19,420, SHA256
`8dca43274971d9c04a3964f91fe846d38c5c236efc3d0888744e5b24f57cad68`.
It retains the 807 reload deficit. This is native evidence only; it does not
validate RTM GL/PDB compatibility or identify the original compiler minor
release. Rich build 50727 alone does not distinguish these local toolchains.

Full hashes, compiler/source pins and reproducible environments are in
`controls-canonical.json` and `compiler-controls.json`. All profiles were private
controls; no shared compiler setting or match-unit profile changed.

## Execution results and selection limit

Both shared-tail forms agree with target in 5,168 actual-code position cases:
2,584 per action. This includes ordered actor writes, live x87 snapshots at
X/alpha/Y and scale stores, frame calls, final actor/parameter bytes, status
and tag, eight masked control words and owner-Y raw-bit boundaries. The
predecessor has 2,584 write/snapshot differences for 861, while 826 stays equal.
The common 37-byte interval and 807's 26-byte angle interval each occur once.

The shared forms also pass all 3,072 nonzero-sequence phase cases: no phase/count
writes, no state differences and no old alpha/X reorders. The shared-fade form
passes the default 6,216-case 853/861 scale audit. These matrices do not cover
arbitrary resources/owners, complete sequence-0 random/spawn behavior,
callbacks or unmasked exception delivery.

However, 807's strict audit fails. Its explicit scoped mode runs all 3,968
cases and finds **2,456 sequence-read differences**, with no other recorded
differences and all 688 live-angle snapshots preserved. The shared-phase form
and native RTM form retain the same deficit. At the first sequence-1 example:

| Code | WORD13E read instructions before retirement |
| --- | --- |
| Target | CMP at `0x61A791`, CMP at `0x61A7AE`, MOVZX at `0x61A853` |
| Selected source | CMP, CMP, MOVZX |
| Shared source | CMP, MOVZX |

The second independent zero-sequence check is folded away. Thus preserving an
exact angle interval does not preserve the already recovered read trace.
Tiny getters at the final capture or missing guard do not change the complete
shared-phase payload. This identifies the specific compiler/source interaction;
it is not a demonstrated game-state bug or evidence for adding volatile fields.

Strict outside-861 graph comparison stops at the new early `MOV EBX,1`.
Private relational exploration accounts for some constant-one forms and typed
normal calls, but is incomplete. The first shared form also exchanges the two
826 sequence-0 clear stores; the explicit shared-phase form changes zero-register
handling. No full other-action equivalence is claimed and no strict checker is
weakened. These issues and the 807 regression keep every control unselected.

## Strengthened action-specific interval evidence

`audit-aya-object-scale-adds.py --position-lifetimes` now supports 826 and 861
and records actual visits to each 37-byte interval start. Global byte
counts alone are insufficient: the predecessor contains one copy for 826,
yet 861 executes it **zero times** in all 2,584 cases. Both shared controls
execute the one common copy once per case for each action. Strict mode requires
those per-action hits as well as matching observations and the literal interval.
The original default 853/861 scope is unchanged.

The 807 auditor now includes examples of missing sequence reads in its existing
scoped mode; default strict assertions remain unchanged. Selected source was
restored and freshly compared: full canonical SHA256 remains
`a5dc22f5c6f0e93a3fc81592510327c5708c8c4d41938f2bd96eaf7947523ede`,
19,522-byte comparison nonexact at `+0x22`, target `0F` / source `9B`.
No new authored exact credit or aggregate cold replay.

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py --unit gpt-web-aya-object-vslot28-full-root --compare --json
taskset -c 0 nice -n 10 python3 scripts/audit-aya-object-scale-adds.py --actions 826 --position-lifetimes
# Selected861 is intentionally diagnostic: its interval hit count is zero.
taskset -c 0 nice -n 10 python3 scripts/audit-aya-object-scale-adds.py --actions 861 --position-lifetimes --diagnostic
```

Private artifacts are under `build/aya-861-owner-y-20261023/`; frozen CPPs,
formal/native receipts and the per-object registry retain their source epochs.
Completed variants may be in its SHA-verified `completed-controls.tar.gz`;
consult `retention.json`, restore repository-relative members with `-C .`.
The partial `.analysis/` flow exploration is not acceptance evidence. Future
work needs a supported context preserving 807's second zero-sequence check
while closing shared-tail effects; the now-working native RTM compiler also
allows a separate test of 852's still-unresolved promotion/conversion shape.
