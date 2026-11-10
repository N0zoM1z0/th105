# Line and rectangle use the real render owner

The line renderer `0x00401180` is now a method of the existing target-backed
`RenderModeManager`, and rectangle `0x004012A0` calls that actual member instead
of a duplicate receiver view. Their source declarations and emitted call use
the same C++ symbol, with the already asserted device offset `+4`. This is a
source-owner reconciliation, not proof of the original class spelling or an
entire application link.

Fresh full comparisons reproduce the previous candidate hashes exactly: line
is 148/148 but nonexact from +20; rectangle is 394/native395 and nonexact from
+9. The three bounded rectangle call-observer cases still agree. No new authored
functions or bytes are credited. Three targeted origin rules were revalidated.
All 99 accepted roots in 38 actual header-dependent units, including three real
linked units and the 670-byte battle overlay, replayed exact.

The separate overlay diagnostic again links its actual texture, primitive, rectangle
and line sources without a fake provider. Its linked overlay remains 676/native670
and nonexact; this does not replace the independent 670/670 COFF proof. No real D3D
rendering or gameplay was executed. All 1,030 target-independent CI tests and
generated-progress checks passed.
