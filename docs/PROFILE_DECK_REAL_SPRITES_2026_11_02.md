# Actual profile deck sprites and tile

ProfileDeckConstructor.cpp now uses global CSprite for its four sprite members
and global CTile for its tile. ProfileDeckDisplay.cpp uses the same actual
CSprite for its three accessed sprite members. The three local color-derived
substitutes are removed. CSprite has nine virtual slots, not the eight-slot
prefix described in the older recovery. CTile has four inherited slots and a
nonvirtual texture wrapper. No shared class header or compiler flag changes.

The original executable identifies these owners through their vptr publications
and RTTI. The new constructor object independently emits both real class
hierarchies and all nine/four table role identities. Its direct tile texture
call now uses the actual signed-extent CTile::set_texture declaration, bound to
4098B0; that complete37-byte wrapper freshly compares exact. The global CTile
relocation anchor is strengthened from its first4 bytes to all16 slot bytes.
All11 roots in the three existing explicit alias consumers freshly remain exact.

## Measured change, not an exact promotion

A fresh before-control at HEAD0adeb3da produced2132 bytes, SHA
eec4e2cae3d74cdadd236e79582942ec3ade1f7cdb130b2284b6c41b2ba335be,
with its first mismatch at+110. That differs from the old document's historical
+1127 measurement; historical descriptions are not current acceptance evidence.

The actual CSpriteBase initializing handle naturally corrects28 byte positions
in the five member-initialization sequences. Every changed byte now agrees with
the target. No source byte after offset200 changes. The new candidate remains
2132/native2136, SHA
16486e43f67cabf742b1fe83d06e6476831b4888b451b5879fd168f98d336973,
and its first mismatch is again+1127 in the existing EDI/EBP loop assignment.
Neither the matched prefix nor those28 corrected positions receives credit.
The loop-shaping lane remains closed; no register/EH/padding coercion was added.

The independent signed-byte number adapters retain7/15 exact. Display448B40
retains its whole440-byte SHA
08b944aedbf4badea9d3455c5a30f0f11e3bc39a67ac696446d0730922d5bca5;
it remains nonexact against439 native bytes. No new source selection, exact
count or authored bytes are added. Original complete menu nominal layout and
full parent unwind graph are not claimed by these sprite ownership checks.

The corresponding .analysis scope holds the bounded controls. Default CI and both
diff checks gate the checkpoint.
