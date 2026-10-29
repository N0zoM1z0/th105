# Scene render-cluster destruction, JP1.06a

41F1F0 is canonical exact247/247, SHA256:
99376a4baf79fa0a5c1e6ad808e566bff49d04b003077960ab55813ae8d2f961.
The first complete source with the recovered real member types matches; no
source-spelling grid or compiler flag control is needed.

Exact Ending destruction41F2F0 calls it at41F338; exact Opening destruction
41F900 calls it at41F948. The normal body destroys string070, start-time
multiset064, the list of real7C timeline records058, object-pointer map04C,
and finally the embedded CScript018 through its actual containing registry.

The destructor is implicit. Real record ownership keeps list clear out of
line and releases each record's textures through its recovered destructor.
Object-map values are pointers into that list; clearing the map later destroys
only tree nodes, not the records again. There is no invented extra cleanup
call: Ending/Opening already invoke explicit cluster cleanup before normal
member destruction, just as their existing accepted source shows.

This closes the older stop based on incomplete container/lifetime views. The
new source reuses the unsigned-start multiset, typed timeline records and real
CScript ownership. It does not manually call STL private helpers, manipulate
nodes, publish vptrs or force a register schedule. The unmapped delete helper
only requests compiler emission of the implicit destructor; it receives no
native address or authored credit.

## Boundary limits

All accessed owned members end by08C. The unused seven-byte tail is retained
only as an observed view; no native allocation-size or containing-scene tail
padding conclusion is drawn. In particular, this does not replace the existing
93-byte opaque scene-member views or move Ending's alpha byte. Those enclosing
layout questions are separate from the complete247-byte destructor equality.

## Reproduction

scripts/repo-python scripts/build.py --unit exact-first-scene-render-cluster-lifetime --compare --json

Source:src/ui/SceneRenderClusterLifetime.cpp.
Receipt:build/frontier-scene-cluster-lifetime-20261029/formal.json.
One new complete EH-handler mapping is scoped to this root. Shared headers and
accepted caller sources are unchanged. Default CI covers final selection,
tracking and progress; no cold-corpus rebuild is claimed.
