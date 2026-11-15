# Seven additional original VC8 container origins

A read-only exact-owner/callee-symbol census examined 783 existing ordinary
x86 COFF objects and found 99 emitted candidate rows. LTCG intermediate objects
are not ordinary COFF symbol inputs and are excluded from this discovery pass;
the old bulk nm entry point fails on them. No existing object alone grants
acceptance, and no corpus-wide build was performed.

Seven bodies have complete, inventory-unique non-relocation fingerprints:

- 451BD0/94: deque<CSpriteEx>::push_back, SceneTimelineLoader.cpp.
- 4519E0/107: checked timeline multiset insert, SceneTimelineLoader.cpp.
- 455BE0/100: list<RebuildEntryView>::_Buynode, ScenarioTextRebuild.cpp.
- 455E50/160: list<RebuildEntryView>::_Incsize, ScenarioTextRebuild.cpp.
- 42DFC0/160: vector<ScoreDefaultRecord24>::push_back, ScoreDefaults.cpp.
- 4285C0/191: basic_string<char>::find, ReplayFilename.cpp.
- 4229E0/256: vector<FrameData>::_Assign_n, EffectResourceLoading.cpp.

Each committed source-specific anchor is freshly rebuilt with pinned VC8 SP1
and the source unit's existing /O2 /GS settings. The unchanged origin validator
checks complete COMDAT boundaries, target and compiler hashes, minimum 0.70
non-relocation coverage, minimum 24 bytes, no allowed tail, and uniqueness over
the full 4027-candidate inventory. All five rule groups pass; no first-hit or
review-only uniqueness assumption is used. Full native body hashes are also
pinned. These are compiler-origin proofs, not full relocation-canonical body
receipts and not authored matches. The seven exclusions total 1068 code bytes.

The same-sized package-tree allocator 41D160/55 is deliberately not classified:
its non-relocation instructions differ, and the emitted fingerprint instead
matches the already excluded 41EB90. Equal length or adjacency is insufficient.

Fresh public replays preserve all six selected authored roots from the five
sources: timeline 1584, text rebuild 563, score defaults 2428, replay filename 1322,
pattern expansion 1323, and effect loader 2528. The timeline verifier also passes
the full 1676-byte payload including 92 table/alignment bytes and fresh build
provenance. No source, compiler profile or acceptance tool changed.

The census and registration scripts remain private in the corresponding .analysis
scope.

Only origins change: excluded 1721, review 511. Exact 1577/448878, source 1775,
authored 1795, mapped 1802 and units 760 are unchanged. No compiler bytes are
added to the game's exact numerator.

## Follow-up: complete emitted-symbol discovery

The broader read-only pass considers all function symbols in the 710 existing
manifest probe objects, rather than only symbols already named on exact-owner
call edges. It examines 11311 size-compatible symbols and finds 98 candidate
rows covering 63 distinct review addresses. This is still discovery, not an
acceptance census: objects can be stale and nominal source types can differ.

The authored spell owner 4619C0 is handled separately as a full canonical 101-byte
match with complete EH. It is not
excluded as a container helper. Two symbols from the temporary sequence-advance
control are omitted because that source was restored; their old objects do not
establish a reproducible current source. Other ambiguous hit sets overlapping
previously classified bodies remain outside this batch.

Fourteen fresh source-specific origin rebuilds prove 59 more compiler-generated
bodies totaling 14055 bytes:

| Source family | Bodies | Bytes |
| --- | ---: | ---: |
| Package file index | 1 | 509 |
| Network receive address records | 4 | 231 |
| Design handle vectors | 9 | 948 |
| Select input scalar deleting destructor | 1 | 40 |
| Filtered spell CSV short set | 2 | 164 |
| Scene bootstrap input records | 13 | 1982 |
| Effect FrameData vector insertion | 1 | 880 |
| Score default records and set insertion | 10 | 1831 |
| Deck count tree node allocation | 1 | 55 |
| Character sequence deque cleanup | 1 | 135 |
| Scenario text map/list lifetime | 3 | 995 |
| Timeline sprite deque and event/list helpers | 8 | 4647 |
| Effect sprite vector helpers | 3 | 944 |
| Event-effect vector-valued map | 2 | 694 |

The 59 bodies occupy 55 complete fingerprint hit sets. Four design handle-vector
sets have two members each; both addresses are explicitly retained in an
identical-symbol/size equivalence group. Uniqueness is over the full 4027-candidate
inventory, not only remaining review rows. All other sets are singleton.
Each whole native body hash is pinned, and fresh original-source compilation
passes the unchanged 0.70/24/no-tail contract. This proves compiler ownership,
not unique original nominal template spelling or full relocation-canonical
exactness. Cross-specialization shape witnesses are not named as new gameplay
methods, and no caller's unresolved body is promoted.

No source, compiler profile, manifest unit or comparator changed. The earlier
six selected authored-root replays remain applicable, and the current spell
owner 101/117EH checkpoint is preserved. All 14 origin rebuilds complete serially
on CPU 0/nice10. Receipts are full-groups.json, all-coff-hits.json, and the 14
source-specific validation JSONs under the existing origin-report directory.

After the independent spell-owner match and this classification batch:
exact 1578/448979, source 1776/authored1796/mapped1803, excluded 1780/review451,
units 760. This follow-up adds zero authored functions or exact authored bytes.
