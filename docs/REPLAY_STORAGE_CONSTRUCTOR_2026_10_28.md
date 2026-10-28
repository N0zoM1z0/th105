# Replay storage constructor 43F1B0

Canonical exact: 161/161 unmasked bytes, SHA
cab2e1640d35106c4d671b484df0b40e722b4a161f21134e878c8ac8f6ed3e06.
Unit: exact-first-replay-storage-constructor.
Receipt: build/frontier-43f1b0-20261028/formal-build.json.
Boundary audit closes all 43 instructions / 161 bytes through RET43F250.

The global initialization thunk6BE9F0 passes storage6FBDD0 to this constructor
and registers destructor thunk6BF180. The constructor's explicit authored
policy publishes embedded input08 to selected pointerD8 and input70 to pointerE0.
Those self-relative publications distinguish it from implicit member-only
construction. No origin exclusion rule selects this address. The global thunk,
array helpers and implicit destruction are not credited as authored functions.

The real member layout is supported independently by the native constructor,
destructor43F260 and exact replay serializer: two0x68 injected input owners
begin at08, checked vector of0x50 replay slots atF4, std::string at108 and
CriticalSectionWrapper at124. The two inputs use out-of-line constructor42C930
and destructor42C950; the latter is a tail alias to input base destruction.
The existing input and critical-section definitions are reused without edits.
The local replay-slot value preserves actual short deques and natural alignment,
not a fake container or manual allocation recipe. Header and unknown scalar
cells are left uninitialized exactly as in the native construction path.

Natural C++ member construction followed by the two pointer publications
matches on the first focused replay. No register coercion, padding-for-codegen,
manual SSO initialization, vptr stores or copied instructions are used. The
source model names are descriptive; original source spelling is not known.

## Shared injected-input lifetime

The replay owner now reuses ProfileInputManagerExLifetime directly. Its natural
EH array emits the authored input constructor42C930, canonical exact27/27,
SHA67216fd859e17482996372d52b7418374c78d0d1ee59e89af0e92ae312eb6744.
The constructor explicitly clears enable64 and injected mask60 while leaving
resolved mask62 untouched. This policy is not an implicit generated constructor.
The complete boundary is independently audited in input-boundary.json.

RTTI COL6D7A50 / type descriptor6E6588 names CInputManagerEx; table6C1154
contains deleting destructor42CBC0 and update409F70, followed by literal data.
The Profile lifetime header previously declared an additional virtual method
instead of overriding the inherited update. That declaration is corrected to
the real two-slot shape. Its two-slot physical data layout remains0x68.

Focused receipts shared-input-lifetime.json, profile-affected.json and
score-affected.json preserve replay161, profile constructor192/destructor205
and ScoreDefaults respectively, while accepting the input constructor27.
No global input runtime rewrite or generated destructor credit is included.
