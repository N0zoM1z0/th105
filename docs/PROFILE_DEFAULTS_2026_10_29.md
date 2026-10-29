# Profile defaults, JP1.06a

432050 is canonical exact334/334. Complete section SHA256:
dec4a6bb8c88010804f180e336b81f779f689abbf9907a2a331a0e207157fcb1.

The whole body through RET43219D initializes two strings, two52-byte input
binding blocks, profile flags, twenty deck containers and fifteen character
default decks. Existing independent exact callers43AF30/site43AF56 and
44C110/site44C1C7 prove authored ownership. This supersedes the nonexact
profile-slot-defaults origin rule; the canonical exact baseline now owns it.

## Source recovery

Use the existing InputBindings type rather than byte buffers with integer
casts. Its signed source byte and up/down/left/right plus eight buttons match
the serialized52-byte blocks. The method-facing prefix preserves strings98/B4,
primary140, secondary174, flags13C/1A8 and decks1AC. Unaccessed texture/sprite
and input prefixes are opaque here, not invented complete subobject classes.

With typed fields but the old early secondary memset, the complete334-byte
probe has106 unequal bytes from+72. Completing primary fields before clearing
the secondary bindings gives zero differences. VC8 naturally prepares the
second memset arguments before some primary stores, then calls memset at the
native location. No manual scheduling dependencies or register directives are
introduced. This demonstrates a valid source/type context, not the uniquely
original source spelling. The old blanket scheduling stop no longer applies.

All20 deck clears and15 default-deck calls remain ordinary indexed loops.
The source uses real deque<unsigned short> storage and the already identified
431E80 default-deck helper. Shared profile headers and the old unselected
ProfileMenuData default body are untouched, so accepted writer/normalizer and
caller objects have no changed input source.

## Reproduce

scripts/repo-python scripts/build.py --unit exact-first-profile-defaults --compare --json

Source:src/ui/ProfileDefaults.cpp.
Receipt:build/frontier-profile-default-types-20261029/formal-build.json.
Private whole-section comparisons:compare.json and compare-after.json in that
directory. Full formal section tail equals334; only334 new bytes are counted.
