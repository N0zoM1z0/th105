# Complete server input-frame publication source

The retained natural implementation44F9A0 is now formally selected and
registered as authored/source-present. Native CNetworkServer primary table
6C16EC, slot1C at6C1708, COL6D803C and type descriptor6E6904 establish the
callback's owner. The complete409 bytes contain128 instructions and two
external tail exits to CriticalSectionWrapper::leave at40AC40.

Native SHA256:
`058dc706f51602a4bf33490d47d37a5efc93a394c31b303a8f058481571b3ca5`.
Source remains404 bytes/127 instructions, SHA256:
`f4ddd799e5e14f58c423c098389859a6e781799519678b93be02e4d06f607862`.
First canonical difference+117 concerns input masking versus sequence update;
subsequent register/stack scheduling remains nonexact. No old source-spelling
or register-forcing lane was reopened.

## Recovered game policy

The outer critical section48 guards sequence-distance backpressure and input
publication. When the unsigned distance exceeds signed delay+3 (converted to
unsigned for the comparison), the current packet is serialized/sent with
option50, then the function tail-leaves the outer critical section.

Otherwise the input word at input208+62 is masked to10 bits, current7C and
sequence98 are published, previous/current values are pushed to historyA0,
and paired pop_back operations trim it to twice the outstanding sequence
distance. The packet is sent, adaptive-delay virtual slot34 is invoked, and
critical sectionDC guards appending current/previous words to outputs160/1DC.
The inner lock leaves normally and the outer lock leaves through the second
tail exit. No missing guard, retry or new error policy is added.

The only C++ change is correcting NetworkServerSend5View::send_server's
return declaration from int to void. The independently recovered real sender
416B60 has no meaningful EAX result on its inactive path, and this caller
discards the result. Actual five-word arguments/RET20 remain unchanged.
An explicit before/after build proves the entire404-byte caller is identical.
The client result-sender view is not changed.

## Verification boundaries

`audit-server-input-publish.py` closes both complete CFGs, verifies nine direct
call sites, three indirect calls, both outgoing leave tails, the16-bit input
mask/current store and32-bit sequence publication. It replays the exact162-byte
adaptive helper and its native slot34 identity. Native send548 and deque
push_front122/push_back119 stack cleanups are checked (RET20/RET4); these are
not promoted to exact source/helper matches by this audit.

This is static CFG/call/field-width evidence, not runtime behavior, packet,
network, concurrency, lock or gameplay execution. No broad emulator matrix was
invented for this registration. Four contract tests reject missing calls,
incorrect tail exits/returns and wrong mask/publication widths. The unchanged
generic RTTI/full-body/call gate validates authored ownership; the full hash
covers outgoing tail bytes and the CFG audit verifies their destinations.
No generic gate was weakened or extended.

The same TU's accepted48-byte client sender and162-byte adaptive routine stay
exact. Its78-byte ACK callback keeps the same8-byte mismatch; all six guarded
ACK cases and the wrong-field negative rerun. The critical-section unit is
freshly exact. No other source/header or cold whole-corpus rebuild is needed.

## Accounting and evidence

One review row is now source-present/authored: source1636, authored1655,
mapped1825, review298. Excluded2074, provisional4027, units812 and authored
exact1427 /443604 bytes stay unchanged. matches.csv is untouched.

Reproduce with the existing gpt-web-network-primary-packet-continuation unit
(full comparison intentionally nonexact), audit-server-input-publish.py and
audit-client-ack-tail.py. Private evidence is under
`.analysis/frontier-server-input-publish-20261102/` and
`build/frontier-server-input-publish-20261102/`. Original pinned target only,
serial CPU0/nice10 work, no IDA semantics or push.
