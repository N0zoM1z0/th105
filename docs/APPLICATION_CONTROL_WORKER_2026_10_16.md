# Application control worker: complete source, nonexact 787/771

## Observed target and complete boundary

Only original Japanese TH10.5 v1.06a was used, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Exact native callback `408800` calls this no-argument worker at `40880C`.
`Application_control_worker @ 4081E0` establishes singleton `702820` itself.
Its complete physical callable ends at RET `4084E2`, before INT3 padding.
Whole-body SHA-256:
`2605408e36e40aead462ff799627921a8943b3c1f68bfd59dbcc35e695e35010`.

Normal CFG closure reaches755 bytes / 240 instructions. The remaining16 bytes
at `[408495,4084A5)` are an int-catch funclet, selected through GS/EH handler
`6BE3E0`, FuncInfo `6E4C24`, try block `6E4C10` and catch descriptor `6E4C00`.
The descriptor names int type `6FA40C` / `.H`, with no named catch object.
Two unwind states have null actions. The catch clears running+4C and returns
continuation `4084A5`, which resets floating control and removes the listener.
Together these close **771 bytes / 244 instructions**. Ghidra's first
decompilation omits the catch and remains a private hypothesis.

The combined88-byte EH tables `[6E4BF0,6E4C48)` have SHA-256
`4ca138700af3cb1d0d3302c639bc8fb62c3cb851dcd73861b749ee8fba4c358b`.
The complete40-byte GS/EH handler has SHA-256
`b0db13c05a84f6f69d6081b83c14fa697d280eef529a6c81d6754ae051e0f4c0`.
It checks two frame cookies and tail-enters CxxFrameHandler3 `6899E7`.

## Behavior and source selection

The worker obtains an audio-scheduler listener event, queries floating control,
then selects upward rounding. The actual calls are:

```cpp
_controlfp_s(&fp_state, 0, 0);
_controlfp_s(&fp_state, _RC_UP, _MCW_RC); // 0x200, 0x300
// control loop and catch(int)
_controlfp_s(&fp_state, _CW_DEFAULT, 0xffffffffu); // 0x9001f
```

The pinned VC8 float.h and raw three-argument CRT wrapper independently support
the signature and constants. `200/300` controls rounding; VC8 precision control
uses `20000/30000`. Exit selects the default word rather than restoring the
initially queried value. This is a current-thread runtime policy, not evidence
for a global compiler flag or every thread's environment.

While running+4C, the worker publishes three per-second counters and advances
timestamp+38 by1000 when unsigned elapsed time reaches1000. Option byte+2E
enables a title update using the exact `%s    Game:%dFPS    Draw:%d+%dFPS`
format and empty prefix. The three live counters are cleared in the observed
+34/+44/+48 order. A real260-byte title buffer follows the target's addressed
title-to-cookie span; the API passes no capacity, so original source capacity
is not uniquely proved. No capacity variants or inflated buffer were used.

The input option gates exact gamepad polling `40D6D0`, keyboard GetDeviceState
for256 bytes, and mouse GetDeviceState for20 bytes. A keyboard failure reacquires
the device and clears its state; a mouse failure only reacquires. Narrow COM
views preserve Acquire+1C and GetDeviceState+24, including global reloads.
Existing native input layout is reused without changing its header.

The manager updates every tick. When requested state+B0 equals active state+B4,
fade and the previous scene update; scene result -1 clears running but still
reaches frame pacing. A changed scene state joins the creation-thread owner+64
and starts native callback `408840`. Otherwise, an absent or ready fade permits
pending-scene commit `408080`. That helper independently uses singleton globals;
no private register receiver is fabricated for the source declaration.

With sync option+2D false, pending presentation byte `6FA246` selects either
signaling graphics event+60 or rendering a new request. The latter explicitly
clears the byte under backend locking, combines scene/manager/fade render
results with bitwise AND, then publishes a successful request under the same
lock. Successful immediate `401060` presentation increments render count+44
and follows the fast listener-wait/continue path. Failed presentation signals
the graphics event. Every completed iteration reaches scheduler pacing.
Normal and caught-int exits reset floating control and remove the listener.
The three scheduler helpers already have complete source but remain nonexact;
this worker does not promote them.

`src/platform/ApplicationControlWorker.cpp` contains the entire ordinary C++
loop, real API outputs, typed callbacks, manual lock ownership and int catch.
The accessed application prefix has compile-time offset checks. Existing
shared headers, flags and relocation permissions are unchanged. A dedicated
input alias allows only the keyboard/mouse pointer and keyboard-buffer addends;
other new mappings attest the singleton, title literals, mouse output,
creation callback, full GS/EH handler and SetWindowTextA IAT slot.

## Focused result and remaining unknowns

```bash
python3 scripts/audit-candidate-boundaries.py 0x004081E0 --json
python3 scripts/build.py --unit cross-v106a-application-control-worker --compare --json
```

Reports are `build/application-control-worker-boundary.json` and
`build/application-control-worker-formal.json`. The boundary report exposes
the EH-only interval; the tables above reconcile it. The complete COFF tail
is787 bytes versus target771, nonexact at **+1**. The candidate uses a biased
EBP frame, combines the first two cdecl argument cleanups, emits three pacing
tails versus two, and clears EH state explicitly before post-try cleanup.
All target-range relocations are resolved; the overlong candidate is never an
accepted boundary or executable replacement.

A local frame-pointer-retention control produces803 bytes and restores the
target's ordinary EBP base, but still reserves280 bytes versus target284 and
retains other differences. It is not selected. No padding or buffer increase
addresses that four-byte residual. Post-try state writes may depend on original
callee visibility or exception contracts; no unproved nothrow annotation or
C-linkage substitution is added to erase them. Original TU, frame and exception
optimization remain unknown. No match row or exact bytes are added.

An independent authored-origin rule checks the exact callback edge, exact
input/thread-wait/presentation calls, existing scheduler source, complete body,
FP constants, key input/title/callback operands and the entire EH table shape.
Only this origin row changes after checking unchanged older rules for overlap;
unrelated library fingerprints are preserved without a full regeneration.
Direct Ghidra save/readback sessions attest executable/program SHA, image/entry,
x86 Windows identity, every mapped .text byte and EH/type data hashes before
verifying the771-byte cdecl/void no-argument contract, purge0 and catch label.
Private scripts are under
`.analysis/application-control-worker-20261016/ghidra-scripts/`; logs stay under
`build/application-control-worker-ghidra-*.log`. Each process uses768MiB and two
active processors. The mismatched IDA session is excluded from analysis.
