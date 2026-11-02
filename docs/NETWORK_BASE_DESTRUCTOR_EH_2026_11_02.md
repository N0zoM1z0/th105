# CNetworkBase destructor: complete natural member unwinding

The ordinary constructor and destructor now share `NetworkBaseMembers.hpp`.
The input packet at +0x90 and the minimum observed nested queue-pair view at
+0x20C retain their own implicit lifetimes. The queue pair exposes two 0x20
slots at +8; the following eight parent bytes remain opaque, not a claim
about the original type's complete source declaration. Endpoints contain
CInputManagerEx and a short deque; sprite arrays use the actual global CSprite.
No manual vptr writes, fake ABI, inline assembly or emission barriers were added.

## Whole checks

- Constructor 0x0044DB10: 411 bytes unchanged; packet cleanup 8 exact.
- Destructor 0x0043C950: 259 bytes unchanged; scalar 30 and reset 175 exact.
- Destructor EH at 0x006B8C60: 169 bytes exact, rather than the old flattened
  source's 179. Handler 0x006B8CEE is at section offset 142.
- FuncInfo 0x006DEC98 and unwind table 0x006DECBC: complete 36 + 64 bytes exact.
  Eight actions start at offsets 0, 11, 25, 49, 63, 87, 101 and 115, with
  previous states -1 through 6. Typed relocations and complete metadata checked.
- EH SHA256: c3830b6c934208316ea0ddb3d31723aedbc5301a31a127c9282ee30efbfb0e8c.
- Metadata SHA256: bd3d5f4d9ebb83e4394b2358672f6c30f1fca4ad358c4bc00eb1c689960fb76e.
- Packet 8, queue pair 19, slot 8, endpoint 19 and deque callback 5 are fully
  replayed as support. Natural CSprite ctor 16 and cleanup 7 also pass.
- Existing constructor remote EH 197 / metadata 116 remains exact. Its region
  is 0x006BA400, distinct from the destructor region above.

The public destructor audit verifies fresh owner provenance, whole main and
remote regions, all eight funclets plus the handler, named terminal jumps,
real member helpers and natural sprite callbacks. Eight structural tests and
610 distinct single-byte corruption controls reject incomplete or altered
proofs. This is static reconstruction evidence, not execution of OS exception
handling. Overlap with earlier mutation scopes is not added as new coverage.

Both source-hash gates were renewed only after whole comparisons: CSprite
lifetimes and implicit packet cleanup now pin the shared header. Both pass;
the existing scalar-wrapper 30-byte receipt was freshly rebuilt in isolation.
No global cold exact rebuild was performed and no aggregate freshness is claimed.

No authored or inventory credit is added: exact authored 1429 / 443911 bytes,
source-present 1634, authored 1653, excluded 2072, review 302, mapped 1821,
units 808. The queue-pair helper remains support outside the inventory.

Reproduce serially using CPU 0 / nice 10 and scripts/repo-python:
`build.py --unit gpt-web-network-base-runtime --compare --json`, the analogous
constructor and sprite builds, `audit-network-base-destructor-eh.py`,
`audit-network-base-constructor-eh.py`, the two lifetime origin gates, and
`scalar_wrapper_origins.py --unit gpt-web-network-base-runtime`.
Local proof and corruption receipts are in the ignored
`build/frontier-network-base-dtor-20261102/` directory.
