# UDP request routing and peer admission

## Observed boundary and ABI

The original Japanese TH10.5 v1.06a executable has SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
`NetworkWinsock_receive_request @ 00415560` contains410 instructions /
1355 bytes, all reached by raw CFG traversal. There is one RET4 at415AA8,
with no indirect jump, escaped branch, overlap or remote authored chunk.
Body SHA-256 is
`88cfb779934e14a2dae7c87e48c014676e9fb8b000e0817774411a89dfa45ed1`.

Receive opcode5 calls this function at41DA9E after requiring payload length
to equal its WORD+14 plus24. ECX is the16-byte sender, EDX the packed request
header and the sole stack slot the UDP owner. The entry saves all remaining
general registers before use. This physically fits an ordinary three-argument
x86 fastcall definition; original declared/private spelling remains unknown.
The source uses void because the caller discards the incidental result.

## Complete recovered policy

`src/network/NetworkWinsockReceiveThread.cpp` now supplies the full request
body beside its real receiver and private helper definitions. The owner view
adds the observed keys+4/+14, WORD+24, active count+118 and peer limit+11C,
and names peer+18 as response code. The limit role follows the actual
allocation guard415647/41564F, independently of initialization to16. The
initializer's former `timing_value_11c` name is corrected to `peer_limit_11c`.

1. Drop requests when running+74 is zero or the peer limit is zero. Compare
   all16 key bytes with owner+4, then owner+14 only on the first mismatch.
   Drop a double mismatch before taking a lock.
2. Initialize reply pointer and WORD length to zero once. Leave the response
   code local untouched until a callback writes it. Under a scoped peer lock
   at wrapper+120, find the sender through the native IP-key multimap and
   WORD port filter. An existing nonnull peer proceeds directly to another
   acceptance reply, without routing, allocation or active-count changes.
3. On a miss with active count at least the limit, find the first active peer
   with the smallest positive report+1C strictly below FFFFFFFF. If none
   exists, drop the request. Otherwise inspect at most four circular vector
   positions starting there; this counts inspected positions, not emitted
   addresses. Copy active peers with nonzero reports into the redirect and
   send all69 bytes even when fewer than four addresses were copied.
4. Below the limit, examine inactive vector slots in order. Hold a nested
   callback guard at wrapper+84 while calling vtable slot+10 with six DWORD
   argument slots: index, response-code pointer, payload at request+18,
   zero-extended WORD length+14, reply-pointer output and WORD-length output.
   A null callback or a result other than0/9 continues to later slots. Outputs
   persist across those attempts rather than being reinitialized per slot.
5. Result0 copies the full sender16, writes slot+10, clears probe counter+14
   and stores callback code at+18. It leaves report+1C untouched, inserts the
   real record pointer under its IP key and increments active count. The
   callback guard ends before sending the acceptance, while the peer guard
   remains held. Result9 sends the five-byte rejection and exits both guards.
6. For a nonnull accepted/existing peer, emit opcode6, low slot byte,
   owner WORD+24, stored response code and reply WORD length. Copy payload
   only when its output pointer is nonnull; send13+length bytes to the stored
   peer endpoint. Do not add length clamps, output ownership/freeing, a new
   report reset or reply initialization absent from the target.

The source preserves these wire writes:

| Reply | Bytes | Fields written |
| --- | ---: | --- |
| Acceptance | 13+payload length | Opcode+0, slot+1, WORD+3, DWORD+5, WORD+9, optional data+D |
| Rejection | 5 | Opcode7 and DWORD code+1 |
| Redirect | 69 | Opcode8, DWORD count+1 and only the selected16-byte addresses+5 |

Acceptance byte+2 and bytes+B..C remain untouched. Unused redirect entries,
the peer report+1C and callback response-code local also remain untouched until
their observed producers write them. These are target facts, not new zero
defaults or padding used to obtain a comparison.

## Storage evidence and source controls

Constructor sites43CB84/43CCF4 register the secondary object at owner+6DC with
the UDP subobject+3B4. Their vtables6C16CC/6C1734 dispatch slot+10 to the
independently exact server289-byte44F600 and client93-byte44E880 route bodies.
Both successful routes publish exactly `0x44` (68) bytes.
The base table6C1630 instead points to43AA30, which returns9/RET24 without
writing outputs. The selected reply view therefore reserves the minimum
observed81 bytes: acceptance header13 plus68 data, covering redirect69 too.
This does not recover the original local capacity, and the target's variable
copy/send lengths are not changed.

The initial direct native-container source emits1275 bytes. Two boundary
facts support the selected1265-byte source: a complete file-local checked
accessor naturally produces the target ESI-vector/EDI-index entry, and the
target's insertion returns a native12-byte iterator/bool pair whose first
component is consumed. The source uses the pinned VC8 multimap's public
`_Mybase::insert(...).first` operation. Its real header implementation owns
allocation/insertion. Mapping the separate eight-byte public multimap wrapper
to the target's pair-returning stage would be the wrong boundary.

