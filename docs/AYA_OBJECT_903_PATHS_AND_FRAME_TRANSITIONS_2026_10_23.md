# AyaObject 903 paths and real frame transitions

Current selected source passes 13,596 paired original-code cases across all ten
903 sequences, including real frame/sequence helper calls and twelve masked
x87 control words. No effect or recorded read-epoch difference was found.
This extends the earlier sequence-2/3 audit; it does not resolve the root's
remaining physical sharing and canonical differences. Game source is unchanged.

## Target and execution contract

Only original Japanese 1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. Target/status/tracking checks pass. IDA rejects the open database's
different hash; evidence uses the attested PE and a freshly rebuilt native
object for `AyaObject_update_action_state_vslot28` at `0x61A290`.

New tool: `scripts/audit-aya-object-903-paths.py`. It reuses the guarded original
math/animation fixture and preserves the old focused 2/3 auditor. Target and
candidate enter their actual roots, use the target Aya vtable and return
normally. Stack cleanup and saved registers are checked. Unknown code, writes,
callback errors and instruction-budget exhaustion reject execution. Helpers
execute their original instructions; no returns or trigonometric values are
fabricated. The lookup table still comes from original initialization at PC53,
with SHA256 `c134fa85e7988574c2db386dc8e14de2113d6e465c18f4503bd265219c5ca898`.

The resource model has ten valid sequence blocks and zero textures. Changing
WORD frame timer `+0x142` across `-1,0,2,3,32767`, with limit 3, exercises both
ordinary frame increments and the virtual dispatch threshold. Target executes
8,828 calls to frame dispatcher `0x4351C0`, 1,320 to frame step `0x45C1A0`, and
348 to next-block `0x45C220`. These are observed calls, not a count of successful
sequence changes. There are no prefix-only or synthetic returns in this run.

## Matrix and observations

| Sequence | Paired cases |
| --- | ---: |
| 0 / 9 | 1080 each |
| 1 / 6 | 408 each |
| 2 / 3 | 648 each |
| 4 / 5 | 1062 each |
| 7 | 3432 |
| 8 | 3768 |

The matrix includes owner health/action/sequence gates, initial/fading states,
WORD364 signed boundaries, WORD384/BYTE184 wrap boundaries, alpha saturation
and retirement gates, facings -1/1, coordinate/scale/angle raw-bit boundaries,
and the velocity/floor combinations in sequence 7. Heading arguments remain
finite. Sequence 9 deliberately avoids random/spawn paths.

The initial eight-control-word pass omitted PC24. The final matrix adds
`0x007F/0x047F/0x087F/0x0C7F` to the existing PC53/PC64 rounding variants.
All twelve masked settings pass. This is a tested comparison environment, not
an assertion about the game's global control word or lookup initialization.
Private earlier 8-word reports retain their own source/input epoch.

Compared observations include actor/parameter bytes, ordered writes, calls,
final x87 status/tag, and the value, preceding write count and live x87 state
at byte alpha `+0x113`, WORD gate `+0x364` and DWORD timer `+0x144` reads.
Empty physical x87 slots are excluded. The report pins the object, mapped
payload, generated input matrix and auditor/fixture source hashes.

The 14-byte target alpha/store interval at `0x61E829` must occur once and must
actually execute in the fading cases. For each of sequences 2 and 3, target
and selected object execute it in 192 cases and skip it in the other 456.
Thus an unrelated copy of the bytes cannot satisfy this dynamic check.

## Negative controls and source visibility

The frozen pre-recovery object from `aya-903-shared-fade-20261022/previous.obj`
has no final-effect differences in the same 13,596 cases, yet is rejected:
192 alpha-read epoch differences and 192 missing interval visits per fading
sequence. Its literal interval is absent. This separates final-state agreement
from the recovered timing constraint. An injected failure in the actual timer
read callback at `0x4351C8` is stopped and rethrown, rather than accepted as RET.

A new ordinary in-class `update_faded_color(unsigned char)` control puts the
three existing alpha/green/blue stores behind one source-visible helper used
by the common fade path and sequence 8. It adds no state or virtual slot.
The complete canonical and `0x800000`-rebased payloads are identical to selected
code; there is no new root call or sharing-layout improvement. This control
remains unselected. Earlier lexical fallthrough/retirement controls are in the
[placement report](AYA_OBJECT_903_TAIL_PLACEMENT_CONTROLS_2026_10_22.md).

## Selected state and limits

Root remains nonexact at `+0x22`, target `0F` / source `9B`. Full payload is
20,132 bytes, metadata starts at 19,664; canonical SHA256 remains
`a5dc22f5c6f0e93a3fc81592510327c5708c8c4d41938f2bd96eaf7947523ede`.
The callable ledger size remains 19,522; no 903 subfunction boundary or authored
exact credit is added. Headers, ABI, compiler profile, partition and relocation
contracts are unchanged; no accepted-unit replay or aggregate claim is made.

Arbitrary resources, other heading inputs, full spawning/callback behavior and
unmasked exceptions remain unproven. Physical fade/color/retirement ownership
still differs. This audit supports the tested behavior and read lifetimes;
it does not prove original source spelling or an LTCG/native impossibility.

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py --unit gpt-web-aya-object-vslot28-full-root --compare --json
taskset -c 0 nice -n 10 python3 scripts/audit-aya-object-903-paths.py
```

The canonical build is expected to exit nonzero. Private scope is
`build/aya-903-read-epochs-20261023/`: positive/negative execution receipts,
callback fault receipt, raw target blocks, frozen CPPs and helper-control pins.
Partial exploratory probes under `.analysis/` are historical inputs, not the
new public auditor's acceptance path.
