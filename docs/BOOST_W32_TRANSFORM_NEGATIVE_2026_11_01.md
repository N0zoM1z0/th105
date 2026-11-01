# Bounded original W32 transform checks remain nonexact

The unchanged original w32_regex_traits.cpp was freshly compiled through its
existing wrapper, O2/GS and pinned original packages. The narrow character
w32_transform source body and native6B57B0 are both539 bytes, but 88 positions
outside the source relocation fields differ. Instruction locations diverge;
source relocation offsets must not be treated as native pointer/call slots.
This is a negative comparison, not a partially accepted body or a matching
callee assignment. The retained original seven/eight-TU CIL graphs both emit
533 bytes rather than539. No source, profile or header was changed.

## Bounded historical-source check

Official Boost1.34.1 source at commit
3cd2b52030fbca6e30d32c787e65778283c2904b was fetched and checked against its
Git blob64fd2ce410b2289a5290e2675915e840a9208bde. Compared with selected1.40,
the active ANSI char w32_transform function text is identical after selecting
the BOOST_NO_ANSI_APIS-disabled branch. The new text is a non-ANSI fallback;
the native routine calls LCMapStringA. This supplies no changed active body to
try, so no alternate-version build was performed. It does not compare every
header, prove whole-TU equivalence or identify the shipped release.

[Verified official source](https://github.com/boostorg/regex/blob/3cd2b52030fbca6e30d32c787e65778283c2904b/src/w32_regex_traits.cpp)

Private source and build recipe:
.analysis/frontier-regex-w32-source-20261101/. Evidence:
build/frontier-regex-w32-source-20261101/transform-negative.json,
history-negative.json and version.diff. The latter reflects the exploratory
text diff; Git-blob verification and active-body equality are recorded in the
JSON. The selected original packages stay untouched. Do not repeat this same
ordinary/CIL or1.34.1-char-function comparison without new independent evidence.
