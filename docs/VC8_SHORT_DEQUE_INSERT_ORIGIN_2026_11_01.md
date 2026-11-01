# Original VC8 short-deque count insertion

The existing untouched scripts/probes/deque_short.cpp explicitly instantiates
std::deque<short> from the pinned original VC8 standard library. Fresh ordinary
compilation emits the complete1404-byte _Insert_n member matching4638C0 by the
existing strict relocation-aware compiler-origin fingerprint. The full4027-row
inventory has exactly one qualifying occurrence. No game transcription, copied
instructions, source ABI annotation, profile change or alignment tolerance is used.

Native whole-body SHA256:
d79e2baf0eb343544e0ed2bd7d6f2ef18cd20085623df4606805890367dac8c0.
All1404 source/target bytes participate. Forty-six genuine COFF relocation fields
cover184 bytes; the remaining1220 bytes agree,86.89% coverage. The unchanged
minimum0.70/24-byte and zero-tail rules pass. Generated exception catch regions
inside this complete body are retained, not truncated at the first normal RET.
The private caller/callee analysis retains normal thiscall and RET20; no private
register ABI is fabricated.

The ordinary library supplies prefix-versus-suffix choice, push_front/back,
checked iterator arithmetic, copy/copy_backward/fill and exception rollback.
Every repeated native call site corresponding to a given source relocation
symbol selects the same target. This supports the algorithm identity but does
not turn call destinations into matches:428680 pop_back, for example, remains
review. Existing independently proven short-deque providers cover the other
container helpers, and pinned CRT provenance covers invalid-parameter/throw.

This is **compiler provenance**, not a new canonical authored function or a
claim that remote EH handler/FuncInfo bytes passed full linked comparison.
No matches.csv, authored source, public match unit or old accepted body changes.
Only4638C0 moves from review to excluded through the new positive rule:
vc8-generated-short-deque-insert-106a. The rule recompiles the original probe
and verifies full-inventory uniqueness; a separate discovery scan is not the
acceptance result.

Receipts: build/frontier-short-deque-members-20261101/{hits,bindings}.json,
build/frontier-boost-library-20261031/vc8-generated-short-deque-insert-106a-validation.json,
and the focused scope ci.log. Anchor file:
config/vc8-generated-short-deque-insert-origin-anchors.toml.

Excluded1790/review435; authored1802/source1782/mapped1809 and units764 stay.
Authored exact1582/449309 bytes stays. Default CI235 and whitespace checks pass.
