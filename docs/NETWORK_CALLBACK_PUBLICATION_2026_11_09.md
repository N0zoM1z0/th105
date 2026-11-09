# Network callback publication and state queries

The constructors and destructors previously called a method named `cleanup`
through two undefined local classes. Their target is actually `0x413360`, the
existing `NetworkSendStateView::publish_callback` implementation. The complete
39-byte function enters the critical section at transport +0x88, stores its
argument at +0x80, leaves the same critical section and returns. It neither
removes a peer nor destroys a resource.

## Native call policy

Evidence comes from the hash-attested Japanese 1.06a PE
(`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`).
All four callers use the transport receiver at owner +0x3B4:

- Server constructor `0x43CB30`: call at `0x43CB84` publishes owner +0x6DC.
- Client constructor `0x43CCA0`: call at `0x43CCF4` publishes owner +0x6DC.
- Server destructor `0x43CC10`: call at `0x43CC58` publishes null.
- Client destructor `0x43CD40`: call at `0x43CD89` republishes owner +0x6DC.

The Client and Server destructor arguments genuinely differ. The source keeps
that distinction rather than imposing a uniform callback-clearing policy.
Why the Client lifetime uses this policy remains an ownership question.

## Source change

`NetworkSendState.hpp` now holds one shared declaration for callback
publication, indexed state checking and status reads. It replaces four
incompatible local definitions of `NetworkSendStateView` and the two cleanup
call aliases. The constructors and destructors embed this state prefix at
+0x3B4 and call the existing implementation directly.

The shared layout carries callback +0x80, critical sections +0x88/+0x124,
the existing vector at +0x108 and status +0x144. Compile-time assertions
check the offsets and the modeled 0x148-byte prefix. This is not a complete
transport-class definition. The UDP send view still describes another prefix,
and the peer-removal binding is now shared as described in
`docs/NETWORK_PEER_REMOVAL_BINDING_2026_11_09.md`.
The follow-up in `docs/DERIVED_UDP_CALLBACKS_2026_11_09.md` connects the complete
secondary interface and native override declarations. Concrete callback
implementations and the primary base still require owner-view unification.

## Focused comparison

Using the pinned VC8 SP1 O2 probe profile, all 19 whole-body comparisons retain
complete equality: 17 accepted authored roots and two compiler-generated
scalar wrappers excluded from authored totals. The affected units are:

- `gpt-web-network-derived-constructor`: constructors `0x43CB30/108` and
  `0x43CCA0/108`, factories `0x43CE00/113` and `0x43CE80/113`.
- `gpt-web-network-derived-lifetime`: Server normal/scalar destructors
  `0x43CC10/109`, `0x43CC80/30`; Client `0x43CD40/110`, `0x43CDB0/30`.
- `gpt-web-network-send-state-check`: publication `0x413360/39` and
  indexed check `0x413390/143`.
- `gpt-web-network-small-accessors`: status `0x415D50/7` and replay reset
  `0x428B70/8`.
- `gpt-web-network-client-primary-protocol`: `0x44E730/30`, `0x44E750/100`,
  `0x44E9E0/79`, `0x44EA80/79`.
- `gpt-web-network-server-primary-protocol`: `0x44F520/37`, `0x44F4E0/53`,
  `0x44F830/165`.

The four constructor/normal-destructor owners independently replay to the
same physical EH region: complete code35 at `0x6B8D10` and metadata44 at
`0x6DECFC`. Its unwind action tail-calls the base destructor at `0x43C950`.
Both factories replay complete code38 at `0x6B8D40` and metadata44 at
`0x6DED28`; the action calls operator delete at `0x6898EA`. Every relocation
is resolved, both action and handler bodies close, and each metadata record
has one unwind state with predecessor -1. Folded regions are counted once.

Across all six objects, 175 existing non-debug sections retain their bytes
and relocation roles after the two cleanup-symbol renames. The new vector
header dependency adds the ordinary `libcpmt` linker directive and the
`bad allocation` literal/pointer in the three previously STL-free translation
units. It adds no code section. This is a focused COFF comparison, not a
whole-application link.

No origin configuration consumes these six source files, so no source pins
were changed. Acceptance and exact ledgers are unchanged.

## Evidence and continuation

Focused before/after build reports, the section comparison and complete EH
replays are retained in `build/frontier-network-callback-publication-20261109/`.
The local replay uses the existing `audit-select-constructor.py` section
resolver; private scripts and the original worktree snapshot remain in
`.analysis/frontier-network-callback-publication-20261109/`.

The derived UDP callback follow-up resolves the six-slot declaration boundary;
joining the remaining primary and callback implementation views is still open.
