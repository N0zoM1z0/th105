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
Existing exact WinMain owner evidence independently fixes the four-byte manager
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
