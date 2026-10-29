# Scenario's selected input pointer, JP1.06a

Scenario offset064 is the selected CInputManager pointer, not a scenario ID.
The accepted story setup45A4E0 publishes its selected-input argument to the
phase's selected-input field and passes that pointer to scenario virtual slot0.
Configure454FE0 stores the word at064. The interpreter later loads it as a
pointer and reads signed counters at040/048. Existing InputManager.hpp places
hold.buttons[0] and hold.buttons[2] at precisely those offsets.

CScenarioData::configure now takes CInputManager*, and the member is input_064.
The constructor/render views share that pointer type. The interpreter uses
the existing actual input class instead of a raw prefix with ambiguous
pressed/held labels: button0 count equal1 or button2 count nonzero advances
local result/text waits. Network synchronization and all guards are unchanged.
The constructor-facing update slot is also reconciled to the signed-byte
return established by the separate advance-loop review.

The exact90-byte configure body is unchanged, SHA256:
a0c42bacc85c612f4bc5f14c8c578168f4433b92150fb0de99f1ac2fddebed0d.
Twenty-one accepted functions in the affected shared-header units freshly
replay exact. The two untouched story setup/ending units retain their preceding
focused receipts; they were not unnecessarily rebuilt again. Scenario constructor
and render retain their prior nonexact hashes. The interpreter's complete raw
5640-byte source section is byte-identical before/after, but its comparison
still blocks at the unqualified string copy constructor. Raw equality does not
grant a canonical match or restore the old integer-carried-pointer hypothesis.

Receipts:build/frontier-scenario-input-owner-20261029/runtime.json,
regressions.json and interpreter-raw.json. No accepted-byte total changes,
new target mapping, compiler flag change or cold-corpus claim. Default CI and
tracking validate the source/signature reconciliation.
