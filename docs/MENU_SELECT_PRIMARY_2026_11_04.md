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
Only the native exception-handler prefix is pinned; full exception metadata
is not verified. No exact bytes are claimed.

The observer executes actual native and fully relocated source code for the
case-7 exit, button cancellation, menu-input cancellation and neutral path.
All four agree on return and mocked call traces, and redirecting case 7 to
the cancel-sound path is detected. Cursor, color, event and menu-input
providers are mocked. Other menu cases, allocation, exception handling and
full-game behavior are not covered. Run
`scripts/repo-python -m unittest discover -s tests -p
test_menu_select_cancel_observer.py`. Receipts are under
`build/frontier-menu-select-primary-20261104/`.
