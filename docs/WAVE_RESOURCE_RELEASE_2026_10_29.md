# Wave resource release, JP1.06a

401BD0 is canonical exact76/76 in genuine linked source context.
SHA256:7b37941f416d63e1938b5e2ba0b7d82bf62fed5aad81b9f022e89c4ba499374c.

Exact scene-resource shutdown43D670 calls it at43D70E while releasing the128
indexed event-wave handles. The root rejects token0, tests its generation-checked
lookup, repeats the lookup on success, deletes the stored sound resource through
virtual slot04 if nonnull, recycles the token and returns true in AL. A failed
lookup returns false. All three RET4 exits belong to the complete76-byte body.

The actual sound-resource interface has initialize at slot00 and the virtual
deleting destructor at slot04, consistent with DirectSoundResourceLifetime.cpp.
The manager is at owner+64 and its checked containers/lock have the established
64-byte shared handle-manager layout. Only pointer views are used; no synthetic
resource instance or initializer is introduced.

## Genuine source context and provider check

WaveResourceRelease.cpp contains the natural resource release and real
generation-check/free-slot recycling body. The real existing
ResourceHandleLookupRuntime.cpp participates in CIL. The ordinary unsigned-int
list instantiation is the sole compiler-library COFF input. No fabricated
provider, private register declaration or copied machine code is used.

This context naturally places the shared405200 recycler receiver in EAX.
An additional linked provider audit validates the original401C09 caller edge
and reproduces the complete167-byte405200 body:
f225dfcb190c5b55cba3f65a784ba7a244a15da3670549afac6573f6c4166421.
That helper was already accepted independently in the network-send context;
its existing ledger/receipt remains unchanged and earns no additional bytes.
The lookup participates as real source but gains no new acceptance claim.

The first private probe placed the actual lookup in COFF and also matched.
Public workflow validation disallows an application-source COFF input, so the
final unit includes that real definition in CIL instead. Both the76-byte root
and167-byte provider remain exact in this supported final configuration.
No validator was weakened or bypassed.

## Reproduction

scripts/repo-python scripts/build.py --unit exact-first-wave-resource-release-linked --compare --json

Public source:src/audio/WaveResourceRelease.cpp.
Final formal receipt:build/frontier-wave-release-context-20261029/formal-build.json.
Private provider witness:provider-public-compare.json in the same directory.
The full linked-symbol/CFG boundary is76, not an accepted prefix of a larger
body. No shared source/header or previous accepted unit changed. Default CI
and diff checks validate the final ledger/progress update.
