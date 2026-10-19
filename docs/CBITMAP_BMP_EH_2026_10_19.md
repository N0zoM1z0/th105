# CBitmapData BMP: EH lifetime and allocator-interface evidence

Continuation of [the boundary/source-form audit](CBITMAP_BMP_2026_10_19.md),
with one writable scope: authored BMP root `0x00419FF0`. This checkpoint
checks the remaining lifetime assumptions against current target and compiler
evidence.
Original Japanese1.06a SHA256 remains
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
**No new authored exact credit.** The2230-byte callable boundary is unchanged.

## Target EH chain and compiler observations

The handler pushed at419FF2 is `6BDC3B`. It checks an encoded stack cookie
through689D25, loads EAX=`6E42B4`, then tail-jumps to6899E7. The latter is the
frame-handler entry referenced by the compiler's `___CxxFrameHandler3`
relocation. FuncInfo-style data at6E42B4 contains magic19930522, state count1,
unwind table6E42AC, zero further table/specification fields, and flags1.
The single unwind entry is previous state-1, cleanup action6BDC30. Named
VC8 COFF records corroborate this layout; field names alone are not target
source evidence.

Cleanup `[6BDC30,6BDC3B)` is `LEA ECX,[EBP-428h]` followed by a tail jump to
40CF20. That15-byte reader-owner destructor loads its owned reader, tests it,
and calls virtual scalar deletion with argument1. Exception cleanup therefore
uses the out-of-line owner destructor while normal main-body cleanup expands
it. The target supports one EH-managed owner lifetime; it supplies no evidence
for an additional EH-managed palette/buffer owner.

| Target region | Bytes | SHA256 |
| --- | ---: | --- |
| Cleanup plus handler `[6BDC30,6BDC5C)` |44|`a683fc1ec26d01bd83d23d1a6e3f0515a03249a8e5d3bd05384590a1f69d9e32`|
| Unwind table plus FuncInfo `[6E42AC,6E42D8)` |44|`ccb85b9fdaba12e79b13d719800f8eb9b115f52f578e5f7c11b3bb61533f194a`|

Private replay of the generated COFF metadata binds the destructor, cookie
check, frame handler, FuncInfo, unwind table and cleanup symbols to those
observed target references. This is compiler-metadata investigation, not
acceptance of another authored function:

| Region | Source/target bytes compared | Differing bytes |
| --- | ---: | --- |
| Cleanup thunk |11|One: owner offset-438h versus-428h|
| EH handler |33|Two: cookie-base/cell offsets differ by8|
| Unwind entry |8|Zero after its action-pointer relocation|
| FuncInfo |36|Zero after its unwind-table relocation|

An actual inline destructor definition in the existing diagnostic header
switch gives the same metadata and canonical body as the earlier visible
out-of-line definition. It does not recover the frame. No shared owner
header or destructor definition is changed publicly. Matching these metadata
fields does not imply that main-body differences are only stack offsets.

A completed direct Ghidra run independently checks imported/raw executable
identity, entry/base/language/compiler, the complete mapped .text, root hash,
and both EH-region hashes. Read-only typed table creation is read back and
its44 bytes rechecked. All nine primary DB hashes remain unchanged; aliases
are removed. Only completed attested output is used. No target bytes change.

## Stack workspace, using entry ESP as the reference

Let E be ESP on entry, pointing at the return address. Normal CFG ESP
propagation, with checked callee cleanup contracts, closes all666 target
instructions and every RET4. The selected candidate similarly closes629
instructions. This is stack-access evidence, not alias-aware compiler liveness.

| Property | Target | Selected candidate | Member32 diagnostic |
| --- | --- | --- | --- |
| SUB ESP frame |430h|438h|42Ch|
| Steady ESP |E-450h|E-458h|E-44Ch|
|1024-byte palette start |E-40Ch|E-40Ch|E-40Ch|
| Scalar workspace below palette |48 bytes /12 DWORD bins|56 /14|44 /11|
| Owner referenced by EH cleanup |E-428h|E-438h|Not selected|
| Magic-word storage |E-420h|E-420h|Not needed for this control|
| Registration record / state |E-Ch / E-4h|E-Ch / E-4h|Same frame-relative end|

The palette itself does not account for the extra8 bytes. The owner offset
also differs by16, so simply reducing SUB ESP by8 would not recover its
placement. No such byte/stack adjustment is used.

Between the palette32 allocation return and switch dispatch, target writes
five distinct scalar stack locations: palette32 and four address deltas.
Selected source writes seven: palette32 and six address deltas. Target keeps
two of those deltas in registers and reloads the palette base after the loop;
selected source keeps the base in a register across the loop. Palette16 has
the analogous target base reload. These observations focus the next inquiry
on table-address induction and base-pointer lifetime, without proving the
original source spelling or optimization phase.

## Allocation interface correction

The root's seven array allocations call665B8A, a five-byte E9 forwarding entry
to689DCB. Reader-opening helper40CF40's scalar allocations call689DCB directly.
Previous BMP COFF used scalar `??2@YAPAXI@Z` even for array expressions because
the TU lacked array-new declarations. Including the real VC8 `<new>` changes
all seven to `??_U@YAPAXI@Z`, preserving their cdecl size/pointer ABI.

