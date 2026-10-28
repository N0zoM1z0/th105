# Combo resource load 0x0046A8C0

Fresh independent recovery retains the complete413-byte native body as a
427-byte unselected candidate. First mismatch+2 is the extra saved EBP.
No exact/source-selection credit is added.

The native root virtually loads data/battle/combo.dat, looks up ids1000..1003,
releases each old number adapter, allocates an8-byte typed adapter and enables
the corresponding object. Bindings are int5C, float64, int68, int60 in that
order. It then looks up ids2103/2104/2105/2100/2101/2102 into the six slots44..58.
All allocation-null paths and scalar delete/new order are preserved.

The public candidate uses the shared CDesignBase and CNumber types, an
observed UI-header18/embedded-number view, and owner fields from the exact
combo renderer. The full native extent ends at46AA5D exclusive. Nominal
original owner names and return-value semantics remain unresolved; the local
candidate does not manufacture a return value or change existing caller ABIs.

The static-type evidence that closed story binding was independently tested
here rather than assumed transferable. An outer-UI adapter-field view, direct
post-release allocation, and a typed lookup output did not remove the
extra adapter-slot address lifetime. Native keeps the found UI owner in EDI
and accesses +3C; the candidate keeps both the owner and its adapter-slot
address across calls. The simpler shared CNumber candidate is retained.
No volatile, fake storage, register forcing or manual instruction reproduction.

Receipts: build/frontier-46a8c0-20261028/typed-owner.json (retained source),
ui-owner-binding.json, post-release-address.json, typed-output.json.
The added path literal is independently pinned to6C35E0 including NUL.
Only the new unit was compiled; no shared header, existing binding or caller
source changed.
