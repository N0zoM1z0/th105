# Iku common surface-restoration exit

The complete `Iku_dispatch_action_state_vslot28 @ 620920` now recovers one
shared surface-height/velocity-clear exit with exactly the target's 17-action
incoming set. Whole-root canonical comparison remains **nonexact at +0x64**.
This is source/control-flow recovery, with no exact or partial authored credit.

## Observed target and selected source

Target remains original Japanese TH10.5 1.06a, executable SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Root `[620920,62EFBE)` remains 59,038 bytes / 15,132 instructions, SHA-256
`abc831c6ccd95986bed811694f532ad8c8b92cb49702a7f6ce4de100b8a73dea`.

Both target calls have the same independently propagated incoming set:
`6,7,8,9,220,307,308,309,404,406,414,415,416,417,795,797,798`.
The complete 28-byte interval `[621042,62105E)` has SHA-256
`b0fcfb774191eee614e6b89906fb53bceb319a4c6028dc9a1b16cffb22cf0d9b`:

```text
621042  MOV ECX,ESI
621044  CALL 435D60             ; actual surface height in ST0
621049  FSTP DWORD PTR [ESI+F0]
62104F  MOV ECX,ESI
621051  CALL 45AF40             ; actual velocity/acceleration clear
621056  ... RET
```

The selected source directs those terminal paths to
`restore_surface_and_return`, preserving their preceding action/sequence
callbacks. For 797/798, the target explicitly writes X=480/800 after the
callback and before jumping to `621042`; source retains that order. The
target loads these attested float literals from `6C0578`/`6C3B38`, stores X,
then enters the common height lookup. Coordinates are not cached across a
callback that can change the object.

404/406 previously completed restoration inside the private forced-inline
fan routine. That routine now reports whether restoration is pending, and
the two callers join the common continuation on that actual status. Its
three ground callers 400/401/402 retain their completed behavior. This is an
internal source-organization choice: no original callable boundary or return
ABI is claimed for the helper. All helper work remains inlined, with no local
CALLs; public ABI, class layout, vtable and external declarations are unchanged.
No fake external return, padding or register constraint is introduced.

The current candidate height/clear calls at `62ECBE`/`62ECCB` have exactly
the target incoming set. Physical placement and other call-sharing groups
still differ. A private label-inside-case8 control retained that set but put
the calls near the end anyway, grew the section by 32 bytes to 59,510 and
remained nonexact at +0x64. It is unselected; the simpler common continuation
is retained. This does not prove a particular optimizer pass or LTCG barrier.

## Current whole-root diagnostics

Source CRLF SHA-256:
`c9a1c3e4715f18e19991fd7d5b19239fda5b482b1b1beaa4d6c13c41b867bda6`.
Normalized full 59,478-byte section SHA-256:
`ec153b60cb6f2d40487e486a25c78d619efcd901ae01291d9c1c7b88f3a361f6`.

The section is 72 bytes smaller. Candidate CFG closes 15,000 instructions /
58,318 instruction bytes in a 58,321-byte callable span, with three internal
alignment bytes and 1,157 following alignment/metadata bytes. Metadata starts
at 58,324. There are 128 RETs, 862 ordinary / 178 register CALLs, no local
CALLs or external tail transfers, and 33/42/35 switch entries. Target has
131 RETs and 865/177 CALLs. Physical-owner diagnostics remain 7/109; frame
0x400, 84 natural payload homes and 57/84 identity correlations remain.
All 84 conditional action/physical-ordinal constraints are singleton and
bijective, without issues. Candidate pre-epilogue coverage is 14,744 PCs /
16,900 states; target 14,870 / 16,959. Storage correlations are not value proof.

Other per-callee target/candidate counts differ: advancement 107/106,
height 19/18, velocity-clear 30/28, facing 9/10. Expanding ordinary calls by
possible incoming action leaves only action730's five facing sites versus
four. A matching incoming set or total does not establish path feasibility,
argument values or exact bytes. Earlier 412/418 and six-action effect groups
remain intact.

## Focused native scope

The selected source passes **0/3,252** whole-entry cases for the 17 actions
and affected ground callers 400/401/402. Both sides execute real preludes and
helpers. Each side reaches 2,566 RETs and 686 genuine first backend entries:
13 effects, 511 action changes, 8 next-sequence, 120 sequence selections and
34 objects. Coverage is 2,040 target-root instructions. The native/configured
objects normalize identically across all 59,478 bytes.

Input SHA-256:
`7956f11502132f4c117c895ca299901d0227b9d7bf74dd8c9557e357f0ed8b0b`.
Target-output SHA-256:
`f9bf99b08e2f1b9cd433a4928c6e2a0ff6c2950085fdec353f06f512ddeddf86`.
An input-matched 404/406 subset control reverses the new caller status tests
and detects **186/284 differences, 93 per action**. It changes source only;
genuine helper results and returns are not replaced.

For landing paths that first enter an action/sequence callback, the native
probe stops before that callback. It therefore does **not** execute the
subsequent common height/clear tail. Accepted tail/order/incoming-set facts
are static target evidence, not post-callback runtime proof. The bad-status
control detects erroneous restoration on normal completed paths. Broader
callback/exception behavior remains unknown.

A single direct Ghidra read-only clone independently re-attested imported/
file identities, entry, mapped `.text`, language/compiler and root bytes,
then read back/hash-checked the complete shared tail. Heap was limited to
768 MiB and CPUs to two; all nine primary database files are hash-unchanged.
Wrong-image IDA remained rejected and unused.

```bash
python3 scripts/build.py --unit gpt-web-iku-action-state --compare --json
python3 scripts/probe-iku-upper-actions.py --all-actions --actions 6 7 8 9 220 307 308 309 400 401 402 404 406 414 415 416 417 795 797 798 --output build/IkuCommonSurfaceNative.obj
python3 scripts/audit-iku-full-root.py --object build/match-units/GptWeb_IkuActionState.obj --native-object build/IkuCommonSurfaceNative.obj
python3 scripts/audit-iku-call-sharing.py --object build/match-units/GptWeb_IkuActionState.obj --partition-payloads
python3 scripts/audit-giant-action-owners.py iku-vslot28 build/match-units/GptWeb_IkuActionState.obj --unit gpt-web-iku-action-state --json
```

Strict comparison intentionally exits 1. To reproduce the negative control,
copy current source below `build/`, negate only the two
`if (middle_ground_air_fan(404/406))` conditions, then use `--source` with
`--all-actions --actions 404 406`. Reports are under `build/iku-common-landing/`;
small control/readback sources remain under `.analysis/iku-common-landing-20261017/`.
Older native/link checkpoints retain their source hashes. No broad accepted-
unit or cold aggregate replay was needed; shared interfaces/profiles and
relocations stay unchanged. Initial constant lifetime, physical layout,
remaining argument/call sharing and original source/TU provenance remain open.
