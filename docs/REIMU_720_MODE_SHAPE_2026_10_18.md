# Reimu720: four random-angle mode loops

## Target observations and source hypothesis

Target is original Japanese TH10.5 v1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Parent `Reimu_dispatch_action_state_vslot28 @478FA0` remains81550 callable
bytes, SHA256 `dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6`.
Its candidate/origin/name/source rows remain authored, unclassified and
declaration-only. No implementation or exact credit changes.

Action720's physical owner `[48BC4D,48C1F8)` is1451 bytes/376 instructions,
SHA256 `30b4098ee8e0d0c7d05e9a418ad9caca372d225da3c117db685e401862678f01`.
All body bytes/instruction encodings were rechecked against the PE. The mode
table at48D34C selects four separate loops, physically ordered3,2,1,0:

|Mode|Count|Spacing|Fourth float|
|---|---:|---:|---:|
|0|3|120|1|
|1|4|90|2|
|2|6|60|2|
|3|8|45|3|

Each arm calls the real random-roll helper4067D0 once with360 before its loop,
converts its DWORD result as unsigned to float32, and initializes a float
counter to positive zero. Each iteration prepares901/count4, with float32
`i*spacing + base`,10,positive zero,variant. Current x/y and unsigned direction
are read again. Counter+1 is stored to float32 and compared with the arm's
finite upper bound. Out-of-range modes skip these draws and requests.

`ReimuActionStateHighFinalCases.hpp` now expresses four independent loops,
sharing one mutable float[4] across mutually exclusive modes and resetting all
four elements every iteration. Each arm owns its one random draw/base lifetime.
The rest of720's motion, visual fades, sequence transitions, random positioning
and completion handling is unchanged. The earlier generic loop was a semantic
staging hypothesis; source spelling and original compiler/TU/LTCG ownership
remain unknown. No accepted header/layout/profile/relocation changes.

## Focused compiler and native evidence

```bash
scripts/compile-unit.sh src/characters/ReimuActionStateDispatch.cpp build/reimu-720-mode/ReimuActionStateDispatch.obj
python3 scripts/probe-reimu-action-source-shape.py --output-dir build/reimu-720-mode/expanded
python3 scripts/audit-reimu-720-mode-shape.py build/reimu-720-mode/ReimuActionStateDispatch.obj
python3 scripts/audit-reimu-720-mode-shape.py build/reimu-720-mode/expanded/ReimuActionStateDispatch.obj
python3 scripts/audit-reimu-720-mode-loops.py build/reimu-720-mode/expanded/ReimuActionStateDispatch.obj
```

The current9c8eca9 baseline object passes0/12 new smoke cases. VC8 SP1
`/O2 /GS- /GR /EHsc /MT`, default FP, produces:

- Compact object: `667f0d74420aa4d31c07f90165cae86ef287514d387157b0af457016f27286d4`.
- Three-region probe: `4784a42edb3ab99d4371b71825c03fcc6929055c22a27fcabb5c53d95f726a0b`.

Both pass **0/2098 native differences**, input SHA256
`3f583e5f35749cb4300c34f049223085cb519ca066cb45e9eca809682a095f09`.
The matrix covers108 motion,288 nodes,504 visual states,216 random/mode cases,
8 required branch cases and974 earlier/current integration cases. It includes
real MT state/draws, helpers, full actor bytes, ordered arguments and first
pointed payload. Stops are1906 genuine RETs,154 object requests,30 effects,
6 common entries,1 set669 and1 pending. RET checks stack/register/x87 cleanup.
The fixture still stops at the first real world request; later rays and
returning callbacks are outside native coverage. All8 earlier710/711 static
mode contracts and48 510 packet/12 level-reload contracts still pass. No full
historical matrix or aggregate cold replay was run.

The unchanged mapper retains45/50/33 primary groups,126 destinations and0
splits. Candidate720's span grows961->1448 versus target1451. Expanded text
grows81652->82088; its first table moves80344->80764. Decoded E8s grow1158->1164
versus target1188; RETs grow146->149 versus153. Indirect switches grow7->8
versus11. The frame shrinks5A8h->598h; target is570h and first diagnostic
difference remains478FA8. The pre-table deficit is786 bytes. Layout spans and
prefix sizes include alignment and do not establish boundaries or equality.
The existing opt-in metadata fixture needs no additional bound relaxation.

## Static loop evidence and limits

`audit-reimu-720-mode-loops.py` reuses the symbolic x87 facts engine with a
four-element exposed buffer. The engine's default three-element behavior is
unchanged. The720 checker recognizes the exact signed-load/negative-add2^32
conversion diamond after one real360 draw; both paths reach the float32 base
store. It carries that result as an unvalued symbol. No numeric helper result,
game callback return or target bytes are supplied or modified.

For every mode it requires a distinct bounded natural loop, positive-zero
initial counter, exact integer increment, ordered bound predicate, one901
call through the proved self receiver, all four payload stores, fresh x/y/
unsigned-facing loads and a preserved base/counter outside the exposed array.
The x87 counter carried across each backedge is proved consistent. All four
target and four candidate rows satisfy these constraints. Target base/counter/
buffer slots relative to mode-entry ESP are24h/20h/16Ch; candidate uses
18h/14h/144h. These layout differences remain unresolved.

The finite nearest-PC53/PC64 expression rules preserve addition grouping and
literal zero signs. Full coordinates, arbitrary FP environments, exceptions,
callback effects and complete function behavior remain outside this static
contract. The old combined-loop baseline is rejected before mode analysis.
Two compiled mode3 controls each pass the first-request random720 matrix
with0/216 native differences, but fail exactly source mode3 statically:
spacing45->36 and count8->6. This demonstrates the native stopping limit
without manufacturing subsequent execution.

Reports and source/compiler/control receipts are under `build/reimu-720-mode/`.
The earlier direct Ghidra identity is reused after current PE/instruction checks
and all9 unchanged primary DB hashes; no new process/clone or IDA semantics.
Superseded current-checkpoint objects, control source/objects and caches are
cleaned; current two objects, expanded source and small evidence receipts stay.
Next prioritize730's mode-specific request lowering, then740's undefined
paths, complete void/default ABI, real returning world contexts and full
relocation/compiler provenance before canonical root acceptance.
