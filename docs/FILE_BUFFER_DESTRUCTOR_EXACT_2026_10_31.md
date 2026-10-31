# FileBuffer destructor: whole 14-byte exact acceptance

FileBufferContext::~FileBufferContext at4055F0 now passes canonical whole-body
comparison, adding one authored function /14 bytes. Source and native SHA-256:
22cce6900ead54873cbd1da9e0bd9d27451617d54e823bdf3bb761c35fd9ae63.

The existing source destructor conditionally releases its owned unsigned-char
array through actual array delete. The C++ declaration remains an ordinary
member destructor. Genuine VC8 CIL chooses its private EAX receiver naturally;
there is no source register convention, naked function, assembly or helper stub.

The source graph is the existing exact-first-csv-file-loading unit. The
independently padded native body remains [4055F0,4055FE); no boundary changed.
Earlier work had a length-correct private body but no accepted standalone
caller path. The array ownership correction and strict cleanup-entry witness
now close that acceptance gap, not by assuming all private helper bodies match.

## Complete exact caller and cleanup edge

The exported CScript::load405810 is freshly exact282/282. Its handler6BDF78/27,
FuncInfo6E4618/36, unwind map6E4610/8 and cleanup funclet6BDF70/8 all replay
completely. At6BDF73 the actual funclet tail-calls4055F0.

The new optional private-from-cleanup witness admits only an ordinary
nonvirtual source destructor behind an exported caller with full static CRT
cleanup evidence. Every comparison freshly replays the entire caller and its
complete EH packets before considering the child. It then requires:

- The selected cleanup index and exact native site.
- The unique original compiler funclet in the source CIL map, not an export.
- Its entire eight-byte source/native receiver-preparation and tail-jump body.
- The exact canonical cleanup hash and explicit callee symbol binding.
- A real source jump to the actual unexported destructor and native jump to
  the selected target entry.
- Unchanged normal full-function comparison for the destructor itself.

Missing/stale parent replay, mismatched receiver preparation, wrong source or
native destination, absent/duplicate cleanup packet, wrong site/index, exported
cleanup helper and an unbound destructor all fail. No caller bytes are waived.
The compiler's eight-byte cleanup funclet receives no separate authored credit.

This is distinct from the unaccepted ordinary free stdcall line parser405930.
That parser's unsupported member-cleanup contract is not generalized or bypassed.

## Focused validation

All twelve previously accepted functions in this CSV/script/reader/texture unit
remain exact, now thirteen with the new destructor. The two existing Ogg/SFL
nested private/EH functions also freshly replay exact after the tooling change.
Eight new target-independent regressions cover the cleanup-entry contract.
The new helper is included in linked build input hashes.

Receipts: build/frontier-script-parser-lifetime-20261031/
cleanup-final-accepted.json and cleanup-bgm-accepted.json.
This is a focused replay, not a fresh all-unit corpus claim.

The obsolete source-only origin rule for4055F0 is removed and its census row
now follows canonical-exact-authored. Exact totals become1,554 /441,693 bytes.
Source1,752, authored ownership1,772, exclusions1,640, review615, mapped1,779 and
match units745 are unchanged.

Default target-independent CI passes188 tests; generated progress and whitespace checks pass.
