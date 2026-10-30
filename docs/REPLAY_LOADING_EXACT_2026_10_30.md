# Replay file loading, JP1.06a

`BattleInputRecordingView::load_battle_input_recording @ 0x0042C5C0` is
canonical exact848/848 in `exact-first-battle-input-recording`. The pinned VC8
ordinary /O2 /GS probe uses the actual CFileReader source and real VC8 string,
vector and deque templates. No padding, assembly, forced registers or extra
initialization is used. The complete source section and target body have SHA256
`06cb2c0a3af5937d542cbbcf43dd67a042a1a69f06ad2e448d4ed423dccde926`.

## Evidence and recovered semantics

Fresh Factory metadata, entry point, all five mapped samples and semantic
probes passed. Private evidence is retained under
`build/frontier-medium-scan-20261030/`. Raw PE disassembly independently closes
all238 instructions, including the failure tail after RET that jumps back into
the common epilogue. Internal alignment instructions remain compared.

The old retained source was not a current-target match. It placement-constructed
a reader into byte storage, requested GENERIC_READ rather than the native access1,
and explicitly closed handles without authentic reader cleanup. The current
source uses a normal CFileReader local and its real constructor/read/destructor.
It preserves the native open and version-failure path-string clearing, but does
not clear the stored path on slot-deserialization failure. Read results are not
newly checked: the target also ignores them here.

The10-byte header at owner+E8 supplies the signed slot count at+EF. The published
slot byte at+140 becomes count-1. Vector+F4 is cleared and assigned default slot
objects. Only deque members are initialized; scalar metadata is intentionally
not value-initialized. The temporary slot ends before the slot-reading loop.
Success marks injected-input bytes+6C/+D4 and clears words+68/+D0.

Paired word fields use the already-established BattleInputSlotConfig layout and
word-copy evidence. The byte serializer accesses components of these words.
Replacing the old array hypothesis changes genuine VC8 /GS local ordering;
together with correct ownership and lifetime, the native frame is recovered.
The full original C++ spelling remains an inference, not recovered source text.

A private complete EH check also matches all six records: string cleanup8 at
6B7DF0, reader cleanup11 at6B7DF8, slot cleanup8 at6B7E03, handler46 at6B7E0B,
FuncInfo36 at6DE038 and its observed unwind-table24 at6DE020. Calls resolve to
401E00/40CEB0/429480 and the pinned cookie/frame runtime. No EH bytes are added
to authored byte totals. The durable match-unit recipe verifies the full848-byte
main body; the supplementary EH audit is retained in
`build/frontier-replay-load-20261030/eh-audit.json`.

## Affected evidence

Only the new match unit includes the changed loader; no prior accepted unit is
a source consumer. Existing exact receipts are preserved. The old independent
vector::_Assign_n origin fingerprint was affected by the source change, so its
minimal template-instantiation evidence is now in
`scripts/probes/replay_slot_assign.cpp`. This retains the original byte-wise
serialized view solely as library-origin evidence, not an alternative loader.
Its218-byte fingerprint was freshly rebuilt and uniquely checked against the
complete inventory by the existing origin validator. No library or denominator
gain is claimed; other origin rules were not rebuilt.

Reproduce the new function:

```
scripts/repo-python scripts/build.py --unit exact-first-battle-input-recording --compare --json
scripts/repo-python scripts/ci.py
```

Private negative controls: real reader with unrestricted inline string assign
894; preserved assign boundary with old byte-array slot layout824; paired scalar
slot layout848exact. These are source/ownership observations, not padding trials.
