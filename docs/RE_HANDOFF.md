# TH10.5 reconstruction handoff

This is the short operational handoff as of 2026-10-17. The live ledgers and
fresh canonical comparisons override dated prose. Older checkpoints are in
[the October archive](RE_HANDOFF_HISTORY_2026_10_02.md),
[the September archive](RE_HANDOFF_HISTORY_2026_09_26.md), and the focused
evidence notes linked below. Their former "current" and "next" instructions
are historical.

## Target and live state

- Target: original Japanese TH10.5 v1.06a, SHA-256
  `56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
  Never substitute 1.06 or a localized executable.
- Last checked ledger census: **4,023 provisional candidates**, with
  **1,541 authored / 1,415 excluded / 1,067 in review**; **1,454 mapped**,
  **1,434 source-present**, **1,333 exact / 225,099 exact bytes**, and
  **514 match units**. These are ledger/status totals, not a fresh aggregate
  cold replay. Recompute before quoting them.
- `config/claims.csv` remains header-only. `implemented.csv` means source
  present, and only `matches.csv` plus a reproducible canonical 100% unit
  supports exact credit. Candidate size and disassembler analysis do not prove
  function ownership or a compiler boundary.
- The local target passed `scripts/verify-target.py`. The attached IDA MCP
  still reported SHA-256 beginning `10350095` at this handoff, so its data
  cannot be used. Hash-attested raw PE analysis remains available. Existing
  direct Ghidra working databases under `.analysis/` were independently
  checked for target identity, entry and mapped `.text`; re-attest each
  database before a new bounded analysis unit. Do not use the factory adapter.

Run the preflight in [AGENTS.md](../AGENTS.md) before changing reconstruction
state. The source tree predates the corrected target; retained source is a
hypothesis until 1.06a instruction, ABI and comparison evidence support it.

## Active priority: Aya CPU decision root

`Aya_update_cpu_action_policy @ 6126E0` now has complete target-reviewed source:
16032 callable bytes /4097 instructions, six validated switches and no
unresolved transfers. A strict bridge checks all4069 instructions/15910 bytes
of the default CPU target plus all632 metadata bytes. Aya adds only two61-byte
command branches, recovering ordered distance>320, native RNG thresholds20/2,
signed resource>=400 and command728 bits400/200hex. Direct Ghidra saves and
independently reads back void/ECX/no-stack-argument ABI, all4097 instructions,
switch refs and branch comments, with target bytes unchanged.

Fresh whole comparison remains nonexact+12E /61280E,14/41 diagnostic owners,
metadata16052 and section tail16677; no exact credit. Native real-helper
controls pass0/5000 finite and0/470 command/resource/truncation/NaN cases,
including all28 added target instructions. Omitting the additions fails2/2
positive seed controls. The retained source now uses11 genuine opponent pointer carriers and the real
checked VC8 deque; its94-byte template provider replays under the existing
library unit, with no authored credit. Ordinary root compilation is byte-neutral.
Genuine /GL links now close actual engine dependencies and static CRT startup.
A guarded all-float alias control removes the former aligned EBP frame but
still differs at entry; narrower type controls keep alignment. Thus source/type/
TU context remains open, without a claim that LTCG is required or impossible.
Full linked inspection now exposes a79-byte EDI/index-zero deque specialization;
its map name cannot authorize substitution with the target94-byte ECX/RET4
callee. A real SDK COFF instantiation replays94 bytes both before and after
linking, restoring that interface without stubs. The all-float/COFF root closes
16021 reachable bytes /4069 instructions through six bounded switches, but
has119 selector sites versus target114 and a five-entry sequence table versus
target six. Its first16 entry bytes agree; deferred EBP save and control/tail
ownership still differ. Retained types remain a separate15850-byte linked
control. No experiment changes the selected root source or acceptance profile.
The next task is canonical control/register/shared-tail matching using this
verified dependency ABI. See [the complete linked evidence](AYA_CPU_LINKED_ABI_2026_10_17.md),
[the source/dependency checkpoint](AYA_CPU_NATIVE_DEPENDENCIES_2026_10_17.md)
and [the initial source checkpoint](AYA_CPU_ROOT_2026_10_17.md).
No shared C++ header/global ABI/profile or accepted-unit change.

## Shared Fighter action checkpoint

The shared root `Fighter_update_common_action_state @ 4740C0` remains a stable
10219-byte checkpoint used by all15 roster action roots. It retains53/66 diagnostic
owners and remains canonically nonexact+14, metadata+2838 and section tail10801.
The source's7A4 method view now names signed frame limit+14C from the already
exact62-byte frame-advance helper; layout and compiled bytes are unchanged.
A new native motion oracle executes all six original dependencies without
result hooks:0/14208 differences through genuine RET, comparing the actor,
calls, conversion inputs, stack and control word. It visits403/2799 target
instructions under flat-stage/unexpired-frame inputs, not complete gameplay.
A once-rounded action159 control changes velocity by one ULP and is detected;
wall-event inputs fail the explicit context guard. That is the earlier
[native motion checkpoint](COMMON_FIGHTER_NATIVE_MOTION_2026_10_17.md), not
a newly rerun matrix.

The previous common-root batch executes the original animation virtuals, frame/tree lookup
and untextured sprite updates for actions73/75/88:0/6048 sampled differences
through genuine RET, including actor/call/argument/conversion/stack/callee-save/
CW checks. It visits159/2799 target instructions in an explicit resource
fixture; coverage is not added to the old motion count. A NaN zero-test control
produces3/72 differences; missing wall-action context is rejected. Whole-root
comparison retains the same canonical window and53/66 owners. Complete-handler
inline extraction is neutral under nested dispatch and fails the required
owner topology under flat dispatch. See
[the native animation evidence and remaining blocker](COMMON_FIGHTER_NATIVE_ANIMATION_2026_10_17.md).

All2799 raw instructions and eight receiver-domain virtual tails remain
reviewed. Direct Ghidra saves/reads back the ECX/no-stack ABI,52 named data
fields plus the vptr, and helper/receiver evidence while preserving target
bytes. The next task is simultaneous clamp/sequence physical ownership and
SUB lowering with the required rounding retained. Failed source-order,
normalized-index, reference-clamp, complete-handler inline and earlier FP
controls are not retained.
No exact or partial byte credit. The prior receiver/control details remain in
[the complete common-root record](COMMON_FIGHTER_ROOT_2026_10_16.md).

The default CPU root `5F1F80` is a stable15910-byte source checkpoint. Its signed
policy selector and action300 store arms remain intact; whole comparison is
nonexact+12E, metadata+3E38, section tail16553 and15/41 diagnostic owners.
Earlier native controls have0/1408 boundary,0/5000 finite,0/16000 policy0 and
0/368 height differences. These are historical checkpoint results, not rerun
in this common-root batch. New counter320 controls preserve signed compares
but move the shared store/branch ownership; they are discarded. See
[the CPU source checkpoint](CPU_SOURCE_OWNERSHIP_2026_10_17.md). No unrelated
accepted-unit or aggregate cold replay is claimed.

The receive chain is fully implemented/linked; the connection checkpoint
retains target-backed handoff/DNS lifetimes and isolates a genuine84-byte
linked residual beginning+14C. Direct clear and RTM controls were negative.
Its ordinary524-byte connection and accepted14-byte callback are unchanged.
See [the connection record](NETWORK_UDP_CONNECTION_2026_10_16.md).

## Receive-chain link closure: connection and handshake worker

The complete UDP receive/connection subsystem is source-present.
`NetworkWinsock_start_connection @ 415340`
(160 instructions/542 bytes) and its actual native worker
`NetworkWinsock_connection_thread_entry @ 415D60` (286/1009) now have complete
source in the receive TU. Persistent request ownership/FFFF reuse, numeric/DNS
endpoint selection, stack handoff acknowledgement, auxiliary UDP socket,
endpoint/port probes, candidate rotation and state2/3/6 retries are closed.
A genuine mixed COFF/LTCG image now links the entire receive/request/connection
chain with actual peer-removal, acceptance and platform-thread implementations:
**zero missing link inputs**, with no source stubs or executable ABS bindings.
Preserving the real connection entry's external UI call surface restores its
linked542-byte body; ordinary connection524 and worker945 remain nonexact.
A target-backed two-native-packet control is992/1009 with frame860 versus870,
so the original storage is still unresolved, without added padding. The linked
callback remains a canonical14-byte diagnostic, and its configured ordinary
accepted replay is exact. No new exact credit. Ghidra types/ABI/body metadata
are saved and independently read back. The next major blocker is canonical
comparison of the fully linked receive roots: native EH/GS data ownership,
switch metadata and source packet storage, rather than missing implementations.
See [the connection, worker and real link evidence](NETWORK_UDP_CONNECTION_2026_10_16.md).

## UDP request and peer admission

`NetworkWinsock_receive_request @ 415560` now has complete source in the real
receive TU. All410 instructions/1355 bytes close; running, dual16-byte key and
peer-limit checks precede nested peer/callback guards. Existing peers receive
another acceptance; full capacity chooses the lowest positive peer report and
inspects at most four circular positions; free slots route through callback
slot+10 and preserve accept/reject/retry behavior. Packed reply holes, unused
redirect entries and peer report+1C remain untouched. Current observed reply
storage81 covers header13 plus the two known providers'68 bytes. Source is
1265/1355 nonexact; a genuine41C packet-type control is1281/1355, with frame460
versus target468, and is not retained as an invented storage claim. Private
key148 and checked access33 are canonical byte controls but remain in origin
review, without authored/source/exclusion credit. SDK IsEqualGUID provenance
cannot be distinguished from an equivalent wrapper. The actual native tree
insertion stage returns12 bytes and its iterator first component is consumed.
At that checkpoint the mixed-source link stopped on connection415340; the
connection/worker section above now closes all genuine inputs. No source
stub or executable ABS binding is used. Callback14 and all four affected
Winsock runtime helpers retain exactness. Ghidra request/control ABI metadata
is saved/read back. See [the policy, storage and provenance evidence](NETWORK_UDP_REQUEST_2026_10_16.md).

## UDP receive-loop source

`NetworkWinsock_receive_loop @ 41D7C0` now has **complete source**, together
with its real callback and file-local lookup/rejection/endpoint-list helpers.
The364-instruction/1424-byte target closes through its14-entry switch; the56
metadata bytes and four EH cleanups remain separate. Source main1456 plus56
metadata bytes is nonexact, first at+0x16 on frame470 versus890. Native peer
map/vector views, all opcode gates and manual versus scoped locks are
preserved. The actual caller naturally generates EAX lookup and ESI rejection;
no register facade or synthetic caller is used. Minimum21-byte forwarding
reply storage preserves its four untouched tail bytes. The accepted callback
stays14/14 with the full source and GS enabled. A genuine mixed-source LTCG
attempt resolves actual acceptance/peer-removal bodies and then stopped on missing
connection415340; the connection/worker section above now closes all inputs. Original reply capacity,
endpoint-helper/STL boundaries and TU remain open. No new exact credit.
Direct Ghidra owner types and complete caller ABI are saved/read back. See
[the opcode map, source and link boundary](NETWORK_WINSOCK_RECEIVE_2026_10_16.md).

## UDP connection acceptance

`NetworkWinsock_accept_connection @ 415AB0` now has complete source in
`src/network/NetworkWinsockAccept.cpp`. Its observed ECX sender, EDX owner,
stack packet and RET4 physically fit a normal fastcall definition, with no
register adapter or synthetic caller. The complete69-instruction/223-byte
handler copies the sender and clears the probe counter under the endpoint
lock, invokes callback slot0 under a nested callback lock, and changes
state3 to0 before reverse guard destruction. The packed12-byte packet view
preserves DWORD code+4, WORD length+8 and payload+C. Ordinary223/223 remains
nonexact on incoming-register saves and EH-state scheduling. A genuine
resolved223-byte LTCG control reproduces both target EH-state windows but
retains reversed entry saves; native linked EH/GS replay is not supported.
Original standard/private spelling and TU remain unknown. No exact credit
is added. Direct Ghidra metadata/types are saved and independently read back.
See [the ABI, EH facts and focused controls](NETWORK_UDP_ACCEPT_2026_10_16.md).

## UDP probe worker

`NetworkWinsock_probe_thread_entry @ 416F40` now has complete ordinary
stdcall source in `src/network/NetworkWinsockProbeThread.cpp`, retaining the
initializer's existing callback symbol. Raw closure covers201 instructions /
682 reachable bytes plus ten skipped internal alignment bytes through RET4.
It sends the five-byte opcode4 report, preserves dynamic checked peer-vector
accesses and manual locks, removes peers on the old counter>=10, transitions
primary state0 to6 on the same threshold, and uses a private local auto-reset
event for pacing. Selected minimum-storage source is664/692 nonexact. A real
41C pool-packet control is670 bytes; genuine fully resolved mixed COFF/LTCG
links with actual peer-removal source retain664/670. Original local storage,
aligned GS frame and report-value meaning remain open, with no new exact
credit. Direct Ghidra owner/peer types and full callback ABI/body are saved
and independently read back. See
[the behavior, callback registration and source controls](NETWORK_UDP_PROBE_WORKER_2026_10_16.md).

## UDP shutdown preparation

`NetworkWinsock_prepare_udp_shutdown @ 4130D0` now has complete source beside
its real shutdown caller in `src/network/NetworkWinsockShutdown.cpp`. The
46-instruction/149-byte target sends opcode0B under the native endpoint lock,
removes each dynamically counted peer and resets state144 to1. A genuine
file-local normal C++ helper naturally recovers the private ESI entry; the
existing caller remains175/175 exact. Preparation115/149 remains nonexact
because the target aligned0x42C GS packet-storage frame is unresolved. The
selected source uses only the established transmitted byte. Reusing the real
41C pool-buffer type produces150 bytes, and a fully resolved mixed COFF/LTCG
control with actual peer-removal/thread sources retains that150-byte shape;
it also encounters unsupported native GS-cookie data replay. No larger
buffer, padding or synthetic callee is retained, and this is no new exact
credit. Direct Ghidra owner/peer types, ESI preparation versus ECX caller
storage and complete extents are saved and independently read back. See
[the behavior, source controls and remaining storage question](NETWORK_UDP_PREPARE_SHUTDOWN_2026_10_16.md).

## UDP initialization and native worker ownership

`NetworkWinsock_initialize_udp @ 412E10` now has complete ordinary C++ source
in the same Winsock runtime/error TU. Full raw CFG closes149 instructions /
441 bytes, reached by two independently exact MenuConnect callers. Native
peer-vector assignment, duplicate16-byte key copy, Winsock/socket/bind failure
paths, prior-buffer and token cleanup, three native thread starts and the
first two priority15 calls are all implemented. Target only establishes AL0/1;
source bool is a hypothesis, and the older UI int-forwarding declaration is
not changed without reviewing its consumers. The ordinary POD-source result
is439/441 nonexact on aligned GS frame, private vector interface and API
pointer allocation. A full file-local bind helper naturally reproduces its
68-byte ECX/EAX body, now separately accepted as
`NetworkWinsock_bind_udp_socket @ 413080` at **68/68 canonical exact**. A resolved LTCG attempt stops on missing real callback
and wait link inputs; no replacement bodies or executable ABS bindings are
introduced. This neither proves LTCG necessary nor proves it would match.
Adding the actual caller preserves all three accepted runtime helpers at
148/47/84. Supported owner/key/peer types and physical caller/callee storage
are saved and independently read back in direct Ghidra. See
[the complete behavior, controls and remaining boundary](NETWORK_UDP_INITIALIZE_2026_10_16.md).

## Winsock reference lifetime

`NetworkWinsock_acquire_runtime @ 41DDC0` is canonical **148/148** from ordinary
C++ and its complete file-local error reporter. Full switch-resolved CFG owns
40 instructions; all103 adjacent dispatch bytes also replay exactly and earn
no authored credit. The zero-reference path calls WSAStartup twice with
version2/the same native WSADATA, ignores the first result and dispatches the
second failure through five observed texts. Success increments the shared
count; all paths release the native lock. The private helper naturally uses
ESI without an ABI facade. `NetworkWinsock_show_error @ 41DEF0` is also canonical **84/84**, with
its complete256-byte GS buffer and native formatting/dialog calls. All three
reviewed callers discard incidental EAX. No external private-register facade
is used. Direct Ghidra metadata is saved and independently read back.
`NetworkWinsock_release_runtime @ 41DEC0` is also canonical **47/47**. Its
10-instruction body decrements only a positive unsigned count and calls
WSACleanup only on transition to zero under the same lock. Adding this real
member of the source TU preserves the acquisition at148/148.
See [the complete control flow and comparison](NETWORK_WINSOCK_RUNTIME_2026_10_16.md).

## UDP client sender and real private-helper context

`NetworkWinsock_send_loop @ 416DB0` and its real native callback `416D90`
now have complete source in the same sender/helper TU. Full raw CFGs close
395/18 bytes. The worker creates/waits/closes its event, drains the locked token
deque, looks up packets, sends only unexpired packets and recycles every valid
token. Packet+14 now has the observed `timeout_ms_14` meaning, with zero
disabling expiry. The actual pinned SDK import library resolves the target's
ordinary sendto E8/thunk; strict source/target ordinal, symbol, library, thunk
and IAT checks join linked provenance. The complete worker is395/395 nonexact
on callee-save shrink wrapping; the callback is16/18 nonexact on scratch-frame
reservation. Their private ESI interface arises naturally from real source.
No new exact credit is added. Fresh focused replay preserves scene281,
pool98 and release167; all155 local CI tests pass. Original frame/optimizer
context remains open. See [the complete behavior and comparison evidence](NETWORK_UDP_SEND_WORKER_2026_10_16.md).

`NetworkWinsock_send_server @ 416B60` now shares the complete sender/helper
source in `src/network/NetworkWinsockSendClient.cpp`. Full raw CFG closes
168 instructions/all548 bytes. It checks the32-byte peer record before any
allocation, returns immediately for slot+10==-1, and rechecks the endpoint
under peer lock+120. Active requests enqueue opcode0D with the same token
replacement policy as the client. Source uses void: the inactive path has no
established meaningful EAX result, so no synthetic return value is added.
Ordinary548/548 remains nonexact at+42 on the private acquire call; the formal
two-sender mixed unit gives644/548 nonexact on inlining/context. All relocations
resolve, and the accepted shared release remains167/167 with both genuine
senders exported. Source layout assertions now include peer vector+108 and
lock+120. See [the behavior, ABI and full comparisons](NETWORK_WINSOCK_SEND_SERVER_2026_10_16.md).

`NetworkWinsock_send_client @ 416990` has complete source in
`src/network/NetworkWinsockSendClient.cpp`, alongside the actual acquire and
release member definitions. Full raw CFG closes145 instructions/all464 bytes.
Type0E packet/options/timestamp, locked endpoint copy, payload/size, native
token deque and optional old-token replacement precede SetEvent and its return.
Ordinary source is **465/464 nonexact**, with all relocations resolved.
The real caller makes LTCG naturally recover stack self for acquisition and
EAX self for release. Source stays normal C++ members; no private ABI facade
or dummy caller is added. Sender inlining still differs: native token push_back
is out of line in the target, but561 bytes with retained-source/list context.
See [the complete sender and context controls](NETWORK_WINSOCK_SEND_CLIENT_2026_10_16.md).

`CHandleManager_release_token @ 405200` is now canonical **167/167** in
`cross-v106a-network-winsock-send-client`. Full raw CFG independently closes
63 instructions; nine callers include two exact Title resource methods as well
as the UDP sender. Shared game policy checks low16 slot/high16 generation,
zeros matching generation and appends the free index under a manual lock;
it does not destroy payload. The source remains an ordinary C++ member.
The mixed link uses the existing ordinary unsigned-list instantiation and
naturally generates the private EAX receiver/RET4. A narrow `private_from`
contract verifies a unique source-owned, nonexported/nonaliased map entry,
fully closed source/target caller bodies and their unique direct E8 edge
(`416B01` in the original). Full callee CFG, calls, IATs and all167 bytes are
compared. The sender remains561/464 nonexact; selecting the accepted helper
still validates its real caller. See [the exact shared helper and contract](HANDLE_MANAGER_RELEASE_2026_10_16.md).

The original TU and token-queue inlining remain unresolved. Continue with the
remaining real UDP callers rather than adding fake callers or
ABI facades. Replay only affected accepted units during iteration; this batch
adds167 authored exact bytes without a fresh aggregate cold replay.

## UDP owner and packet-pool lifetime

`NetworkUdpPacketHandleManager_acquire @ 417660` now has complete native
C++ source in `src/network/NetworkWinsockSendClient.cpp`. Full raw CFG closes
125 instructions/all410 bytes. Two authored send paths `416990`/`416B60`
pass the pool+17C and output token on the stack. The source preserves zeroed
fresh packets, stable pointers, LIFO free-slot reuse, checked vectors and
16-bit slot/generation writes under a scoped lock. Reused payload is retained.
The focused ordinary candidate is **427/410 nonexact**, with every relocation
resolved. Ordinary GS-minus387 and resolved LTCG540/486 controls also differ;
the latter recover alignment but change inline/helper context and keep ECX
self. Its new real caller now naturally recovers stack self under LTCG, but
the helper still differs on inline/EH context. Keep the real member definition
and recover the remaining TU context rather
than adding private ABI facades. One new nonvirtual declaration leaves layout
and vtable order unchanged; a fresh pool-destructor rebuild remains98/98.
Ghidra physical stack parameters, token/payload types and full main extent
were saved and independently read back. See
[the complete behavior, EH and controls](NETWORK_UDP_PACKET_ACQUIRE_2026_10_16.md).

`NetworkUdpPacketHandleManager_dtor @ 413820` is canonical **98/98** in
`cross-v106a-network-udp-packet-pool`. RTTI identifies
`CHandleManager<NET_PACKET_UDP_BUFFER>`; packet allocation and native members
establish the real0x64-byte layout. Ordinary C++ member destruction matches
after a resolved mixed COFF/LTCG link: an ordinary VC8 `std::list<unsigned int>`
instantiation preserves its normal helper ABI, while the packet deque retains
the target's private ESI helper. Typed primary-vtable replay checks source and
target RTTI/entry identity plus exact HIGHLOW fields. Compiler-library source
and generated wrappers receive no authored credit. The original TU remains
unknown. See [the source, ownership and strict evidence](NETWORK_UDP_PACKET_POOL_2026_10_16.md).

The same source's constructor `413780` remains nonexact: the target has a
private stack receiver/RET4, while source keeps an ordinary C++ constructor.
Its linked EH surface is still unsupported. The owner is original `CNetworkUDP`,
source view `NetworkWinsockState314CtorView`: corrected native peer multimap+FC,
real packet manager+17C and separate owner event+1E0 give **354/357 ctor** and
**398/333 dtor**, both nonexact. The second tree+15C still lacks a concrete type.
Continue from native container/lifecycle context; do not invent private ABI
facades. Ghidra types, full extents and parameter storage were saved and read
back after independent target attestation.

Fresh native source also proves that owner scalar deleting wrapper `412C80`
is compiler-generated. Its canonical30/30 remains a configured witness, but
its former authored match/source credit is removed. Packet-pool wrapper
`4138B0` also reproduces30/30 and retains its prior compiler exclusion.
This batch adds98 authored exact bytes and removes30 compiler bytes: net68.
Revalidate only affected units during iteration; aggregate exact totals still
require a separate cold `--all` replay.

## Winsock receive-thread boundary

The related `NetworkWinsock_remove_peer @ 413170` and
`NetworkWinsock_find_peer @ 412A60` now have complete native vector/multimap
source in `src/network/NetworkWinsockPeerRemoval.cpp`. Full raw CFGs close
489/167 bytes and141/59 instructions. Exact server caller44F538 independently
establishes removal ownership/receiver; endpoint lookup is source-defined in
the same TU. Focused candidates are **440/489** and **162/167 nonexact**.
The target's large packet-storage/aligned GS frame and private compiler/iterator
context remain unresolved. One-byte protocol content is preserved without
guessing a larger buffer. A real LTCG control naturally generates lookup's EAX
receiver, but changes iterator inlining and still differs. Keep the paired
source together, retain real lock scopes and all five vector checks, and do
not replace the private entry with an external ABI facade. See
[the behavior, full comparisons and negative controls](NETWORK_WINSOCK_PEER_REMOVAL_2026_10_16.md).

`NetworkWinsock_receive_thread_entry @ 41D7B0` is canonical **14/14** in
`cross-v106a-network-winsock-receive-thread`. Native CreateThread registration
at412F7F passes the Winsock owner and stores worker+64/+68; ordinary C++ forwards
the pointer in ECX, calls the loop, returns zero and pops the parameter.

## Accepted exact unit: Application message loop

`Application_run_message_loop @ 0x00408120` is canonical **177/177** from
`src/platform/ApplicationMessageLoop.cpp`, unit
`cross-v106a-application-message-loop`. Full CFG closure reaches65 instructions;
a real28-byte MSG frame, running+4C, native message dispatch and the D3D idle
check/reset/four-millisecond event wait reproduce the complete callable on the
first source probe. All eleven relocation fields replay. Four new imports and
a dedicated HRESULT+1A4 mapping preserve existing backend permissions and shared
contracts. Ghidra metadata was saved/read back after independent target
attestation. See [the behavior and exact evidence](APPLICATION_MESSAGE_LOOP_2026_10_16.md).
Bootstrap and both singleton workers now have complete nonexact source;
WinMain retains its separate four-byte frame residual.

## Source checkpoint: WinMain

`WinMain @ 0x00665810` now has complete source in `src/platform/WinMain.cpp`,
unit `cross-v106a-winmain`. Raw CFG closure covers201 instructions/all695 bytes
through RET16. CRT ownership, version/archive strings, RTTI-backed scene/fade
allocations and exact option/shutdown callees establish authored identity.
The complete VC8 candidate is695/695 and differs in only eight stack-frame/home
bytes: target reservation270 versus source26C. Every branch, call and non-stack
byte agrees. Buffer capacity beyond260 and original frame ownership remain
unknown; no extra buffer bytes, fake local or alignment are added. RTM697 does
not resolve the frame difference. Direct Ghidra metadata was saved and read
back. This is source-present only, without exact credit. See
[the full behavior and bounded residual](WINMAIN_2026_10_16.md).
The message loop is exact; bootstrap `407DA0` is source-present/nonexact.

## Accepted exact unit: Application shutdown

`Application_shutdown @ 0x00407F80` is canonical **245/245** from
`src/platform/ApplicationShutdown.cpp`, unit
`cross-v106a-application-shutdown`. All 82 instructions are reached; its sole
indirect exit resolves to the PE-attested OLE32 CoUninitialize IAT tail jump.
The source preserves four thread joins, two SetEvent signals, explicit scene
locking, virtual scene deletion, CSceneManager/CFade callback shutdown/free,
and IME/subsystem teardown. Existing shared contracts and mappings did not
change. Direct Ghidra metadata was saved and read back after target attestation.
See [the ownership, layout and full comparison](APPLICATION_SHUTDOWN_2026_10_16.md).
The same chain's WinMain and bootstrap `407DA0` are source-present/nonexact.

## Accepted exact unit: Application startup options

`ApplicationStartupOptions_ctor @ 0x00407BB0` is canonical **54/54** from
`src/platform/ApplicationStartupOptions.cpp`, unit
`cross-v106a-application-startup-options`. Raw WinMain and bootstrap edges
establish the 40-byte option value, window/instance and callback pointers,
and graphics/input/audio/IME/cursor gates. Ordinary C++ defaults reproduce the
whole return-terminated extent; no relocation or shared accepted contract
changed. Unknown scalar/flag purposes retain offset names. Direct Ghidra
metadata was saved and read back after independent target attestation. See
[the layout, ownership and comparison evidence](APPLICATION_STARTUP_OPTIONS_2026_10_16.md).
WinMain `665810` and application bootstrap `407DA0` are source-present/nonexact.
Their observed control flow does not grant exact credit.

## Application bootstrap island

`Application_initialize_window_paths @ 0x0040D020` is canonical **137/137**
from the complete caller/private-helper TU `src/platform/ApplicationBootstrap.cpp`.
Ordinary static stdcall source naturally generates the observed ECX instance,
stack HWND and RET4, with a real char260 buffer and GS cookie. Bootstrap
`407DA0`, graphics `4147E0` and audio `418670` also have complete source and
independent authored ownership evidence, but remain **447/472**, **539/547**
and **561/583** respectively. Original frame/argument optimization remains open;
the diagnostic LTCG audio frame changes without reproducing the target ABI.
All four raw CFGs close their full callables. Direct Ghidra metadata is saved
and read back under independent target attestation. See
[the ABI, exact result and residuals](APPLICATION_BOOTSTRAP_2026_10_16.md).
Keep this closed TU together; no shared headers or earlier relocation
allowlists changed.

The native control/graphics COM thread entries `408800`/`408820` are now
canonical **28/28 each** from `src/platform/ApplicationThreadEntries.cpp`.
The same unit now includes scene-creation callback `408840`, canonical
**48/48**, which dispatches manager slot+10 using requested state+B0 and
publishes pending scene+80. Both earlier entries were replayed from the changed
object and remain exact.
Their ordinary Win32 callback signatures reproduce both full callables and
all import/worker relocations. No shared source or mapping changed. See
[the ownership, ABI and exact evidence](APPLICATION_THREAD_ENTRIES_2026_10_16.md).
The graphics singleton worker `4084F0` now has complete source, **401/401
nonexact**, in `src/platform/ApplicationGraphicsWorker.cpp`. Raw normal CFG383
plus table-referenced catch(int)/continuation18 close the entire callable;
the option branch reads startup flag at application+2D. Twenty differing bytes
remain in EH state-write ordering and two register choices. No exact credit
is added. See [the exception, layout and focused comparison evidence](APPLICATION_GRAPHICS_WORKER_2026_10_16.md).
The control worker `4081E0` now has complete source in
`src/platform/ApplicationControlWorker.cpp`, **787/771 nonexact**. Normal
CFG755 plus table-owned int-catch16 close the full771-byte callable. Its
three controlfp_s calls query state, select upward rounding200/mask300 and
reset default9001F; they do not select24-bit precision. Frame, stack cleanup,
tail sharing and EH-state scheduling remain unresolved. See
[the behavior, FP/EH facts and comparison](APPLICATION_CONTROL_WORKER_2026_10_16.md).
No exact credit is added for the worker.

## Accepted LTCG unit: Scene retirement

`Application_scene_disposal_thread_entry @ 408870` is canonical **281/281**
from real checked-list source in `src/platform/ApplicationSceneLifecycle.cpp`.
The native COFF candidate is278; genuine VC8 /GL+LTCG naturally generates the
target's aligned dual-EBP frame and full body. The new resolved linked-PE unit
pins tool/header/import-library inputs, proves export/map/CFG ownership and
replays every named call/data reference without masks or synthetic callees.
It is a comparison artifact, never an executed replacement image. See
[the source and exact evidence](APPLICATION_SCENE_LIFECYCLE_2026_10_16.md) and
[the linked comparison contract](LINKED_PE_MATCHING.md).

Its source producer `Application_commit_pending_scene @ 408080` remains
**189/148 nonexact** on frame/insertion ownership. Native12-byte list+84,
event+90 and scene hooks are recovered, with full source and independent
authored ownership. Private53-byte insertion `4089C0` and constant-count
Incsize `40C6D0` still have no new source/exact/exclusion credit. Recover original
template visibility before tuning that producer. Keep the paired TU together.
Fresh resolved `/Os`, `/Ob1` and `/GS` controls do not recover the producer's
outlined insertion. `/GS` changes `_Incsize` to153/154 with a different frame;
`/Ob1` leaves producer189 and callback281 unchanged. Verified shared growth
callers include independent device/audio pointer lists. These are bounded
negative/ownership observations only; see the visibility-controls table in
the scene-lifecycle evidence note before repeating those experiments.

## Accepted exact unit: Sprite texture setup

`CSpriteEx_set_texture_options @ 0x00407160` and
`SpriteTexture_initialize_rectangle @ 0x00407230` are canonical **193/193**
and **261/261** from `src/battle/SpriteTextureSetup.cpp`, unit
`cross-v106a-sprite-texture-setup`. The whole caller/helper TU supplies real
unsigned dimension locals, float UV/source-quad lifetimes and the observed
zero/color assignment order. A normal file-local static stdcall definition
lets VC8 naturally generate the helper's private EAX pointer and RET24; no
external fake ABI declaration, assembly or register directive was introduced.
This demonstrates that a private register entry alone does not prove an
LTCG-only blocker. Keep this closed TU together and replay both functions
after visibility or convention changes. Existing texture wrapper and CLogo
caller units were also replayed. See
[the exact evidence and reproduction](SPRITE_TEXTURE_SETUP_2026_10_16.md).

## Active reconstruction lead: Iku Fighter vslot +0x28

`Iku_dispatch_action_state_vslot28 @ 0x00620920` has a hash-attested complete
callable `[620920,62EFBE)`: **59,038 reachable bytes**, **15,132 instructions**,
131 returns, three compressed action switches, and no unreached bytes or
external direct jumps. The target body has 4,676 x87 instructions and no
`FSINCOS` or `FRNDINT`. The attested Ghidra decompilation drops some reachable
blocks and remains a private hypothesis. The root is **identified and
declaration-only**, with no source-present or exact claim. See
[the boundary and action map](IKU_VSLOT28_BOUNDARY_ACTION_MAP_2026_10_02.md).

Target-to-target comparison of Iku actions 0–10 against Youmu established
shared helper topology but different constants and x87 zero lifetime; see
[the opening comparison](IKU_OPENING_ACTION_TARGET_COMPARISON_2026_10_02.md).
Actions 565–568 occupy 8,390 consecutive physical bytes and each has 14
static object-818 spawn call sites. They share cross-case tails; 567/568 add a
descending stage-crossing path. See
[the object-818 family evidence](IKU_565_568_OBJECT_818_FAMILY_2026_10_02.md).
The tracked `scripts/audit-iku-object-818-family.py` reproduces its diagnostic
JSON from the exact PE without a cached action-map report:

```bash
python3 scripts/audit-iku-object-818-family.py
```

Next, recover the remaining action families, payload semantics, helper ABI,
x87 lifetimes and shared-tail conditions from target instructions. Select
natural VC8 C++ only after those facts support it, then configure and compare
the complete root. TH08's VC7 inline `FSINCOS` is only a technique reference;
it does not establish an assembly requirement here, and this repository
forbids assembly for forced comparisons.

## Renderer source checkpoints

`CSprite_render @ 0x00406BE0` and `CSprite_render_fvf4142 @ 0x00406E50`
now have complete source in `src/ui/SpriteRender.cpp`. Both are 610-byte
CSprite primary-vtable entries, independently owned by the exact-backed
constructor and Menu cursor caller. The new origin rule adds two authored
roots / 1,220 bytes from the review queue. Each raw CFG closes all 210
instructions, and the target pair differs only in its FVF push. Fresh strict
VC8 candidates are 610 bytes with the first 541 canonical bytes equal; only
two COM method-loading/argument-scheduling windows remain nonexact. Their
16-byte frame and all floating geometry match, so do not conflate this lead
with the tile's unresolved frame reservation. The target-only checker is
`scripts/audit-sprite-render-family.py`; see
[the source, ownership and comparison evidence](SPRITE_PRIMARY_RENDER_2026_10_16.md).
No exact credit or accepted match-unit row was added. Original TU/inline
visibility and COM scheduling remain unknown.

`UiTileA4_render @ 0x004099F0` now has complete natural C++ source in
`src/ui/UiTileRender.cpp`. Fresh raw CFG closure reaches all 246 instructions /
756 bytes, and independently attested direct Ghidra sessions saved and read
back the `(float x, float y, int column, int row)` thiscall contract. The source
recovers float geometry/UV lifetimes, rotation and cached texture submission.
Strict FP with local exception scheduling off produces 756 bytes, nonexact at
+2: target frame 12 bytes versus candidate eight. The first 624 bytes differ
only in frame allocation and ESP homes; the tail also differs in COM method
load/push scheduling. No dummy stack slot or exact credit was added. See
[the source, controls and reproducible comparison](UI_TILE_RENDER_2026_10_16.md).
Existing shared headers and accepted match units were unchanged. Investigate
original inline/TU ownership before repeating the documented negative controls.

`CSpriteEx_finalize_render @ 0x00407AD0` also has complete ordinary source in
`src/battle/SpriteRenderFinalizer.cpp`, using the existing CSpriteEx layout.
All 67 instructions / 219 target bytes are reviewed. The 219-byte strict-FP
candidate is nonexact at +0x12 because it hoists the texture handle load/push.
All 43 x87 operations and the final 56-byte submission tail agree; this is
diagnostic evidence only. Normal submission-wrapper and handle-view probes
are byte-neutral, while plain strict FP and disabling global optimization
worsen codegen. See [the focused evidence](SPRITE_RENDER_FINALIZER_2026_10_16.md).
The original scheduling/TU phase remains unknown; no exact claim was added.
New RTM and ordinary base-submission-member controls reproduce the same
comparison bytes as the SP1 source; they do not explain the handle hoist.

TH075's local R182 evidence corroborates the 3600-entry angle-table policy,
but its integer-abs conversion order differs from TH105's float-phase path.
Do not transfer source or compiler assumptions between them.

## Other bounded nonexact leads

| Target | Current evidence and blocker |
| --- | --- |
| `Youmu_dispatch_action_state_vslot28 @ 0x00530200` | Source-present 37,692-byte root; latest canonical first mismatch `+0xCA`, 31/98 diagnostic owners. Physical return sharing, float lifetimes and TU context remain open. [Latest controls](YOUMU_SHARED_ZERO_RETURN_AND_CONTROLS_2026_10_02.md). |
| `AyaObject_update_action_state_vslot28 @ 0x0061A290` | Source-present 19,522-byte root; still nonexact at `+22`, with unresolved action-903 fade-tail/x87 scheduling and other cases. [Latest controls](AYA_OBJECT_903_FADE_TAIL_CONTROLS_2026_10_02.md). |
| `AyaObject_initialize_action_entry @ 0x0061F0B0` | Source-present 4,531-byte root; 11 target vslot+0x0C calls order `MOV ECX,ESI` before `PUSH EAX`, unlike the candidate. [Call scheduling](AYA_ENTRY_VSLOT0C_SCHEDULING_2026_10_02.md). |
| `YoumuObject_initialize_action_entry @ 0x00543670` | Source-present 5,159-byte root; nonexact at `+0x80`, with 6/30 diagnostic owners. [Load timing](YOUMU_OBJECT_ENTRY_LOAD_TIMING_2026_10_02.md). |
| `Fighter_update_common_action_state @ 0x004740C0` | Source-present 10,219-byte root; nonexact at `+0x14`, 53/66 diagnostic owners. [x87 and Ghidra audit](COMMON_FIGHTER_X87_AND_GHIDRA_2026_10_02.md). |
| `AnimationObject_prepare_render_transform @ 0x00435360` and `render_to_battle_scene @ 0x00435740` | Each candidate has the target size but differs in `FILD`/`PUSH EDI` scheduling; no exact claim. [Focused evidence](ANIMATION_RENDER_EDI_X87_SCHEDULING_2026_10_02.md). |
| `KomachiObject_emit_owner_gated_object_826_pair @ 0x005F9350` | Source-present 205-byte target, 203-byte candidate; call argument/register scheduling remains open. [Focused evidence](KOMACHI_PAIR_CALL_SCHEDULING_2026_10_02.md). |

Do not extrapolate a global VC8 flag, assembly need or LTCG explanation from
these local differences. Existing negative source/compiler probes are recorded
in the linked notes; repeat them only with new independent evidence. Recent
accepted exact anchors include
[fighter body collision](FIGHTER_BODY_COLLISION_2026_10_02.md) and
[three-axis sprite rotation](SPRITE_PIVOT_ROTATION_2026_10_02.md).
The separate origin/boundary review queue is documented in
[the focused review](ORIGIN_BOUNDARY_REVIEW_2026_09_26.md).

## Local state, artifacts and gate

The user's October 16 instruction is to prioritize reconstruction and avoid
routine full replays. Default to the current function/unit and accepted units
affected by shared changes. Reserve a cold all-unit replay for an intentional
aggregate verification checkpoint. The October 16 all-unit run was stopped
at the user's request after **113/464 units passed**; it is neither a completed
aggregate replay nor a comparison failure. The latest texture pair and its
affected callers had already passed focused comparisons and the local CI gate.

At the October 2 checkpoint the ignored `build/` directory was cleared, including old
objects, reports, caches, a CI virtual environment, and downloaded reference
copies. Compiled object/link products and Python bytecode scattered in
`.analysis/` were also removed; private probe source and Ghidra databases
remain. The October 16 render probes regenerate small objects/reports under
`build/`; private source and Ghidra state stay under `.analysis/`. Dated notes may name former `build/` report paths as reproduction
references; those files are absent until their commands are rerun. The pinned
official VC8 manual can be fetched and regenerated through
[the reference guide](VC8_REFERENCE.md). Private `.analysis/` Ghidra state and
`.tools/` compiler installations were preserved; neither is committed.
On October 16 the redundant `.tools/msvc80-rtm-media` extraction was removed
(247.84 MiB); the actual RTM compiler/header installation and its pinned
compiler hashes were preserved and checked before and after cleanup.
Do not treat an old ignored report as a current comparison. Use a fresh
focused build/comparison for any source change, and run affected accepted
units after shared contract changes. A reported aggregate exact percentage
requires a cold `python3 scripts/verify-exact-units.py --all` run.

Before committing any future source, ledger, script, test or generated-progress
change, run the mandatory local gate in the finished worktree:

```bash
python3 scripts/ci.py
git diff --check
```

CI is target-independent and may recreate disposable Python caches under
`build/`; remove them again if preparing a clean handoff. Inspect `git status`
before pushing. The user explicitly requests commit **and push** at stable
checkpoints; verify remote main equals the intended local commit after pushing.
