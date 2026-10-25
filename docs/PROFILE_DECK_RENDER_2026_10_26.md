# Complete CProfileDeckEdit renderer448F60

The complete2521-byte source is **nonexact**. Full canonical relocation replay
finds1622 unequal positions, first449268; the first776 bytes agree. Candidate
SHA is `73fb53f64d54c145d1e16c345045f4fa3373de46b173a6e9a648b64145942e38`.
Equal body/frame size is diagnostic evidence, not an exact result. Source is
unselected, with no implemented.csv or matches.csv row.

## Observed target and ownership

Only Japanese1.06a SHA
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
was used. Fresh target/status/tracking checks passed; IDA again rejected the
10350095 target and supplied no semantic evidence or writes. Raw PE decode
closes all744 instructions/2521 bytes through RET0 at449938. Seven following
INT3 bytes separate449940. No escaping direct edge or indirect jump exists.

Primary vtable6C222C has render slot+0C at6C2238 pointing to448F60. Adjacent
COL slot6C2228 points to6D8610; its complete locator points to type descriptor
6E6DDC and the NUL-terminated name `.?AVCProfileDeckEdit@@`. The origin rule
replays the full body, vtable/COL/type chain and selected menu/availability/
guide E8s. This is independent authored ownership evidence; helper origins
are unchanged. Forty invalid-parameter sites and five virtual calls are present.

The function uses an aligned D4 scalar frame with GS/EH handler6B9E0B. A real
94-byte sprite temporary has four28-byte vertices, texture dimensions and five
32-bit extension values. Its constructor stores handle0 and vptr6C0668; source
does not initialize the remaining fields before the actual texture operations.
The existing opaque character-array UiSprite facade triggers an extra local
GS cookie under /GS and is unsuitable as this constructor-facing local type.
The public typed local preserves real storage rather than adding inert bytes.

The complete policy is represented: scroll offset16*(selection-window), full/
incomplete-deck indicators, shared background/cursor, up to40 deck thumbnails,
up to15 filtered rows, three count/availability digits per row, selected text
preview and overlays, player/footer and four A8-byte guides. Native widths and
signed comparisons are retained: short keys, signed-byte deck counts, signed
string-width clamps200/272, unsigned global half dimensions and late thumbnail
alpha `(39-index)*0x28000000 | 0xFFFFFF` beginning at index33. Scale-X and scale-Y
are distinct0.5 stores. Original field terminology and source spelling remain
unknown; retained header names do not independently establish their meaning.

Checked map/deque iterator operations remain real C++ operations or declaration-
only entry views at the observed helpers. The single map iterator is reused
for deck traversal and per-row count lookup, and is default-constructed then
assigned begin. The native helper4300B0 returns a checked8-byte iterator element;
the later selected-card paths also contain inline deque indexing. All six
external indexing sites and three tile rendering sites are retained. External
sprite/tile implementations receive no new source, ownership or exact credit.

## Early complete comparison and bounded controls

| Whole source trial | Bytes | Result |
| --- | ---: | --- |
| first complete source, /GS- opaque sprite |2488 | Compared immediately;2384 unequal common-range positions; wrong EH prologue |
| native /GS with same opaque local |2662 |Extra local GS protection/frame caused by character-buffer representation |
| actual typed sprite storage |2505 |Native EH-only GS structure; frameCC instead ofD4 |
| reused real count iterator / after-lookup highlight |2521 |Native D4 frame;1957 unequal positions |
| default-constructed then assigned iterator |2521 |1624 unequal positions; first449146 |
| native independent scale stores |2521 |Current1622 unequal positions; first449268 |

These are full-function results, not small matching windows. First/private
reports use ordinary comparator relocation replay with target-pinned temporary
bindings. Public formal-first/formal-second and the full-section audit agree
on all2521 bytes and the final SHA. Normal /GS selection follows the observed
EH prologue; no compiler profile or accepted shared header was changed.

Two genuine polymorphic-local controls, before/after the independently changed
iterator lifetime phase, are whole-payload byte-neutral within their private
snapshots. Both preceded rejection of the row-default hypothesis; they do not
prove neutrality in every corrected phase. The row multiply
operand-order control and local exception-scheduling-off control also leave
the final correct-zero payload unchanged. This finite FP lane is closed.
Native row arithmetic uses FIMUL where this candidate uses FILD/FMULP, shifting
the subsequent physical layout; branch displacements, registers and stack
homes also differ. Do not claim exactness from body/frame equality or infer
LTCG impossibility. Original local identities/TU/backend context remain open.

## Push-relative count ambiguity: rejected inference

An initial manual reading mistook the per-row count's stack clear for a
different local and suggested a missing map key retained the row index. That
inference was wrong. At4493DB an index argument has already been pushed; the
clear at4493E2 encoded `[ESP+20]` therefore writes the count at base+1C. Native
execution confirms the zero default. The public source keeps zero, and the
erroneous row-default source is retained privately as a negative control.

`scripts/audit-profile-deck-render-target.py` executes the whole renderer in
one finite call-observer fixture: an empty deck-count map, three filtered card
records and valid selected index0. It executes the real target checked-index
and short-map-find providers, while drawing/availability calls are typed
observers. Native missing counts are `[0,0,0]`; current candidate matches all32
events, including the selected preview. The wrong row-default candidate gives
`[0,1,2]` and is rejected by the same audit. Return stack, callee saves and FS:0
restoration are checked. Temporary stack sprite addresses are normalized only
for observer-event identity; code bytes receive no masking.

This fixture resolves a concrete stack/data ambiguity. It is not an end-to-end
D3D/score implementation, populated-deck-grid matrix, FP/NaN equivalence claim
or substitute for the complete canonical comparison. No broad behavior matrix
was run. A private early fixture with selection7 outside a three-element deque
was superseded by the in-range case and does not support the public result.

## Reproduction

```bash
scripts/repo-python scripts/build.py --unit exact-first-profile-deck-render --compare --json
scripts/repo-python scripts/audit-profile-deck-render-target.py
scripts/repo-python scripts/audit-profile-deck-render-target.py --object build/match-units/ExactFirst_ProfileDeckRender.obj
```

Build/object audit exit1/nonexact; target-only audit exits0. Receipts are under
`build/frontier-448f60-20261026/`; private first/control sources and recipes are
under `.analysis/frontier-448f60-20261026/`. New data rows qualify the EH prefix,
float384 and double304; double21 reuses an existing value-checked literal row.
All other prior bindings, source and profiles are unchanged. Heavy work runs
serially on CPU0/nice10; available memory stayed over10GB. Swap rose from134MB
to140MB during the focused work and then remained stable.
Fresh `origins-check.log` passes all4024 candidates:1604 authored/1419 excluded/
1001 review. `cold-all.log` passes all526 accepted units/1414 functions under
the current manifest; exact bytes remain385903. Floating audit passes399 ledger
literals/1603 explicit mappings and2002 target references. During cold replay,
swap reached143MB while available memory stayed over10GB. No new exact credit.