The pinned SP1 `libcpmt.lib` member `build/intel/mt_obj/newaop.obj` provides a
compatible counterpart: its `??_U` body is five-byte E9 with one REL32 to
`??2`. Extracted object size3883, SHA256
`846dc4ebc80bbbd4708c0697c569bfd807aeb1244c9e11b6001e79213fb94276`.
This corroborates the array-allocation binding; a five-byte alias alone does
not prove a unique original public symbol or target runtime release. Existing
compiler/excluded classification is unchanged; no runtime/authored match is
registered from this corroboration.

```bash
python3 scripts/extract-msvc-library-object.py --library libcpmt \
  --object newaop.obj --output build/cbitmap-bmp-eh-20261019/newaop.obj
```

Public changes are the real include and array-allocation symbol mappings in
the four affected CBitmapData functions. Canonical BMP payload remains
`630c5b9151d678505cf448c106ad38a0d30c267da3c08a119166b449977ec2a1`:
2133 callable +3 alignment +45 metadata bytes. Updated source SHA256:
`109e8b2c2dea528c4bf6969b929f7979d486e961bcda061a11653ae721af2ed7`.
All five previously accepted siblings still compare exactly. PNG/file loaders
remain nonexact680/703 and440/448; BMP still differs first at+10h.

Paired whole-program context probes (/GL compile, /LTCG link) differ only in the include, and link real
FileReader/CRT definitions with exported root/open/global-data contracts.
Both emit2152 callable/2197 section bytes and frame438h. With scalar symbols
bound to689DCB and array symbols to665B8A, all21 differing bytes lie in the
seven allocator REL32 fields; every other canonical byte agrees. Thus the
interface correction fixes provider identity but does not fix code generation.
`open_package_file_entry` remains unresolved via /FORCE in these diagnostic
links, so they are not runnable/acceptance artifacts. In the actual opening
helper the package-entry CALL is41BFA0, not the separate40CF30/41BA70 path.

## Source-shape controls retained privately

All are ordinary /O2 probes with the real class widths, no fake locals,
padding, register constraints or changed calling conventions:

| Control | Callable / section | Frame / observation |
| --- | --- | --- |
| Inline owner destructor |2156 /2201|438h; same as previously visible real destructor|
| Real `<new>` declarations |2133 /2181|438h; complete canonical payload unchanged|
| `<new>` plus inline owner destructor |2156 /2201|438h; complete payload unchanged from inline-owner control|
| Color assignment method |2133 /2181|438h; no frame recovery|
| RGB1555 member conversion only |2133 /2181|438h; source induction changes|
| ARGB32 member conversion only |2069 /2117|42Ch; pointer/count loop differs from target|
| Both member conversions / plus assignment |2053 /2101 each|42Ch; the two complete payloads agree|
| Both member conversions plus visible destructor |2076 /2121|42Ch; still nonexact|
| Four explicit ARGB32 member calls per iteration |2069 /2117|42Ch; no frame recovery|
| Three scalar channel arguments to free inline converters |2133 /2181|438h; complete selected payload unchanged|
| Explicit palette16 output iterator |2133 /2181|438h; no frame recovery|
| Explicit palette32 / both output iterators |2053 /2101 each|42Ch; different induction, still nonexact|
| Allocating palette32 helper taking the256-entry array by reference |Not canonicalized|Ordinary inliner retains a new local CALL absent from target|

Smaller code or a frame numerically nearer430h is not a match. None of these
API/iterator/helper controls is selected. TH075's retained source search
provided only clear-color API examples, no BMP/palette reconstruction to
corroborate a shared implementation.

## Receipts, validation and next action

Fresh comparison command remains:

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-cbitmap-data-runtime --compare --json
```

The local gate initially exposed a stale workflow test requiring the historical
`2197/2230` evidence substring. It now pins the attested callable end41A8A5
and nonexact percentage instead of a changing COFF section-size phrase.
All five accepted-function checks remain intact.

Private scripts: `.analysis/cbitmap-bmp-eh-20261019/`, including `audit-eh.py`,
`stack-atlas.py`, the source controls and paired link commands. Receipts:
`build/cbitmap-bmp-eh-20261019/`, including `array-interface-unit.json`,
`*-eh.json`, `*-stack.json`, Ghidra attestation/hash readback, and
`array-interface-pair.json`. Generated data, compiler members and linked
images stay untracked. Previously checked149 execution cases still apply to
the unchanged canonical selected payload; no new behavioral scope is claimed.

Next constraints: recover how the original indexed conversion preserves its
working registers while reloading heap bases, and obtain truthful reader/
package-provider context before relying on an LTCG explanation. The213-byte
40CF40 opening helper already has retained source but no accepted mapping/
unit member; reviewing it is a concrete dependency step for this large loader.
Keep BMP as the active substantial-function objective. No aggregate exact
percentage or cold-all replay is claimed.
