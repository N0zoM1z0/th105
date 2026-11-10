# CSelect prefix and seventh virtual role

The original table at6C0BC4 has seven slots, ending with selection flow4208E0
at6C0BDC. The constructor-facing CSelect previously declared only six scene
slots and frame update used a separate seven-slot dispatch surrogate. The
native frame invokes offset18 at4216CC. The independently exact341-byte flow
body establishes the existing selection policy at that destination.

Both constructor/destructor-facing declarations now include virtual
`update_selection`. The frame calls it through CSelect directly. No wrapper,
new helper body, forced inlining or manually loaded vtable is introduced.
The existing flow implementation still uses its separately verified view;
this scope does not claim a linked whole-class implementation or matching
namespace-qualified CSelect RTTI. Only actual virtual role/slot identity is
reconstructed here.

State08, setup pointer0C and the two input pointers10/14 now have explicit
members in both full layout declarations, replacing the unknown16-byte range.
Compile-time offsets check these fields. Entry/frame use the members directly
and delete their prefix surrogates. The setup pointer's field view remains
forward-declared and implemented in the entry TU; no stronger nominal setup
identity is inferred. Other state flags retain their original widths.

## Byte evidence

- Whole entry783 before/after unchanged:
  c5a5b8b1dc50bbd2e16c13d84f36263ed6bead06faa0536c0547a9fed2474ef3.
- Whole frame685 before/after unchanged:
  718a936b35f387880f875d139c2293cb95d8e06498a4a319645d06a4e6560f5d.
- Frame native697/source685 remains nonexact. First difference+337 is cdecl
  cleanup ordering; later native independent null-pointer branches become
  merged in the source, accounting for12 bytes. No shaping trial was made.
- Constructor4247/13 retains candidate76c04f84..., full remote EH461 and
  metadata188 remain exact. Existing implicit CSpriteEx16/array/RTTI gate
  freshly passes after its normalized owner-header pin is renewed.
- Destructor845, character binding258 and flow341 freshly exact. Render1497
  retains its prior candidate bytes; no new rendering exactness.
- Actual include closure6 units; both accepted authored consumers rebuilt,
  and all four nonexact consumers compared in full. Unaffected receipts were
  not globally rebuilt. The flow support unit was freshly compiled separately.
- `audit-select-owner-layout.py` checks source table32 bytes with COL prefix,
  all seven role relocations against native28 bytes, actual slot18 dispatch,
  and fresh whole consumer receipts. Four tests cover the missing seventh slot,
  wrong flow role and all28 single-byte native slot mutations.

No ledger, matches or count changes. Raw pinned target only, serial native jobs, no
IDA semantic reuse or push. This consolidation does not reopen the closed
frame/entry source-spelling or register-scheduling lanes.
