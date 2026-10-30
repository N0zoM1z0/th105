# Application window-message source

Dispatcher408690 is now canonical exact240/240 in the real IME/window TU.
Callback6657E0 remains33/33, mode helper408780 remains126/126, and cursor40EBC0
remains157/157. This checkpoint adds240 authored exact bytes, bringing the
incremental total to1537 functions /435387 bytes.

## Actual callback and helper

WinMain's WNDCLASSEXA callback is the complete four-argument stdcall entry
6657E0. It forwards HWND/message/WPARAM/LPARAM plus the real application
singleton 702820 to dispatcher 408690 at 6657F9, returning its LRESULT with
RET16. The existing callback-address binding already contains these exact
33 target bytes; the source now reproduces them. No compiler-library credit
or invented caller is involved.

The dispatcher calls mode helper 408780 at 40871D for system-key Enter.
The ordinary file-local C++ helper and this real caller naturally produce its
EDI owner, one stack bool, AL result and RET4. It snapshots !windowed and
returns false unless its argument equals that snapshot. It manually holds
application critical section +94/native +98 around the already exact window
mode toggler, then releases it before cursor handling.

Flag +2C controls cursor updates. If the old mode was windowed and the new
mode is fullscreen, ShowCursor(0) is followed by false. The opposite successful
transition calls ShowCursor(1) and returns true. Otherwise the function returns
the old windowed state, including when cursor handling is disabled or a toggle
fails. This unusual native return policy is preserved, not normalized into an
invented success flag. Original source-level meaning of the option name is
not established by this reconstruction.

## Dispatcher source and IME boundary

The complete 240-byte native root is stdcall with five arguments. Option +2B
first permits the IME provider to consume a message. Otherwise it handles
WM_CREATE, WM_DESTROY, WM_QUIT, WM_SYSKEYDOWN/UP, WM_SYSCOMMAND and WM_IME_NOTIFY.
Destroy clears the singleton's running byte +4C and posts quit. Alt-Enter uses
the mode helper. Alt-F4 and unhandled messages go to DefWindowProcA. Exact
screensaver/monitor-power command values return one without masking WPARAM.

The provider at 40EDE0 consumes HWND in ESI as well as LPARAM in ECX,
WPARAM in EDX and message on the stack. Its WM_IME_SETCONTEXT tail at40F02E
pushes ESI into DefWindowProcA. This full-body observation corrects the earlier
three-argument fastcall inference, which missed the hidden window input.
Source now includes the complete four-input provider/cursor/composition graph.
The compiler derives its private ABI, but the616-byte root remains nonexact.
No ESI facade or false standard-ABI compatibility is claimed. See
PROFILE_IME_MESSAGE_SOURCE_2026_10_30.md for its source and switch proof.

The selected dispatcher preserves all native cases and external dependencies.
An explicit memset of the real20-byte ToAscii output buffer allows the compiler
to derive the observed private IME interface, including HWND in ESI. The final
remaining dispatcher difference was the system-command if/OR expression;
the native two-case switch produces its subtract sequence and complete240-byte
match. Neither parameter order nor calling convention was forced. The IME
body remains nonexact even though its caller is now exact.

Earlier242/246-byte dispatcher outputs and the singleton-member CIL control
are diagnostic history, not accepted alternatives. No padding or partial
function credit is used.

## Evidence and validation

Raw CFG audits close all three target bodies without unreachable bytes,
indirect jumps, missing tails or overlapping decode. Application option and
critical-section offsets have source size/offset assertions. USER32 imports
DefWindowProcA and PostQuitMessage are independently PE-attested; the singleton
view only binds base and running +4C. Existing backend field bindings and
accepted reset/toggle code are unchanged.

The sole changed source unit is exact-first-application-window-messages;
its six whole-function comparisons resolve all relocations, with four exact
and two explicitly nonexact IME bodies. New exact
functions use unchanged compiler flags. The dispatcher now uses the exact-origin baseline; its superseded explicit
authored rule was removed. Unaffected origin rules are retained. No full-corpus replay or new test infrastructure was added.

Evidence: build/frontier-application-window-20261030/boundaries.json and
formal.json; final checkpoint uses
build/frontier-profile-ime-zero-20261030/formal-window.json. Source controls
remain in the matching private .analysis folders.

`scripts/repo-python scripts/build.py --unit exact-first-application-window-messages --compare --json`