Selected source remains1265/1355 nonexact, first at+0x10: its frame
is0x98 versus target0x468. A separate control uses the genuine RTTI-backed
`NetworkUdpPacketBuffer41C` and its payload member. It emits1281 bytes with a0x460
frame, still nonexact. That pool type is known elsewhere; its local ownership
is not established here, so neither it nor extra buffer bytes are retained to
fit the target frame. Original local storage and compiler/TU context remain
unknown.

## Dependency equality and provenance

The full actual caller and ordinary typed file-local definitions canonically
reproduce key equality4152A0 at148/148 and checked access413740 at33/33. Their
configured unit records complete extents and all relocations, including the
checked accessor's invalid-parameter call. They use no register directives,
external private-ABI facade, synthetic caller or fake return.

Neither result is accepted as authored progress. The key helper's generic
`memcmp(...,16)==0` operation also appears as `IsEqualGUID` in the pinned SDK
`PlatformSDK/Include/Guiddef.h`; comparison bytes cannot distinguish SDK
ownership from an equivalent wrapper. Native-container versus wrapper
ownership of the checked accessor is also unresolved. Both rows stay in
origin review, outside `implemented.csv` and authored `matches.csv`. Their
physical ABI facts are recorded without assigning durable authored names.
The source's SDK/header hash corroboration is in the raw fact packet.

## EH, link boundary and reproduction

The complete46-byte GS/EH handler6BDDD6 has SHA-256
`8968bd9422fe7e8d69b276ab34d76409717eb74962a423f7d4ed11b93a493039`.
FuncInfo6E441C has magic19930522, two states, unwind map6E440C and EHs flag1.
State0 unwinds to-1 through6BDDC0; state1 unwinds to0 through6BDDCB. Both
eleven-byte chunks derive their guard from the enclosing EBP and tail-jump
to401870. They remain compiler auxiliary code outside the1355-byte main.
The source uses the actual nested peer/callback lifetimes and ordinary EHsc.

A genuine pinned GL/LTCG control includes the actual ordinary-COFF acceptance
and peer-removal source, real VC8 runtime/WS2_32 libraries and attested data/IAT
bindings. Request415560 now resolves. The link stops at LNK2001/LNK1120 for
only the real connection415340 body. No stub, executable ABS binding or forced
unresolved link bypasses it. This establishes the remaining source input,
not a claim that a completed LTCG unit would match.

```bash
python3 scripts/audit-candidate-boundaries.py 0x00415560 --json
python3 scripts/build.py --unit cross-v106a-network-winsock-receive-thread --json
python3 scripts/compare-unit-object.py cross-v106a-network-winsock-receive-thread build/match-units/CrossV106a_NetworkWinsockReceiveThread.obj --json
python3 scripts/compare-unit-object.py cross-v106a-network-winsock-receive-thread build/match-units/CrossV106a_NetworkWinsockReceiveThread.obj --address 0x0041D7B0 --json
```

The complete comparison intentionally returns1 for the two nonexact authored
bodies. The accepted-only callback remains14/14; the two148/33 dependency
controls earn no authored credit. The four affected Winsock runtime functions
are independently rebuilt/replayed after the limit-field rename and retain
148/47/84/68 exact. No shared header, compiler flag or earlier relocation
permission changes. Reports are `build/network-udp-request-{facts,build,formal,accepted}.json`,
`build/network-udp-request-runtime-{build,accepted}.json` and
`build/network-udp-request-ltcg-probe.diagnosis.json`. Fresh source/object
hashes and unit-input digests are independently checked against both builds.
Private recipes stay under `.analysis/network-udp-request-20261016/`.

IDA preflight still identifies another executable and is not used for
analysis. Direct Ghidra attests executable/program SHA, base, entry marker,
x86 Windows identity and all mapped .text bytes. It saves and independently
reads back the1355/148/33 extents and physical parameter/return storage, the
packed24-byte request, native peer/vector types and method-specific13C-byte
owner prefix. Decompiler output remains a hypothesis. Logs are
`build/network-udp-request-ghidra-{inspect,save,readback}.log`; one process is
limited to768MiB heap/two CPUs. The new origin rule classifies only request1355
as authored, with no new exact or library exclusion credit.

## Subsequent connection-chain closure

The later [connection and handshake-worker checkpoint](NETWORK_UDP_CONNECTION_2026_10_16.md)
implements415340 and415D60 in the actual receive TU. A genuine mixed COFF/LTCG
image now links with all actual peer-removal, acceptance and platform-thread
inputs and zero missing implementations. Earlier missing-input statements above
are historical. Native EH/GS replay and original packet storage remain open;
this link success adds no authored exact credit.
