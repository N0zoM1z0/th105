# Menu selection primary update

`0x00447D20` is the game-owned 669-byte primary selection body reached by
the exact `CMenuSelect::update` tail jump. Its full callable SHA-256 is
`1235b1756799370d4216478c8f698fa93cebcc4f382e2fcdca1be635ec44e89b`.
Eight target switch destinations at `0x00447FC0` are pinned separately. The
callable is followed by three alignment bytes and the 32-byte switch table;
the full 704-byte payload SHA-256 is
`734fdf7846611548e8cbe17846298fb1190dcfeee014c6aae36e14c980eb268e`.

The recovered source uses the real, size-checked `CProfileCharacterSelect`
and `CProfileKeyConfig` classes whose constructors the native body calls,
instead of old placeholder class definitions. It also uses the actual C++ UI
menu-install interface. Target switch case 7 jumps directly to the false
return at `0x00447FA7`, skipping the cancel sound at `0x00447F9D`; the previous
source incorrectly played that sound. The separate cancel-button paths do play
it. Source now reflects that distinction without gotos.

A pinned VC8 `/GS` build emits a 680-byte COFF section containing its own
switch data, SHA-256
`e34ac53616d075aa906247e216098bdecbed6f9ad8b8e5bb7d6fb6788b78d7a7`.
The native callable and source section lengths are not comparable directly;
the full native payload is 704 bytes. Formal comparison fails from +111 on a
branch displacement, and the target and source switch placement differs.
The complete remote exception handler and metadata have since been independently
replayed as described below. No root exact bytes are claimed.

The observer executes actual native and fully relocated source code for the
case-7 exit, button cancellation, menu-input cancellation and neutral path.
All four agree on return and mocked call traces, and redirecting case 7 to
the cancel-sound path is detected. Cursor, color, event and menu-input
providers are mocked. A second matrix covers all eight selections and both
network-mode branches against an independent expected call/state model.
Allocation, player lookup, submenu constructors and installation are mocked.
For selections 2–5, both images also follow the modeled null-allocation
branch and install a null pointer without constructing a submenu. Real
allocation and exception handling and full-game behavior are not covered. Run
`scripts/repo-python -m unittest discover -s tests -p
test_menu_select_cancel_observer.py`. Receipts are under
`build/frontier-menu-select-primary-20261104/`.

An unmasked whole-payload census compares the complete native callable,
alignment and eight-entry switch table to the entire emitted source section.
The target table begins at +672 and the source table at +648. The positional
comparison has 555 unequal positions including 24 missing source bytes; these
are not 555 independent semantic defects because shifted code moves later
bytes. The census does not cover remote exception code or metadata and is not
an acceptance mechanism. Reproduce with `scripts/repo-python
scripts/audit-menu-select-primary-payload.py`; the receipt is `payload.json` in
the same build directory.
The same mocked comparison also checks out-of-range selection values -1, 8
and `INT_MAX` with confirmation pressed; both return true after the event. These are
bounded malformed-state observations, not a general input-safety claim.


## Remote exception code and metadata

The complete 82-byte remote exception section at `0x006B9C40` and 76-byte
FuncInfo/unwind map at `0x006DF910` replay byte-for-byte against the genuine
emitted source after only named relocations are resolved. Five unwind states
all perform the actual delete cleanup. Whole code and metadata hashes, source
provenance and relocation roles are pinned in
`scripts/audit-menu-select-primary-eh.py`; tests mutate each metadata byte.
This is static EH code/metadata equality, not OS exception execution. The
menu root still differs and earns no exact-byte credit.
