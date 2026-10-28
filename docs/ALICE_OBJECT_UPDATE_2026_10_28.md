# AliceObject complete update, 2026-10-28

AliceObject_update_action_state @ 004FCAB0 now has a complete manual source
hypothesis for 38 primary actions and the default. Whole canonical replay is
**nonexact**. Structural agreement does not earn exact-byte credit.

## Target observations

Canonical Japanese 1.06a SHA256 is
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Raw RTTI owns slot28 through vtable6C4B54, cell6C4B7C, COL6DA328 and
TD6E81F8 AliceObject. The adjacent accepted initializer50C1C0 is unchanged.

Callable [4FCAB0,50BDF6) is 62278 bytes, SHA256
`363a5bbe7c9294389e5a6ddad319d2b0ffd628b5f821155b24516047476edf03`.
14945 instructions decode; 14944 instructions / 62271 bytes are reachable.
The sole seven-byte padding range is [4FE2E9,4FE2F0). Native has 120 RET0s,
134 virtual calls and 424 direct calls to 28 distinct targets, without outgoing
tails. ESP alignment is 8 and the frame allocation is 0x348.

Complete payload [4FCAB0,50C1C0) is 63248 bytes, SHA256
`b293547ae355c58990d6bdb38fb5c1e26bb199556aa123a9dfb4a8b7dc0e00b0`.
18 table dimensions are 39,7,6,7,7,11,5,6,11,7,15,23,6,7,4,6,4,5.
Remaps at50BE94/50C0A4/50C11C have 200/25/35 bytes. Two-byte8BFF callable
alignment, three-byte8D4900 at50C0BD and NOP at50C13F are independently covered.
No initializer or inter-function padding is claimed.

## Source and evidence limits

The local IDA preflight lacked its pinned MCP runtime; that session was not
used. Factory-native th105-ida was independently re-attested at20:42 UTC with
canonical metadata, entry68B9D2, mapped entry bytes, inventory and46 exposed
operations. Decompilation supplied navigation hypotheses only. Raw instructions,
operand widths and whole target comparison decide the retained evidence.
No target bytes or database metadata were changed.

The receiver is a pointer-only view, not an allocation layout claim. Motion
uses this+4, wave uses owner348, and all four indexed4359F0 calls use owner348.
The three early4359D0 calls in815/816 use this; distinct receiver declarations
preserve the established callee ABI. ST0 sine/cosine/square/atan2 results omitted
by decompilation are represented explicitly. Signed and unsigned fields,
callback-sensitive reloads, genuine packet arrays and observed guards are kept.
849 and858 ignore the advance result before their frame-entry checks.902 uses
float dx/dy/radius and has no invented zero guard. Scalar lifetime and exceptional
floating-point equivalence remain unresolved, not asserted by a successful build.

The first complete source exposed an unsupported double0.02 hypothesis. Raw
literal operands instead establish float0.02 in831/834/852/855/858. Correcting
those widths allowed complete relocation replay. That first candidate was63052
bytes with one extra call each to435D60,45C030 and64CCB0. The selected source
represents817 phase1/10's actual shared ground-impact continuation, with two real
packet arrays and a pointer selected by the branch. This restores all direct-call
counts without inert storage, fake aliases, copied bytes or assembly.

## Selected complete replay

`scripts/repo-python scripts/build.py --unit exact-first-alice-object-update --compare --json`

Selected complete payload is62960 bytes, SHA256
`64ed3752a3efde280ad84dbd8d242e7ee518e0df6501ba3a66c0162e04f0df8d`.
First mismatch is +37 /4FCAD5; 58935 unmasked positions differ including length.
Frame348, all28 direct-callee counts (424 calls), all18 table dimensions and all
260 remap bytes agree. Candidate126 returns/138 virtual calls differ from native
120/134. Stack homes, shared tails and floating-point scheduling remain open.
No normalized comparison, partial case or structural count receives exact credit.

Audit: `scripts/audit-alice-object-update.py`.
Receipts: `build/frontier-4fcab0-20261028/{formal-build,full-audit,target-audit}.json`.
Private preparation: `.analysis/frontier-4fcab0-20261028/`.
Only source and mapping advance; matches.csv is unchanged. Dedicated aliases do
not alter existing consumers. No shared ABI, compiler profile or accepted source
changed, so unchanged accepted receipts remain incremental and no corpus rebuild
was required. The focused replay and default repository CI gate this checkpoint.
