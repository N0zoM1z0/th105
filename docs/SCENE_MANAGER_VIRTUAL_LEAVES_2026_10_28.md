# Scene manager and fade virtual leaves, 2026-10-28

Three complete authored virtual methods are canonical exact in JP TH1051.06a:
CSceneManager update41E140 (5 bytes), render41E150 (5), and CFade initialize41E240
(11). The existing unit sources now define their actual ordinary C++ bodies.
No generic adjusting/deleting thunk is reclassified as authored here: the first
two are named virtual policy methods forwarding to global scene behavior, and
the third initializes the owning fade's scalar state.

Fresh raw PE readback attests the canonical executable SHA256
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.
CSceneManager's primary vtable6C74AC/COL6DBD58 resolves its current RTTI name;
slot8 cell6C74B4 points to41E140 and slotC cell6C74B8 points to41E150. CFade's
vtable6C74C4/COL6DBDA4 likewise resolves its RTTI name and points to41E240.
Raw WinMain owner evidence independently fixes the four-byte manager
and twelve-byte fade allocation and their initialization calls.

41E140 directly tail-calls43B4A0, ignoring its unused receiver. Its internal
scene-runtime callee remains independently unclassified/nonexact. 41E150
tail-calls the already exact43AAD0 byte-return fade renderer. 41E240 clears
fade timer+8, then color+4, and returns true in AL. Complete instruction decoding,
tail targets/RET and following INT3 padding fix all three boundaries. Original
method spellings are source names, not claims about recovered debug symbols.

`gpt-web-scene-manager-initialize` replays four methods exact: existing startup
and shutdown plus the two new forwarders. `cross-v106a-render-scene-consumers`
replays nine methods exact: eight existing consumers plus the new initializer.
The shared CFade slot0 declaration is corrected from an unused void placeholder
to the observed Boolean return; the other slots and scalar offsets are unchanged.
No assembly, custom ABI, copied bytes, forced reload or padding is introduced.

Receipts are in build/frontier-41e140-20261028/{manager-build.json,fade-build.json,
boundary.json}. The thirteen affected functions were compiled and compared;
unchanged accepted receipts remain incremental. Only the three new complete
roots add21 exact authored bytes. No cold corpus replay was needed.


## Shared constructed fade, November 9, 2026

WinMain now allocates the same `CFade` whose methods are implemented in
`RenderSceneConsumers.cpp`, rather than an unrelated entry-only class with
five undefined methods. The new `ui/Fade.hpp` also restores its IFade base and
the real empty shutdown method.

Native vtable `0x6C74C4`, COL `0x6DBDA4` and hierarchy `0x6DBDB8` identify
CFade with the offset-zero IFade descriptor `0x6DBD3C`. The old emitted entry
view had a one-type hierarchy. The shared class now has the corresponding
two-type inheritance geometry, size 12, color at +4 and timer at +8. Its
implicit construction leaves those scalars uninitialized, as the target does.

The complete five-method table now resolves to real source providers, each
strictly equal to the native body: initialize 11 bytes, shutdown 1, update 30,
midpoint 30 and render 142. Shutdown shares physical `0x41F890` with other
already recorded empty methods; it adds no independent authored credit.

Only two units consume the changed files. All nine renderer roots remain
exact. WinMain's full 695-byte candidate is byte-identical to the prior
candidate after canonical relocation and still differs from the target at +2;
the frame-home residual is not addressed. Source RTTI spelling and a full
application link are not part of these table/body comparisons.

Evidence is retained in `build/frontier-fade-interface-20261109/`, with the
native RTTI, before/after objects, comparisons and `proof.json`. The private
verification script checks fresh provenance, source hierarchy geometry, the
entire table and all five providers. No source pins or input migration files
changed. The scene-manager entry view remains separate work.
