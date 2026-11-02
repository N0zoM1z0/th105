# Actual scenario draw and text sprites, 2026-11-02

Pinned Japanese v1.06a SHA-256:
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.

ScenarioData.hpp now uses actual global CSprite in the 0x9C draw and 0xDC text
records. ScenarioCommandUpdate.cpp uses the actual scale_x_88/scale_y_8c fields
instead of byte-offset writes. ScenarioRender, ScenarioRuntime, list-fade and
text-rebuild consumers likewise use actual CSprite, removing their partial
sprite interfaces and the rebuild-only color/sprite class hierarchy. Their
outer record views and explicit initialization policies are not merged here.

The old rebuild sprite copy was only an external nonthrowing declaration.
With the actual class, VC8 naturally emits the complete implicit CSprite copy
at 0x455160: 116 canonical bytes. The original list node at 0x455BE0 remains
100 canonical bytes and calls that actual copy. No copied body, custom copy
implementation, forced noinline or artificial COFF barrier is added. The existing
entry cleanup at 0x434C60 also matches all 85 bytes from the rebuild context;
this is the same physical root already accepted elsewhere, not another function.

All 22 accepted roots in 11 units remain exact across the 14-unit actual include
closure. This includes dynamic text render171, text constructor95, release133,
entry cleanup85, entry fade242 and window text rebuild563. The existing generated
container-origin gate passes its two roots /260 bytes without changing coverage
thresholds or classifications. Full sprite RTTI273 and the nine-slot table pass.

The pending render930, list-fade418 and ScenarioData constructor1528 keep fresh
before/after candidate hashes. Command update0x458440 retains its unqualified
?$basic_string_ctor relocation. That blocked root still has no accepted native
comparison; the new member types do not bypass its source/ABI uncertainty.

Full EH comparisons cover rebuild58+52, text release52+52 and draw-entry
cleanup38+44, totaling296 support bytes. Rebuild's handler is33 bytes because
its large negative frame displacements use the longer addressing form. The
complete source-owned region and actual native handler form are checked rather
than imposing the usual27-byte size. The other two handlers are27 bytes. No EH,
copy-provider, container or duplicate cleanup bytes are added to authored credit.

Private controls and receipts are under
.analysis/frontier-scenario-real-sprites-20261102/ and
build/frontier-scenario-real-sprites-20261102/. Final CI passed all 962 tests in 112.862 seconds. Both diff checks gate
the local checkpoint. No target or generated binary is committed.

Totals unchanged:1426 exact /443399 bytes,1636 source-present,1655 authored,
1826 mapped,2075 excluded,297 review and813 units.
