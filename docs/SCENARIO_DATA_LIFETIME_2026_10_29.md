# CScenarioData member lifetime exact, JP1.06a

438A70 is canonical exact411/411, SHA256
1978302132a03e001e9f9417b1b02eb7e305d5943f546eed681ef33d5c918858.
Its complete body has one RET0 at438C0A and no omitted cold tail. Independent
exact manager/phase destructor edges are 00438D56 -> 00438A70, 00438EEC -> 00438A70.
These callers and the existing configured constructor/member layout establish
a game-object lifetime, not an unnamed generic container helper.

## Real member ownership

The524-byte constructor-facing ScenarioData view now provides the actual
reverse member destruction: strings+4F0/+4D4/+4B8; result resource+390;
CScript+35C; three render-entry lists+350/+344/+338; text-entry map+32C;
font+68; system-effect manager+4. Actual string SSO cleanup, list sentinels,
checked map erase and seven-state EH publications emerge from ordinary C++.

The member at+68 is the existing non-polymorphic TextFontOwner194, whose
independently exact destructor4114C0 is called directly. Its first field is an
HDC, not a vtable. The older ScenarioEffectOwner194 runtime-facing header is
not used as an owning font definition here. No shared header is changed.
The config at+1FC is the real128-byte text configuration. Trivial tail storage
is not given fabricated destructor behavior.

The524-byte extent is independently used by the exact BattlePhaseBlock
lifetime. The normal-manager source's larger528-byte storage wrapper is not
silently reinterpreted as proof of additional nontrivial members. No complete
original nominal hierarchy beyond these observed members is claimed.

## Implicit destructor and provenance

The destructor is intentionally implicit, with no added destruction body or
synthetic vptr publication phase. The class
definition itself expresses the game-specific ownership; compiler-generated
list/map helpers are dependencies and get no new authored credit. This follows
the existing ordinary implicit-owner lifetime reconstruction used for the
normal manager and ResultList.

An unmapped ordinary delete helper merely causes VC8 to emit the destructor
COMDAT for comparison. It is never treated as a native entry or credited as
source/game bytes. There is no manual vptr operation, fake register convention,
extra state, alignment, assembly or copied instruction stream.

## Focused replay

scripts/repo-python scripts/build.py --unit exact-first-scenario-data-lifetime --compare --json

Source:src/battle/ScenarioDataLifetime.cpp.
Receipt:build/frontier-scenario-lifetime-20261029/formal.json.
One full native EH-handler binding is added. Accepted callers, shared classes,
font/script/member providers and their receipts remain unchanged; this isolated
new unit needs no whole-corpus rebuild. All411 bytes are credited only after
its complete canonical comparison reports zero differences.

The later constructor addition is recorded in SCENARIO_DATA_CONSTRUCTOR_2026_10_29.md.
The unit now also reports that1528/1527 nonexact constructor; its newest full
report is build/frontier-scenario-constructor-20261029/formal-environment.json.
Destructor411 remains exact in the same changed-source replay. The local
empty Environment base restores the observed RTTI+4 overlap without changing
any destructor byte.

The shared Environment reconciliation subsequently replaces the local empty
proxy with the common native tag and moves the animation-state fields to their
actual owner. All physical offsets and both lifecycle bodies stay unchanged;
see ENVIRONMENT_EMPTY_BASE_2026_10_29.md.
