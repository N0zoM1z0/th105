# Recover timeline ordering, not just its tree layout

The timeline tree at SceneRenderCluster+064 is ordered by unsigned start time,
and permits equal timestamps. It is not a unique map keyed by object ID.
The older map<int,20-byte-value> declaration happened to reproduce constructor,
traversal and erase code, but did not establish the insertion semantics.

## New independent evidence

Native insertion4519E0 reads the incoming24-byte command's word004 and compares
it unsigned against node+010, the resident command's start004. Equal values
follow the right branch. There is no unique-key rejection: successful insertion
always publishes true in the returned tree result. Object ID is command000,
not the comparison key. This explains why update451400 stops at the first
future start time, while still using command000 to find the animated object.

A fresh ordinary std::multiset<SceneInterpolationEntry24,SceneTimelineStartLess>
with predicate a.start_04 < b.start_04 regenerates all107 bytes of the tree
insert body, SHA256:
d625bc71356fc291075b935a3f1e67ec1efdd119d8f952cde5587d433f2c7b13.
This private provider check grants no authored credit. The exact historical
nominal typedef or wrapper spelling is unknown; ordering and duplicate behavior
are observed, and the natural multiset is a matching source model.

## Reconciled source

SceneTimelineEntries.hpp holds the actual24-byte command and unsigned-start
predicate. Constructor, update and cleanup now share that multiset type.
The update accesses object_id/start/end/type and &*it directly instead of
pretending that the command is a map pair. The original numeric switch order,
checked access frequency and interpolation calls remain unchanged.

All three complete accepted roots freshly replay exact:
- Constructor41F120:196/196.
- Update451400:801/801. The diagnostic complete848-byte source section,
  including its trailing switch table, also matches without changing the
  accepted callable-byte accounting.
- Cleanup452E60:104/104.

The shared cluster remains94 bytes. No extra fields, stateful comparator,
manual tree nodes, fake ABI, register forcing or target patch is introduced.

## Provenance and bounded checks

The three existing compiler-origin anchor files are updated to their actual
emitted multiset symbols. Their targeted SHA-pinned rebuild/full-inventory
fingerprint validation passes all3/5/2 existing anchors. Classification totals
stay unchanged; no compiler-generated helper is credited as authored code.
This is not a claim that all unrelated origin rules or native units were rerun.

Receipts:build/frontier-timeline-ordering-20261029/ contains the three formal
unit JSON files, shared.json and insert-proof.txt. Private source/provider
recipes remain in the matching .analysis directory. Default CI and tracking
checks cover the final source/manifest/anchor reconciliation. No cold-corpus
rebuild was performed.
