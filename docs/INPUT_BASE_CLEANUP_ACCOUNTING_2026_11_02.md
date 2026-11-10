# Input base cleanup: compiler-only accounting

The seven bytes at409D50 still match exactly. Their former authored credit is
withdrawn: the source destructor body is empty and the emitted operations are
only compiler-managed CInputManager virtual-table restoration and RET. Keeping
an empty destructor declaration is not seven bytes of reconstructed game logic.
The callable/source mapping and full canonical evidence remain available.

## Positive ownership proof

Native RTTI names the global CInputManager type. The retained source formerly
called it th105::CInputManagerLifetimeView. Renaming only this isolated source
owner to the actual global type leaves both complete normal7 and scalar31
bodies byte-identical after their ordinary named relocations. No field layout,
virtual slot order, compiler option or source statement was added to force code.

The fresh object reproduces seven RTTI records covering100 unique bytes:
actual TypeDescriptor28 at6FA43C, base descriptor28, base array4, hierarchy16,
COL20 and table-prefix4. The repeated TypeDescriptor record is not counted twice.
Both table slots at6C1674 are checked against scalar409D30 and update409DA0.
The original COFF table names weak vector-deleting symbol ??_E; its actual
auxiliary tag/search-characteristic resolves to the defined ??_G scalar body.
The weak relation is checked rather than replacing an unknown symbol by name.
The complete scalar31 remains independently qualified under its unchanged gate.

Actual static callback6BEFB0/10 loads receiver6FBD60 and tail-enters409D50.
This witnesses a cleanup edge, not the global object's dynamic type: the
registered initializer writes the CInputManagerEx vptr6C1154. The destructor
publishes its base CInputManager vptr6C1674. No exclusive base-versus-derived
original symbol spelling, linker ICF choice or new static callback credit is
claimed. Registration site6BEB4C is not a standalone22-byte initializer.

The source file is not a shared header and has one owning unit. Both formal
unit bodies and the scoped scalar-wrapper replay pass after the symbol update.
Ten tests and156 unique initialized-byte mutations cover the100 RTTI bytes,
eight vtable bytes, normal7, scalar31 and callback10. No generic proof threshold
or comparison rule changed, and no unrelated cold replay was performed.

Accounting: authored exact1431/443934 bytes, source-present1636, authored1655,
excluded2067, review305, mapped1821, units808. This is an accounting correction,
not a byte-match regression. The preceding receive-lock constructor still adds
its real25 authored bytes; the net authored gain since that earlier baseline is18.

The source hash and actual two-symbol contract are pinned by
config/input-base-cleanup-origin-anchors.toml.
