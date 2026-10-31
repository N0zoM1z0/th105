# BGM token queues and manager construction

Original Japanese TH105 v1.06a SHA-256:
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.

BgmAllocationManager constructor403ED0 is canonical exact133/133, SHA-256
30660ad1adaf6edbf85a4b57c976b6a726fcc26630996fda3b51dee1b7f0c7e8.
All101 cleanup/EH bytes also pass: handler27, two11-byte vector cleanup
funclets, FuncInfo36 and unwind map16. Handler6BE496 selects info6E4CC8.
The actual compiler-generated entry takes its receiver on the stack and
returns with RET4; source remains an ordinary default C++ constructor.

## Evidence-driven type distinction

The service allocates and returns a real BgmHandleResult value, initialized to
zero and filled with separate slot/generation words. The complete native
allocation contract was established earlier; see BGM_ALLOCATION_CONTRACT_2026_10_29.md.
The worker queues88/94/A0 contain allocated handles for manager lookup/release,
whereas the manager's free_24 list contains unallocated slot indices. Thus the
outer queues now use the existing real four-byte BgmHandleResult class, while
the free list retains unsigned indices. No dummy class, inert fields, private
calling-convention annotation or copied instructions are introduced.

The distinction is semantically supported by these uses, but does not prove
the exact original nominal C++ spelling. Older worker views use the same
four-byte physical representation; their source and behavior are unchanged.

Genuine original VC8 unsigned-list/vector COFF now coexists with the token
list's ordinary CIL. The manager's free-list constructor retains its normal
ECX node-allocation call, while outer token node allocation needs no receiver
and token cleanup naturally uses ESI. The previous all-unsigned CIL model
matched the outer lifetimes but left this constructor126/native133; the
all-unsigned COFF control matched its size but broke both outer lifetimes.
The single real value-type distinction resolves all three together.

## Whole caller and global proof

The public exact-first-bgm-service-lifetime unit freshly passes all three
bodies: global constructor199, global destructor148 and member constructor133.
The actual direct call40334B in4032F0 is the member's sole witnessed entry.
Before accepting it, the existing strict global-parent mechanism replays the
whole199-byte parent, all180 parent EH bytes and the same current B4-byte
storage7026E0, initializer17, actual CRT table slot and exit callback5.
The receipt retains that evidence, rather than relying on a historical match.
The global destructor and all117 EH bytes also remain exact. Typed vtable
and RTTI checks identify CHandleManagerEx<BgmBuffer>; no verifier change is
needed in this follow-up.

Only BgmServiceLifetime.cpp and its public unit change source/compilation
context. Other source consumers remain untouched. The previous checkpoint's
BGM, wave and package regressions remain recorded; this follow-up reruns the
three directly affected roots and default CI, not a cold whole-repository scan.

One authored function adds133 bytes:1572 exact /447512 bytes;
source1768, authored1788, mapped1795, excluded1658, review581, units755.
Full receipts: build/frontier-bgm-token-lifetime-20261031/.
