# Iku frame-7 boundary recovery

The complete `Iku_dispatch_action_state_vslot28 @ 620920` now spells two
signed frame predicates as observed in the target: action 225 uses `<= 7`,
and action 408 uses `>= 7`. Their previous `< 8` and `> 6` forms have the same
signed-short behavior, but generated different comparisons. Whole-root
canonical comparison remains **nonexact at +0x64**; no exact credit is added.

## Observed predicates

Target is original Japanese TH10.5 1.06a, executable SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Root `[620920,62EFBE)` remains 59,038 bytes / 15,132 instructions, SHA-256
`abc831c6ccd95986bed811694f532ad8c8b92cb49702a7f6ce4de100b8a73dea`.

| Action | Target comparison and signed branch | Meaning |
| --- | --- | --- |
| 225 | `62325C CMP WORD PTR [ESI+140],7`; `623264 JG 623306` | Only frames <=7 can reach the time-modulo-5 periodic effect. |
| 408 | `625759 CMP WORD PTR [ESI+140],7`; `625761 JL 625775` | Subtract 0.75 from horizontal velocity starting at frame7, then apply the separate zero clamp. |

Both selected predicates now produce the same immediate-7 comparison and
branch polarity in the candidate. Neighboring 320/321/322 gates were also
inspected: their target `>1`, `>3` and `>5` forms already agree with the source
and remain unchanged. This is target-specific source recovery, not a rule
for mechanically rewriting equivalent integer comparisons.

A single direct Ghidra read-only clone independently re-attested imported
and file identities, PE entry, mapped `.text`, language/compiler and root
bytes, then read back both comparisons/branches and the prelude's constant-1
definition. Heap was limited to 768 MiB and CPUs to two. All nine primary
database files are hash-unchanged. Wrong-image IDA remained rejected and
unused; no target bytes or database metadata were changed.

## Fresh focused verification

Current source CRLF SHA-256:
`0e8c5e26d3bdf5849b00f7a684a217d75ef8aec30c608990e3377ce6f8ae3593`.
Normalized complete 59,550-byte section SHA-256:
`9843aea7c1d1cd156ac68422212313c86c38cb9d37f913db8c449a3c9d2fb207`.

The current root has 15,021 reachable instructions / 58,394 instruction bytes
in a 58,394-byte callable span, no internal unreached bytes, and 1,156 following
alignment/metadata bytes. Metadata starts at 58,396. There are 130 RETs,
866 ordinary / 175 register CALLs, no local CALLs or external tail transfers,
and 33/42/35 switch entries. Owner diagnostics remain 7/109, including 696;
these are not independently accepted matches. Frame 0x400 and all 84 natural
payload homes remain. Conditional action/physical-ordinal correlation still
gives 84 singleton/bijective constraints, 57 identity, without issues.
Candidate pre-epilogue coverage is 14,761 PCs / 16,893 states; target remains
14,870 / 16,959. These counts do not prove payload values or feasible paths.

The public `--frame-bounds` fixture passes **0/512** through each side's own
entry and genuine helpers. It covers frames 0/1/6/7/8/9/14/15. Action 225
varies times -5/0/1/5, both facings, PC53/PC64 and actual MT seeds 1/119;
408 varies timer -1/0, sequence 0/1, both control words and velocities
0.25/0.75/1/quiet NaN. Each side reaches 96 real effect entries, 16 real
object entries and 400 RETs. Coverage requires the actual target comparison,
modulo/continuation and subtraction PCs; 164 target-root instructions are
visited. Native/configured objects normalize identically over all 59,550 bytes.

Input SHA-256:
`293a58708c1f4008a06b98e89c744d7f9d37fd4e6e5018b36f6cbc79b28cdb07`.
Target-output SHA-256:
`7ec11852d0cb3999878c7c6078774c05683aa88d2a80d0ab3a7fd298490ace14`.
The `frame-bound-gates` control changes 225 to `<= 6` and 408 to `>= 8`,
detecting **48/512 differences: 24 per action**. No helper result or return
is injected. Paths after the first real effect/object backend remain outside
this native scope. Earlier event, landing and broader native results retain
their recorded source hashes; they were not routinely replayed.

## Prelude compiler-context controls

The first difference is still target `MOV EDI,1 @620984`, after 100 identical
bytes. The inspected range tests and countdown decrement already agree with
the source. The new predicates do not resolve the initial constant hoist.

On the preceding source `4e852076` at commit `557597a`, a private `/Z7` build
produces **all 59,550 normalized bytes identical** to the ordinary candidate
(SHA-256 `5e8c9caa835d0211a6b243fa96911445f03ba51aab9a9c7d2470942537b8af5c`).
Embedded debug information alone does not explain that checkpoint's code.
The separate `/Zi` attempt failed with PDB-manager error C1902 and produced
no usable comparison. On-disk compiler/PDB components report SP1 .762;
the active PDB-manager failure is not diagnosed. Do not treat it as an
optimizer result or infer original debug flags merely from the target's
CodeView/PDB record. Canonical profiles and installed tools are unchanged.

```bash
python3 scripts/build.py --unit gpt-web-iku-action-state --compare --json
python3 scripts/probe-iku-upper-actions.py --frame-bounds --output build/IkuFrameBoundsNative.obj
python3 scripts/probe-iku-upper-actions.py --frame-bounds --control frame-bound-gates
python3 scripts/audit-iku-full-root.py --object build/match-units/GptWeb_IkuActionState.obj --native-object build/IkuFrameBoundsNative.obj
python3 scripts/audit-iku-call-sharing.py --object build/match-units/GptWeb_IkuActionState.obj --partition-payloads
python3 scripts/audit-giant-action-owners.py iku-vslot28 build/match-units/GptWeb_IkuActionState.obj --unit gpt-web-iku-action-state --json
```

The strict comparison and wrong control intentionally exit 1. Reports are
under `build/iku-prelude-constant/`; the small source patch/readback script
is under `.analysis/iku-prelude-constant-20261017/`. No shared header, ABI,
compiler profile, partition, relocation or accepted-unit ledger changed.
Initial constant lifetime, remaining shared call/argument placement and
original source/TU/optimizer provenance remain unresolved.
