# Actual title lifetime members, 2026-11-02

Target SHA-256: 56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.

The shared Title.hpp now uses actual CSprite for members +0x0C / +0xA4 and
actual CTile at +0x138. TitleColor94 / TitleColorA4 and their manual color-vptr
cleanup stores are removed. Ordinary member lifetimes generate the same complete
161-byte title destructor at 0x425D40. The outer CTitle and resource declarations
are otherwise unchanged; constructor-facing outer ownership is still separate.

Because Title.hpp is broadly included, validation uses its actual quoted-include
closure, not a repository-wide replay or a few selected examples. The closure
contains 147 units. All 222 accepted roots in 113 units pass adopted canonical
replays. Before/after comparisons for 73 other roots in 61 units are unchanged:
71 compared candidate hashes and two prior blocked results. The blocks remain
Scenario command 0x458440 basic_string constructor relocation and design loader
0x40B000 EH relocation; neither is bypassed or called exact. Other nonexact
functions remain nonexact. All native work ran serially on CPU 0 at nice 10.

Title's 30-byte scalar wrapper keeps its existing origin proof. The full normal
destructor EH is 88 code + 76 metadata bytes, canonical throughout. Its emitted
IColor RTTI graph is 93 bytes and matches. This destructor TU does not emit the
CSprite / CTile RTTI roots; their complete member identity proof is the already
accepted actual title-constructor context in TITLE_REAL_SPRITES_2026_11_02.md.
No synthetic owner or additional RTTI emission is inserted for the audit.

Final CI passed all 962 tests in 105.814 seconds. Both diff checks gate the local
checkpoint. No manifest, validator or ledger changes. Totals remain 1426 exact /
443399 bytes, source 1636, authored 1655, mapped 1826, excluded 2076, review 296 and
units 813.
