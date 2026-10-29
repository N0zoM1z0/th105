# Group-A versus primary collision, 0046B940

The canonical Japanese1.06a function is [46B940,46BA05),197 bytes, SHA256
`85ed2b3aae25817a15189dd4b28b698617c2566fd9b433ccecec6af1cb545d9b`.
Exact attack-candidate resolver46DA10 calls it at46DACC. Its two outgoing
calls reach exact descriptor test46B7B0 and extent accumulator46B3B0.
Raw CFG reaches194 instruction bytes, with only the three-byte internal
alignment LEA at46B97D unreached. All197 bytes remain strictly compared;
eleven following INT3 bytes are outside this callable. Both returns pop8.

The receiver is CollisionContext. The second object's primary-box pointer at
+32C gates the traversal. The first object's signed-byte count at+1AF controls
a signed-byte index; each index selects a16-byte box at+204 and descriptor
pointer at+304. A nonnull descriptor invokes the established shaped-box test.
Otherwise four signed separation differences are ANDed, and bit31 selects
extent accumulation and result1. The function ORs every hit into its result,
without early success return. It does not add a missing-primary check inside
the loop or clamp the observed signed count.

The earlier unselected GeometryGroups source cached second+32C across calls.
Native instructions instead reload that pointer at46B998 and46B9AA on each
iteration. The selected source restores that callback-visible read lifetime.
The bit31 condition is expressed directly, as independently established for
the exact descriptor helper, without synthesizing register dependencies.
Only this function changes; its siblings and shared layouts are unchanged.

Focused whole-body controls:
- Retained cached-pointer source:161/native197.
- Restored primary-pointer reload:180/native197, first difference+1.
- Reload plus explicit bit31 condition and result initialization:197/native197,
  first difference+0, SHA256
  `171f718877017f47736cfa592fad7fd99c3712c8978dc184d2fe3b01b4308b73`.
- Returning the initialized result at the null guard is codegen-identical.

The final candidate remains **nonexact**. Native persistent receiver/index and
stack lifetimes differ; equal total size is not a match. No register forcing,
padding, fake ABI or partial-byte credit is used. Source-level complete object
extents and original class/TU spellings are not recovered; the existing narrow
raw-offset accessors remain explicit views, not full object definitions.

Unit: exact-first-group-a-primary-collision. Receipts:
`build/frontier-46b940-20261029/{formal-build,boundary}.json`.
Private controls: `.analysis/frontier-46b940-20261029/`.
