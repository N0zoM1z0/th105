# Input base cleanup: compiler-only accounting

The seven bytes at 409D50 still match exactly. Their former authored credit is
withdrawn: the source destructor body is empty and the emitted operations are
only compiler-managed CInputManager virtual-table restoration and RET. Keeping
an empty destructor declaration is not seven bytes of reconstructed game logic.
The callable/source mapping and full canonical evidence remain available.

## Positive ownership proof

Native RTTI names the global CInputManager type. The retained source formerly
called it th105::CInputManagerLifetimeView. Renaming only this isolated source
owner to the actual global type leaves both complete normal 7 and scalar 31
bodies byte-identical after their ordinary named relocations. No field layout,
virtual slot order, compiler option or source statement was added to force code.

The fresh object reproduces seven RTTI records covering 100 unique bytes:
actual TypeDescriptor28 at 6FA43C, base descriptor 28, base array 4, hierarchy 16,
COL 20 and table-prefix4. The repeated TypeDescriptor record is not counted twice.
Both table slots at 6C1674 are checked against scalar 409D30 and update 409DA0.
The original COFF table names weak vector-deleting symbol ??_E; its actual
auxiliary tag/search-characteristic resolves to the defined ??_G scalar body.
The weak relation is checked rather than replacing an unknown symbol by name.
The complete scalar 31 remains independently qualified under its unchanged gate.

Actual static callback 6BEFB0/10 loads receiver 6FBD60 and tail-enters409D50.
This witnesses a cleanup edge, not the global object's dynamic type: the
registered initializer writes the CInputManagerEx vptr 6C1154. The destructor
publishes its base CInputManager vptr 6C1674. No exclusive base-versus-derived
original symbol spelling, linker ICF choice or new static callback credit is
claimed. Registration site 6BEB4C is not a standalone 22-byte initializer.

The source file is not a shared header and has one owning unit. Both formal
unit bodies and the scoped scalar-wrapper replay pass after the symbol update.
Ten tests and 156 unique initialized-byte mutations cover the 100 RTTI bytes,
eight vtable bytes, normal 7, scalar 31 and callback 10. No generic proof threshold
or comparison rule changed, and no unrelated cold replay was performed.

Accounting: authored exact 1431/443934 bytes, source-present1636, authored 1655,
excluded 2067, review 305, mapped 1821, units 808. This is an accounting correction,
not a byte-match regression. The preceding receive-lock constructor still adds
its real 25 authored bytes; the net authored gain since that earlier baseline is 18.

The source hash and actual two-symbol contract are pinned by
config/input-base-cleanup-origin-anchors.toml.
