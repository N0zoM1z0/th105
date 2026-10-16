# Winsock peer removal and endpoint lookup

## Observed target and authored ownership

Only original Japanese TH10.5 v1.06a was inspected, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.

| Address | Reviewed role | Main bytes | Instructions | Body SHA-256 |
| --- | --- | ---: | ---: | --- |
| `413170` | `NetworkWinsock_remove_peer` | 489 | 141 | `a9e56aea301bd66a443e563205bef0f2e463a67b88e4c8be7631653cbe1822b4` |
| `412A60` | `NetworkWinsock_find_peer` | 167 | 59 | `8b476268fd3f9bb1f3ca227ab33b1b2aee18f5219bd7984d29b1fd6df6e6eb49` |

Both raw CFGs own every main byte, with complete return boundaries and no
outgoing direct branch, indirect jump, overlap or unreached main bytes.
Canonical-exact `CNetworkServer_flush_send_state @ 44F520` calls removal at
`44F538`, using its Winsock member+3B4 and slot0. The independently reviewed
UDP receive loop also calls removal at `41DB7B`. Removal calls endpoint lookup
at `413277`; that lookup additionally serves receive-loop opcodes4/11/14 and
the protocol handler at `415560`. The IP/port filtering and packet/peer policy
are authored behavior, not a generic library exclusion.

Removal consumes ECX plus a32-bit stack slot index and executes RET4. The
lookup's private entry consumes EAX=owner, stack+4=iterator-result pointer and
stack+8=endpoint pointer, returns that result pointer in EAX and executes RET8.
Its source-level iterator is returned through a hidden result object. The
ordinary C++ member definition is retained in the same TU as its caller;
there is no external fabricated fastcall or register declaration.

## Complete behavior and native containers

Removal takes the peer lock at owner+120/native+124. A checked vector access
selects a32-byte record from the vector at+108 (begin+10C/end+110). If its
slot field+10 equals-1, the function releases the lock and returns. Otherwise:

1. Send exactly one byte, opcode0B, through the WS2_32 sendto IAT at6C0274,
   using socket+28 and the record's16-byte endpoint. Ignore the send result.
2. Find that endpoint in the peer index at+FC and erase the returned iterator.
   There is no added not-found guard; native iterator validation remains.
3. Set record+14 to10 and record+10 to-1.
4. Take the callback lock at+84/native+88; if callback+80 is nonnull, dispatch
   slot+14 with the input index. Decrement active count+118 while holding this
   lock, then release the callback lock and finally the peer lock.

All five checked vector accesses are preserved across the external/container
calls. The vector is not shrunk and its records are not deleted. The index
stores pointers to those records, so erasing an index node does not own the
record lifetime. The callback decrement follows the callback: if it throws,
the two lock guards unwind and the decrement has not happened.

Lookup obtains the equal IP-key range from the peer container, then checks
the16-bit endpoint port for each candidate. It returns the first matching
iterator or the container end. Raw `4136E0` uses unsigned key comparisons and
produces a pair of checked iterators; native `std::multimap<unsigned int,
NetworkPeerRecord20*>` reproduces that layout and algorithm. The native tree
node has the value pair at+C, record pointer at+10 and nil flag at+15. Its
12-byte container and the16-byte vector header fit the independent owner
offsets. Compile-time assertions guard these layouts. Unknown record fields
retain offset names; timeout units and original class/type spellings remain
unknown. The callback view uses the observed slot+14; preceding slots are
unreviewed declarations only.

## Exception state and unresolved storage

Removal pushes GS/EH handler `6BDE26`, which validates two cookie/frame contexts
and supplies FuncInfo `6E4450` (magic19930522). Its two-entry unwind map at
`6E4440` has state0 ->-1 through `6BDE10`, and state1 ->0 through `6BDE1B`.
Each11-byte cleanup derives a guard from the enclosing EBP and tail-jumps to
guard destructor `401870`. These compiler auxiliary chunks are recorded
separately, without new authored or exclusion credit.

Only the transmitted opcode byte is independently established as packet
content. The target reserves448h stack bytes, uses an aligned EBP frame and
an additional GS cookie; its larger packet-storage capacity is not established
by a one-byte send. Source uses a real `char packet = 11` and its address.
No expanded buffer, inert local, padding or alignment directive is added to
force that frame.

## Source and strict comparison

`src/network/NetworkWinsockPeerRemoval.cpp` provides the complete removal and
lookup behavior with real native vector/multimap operations and two scoped
lock objects. No shared header or existing relocation permission changed.
Two dedicated target-attested relocations bind this function's EH handler and
the ordinal20 sendto IAT slot. The original IAT dword is80000014, an ordinal
import rather than a hint/name RVA. The local VC8 PlatformSDK `WS2_32.Lib`,
SHA-256 `fc1fbe94773a2bafd735b7123d31e5f9377d8381d704494a7757c8a2eccfec90`,
independently corroborates `_sendto@24` -> WS2_32.dll ordinal20: its x86 short
import member has name-type0 (ordinal) and SHA-256
`677c886dace564fc7dd6ca26b7eec488a4b65d67c46847ba0da1b9396d261168`.
This is import-identity evidence, without library-code exclusion credit.

The focused ordinary VC8 unit reports **440/489 removal** (first difference+0)
and **162/167 lookup** (first difference+2), both **nonexact**. Every relocation
resolves without masks. The source and target also differ in private lookup,
equal-range/iterator and erase call contracts. These differences are recorded
rather than hidden behind external ABI facades.

A resolved `/O2 /GL /GS` diagnostic naturally moves the lookup receiver into
EAX, confirming that a normal member source can acquire the observed private
entry. It also inlines iterator increment, producing227/167 lookup and446/489
removal. A bounded `/Os` control produces207/167 and288/489 respectively;
neither is exact. Neither profile nor comparator was changed. Further tuning
requires original inline/TU context and independent packet-storage evidence.

```bash
python3 scripts/audit-candidate-boundaries.py 0x00412A60 0x00413170 --json
python3 scripts/build.py --unit cross-v106a-network-winsock-peer-removal --compare --json
```

Reports are `build/network-peer-removal-boundaries.json` and
`build/network-winsock-peer-removal-formal.json`. Private resolved LTCG drivers,
commands and logs stay below `.analysis/network-peer-removal-20261016/` and
`build/network-peer-removal-ltcg*/`. The expected full-unit comparison exit is1;
neither function enters matches.csv. The existing server caller unit is
replayed separately as `gpt-web-network-server-primary-protocol`.

Direct Ghidra inspection independently attests executable/program SHA, base,
entry marker, x86 Windows identity and every mapped .text byte. Its decompiler
output remains a hypothesis. Supported names, complete main extents and native
versus custom parameter/result storage are saved and independently read back;
scripts and working databases stay private. One process uses768MiB and two
active processors.
