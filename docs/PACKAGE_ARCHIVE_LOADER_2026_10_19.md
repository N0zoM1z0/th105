# Package archive loader, 2026-10-19

## Observed target and boundary

`load_package_archive_impl @0x0041BA70` is game archive policy, now mapped and
source-present in `src/assets/PackageArchiveLoader.cpp`. It remains **nonexact**.
Only original Japanese 1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used.

The complete callable is `[41BA70,41BCE5)`, 629 bytes, SHA256
`9e97c3ceea6298777705f8f031fa7d4a6d4daf81a954b3ec19a60ea66b2bb63a`.
All direct branches close inside it. Of 205 decoded instructions, 204 are
reachable; the three-byte alignment instruction at 41BC0D is skipped. There
are no indirect jumps or outside branch exits. A raw full-text E8/E9-lead
scan finds only the tail jump at 40CF34. Its independently decoded nine-byte
wrapper reads a stack path into ECX and jumps to this root. The root returns
AL with RET0; the wrapper leaves its caller's path argument on the stack.
This establishes a private ECX entry, without prescribing a custom source ABI.
The wrapper's independent origin classification remains in review.

The direct Ghidra project was checked against the executable hash, image base,
entry, x86 Windows analysis target, complete mapped text and all root bytes.
The root's 629-byte body, ECX parameter storage and zero purge were read back.
Decompiler output is a hypothesis; imperfect imported I/O prototypes still
distort its stack analysis. Raw instructions establish the facts below.
Two read-only processes ran sequentially with no analysis, CPU0/nice10 and a
384 MiB heap. All nine primary database hashes agree afterward; aliases are
removed. IDA failed identity preflight and provided no semantics.

## Archive format and lifetime

CreateFileA uses GENERIC_READ, share-read, OPEN_EXISTING and flags 80h. Only
INVALID_HANDLE_VALUE returns false. After a successful open, the root saves
the current `vector<string>` size as the new archive index, appends the path,
then publishes the vector's new size to 702914.

The physical vector at 7028F8 has its first and last pointers at +4/+8, with
28-byte string elements. Its direct size reads justify relocation addends
4/8. The store at 41BBB0, reset at 41B9F4 and consumer at 40CF54 establish
702914 as an unsigned 32-bit archive count. The old `void* g_package_file_index`
alias was an unsupported type hypothesis. The first review used an unsigned count alias. The
[physical-store follow-up](PACKAGE_ARCHIVE_STORE_2026_10_19.md) now represents
it as `g_package_archive_store.count_38`, alongside the actual critical section,
names and map owners. The physical address is unchanged.

The input begins with a little-endian unsigned 16-bit entry count and unsigned
32-bit index length. The root allocates a byte array of that length, reads it,
and closes the file **before** decoding. ReadFile statuses and bytes-read
values are ignored. No size/count validation or rollback is added.

Decoding uses the independently exact MT19937 seed/next functions at
406670/4066B0. Seed is index length +6, modulo 32 bits. First every index byte
is XORed with the low byte of the next MT output. The second pass starts with
byte key C5h and step 83h; each byte is XORed with key, then key += step and
step += 53h, both modulo 256.

Each decoded entry is packed as DWORD file offset, DWORD file size, byte path
length, and that many path bytes. The root copies the path to a local buffer,
appends NUL, and invokes register_package_file_entry(path, archive_index,
size, offset) at 41BC9D. Zero-length and embedded-NUL names are not rejected.
Duplicate handling remains the registration routine's responsibility. The
whole index, including trailing bytes unused by parsing, is decoded.

Index allocation calls 665B8A; final release calls the distinct forwarding
entry 68AA26, which jumps to 6898EA. Normal new[]/delete[] source models this
lifetime. Compatible CRT forwarding does not uniquely prove the original
release symbol spelling. The path string temporary instead releases heap
storage directly through 6898EA.
The temporary string is the sole root EH owner. Its assignment has state -1,
push_back has state 0, and index allocation/registration have state -1. The
raw handle and index have no added RAII cleanup on those exception paths.

## Source, execution and comparison

