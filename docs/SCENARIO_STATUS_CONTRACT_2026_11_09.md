# Scenario status is a signed three-state result

`BattlePhaseBlock::run_scenario_step` at `0x45A290` now returns `signed char`
instead of `bool`. Its source virtual-call declaration has the same correction.
The story pipeline now calls that real method rather than a separate undefined
signed-byte alias. This repairs a source contract that a matching tail jump
had previously concealed.

The complete 11-byte native wrapper reads the vptr at this+0x68 and tail-jumps
to slot +8 without converting the result. That slot at `0x6C2998` points to
`CScenarioData::update`, whose complete target audit closes 6,121 code bytes,
1,690 reachable instructions and 23 switch destinations. Its observed AL
results are 00, 01 and FF. In particular, `0x459C22` sets AL to FF and jumps
to the common return path. The upper EAX bits do not establish an int result.

All four physical E8 callers were located in the executable and checked at
instruction boundaries:

- Ending at `0x41E83C` tests AL for zero.
- Continue/reset at `0x471286` loops while AL is nonzero.
- Story gate at `0x47159E` tests AL for zero.
- Story pipeline at `0x471829` tests AL and takes signed JG for positive status.

The last caller needs the negative state. A bool interface cannot express it.
The correction preserves the existing machine behavior; it does not claim
that the previously emitted wrapper itself changed bytes. Original nominal
type spelling remains unknown, but a signed byte faithfully expresses this
observed call contract.

The focused build also found an existing compile failure in the story
threshold method: it referenced removed Fighter names `value_174` and
`maximum_176`. Those accesses now use `health_174` and `max_health_176`.
Native `0x4716EC..0x4716FA` independently confirms the same word copy from
+0x176 to +0x174. All six story methods again compile and compare exact.

## Validation

Only three units use the changed method declaration: phase wrappers, story
core and continue/reset. The other 28 units that include BattleController.hpp
do not refer to this member. The nine affected root comparisons retain their
results: eight exact and the existing 290-byte nonexact continue/reset body.
All 295 non-debug COFF sections are unchanged after symbolic relocation
normalization; the story baseline uses only the preceding field-name repair.
Its original compiler failure is retained separately.

The 309-byte story pipeline, its complete 35-byte EH code, 44-byte exception
metadata and 10-byte event destructor all match the target. The adjacent
phase/render wrapper was replayed but its separate return contract was not
changed. No interpreter-source, input migration, source-pin or exact-count
change is included.

Evidence is in `build/frontier-scenario-status-contract-20261109/`: native
provider/callers, the original compile diagnostic, before/after objects,
comparison reports and `proof.json`. The existing target-interpreter auditor
was rerun without modifying it.
