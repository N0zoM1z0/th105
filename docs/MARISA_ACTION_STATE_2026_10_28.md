# Marisa action-state root at 0x004A3710

The original Japanese TH10.5 v1.06a root is canonically exact in
`exact-first-marisa-action-state`, built from
[MarisaActionState.cpp](../src/characters/MarisaActionState.cpp) with VC8 SP1
`/O2 /GS- /GR /EHsc /MT`.

The complete callable extent is `0x004A3710..0x004B3B97` (exclusive end),
66,695 bytes. Its SHA-256 is
`98fd68e00763955f64d7489b2a5cb04b20f209031d739a7e9117273080a45aa5`.
All 67,936 envelope bytes through `0x004B4070` also match; envelope SHA-256 is
`58dd1936fc5db5341cbf3e08d9f19beaa7d106ffbf84d82b673644da542c6447`.

Three compact action switches contain 32/45/48 destination words and
227/231/230 byte indices. Actions 720/731/733 each own an additional four-way
difficulty table. The strict contract includes all 137 destination words,
688 indices, three one-byte NOPs and the two-byte alignment before the first
difficulty table. Metadata contributes no authored code credit.

The owner audit is 125/125. Raw traversal reaches all 16,999 instructions,
with six resolved switches and no unresolved indirect exits. All 1,929
relocations are replayed: 978 REL32 calls to 29 targets and 951 DIR32 entries.

Reproduce the complete comparison and boundary audit with:

```bash
WINEDEBUG=-all DISPLAY= WAYLAND_DISPLAY= scripts/repo-python scripts/build.py --unit exact-first-marisa-action-state --compare --json
scripts/repo-python scripts/audit-giant-action-owners.py --unit exact-first-marisa-action-state marisa-vslot28 build/match-units/ExactFirst_MarisaActionState.obj
```

Current private results are `build/marisa-root-work-codex/canonical.json` and
`build/marisa-root-work-codex/owners.json`. The manifest and source reproduce
them; intermediate trials were removed.

The source now uses a character-scoped typed receiver, checked member offsets
and explicit sequence vslots. The previous header and nine include fragments
were used only by this root and have been replaced by the standalone source.
No shared header, callee implementation or accepted consumer changed.

The [giant-root playbook](GIANT_ACTION_ROOT_PLAYBOOK.md#marisa-source-shape-findings)
records the useful compiler findings and rejected array-extent trial. The exact
comparison also corrected retained hypotheses: actions 730/732 advance to
731/733, and flight release preserves both native input gates. The target's
unusual prelude clamps, float rounding, callback-dependent field rereads and
unwritten third payload slots in 307/308 are preserved. The original source
spelling and the meaning of those unwritten slots remain unknown.
