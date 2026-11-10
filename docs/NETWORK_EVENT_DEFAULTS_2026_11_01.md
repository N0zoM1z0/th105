# Default UDP event interface policy

Three complete authored default callback bodies are now canonical exact:

-43AA10, two-word primary-data notification:3 bytes, RET8.
-43AA20, shared three-word notification:3 bytes, RET12.
-43AA30, route rejection:8 bytes, return9 and RET24; no output writes.

Original primary INetworkUDPEventProc table6C1630 has COL6D7FAC and type
 descriptor6E68C4. Its six native entries are43AA20,44E8E0,43AA10,43AA20,
43AA30,44E8E0. The three-word body is shared by accepted and peer-data callbacks;
it counts once. The one-word null body44E8E0 was already mapped/exact elsewhere
and receives no new credit. Short byte equality alone would not establish
ownership; the independently verified complete RTTI/table and existing actual
network receive/accept/peer-removal callback interfaces establish these roles.

NetworkEventDefaults.cpp uses six ordinary virtual method definitions, no
virtual destructor (none occupies this interface table). The route signature
matches the real six-word callback: slot, response code, payload, size, reply
pointer and reply length. Its default rejects with9 without initializing any
output. The declared state field reflects the previously established eight-byte
secondary interface; no interface allocation or synthetic caller is introduced.
Original method names remain descriptive rather than recovered symbols.

All three complete compiler section tails match without relocations or masks.
Canonical hashes in order:

-1d10894625976bca9d8906f3ecf1e766b94e9219ec3bf1c30e02feea5e18e45a.
-dbd1a662565b07272069f88faadf4327acaf51b7d14f236c84c0a9679d07cef3.
-7916076869ec2aa745befb3ef79db03cb2811aaa7efe913f5cfa51c7db82012b.

The source's same no-op peer-data and one-word methods may be folded; no
nominal uniqueness is claimed and no physical body is counted twice. These
are explicit application-interface policies, not implicit compiler lifetimes.

The independently accepted client93/server289 derived route bodies freshly
remain canonical in gpt-web-network-secondary-route-runtime. Shared source,
headers and prior native ABI contracts are unchanged.

A focused ownership-rule replay checked the full RTTI-owned bodies and every shared
native slot before promotion. Exact entries then use the canonical authored origin
baseline, not a competing census rule. Exact1431 /443916 bytes;
source1634/authored1654/mapped1819/review404/excluded1969/units771. No new library
credit, cold all-exact build or push.
