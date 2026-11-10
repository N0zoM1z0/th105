# Original static-codebook destroy

681190/29 (_vorbis_staticbook_destroy) is now whole canonical and inventory-
unique from actual original SDK vorbis/sharedbook.obj. The full32-byte source
and native section, including three NOP alignment bytes, matches. The actual
ownership flag at object+30 gates clear and free exactly as in the original
object; no replacement C++ layout or runtime behavior is invented.

The named _vorbis_staticbook_clear at6810C0 is independently identified by its
previous original-SDK anchor and freshly compared over its complete193-byte
callable plus15 NOPs. All ten original free-call fields bind to the independently
owned CRT _free at68C686. Both complete CFGs close, every relocation and every
remaining byte matches, and the destroy body is unique across the whole
same-sized candidate inventory.

Only29 new library code bytes count. The existing193-byte provider and18 total
padding bytes are not counted again, and no authored bytes are added. The
original generic24-byte nonrelocation minimum remains unchanged: this root has
21 such bytes, but the narrow typed proof closes both exact calls and complete
provider rather than accepting a masked fingerprint.

Official SDK archive SHA256:
fead50bbdf6a17e695b8b628f4ebe2c64a8f589ca6b983909484f4f361afbfcc.
Original sharedbook.obj SHA256:
0c98ab8712fbf5f287d563a925e7f407e3a0a67b469c0d1bd9a67c6677582704.

Two formal comparisons pass. Seven focused tests reject changed source/member,
missing calls/provider, partial/masked extents and padding-as-code credit. All 240
actual byte-corruption controls fail, covering both entire source/native sections.
The narrow origin rule passes before the single review row changes.
