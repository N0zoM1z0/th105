# Original package-map subtree cleanup

The complete94-byte41C630 subtree cleanup is canonical exact from original VC8
std::map<unsigned, PackageFileIndexNode>, instantiated by the existing actual
package-store/node/critical lifetime source. The public compiler-only unit is
vc8-package-store-library-origin; source stays PackageArchiveStoreLinked.cpp.
No synthetic gameplay caller or replacement library body is introduced.

Native/canonical SHA256:
30a284075b906c8b5c84455218fb233853c58ba9f55700d6fa3682ce1204a987.
All94 bytes, including recursive control flow and the final return, participate.
Five source REL32 fields resolve to the same recursive member, original free,
PackageFileIndexNode's actual destructor and scalar delete. The freshly emitted
node destructor also remains canonical43 bytes. This preserves the real filename
and chained-node ownership, rather than treating the20-byte value as a trivial
raw payload. No EH or global lifecycle inference is made from this leaf.

The unchanged0.70/24/no-alignment-tail source-origin gate independently finds
exactly one full-inventory occurrence. Seventy-four nonrelocation bytes agree;
the remaining20 bytes are genuine COFF relocation fields. Discovery first used
an original-template exercise, then the actual existing package lifetime source
independently reproduced the same helper. Only the latter is selected as the
reproducible public witness.

Rule vc8-generated-package-map-erase-106a moves only41C630 from review to excluded.
Anchor: config/vc8-generated-package-map-erase-origin-anchors.toml.
No matches.csv row or authored-byte credit: exact1582/449309 stays; source1782,
authored1802 and mapped1809 stay. Excluded1791/review434; units765.

Receipts: build/frontier-map-members-20261101/formal.json,node-dtor.json,
store-hits.json and ci.log; new-rule full-inventory validation is under
build/frontier-boost-library-20261031/. Default CI235 and whitespace pass.
The unrelated larger map/PatRecord member controls remain nonmatching and get
no inferred classification from this result.
