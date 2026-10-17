# Iku whole-root real source link

The complete selected Iku action root now links against real game source and
the pinned VC8 SDK/CRT. All three linked switches close. This establishes a
reproducible larger compiler context; it does not resolve the root's first
mismatch or establish whole-game behavior.

Target is original Japanese TH10.5 v1.06a, executable SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Iku620920 covers `[620920,62EFBE)`, 59038 bytes, SHA-256
`abc831c6ccd95986bed811694f532ad8c8b92cb49702a7f6ce4de100b8a73dea`.
The ordinary canonical comparison remains **nonexact +0x64 /620984**.
No exact or partial authored credit is added.

## Source and link closure

`scripts/probe-iku-action-ltcg.py` compiles the whole Iku source with `/GL`
and 41 game source providers as ordinary `/Gy` objects. It links those with
two genuine SDK deque instantiations, a provisional float adapter and pinned
static CRT/Windows SDK libraries. There are 44 compilation steps. The normal
DLL link uses `/LTCG /NODEFAULTLIB /OPT:REF /OPT:NOICF /INCREMENTAL:NO`, real
CRT startup and an exported root; unresolved code is a failure.

The probe independently compares 52 required game dependency addresses:
47 are canonical exact and five remain nonexact: angle lookups406360/4063D0,
resource-handle lookup417800, ScoreData42CF70 and Common Fighter4740C0.
These diagnostic comparisons do not add accepted matches. Nine bounded source
partitions retain only the required bodies, with guarded method inventories.
They are diagnostic partitions, not recovered original translation units.

Forty-four aliases bind source views already contracted to the same target
address; map readback checks that the alias and provider share their address
and object. Eighteen ABS bindings supply independently attested non-executable
game data. They do not supply function bodies, imports or CRT storage. These
bindings and aliases do not prove original class declarations or runtime state.

The missing source provider406330 is still unclassified. A genuine C++ float
adapter calls the pinned CRT `fabs` and returns float, following the observed
target float argument/result ABI. It is explicitly provisional and nonexact;
its ordinary frame does not recover the target's aligned frame. No source,
ownership or exact ledger entry is promoted for it. The actual CRT provides
`__ftol2_sse`; no invented C++ return ABI or helper result is substituted.

Both real SDK providers reproduce their target standard ECX/stack-index/RET4
interfaces before and after linking:

| Target | Provider | Bytes | Canonical SHA-256 |
| --- | --- | ---: | --- |
| 4399C0 | `deque<FighterSequenceSlot>::operator[]` | 94 | `5e6d9bae7c00a857a51b7ca00c03b37c95e1986a9e389d56e35924b205f7491b` |
| 42D1B0 | `deque<unsigned>::operator[]` | 100 | `712c71f4f6e8b3dfe423c4312ea4f5ee45f92e5e842fa9183cb97abce714e04f` |

These are existing excluded compiler islands, not authored progress.

## Linked root observations

The linked root starts10001000, retains frame400hex and closes15032 reachable
instructions /58433 instruction bytes. Its callable-and-padding extent is58440
bytes. Seven unexecuted bytes comprise two three-byte LEAs after short jumps
to aligned loop headers and one trailing NOP after RET. The shared inspector
accepts the precise interior jump/LEA pattern only through an explicit Iku
opt-in; its default remains strict. This check does not remove bytes from a
canonical comparison.

The three switches retain33/42/35 destinations and227/247/238 indices.
All ordinary calls resolve to32 provider names, totaling867 physical sites.
No unresolved indirect exit or local CALL target remains in the root CFG.
These counts agree with the ordinary source object's diagnostic counts;
whole linked/ordinary byte equality has not been established.

The first101 linked entry bytes need no CALL or HIGHLOW relocation. Exactly
100 agree with target; byte100 differs at620984, where target hoists EDI=1
before the action-range branch. This is an entry witness, not a whole-root
canonical replay. The image is not executed by this probe. Root source remains
unchanged from [the steering checkpoint](IKU_STEERING_CLAMPS_2026_10_17.md):
CRLF source SHA-256
`ff79e5743533c50c885a0139facff1febc726f2c2b5e5a84497fe2bd27b014ad`;
ordinary normalized section SHA-256
`33f09d2ac49075ed6495a5b10a884fe18cf1f5b9e8556dcdec157eb58038549d`.

## Required ScoreData provider42CF70

