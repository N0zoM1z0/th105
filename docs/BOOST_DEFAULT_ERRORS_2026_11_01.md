# Original Boost default error messages

6B4800/18, get_default_error_string, is now fully canonical and inventory-unique
from unchanged original regex_traits_defaults.cpp. Its genuine header
fastcall declaration naturally uses ECX; no ABI facade or replacement body is
introduced. Only 18 third-party code bytes are newly classified.

The existing original-source wrapper is now selected by a focused unit. Its
normalized source hash, original 184 headers and separate original-source
package are verified. Compiler profile O2/GS and original implementations are
unchanged. The complete getter has precisely two DIR32 fields: +4 names the
Unknown error literal at 6D32B4, and +13 names its own static table at 6D65E8.
All other bytes, full COFF extent, closed CFG and inventory uniqueness pass.

The proof covers the complete 96-byte table, all 24 zero-addend symbolic
source pointers and all 22 unique whole NUL-terminated strings. Every literal
is compared in readonly storage, including its final terminator; repeated
source pointers must preserve native identity. Slot 20 names the same fallback
literal used by the getter. The three trailing entries share the exact empty
string. This proves complete data dependencies rather than merely fitting two
addresses to an 18-byte code pattern. No metadata bytes receive function or
authored credit.

Seven focused tests reject wrong source/profile/headers, changed calling
convention symbol, shortened/masked comparisons and altered literal bindings.
All 85 real byte-corruption controls fail: every getter byte, every table
pointer, and the first and final bytes of every unique string. The full narrow
origin rule passes before reclassifying the one review row.

All eight selected original regex.cpp comparisons and the 14 release matcher
comparisons freshly pass after adding the two typed data bindings; the prior
matcher stack/dispatch ownership proof also passes. No cold corpus rebuild
was needed. Generic byte/coverage thresholds remain unchanged.

Evidence: build/origin-anchors/boost-default-errors.json and
build/frontier-regex-default-errors-20261101/. Private exploratory scripts are
under .analysis/frontier-regex-default-errors-20261101/.
