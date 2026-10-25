# Tenshi Object update boundary and resume point, 2026-10-25

**Observed boundary/ABI and private partial draft only.** Root64CD50 remains
unclassified/source-missing in the public ledgers. No complete-source build,
source selection, new match unit or exact claim has been made. The user requested
session handoff before completion of the first body.

## Target observations

Original Japanese1.06a SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Primary Object vtable6C670C, slot28 cell6C6734 ->64CD50. Same-owner initializer
657150, slot3C cell6C6748, is separate source-present/nonexact context only.

Main `[64CD50,656D79)` is41001 bytes, SHA-256
`d5ed24f23b4e6e385588593fe81b5e9ec83bd77c402fa7a3d387412823e571b2`.
All9800 instructions decode;9797 reached instructions cover40993 bytes. The
three unreachable alignment instructions are64FFDD:8d4900,65269D:8d4900 and
65561E:8bff (eight bytes). All67 exits are RET0, no escaping branches or tails.

Full `[64CD50,657150)` is41984 bytes, SHA-256
`44fedf398c8bfbf882959b4a8d33f15217a8a4ddca02cdbcb695fd330af82fc4`.
It owns28 tables/195 destination DWORDs,199 remap bytes at656DF0 and alignment
656D79:8d4900 /656EB7:90. Seven leading INT3 bytes separate64CD00's provider.
There is **no trailing INT3 gap**: the last table ends at initializer657150.
Default656D6C calls4351C0 once, ignores AL and performs the aligned RET0 exit.

Nondefault actions:800,801,810,811,815,816,820,821,825,848,850,851,852,853,854,
855,856,857,900,920,930,940,960,961,962,980,997,998. Primary dispatch stops at998.

## ABI facts and interpretation limits

thiscall/RET0, `PUSH EBP; MOV EBP,ESP; AND ESP,-8; SUB ESP,2A8`, then saved
EBX/EBP/ESI/EDI. ESI is the primary receiver. Restore with MOV ESP,EBP/POP EBP.
The cause of source-level alignment is not recovered; do not force it with
padding or inert doubles. Write complete natural source before codegen controls.

The427 direct calls use22 entries.22 virtuals use the primary Object at slots
0C/14/1C/20; their providers45C390/45C220/45C180/45C1A0 are independently exact.
The remaining virtual651AD3 calls **manager slot04**, with ECX from
`parent+658`, nine four-byte argument slots and RET36:
`(0, self[16C], 853, x, y, facing, layer, packet, 3)`.
Do not give that call the primary Object slot/purge contract.

Surface helper434EE0 is stdcall, three float arguments, RET12. Sequence helper
4399C0 is thiscall, one unsigned index, pointer/reference result, RET4; both
callers use parent+55C as receiver and read the first WORD. This generated
std::deque island is excluded from authored progress. All other direct call
contracts are retained in the private Java/stack recipes and ordinary accepted
provider sources; no new callee implementation credit is implied.

Backward tracing from actual packet and count argument slots closes97 requests
(85 unparented,11 parented,one direct factory) with53 bases/652 bytes. No pointer
or count definition remains unresolved under the recorded call/clobber/span
contracts; this is not general alias/path-feasibility proof. Most packets have3
words, but p244/654639 has4, p384/65473F has5, and p520/654AF8 has4. p520 is
also used with count3. Preserve per-call counts and independently initialized
words. There are46 qword stack accesses at relative offsets -680/-672/-664;
the dataflow is not permission to add artificial alignment storage.

## Available material and exact next step

The raw shared-callee census ran first. One readonly/noanalysis Ghidra process
used384MiB, independently checked import SHA/entry/all mapped bytes, read back
its temporary call views and rolled back. Sentinel
`TENSHI_OBJECT_UPDATE_READONLY_ATTESTED`; all nine primary DB hashes unchanged.
The decompiler reports an inability to track stack spacebase fully. Use it as
reading assistance only; the raw PE and predecessor/count facts are authoritative.
For example, its undefined4 heading-pointer cast does not justify integer
conversion: native64CFF6 reads H[1] using FLD before FADD.

Private recipe/draft directory:
`.analysis/exact-first-tenshi-object-update-20261025/`.
Observed JSON/assembly/logs and reading worksheet:
`build/exact-first-tenshi-object-update-20261025/`.
`probe.cpp` is71 lines with **only800/801**; `probe.hpp` is32 lines. The switch
and function are intentionally incomplete. No compiler was invoked. Review
these two cases, then write810 onward manually; never compile/promote a partial
body. The worksheet/decompiler must not be mechanically translated into source.

Keep actual short/byte widths, repeated calls and receiver/heading capture epochs.
The first complete body should be compiled and compared against the entire
41984-byte payload before shape controls. Create public audit/unit/ledger entries
only after independent full semantic/boundary review. Full size, table/call counts
and local windows alone never qualify as exactness.

The local31-file resume bundle and its SHA/restore notes are in
[the live handoff](RE_HANDOFF.md). It contains no target executable, compiler
installation or database. Private observations are not committed artifacts.
