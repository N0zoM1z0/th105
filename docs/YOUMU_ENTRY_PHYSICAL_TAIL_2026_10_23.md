# YoumuObject initializer physical-tail recovery

The selected5159-byte initializer at `0x543670` now reproduces the target's
physical conversion/return copies, complete callable extent and adjacent
metadata. It still differs at21 callable bytes, first `+0x74F /0x543DBF`.
No authored exact function or byte is added.

## Target observations and selected source

Only original Japanese1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. Fresh target/status/tracking checks pass. IDA preflight rejects the
other open image; all new observations use raw PE and compiled objects.
The complete raw CFG still covers1294 instructions/5159 bytes,29 primary
destinations and one auxiliary switch. Vtable6C50BC binds this initializer
at+3C and the independently reviewed45C390 selector at+0C.

Observed target edges distinguish two848 entry points.821 captures heading340,
writes rotation and jumps to543EF1, after848's pointer load.812 jumps to
543EEB, the pointer-load entry;854 writes state344 and falls into that entry.
820 jumps into850 after its two scale stores. The previous source instead
reloaded821's pointer and omitted850's physical conversion/return copy.

Selected C++ expresses those actual edges with one used shared pointer and
explicit812/854 load-entry labels.850 uses the existing
`AnimationSequenceObjectView` int facade, as851 already did. Both int and
natural-short consumer witnesses reproduce the complete202-byte45C390 body
and its four-byte stack protocol. This is a compatible runtime view, not a
claim that the original C++ source mixed these declarations. No new prototype,
helper, volatile/restrict promise, inert local or forced register is added.
The pointer is assigned on every source path that reaches its uses.

| Complete obligation | Previous selection | Current selection / target |
| --- | ---: | ---: |
| Callable bytes | Source metadata overlapped the5159-byte comparison |5159|
| Callable instructions |1286 plus post-RET alignment|1294|
| Direct calls / conversion calls |77 /20|78 /21|
| RETs |22|23|
| Metadata start / metadata bytes |5156 /332|5160 /332|
| Full canonical payload |5488|5492|

All332 metadata bytes now agree, including every primary and auxiliary code
pointer. The natural single NOP at offset5159 also agrees; it is not callable
credit. All remaining differences lie in five call/register regions:
850(6 bytes),851(3),848(5),855(5),856(2). The unchanged owner diagnostic reports
24/30, including a source alignment NOP in its last-owner difference; that NOP
is outside the callable. Neither count nor a matching window is exact credit.

Source SHA256:
`66d01e60ca540b11515ebe4a58dc87f913ab340dd4845bcb1e992d9000c9be2d`.
Complete canonical payload SHA256:
`d00f4fc4ceca80c8fc4510ff03dcf064e3188fa5dc33afc8e25815d880da413a`.
The5159-byte target body remains
`d680c9d1386e6c3f8cc5e755dffccbbd431864dee308f760cf48fe00274ed245`.

## Scoped execution and genuine link context

The fresh public object has **zero mismatches in592** actual selector/frame/
texture/commit cases, through native RETs. The matrix retains812/820/821/848/850/851/854 and
the four851 alias stress inputs, with input SHA256
`02a34a45b03f1329f3a5376e81db3579e9ffb560ffe96ca1709453ef03e30d55`.
The [earlier audit contract](YOUMU_ENTRY_CALLS_2026_10_19.md) still applies:
zero textures, bounded resources and two x87 precisions; no arbitrary-resource,
unmasked-exception, spawning-action or whole-root execution claim follows.

A frozen equivalent source compiles with `/GL` and links with `/LTCG`,23 real
native object inputs and pinned static CRT/SDK libraries. The missing texture
setup dependency is supplied by its real193/261-byte native unit, freshly
exact. Auxiliary replacement344 and the color unit also replay exact. Older
fixed providers retain their own pins/status; the lookup pair,417800 and the
ordinary texture-query candidate remain nonexact. This is not an all-exact
dependency graph. No executable ABS binding or invented caller closes it.

Independent complete replay checks229 fields:79 REL32 edges (78 calls plus
the596370 tail),113 numeric references,3 metadata addresses,33 internal code
pointers and one game-data reference. All 149 HIGHLOW entries agree; the fixed
foreign game-data address correctly has no base relocation. MAP destinations,
source ownership and literal bytes/widths are checked before normalization.
The resulting5492 bytes equal native d00f4fc4, with the same21 differences.
No register mask, DLL execution, original-partition proof or LTCG impossibility
is claimed. Further work must address the remaining five regions in this epoch.

