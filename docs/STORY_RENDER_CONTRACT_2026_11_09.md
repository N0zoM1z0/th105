# Story rendering has a void callback contract

The 42-byte function at `0x470ED0` is the Story battle manager's render
callback, not an integer simulation result. Native RTTI names its owner
`CBattleManagerStory`: vtable `0x6C1374`, COL `0x6D7AE8`, slot +0x38 at
`0x6C13AC`. That cell is the executable's only absolute reference to the
function. The shared scene renderer at `0x41E040` calls slot +0x38, finishes
the frame and supplies its own boolean result without using the callback's
return value.

The source now implements `CBattleManagerStory::render` in that existing
slot and exposes its observed phase field at +0x88. It calls the real shared
void provider at `0x46BF00`, then renders the scenario only for phases 0, 5
and 6. Previously a separate `BattleController` method declared the shared
provider as returning int and propagated that supposed result. The shared
member-call view now lives in one header used by provider and caller.

The 11-byte wrapper at `0x45A2A0` is likewise named `render_scenario` and
returns void. It adds +0x68 to the receiver and tail-jumps through slot +0x0C;
the native CScenarioData table cell `0x6C299C` names render `0x457F90`.
An executable-wide E8/E9 scan finds just the Story tail at `0x470EF3` and
Ending call at `0x41E94C`. Ending also discards the value before continuing
its rendering work. These caller and provider contracts justify removing
invented status propagation; machine bytes alone do not recover the original
nominal return-type spelling.

## Validation

All 21 roots in the five affected units remain fully exact. All 233 non-debug
COFF sections, including symbolic relocation targets, are unchanged after the
three method-symbol substitutions. The Story class's field and virtual-slot
names do not change its layout. Its six existing phase methods remain exact,
including the pipeline's complete 35-byte EH code and 44-byte metadata.
Twenty-seven other units only include the declarations and use none of the
changed methods; they were not rebuilt.

The complete native Story callback, phase wrapper, shared render provider,
scene/Ending callers and 930-byte scenario render body were decoded. The
indirect tail exits are checked explicitly, and the Story callback's external
E9 edge is bound to the scenario wrapper. Evidence, fresh before/after objects,
comparisons and `proof.json` are retained in
`build/frontier-story-render-contract-20261109/`.

Historical function keys and the unit name remain stable. This connects an
existing exact implementation to its actual virtual slot and corrects its
source contract; it adds no new exact credit. The pending input migration,
scenario implementation and origin pins are unchanged.
