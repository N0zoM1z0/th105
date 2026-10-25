# IkuObject update632C30: complete target boundary

This is the next large exact-first root after the neutral Komachi600390
context controls. It has no selected source or exact credit yet. The complete
hash-attested target boundary and compiler switch metadata are now independently
reviewed; do not infer a source boundary from the old IDA candidate alone.

## Observed target and boundary

Only Japanese1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. The authored roster-object origin anchor pins primary slot28 cell
`6C64CC` to632C30. The same owner's slot3C cell6C64E0 points to the separately
accepted initializer63B310. Its exact source is family context, not evidence
that this update already matches.

| Region | Reviewed extent |
| --- | --- |
|Callable|632C30..63AF80 inclusive /33617 bytes|
|Compiler alignment|63AF81..63AF83 /`8d4900`|
|Primary destination table|63AF84..63AFFB /30 DWORDs|
|Actions800..998 remap|63AFFC..63B0C2 /199 BYTEs|
|Remap alignment|63B0C3 /`90`|
|Secondary tables|63B0C4..63B30B /24 tables /146 DWORDs|
|Following separation|63B30C..63B30F /four INT3 bytes|
|Next independent initializer|63B310, outside the update payload|

Callable SHA256:
`138baaf0eb38d0e9c40e3dbace9bf7c89ca77bcd520f01a01d79d5ba29368ddf`.
Full34524-byte payload SHA256:
`7c578a068ac0dac2e594bcadcf05671ced799940e8c730f0998c9657bd04525a`.
The five bytes immediately before632C30 are INT3 separation after the independent
27-byte helper632C10.

Raw decoding accounts for7904 instructions. CFG traversal reaches7903 /
33614 bytes, including all44 RET0s; there are no escaping edges or external
tails. The sole unreachable instruction is `639FFD:8d4900`, an actual internal
alignment instruction. The audit requires its exact address and bytes; it
cannot waive another instruction as padding. All176 table targets are decoded
instruction starts. Primary dispatch has29 nondefault action entries plus the
common default return63AF79. Secondary table lengths, in address order, are
7,6,5,6,5,7,10,5,4,6,7,5,6,9,7,8,4,9,4,4,4,9,4,5.

```sh
taskset -c 0 nice -n 10 scripts/repo-python \
  scripts/audit-iku-object-update.py --target-only
scripts/repo-python -m unittest discover -s tests \
  -p test_iku_object_update_audit.py -v
```

The first command re-attests the PE, both vtable cells, callable/full hashes,
metadata coverage, direct-call census, exact unreachable bytes and closed CFG.
The second passes eight synthetic controls without requiring game bytes.
No source implementation, canonical acceptance or masked score follows from
this target-only result. The next complete-source comparison must replay the entire emitted section
without a length mask; an object comparison is not configured at this checkpoint.

## Observed call and storage contracts

There are316 physical direct calls to23 entries and15 indirect calls. The
indirect call sites load primary slots0C (nine calls, four-byte argument) and14
(six calls, no stack arguments). Raw receiver flow uses ECX=this. The main
prologue aligns ESP to8, reserves0x258 bytes and saves EBX/EBP/ESI/EDI in
addition to its frame pointer. No EH/GS prologue appears in this bounded root.

| Direct entry | Calls | Reviewed contract |
| --- | ---: | --- |
|5575C0|19|ECX receiver, three integer slots, RET12, consumed AL|
|435160|36|ECX=this+4, two float slots, RET8|
|4351C0|16|ECX receiver, no arguments, consumed AL|
|4067D0|70|cdecl integer bound, EAX result|
|4963A0|28|ECX receiver, one integer slot, RET4, AL result|
|45C030|7|ECX receiver, one handle slot, RET4|
|64CCB0|56|Unparented request, seven slots, RET28|
|64CD00|18|ECX receiver, one integer slot, RET4, AL result|
|632C10|2|Two byte carriers in four-byte slots, RET8|
|496370|2|One alpha byte carrier in a four-byte slot, RET4|
|406540|5|cdecl two floats, x87 float result|
|435D60|15|ECX receiver, no arguments, x87 float result|
|5B0400|9|ECX receiver, two integer offsets, RET8, owner pointer in EAX|
|406360|7|cdecl float, x87 double sine result|
|435240|1|ECX receiver, five slots, RET20|
|4E0BF0|1|ECX receiver, three floats, RET12|
|4FCA60|6|Parented request, seven slots, RET28|
|4063D0|4|cdecl float, x87 double cosine result|
|68A1A0|8|Compiler conversion, implicit ST0 input/EAX32 output, no stack args|
|4FC710|3|ECX receiver, four integers/three short carriers, RET28|
|478DD0|1|cdecl float, x87 float square-root result|
|53CBC0|1|ECX receiver, no stack arguments|
|435520|1|ECX receiver, two floats, RET8|

These declarations draw on independently accepted helper bodies and this root's
actual call/cleanup/width evidence. They do not import helper implementations
or claim the original owner's nominal layout. In particular68A1A0 must remain
a normal C++ numeric conversion, not an ordinary invented external declaration.

Private depth analysis follows incoming ESP depth through every reachable edge,
including all direct/virtual purges. At each of the62 parented/unparented calls
it proves the actual LEA and register PUSH at argument+20. It finds48 distinct
consumed packet bases, rather than one shared temporary array. This is storage/
visibility evidence for the first complete source; it does not prove48 original
source variables or prescribe a stack layout. No inert storage, union, padding
or register forcing is authorized by that observation.

## Analysis state and next action

The GUI IDA preflight rejects its different executable SHA10350095; no GUI
analysis calls or metadata writes are used. Raw PE inspection remains valid.
One direct Ghidra run independently attests executable identity, entry point,
Windows x86 language and every mapped section against the pinned PE. Its
complete33617-byte temporary root and reviewed callee ABI views are read back.
The first decompilation times out at60 seconds: no pseudocode from that run is
used. Temporary entry removal and transaction rollback are read back, and all
nine primary database-file hashes remain unchanged. The failed receipt is retained separately. A serial retry extends only the
timeout to240 seconds and completes the decompiler hypothesis. It again passes
identity/mapped-byte/body/ABI readback, entry removal/rollback, and all nine
unchanged database-file hashes. Both runs keep one core/384MiB heap. No database
metadata is accepted or saved by these temporary analysis views.

Generated observations, the raw/depth driver and the readonly script are under
`build/exact-first-iku-object-update-20261025/` and
`.analysis/exact-first-iku-object-update-20261025/`. Analysis artifacts remain
private. The next step is manual complete-body source from these exact
instructions, then early full34524-byte canonical comparison. Numeric states,
offset accesses and declaration-only interfaces remain appropriate. Complete
source semantics, original TU identity and recoverable standalone exactness
are still unknown. The accepted graph is unchanged; no new aggregate cold
replay is claimed at this boundary-only checkpoint.