RTM, a successful real `/Zi` object/PDB, a void word-result view, pointer
declaration placement and typed parameter records do not improve these21
bytes. Explicit table dispatch also keeps the int-view result or loses the
physical copy with the short view. Additional855/856 int calls worsen the
residual to22/24/25 bytes. A rebased physical hierarchy and an unsigned RNG
result control with an independently matching27-byte callee also leave the
caller unchanged.
These are bounded negatives, not universal rules.

Recipes: `.analysis/youmu-entry-tail-20261023/`. Artifacts:
`build/youmu-entry-tail-20261023/`; start with `baseline-build.json`,
`joins.json`, `final-build.json`, `final-owners.json`, `final-native.json`,
`link/receipt-resolved.json` and `link/audit.json`. Link receipt SHA256 is
`569552a5557675df9cfbc13da04126af66ce7081fae6727ba8ef93ff0338bee5`.
Completed controls are archived with verified member hashes. Shared headers,
profiles, helper implementations and relocation bindings remain unchanged;
the unit/function notes now identify this selection. No aggregate cold replay.

## TH075 offset-view control

The read-only TH075 review is refreshed at commit
`4aeea7acc76b1a7db67722aff88ce9d8f8293f5b`. Its latest auxiliary action uses
a declaration-only receiver and typed offset fields while accepting the entire
31777-byte payload. Peer source, configuration and evidence notes were read;
its target corpus was not rebuilt and its dirty handoff was not changed.

Private recipe `.analysis/th075-exact-first-review-20261023/probe.py` applies
that concrete source property to this 5159-byte callable. It removes the local
complete-owner field declarations and size/offset assertions, retaining all
virtual declarations in their existing order and all actual operations. It
replaces 309 references to 23 used fields with typed offset lvalues. The sprite
subobject retains its existing independently typed view. This partial receiver
is never constructed or embedded. No helper, flag, ABI promise or binding changes.

Fresh serial baseline and control builds both have a complete COFF extent of
5492 bytes and canonical SHA256 `d00f4fc4ceca80c8fc4510ff03dcf064e3188fa5dc33afc8e25815d880da413a`.
Both strict comparisons fail at +0x74F with the same 21 callable byte differences,
zero alignment differences and zero metadata differences. Control source SHA256
is `0e2a3d153a6d67af1cb6966518301a04f00ef54b4004fb622992b5cc28f4e4b4`.
This is a native code-generation negative for this source/compiler context;
it does not establish original layout or rule out other source shapes.

Receipts, source, objects, full canonical payloads and field map are retained in
`build/th075-exact-first-review-20261023/`. The complete `report.json` SHA256 is
`685baf4513eb54f02790fa78ff0a32953819ff3e9fff73e1ab7a37b7cd4a3c01`.
The public source remains unchanged. No execution matrix is rerun for these
byte-identical payloads, no new exact credit and no aggregate replay are claimed.

## Dispatch-source controls

Selected source `66d01e60` remains unchanged. Six further complete native builds
retain all 5492 canonical bytes of `d00f4fc4`, with the same 21 target differences:
an inline float-to-int conversion, minimal int-parameter receiver views with
int/void ignored results, forwarding helpers with int/float parameters, and
numeric source order for case 848. The latter retains both 848 entry labels and
all 812/821/854 edges. Existing callees, bindings and shared headers remain
unchanged. The controls do not recover an original declaration or prove another
compiler context equivalent. Their complete-byte equality needs no new execution
matrix; no source replacement or exact credit is justified.

A genuine member-function-pointer expression in 850 instead emits a local
virtual thunk. The ordinary comparator rejects its unmapped REL32; it is never
assigned a fabricated game address. Although its full COFF extent is 5492 and
metadata still starts at 5160, its last RET ends at 5157, followed by a three-byte
alignment LEA. This is not the target's 5159-byte callable or natural single NOP.

Real `/GL` compilation and `/LTCG` linking with the same 23 hash-pinned native
inputs retain the extra root CALL at +0x750. MAP owns its five-byte vptr-load / slotC
JMP thunk at `0x10002580` in `YoumuCil.obj`. Independent source-to-link checks
resolve all 230 fields: 80 REL32, 113 actual numeric literals, 36 internal pointers
and one attested nonexecutable ABS game-data reference. All 149 HIGHLOW fields
agree; every other linked root byte equals its native COFF source. The thunk's
complete bytes also equal the actual compiler-generated native section. This
establishes the rejected compiler result, without normalizing the thunk to an
unsupported target address, executing the DLL, claiming target equivalence or
excluding other LTCG partitions. Provider exactness limits remain as above.

