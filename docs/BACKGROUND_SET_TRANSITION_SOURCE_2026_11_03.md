# Background transition setter

`BackgroundBase::set_transition_4654f0` is now individually selected at
`4654F0`. The 407-byte native body is game-authored: exact battle object
request dispatcher `467380` calls it at `4676C7`, `4676FD` and `467715`, and
its four-entry original state switch is pinned separately at `465688`.
The body hash and all three call edges are checked by the focused origin rule.

The actual `BackgroundBase` source publishes the transition state and value,
then applies alpha to both checked sprite vectors. A pinned build reports the
407-byte callable plus one alignment and 16 bytes of jump-table data, for a
424-byte object section. Its first canonical body difference is at +92: the
compiler assigns the x87 control-word and alpha spill slots in the opposite
order. The body remains nonexact and no byte credit follows. The switch table
is metadata and is not counted as authored instructions. Neither original
source spelling nor live rendering is established by this comparison.

The unchanged source file also supplies the already exact transition stepper
at `4656A0`. Reproduce the nonexact setter with `scripts/repo-python
scripts/build.py --unit exact-first-background-set-transition --compare --json`.
The targeted origin rule was checked directly; no full origin-census replay is
claimed.

A subsequent bounded type control used an explicitly consumed unsigned-byte alpha in
each loop, preserving the low-byte color result. It still emits a 424-byte section
and differs earlier, at +5; it does not resolve the stack assignment and was not
selected. The original source was restored.
