# Profile IME message and cursor source

move_profile_input_cursor at 40EBC0 is canonical exact 157/157 bytes in its
real message/window caller TU. Its EAX direction parameter is compiler-derived
from an ordinary file-local stdcall source function. No external EAX declaration
or copied assembly is used. Incremental progress is 1536 exact functions /
435147 bytes. Composition 40E8B0 and message processing 40EDE0 receive no exact
credit.

## Source completion

ProfileImeRuntime.cpp includes the existing profile text runtime and defines
three previously missing bodies. The application window source includes this
real graph, replacing the unresolved four-argument IME declaration. Native
HWND in ESI is now supplied semantically by the actual window caller; the
compiler is free to derive its private register/stack interface. Current
source still selects a different interface, so the message root and window
dispatcher remain nonexact.

Cursor movement preserves the native asymmetric policy. Negative direction
uses a two-byte lookbehind to select one or two bytes, with cursor below two
reset to zero. Positive direction first checks the current character, changes
cursor at least 1022 to 1023, advances by the observed Shift-JIS lead-byte
ranges and clamps to the configured maximum. Direction zero does nothing.
This is not replaced by a modern Unicode or symmetric-bound implementation.
The additional +6 global address is an independently attested lookbehind base,
not permission to access an arbitrary range in existing units.

Composition retrieves result text through the native ImmGetCompositionStringA
entry and preserves its unchecked returned length. It saves a real 1024-byte
suffix, inserts composition and suffix with the original signed remaining-space
choices, advances or rolls back cursor by the result length, preserves the
native lead-byte truncation policy, clears the 256-byte composition buffer and
sets the primary-pending flag. Ordinary source is 375/native383: the first295
bytes agree, but the compiler merges the final truncation stores. No prefix
credit is awarded. A natural shared trim helper and genuine CIL control retain
this same residual; no inert locals or forced branches were introduced.

## Complete native message policy

40EDE0 owns 616 callable bytes / 169 instructions. Two switch destination/index
pairs account for another 99 bytes through 40F0AA; these metadata bytes are not
authored credit. The target-pinned switch proof checks all destination boundaries
and reaches every callable instruction, including the HWND-consuming tail.

When mode is active, the handler covers composition messages, character/key
input, IME context and notifications. Character input swallows Backspace/Tab,
requests reset on Enter while returning false, disables mode on Escape, and
passes other low character bytes to the existing insert implementation. Key
input handles Enter, left/right, Backspace and Delete using the real cursor
and delete bodies. Other keys call ToAscii with arithmetic-shifted scan code,
null keyboard state, flags1 and the actual 20-byte zeroed output buffer.

The context branch masks LPARAM with 3FFFFFF0 and forwards HWND, message281,
WPARAM and masked LPARAM to DefWindowProcA. The complete native body therefore
requires HWND in addition to the three values obvious at its entry. Source
retains this input instead of an incorrect three-argument fastcall facade.
Notifications1 through5 return true; the original inactive/default/other
return policies are unchanged.

The ordinary source envelope is731 bytes versus native715, including both
switch pairs. Its callable/register allocation and switch layout are nonexact.
The ordinary registered comparison covers the native616-byte callable and is
already nonexact; the separate target switch proof does not claim source table
equality. A genuine resolved CIL control with actual SDK Imm32.Lib and the real
D3D reset/toggle source preserves the same residual. No synthetic import stub
or substituted function body is used.

## Validation and reproduction

The expanded actual window TU preserves its accepted126-byte mode helper and
33-byte WNDPROC. Its dispatcher is242/native240. The three new whole-body
comparisons resolve all relocations; only the157-byte cursor passes. The prior
profile runtime source/unit is unchanged. Origin validation is limited to the
two newly authored rules, the changed dispatcher evidence and the new exact
cursor baseline; all other origin evidence is retained.

Private evidence: build/frontier-profile-ime-20261030/formal.json,
target-switch-proof.json, linked.log and matching .analysis controls.

`scripts/repo-python scripts/build.py --unit exact-first-application-window-messages --compare --json`