Recipes: `.analysis/youmu-dispatch-context-20261023/`. Receipts and artifacts:
`build/youmu-dispatch-context-20261023/`; start with `caller-views.json`,
`forwarding.json`, `case-order.json`, `pmf850-native.json` and
`pmf850-link/field-audit.json`. The member-pointer source SHA256 is
`9915df5f348579a054bed38914cad6c0b23f41726ae885c2766a95f5d76e1e06`;
its real link receipt SHA256 is
`457e7d541dc198d6712bd839903312c20febb6023c6b1dcac0dd1b20ff084f09`.
Completed equivalent controls are hash-verified before compression; `retention.json`
lists their members and the active external native inputs, which must remain.
The five remaining call/register regions are still open.

## Selector visibility and native map implementation, 2026-10-24

The selected Youmu root remains source `66d01e60` / full payload `d00f4fc4`,
with 21 differences. A same-class short selector definition independently matches
the complete 202-byte `0x45C390`, as does the existing int facade. Both can be real
exports in one `/GL` input linked with the same 23 native providers, without a
constructed receiver, fabricated vtable or invented caller. Each selector still
matches 202/202 after complete link replay of its three actual REL32 fields.
The root's full 229-field/149-HIGHLOW replay is unchanged. These tested callee
visibility contexts do not improve the five remaining root regions.

The first link exposed a genuine missing dependency under the old `lower_bound`
caller-view spelling. Its actual provider was already present: checked VC8
`std::map::find` in `CharacterObjectSecondaryAnimation.obj`, independently
105/105 exact against `0x45C320`. A real symbol alias resolves that source body; no
executable ABS address or stub is used. Raw target traversal closes all 39
instructions/105 bytes and returns with RET8. The existing compiler exclusion
and unknown original template identity remain unchanged.

The public improvement is in
[AnimationSequenceVirtuals.cpp](../src/characters/AnimationSequenceVirtuals.cpp):
`0x45C390` now obtains the sequence block through a real checked
`std::map<int, AnimationSequenceBlock *>::find(key)->second`. Its native caller
remains 202/202, and its emitted template helper independently matches 105/105
without relocations. The complete affected object replays all 10 accepted
functions exact. The independent short-parameter probe also remains 202/202;
its existing caller-view binding is retained alongside the real template
binding. Shared headers, vtable declarations and compiler flags are unchanged.
No duplicate selector or compiler-helper credit is added. Public source SHA256:
`f100f7b85f9a40a66f2f6232999ebf5898de20451410a3b11e4509b4aa1a0680`.

A further genuine CIL input includes both real map-based selector bodies and
the actual template definition. The root again replays to the same 5492 bytes
and 21 differences. The selector guard rejects this CIL result before canonical
normalization: its prologue now aligns ESP to 8, and its actual helper call
prepares tree/key/result pointers in ESI/EBX/EAX. No private convention is
declared to force a target match. The 202-byte diagnostic prefix is not accepted
as the linked function's extent, and no linked selector exactness or original
partition conclusion follows. Native accepted builds retain their full proofs.

Reproduce the public object with:

```sh
python3 scripts/build.py --unit cross-v106a-animation-sequence-virtuals --compare --json
python3 scripts/compare-function.py 0x0045C320 build/match-units/CrossV106a_AnimationSequenceVirtuals.obj --symbol-base '?find@?$_Tree@V?$_Tmap_traits@HPAUAnimationSequenceBlock@th105@@U?$less@H@std@@V?$allocator@U?$pair@$$CBHPAUAnimationSequenceBlock@th105@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@ABH@Z' --json
```

Recipes: `.analysis/youmu-selector-visibility-20261023/`. Artifacts:
`build/youmu-selector-visibility-20261023/`; start with `public-selector-final.json`,
`public-find-compare.json`, `public-word-witness.json`, `find-facts.json`,
`selector-audits.json` and each of `link/`, `dual-link/`, `map-link/`.
The last contains the full qualified root replay and the retained rejecting
`selector-rejection.json`. No DLL execution or new runtime-matrix claim.
Completed earlier link contexts are hash-verified and compressed; restore their
sources/objects/images from `completed-visibility-controls.tar.gz` as listed in
`retention.json`. The actual map context and all 23 external native inputs remain.
Exact ledgers are unchanged; no aggregate cold replay is claimed.
