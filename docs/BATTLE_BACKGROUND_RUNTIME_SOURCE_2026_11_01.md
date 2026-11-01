# Complete background-runtime source registration

The existing BattleObjectManager::update_background_runtime_466f40 body is now
formally source-present and authored, not exact. No C++ statement, header,
compiler flag, helper implementation or source-control variant is changed.
This closes an old tracking gap without reopening its documented register/TU
experiments or granting prefix credit.

## Complete target and ownership

Canonical original Japanese1.06a body [466F40,467372) is1074 bytes, SHA256
f9067cb5f6b20c5732e0bd18222d9c0211ec8a1fc41b61f484ba80f7e2c9fa6a.
Independent raw-PE CFG decoding reaches all308 instructions and both RET0 exits
at467362/467371. There are no missing tail chunks or discarded instructions.
The independently exact presentation caller is46B160/105, whose46B1BC direct
call reaches466F40. That full
caller is replayed before using it as authored-ownership evidence.

The function implements game policy rather than a generated container member:
- apply the byte effect-level delta with60/255 bounds, or fade toward255;
- dispatch the actual background/weather entry, then update four drift fields;
- approach the current event's X/Y/Z targets by the observed0.01f value;
- update background entries and traverse the actual checked renderer list;
- publish position/offset, step transitions, retire completed entries to the
  owned list and signal the existing event, or invoke the renderer callback;
- increment this manager's own runtime_tick114.

The real manager layout and two lists already have exact lifecycle/worker
consumers. Primitive literal bindings are the existing correctly promoted
0.005f/0.01f values, not replacement decimal-double constants. Call and IAT
bindings are explicit; standard-library helpers get no new credit.

## Whole source comparison and retained limits

The unchanged complete current source compiles to1064 bytes, canonical SHA256
4dfaf713920f1974e9e2fb373dcff7e79ecdf0a6a0a8b00561bd356c6670f5b6.
The1074-byte target comparison is nonexact at+12/466F4C. The existing clamp
register and delayed register-save differences remain; the previous same-TU
weather-provider experiment was byte-neutral and is not repeated.

The function is added to the existing cross-v106a-battle-object-manager-runtime
unit. All nine previously accepted functions in that source freshly remain
exact:466980/99,4669F0/83,466A50/83,466C70/126,466CF0/32,4677B0/145,
4678D0/32,466AF0/379 and4678F0/279. Presentation46B160/105 also freshly passes.
The mixed unit's comparison_failed result is expected and not an aggregate pass.

Reproduction:

    taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py --unit cross-v106a-battle-object-manager-runtime --compare --json
    taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py --unit exact-first-battle-presentation-phase --compare --json

Receipts: build/frontier-background-source-20261101/formal.json, caller.json and
boundary.json, plus the scoped authored-origin validation. The older bounded
negative controls remain under frontier-466f40-20261027; they are not new work
or permission for register forcing, dummy lifetimes, padding or assembly.

Source1784, authored1804 and mapped1811; review425, excluded1798 and units764.
Exact1585/449721 bytes is unchanged. No new function enters matches.csv.
