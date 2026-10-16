# Application message loop: canonical 177/177

## Observed target

Only original Japanese TH10.5 v1.06a was used, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The complete callable `408120..4081D1` closes **177 bytes / 65 instructions**
through a plain RET, without gaps or indirect/outgoing branch exits. Fifteen
following INT3 bytes separate it from the next candidate. Body SHA-256:
`a500c264bce3ac16d238d6b6e34b29ab3ce54552a482947e87cd4134a5473ef8`.
Source-present WinMain calls it at `665A78` with singleton `702820` in ECX.
The receiver's running byte +4C is the same byte cleared by exact shutdown.
That application lifetime and the game-owned device-reset policy establish
authored ownership, separate from the compiler comparison.

## Complete behavior and ABI

The function creates an unnamed, initially unsignaled automatic-reset event,
then loops while running+4C is nonzero. A native 28-byte MSG value supplies the
real stack frame. PeekMessageA uses flags0; if a message exists, GetMessageA
removes it. A zero return exits; any nonzero return follows TranslateMessage
and DispatchMessageA. The source preserves the target's zero-only test.

The idle path queries device `7036C0` through TestCooperativeLevel vslot+0C,
when the device exists, and stores HRESULT at `703844`. That cell is the
already modeled D3DBackend+1A4 at base `7036A0`. If the result equals target
literal `88760869`, reset helper `414A10` is called. The helper first checks
backend globals, with no required incoming register receiver or stack argument.
The idle path then calls WaitForSingleObject(event,4). The function closes its
local event on every normal exit, including an initially false running flag.
CreateEvent failure is not guarded in the target or reconstructed source.

All seven imports were independently named through the PE IAT. Four new import
entries plus a dedicated +1A4 result-field mapping are added; existing aggregate
addend permissions remain unchanged. The HRESULT lies in the PE loader-zero
virtual tail, rather than initialized file bytes. The comparator's PE reader
attests that zero-fill explicitly. No shared source/header/compiler flag changes.

## Reproduction and accepted state

```bash
python3 scripts/build.py --unit cross-v106a-application-message-loop --compare --json
python3 scripts/audit-candidate-boundaries.py 0x00408120 --json
```

`src/platform/ApplicationMessageLoop.cpp` produces **177/177 canonical exact**
over the complete callable and complete COFF section tail. The first source
probe already matched after target-pinned relocation resolution. The formal
report is `build/application-message-loop-formal.json`; all ten DIR32 fields
and the one reset-helper REL32 field replay with zero differences. Compiler
loop alignment supplies the target's one NOP naturally. No extra stack local,
manual instruction, fake return or ABI adjustment is used.

Mapping, source-present and exact rows advance together. The generated origin
baseline for this one newly matching row is updated after target attestation,
checking unchanged earlier rules/rows and absence of any exclusion-rule overlap.
Unchanged library fingerprints are preserved; no full exact-unit replay is run.
The WinMain caller remains nonexact at its previously documented frame homes.

Sequential direct Ghidra sessions independently attest executable SHA, image
base, entry/external-entry marker, x86 Windows analysis identity and every
mapped .text byte before saving the function, thiscall/void caller-view contract,
ECX receiver and zero purge. A fresh read-only session verifies metadata and
whole-body SHA. Scripts stay under
`.analysis/application-message-loop-20261016/ghidra-scripts/`; logs stay under
`build/application-message-loop-ghidra-*.log`. Each process uses768 MiB heap and
two active processors. No failed IDA session or factory adapter is used for
analysis. Original application type/TU spelling and unused receiver-prefix
fields remain unknown; no complete class-size claim is made.
