# Complete ScoreData defaults/reset42ED70

The complete function is canonical **2428/2428**, selected source-present and
matching. Two independent public builds reproduce target/candidate SHA-256
`edf6201796372e2afccac1e7d42589bf8c3a5c6014a4f35490b9c3f2b004ccc5`.
The first whole source was compiled and compared before focused adjustments.

## Observed target evidence

Only the original Japanese1.06a executable, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`,
was inspected. Fresh target/status/tracking checks passed. IDA rejected its
10350095 target, so no IDA semantic evidence or metadata writes were used.
Raw PE instructions establish2428 bytes,664 decoded instructions,661 reached,
RET0 at42F6EB and four following INT3 bytes. Three unreachable alignment
operations are retained at42EF69,42EFF6 and42EFFD. There are no escaping edges,
indirect calls or indirect jumps. The native aligned frame is458 with GS/EH
handler6B8012 and a ProfileMenuBaseData local at stack+11C.
The unselected score-loading caller42F6F0 directly calls this root at42F765 and
42F82F; those edges do not classify or select that caller.

Game-specific writes and resource/CSV policy establish authored config
ownership independently of compiler helpers. Exact body identity does not
establish the original nominal type names or translation-unit boundary.

## Complete recovered behavior

The source constructs a real33C ProfileMenuBaseData lifetime, initializes its
default bindings and retains it through completion. It clears three20-byte
availability arrays at+08/+1C/+30, unsigned sets at+50 then+44, and checked
four-byte-element vectors at+7C/+8C. It constructs a real20-byte spell-resource
group and inserts every global common-spell key into the+9C count map with
initial value zero. Insert preserves an already existing mapped value; the
common count map is not cleared here.

For each of15 character keys, it clears the count map at+A8+12*key, loads
normal spell CSV data, inserts each local spell key with zero count and clears
temporary resources. The default deck is a checked deque of signed shorts.
Each local key increments its count. A key absent locally is looked up in the
common map; if found, its count becomes max(existing,4), without insertion for
an unknown key. The record vector at+198+16*key is cleared.

The native path is directly constructed from `data/csv/`, then appended with
the character name and `/story.csv`. The reader consumes a signed group count,
advances a row, then for each positive-count group ignores one integer, reads
a name and resolves a by-value String28 copy, reads a signed row count and
advances again. Every positive-count row reads four integers, one per difficulty
0..3. Values below200, including negative values, can produce a24-byte record:
resolved key at+00, difficulty at+04, parsed value at+08 and three zero statistics
at+0C/+10/+14. Deduplication compares only+00 and+08; an earlier difficulty wins.
There is no lower bound or difficulty component in that native dedup key.
Each record row advances once. Names, path, CSV rows and deck are destroyed in
the observed nesting, followed by temporary spell resources and profile data.

Finally the first three primary availability bytes become1, the first13
secondary availability bytes become1, unsigned set+50 receives10 and11,
flags+04 become0, story progress refresh42E3F0 runs, and byte+00 becomes1.
42DB20 is the independently identified unsigned-set insertion provider.
Its hidden result argument is not evidence for erasure.

## Focused whole-function comparisons

All rows replay the complete COFF section and all relocations. Unequal
positions count only the shared extent; size differences remain separate.

| Source phase | Candidate bytes | Unequal positions | Finding |
| --- | ---: | ---: | --- |
| First complete source |2431 |2216 | First difference42EDD7; one60-byte memset call instead of15 native DWORD stores. |
| Local intrinsic directive |2431 |2216 | Whole-payload byte-neutral; this lane is closed. |
| DWORD clear loop |2655 |2256 | Correct store widths, different inlining/register decisions; discarded. |
| Three real20-byte array clears |2463 |713 | First1335 bytes agree; no aliasing or synthesized store facade. |
| Real dedup-found state and ascending primary writes |2428 |224 | Residual vector-iterator comparison, path lifetime and two CMP operand orders. |
| Native vector clear and record-first equality |2412 |851 | First1499 bytes agree; direct path construction remains. |
| Direct String28 path construction |2428 |0 | Exact complete native frame, EH states, control flow and body. |

The last private replay initially bound two different basic_string assign
specializations to the same address. Distinguishing actual `assign(char*,n)`
4021C0 from `assign(string,pos,n)`4020D0 removed two relocation-only differences.
The public manifest uses those exact decorated symbols separately. No fake
returns, inert locals, manual instructions or padding were introduced.

## Reproduction and semantic checks

Source: `src/config/ScoreDefaults.cpp`.
Shared lifetime declarations were extracted without layout changes to
`src/ui/ProfileMenuBaseDataLifetime.hpp` and
`src/ui/ProfileDeckResourceLifetime.hpp`; existing constructor/destructor
implementations include them. Rebuild all accepted units after this extraction.

```bash
TH105_ENABLE_GS=1 taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py --unit exact-first-score-defaults --compare --json
scripts/repo-python scripts/audit-score-defaults-target.py --object build/match-units/ExactFirst_ScoreDefaults.obj
```

Public receipts under `build/frontier-42ed70-20261026/`:
`formal-first.json`, `formal-second.json`, `target-audit.json` and
`target-audit-second.json`. Private first/control sources and raw decode recipe
remain under `.analysis/frontier-42ed70-20261026/`.
The audit pins the full CFG, caller sites and guard/reader census. Five native
CSV-region executions and candidate replays cover positive/zero/negative group
or row counts, all four reads, duplicate values across difficulties, signed -1,
199/200 boundaries, different resolved keys, complete24-byte append values and
stack preservation. The populated case appends six records and consumes all17
integer reads. External services and STL providers are observers; game I/O,
full initialization fixtures and exception unwinding are not executed.

No helper receives new authored or matching credit. Existing exact constructors,
resource wrappers, resolver and story-progress refresh retain their independent
units. Literal/path and EH relocation ownership is pinned separately.
Fresh origin generation/check passes all4024 rows. Full current-manifest cold
replay passes527 accepted units/all1415 functions,388331 authored bytes,
including both extracted lifecycle units and this complete2428-byte root.
Floating relocation audit remains399 ledger literals/1603 explicit mappings,
2002 target references. Final local CI is recorded in `local-ci.log`.

Next coherent peer is score loading42F6F0, provisional1672 bytes. It requires a
fresh bounded preflight, full boundary review and early complete comparison.
