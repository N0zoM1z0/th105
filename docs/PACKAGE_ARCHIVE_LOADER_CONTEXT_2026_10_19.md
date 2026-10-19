# Archive loader template ABI and persistent analysis, 2026-10-19

## Result and evidence class

The authored loader `41BA70` remains **nonexact**, with its selected ordinary
source unchanged. No authored match, byte increment, source selection or
compiler-profile change is made here. Vector string append `41C270/162` is newly classified as a compiler exclusion.
Allocator string destruction `4102D0/42` was already excluded by the native
CFileList template anchor; its unclassified function-table status did not mean
unknown origin. This checkpoint adds ABI/context corroboration for it. The
paired body replays are private compiler-origin diagnostics, not accepted
canonical match-unit results.

Only the original Japanese1.06a executable is used, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Fresh preflight rejects the attached IDA hash10350095; no IDA semantic calls
are used. Exact observations come from that PE and independently attested
mapped Ghidra bytes. Retained source, generated decompilation, original class
names and TU ownership remain hypotheses.

## Complete target scopes and the hidden allocator use

| Address | Bytes | Decoded / ordinary reachable | EH-augmented reachable |
| --- | ---: | ---: | ---: |
| Loader41BA70 | 629 | 205 / 204 | 204 |
| vector<string>::push_back41C270 | 162 | 67 / 67 | 67 |
| allocator<string>::destroy4102D0 | 42 | 14 / 14 | 14 |
| Uninitialized-fill hypothesis41D4F0 | 170 | 66 / 51 | 66 |

The loader's sole skipped instruction is the3-byte alignment LEA at41BC0D.
Both162/42-byte helper CFGs close completely at their RET4 boundaries. The
loader supplies ESI=7028F8 and a stack string reference to push_back. The
allocator destroy caller supplies ECX=allocator and a stack string pointer;
the42-byte callee does not read ECX.

The170-byte fill helper reads count from ECX and first/value from its stack.
Its ordinary CFG misses the allocator use. Target handler6BDB11 selects
FuncInfo6E418C, whose nine DWORDs are:

```text
19930522  3  006E4150  1  006E4178  0  0  0  1
```

The try-map at6E4178 is `(0,1,2,1,6E4168)` and the handler record at6E4168 is
`(40h,0,0,41D563)`. The EH landing41D563 reads allocator at `[EBP+10h]`, then
calls4102D0 at41D573 with ECX=allocator and a stack element. Adding that entry
reaches all66 instructions. Source/header corroboration is the pinned VC8
`memory` implementation of `_Uninit_fill_n`: partial-copy failure destroys
constructed elements through its allocator and rethrows. The two tag words
are opaque physical stack slots, not recovered original application types.
This helper remains in origin review; its full170-byte code/EH layout has no
accepted match. A normal-RET-only extent would miss required exception code.

Target scope SHA256 values:

| Scope | SHA256 |
| --- | --- |
| 41BA70/629 | 9e97c3ceea6298777705f8f031fa7d4a6d4daf81a954b3ec19a60ea66b2bb63a |
| 41C270/162 | 924c9a86c11ae4ebb63357e9f7289dbc0c6140f6cf9d46a02648bafe8aeb1d0b |
| 4102D0/42 | f6476a560fe2750fb569a3f97078bfc822071f81acd3967d3edb7c5457a90e03 |
| 41D4F0/170 | 47d5f67465c2bfa2816ab8eddb18236fea15a5feb57307d573b7e88acd2bb787 |

## Actual source partition controls

Sixteen fresh successful serial controls use the current Store, Node/registration,
opener, loader, reader, critical-section and MT sources, plus the selected
real CRC body, real zlib and pinned static CRT/Kernel32 providers. All compile
with /O2 /GS /GR /EHsc /MT; the primary aggregate has /GL, and the named native
inputs omit /GL. The linker uses real DLL CRT startup, /LTCG and /OPT:NOICF.
No unresolved/force option, custom code stub or fabricated register declaration
is used. Commands, current implementation/header hashes, tool/library pins,
objects and image/map hashes are retained in each control's commands.json.

