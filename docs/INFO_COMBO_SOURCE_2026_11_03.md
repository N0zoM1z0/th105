# Combo resource loader source, 2026-11-03

The existing combo resource loader source is now tracked individually. Native `0x46A8C0` has a 413-byte callable body, SHA-256 `396333d39a6ed32d902c670f80a884eacb5eb714a347451d93576e0201c61f48`, 141 decoded instructions and one return. The exact normal InfoManager initializer calls it at `0x46EBB0`; all four accepted functions in that caller unit freshly replayed.

The source loads the combo design, binds four number adapters to the observed integer and float fields, enables their objects and looks up six additional objects in native order. `INFO_COMBO_LOAD_2026_10_28.md` records field, allocation and owner evidence. Source-view names and the native return convention's original nominal meaning remain unknown.

The existing public probe emits 427 bytes against native 413 and first differs at
offset 2. It is source-present and nonexact, with no partial or exact-byte credit.
