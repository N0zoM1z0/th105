# Profile message update, JP1.06a

43F6E0 now has complete ordinary C++ source and a reproducible selected unit.
Native298-byte SHA256:
7cd81ee125c1ed51f0c66aec0e25e1be8f8652d63af1e0f14f1c51d3395172ed.
Source294-byte SHA256:
94f4c7114a77515065a9b95389474ac3591297d4ffe4e9385bd68f68d49fd0bd.
No exact credit is added.

Current raw code has five returns and no external branch tail. The existing
profile-message-update-authored-106a rule retains independent exact UI callers
442790/site442844 and44CC50/site44CD73 and its complete body hash.

The global cursor6FD018 updates first. A changed selection emits event27,
toggles choice B/C opposite A/D, and returns0. Button0 at input+40 emits28,
hides all five message objects and returns3 or4 according to cursor selection.
Button1 at+44 or is_menu_initial_press(1,0,0,0) emits29, hides the same objects
and returns2. Otherwise it returns0. Existing typed UiDesignObject, MenuCursorState
and CInputManager fields provide the actual offsets; no new shared layout is
introduced. Both calls consume AL as their boolean result.

All first217 bytes match. The sole structural residual starts at43F7B9:
native has a local four-byte XOR EAX/POP EBX/RET after the cancel-input test;
source instead branches back to the existing zero return43F757. This shortens
the remaining cancel block by4 bytes. Positive and early-negative guard forms
produce identical complete294-byte source. Retain this bounded stop rather
than force an extra return with dummy lifetimes or assembly.

scripts/repo-python scripts/build.py --unit exact-first-profile-message-update --compare --json

Source:src/ui/ProfileMessageUpdate.cpp.
Receipt:build/frontier-profile-message-20261029/formal-build.json.
Only this isolated source unit changed; existing accepted consumers and
shared headers are unchanged.