The source uses a normal typed static C++ helper plus its real public wrapper,
native vector/string operations, unsigned byte arithmetic, memcpy and raw
array ownership. Ordinary VC8 naturally passes the private path in ECX and
reproduces the nine-byte forwarding shape. There is no register facade,
assembly, inert local or artificial stack allocation. The 256-byte path
buffer accommodates every stored byte length plus NUL; its original source
declaration remains unknown, and no buffer-size search is used to tune the
frame.

A fresh instruction model passes **100/100 cases**, executing actual target
and selected COFF root/wrapper instructions plus target MT19937 instructions.
An independent Python MT implementation creates the encoded inputs. Cases
include reserved/empty and nonempty archive vectors, both entry stack
alignments, SSO boundaries, failed open with a preexisting count, zero/nonzero
empty indexes, byte-length 255, empty/embedded-NUL paths, high-bit sizes and
offsets, trailing bytes, and 70 records crossing MT twist boundaries. Four
controls stop at string, vector, allocation and registration exception-call
boundaries and compare event prefixes and live EH states.

Coverage is 202/204 reachable target instructions. The two unexecuted
instructions are the nil-vector arm after a successful append: valid push_back
cannot leave its first pointer null. Win32 I/O, STL string/vector operations,
allocation, memcpy and registration are modeled. This does not prove real OS
unwinding, locale behavior, malformed indexes or short-read/uninitialized-data
execution. It provides no partial-byte credit.

Ordinary source is 598 bytes with a 138h local frame; target has a 150h frame
and eight-byte stack alignment. Public vector push_back is 165 bytes/ECX this;
target 41C270 is 162 bytes/private ESI this. Its false binding is deliberately
absent. The formal probe fails closed with `relocation.rel32.unknown_target`
for push_back. No canonical source hash or first byte mismatch is claimed.

A real-source `/GL` closure contains the root/wrapper, selected registration,
opener, node lifetimes, MT19937, selected CRC source, real zlib and CRT providers.
It links without unresolved symbols or force flags. Root is 627 bytes with
frame 148h, still different from target; private seed, registration and vector
boundaries also differ. This is evidence for further compiler/context review,
not original-TU provenance or permission to force those ABIs. The ordinary
source remains selected. The helper's only raw E8/E9 incoming lead is the
loader call at 41BB47, so an undiscovered second direct caller does not explain
this control's different interface. An alternate RTM compiler/linker-path
control, using the installed SP1 object-reader DLL and CRT providers, produces
the same 627-byte/200-instruction root shape, with differing linked addresses. This
mixed auxiliary environment is recorded in its commands; it is not a stock
RTM-release provenance claim. No tool installation or selected profile changes.

After the shared count-type correction, all 15 affected units were cold-built
serially. Their 33 comparison outcomes are unchanged, including all
21 accepted exact functions. The vector relocation-addend expansion is also
rechecked in its opener and new loader consumers. No matches.csv change or
aggregate cold replay is claimed.

Selected loader source SHA256 is
`e36f0cf84dc606510f157d01a69bd3e4f4fbd279275f64fddfe8606213eaab07`.
Reproduce the fail-closed focused probe with:

```bash
python3 scripts/build.py --unit gpt-web-package-archive-loader --compare --json
```

Receipts are under `build/package-loader-20261019/`: target-cfg.json, all raw
assembly, before/after database pins, formal.json, execution.json,
shared-count-controls.json, focused reports and closure commands/map/CFGs.
Private scripts and decompiler hypothesis are below
`.analysis/package-loader-20261019/`. Continue the truthful vector-helper,
EH/frame and translation-unit context review before returning to reader/BMP
code generation. Their previous residuals are not resolved by this checkpoint.

The subsequent physical-store batch rebuilds17 existing affected units and
preserves all36 outcomes/22 accepted functions. Its current-source100-case
loader model is under `build/package-loader-context-20261019/`. Full lifecycle
execution and private constructor/destructor/EH receipts are in the
[store review](PACKAGE_ARCHIVE_STORE_2026_10_19.md). The later formal linked
contract accepts391 lifecycle bytes; the loader remains nonexact. Its fresh
[template/ABI controls and persisted analysis](PACKAGE_ARCHIVE_LOADER_CONTEXT_2026_10_19.md)
supersede the historical independent-global controls for current-source context
claims, without changing this selected source.
