# Scenario interpreter uses the real script member

The existing complete but unselected scenario interpreter hypothesis now calls
`CScript::next_command` directly on `CScenarioData::script_35c`, instead of a
separate declaration-only receiver view. The emitted relocation uses the same
symbol as `src/battle/ScriptNextCommand.cpp`. This is source-level identity,
not proof that the complete game links or executes correctly.

The interpreter's strict comparison is still blocked by an unqualified local
string copy constructor emitted for the case-two by-value arguments. No
invented binding is supplied. Its current raw section is 5,576 bytes, which
is not a canonical comparison against the native 6,121-byte callable. The
interpreter remains unselected and receives no authored exact-byte credit.

A separate bounded control used the real substring constructor with offset zero
and full length, reflecting native string assignment arguments. VC8 instead
outlines that constructor too, so the strict comparison remains blocked; that
control is not selected and does not establish an exact difference count.
Receipts are under `build/frontier-scenario-interpreter-real-script-20261104/`
and `build/frontier-scenario-argument-20261104/`.
The native target CFG audit and all 1,030 target-independent CI tests passed.
