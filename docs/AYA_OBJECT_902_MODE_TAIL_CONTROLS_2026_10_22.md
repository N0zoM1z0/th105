# AyaObject902 mode-tail source controls

This bounded follow-up to the [spawn-prefix recovery](AYA_OBJECT_902_SPAWN_PREFIX_2026_10_22.md)
keeps the selected source at fbb53eb unchanged. Seven complete-root VC8 builds
were run serially on CPU0/nice10. Target verification/status/tracking passed;
IDA again rejected the other image. All observations below use the original
Japanese1.06a hash-attested PE, not that IDA session.

## Observed target edges

In root61A290, action902's mode table dispatches to four comparisons:

| Mode | Compare | Shared conditional edge |
| --- | --- | --- |
|3|61E5B2: counter versus600|61E5BC JG61E5CD|
|2|61E5F1: counter versus500|JMP61E613|
|1|61E5FD: counter versus320|JMP61E5BC|
|0|61E609: counter versus180|61E613 JG61E624|

For3/1,61E5BE loads the owner,61E5C4 compares signed health with CX, and
61E5CB branches to61E634 when positive. The actual call prefix at61E5CD
loads the vtable and slot14, sets ECX=this, clears BYTE184 and calls EAX.
61E5DD then loads signed facing into EAX, spills/FILDs it and jumps61C4B0.
The2/0 pair uses the analogous EDX owner/call carriers at61E615/61E624.
Its shared movement entry is61E634, also ending with JMP61C4B0.
The current source shares the3/1 comparison/call region at the later physical
case1 location. Equal conditional behavior does not establish this placement.

## Controls and results

The source variants preserve useful operations and real control-flow edges;
there are no fake ABI declarations, padding or inert locals. They are private
hypotheses, not selected reconstructions.

| Source control | Full bytes | Canonical SHA256 prefix | Result |
| --- | ---: | --- | --- |
| Repeat movement/return in mode3 |20132|e69c24b7|Rejected|
| Repeat movement/return in modes3/1 |20132|a6733130|Rejected|
| Repeat movement/return in all four modes |20204|875e3fb6|Rejected|
| Move the single shared tail after mode3; incoming GOTOs |20064|d08781e4|Byte-neutral|
| Move the single shared tail after mode0; incoming GOTOs |20064|d08781e4|Byte-neutral|
| Express mode3's healthy/in-time condition as early BREAK |20064|d08781e4|Byte-neutral|
| Express both modes3/1 with early BREAK guards |20064|d08781e4|Byte-neutral|

All four neutral controls have the **complete**, identical SHA256
`d08781e483c6d906dfce2de93a56b5df0bca35d541564ad28f5d9655addc53c3`.
This is not a comparison of only the first mismatch or of a truncated owner.

The mode3 repeated-return control expands902 from652/159 to718 bytes/175
instructions. Its real extra return path changes register allocation upstream:
EDI acquires-1, EBX uses LEA[EDI+2], and the negative spawn side becomes PUSH EDI.
The movement multiply/add/store also stays inline instead of sharing the
observed61C4B0 tail. Merely getting the mode3 call earlier is not an improvement
that justifies losing the already recovered prefix. The other repeated-return
controls likewise enlarge the complete root; none is selected or claimed
behaviorally proven by the successful selected-source fixtures.

## Consequence and limits

These seven controls show that moving the single lexical tail or changing
these guards does not overcome this compiler's current merge decision, while
repeated returns perturb more than the intended block. They do **not** prove
that a standalone native object is impossible, that LTCG is required, or that
all source forms are exhausted. Do not repeat these controls without another
lead. A future change needs evidence about the surrounding merge context or
real value lifetimes; the903 numerical paths remain a separate useful lead.

The configured selected root was rebuilt after the controls and still fails
canonical comparison at offset34/hex22, target0F versus candidate59, with
full20064 and the same compared-window SHA256
`e51da96720d42d51649f5df692080214f82b3d3fa3004e889c64b59b812c63ad`.
No source, ABI, manifest, accepted-unit or exact-ledger change follows.
No all-unit cold replay is claimed or needed for unchanged selected inputs.

## Receipts and storage

Recipes and all complete CPP inputs:
`.analysis/aya-902-mode-tail-20261022/{probe,placement,guard}.py` and sibling CPPs.
Build/provenance/comparison receipts and `mode3-owner.json`:
`build/aya-902-mode-tail-20261022/`.
`current-formal.json` is the final configured rebuild report.

The fourteen completed private OBJ/BIN files were compressed into
`build/aya-902-mode-tail-20261022/completed-controls.tar.gz`:
421977 original bytes to107600 archive bytes. Every decompressed member's length
and SHA256 was verified before removing the originals; member hashes remain in
`archive-verification.json`. Archive SHA256:
`85d1009d5a3ef6243722c1e9336f4a65d12b234260e1484ed4255c5f71357e`.
Selected configured object, predecessor object, source recipes and JSON receipts
remain available. Restore archive members before rerunning an owner audit;
regeneration scripts also rebuild the same private paths.

Final gate: `python3 scripts/ci.py` and `git diff --check`; stable checkpoints
use the current `gpt-6-astra-medium:` prefix. This is a recorded negative-control
result, not new exact credit.
