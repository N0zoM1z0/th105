# CNetworkClient ACK-tail callback source registration

## Complete native and source scope

The previously retained natural source in
NetworkPrimaryPacketContinuationRuntime.cpp is now formally selected and
registered for44E6D0. No C++ source was rewritten. Native CNetworkClient
primary table6C1754 has this callback in slot8 at6C175C; COL6D80BC and type
descriptor6E6924 identify the owner. The entire78-byte body decodes to21
reachable instructions and ends in RET4. Native SHA256:
`d0c302e135a6cab0a56a6b33b09a5f53b6d0544dd69d77e4db6697a17aee9cc0`.

The callback enters the actual critical section at this+25C, copies the local
peer's byte4 into the remote peer's byte4, imports snapshot bytes0E/2E into
owner21A/23A, writes pending3A6=1 and leaves the same critical section. Calls
44E6DC and44E714 reach independently exact11-byte enter/leave wrappers40AC30
and40AC40. These explicit game-state publications establish authored ownership;
this is not a template or compiler cleanup.

The ordinary source remains78 bytes with8 unequal bytes, first+53, SHA256:
`1d45830da4c88ed203cfef7be22ca55769c7f68a4eca0ec8b2252d3a6083c005`.
Only the late side1-byte store and leave-receiver load are reordered. The old
source/register scheduling lane remains closed. No volatile field, fake
liveness, padding, assembly or source-spelling trial was introduced.

## Bounded observations and safeguards

`audit-client-ack-tail.py` compares complete bodies and executes six finite
normal-path cases, including high unsigned bytes and equal local/remote peer
pointers. Both sides preserve RET4 and all nonvolatile registers, publish the
same bytes, leave the snapshot and local peer unchanged, and call enter/leave
in order with the correct receiver. Write hooks permit only the four observed
byte destinations while between the helper boundaries, plus normal stack
writes. Helper simulation clobbers EAX/ECX/EDX/flags rather than depending on
unspecified void-return values.

The helper calls are intercepted; actual Windows critical sections, network
traffic, concurrency and gameplay are not executed or claimed verified. The
observations are finite, not universal equivalence. The existing guarded
callback helper stops on errors and errors are checked immediately after
execution. Changing the source side0 displacement21A to21B is rejected by the
write guard. Four tests cover publication values, lock ordering and readonly
source contracts.

## Reproduction and conservative bookkeeping

```
scripts/repo-python scripts/build.py --unit gpt-web-network-primary-packet-continuation --compare --json
scripts/repo-python scripts/build.py --unit cross-v106a-critical-section-wrapper --compare --json
scripts/repo-python scripts/audit-client-ack-tail.py
```

The first command now intentionally reports an overall mismatch because the
new selector is nonexact. Its two previously accepted functions48/162 remain
canonical exact; accepted-only validation remains unchanged. The critical
section unit is freshly exact. No unrelated source/header or whole-corpus
rebuild is required.

The unchanged generic RTTI/body/call evidence gate validates the new authored
rule. One review row becomes source-present/authored: source1635, authored1654,
mapped1824, review299. Excluded2074, provisional4027 and units812 stay.
Authored exact remains1427 /443604 bytes; matches.csv is unchanged.

Raw pinned target, serial native work CPU0/nice10, no IDA semantics or push.

## Shared-record clarification

The input is the in-process NetworkStateRecord4C with native deques at10/30,
not the separate40-byte CDPP_ACK_INFO C++ packet object or MatchSetup. The
historical ACK-tail label refers to marking ACK pending during state import.
The shared-record follow-up replaces the old narrow input view without changing
its78-byte candidate and adds client/server slot checks; see
NETWORK_STATE_RECORD_2026_11_02.md. The earlier statement that C++ was unchanged
refers specifically to the registration checkpoint.
