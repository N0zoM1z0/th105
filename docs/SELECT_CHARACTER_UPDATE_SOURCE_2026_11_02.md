# Complete CSelect character-selection policy

The complete 619-byte policy at 0x0041FC90 is now retained in ordinary C++ as
src/ui/SelectCharacterUpdate.cpp and in a reproducible candidate unit. The
partial-owner view is never constructed or allocated. It uses actual input,
setup and cursor fields, with offset/extent assertions; no private-register
calling convention, dummy stack lifetime or copied instruction implementation
is introduced.

A real prerequisite has changed since the private October27 investigation:
refresh_character at 41FB80 now has an independently accepted 258-byte source
body and ordinary two-int thiscall ABI. The exact 341-byte CSelect update-flow
at 4208E0 reaches this policy by E9 at 420A30. Both complete supporting bodies
are freshly rebuilt and verified by the public audit. The old cursor-pair,
array and lifetime spelling controls remain closed; they were not repeated.

## Full comparison and ownership

The unchanged generic authored-origin gate pins the whole619-byte native hash,
the exact caller tail edge and the skipped six-byte LEA EBX,[EBX] at41FCBA,
preceded by EB06 at41FCB8. Native and source each contain192 instructions,
191 reachable, and four RET0 paths at41FE2A/41FEB1/41FED7/41FEFA. All alignment
bytes remain compared, with no partial-body or displacement mask.

The entire source is still nonexact:25 unequal bytes, first at+36, associated
with the cursor induction base and corresponding offsets. Source SHA256:
537459e26772b9fb7aa85db0339011557c774ec435680fcd158fe12bd838f7c3.
Native SHA256:
a4bb43c20a44efc5f92ec5b027f9c52aa72fb633c1854f39090c8d62202d4e0c.
No matching credit is granted for correct length or bounded behavior checks.

## Policy and isolated checks

The source preserves separate player polling, locked-character skipping,
confirm-versus-cancel order, the unsigned button-option test, shared-input
cancellation behavior, independent game-mode queries, story preparation,
13/15-entry random selection and the final state/return policy. Its real local
cancelled[2] is used by the return logic, not a frame-shaping dummy.

The public audit compares native/source call receivers, arguments, selected
state fields, setup fields, cursor results, stack balance, callee saves and
full integer return values in twelve bounded cases:
idle; normal movement; locked-slot skipping; story confirmation; locked and
open VS-COM random selection; cancelling a prior confirmation; story cancel;
both players confirmed; shared and independent second-player cancellation;
and two game-mode queries returning different values.

Bool cursor returns carry nonzero unused upper EAX bits. Void helpers return
opaque EAX bits; ECX/EDX and arithmetic flags are clobbered. This checks actual
caller ABI use rather than accidentally granting zeroed or preserved registers.
All twelve native/source observations agree. All external helpers are observed
without executing them, and callbacks use the existing fail-closed guard.

A negative control changes only the candidate's initial cursor base from114
to100, superficially removing its first differing field. The observer rejects
its wrong cursor receiver before any helper executes. This illustrates why an
isolated byte patch is not source reconstruction. The altered bytes are only
a rejected test input, never an implementation or acceptance artifact.

Twelve target-independent structural/policy tests protect boundary, return,
alignment, random-range/flag, independent mode-query and shared-cancel checks.
These finite cases do not prove all behavior or execute gameplay, sound,
resource loading, actual helper bodies or OS operations.

## Reproduce and accounting

Use scripts/repo-python serially on CPU0/nice10 to build
exact-first-select-character-update, exact-first-select-update-flow and
exact-first-select-character-binding. Then run audit-select-character-update.py,
validate-tracking.py --require-target and ci.py. The candidate compare and
audit intentionally report mismatch; they cannot turn25 unequal bytes into
exactness.

Source-present rises1635 to1636, authored1654 to1655, mapped1822 to1823,
review301 to300 and units810 to811. Excluded stays2072. Exact authored remains
1429 /443911 bytes; no matches.csv entry is added.
