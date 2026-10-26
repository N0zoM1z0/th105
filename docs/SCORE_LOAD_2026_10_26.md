# Complete ScoreData loader42F6F0

The whole1672-byte target has complete source and full relocation replay.
The public candidate is **nonexact**:1666 bytes,564 unequal shared-extent
positions, six missing target bytes, first difference42F91B. Candidate SHA-256
is `9979a9c50f74adbc0df6a075e2665f12a74403e48ca00cc86dcadfc84e796645`.
The first555 bytes agree. Source is unselected; no implemented.csv or matches.csv
row is added. A whole native/candidate observer audit agrees in four cases.

## Observed identity, ownership and boundary

Only original Japanese1.06a SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
was used. Fresh target, status and tracking checks passed. IDA again rejected
the10350095 target; no IDA semantic queries or writes were used.
All521 instructions/1672 bytes are reachable, with no escaping direct edges or
indirect jumps. Native RET0 sites are42F795,42F876 and42FD77; eight following
INT3 bytes separate the next callable. Native AL is boolean: both fallbacks
return false and the parsed-data path returns true.
The aligned frame allocation is74, with EH cookie and handler6B8058. The file
is a12-byte plain CFileReader lifetime with its real five-slot vtable6C0F34.
Two independent eight-byte owning buffers each allocate512KiB through array
new665B8A and release through array delete68AA26.

The `score.dat` path, reverse/XOR policy, default fallback, availability arrays,
sets, card-count maps, story-record policy and refresh establish authored config
ownership independently of OS, codec, allocation and STL providers. The existing
scene resource bootstrap calls this address and ignores AL; its previously
provisional void declaration is corrected to bool with the corresponding
explicit decorated relocation binding. Focused caller build/audit retains3722
bytes and11 differences, SHA
`dd302ab4d718d3e410fedf672ea3caa5aadf75ba1daf3bdcf86e363d0ded2486`.
No additional caller exactness follows.

## Complete target behavior

Open `score.dat` with CreateFileA(access1,share1,OPEN_EXISTING3,attributes80).
INVALID_HANDLE_VALUE becomes zero. A missing file calls exact defaults42ED70
and returns false. A valid handle owns two512KiB buffers. GetFileSize determines
the ReadFile request and the transform loop count; ReadFile's boolean and actual
byte count are not checked here. The second buffer receives the reversed first
buffer XORed with the low byte of7*index. Codec406890 is called with encoded
pointer/file count/decoded pointer/512KiB capacity. A zero result calls defaults
and returns false, preserving reverse buffer cleanup and handle closure.

After successful decoding, the first DWORD is skipped. Restore flags+04 and the
three20-byte arrays+08/+1C/+30. Clear/rebuild unsigned sets+44 then+50 from
unsigned counts and DWORD keys. Clear/rebuild common counts+9C from DWORD key/
value pairs, preserving std::map insertion's first value for duplicate keys.
Read an unsigned character count. For each represented character, clear/rebuild
its map at+A8+12*index, erase the record-vector range at+198+16*index and read
an unsigned record count. Every serialized record copies all six DWORDs.
Deduplication compares only record+00 and+08; difficulty+04 and statistics do not
participate, so the first complete record wins. No200 threshold applies in this
loader. A zero character count preserves every character map and record vector.
No file count/character count bounds checks are added to this source hypothesis.

Finally call story refresh42E3F0, set initialized byte+00 to1 and return true.
Both buffers are released in reverse construction order before file closure.
The public audit observes the caller policy; it does not execute codec406890,
real file I/O, allocation implementations, STL helpers or EH unwinding.

## Newly observed shared layout

Native static initializer6BEC30 loads g_score_data6FCC98 and calls43E1A0 at
6BEC35; its atexit wrapper6BF170 tail-calls43DF10 with the same receiver.
The306-byte constructor43E1A0 has SHA-256
`991bc3a6dde8fab75eeea8f3d07879689361f418cc7e241cc8ff31a513ec690c`.
Its real vector-construction calls pass count20/stride12 at+A8 and
count20/stride16 at+198. The prior defaults view's fifteen map slots plus opaque
3C-byte gap are therefore corrected to20 map slots; record-vector capacity is
also20. Defaults42ED70 still loops over only15 roster keys. No constructor,
initializer, destructor or helper is promoted or given new coverage credit.

