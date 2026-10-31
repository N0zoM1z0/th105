# Complete DirectInput shutdown policy, nonexact

DirectInput shutdown40D3F0 now has complete source and independently checked
authored ownership. Canonical original Japanese v1.06a executable SHA-256:
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.
The whole331-byte native body, through RET40D53A, has SHA-256
ef5bbfadd0d7b228892bf466d79becdf80dd00b82d25b7f820c4440c44c00f23.
Exact application shutdown407F80 calls it at40805B. Both the complete hash
and actual selected caller edge are replayed by the new authored-origin rule.

## Native policy and source

Release order is mouse, keyboard, indexed gamepads, three vector clears, then
the DirectInput interface. Each non-null device receives Unacquire at COM slot20,
then Release at08, then its stored pointer is zeroed. The interface receives
only Release. A COM call may affect state, so source retains the target's later
pointer reloads rather than caching a device across both calls.

The existing DirectInputBackend header supplies the actual vectors and their
observed offsets: devices10, raw states124, button counts134. Ordinary clear()
retains allocated capacity; original VC8 vector.clear() itself calls
 erase(begin(), end()). No manual STL teardown, allocation release or fabricated
vector wrapper is used. The target does not clear raw keyboard bytes, window
handle or gamepad_count; source does not add those resets.

A truthful narrow COM prefix uses normal virtual dispatch. Its uncalled
capabilities/object/property descriptors remain opaque; QueryInterface/AddRef/
Release and the five following device methods establish the actual Unacquire
slot without fake private registers or vptr writes. No interface instance is
constructed. Virtual dispatch evaluates each checked gamepad-vector receiver
once, avoiding duplicated operator[] evaluation from an explicit function-
pointer/argument facade.

## Comparison boundary

The public ordinary COFF unit emits581/native331, mismatch at5. A genuine
LTCG source control emits585 and inlines vector clearing that the target keeps
in separate complete helpers40DC40/58,40DC80/62 and40DD60/87. Including the real
existing gamepad enumeration/bootstrap users does not close this boundary and
also remains585. No private ESI/ECX declaration, noinline attribute, artificial
caller or manual clear-loop substitute is introduced. Original container/TU
context remains unresolved. Equal source semantics is not byte equality.

The temporary bootstrap aggregate is restored out of selected source. Its
Windows declaration conflict was resolved locally in the narrow COM prefix,
not by changing an old bootstrap/header. All prior accepted source and existing
data contracts remain unchanged. A new scoped zero-data alias covers only
shutdown fields and vector begin/end accesses established by the actual native
clear helpers; it does not broaden the old raw-key-state alias.

## Validation and accounting

Public unit: exact-first-directinput-shutdown.
Focused report: build/frontier-direct-input-shutdown-20261031/formal.json,
intentionally comparison_failed/mismatch. Private linked controls are in the
same directory. Only the new ownership rule is materialized after focused
body/caller validation; existing census evidence is retained.
Default CI210 and whitespace checks pass. No cold whole-corpus replay.

Source1773, authored1793, mapped1800, excluded1658, review576, units758.
Exact authored stays1576 /448613 bytes. No library helpers or partial native
prefix bytes receive credit.
