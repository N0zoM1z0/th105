# Audio/network allocation interfaces, 2026-10-19

## Target observations and source correction

This bounded batch uses original Japanese1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Fresh raw CFGs close both complete bodies:

| Root | Bytes / reachable instructions | SHA256 | Allocation CALL |
| --- | --- | --- | --- |
| SFL metadata418D10 | 484 /150 | `3cdccc342d52b6da45d522a9c4cb3e4f9e9e74229910987c36e12fab4e3d6d8a` | 418DD1 ->665B8A |
| Network connection415340 | 542 /160 | `5adc2f59eba3c9831a6813a1bf82cfe0e803ae2e9db354c558524d6f83089b3b` | 4153FD ->665B8A |

There are no outgoing direct branch exits, unreachable decoded instructions
or unresolved indirect jumps. SFL takes its filename in ECX and source pointer
at stack4, returning with RET4. Connection takes its owner in ECX and four
stack argument slots, returning AL0/1 with RET16. Ghidra's input hash/base/
entry/language/compiler, full mapped `.text` and both root spans were attested
before semantic use. Temporary parameter storage was read back; decompilation
was a hypothesis checked against raw instructions. All nine primary DB hashes
remain unchanged and the read-only aliases are removed. IDA failed target
preflight and was not used for semantics.

The665B8A entry is `E9 3C 42 02 00`, forwarding to scalar new689DCB. The earlier
[pinned VC8 library-member check](CBITMAP_BMP_EH_2026_10_19.md) supplies a
compatible array-new provider: libcpmt/newaop.obj,3883 bytes, SHA256
`846dc4ebc80bbbd4708c0697c569bfd807aeb1244c9e11b6001e79213fb94276`,
whose array-new symbol similarly forwards to scalar new. This corroborates the
provider family; five bytes alone do not identify a unique original public
symbol or runtime release. No origin/exclusion or runtime match is added.

The two source files had called CRT malloc and mapped that name to665B8A.
They now include real VC8 `<new>`, allocate `new unsigned char[size]`, and bind
`??_U@YAPAXI@Z` to665B8A. This represents the C++ allocation/exception interface
instead of relying on a C malloc declaration. Byte arrays require no element
constructor or array cookie. Observed CRT free calls remain unchanged.

SFL still owns its FileReaderOwner while allocating and reading. Connection
still frees the old request, writes the new WORD size, then allocates/copies
its replacement; zero size clears the pointer and FFFF preserves prior state.
The old pointer is not cleared before the allocation call, and no failure
recovery or extra rollback is introduced. Its endpoint RAII lock spans the
allocation. This batch changes allocator identity, not those game policies.

## Fresh ordinary and linked controls

Both units were freshly built before and after editing. Full configured
comparison payloads, including relocation replay, are identical in all eight
functions. The root results remain:

| Root | Ordinary candidate / target | First strict difference | Unchanged payload SHA256 |
| --- | --- | --- | --- |
|418D10|463 /484|+10h, frame110h versus118h|`81d2d169d7b4ac2d2292cb092e0c901e2411b8ed95b27ec07eefeca8f52146b9`|
|415340|524 /542|+0, aligned EBP frame|`d86263ae23e1e3c3d7d5c2e15b012028d5d8a9e25797be508bedc6ef76fc5ce3`|

All existing named code containers are byte-identical before COFF relocation;
only allocator relocation identity changes. The Ogg object additionally gains
the real header's bad-allocation message/data and C++ runtime directive.
The accepted network callback41D7B0 remains14/14 exact. Lookup/access controls
4152A0=148 and413740=33 remain exact diagnostics in origin review, without new
authored/source/exclusion credit. The other configured network roots stay
nonexact; their complete payload hashes are unchanged too.

The actual current network source was also freshly linked through the existing
mixed COFF/LTCG recipe with genuine peer-removal, acceptance and thread bodies,
pinned runtime/SDK imports and reviewed nonexecutable IAT/data bindings. It has
zero unresolved implementations, no stub bodies, force flags or executable ABS
bindings. The array call resolves by its real array-new symbol. The complete
connection diagnostic is542 bytes with84 differing bytes and first difference
+14Ch, consistent with the earlier recorded residual. All call fields resolve;
the handler, cookie and worker-pointer HIGHLOW hypotheses remain unaccepted.
This is not canonical acceptance or a runnable standalone game claim.

## SFL visibility and floating-point experiments

Raw target SFL normally inlines FileReaderOwner destruction and retains its
reader in a saved register through cleanup. It converts the cached unsigned
sample rate separately for each quotient and uses two FDIVP instructions;
the default standalone source keeps a converted denominator on the x87 stack.
These observations motivated partial same-TU controls with the retained real
Ogg caller/callback bodies and already-reviewed reader ownership bodies:

| Private control | Complete SFL size | Physical entry / result |
| --- | --- | --- |
|file-local normal cdecl helper|452|ECX filename, stack source, caller pops4|
|file-local normal stdcall helper|454|ECX filename, stack source, RET4|
|same plus actual reader destructor body|470|RET4, normal cleanup inlined|
|same plus local fenv_access(on)|492|two FDIVP, still wrong whole body/frame|
|same under fp:strict|492|two FDIVP, still wrong whole body/frame|
|actual reader open body also visible|475|still nonexact|
|reader open body plus local fenv control|497|still nonexact|

All retain frame110h versus target118h. The ordinary static stdcall definition
lets VC8 generate the observed entry without a register-forcing declaration;
this is evidence about visibility, not a source ABI facade or original spelling
claim. Neither partial entry agreement nor two matching division opcodes prove
the original FP profile. None of these controls changes selected source,
headers, shared flags or comparison acceptance.

These are partial COFF visibility contexts. The retained Ogg caller's
`OggDataSource::open_reader` is still a declaration-only alias for40CF40; its
source definition does not exist. That context has not closed into a genuine
Ogg link. The target calls the reviewed FileReaderOwner operation on the
observed receiver prefix; resolve that source interface honestly before using
whole-program Ogg visibility to explain the remaining frame/register state.
The caller's own ESI entry and helper's private entry also need coupled review.

## Reproduction and remaining work

Public focused commands are the two standard `build.py --unit ... --compare
--json` invocations for `gpt-web-ogg-metadata` and
`cross-v106a-network-winsock-receive-thread`. Private before/after builds,
source/object hashes, raw CFGs, ordinary/formal/section controls, SFL visibility
summaries and Ghidra pins are under `build/allocator-interface-20261019/`.
Drivers and visibility source are under `.analysis/allocator-interface-20261019/`.
The mixed network command/source pins and image/map/replay records are
`build/allocator-interface-network.*`, from
`.analysis/network-udp-linked-20261016/probe-linked.py` and `replay-diagnostic.py`.

The final ledger scan also records seven other nonexact probes that bind
scalar-new symbols to665B8A:419860,419A60,419E80,419590,419690,419950 and46FA90.
Their corresponding source expressions and declarations need separate review;
they are leads rather than automatically invalidated functions. The complete
unit/source/address list is `remaining-array-bindings.json` in the receipt
directory. None is changed in this batch. The later
[gauge/array-declaration checkpoint](BATTLE_INFO_GAUGE_BINDING_2026_10_19.md)
reviews all seven: six are array declarations, while46FA90 actually calls
scalar new689DCB and now matches648/648 after ownership/layout corrections.

No exact authored numerator changes and no cold aggregate replay is claimed.
Keep original compiler/TU ownership, SFL floating-point/frame behavior and
network native EH/GS surfaces open. Continue the archive-loader41BA70/context
review before returning to reader/BMP code generation.
