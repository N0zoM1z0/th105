# Connect menu middle-state policy: complete source

The complete CMenuConnect method444490 is now source-present and authored,
but remains nonexact. Native callable699 bytes contains205 reachable
instructions and26 calls. The two destination tables contain11 and4 entries,
plus one alignment byte, giving a complete760-byte payload.
The selected source payload is772 bytes; the full comparison first differs
at+13 on the downstream default-return displacement. No exact credit.

Exact virtual update444B90 tail-jumps this method at444C35 for outer states2..5.
Both switch destinations and every normal control-flow instruction were
traversed from the pinned raw PE. Complete payload SHA-256:
1a11457cc5956e11c54f901a512b01186c4a8270c9815f09a597114fe523311b.
Callable SHA-256:
bb6159fbe53c1882c8797a1c1ae19f527bb3d2bed4e67463a394eec6d0c7949d.

## State and ownership facts

- Substate0 dispatches outer state2 to the combined digit wrapper442CE0,
  states3/4 to history wrapper4430D0, and state5 to clipboard wrapper4424D0.
  Their results are ignored; this method returns true.
- Substates1/2 show and consume the profile prompt. Choice2 returns to outer0.
  Choices3/4 select substates3/6 and set byte3B8 to1/0 before the waiting
  message and exact finalize-message4425D0 call. Do not substitute state-one's
  different byte3B9.
- Substates3/6 query the session status at3B4, with native outcomes0/6/9 and
  reason dword3AC. Status0 publishes scene/next-scene9/5 or12/6, calls exact
  history finalization443D70, and sets substate to-1.
- Failure/prompt branches retain their separate message-before-state or
  state-before-message order. Text declarations use numeric target addresses;
  no untranslated message semantics are guessed.
- Substate5 handles the second prompt; substate10 enables the final guide and
  checks confirmation. Closing clears outer state, releases the network
  session and clears its pointer. Active cancellation additionally hides the
  profile message before release.

All target reads, low-byte stores and ignored API paths are retained. No new
network operation or defensive guard is invented. Partial receiver views are
never instantiated. Only the original normal thiscall/cdecl call protocols
are used; no code-address binding or private-register facade is introduced.

## Bounded source controls

An initial if-chain candidate merged one physical message call and emitted a
724-byte payload. Source switches matching the observed status/reason families
restore the distinct message blocks, but leave27 physical calls versus the
native26 because a disconnect path is duplicated. Receiver preparation also
differs. An explicit member-layout view hoists a10 constant; a separately
shared disconnect exit removes the native EBX save. Both remain nonexact
and are not selected. There is no
register forcing, volatile state, dummy lifetime or optimizer barrier.

The ordinary unit exact-first-connect-join-state compares the complete699-byte
callable and reports mismatch. A separate canonical relocation replay compares
the entire772/760 source/target payload, including both switch tables.
No prefix, table-only or equal-length acceptance is claimed.

Receipts and reproducible private source controls are retained under
build/frontier-connect-join-state-20261031/ and its .analysis counterpart.
Fresh target/IDA attestation is retained under
build/frontier-medium-discovery-20261031/. The new narrow origin rule checks
the whole callable, exact-caller tail edge and two accepted downstream calls.
Only its new origin row is updated; unchanged origin evidence is retained.

This append-only source/unit/data checkpoint changes no accepted consumer.
Progress becomes source1743, authored1763, review844; exact remains1547
functions /439428 bytes. Final CI and whitespace gates precede the local commit.
