# D3D reset-listener registration414CB0

Complete157/157 canonical exact, SHA-256
31d2b2725c61f8cf6902a1d6dab316b028eb5887437fdf72786d3476249cc8ce.
The existing exact-first-battle-base-effect-initialize-linked unit now selects
this private function with the actual initializer417FF0 call at418006 as its
private_from witness. Both complete functions are compared; initializer71/71
retains its previous hash. No synthetic caller or ABI declaration is used.

## Independent source evidence

Native414CB0 locks backend critical section+4, walks the listener list at+1AC,
and uses an unchecked node search until equal or end. Only after the search
come the checked-iterator container/result comparisons. It appends the pointer
when absent and performs one common unlock. All60 decoded instructions and
157 bytes are reachable through the closed CFG; RET4 ends at414D4C, followed
by three INT3 bytes.

The prior manual iterator loop inserted checks at every dereference/increment
and duplicated the unlock/return path. In the genuine linked context it was
162/native157. Standard std::find uses VC8's actual unchecked search internals,
then returns a checked iterator. Comparing the temporary directly against end
compiled156/157 with a20-byte frame and premature end materialization. Naming
the actual search result before comparing against end naturally gives the
native12-byte frame, end reload, full control flow and register allocation.
This is an ordinary live iterator value, not inert scratch or stack padding.

The unchanged ordinary member declaration naturally acquires the private EAX
backend receiver in the actual initializer/listener/critical-section CIL.
The public root is still ordinary thiscall. The existing private-caller proof
validates the complete source and target caller CFG and unique E8 edge; the
helper is neither exported nor aliased. Its two invalid-parameter calls and
real list _Buynode/_Incsize references are resolved without masking bytes.
The shared list providers receive no additional credit.

## Selected changes and validation

D3DBackendListenerRuntime.cpp now uses standard find, named result, conditional
push_back and one unlock. The old standalone probe unit is replaced by the
private selection in the existing linked unit. Both ledger source_file entries
point to that real linked wrapper, whose transitive inputs contain the method
bodies. No class layout/header or lifetime code changes in this checkpoint.

Fresh formal-build.json reports exact71/71 and157/157 with the actual private
caller witness. boundary.json records the independent native decode. Receipts
and negative temporary-expression trial are under
build/frontier-d3d-listener-find-20261029/; private replay sources are under the
corresponding .analysis directory. Default CI and diff checks complete the
local gate. Exact total increases by157 only; no cold corpus rebuild.
