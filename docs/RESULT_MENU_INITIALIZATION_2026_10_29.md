# Result-menu initial texture ownership, JP1.06a

The retained CMenuResult constructor omitted initialization of texture_004.
Native4476CF explicitly stores zero before constructing the remaining members.
The source now initializes that real handle in its member initializer list.
This prevents the source refresh/destruction path from consuming an
indeterminate initial handle and restores an observed target store.

Complete constructor source is495/native502, nonexact+45 at4476BD.
No exact credit is added. Native SHA256:
1b56434f8d09960a7d90dfccfe7daeadfa0ef4b7e9035e5cd1df39baaa90a65a.
Selected source SHA256:
6a32046f885a24cb656952a42cff95297b1367634c801e2d4c9273f0c6c18fa7.
The prior493-byte source SHA was
a179e29e18c6e0fb0c1ee6ed028d3772b3620352a58d13a24c7316d9a93eb325.

## Ownership and complete path

Exact Title update425990 calls447690 at425C75. CMenuResult's established
1148-byte owner/vtable6C2070 has independently exact render/update/destructors.
The constructor builds its sprite, character vector, fifteen108-byte ResultList
records, design and guide, then loads data/menu/result/result.dat, binds control100,
scans fifteen score-unlock bytes at+1C, selects the first available character,
binds the horizontal cursor, clears fifteen initialization flags and loads
guide11 before refreshing the selected character.

The native constructor has one RET0 ending447885. Its full27-byte EH handler
6B9B98 points to FuncInfo6DF870. Existing separately verified constructor and
destructor callbacks4471E0/447260 are used for the real ResultList array.
No new vtable words, padding or synthetic locals were added.

The previous scene-mode constant CSE residual remains: source keeps22 in a
register across construction, while native uses immediate publications.
The correction does not attempt to force that allocation or weaken comparison.

## Focused checks

The constructor is added to the existing cross-v106a-menu-result-update unit.
Formal fresh build retains update447560 at43/43. The same changed-source
object independently replays render446F70 at270/270, normal destructor447590
at256/256 and scalar destructor447890 at30/30. No shared header changed.

Commands:
scripts/repo-python scripts/build.py --unit cross-v106a-menu-result-update --compare --json
scripts/repo-python scripts/compare-unit-object.py cross-v106a-menu-result-render-dtor build/frontier-result-menu-initialization-20261029/After.obj --json
scripts/repo-python scripts/compare-unit-object.py cross-v106a-ui-scalar-deleting-dtors build/frontier-result-menu-initialization-20261029/After.obj --json

Full comparisons, raw before/after assembly and exact caller facts are retained
under build/frontier-result-menu-initialization-20261029/. Default CI and
whitespace checks validate final source, tracking and progress.
