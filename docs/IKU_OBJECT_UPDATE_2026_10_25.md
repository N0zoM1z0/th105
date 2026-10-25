# IkuObject update632C30: complete target boundary

`IkuObject_update_action_state @632C30` now has a complete manual source
hypothesis in `src/characters/IkuObjectUpdate.cpp/.hpp`, covering29 nondefault
actions and the default exit. It is source-present, **not canonical exact**.
The first complete compile is compared before any source-shape trial. The
selected complete34748-byte section replays1014 relocations but differs from
the full34524-byte target at32281 unmasked bytes, first632C55/+37. Its canonical
SHA256 is `52ee04c5f7cbc0527759971a519fb21e17d0318815a6803b424db24808312910`.
Both formal and independent cold compilations retain this same full result.

The source naturally reproduces the target0x258 aligned stack frame, all25
switch-table dimensions/176 destination DWORDs,199 identical action-remap bytes
and its90 alignment byte. Those structural facts do not establish byte or
execution equality. Accepted exact totals are unchanged.

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
this target-only result. The default audit now separately replays the entire
emitted COFF section without a length mask and reports complete mismatches.

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
including all direct/virtual purges. It checks the packet-register PUSH at argument+20 for62 physical requests
and identifies48 distinct nearby LEA witnesses; all count arguments are3.
This local witness analysis is not a complete predecessor-sensitive pointer
proof: shared634714 can receive the preceding high-skill packet or the later
random packet. Its nearest lexical LEA does not describe every incoming path.
The complete source keeps48 actually consumed float[3] packet views and checks
these shared predecessors manually; it does not claim48 original declarations
or force their offsets. No inert storage, union, padding or register forcing
is used. The natural first source already reserves0x258 bytes.

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
private. The decompiler reports incomplete stack-spacebase tracking, so its
stack names and array extents are not copied into source. Raw pointer pushes,
comparison flags, store widths and actual branch merges supply the missing
constraints. Original source spelling, nominal full layout, TU identity and
recoverable standalone exactness remain unknown.


## First complete comparison and evidence-backed trials

Only the complete632C30 body is compiled; helpers remain declarations. The
partial primary-vtable view is pointer-only and must never be constructed or
embedded. Signed byte facing/skill accesses, unsigned color bytes, signed WORD
state/counters, actual owner versus opponent/related pointers, and float/double
rounding/capture boundaries remain explicit. Compiler conversions to int/short
use normal C++ casts. Two float-to-color-byte casts independently reproduce
two FISTP m32 operations with two FNSTCW/four FLDCW instructions, including
restoration of the control word. They do not call a fabricated helper.

| Complete source trial | Full bytes / SHA prefix | Observed result |
| --- | --- | --- |
|First complete body|35384 /005d3ee9|33084 unmasked differences, first+37; frame0x258; all25 table dimensions/remap bytes|
|Shared ground continuation, selected|34748 /52ee04c5|32281 differences, first+37; restores target height/advance-six physical counts|
|Outer-case break control, unselected|34872 /8af10a41|31789 differences; grows23 excess RETs to27 and loses another relative-position physical call|

The first complete body uses29 advance-six calls versus target28 and16 height
calls versus15. Native812/0 and852/0 keep distinct first height calls at633EE9
and636B5E, then share the conditional second height call636B70 and advance-six
call636B80. The selected source expresses exactly that common continuation,
without merging the two initial calls. It reduces the section by636 bytes and
restores both relevant physical counts. It also changes other compiler sharing;
there is no claim that fewer differing bytes alone proves correctness.

The next trial asks whether completing the outer action cases through the
common switch exit explains the target's fewer epilogues. It does not: source
RET count rises67->71 versus44 target, and relative-position calls fall9->8
versus9 target. Its lower raw mismatch count is insufficient grounds for
selection. Keep it unselected and do not repeat that source spelling absent
new independent evidence.

The selected source has314 direct calls/23 entries versus316 target,14 virtual
calls versus15, and67 RETs versus44. Counts for21/23 direct callees agree; the
remaining entries are frame advance15 versus16 and unparented request55 versus56.
Every one of the29 action-level static CFG reachable-call inventories agrees,
including virtual-call counts. This over-approximates branches; it is neither
path-feasibility nor execution-equivalence proof. The aggregate physical
mismatches are compensated sharing differences, not permission to ignore bytes.

Concrete remaining witnesses include target801-only633349 and818-only635D8E
requests merged in source635B3C; target810-only633CAD and851-only636B1F virtual
calls merged in source636911; and differently partitioned frame continuations.
The source additionally splits the target's801/813 shared selector. Examine
actual value ownership, publication/capture and return epochs next. Do not
force registers/frame storage or start a compiler-flag grid.

910 phase0's three limit/period selections and920 phase2's duration selection
have no default assignment for global values outside0..3. The source retains
real consumed locals with the same absent default, rather than inventing a
fallback. The original valid-global-value contract and defined behavior for
such invalid states remain unknown. No large execution matrix is run to hide
this ambiguity; a concrete invariant or caller audit is needed if it matters
to a later exact/source question.

## Reproduction and checkpoint scope

