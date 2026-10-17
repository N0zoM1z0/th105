# Iku frame-4 constant lifetime and event ownership

The complete `Iku_dispatch_action_state_vslot28 @ 620920` now expresses
action 305's deceleration gate as `frame >= 4`, matching the target's actual
comparison. This restores its shared constant lifetime and separates the
305/696 event sites. Whole-root canonical comparison remains **nonexact at
+0x64**, with no exact or partial authored credit.

## Target observations and selected change

Target remains original Japanese TH10.5 1.06a, executable SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Root `[620920,62EFBE)` is 59,038 bytes / 15,132 instructions, SHA-256
`abc831c6ccd95986bed811694f532ad8c8b92cb49702a7f6ce4de100b8a73dea`.

The target's action-305 interval `[6240DE,624174)` is 150 bytes, SHA-256
`dc00b2d909fdbde5b04ab0055d591c3a4f27c72327e39bfa3b4e3ad8dd4aa305`:

```text
6240F5  MOV EBX,4
6240FA  CMP WORD PTR [ESI+140],BX
624101  JL 624134                 ; skip deceleration below frame4
        ... decelerate, advance and possible action callback ...
624156  CMP WORD PTR [ESI+140],BX
62415D  JNE 62EFB6
624163  PUSH 29
624165  MOV ECX,ESI
624167  CALL 4359F0
```

The previous source's equivalent `frame > 3` emitted an immediate-3 test,
then a separate immediate-4 event test. The candidate merged the latter
event/return tail with action 696, leaving 40 physical event sites versus
41 target sites. Changing only this signed-short predicate to `>= 4` now
keeps 4 in EDI across the intervening real calls and uses DI in both tests.
Target uses EBX/BX, so action 305 itself remains nonexact. No dummy local,
register forcing, ABI change or altered gameplay condition is introduced.

Current event calls have incoming sets `{305}` at candidate `624157` and
`{696}` at `62D5BA`, matching the target's independent sites `624167` and
`62D7D4`. Action 696's complete 180-byte physical owner now passes the
instruction/edge diagnostic. It is an internal root interval, not a new
callable or independently accepted exact function.

The other missing ordinary-call site is now isolated to advancement:
target 310/409 have separate calls `624612`/`625893`; candidate shares one.
Both target and candidate reload ECX after the landing predicate and before
their conditional branch. Candidate 409 jumps into the shared CALL, skipping
310's preceding receiver move. This is not evidence of special ECX
preservation. The actual height helper even overwrites its pushed ECX scratch
slot before POP ECX. No provider visibility or ABI declaration was changed.

A single direct Ghidra read-only clone re-attested imported/file identities,
entry, mapped `.text`, language/compiler and root bytes, then read back both
BX comparisons, the two target event calls and 409's receiver setup/branch.
Heap was limited to 768 MiB and CPUs to two; all nine primary database files
are hash-unchanged. Wrong-image IDA remained rejected and unused.

## Focused comparison and native evidence

Current source CRLF SHA-256:
`4e852076e88001c3989a9c65e28ab751dc2ec1d84fce64143e5fa23ca295a44a`.
Normalized full 59,550-byte section SHA-256:
`5e8c9caa835d0211a6b243fa96911445f03ba51aab9a9c7d2470942537b8af5c`.
The section grows 32 bytes. It contains 15,022 reachable instructions /
58,394 bytes in the same-sized callable span, no internal unreached bytes,
1,156 following alignment/metadata bytes, 130 RETs and 866 ordinary / 175
register CALLs. Target has 131 RETs and 865/177 CALLs. Tables remain 33/42/35;
no local CALLs or external tail transfers appear. Metadata begins at 58,396.

Owner diagnostics are **7/109**, adding 696 to 2/4/5/204/215/303. Frame 0x400,
84 natural payload homes, 182 spawn calls and 190 action-site records remain.
Conditional action/physical-ordinal pairing retains 84 singleton/bijective
constraints, 57 identity, without issues. Candidate pre-epilogue coverage is
14,762 PCs / 16,894 states; target 14,870 / 16,959. These are static storage
correlations, not payload-value or feasible-path proof. The 412/418 common
landing calls and the six-action effect site's incoming set remain intact.

The public `--event-exits` fixture runs the actual whole entry for 305/696:
frames 2/3/4/5, timers -1/0, sequences 0/1, both PC53/PC64 control words and
velocities 0.25/0.5/1/quiet NaN. **0/256 differences; all cases reach real
RET**. Both target event PCs are required to be visited; 141 target-root
instructions are covered. Actual helpers execute without result replacement.
Native/configured objects normalize identically over all 59,550 bytes.

Input SHA-256:
`ed52445cfedd693f25f1fd406039beeb9aa5beda56235958fcbf0ebdcf459ff6`.
Target-output SHA-256:
`89d039ad0598a2d04d6625d3cc889638d942a0e956af578054903c9ef9941b57`.
The wrong `event-frame-gate` control changes only this gate to `>= 5` and
detects **24/256 differences**, all in 305; both target event sites still
execute. This is focused path evidence, not arbitrary event-registration,
callback, whole-root or exception equivalence.

An unselected RTM compiler control used the preceding source `83311acf`
at commit `3e7c71c`: same 59,518-byte section and 15,008 instructions, but
7,145 normalized bytes differ from SP1 and the first target mismatch is still
+0x64. Swapping RTM alone does not resolve that checkpoint. Its compiler/tool
hashes and complete report remain local; no canonical profile was changed.

```bash
python3 scripts/build.py --unit gpt-web-iku-action-state --compare --json
python3 scripts/probe-iku-upper-actions.py --event-exits --output build/IkuEventNative.obj
python3 scripts/probe-iku-upper-actions.py --event-exits --control event-frame-gate
python3 scripts/audit-iku-full-root.py --object build/match-units/GptWeb_IkuActionState.obj --native-object build/IkuEventNative.obj
python3 scripts/audit-iku-call-sharing.py --object build/match-units/GptWeb_IkuActionState.obj --partition-payloads
python3 scripts/audit-giant-action-owners.py iku-vslot28 build/match-units/GptWeb_IkuActionState.obj --unit gpt-web-iku-action-state --json
```

The strict comparison and wrong control intentionally exit 1. Local reports
are under `build/iku-event-ownership/`; private control/readback sources are
under `.analysis/iku-event-ownership-20261017/`. Earlier landing/effect/link/MT
results retain their recorded source hashes. No broad native matrix or
accepted-unit replay was needed: shared headers, ABI, profiles, partition and
relocations are unchanged. Remaining leads are 310/409 advancement sharing,
730's extra facing site and the effect argument join. Original source/TU/
optimizer provenance and full-root value/exception equivalence remain open.