Shared definitions now live in `src/config/ScoreDataDefaults.hpp`.
`ScoreDefaults.cpp` includes them, and focused replay preserves its entire
2428/2428 target SHAedf62017. The loader's20-slot correction is whole-payload
byte-neutral. Neither this bounded view nor the constructor evidence proves the
complete original ScoreData owner size, nominal record names or original TU.

## Finite whole-source trials

Every scored row uses the complete available COFF section and all qualified
relocations. Difference counts cover only the common extent; size remains a
separate condition. These are diagnostics, never local-window acceptance.

| Source phase | Candidate bytes | Unequal positions | Evidence/conclusion |
| --- | ---: | ---: | --- |
| First complete source, GS disabled |1536 |1469 | First42F704; native EH cookie requires the local GS setting. |
| Native GS/EH setting |1553 |1247 | Native aligned74 frame/cookie recovered; generic64-byte memcpy remains external. |
| Flags getter and three20-byte copies |1666 |627 | First398 bytes agree; header scalar-register grouping differs. |
| One typed64-byte header assignment |1557 |1259 | Emits REP MOVSD, absent from target; discarded. |
| DWORD-read header loop |1589 |1283 | Retains a loop, absent from target; discarded. |
| Four real header-field copies |1666 |658 | First555 bytes agree. |
| Scalar getter uses memcpy instead of dereference |1666 |658 | Whole-payload byte-neutral; getter implementation lane closed. |
| Read set keys through actual output locals |1666 |564 | Native key-reference argument/lifetime shape recovered further. |
| Independently proved20-slot capacity |1666 |564 | Whole-payload byte-neutral; retain corrected layout. |
| Shared public declarations |1666 |564 | Two public builds reproduce full SHA9979a9c5. |

A genuine local record-vector reference control externalized vector::size().
That new provider has no qualified binding in this scope; its complete canonical
comparison is blocked and receives no invented address or diagnostic score.
The retained direct native-array accesses have no such unresolved relocation.
Remaining differences include temporary stack homes, insertion scheduling and
vector erase guard/reload/operand scheduling. No repeated spelling/flag matrix,
manual instructions, padding, inert locals or fake returns were introduced.
Standalone mismatch alone proves no LTCG impossibility. Keep these source lanes
parked until independent lifetime/TU evidence changes the question.

## Reproduction and receipts

Source: `src/config/ScoreLoad.cpp` (complete, unselected).
Unit: `exact-first-score-load` (GS enabled, pinned VC8 SP1 O2).

```bash
taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py --unit exact-first-score-load --compare --json
scripts/repo-python scripts/audit-score-load-target.py --object build/match-units/ExactFirst_ScoreLoad.obj
```

Both commands intentionally return1 for the recorded complete nonexact result;
the audit returns2 for an evidence/fixture failure. Reports are under
`build/frontier-42f6f0-20261026/`: `formal-first.json`, `formal-second.json`,
`formal-audit-first.json`, `formal-audit-second.json`, `target-audit.json` and
`defaults-shared-replay.json`. Private first/control sources, raw decode and
full replay recipes remain under `.analysis/frontier-42f6f0-20261026/`.

Four complete native executions and candidate replays cover missing file,
decode failure, populated data and zero character count. They pin open flags,
reverse/XOR bytes, codec capacity, set duplicate handling, first-map-value
retention, full24-byte record preservation, value300 above the defaults parser threshold,
pair-key deduplication, unchanged
unrepresented character slots, exact cleanup order, AL result, stack, callee
saves and FS0 restoration. These are targeted observer cases, not general codec,
malformed-file or exception equivalence. The new probe/data ownership and shared
header conservatively invalidate old accepted receipts. Fresh origin generation
and independent check both pass all4024 rows; the current-manifest cold replay
passes527 accepted units/all1415 functions,388331 authored bytes. The prior
score defaults remain2428/2428 and the caller3722-byte/11-difference body is
preserved. Float audit remains399 ledger literals/1603 explicit mappings,2002
target references. Final local CI receipt: `local-ci.log`.

Next coherent medium peer is score persistence42D3F0,
provisional1155 bytes, requiring a fresh bounded preflight and early whole build.
