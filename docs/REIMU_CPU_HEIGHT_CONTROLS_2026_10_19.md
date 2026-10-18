# Reimu CPU height and lifetime controls, 2026-10-19

The15999-byte CPU root at48D390 remains nonexact. No source, ABI, compiler
profile, relocation contract or exact ledger changes in this checkpoint.
The new exceptional-height matrix passes0/20200 with genuine target helpers.
Source controls fail to recover the remaining sharing/register choices.

## Target observations and limits

Original Japanese1.06a executable SHA256 remains
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Callable `[48D390,49120F)` SHA256 remains
`3bd363994e140603ae0ec249ffd3a36b1ae0448e72a389e417c4cc7a6d113e2d`.
The next owner begins491450, after the target's four metadata tables.

Raw instructions establish these distinct facts:

- PUSH EBP48D4D3 / MOV EBP,2 at48D4D4 follows the peer-word174 guard.
  EBP retains2 across the returning body. There are126 explicit EBP
  references, including52 restoring POPs. EDI receives400 at48D4D9.
- The selected source instead materializes2 in ECX,400 in EDX and600 in EDI
  near the primary switch. It does not use EBP. No artificial constant local
  or register-forcing operation is introduced to imitate the target.
- The self-air policy0 path compares the same peer-height field at490720
  (FCOM) and490731 (FCOMP), with TEST AH,44 at490728/490739 and JP at
  49072B/49073C. This is evidence of two comparisons, not proof of a unique
  original if/else spelling or floating-point environment setting.

## Unselected compiler/source controls

All controls start from selected source SHA256
`1d121503b98277c808727f58af725f13642dfe5ab78ee91bb03aa32b283876d5`,
saved privately as `build/reimu-cpu-controls/Baseline.cpp`. The ordinary VC8
SP1 options and existing five real callee bindings are used throughout.
Table mapping covers the actions/policy regions; policy0 is separately
traversed to closure with only selector calls, no unresolved indirect exits
or internal calls. These are candidate diagnostics, not whole-root equality.

| Control | Prefix / payload bytes | Root selector / RET sites | Reachable policy0 instructions / selectors / RETs | First strict difference |
| --- | --- | --- | --- | --- |
| Selected baseline | 15920 /16461 | 118 /48 | 1385 /34 /46 | +12E |
| Ordinary input helper | 15920 /16461 | 118 /48 | 1385 /34 /46 | +12E |
| Four independent height cases | 16432 /16973 | 124 /55 | 1484 /40 /54 | +12E |
| Independent peer cases within self-height branches | 16212 /16753 | 126 /56 | 1481 /42 /54 | +12E |
| Floating-point environment access | 16044 /16585 | 118 /48 | 1396 /34 /46 | +2 |
| Target | 15999 callable; metadata to49144D | 121 /52 | 1488 /37 /50 | — |

Root site counts are decoded physical-prefix counts; policy0 counts are
reachable CFG counts. Similar instruction totals do not establish terminal
membership or equality.

**Ordinary input helper:** replace22 adjacent button2/horizontal/vertical
write groups with an ordinary `static inline` function taking the actual
owner, button reference and two input values. It performs exactly those
three writes in their existing order and inlines naturally. The entire
canonical16461-byte payload is unchanged:
`07cb7a406e5c136ccd25e97287419f58e7b8b7eaccd502af81e0cb811fbac091`.
This specific helper shape does not explain the lifetime difference.

**Independent height predicates:** separate the four height-state bodies
using real zero/nonzero field tests, then try the narrower independent
peer-height tests inside the two self-height branches. Existing decision
bodies and terminal labels are retained. Both variants still omit EBP and
produce payloads ending4915DD/491501, past the next owner. They are rejected
before execution; no runtime equivalence is claimed. Their canonical hashes
are respectively
`29724906d7cf4fa7d3348ee9b624f5bc8805cce9b4c43822963569ed93cefb4a`
and `84e457e446fb5cb28d2281b2d67c43d450f20bbdb661c979911733a8035752be`.

**Environment access:** prepend only `#pragma fenv_access(on)` to the
baseline. Stack allocation changes from target12 to16 bytes, giving the
first mismatch at48D392. It also ends491459, nine bytes into the next owner.
Canonical hash is
`52172170b8a0c7d41efe5f4537cdcdd7676fba49690b23e1519cfaf3bba88276`.
It is not executed or selected. This rejects this pragma-only explanation;
other original source/TU/lifetime contexts remain unknown.

**Typed-output follow-up:** replace43 raw `_DWORD` accesses to the existing
6B4/6B8/6BC/6C0/6C4/6C8/724 members with those typed members, preserving
their actual32-bit write widths and values. The entire canonical16461-byte
payload remains07cb7a40, including all primary and policy code. The existing
typed member declarations are not changed. This particular mixed-access
spelling does not explain EBP allocation or terminal sharing and remains an
unselected cleanup. Fresh focused baseline/source-control receipts are under
`build/reimu-cpu-fields/`. A new read-only Ghidra attestation under
`.analysis/reimu-cpu-fields-20261019/` again leaves all nine DB files unchanged
and removes its alias. No extra native replay is needed for byte-identical
code; earlier execution retains its recorded scope.

Private generated inputs, objects, disassembly, table packets and closed
policy0 profiles remain under `build/reimu-cpu-controls/`. Do not repeat
these unchanged controls without new evidence. No fake callee bindings,
forced registers, assembly, padding or fabricated terminal operations are
used.

## Exceptional-height execution

`--y-position-cases` uses the existing101 real MT seeds for actual policy
rolls0..100, two facings and ten finite height pairs, at selfX100/peerX190.
For each vector it substitutes either selfY or peerY with qNaN7FC00000,
sNaN7F800001, positive infinity, negative infinity or negative zero. This
gives20200 input vectors; substitutions can duplicate numerical cases.
The native target independently confirms every predicted policy roll.

Four positive controls use seed35, roll30, facing1 and base heights100/0:

| Overridden input | Target final policy / timer | Genuine selector limits |
| --- | --- | --- |
| selfY qNaN or sNaN | 11 /35 | 1000,100,30 |
| peerY qNaN or sNaN | 0 /40 | 1000,100,60 |

The auditor checks these target outputs before candidate comparison. The
candidate then agrees on the entire7A4-byte actor prefix, full MT state,
call order/arguments/results, actual80-bit conversion inputs and existing
stack/control-word checks. All20200 paths pass. No helper result is injected.
These observations do not prove unmasked exception equivalence, exhaustive
numerical coverage or an exact match.

Reproduce the selected ordinary object and new matrix with:

```bash
python3 scripts/build.py --unit gpt-web-reimu-cpu-action-policy --compare --json
python3 scripts/audit-cpu-policy-paths.py \
  build/match-units/GptWeb_ReimuCpuActionPolicy.obj --root reimu --y-position-cases
python3 scripts/ci.py
git diff --check
```

The focused strict comparison intentionally remains nonzero at+12E/48D4BE.
No cold aggregate replay or new exact function/byte is claimed.

Read-only direct Ghidra re-attests imported identity, entry, full mapped text,
root bytes and typed metadata. All nine primary DB file hashes agree before
and after; the temporary alias is removed. The CPU0/384MiB recipe is under
`.analysis/reimu-cpu-controls-20261019/`. Required IDA preflight rejects its
wrong PE; no IDA semantics or factory adapter is used.
