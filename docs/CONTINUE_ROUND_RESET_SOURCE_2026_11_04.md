# Continue round reset source

`ContinueOwnerRuntimeView::reset_battle_round_471180` (0x00471180, 290 bytes) is
exact. It is called from the exact continue menu at `0x00444E0D`.

The source uses the real phase-block layout: `CScenarioData` at `+0x68` and two
`std::list<int>` members at `+0x598/+0x5A4`, pinned by compile-time offsets.

The deciding change was writing the list copy and the scenario reset as one
inline member of the phase block, `destination_5a4 = source_598;
scenario_068.reset_runtime_state();`, called on the global pointer. The target
loads the global into ECX, derives both list addresses from it and copies it to
EDI for the later `+0x68` reset. That is the shape of an inlined member's `this`.
A local `phase` pointer gives EDI directly, and a hand-written
`if (&dst != &src) dst.assign(...)` changes the iterator lifetimes as well.

`list::operator=` calls the `_Const_iterator` instantiation of `_Assign`, so
the unit maps that symbol to `0x0045A740`.
