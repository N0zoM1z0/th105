# Application startup options: exact default construction

## Observed target and ownership

Only the original Japanese TH10.5 v1.06a executable was used, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
`0x00407BB0..0x00407BE6` is a complete 54-byte callable, with 20 reachable
instructions, no calls/branches, plain RET and ten following INT3 bytes.
Its SHA-256 is
`72856b953cdcdc8976f9a2eae4ec39a90e75bf8e7c94803aad0cb462aa59e76a`.
ECX is the receiver and EAX returns the same pointer. Ordinary VC8 C++
construction reproduces that contract and all 54 bytes without relocations.

The raw WinMain body `665810..665AC7` calls it at `6659B6` on a stack value,
then writes the created HWND, HINSTANCE and two callback-object pointers into
that value. WinMain passes its address to application bootstrap `407DA0` at
`665A6A`. Bootstrap copies exactly ten dwords into receiver+8 and consumes the
same window/instance, callback and subsystem fields. These application call
sites establish authored ownership independently of compiler matching. The
canonical exact origin baseline now owns the accepted constructor row; neither
the caller nor bootstrap receives exact or source-present credit here.

## Recovered layout and remaining hypotheses

The complete value is 0x28 bytes. No vptr, destructor or EH path is observed.

| Offset | Target use | Default |
| --- | --- | --- |
| `00`, `04` | HWND, HINSTANCE populated by WinMain | null |
| `08`, `0C` | graphics initialization option words | zero |
| `10` | audio initialization option word | zero |
| `14` | primary application callback object | null |
| `18` | initial callback selector | zero |
| `1C` | optional secondary callback object | null |
| `20`, `21`, `22` | graphics, DirectInput and audio gates | true |
| `23` | IME context/candidate-window setup gate | false |
| `24` | cursor visibility; false reaches ShowCursor(0) | true |
| `25`, `26`, `27` | further byte options; detailed roles unresolved | false |

Bootstrap calls the independently exact DirectInput initializer `40D360`
under flag21. The flag23 path calls `40E780`, whose target instructions reach
ImmGetContext and ImmSetCandidateWindow; shutdown releases that context
through the imported ImmReleaseContext thunk `66B82A`. Flag27 is normalized
into global `7028D8`. The graphics private receiver boundary and exact option
meanings are not inferred from Ghidra's argument guesses. Signedness of the
three zero-default option words and initial selector also remains unresolved;
unsigned source storage is a compatible layout hypothesis, not a recovered
original spelling. Callback pointers retain opaque types in this bounded unit.

## Source, database and canonical acceptance

`src/platform/ApplicationStartupOptions.hpp` defines real option members and
layout assertions; its companion `.cpp` supplies ordinary default assignments.
No existing accepted source/header, compiler flag or relocation mapping changed.
Build and compare only this unit:

```bash
python3 scripts/build.py --unit cross-v106a-application-startup-options --compare --json
python3 scripts/audit-candidate-boundaries.py 0x00407BB0 --json
```

The formal report `build/application-startup-options-formal.json` is
**canonical exact 54/54**, including the complete COFF section tail. There are
no relocation fields to mask or replay. The function, source-present and exact
ledgers advance together; candidate boundaries are independently closed first.
No full-unit replay is needed for this isolated addition.

Direct Ghidra inspection attested executable SHA, image base, entry/external
entry marker, x86 Windows analysis identity and every mapped .text byte before
exporting constructor/caller/bootstrap hypotheses. The database initially had
no function at this constructor address; bounded disassembly and function
creation were required. The accepted constructor name, thiscall contract,
zero stack purge, self return and 40-byte option structure were saved and read
back in a fresh read-only process. Private exports and Java scripts remain
under `.analysis/application-startup-options-20261016/`; logs stay under
`build/application-startup-ghidra-*.log`. Each Ghidra process used a 768 MiB
heap and two active processors. The failing IDA hash preflight was not used
for analysis, and no factory adapter was used.

The self return and caller lifetime support a source-level constructor;
original class/TU spelling remains unknown. The unreconstructed WinMain and
application-bootstrap bodies are useful next callers, without accepted claims.
