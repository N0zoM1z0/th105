# Shared in-process network state record and corrected publisher owner

Three pointer-facing definitions now share NetworkStateRecord.hpp. The existing
flat4C layout is retained: two real checked deque<short> members at10/30, tail
bytes0E/2E and the existing scalar fields. Compile-time size/offset assertions
cover the complete record. No constructor, destructor, field initialization,
packing or extra storage is introduced; these consumers do not allocate it.
The original nominal record class remains unknown.

This record is not MatchSetup, despite equal total size and overlapping byte
offsets. MatchSetup contains player-side payload where the network record has
native deques. Nor is it the separate40-byte CDPP_ACK_INFO C++ packet object,
which serializes a variable-length message. The historical ACK-tail name at
44E6D0 describes setting ACK pending during state import, not parsing a wire
ACK packet. No fighter-category meaning is assigned to these byte fields.

## Corrected client/server attribution

Raw primary RTTI and consecutive slots8/C identify:

- CNetworkServer table6C16EC: import44FD80, export44FFE0.
- CNetworkClient table6C1754: state-tail import44E6D0, publication44F390.

The existing324-byte publisher44F390 was incorrectly labeled as a server
method. Its source view and descriptive ledger name now say CNetworkClient;
its unit/file identity is retained because that TU also owns other operations.
The full324 bytes remain canonical exact. Its old server-oriented sample_count
label at6E0 is now the neutral state_word: this client method establishes only
zero tests, not server sampling semantics. No original nominal source method
name or complete C++ hierarchy is claimed from this correction.

The ACK audit now checks both primary RTTI owners and all four slot identities.
Its fixture and result terminology says snapshot rather than packet, and the
unused deque headers are modeled empty. Six finite state/lock-boundary cases
and the wrong-field negative still pass. Two added tests reject swapped owner
labels or an incorrect client publication slot. No network, packet codec,
concurrency or actual OS locking is executed.

## Whole-byte checks

All three affected units are freshly compared in full: nine accepted authored
roots remain exact (162/284/99;57/78/69/324;48/162), while the pending78-byte
state-tail body retains8 differences and server input publication remains
404/native409. All eleven complete candidate hashes are unchanged.
The critical-section unit and server CFG audit also pass. The source inputs,
record field semantics and class labels are consolidated without a spelling
or register-allocation matching trial.

No new function, source/exact credit or total changes: exact1427/443604,
source1636, authored1655, mapped1825, review298, excluded2074, units812.
The matching publisher is renamed in the existing row, not duplicated.

Evidence: `.analysis/frontier-network-state-record-20261102/` and
`build/frontier-network-state-record-20261102/`. Original pinned target,
serial CPU0/nice10 work, no IDA semantic reuse or push.