`native-owner` means the actual `PackageArchiveStore.cpp` is an ordinary COFF
input; the other selected providers remain together in CIL. Native registration
initially includes the actual Node definitions. The registration-only controls
separate those same definitions into CIL and compile only the unchanged
registration body as ordinary COFF. Reader and MT controls isolate their real
sources. These are alternate comparison artifacts, not selected original TUs.

Publication controls retain the observed standard callable ABI of the real
registration and/or MT functions through DLL exports. The private loader,
private vector entry and private global lifetimes are never exported. These
flags are diagnostic ABI retention; they do not assert exports in the original
EXE. Whole-COFF publication also loses cross-function optimization information,
so it is not equivalent to retaining an interface while its CIL body remains
visible.

| Context | Loader bytes / frame | push_back bytes | seed bytes |
| --- | --- | ---: | ---: |
| all | 627 / 148h | 161 | 57 |
| native-owner | 627 / 148h | 162 | 57 |
| native-owner-mt | 630 / 148h | 162 | 61 |
| native-owner-mt-published-registration | 631 / 148h | 162 | 61 |
| native-owner-published-registration | 628 / 148h | 162 | 57 |
| native-owner-published-registration-mt | 628 / 148h | 162 | 61 |
| native-owner-published-registration-seed | 628 / 148h | 162 | 61 |
| native-owner-reader | 627 / 148h | 162 | 57 |
| native-owner-registration | 595 / 138h | 167 | 57 |
| native-owner-registration-only | 595 / 138h | 167 | 57 |
| native-owner-registration-only-mt | 598 / 138h | 167 | 61 |
| native-registration | 595 / 138h | 166 | 57 |
| native-registration-only | 595 / 138h | 166 | 57 |
| published-registration | 628 / 148h | 161 | 57 |
| native-string-allocator | 627 / 148h | 162 | 57 |
| native-string-allocator-published-registration-mt | 628 / 148h | 162 | 61 |

The all-CIL allocator destroy is34 bytes, with private ESI input and RET0.
The actual native Store COFF contains a conventional allocator::destroy COMDAT.
In that context the selected CIL destroy retains the stack element/RET4 and
becomes42 bytes; its dependent fill retains allocator, so push_back restores
its allocator PUSH and becomes162 bytes. The same caller can therefore change
interface when real native template definitions are present elsewhere. This is
an observed context dependency; it does not uniquely recover the original TU
or compiler release.

Private full-byte relocation replay of those two bodies gives zero differences
for42/42 and162/162, with one/three named REL32 fields and no internal HIGHLOW
fields. The source identities are the real VC8 allocator/vector template
symbols. All other bytes, including saved registers, arguments and RET cleanup,
are retained. Vector origin is recorded in `package-loader-string-template-context-vc8-106a`;
the allocator keeps its pre-existing CFileList anchor. Neither receives an authored
mapping, source-present row or matches.csv entry.

Retaining the standard registration ABI restores four stack arguments while
preserving the loader's8-byte alignment. Native registration instead changes
both the interface constraints and optimizer information, yielding an
unaligned138h frame. Publishing seed restores its61-byte normal cdecl body;
its loader can remain628 bytes because call-sequence growth changes alignment
padding. Equal sizes are not equal payloads.

The target still has frame150h. The current aligned controls have frame148h,
a different count-publication join and different register/stack scheduling.
The path buffer remains256 in every control; its original declaration is not
recovered from stack slack or decompiler arrays. The ordinary selected probe
still has a conventional ECX vector call, so the new ESI witness is not added
as a false binding to that unit.

The old allocator origin ledger supplies an independent CFileList/deque<string>
instantiation witness. Linking the complete native FileList TU exposes six real
UI dependencies, so that incomplete graph is not used. A smaller control
explicitly instantiates the same real VC8 header method, retaining a genuine
ordinary implementation. It gives627/628-byte loaders, frame148h and the same
162-byte push_back while keeping the archive owner in CIL.

