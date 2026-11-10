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

The thirteen affected functions were compiled and compared;
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

The private verification script checks fresh provenance, source hierarchy geometry,
the entire table and all five providers. No source pins or input migration files
changed. The scene-manager entry view remains separate work.

## Shared constructed scene manager, November 9, 2026

WinMain now constructs `CSceneManager : ISceneManager` from the shared
`engine/SceneManager.hpp`. Its four existing runtime methods and the existing
scene factory provide all five virtual slots. The old constructed entry view
had no base and five undefined methods; the runtime class separately declared
only four slots. The factory is now the real `CSceneManager::create_scene`
member rather than a standalone stdcall function mapped to its address.

Native table `0x6C74AC`, COL `0x6DBD58` and hierarchy `0x6DBD6C` establish the
class and its offset-zero ISceneManager base at descriptor `0x6DBD08`.
WinMain allocates four bytes and writes only the vptr. Application bootstrap
at `0x407F1C` and the creation thread at `0x40885E` call slot +0x10 with the
manager in ECX and one stack selector, then publish EAX as the scene pointer.
The provider ignores its receiver and returns with RET4. This explains why
the old free-function implementation matched bytes despite the incomplete
class contract. The ordinary member now produces the same complete bytes.

Lifetime evidence supports the implicit nonvirtual destructor: application
shutdown calls slot one, then the ordinary deallocator. WinMain's archive-load
failure path directly frees the manager. No destructor slot, scalar field or
new initialization is introduced. The source retains the factory's existing
opaque pointer result; recovering every allocated scene's shared declaration
is separate from the manager's proven five-slot ABI.

All five providers remain exact: initialize 162 bytes, shutdown 25, update 5,
render 5 and factory 980. Factory verification also covers the complete
84-byte, 21-entry switch table, all reachable instructions, 16 allocation
cleanup states, 202 bytes of EH code and 164 bytes of exception metadata.
The entire 20-byte manager table and complete RTTI inheritance geometry match
under their canonical bindings. Descriptive source type names still include
the namespace, so this is not an exact RTTI-name or integrated application-link
claim. The unconstructed application callback views are unchanged.

Only the manager, factory and WinMain units consume the changed sources. Their six
root comparisons are unchanged: five exact, and the same nonexact 695-byte WinMain
candidate. No additional authored method was found in this five-slot closure, and no
source pins changed.
