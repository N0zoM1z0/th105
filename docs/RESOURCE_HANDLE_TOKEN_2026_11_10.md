# Resource-handle token decoding

`CHandleManagerLookupView::lookup_token_417800` now copies its four-byte packed
argument into a real `ResourceHandleToken` object. This removes the unrelated
struct lvalue previously formed over an `unsigned int`, preserving defined
object lifetime and byte-copy semantics on the pinned little-endian VC8 target.
The existing header fixes the token size at four bytes. Native `0x417852` and
`0x417870` read the unsigned low and high words of that same argument for slot
and generation respectively; no new validation or token policy is introduced.

The fixed-size `memcpy` disappears during compilation. All 110 non-debug COFF
sections and 206 symbolic relocations, including the complete 196-byte lookup
and its cleanup metadata, are unchanged. Each of the five linked consumers was
rebuilt before and after the edit. Their entire images are identical after
excluding only the COFF and export-directory timestamp fields, including all
code, data, EH, imports, exports and base relocations. Existing exact roots
remain 148/148 for texture-size query, 76/76 for wave-resource release and
266/266 for tile texture setup.

The lookup itself remains nonexact at the existing unwind-state scheduling
and private vector::at ABI boundary. The two gain callers also remain nonexact.
A private integer-mask/shift control changes the lookup to 177 bytes and was
not retained. No ledger, source pin or Factory acceptance was changed.

Evidence and fresh six-unit receipts are under
`build/frontier-resource-token-20261110/`, with the complete review recorded in
`verification.json`. The target comparator verifies the original JP1.06a
executable SHA-256 before reading its bytes.
