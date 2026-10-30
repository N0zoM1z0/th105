# Complete DirectInput mouse bootstrap source

Mouse initialization40D810 now has complete current-target source, including
the previously omitted SetProperty failure notification. Genuine CIL emits296
bytes versus native282; no new exact credit. Existing1544 functions /437755
exact bytes are preserved. All five affected platform/input exact roots pass.

## Native observations

Application startup407DA0 directly calls this root at407EAD. The complete
282-byte callable ends with RET0 at40D929; all code is reachable. Fresh
Factory-native inventory/disassembly/decompiler/callers/callees and pinned raw
PE establish the scope. Prior same-session metadata and five mapped-byte
samples agree with the original Japanese1.06a target.

An existing mouse pointer immediately succeeds. Otherwise CreateDevice receives
the system-mouse GUID and the actual global device cell, followed by the native
mouse format descriptor, SetCooperativeLevel(window,6), and a five-DWORD
DIPROPDWORD-compatible property {20,16,0,0,1} passed under property ID2.
Each failing HRESULT returns false; successful Acquire is invoked but its
HRESULT is ignored. No missing-interface guard or defensive retry is added.

CreateDevice, format and cooperative failures use their existing native
MessageBox strings. The fourth failure passes the complete CP932 property
message at6D6BC8 through40D540 at40D90C. That22-byte helper receives its string
through linker-private EAX and forwards the actual window, title and zero type
to MessageBoxA. Caller discards the dialog result. Earlier retained mouse source
silently returned false here; the notification is now restored.

## Source and code-generation limits

DirectInputDeviceViews.hpp shares the existing pointer-only COM slot and GUID
declarations. DirectInputMouseBootstrap.cpp contains the full mouse body plus
an ordinary C++ report_direct_input_error(const char*) implementation.
SystemUtilities.cpp includes it so prior source consumers retain availability.
No shared object layout, virtual ordering or keyboard semantics changed.

The real CIL build naturally inlines the normal error helper. Consequently the
last error path is14 bytes longer than the native private call boundary.
The first canonical mismatch is the entry jump displacement at+12, not a
missing relocation. Every call/data reference resolves; the whole296-byte
candidate is compared. Equal earlier regions are not partial exact credit.
The helper itself receives no exact or library-origin credit. No custom EAX
prototype, noinline attribute, fake caller or copied machine code is used.

Unit exact-first-directinput-mouse-bootstrap is reproducible and intentionally
nonexact. An earlier private combined keyboard/mouse CIL also produced296,
while the existing keyboard root independently remained exact188.

## Checks

scripts/repo-python scripts/build.py --unit exact-first-directinput-mouse-bootstrap --compare --json
scripts/repo-python scripts/build.py --unit cross-v106a-system-utilities --compare --json

The first command reports the known mismatch. The second retains all five
accepted168/97/34/138/188-byte roots. Actual quoted-include dependency inspection
finds only these two affected units. Other exact receipts are preserved.
Raw closure, semantic evidence and focused reports are under
build/frontier-mouse-init-cil-20261030. No application or hardware input was run.
