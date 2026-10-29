# Separate scenario advancement from its font member

The old advance454F10 label attached an18-byte virtual loop to the194-byte
font object. That ownership inference was incorrect, despite the exact bytes.
The loop belongs to the complete524-byte CScenarioData object. Source, selected
symbol, durable name, caller declarations and active documentation now agree.
No exact bytes or functions are added by this correction.

## Independent evidence

The accepted story-page caller45A2E0 and ending caller45A3A0 both pass the
script/scenario subobject at BattlePhase+068. Their existing physical layouts
reserve524 bytes through+58C, not194 bytes. The same receiver first loads its
story page through4583E0, then calls454F10. The CScenarioData vtable6C2990 owns
update458440 at slot08. The native loop reads that slot repeatedly, tests AL
and returns the nonzero value unchanged. The interpreter exits with AL00/01/FF;
no meaningful upper-EAX return value is established.

By contrast, the scenario's own member at+068 is the actual nonpolymorphic
TextFontOwner194: DC000, font004, old font008, configuration00C, rendering
surface fields, color pointers, list15C and string170. Its independent native
constructor411430 and destructor4114C0 were already used by the recovered
scenario constructor/destructor. A Win32 DC at000 is not a vptr.

## Source correction

- ScenarioAdvance.cpp now defines CScenarioData::advance_until_ready_454f10.
  It calls the real virtual update slot and preserves a signed-byte result.
  The old ScenarioEffectAdvance.cpp path is replaced.
- CScenarioData::update and both story caller declarations now use signed char
  rather than the old int/bool hypotheses. Original nominal enum spelling is
  unknown; the byte representation and 00/01/FF values are preserved.
- The legacy ScenarioEffectOwner194 field-name view retains its194-byte physical
  layout and configure ABI, but loses the false virtual methods. Its first
  word is explicitly a DC. Constructor/destructor declarations represent the
  real font lifetime; it no longer synthesizes implicit font cleanup.
- No synthetic vptr operation, ABI register convention or new caller is added.
  Existing font/configure field views remain local source compatibility names;
  no unrelated rendering rewrite is performed.

## Focused validation

The corrected18-byte root remains exact, SHA256:
cc9df09e62e570b708f377cbbf06738a179ff84c16e1c656df25d977ccb5a67f.

The dependency graph identifies13 affected units including both direct story
callers. Serial replays preserve all24 accepted functions. Receipts and the
explicit accepted-address inventory are in
build/frontier-scenario-font-owner-20261029/affected.json and regressions.json,
with the root's separate advance.json. This includes scenario runtime/result,
result lifetime, common spell resources, story setup/ending/page load, text
entry lifetime/release, list fading and the accepted scenario destructor.

The constructor remains1528/native1527 nonexact. The interpreter still blocks
at its unqualified source-emitted string copy constructor; the correction does
not invent a target or report that blocked comparison as an ordinary mismatch.
No full cold-corpus validation is claimed. Default CI and tracking checks pass
after the source/name reconciliation.