```sh
taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py \
  --unit exact-first-iku-object-update --compare --json
scripts/repo-python scripts/audit-iku-object-update.py
TH105_ENABLE_GS=0 TH105_FP_MODE=default TH105_INLINE_MODE=default \
  taskset -c 0 nice -n 10 scripts/compile-unit.sh \
  src/characters/IkuObjectUpdate.cpp \
  build/exact-first-iku-object-update-20261025/cold.obj
scripts/repo-python scripts/compare-unit-object.py \
  exact-first-iku-object-update \
  build/exact-first-iku-object-update-20261025/cold.obj --json
scripts/repo-python scripts/audit-iku-object-update.py \
  --object build/exact-first-iku-object-update-20261025/cold.obj
```

The compile returns0; each comparison/audit returns1 with a real nonexact
result. The existing-object comparator correctly leaves build provenance
unverified; the separate cold compile/log supplies its evidence. Formal build
metadata pins source/header/compiler/profile hashes. Full canonical audit
replays all1014 root relocations and reports SHA52ee04c5 for both objects.
All108 new floating aliases are exclusive to this new nonexact unit; no existing
accepted literal binding/header/layout/compiler setting is changed. Floating
audit checks1671 target references:397 ledger literals/1274 explicit mappings.

A fresh private COFF negative changes only the cold object's first PUSH opcode
55->56. The complete audit rejects it at+0,32282 differences, canonical SHA
`24f9c84977e90874967a1475c32f2d0223859b017a98cd5a41dd347b8bdc213c`.
Target PE, selected source and original cold object remain unchanged. Generated
trial/first/full/formal/cold/negative/per-action receipts are in the existing
build directory; `checkpoint-receipts.json` pins source snapshots/object hashes.

This checkpoint adds one mapping, one complete source selection and one probe
unit, not an exact function. Claims remain header-only. The accepted graph
remains524 units/1412 functions/381108 callable bytes; no fresh aggregate cold
replay is claimed. Continue632C30 from the complete-source comparison.


## Return-path and direction-view controls; bounded stop

Fresh target/status/tracking checks retain only JP1.06a. GUI IDA again rejects
SHA10350095, so these controls use raw PE facts and the pinned local compiler.
The selected source/header/profile/bindings remain unchanged. No Ghidra launch,
shared provider edit, accepted-unit change or execution matrix is needed.

Native ordinary retirement632E3B decrements330 and returns; many real edges
enter it. A complete private candidate changes only the RETIRE source macro to
a jump to one actual shared decrement/return. It adds no storage, fake return,
extra behavior or register constraint. Its full34088-byte output SHA
`07ab6c2297fa8d843d4126f9f6d245c6686ccf3145b3ac31a6565e33e324d2a4`
remains nonexact32017 bytes, first+37. Returns fall67->46 versus44 target,
but frame-advance calls fall15->14 versus16 target. Unparented requests55 and
virtual calls14 still differ from56/15. This globally shared source exit
therefore over-factors actual contexts; fewer RETs do not establish acceptance.
Keep the complete candidate unselected. Recovering the target's separate exits
requires actual publication/value-lifetime evidence, not repeating a goto or
subtraction spelling.

For the independent direction question, fresh raw Iku manager631140/237 reads
CL from BYTE[ESP+20] at6311E2 and stores it to BYTE[ESI+104] at631200. DL handles
the distinct33C byte. Its accepted complete source also uses a signed-char
facing formal. The [complete shared-provider width witnesses](REIMU_OBJECT_822_DIRECTION_WIDTH_2026_10_22.md)
independently admit byte-facing Object wrapper definitions/callbacks with the
same native bodies77/78 bytes. The new raw Iku consumer check avoids substituting
Reimu's manager for Iku. Width support does not prove original wrapper formal
signedness or nominal class/TU identity.

Two complete private callers start separately from the selected source, without
the global-retirement trial. They refine only parented/unparented direction
formals to unsigned char and signed char respectively, retaining four-byte
argument slots, native targets, other parameters, vtable order and real data
flow. Both canonical whole sections are **34364 bytes with identical SHA**
`193a73db708bf0513873f86464f4a2f9417eaf70a9834372a8a5a93299c8e157`,
32241 unmasked differences, first+37. Their56 RETs,13 frame-advance calls,
55 unparented requests and13 virtual calls still differ from44/16/56/15 target.
Do not confuse matching instruction counts or a closer section size with byte
equality. The narrow views remain unselected, and repeating signedness changes
is closed after the two identical full outputs.

All three controls retain frame0x258, all25 table dimensions/176 DWORDs and the
same199-byte remap/90 alignment byte. All29 action-level static reachable-call
counts agree with the target for each candidate; this is not path feasibility
or complete execution equivalence. Canonical replay covers every1010 root
relocation for common retirement and1011 for each byte view, without masks.
Generated full reports/bindings/per-action diagnostics/manager-width packet and
`control-receipts.json` are under `build/iku-update-returns-20261025/`; private
complete sources/drivers are in its same-named `.analysis/` directory.

Fresh formal/full selected-source comparison still emits34748 SHA52ee04c5,
32281 differences/+37. No source, type/header, literal binding, function mapping
or exact credit changes. Park632C30 rather than repeating the two closed source
questions. Next independently inspect the source-missing authored YukariObject
slot28 candidate58DB80, provisional33972 bytes, ledger anchor6C586C. Its same-owner
initializer5964C0 has complete nonexact source; it is a hypothesis/family lead,
not an exact representative or proof of the new root's boundary or ABI. The
separate shared980 continuation596370 is already exact323 bytes and must not
be absorbed into the adjacent update. No compiler/LTCG impossibility is claimed.
