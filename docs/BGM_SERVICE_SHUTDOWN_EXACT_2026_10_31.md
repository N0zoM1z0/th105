# BGM shutdown through the real service context

Original Japanese TH105 v1.06a SHA-256:
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.

BgmService shutdown4034F0 is now canonical exact449/449, SHA-256
9ba5a1e02fb81ffaf9c0d5b6844e04c8b4d39af9994eafebe19830d60a2f3fef.
All bytes of the complete callable, including its aligned frame, three list
release traversals and subsequent clears, agree. No padding, fake alignment,
forced register ABI or machine-code substitution is used.

## Source and resolved context

The actual BgmServiceLifetime class already owns two thread handles, events,
manager and three BgmHandleResult queues. Its shutdown now implements the
same previously reconstructed policy in this genuine complete source context:
clear running, signal the loading event if present, join both threads, close
and clear both events, release every handle in all three queues, then clear
all three containers. It adds no service lock or defensive policy.

The old BgmServiceShutdown.cpp selected an opaque manager with only a normal
member declaration and unsigned physical queue views. Its449-byte output was
nonexact at the frame and manager-call boundaries. The actual visible manager
implementation and allocated-token queues now allow ordinary VC8 LTCG to choose
the target aligned frame and private EAX manager-release receiver naturally.
Its source declaration remains a normal C++ member. Existing explicit public
thread method preservation continues to use the independently established
normal ECX wait_for_exit414640; no fabricated adapter is added.

The manager release implementation itself is257/native184 in this context.
It receives no exact credit. Its actual named direct call binding establishes
the caller's callee identity, not whole-callee equality. This is the ordinary
strict canonical caller contract, with all449 caller bytes still compared.

## Public reproduction and accounting

The public exact-first-bgm-service-lifetime unit now selects shutdown alongside
the three lifetimes. All four freshly pass: service199/148 and manager133,
with every previous global startup and cleanup/EH proof intact. The old
standalone shutdown probe unit is removed; its historical source is retained
but no longer selected. Its source-only ownership rule is superseded by the
whole canonical match. No other source consumer or shared header changes.

scripts/repo-python scripts/build.py --unit exact-first-bgm-service-lifetime --compare --json

Focused reports: build/frontier-bgm-shutdown-context-20261031/.
Default CI210 and whitespace checks pass. One previously source-present
function adds449 authored bytes:1573 exact /447961 bytes. Source1768,
authored1788, mapped1795, excluded1658/review581 remain unchanged; units754.
No whole-corpus cold replay or independent manager-release acceptance is claimed.

## Bounded allocation/provider follow-up

A subsequent private control added the already-known actual value-returning
allocate_handle policy to this real service class. The caller stayed26/native28,
acquire547/native401 and release257/native184. Preserving the independently
observed ordinary public lookup entry exposed its genuine provider and made
vector::at outline naturally: lookup195/native196, acquire485/native401,
release183/native184 and vector::at88/native95. This is not equality.

The outlined source vector::at naturally consumes its index in EBX, while
native417A90 receives it from the stack. That difference shifts release's
register allocation and removes its index push. No private ABI declaration,
forced spill, dummy caller or additional spelling grid was used. All four
accepted service roots stayed exact in both private controls. The unsuccessful
allocation additions were restored out of selected source; public manifests,
receipts and counts remain unchanged. The existing incomplete allocation and
provider units are not replaced by these probes. Evidence is retained in
build/frontier-bgm-allocation-context-20261031/.
