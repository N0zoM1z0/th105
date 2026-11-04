# Result-menu selected-character refresh

The actual `CMenuResult::refresh_selected_character` source is now selected as
an authored, source-present function. Native `0x00447080` is called by the
result-menu update at `0x00447328` and constructor at `0x0044786B`; both
callers and the full 342-byte target are pinned by the origin rule. The
existing focused VC8 candidate is 342 bytes and differs first at +38: the
compiler schedules the selected-character load before clearing the texture,
whereas the native body clears it first. Candidate relocated body SHA-256 is
`f8217a94cf5856bd9fc3bee48ee8f464ed006d0ce9df852686c269ec73418d10`.
This is not an exact match and provides no exact-byte or EH credit.

`scripts/audit-result-character-refresh-observer.py` and its unit tests compare
native and candidate execution against an independent model for six fixtures:
valid selected characters 0 through 14, old and new texture handles, already
initialized and new lists, empty and nonempty counts, and null or present
input. The texture, formatter, list, sprite and cookie providers are mocked;
the test does not validate real resources, allocation failures, full-game
execution or invalid/out-of-range character indices. A modified tint serves as
a negative control.
