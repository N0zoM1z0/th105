# Seven additional original VC8 container origins

A read-only exact-owner/callee-symbol census examined 783 existing ordinary
x86 COFF objects and found99 emitted candidate rows. LTCG intermediate objects
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
checks complete COMDAT boundaries, target and compiler hashes, minimum0.70
non-relocation coverage, minimum24 bytes, no allowed tail, and uniqueness over
the full4027-candidate inventory. All five rule groups pass; no first-hit or
review-only uniqueness assumption is used. Full native body hashes are also
pinned. These are compiler-origin proofs, not full relocation-canonical body
receipts and not authored matches. The seven exclusions total1068 code bytes.

The same-sized package-tree allocator41D160/55 is deliberately not classified:
its non-relocation instructions differ, and the emitted fingerprint instead
matches the already excluded41EB90. Equal length or adjacency is insufficient.

Fresh public replays preserve all six selected authored roots from the five
sources: timeline1584, text rebuild563, score defaults2428, replay filename1322,
pattern expansion1323, and effect loader2528. The timeline verifier also passes
the full1676-byte payload including92 table/alignment bytes and fresh build
provenance. No source, compiler profile or acceptance tool changed.

Receipts: build/frontier-existing-emitted-20261031/coff-report.json, hits.json,
five exact-first unit reports and timeline-payload.json. The five origin-rule
validation reports are retained under build/frontier-boost-library-20261031.
The census and registration scripts remain private in the corresponding
.analysis scope.

Only origins change: excluded1721, review511. Exact1577/448878, source1775,
authored1795, mapped1802 and units760 are unchanged. No compiler bytes are
added to the game's exact numerator.
