# DirectInput gamepad bootstrap and device enumeration

Complete current-target source is retained for initialization40D620 and device
callback40D9F0 in DirectInputGamepadBootstrap.cpp. Neither is exact. Their
ordinary unit is exact-first-directinput-gamepad-bootstrap:
- Initialization176/native176, first mismatch+2 at frame54h versus60h.
- Device callback327/native334, first mismatch at entry: native aligned EBP.

This extends the actual caller graph around the separately exact166-byte axis
callback. It adds no exact bytes and does not change its source or receipt.

## Observed behavior

Application startup407DA0 calls initialization at407EA0. Initialization calls
DirectInput EnumDevices(type4, callback40D9F0, context0, flags1). Failure shows
the observed DInput-Error message. Success truncates the checked device count
to an unsigned byte, publishes backend+120, zeroes a real80-byte gamepad state,
and assigns that many state-vector elements. A null DirectInput interface
returns success without enumeration, as in the target.

Device callback fails on a null interface. It pushes a null pointer slot,
passes its checked back element to CreateDevice with instance GUID+4, and
pops that slot if creation fails. The interface is evaluated after checked
argument preparation rather than cached across invalid-parameter callbacks.
For success it invokes SetDataFormat, SetCooperativeLevel(window,5),
GetCapabilities(size44), appends the button count, then EnumObjects with the
actual40DB40 axis callback, context0, flags3. These later HRESULTs are ignored.
No invented error handling, device release or count clamp is added.

The readonly format at6CCBEC has header24/object16/flags1/data80/count44 and
object-table pointer679520. It remains an external original SDK data object,
not synthesized provider code. Narrow pointer-only COM vtable/instance views
are never instantiated; actual callable slots are12/16 on the root interface,
and12/16/44/52 on the device. The range callback remains the existing real
InputManager.cpp implementation.

## Comparison and residual

Both target bodies are fully bounded through their real RET8/RET0 exits.
Whole native hashes:
-40D620:5bee847afc9938f25eda9a7863960f1ea0fc726088ff781a29a7cb4b61027aaa
-40D9F0:5045fa91a987a8ccc7b264779f51168094e2eea11749e0ca97444d46b08155f6

A genuine whole-program context with actual parent, callback, axis runtime,
checked vectors and static CRT links without unresolved functions. It recovers
aligned callback entry but emits573/native334 and182/native176 because it
inlines repeated checked back() operations and specializes helper arguments
differently. The earlier cached-interface control was574; the target-supported
late evaluation is selected. The axis callback retains166-byte length in this
image, but its independent public exact receipt is the accepted proof.

Native404400 pointer-vector push is also reached by real BGM/resource/UDP pool
callers, not solely this callback. Four later back() calls reach40DBF0, whereas
the linked local context tends to inline them. This identifies a genuine
shared-template/TU question, not permission to add noinline, register uses,
extra callers or fabricated public/private signatures.

New relocation rows are limited to the observed backend field addresses,
original readonly format/error strings and the two normal stdcall callback
addresses. The ordinary comparator retains complete byte/relocation checks;
callback address mapping does not award callback body equality. Existing
mappings are unchanged. Only the two new authored-source rules are replayed;
no unrelated exact or origin corpus is rebuilt.

Evidence: build/frontier-gamepad-enumeration-20261030/formal.json,
semantic.json, boundaries.json and the genuine linked private unit/logs.
Fresh Factory session/sample attestation is shared with the immediately
preceding axis scope. No hardware or user-system settings were accessed.
