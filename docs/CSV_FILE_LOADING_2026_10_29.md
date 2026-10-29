# CSV file dispatch and iterator reset

Two complete authored functions are now canonical exact in the real CIL context:

-408E40, FileBuffer_load_csv,140 bytes:
 307c2e312bd8c97d0cb197ea1dabc28ef22560efa4cfb48adc84344cb4ce2525.
-40F730, CsvReader_reset_iterators,151 bytes:
 4baeccc6540c6f698be3d89e497f44dd296c8a0046367190e622c891e7da46b7.

The291 bytes add no acceptance for the file/CSV loader bodies, parser, library
providers or caller EH. No partial-function or size-only credit is used.

## Raw target and actual source context

Factory-native IDA passed a fresh metadata/entry, five mapped-byte samples and
inventory/disassembly/decompiler/call-graph preflight. Samples were compared
with the canonical raw PE; responses remain under build/frontier-csv-load-20261029.
No analysis-database metadata or executable bytes were changed. The575-byte
parser decompilation was only navigation; raw switch/field/call instructions
establish the source behavior below.

The8-byte FileBufferContext owns its allocation and size. In encoded-resource
mode, load_csv copies the path into a260-byte local and replaces its last four
bytes with .cv1; otherwise it calls the plain loader. Both return their actual
callee result. The existing real reader, package lookup, node and casefold CRC
implementations close the link, with real static CRT/Kernel32 providers. The
package global is bound to its independently attested native data, not a fake
initialized substitute. The original TU partition and class names are unknown.

CsvContext owns deque<deque<string>>, its12-byte row iterator, its12-byte field
iterator, and comment/quote bytes. load owns the file buffer, returns false on
file-load failure, then parses and resets iterators on success. The raw170-byte
caller is independently reached by exact default-deck loader431E80 at431FCC.
Its current complete source emits176 bytes and remains unaccepted.

reset assigns rows.begin() and, only if there is a row, assigns that row's
begin() to the field iterator. This jointly controls two reader-owned iterator
members. It is game policy, not one standard-container implementation. The old
origin rule incorrectly inferred compiler ownership merely from the private
ESI entry; that address is removed from the rule. The actual string erase,
nested-row push and EH-only tidy entries retain their existing classification.

Ordinary source definitions naturally produce the private entries: ECX/EDX for
the file wrapper, ESI for reset and encoded load. Exporting the file wrapper
as ordinary thiscall in the first private control instead produced153 bytes;
using its actual CSV caller produces the complete140-byte native body. No
fastcall/register declaration, noinline pragma, stub or artificial caller is
used. The plain loader and FileReaderOwner.open retain their known normal
public member interfaces.

## Parser and provider limits

The full parser is included to supply the actual caller graph, not selected as
exact: its current843 bytes differ from native575. The recovered policy keeps
'#' as comment activation even inside quotes; quotes toggle even in comments;
commas commit a field regardless of quote state when not in a comment. Quoted
CR/LF are appended unless in a comment. Unquoted LF commits the field/row only
outside a comment and then clears comment state. EOF does not flush an
unterminated row. No extra validation or cleanup behavior is invented.

The casefold hash body is factored from ScoreMusicLookup.cpp into the shared
CaseInsensitivePathHash.cpp and calls the real C get_crc_table interface.
Its293-byte body and the99/86-byte score callers replay exact. The zlib1.2.3
static-table getter is supplied by ZlibCrcTable.cpp using unchanged crc32.h.
All8192 table bytes equal canonical6C7630, SHA256
24363a766de82f6877f1c0e25912659526684c30b689fea3d960cc703067a718.
This library context receives no authored credit. No executable ABS binding,
synthetic returned pointer, unresolved link or force option is used.

## Narrow caller address-role witness

The existing private caller proof needs one uniquely owned unexported CIL
callee and one actual E8 edge in each complete source/native caller CFG. This
caller also installs its own compiler EH handler and loads the real CRT
security cookie. The new explicit caller_eh contract identifies only those
two address roles, without claiming the caller or its EH are byte-exact.

It requires the static pinned CRT cookie witness, unique private compiler
handler/cleanup funclet, bounded27-byte GS handler with actual cookie-check/
FrameHandler3 branches, one-state cleanup-only FuncInfo, a valid unwind map,
exact HIGHLOW field coverage and exactly one handler/cookie operand in each
caller. Extra fields, aliases, wrong roles or wrong native handler/Info fail.
Native handler6BE388 selects Info6E4B40. Source/native frame offsets differ,
and receipts explicitly say caller_or_eh_exactness_claimed=false. No field in
either accepted callee is masked. Existing single-edge and two-edge contracts
remain unchanged; only the separately explicit role contract is new.

## Reproduction and focused checks

    scripts/repo-python scripts/build.py --unit exact-first-csv-file-loading --json
    scripts/repo-python scripts/compare-linked-unit.py exact-first-csv-file-loading --address 0x00408E40 --address 0x0040F730 --json

Use address-selected comparison: the other configured root is a nonaccepted
caller witness, whose ordinary full canonical comparison remains blocked by
its unmatched EH surface. The two accepted bodies have closed CFGs and every
byte/relocation is replayed. Receipts are public-build.json/public-compare.json
in build/frontier-csv-load-20261029.

Focused source replay keeps all three score/hash functions exact. Legacy
private single-edge script destructor95/pending cleanup147 and the genuine
two-edge BGM constructor89 also replay exact. Three small checker tests cover
this role contract and rejection cases; existing linked checks remain passing.
No cold corpus rebuild or broad runtime matrix was performed.
