# Reject numbered linker diagnostics and retain native destructor entry proof

The linked build guard previously searched for a word boundary immediately
after `LNK`. It therefore missed actual numbered diagnostics such as LNK4210
when link.exe returned zero. The Gage size-profile experiment exposed this:
`msvcrt.lib(cpu_disp.obj)` warned of possibly unhandled CRT initialization in
the NOENTRY comparison image. That trial is rejected, not accepted as a clean
linked candidate. No new game function or authored byte is credited.

`scripts/linked_pe.py` now checks each completed phase through
`check_build_phase`. Nonzero status, fatal errors, and numbered linker errors
or warnings independently fail the build before successful provenance is
published. A real rebuild of the failing size experiment now rejects LNK4210
and leaves no success sidecar. Regression tests include its actual zero-exit
warning, LNK2001, LNK4098, a fatal compile error, nonzero status and clean output.

## Packet-pool export correction

Inspection of the six accepted linked units' preceding logs found one other
numbered warning: packet-pool LNK4102, caused by explicitly exporting its
compiler-generated scalar deleting destructor. Its actual vtable already
provides a stronger ownership witness. The function retains its configured
comparison and gains:

```toml
vtable_entry = "??_7NetworkUdpPacketHandleManager64@th105@@6B@"
```

This selector requires the exact existing `link_vtables` destructor contract,
including the function symbol and target address. It excludes simultaneous
export/private/global witnesses and cannot serve as an exported private
function's caller. At comparison time the source function must still have a
unique CIL-owned scalar symbol, and the actual read-only native vtable entry
must point to it. Existing source/target RTTI, COL, executable-entry and
single-destructor-slot validation remains mandatory. The only permitted code
alias is VC8's matching scalar/vector deleting wrapper for that same class;
unrelated, duplicate or foreign-object aliases fail. A vtable-only unit still
needs an actual exported source root or the existing CRT global-lifecycle proof.
This adds no general vtable, literal, arbitrary internal address or private-ABI
allowance.

The corrected packet image exports only the real constructor and normal
destructor. Its link log has no warning. Normal destructor 413820 remains
**98/98 exact**, and vtable-selected scalar wrapper 4138B0 remains **30/30**,
canonical SHA256
`58e4f9f275e78197e7a9bc8fead74f8f3b33a2a4198562c0b6c5e73715b46782`.
The wrapper's existing compiler exclusion is unchanged; it adds no authored
source, match row or byte credit. Game sources and shared layouts are unchanged.

## Focused replay

All **13 accepted functions in the six affected linked units** were rebuilt
under the corrected guard and remain exact. No unrelated COFF unit or cold
aggregate replay is claimed. The independently compared 30-byte compiler
wrapper is additional exclusion evidence, not a fourteenth authored result.

IDA rejects the wrong open image; new target facts use only the hash-attested
original Japanese 1.06a PE. Builds are serial on CPU 0 at nice 10.

## Associated large-function diagnostics

The fresh Reimu 496540 baseline remains nonexact 49655F/+31. That first unequal
field is the default-branch displacement; the preceding 31 bytes agree.
Three genuine 908 accumulator/conversion controls (float accumulator, double
accumulator, separated float conversion) all reproduce the complete 45700-byte
canonical source section
`d0ff3d3259c823cc56e322c5e0ec238456d8b490c78b4a5336a249b45a405a58`.
Same-TU4963A0 remains 66/66 in every build. The selected CPP 3b9e4896/header6f469e68
are unchanged; no unnecessary native fixture replay is reported.

Raw target 4A076A first loads float state 374, sign-extends word 366, homes that
integer at ESP+20, then FILD m32/FADDP/stores state 374. Source 809E97 instead
converts the counter first and adds the memory float. These new controls do not fix
the form. The continuation after the opaque wave remains unexecuted; no callback
return or new whole-root behavior is fabricated.

An explicit `/fp:strict` CIL experiment also rechecks Gage 41B3F0 using all real
renderer/binder/lookup/angle definitions. Its 1012-byte/328-instruction raw root is
byte-identical to the preceding pragma-controlled CIL root. Changing both the angle
declarations and their genuine definitions to float return leaves the diagnostic
body identical after checked call/literal replay. Neither variant is a configured
canonical unit: native literal qualification remains unsupported and the aligned EBP
frame still differs at+0. The size variant is 1079 bytes and triggers the
now-rejected LNK4210. Its generated code and prior diagnostic records remain failure
evidence, never new exact credit. No public compiler profile changes.
