# CSelect frame update 0x00421430

Complete697-byte native root is reconstructed as an unselected685-byte
candidate. First mismatch+337 is cdecl stack cleanup ordered before versus
after pointer publications. No exact/source-selection credit.
Receipt: build/frontier-421430-20261028/formal-build.json.
Raw recursive CFG closes all231 instructions through the final return,
including the early menu/exit EH epilogues: boundary.json.

The update first handles a changed UI selection and scene-mode2/3 return.
Either active player input's counter48 can open the real0x1C4 CMenuSelect after
event40; global menu input1 exits2. The main path reassigns input pointers
using signed second-side assignment7F8, first-side assignment7F9, mode3 and
rebind flag92. It preserves all native source=-1 cases, repeated input getter
calls, and the fallback that resets assignment7F9.

Both cursor pairs receive the corresponding nullable horizontal/vertical
counter pointers without resetting their selection values. The native input
deque is cleared, then each non-null input is copied to a real branch-local
value for push_back. The result comes from the scene's actual vslot18 dispatch.
The native helper420A80 is the same deque tidy body already used by accepted
replay/container callers;6183F0 pointer push_back was independently decoded
during entry recovery. Neither library helper earns new authored credit.

Current shared CSelect, CMenuSelect and cursor layouts are reused without
header changes. The real new-expression preserves allocation-null/EH behavior.
The canonical prologue uses existing folded handler6B976B; mapping this address
does not imply generated-auxiliary acceptance. No manual vtable loads, fake
stack cleanup, inert locals, padding or defensive guards were added.

Only this new unit was compiled. The unresolved cleanup / tail scheduling
is retained as a bounded compiler/TU question rather than coerced into place.