The genuine Iku call chain45D110 ->43AF20 ->42CF70 exposed this previously
unselected application method. Target `[42CF70,42D00F)` is159 bytes, SHA-256
`6c772b740b8d672b600fec4ddb0211bad97c315d5148309f710c2d12a46e8922`.
Raw instructions establish void thiscall, ECX receiver, three DWORD arguments
and RET12. The game-mode getter43AC40 must return0 and session getter43B070
must differ from2. The method selects a16-byte checked vector at
`this+198hex+16*selector`, scans24-byte records for two DWORD keys at0/8, and
increments count0C in the first match. It neither appends nor changes later
duplicate keys. Full class size, array cardinality, original counter signedness
and source spelling remain unknown.

`src/config/ScoreSequenceResult.cpp` uses the actual SDK vector iterator with
compile-time size/offset guards. The historical C++ method suffix42c060 is
retained for existing callers; the durable target name is
`ScoreData_record_sequence_result @42CF70`. The selected ordinary object is
142 bytes, canonically nonexact+0xA against159. It omits the target's nine-byte
self-container compatibility check (`CMP EDI,EDI`, conditional jump and genuine
invalid-parameter CALL); two shorter early gate branches explain the other
eight bytes. RTM, postfix-increment and reversed-equality controls remain142.
No redundant source check or storage is fabricated to reproduce it.

Fresh native comparison passes **0/1323 mismatches** with the real target
game/session getters executing for both target and compiled source. It covers
three modes, three session options, three selectors, empty and nonempty ranges,
duplicate/missing keys, two initial counters and malformed begin>end ranges.
There are1317 genuine RET12 outcomes and six genuine invalid-parameter entries,
covering47 target instructions. The fixture verifies callee saves, stack
cleanup, code bytes and permitted counter writes. It stops at the error entry;
handler/exception continuation is not established.

- Source CRLF SHA-256:
  `93070c254e9767b285d61376ca52817d0f331efea8324c1da722cb0555d50ee0`.
- Ordinary object SHA-256:
  `2709b47d6e45fd11d739cfd03cce8099e8eaf03695d4f5a4253b4b1ff20ee8f6`.
- Native input SHA-256:
  `1b39b189f119e294f64be992e4e34caf1efcd2bbf22583abf29067d834cae521`.
- Native target-output SHA-256:
  `ff583795a65deab68e5880fff74410794f5137179046103d9f0b9a57cdd7087b`.

The directly attested Ghidra database lacked42CF70. A bounded159-byte working
function and void/ECX/three-argument/purge12 ABI were created and read back in
a read-only768MiB/two-CPU clone. Fresh decompilation corroborates the scan as
a hypothesis. No target bytes were patched. The clone was deleted and all
nine primary database files remained hash-unchanged. Wrong-image IDA was
rejected before both bounded work units.

Removing the older unverified duplicate method from ScoreObservations.cpp
leaves its existing42D010 statistics method byte-neutral over all182 ordinary
bytes (SHA-256 `cd35ee25b63dcfe225de0cf77b19344a1f263e152f153850d5b5a33622f3fe1e`).
That unit remains nonexact against191 bytes. Shared headers, accepted profiles,
layouts and canonical relocation ledgers are unchanged.

## Reproduction and remaining work

```sh
python3 scripts/build.py --unit gpt-web-score-sequence-result --compare --json > build/score-sequence-result-final-compare.json
python3 scripts/probe-score-sequence-result.py build/match-units/GptWeb_ScoreSequenceResult.obj > build/score-sequence-result-native.json
python3 scripts/build.py --unit gpt-web-score-observations --compare --json > build/score-observations-after-partition.json
python3 scripts/probe-iku-action-ltcg.py --reuse > build/iku-linked-final.json
python3 scripts/build.py --unit gpt-web-iku-action-state --compare --json > build/iku-real-link-root-compare.json
python3 scripts/ci.py
git diff --check
```

The three focused build/comparison commands intentionally exit1 for the
documented nonexact results. The link receipt lives at
`build/iku-action-ltcg/receipt.json` and pins sources, objects, compiler/SDK,
libraries, commands, aliases, data and comparisons. `--reuse` checks source,
full unit-input digest, compiler command, tool pins and current object hash.
A fresh follow-up run reused all44 objects and relinked successfully.

Old compiler/link controls, duplicated raw disassemblies and stale census
reports were removed, reclaiming about174MiB while retaining the current small
link cache, primary Ghidra database and uncommitted historical source worktrees.
Generated artifacts remain below build/ and private analysis below .analysis/.

Next establish full linked-root relocation replay or execute the genuine
linked providers through bounded fixtures, then continue shared call/payload
ownership. Action730 still has an extra face site; effect565..568 still retain
four sites absent from target's shared suffix. Eleven payload-home correlations
remain ambiguous. Original TU/inheritance/LTCG phase, post-backend execution
and exceptional behavior are unknown. No cold aggregate replay is claimed.