`src/library/StdStringAllocator.cpp` now retains that compiler-library source.
The dedicated unit `gpt-web-vc8-string-allocator-destroy` gives a **formal42/42
compiler-only comparison** with its actual standard callable ABI. It receives
no authored source-present or match row. The already-accepted archive lifetime
unit uses that ordinary COFF support through its existing typed library-input
contract. Its focused cold rebuild remains **163/163 and228/228 exact**, with
all coupled EH code/data verified. No accepted authored byte is added or lost.
The private full-graph lifecycle replay also preserves all13 regions/606 bytes.

## Full loader/container execution

Two minimal native-library graphs are executed independently against target
instructions: `native-string-allocator` and
`native-string-allocator-published-registration-mt`. The earlier native-owner
pair also passes the same9 scenarios. Each passes all
**9 scenarios / 31 archive API calls / 194 actual registration entries**.
The model checks registration entry counts, final vectors/count/map/chains,
tree links/order/red-black properties, allocation/release sizes and order,
ABI-preserved registers and stack, and complete final destruction with no live
allocations.

The added8/12-archive scenarios reach the real vector fast path at41C2BD and
fill entry41D4F0, and the corresponding actual source fill entry. They include
long archive strings and repeated updates. Earlier four-archive cases reached
the fill helper through insertion but never reached the fast push_back block. All prior empty/failure,255-byte names,
embedded NUL, high-bit sizes/offsets, punctuation collisions, growth and170
registration scenarios remain. Target coverage is2277 distinct instruction
addresses; source coverage is2191/2218 for the two minimal-library graphs.

Only Win32 I/O/uncontended locks, successful allocation/release and ASCII
stricmp are modeled. Actual C++ initialization and atexit destruction execute;
full CRT startup, OS unwinding, failure cleanup, concurrency and malformed or
short-read input behavior remain outside this proof. The EH ABI observations
come from raw target metadata/instructions, not simulated Windows dispatch.

## Persistent Ghidra state and remaining uncertainty

The initial read-only visit verifies executable identity, base, entry,
x86-Windows target, complete mapped text SHA
`f5cb09ff0a54362356d8c4cce853cbcb14552499cce12cf7390d0868db9ebe97`
and all four scopes. It finds no primary function entries for those addresses:
earlier archive readbacks were temporary views, not persisted primary state.

A private copy now receives the four bounded function bodies and physical
parameter storage, stack purges and returns. The loader return explicitly uses
**AL:1**: a printed bool type alone had left its custom return storage
unassigned. Three real named KERNEL32 external locations become function
metadata with the CreateFileA/ReadFile/CloseHandle stdcall prototypes and
28/20/4-byte purges. External locations are snapshotted before mutation.

The saved copy is reopened read-only. All four bodies, every register/stack
slot, AL return, opaque tag words, nominal thiscall convention for the two
RET4 member views, purges and all three import prototypes are
read back, with target identity/text/scope attestation repeated. Only then is
it promoted to primary; all nine promoted file hashes equal the verified copy.
Current pins are `build/archive-loader-shape-20261019/primary-db-after.json`.
The old CPU-root pins describe the predecessor. No target bytes change.
The direct processes run sequentially, no analysis, CPU0/nice10,384 MiB heap.

Decompiler output is still a hypothesis: remaining direct-callee prototypes
and EH interpretation are incomplete. Original buffer capacity, complete
source partition, enclosing class/inheritance and game-method ownership remain
unknown. Continue the whole629-byte caller and its real call/alias/frame
constraints; the162-byte helper witness does not resolve those residuals.

Receipts: `build/archive-loader-shape-20261019/{context-summary,target-facts}.json`,
`native-owner/{push-back,allocator-destroy}-replay.json`, both *-integration.json,
ordinary baseline.json, compiler-library-formal.json,
store-with-library-formal.json, Ghidra write/readback logs and primary promotion pins.
Private scripts/hypotheses remain below `.analysis/archive-loader-shape-20261019/`.
Reproduce the selected probe with:

```bash
python3 scripts/build.py --unit gpt-web-package-archive-loader --compare --json
```

The current formal outcome remains the supported unknown-vector-call block.
No aggregate cold replay or exact percentage is claimed.
