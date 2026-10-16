# CPU source ownership and dispatch recovery

The active target remains `Fighter_update_default_cpu_action_policy @ 005F1F80`,
15910 callable bytes in the SHA-pinned original Japanese1.06a executable.
This checkpoint changes two source properties in `CpuActionPolicies.cpp`.
The whole function remains nonexact; no exact or partial credit is recorded.

## Observed signed policy dispatch

RTTI-backed Fighter vtable slot+58 identifies five distinct CPU entries. Each
loads policy word+766 with `MOVSX EAX`, before an unsigned upper-range branch.
The four specialized roots are comparison surfaces here; their complete
candidate boundaries and source bodies are not promoted by this audit.

| Vtable owner | CPU entry | Signed policy load | Policy0 entry |
| --- | --- | --- | --- |
| Default, eleven roster owners | `005F1F80` | `005F3DE1` | `005F47B0` |
| Reimu | `0048D390` | `0048FBEE` | `0048FC0C` |
| Marisa | `004B4070` | `004B6941` | `004B695F` |
| Alice | `004F4B80` | `004F75A5` | `004F75C3` |
| Aya | `006126E0` | `006145BB` | `00614F8A` |

The default source switch now reads `__int16`, matching the observed sign
extension and the existing signed-short header/Ghidra field. No physical
layout or ABI changes. In an isolated signed-selector control, the complete
relocated16521-byte section tail differs in exactly one byte: candidate
`005F3A54` changes B7 to BF, turning MOVZX into MOVSX. This is a code-generation
contract correction, not a claim of a newly discovered gameplay failure.
Both versions send negative policy words to the default arm: their extended
unsigned values exceed100. Nonnegative words have the same extended value.

## Observed action300 write ownership

The target has two stores to control+6BC: `005F22F4` and `005F2315`.
The first belongs to the closed counter interval10..90 and clears controls
+6B4/+6B8. The second writes facing/1 to those controls. Between the paths,
`005F230B CMP AX,90` / `JL` preserves an explicit second lower-bound guard.

The preceding source hoisted the +6BC store before its inner branch and used
only `counter>90` there. The source now keeps the two writes in their observed
arms: closed10..90, then otherwise>=90. Counter90 takes the first arm. Values
below10 take neither; values above90 take the second. Values, widths, calls
and call order are preserved. This recovers observed store/branch ownership
without claiming unique original C++ syntax.

The action300 candidate grows from24 instructions/116 bytes to29/138, versus
30/141 in the target. Its remaining differences include a folded unsigned
subtract/range test where the target retains two signed WORD comparisons,
and a different register for facing. It is not an independently exact owner.

## Cross-family observation and source hypothesis controls

Raw policy0 traversal at the default and Aya entries closes1486 instructions /
4879 bytes in each, including shared return tails. Instruction pairing verifies
all non-control bytes, control opcode/width forms, **321 internal destinations**
by instruction correspondence, and **37 external selector-call targets**.
The other specialized regions have1488,1413 and1432 reachable instructions
respectively; these counts alone establish no equivalence.

The default/Aya correspondence supports shared source or copied logic as an
inference. It does not prove an original inline helper or another callable
boundary. A private, real716-line selection helper control tests that hypothesis:
ordinary inline leaves a non-target E8 call; forced inline produces exactly the
same complete16521-byte relocated section tail as the signed-selector-only
monolithic control. Therefore that partition does not explain its residual.
The helper and all proposed source partitions are discarded.

A structured four-quadrant policy0 control retains14/41 diagnostic owners and
changes physical suffix layout without a new identical owner; it is discarded.
No compiler flag, header, shared type, relocation ledger or TU partition changes.
No assembly, copied code bytes, source stubs or shaping locals are introduced.

## Focused verification and remaining work

The final configured source passes these complete-return native controls:

| Controls | Differences |
| --- | ---: |
| Counter/mode/facing and signed-policy boundaries | 0/1408 |
| Existing whole-root finite matrix | 0/5000 |
| Policy0 roll0..99 matrix, all1486 target instructions visited | 0/16000 |
| Existing finite/NaN height matrix | 0/368 |

The1408 boundary controls use action300, counters-32768/-1/0/1/9/10/11/89/90/
91/92/32767, modes0..3, both facings and the eight existing MT seeds (768 cases).
Another640 use action201, policy words-32768/-32767/-1/0/18/19/99/100/101/32767,
timers-32768/0/1/32767, both facings and those seeds. Peer action100 bypasses
common attacks; persistent controls start at1/-1. Action300 uses policy-1 so
later policy output cannot conceal its stores. The native dependencies execute
without result hooks, and comparison includes the actor, MT state, calls,
conversion inputs, stack and x87 control word through the genuine RET.
Boundary input SHA-256:
`ca6517c2df8f5e0f0d22dc16a7cf22d2776cfcddf82ae8396d5df9524327ea7a`.
Reports and private input-generation recipes use `build/cpu-inline-` and
`.analysis/cpu-inline-20261017/`. The existing matrices remain reproducible via:

```bash
python3 scripts/build.py --unit gpt-web-default-cpu-action-policy --compare --json
python3 scripts/audit-giant-action-owners.py default-cpu-action-policy build/match-units/GptWeb_DefaultCpuActionPolicy.obj --unit gpt-web-default-cpu-action-policy --json
python3 scripts/audit-cpu-policy-paths.py build/match-units/GptWeb_DefaultCpuActionPolicy.obj
python3 scripts/audit-cpu-policy-paths.py build/match-units/GptWeb_DefaultCpuActionPolicy.obj --selection-cases
python3 scripts/audit-cpu-policy-paths.py build/match-units/GptWeb_DefaultCpuActionPolicy.obj --height-cases
```

The fresh whole15910-byte comparison still fails at **+12E /005F20AE**,
targetF0 / candidate29. Candidate metadata is at **+3E38** and its section tail
is16553 bytes; the target first table remains+3E28. The comparison-window hash is
`af511b4feecaa98f3b601749f9e3456a299a2fa22b720105c284833a7ee49566`.
All previous14 identical diagnostic owners survive; policy100 also becomes
identical as its former alignment instruction disappears, giving15/41.
These are internal diagnostic owners, not separately accepted functions or
byte credit. The source still has unresolved range lowering, register lifetimes
and physical shared-tail placement. Instruction coverage and sampled native
agreement do not establish full numerical/gameplay/exception equivalence.

Direct Ghidra re-attests the executable, entry point, Windows/x86 target,
mapped text and callable hash. It saves/reads back comments at the signed load,
action300 guard and policy0 correspondence. The fresh readback also verifies
that field+766 is signed16, beyond merely checking its two-byte width. Target
bytes and the ECX/no-stack ABI remain unchanged. Java exits before the verified
private project replaces its working predecessor; temporary copies and probe
objects are removed. Only this nonexact root is rebuilt; no aggregate cold
replay or unrelated accepted-unit replay is claimed.
