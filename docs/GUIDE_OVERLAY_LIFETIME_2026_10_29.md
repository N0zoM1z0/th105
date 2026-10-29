# Guide overlay natural lifetime, JP1.06a

The selected GuideOverlay constructor43F540 remains20/20 canonical exact,
now from ordinary polymorphic member construction rather than the legacy
UiSprite94 manual-vptr representation. No new exact bytes are counted.
SHA256:ce9a93317e0946a83e05b769eb56b142ce0e0c6abbc6dec71ceb1b30711afea2.

The full A8 guide view has a real94-byte sprite at8, a texture handle at4,
scroll9C, widthA0 and alphaA4. Actual IColor construction zeroes its value;
normal derived sprite construction publishes the table, then the guide body
clears its texture and visible flag. No vptr field or manual assignment exists
in this selected source.

Fresh raw RTTI pins sprite table6C0668, COL6DCCDC, TD6FA52C to CSprite;
IColor table6C0624, COL6DCD78, TD6FA560 names IColor. The source models the
established eight-slot sprite interface and its real vertex/size fields.
The narrow view is not a shared-header or whole-program class replacement.

Destructor43F330 now also uses actual C++ member/base destruction. It remains
90/native92, first+40: source caches the handle while target compares memory
then reloads. Source SHA256:
40b7c204051af94d5a4d9806495760ac09e74de8e6469a5b0a37abcc74b35cbe.
The existing27-byte native EH handler6B905B anchors the destructor. No extra
credit is assigned and the handle-load residual is not forced.

The old GuideOverlay.cpp load/render source and shared headers are unchanged
by this checkpoint. Its legacy lifetime definitions are no longer selected as
constructor/destructor evidence. Guide update keeps the newly accepted112-byte
separate definition. All caller ABI mappings remain unchanged.

scripts/repo-python scripts/build.py --unit exact-first-guide-overlay-lifetime --compare --json

Source:src/ui/GuideOverlayLifetime.cpp.
Receipt:build/frontier-guide-natural-lifetime-20261029/formal-build.json.
The report intentionally combines the exact constructor and nonexact destructor.
