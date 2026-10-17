# Iku 412/418 shared landing continuation

The selected source for the complete `Iku_dispatch_action_state_vslot28`
at `0x00620920` now recovers the target's common landing exit for actions
412 and 418. Whole-root canonical comparison remains **nonexact at +0x64**;
this is control-flow recovery, with no exact or partial authored credit.

## Observed target and source change

The executable is original Japanese TH10.5 1.06a, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Root `[620920,62EFBE)` remains 59,038 bytes / 15,132 instructions, SHA-256
`abc831c6ccd95986bed811694f532ad8c8b92cb49702a7f6ce4de100b8a73dea`.

Both landing branches call the real velocity-clear helper, read the actual
ground height into ST0, store Y, select sequence 2 through primary vslot 0x0C,
and return. Raw target instructions and independent incoming-action
propagation give exactly `{412,418}` at all three physical call sites:

```text
626080  CALL 45AF40
626085  MOV ECX,ESI
626087  CALL 435D60
62608C  FSTP DWORD PTR [ESI+F0]
626092  MOV EAX,[ESI]
626094  MOV EDX,[EAX+C]
626097  PUSH EBX                 ; EBX = 2
626098  MOV ECX,ESI
62609A  CALL EDX
62609C  ... RET
```

The common 36-byte interval `[626080,6260A4)` has SHA-256
`c46175161659e3e669e488aeeba2c592e609edb4589a177cb7f690241841fd5f`.
Action 418's JNZ at `627256` enters **the CALL at 626080**: its own preceding
`MOV ECX,ESI` supplies the receiver. Action 412 falls through its receiver
setup at `62607E`. Do not move the branch destination back two bytes merely
because that looks like the start of a source statement.

Previously, the candidate kept 412's landing calls separate while 418 joined
201/567/568's different tail. The source now branches from the two existing
positive landing tests to `land_and_select_sequence2`, containing their real
common operations. Every operation and its order are retained. There are no
new callable helpers, field/type/ABI changes or artificial return values.
This represents observed sharing; original use of a source label is unknown.

The new candidate has exactly `{412,418}` at its clear/height/sequence calls,
at `627216`, `62721D` and `627231`. Their instruction encodings/register
choices still differ from the target. Shared continuation recovery does not
establish whole-root path or value equivalence.

## Fresh focused results

Selected `src/characters/IkuActionState.cpp`, CRLF SHA-256:
`83311acff214f472e5ac77a191b83de68dfdcf89d22ed6151bf5909c0de14181`.
Canonical full section SHA-256:
`34adadd7903312c7193469e059924c9214c67f61b67307363a36b357d064418d`.

| Diagnostic | Current candidate | Target |
| --- | ---: | ---: |
| Full candidate section | 59,518 bytes | Callable extent 59,038 bytes |
| Reachable instructions / bytes | 15,008 / 58,362 | 15,132 / 59,038 |
| Callable span | 58,362 bytes | 59,038 bytes |
| Internal unreached bytes | 0 | 0 |
| Ordinary / register CALL sites | 865 / 175 | 865 / 177 |
| RET sites | 129 | 131 |
| Switch entries | 33 / 42 / 35 | 33 / 42 / 35 |

The section grows 16 bytes from the preceding 59,502-byte source; 1,156 bytes
follow the callable span as alignment/metadata, starting with two alignment
bytes before metadata offset 58,364. There are no local CALLs or external
tail transfers. Physical-owner diagnostics remain 6/109, not accepted matches.
Frame 0x400 and all 84 payload homes stay natural. Conditional incoming-action
and physical-ordinal pairing retains 84 singleton/bijective constraints, with
57 identity correlations; 182 spawn calls / 190 action-site records close.
Target/candidate pre-epilogue coverage is 14,870/14,750 PCs and 16,959/16,894
states. These are static storage correlations, not payload-value proof.

Ordinary CALL totals now equal 865 after two other suffixes split: advancement
sites rise 105 to 106 and wave sites 63 to 64. Per-callee target/candidate
counts still differ for advancement (107/106), indexed events (41/40), height
(19/20) and facing (9/10). Expanding calls by possible incoming action leaves
only the known action-730 facing mismatch, four target sites versus five.
Neither total is an acceptance criterion.

The focused whole-entry **412/418 native run passes 0/722**. Both genuine
root preludes and real helpers execute. Outcomes on each side are 468 RETs,
243 action-backend entries, 10 sequence-backend entries and one object-backend
entry; 208 target-root instructions are visited. The existing grid covers
sequence/frame/timer gates, motion/landing values and quiet NaN velocity,
including both precision control words for 412. The native and configured
objects normalize identically over the complete 59,518-byte section.

Input SHA-256:
`36a63971e0b6f73751902de76ed47636197bec2d0c97e1e2222e5bea66a266ad`.
Target-output SHA-256:
`a01ad37ac07513227c3657b182c597407bb0d411661c38cf62bcb266b0c39adb`.
A generated wrong-sequence control selects 3 at this continuation instead
of 2 and detects **10/722 differences: four for 412, six for 418**. It changes
source only; genuine target/backend code and callee results remain untouched.
Reproduce it from a build-local source copy by changing only
`select_sequence(2)` below `land_and_select_sequence2` to `select_sequence(3)`,
then passing that copy with `--source` to the same focused native command.
Execution stops at the first actual backend, so sequence continuation and
412's ring after its first object spawn remain outside the native scope.

A single direct Ghidra read-only clone independently re-attested imported
and file hashes, PE entry, full mapped `.text`, language/compiler identity
and root bytes, then read back the three calls and 418's exact branch target.
An initial private check assumed `62607E`; the database correctly exposed
`626080`, and the corrected readback passed. Heap was limited to 768 MiB and
CPU count to two. All nine primary database files are hash-unchanged. The
wrong-image IDA session remained rejected and unused.

## Reproduction and remaining work

```bash
python3 scripts/build.py --unit gpt-web-iku-action-state --compare --json
python3 scripts/probe-iku-upper-actions.py --middle --whole --actions 412 418 --output build/IkuLandingJoinNative.obj
python3 scripts/audit-iku-full-root.py --object build/match-units/GptWeb_IkuActionState.obj --native-object build/IkuLandingJoinNative.obj
python3 scripts/audit-iku-call-sharing.py --object build/match-units/GptWeb_IkuActionState.obj --partition-payloads
python3 scripts/audit-giant-action-owners.py iku-vslot28 build/match-units/GptWeb_IkuActionState.obj --unit gpt-web-iku-action-state --json
```

The strict comparison intentionally exits 1. Current local evidence is under
`build/iku-landing-join/`; the small control patch/readback script remains
under `.analysis/iku-landing-join-20261017/`. Older effect, sequence-exit,
full-link and MT-visibility/native results retain their earlier source hash
in their dated notes. No broad native matrix, accepted-unit or cold aggregate
replay was needed; shared interfaces/profiles/relocations stay unchanged.

Remaining leads are the effect argument's partial outgoing-stack join,
730's duplicated facing suffix and the remaining advancement/event sharing.
Preserve the target's explicit float round trip for effect-X in 416/417;
only the four 565..568 raw-X paths load X directly before their common join.
Original C++/TU/optimizer provenance, full-root value equivalence and
post-backend/exception behavior remain unknown.
