# Original Boost release assertion configuration

The unchanged, hash-verified Boost1.40 narrow instance source now supplies
50 additional library-origin bodies /20912 bytes under the ordinary NDEBUG
release configuration. This is library provenance, not authored game progress.
The original header closure, license, instances.cpp and compiler are unchanged.
No library implementation, target instruction or checker threshold is edited.

Canonical target SHA-256:
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.

## Independent reason for this configuration

The old assertion-enabled do_assign source emits466 bytes. Direct source/native
inspection identifies two extra27-byte shared_ptr assertion paths, each ending
in _wassert, absent from the native412-byte function. These are genuine original
BOOST_ASSERT checks of a non-null shared pointer, not unknown game behavior.
Defining standard NDEBUG before the original includes removes those54 bytes
through the vendor's intended configuration and reproduces the whole native
function. No guards are removed by editing a body or copying code bytes.

This proves that the standard release assertion policy reproduces these
observed bodies. It does not uniquely establish the original macro spelling,
Boost release number, or the configuration of every application TU. Other
supported assertion-control macros can have equivalent effects. Existing
assertion-enabled reference probes and their accepted evidence remain intact.
VC8 checked-container validation is not disabled: all invalid-parameter calls
in the literal/set matcher witnesses remain and are canonically compared.

## Reproducible source and verification contract

scripts/probes/BoostRegexReleaseInstancesOrigin.cpp contains only the NDEBUG
configuration and inclusion of the unchanged original narrow instances.cpp.
The upstream verifier accepts this explicit second wrapper alongside the
original wrapper; both still require the sole pinned header directory and
byte/hash/Git-blob verification of the same original CPP. Arbitrary wrappers,
missing header selection, altered original sources and unpinned extra headers
remain rejected. The added test verifies original-instance checking is not
skipped by the release selection. Builds perform no network fetch.

The source/configuration is isolated to this new probe. It is not a global
compiler flag change and does not disable assertions in existing game source.

## Full library provenance and canonical witnesses

The fresh object yields49 complete fingerprint hit sets covering50 previously
reviewed physical bodies. The rule recompiles the original source and checks
those complete hit sets across all4027 candidates, all target body hashes,
minimum non-relocated coverage0.70 and at least24 unmasked bytes. One39-byte
equivalence group contains both6A8790 and6A9600; it establishes the Boost traits
forwarding family, not a unique original method/template name at either address.
Only find_imp6B3420/694 has one original trailing CC; the following native byte
is also CC, under the existing maximum-one-byte alignment gate. No callable
instruction or remote tail is discarded.

Separately, four complete canonical replays resolve every relocation:

-6B4430 do_assign,412 bytes.
-6A0B30 recursive w32 traits isctype,133 bytes.
-6A1AE0 match_literal,224 bytes.
-6A24E0 match_set,146 bytes.

These915 bytes are library witnesses only. do_assign's full27-byte native
handler entry and the actual basic_regex_implementation primary vtable/RTTI
are pinned; no independent full-remote-EH claim is made for this COFF witness.
Its original empty shared-from-this hook resolves to an already shared RET
body; no new origin or credit is inferred for that shared address.

## Focused regressions and accounting

All nine connect-unit functions freshly pass (application827 plus eight
library witnesses1116), as do the original three narrow witnesses120 bytes.
All six prior Boost/std origin rules,191 physical bodies, are freshly
revalidated with no errors. Unrelated census/native evidence is retained;
this is not a cold all-unit reconstruction replay. Default CI211 and whitespace
checks pass.

The new origin rule is boost-release-library-106a, backed by
config/boost-release-library-origin-anchors.toml. The public canonical unit is
boost-regex-release-library-origin. Reports and private controls are under
build/frontier-boost-release-20261031/; the new rule's focused validation is
also retained under build/frontier-boost-library-20261031/.

Excluded rises1658 to1708 and review576 to526. Authored exact1576 /448613 bytes,
source1773, authored1793 and mapped1800 stay unchanged. Units759. No authored
matches, partial native prefixes or duplicate source instantiations are counted.

The subsequent compact-switch follow-up also fully matches the two larger
parser envelopes, including all metadata rather than treating section length
as callable length; see BOOST_COMPACT_SWITCH_PAYLOAD_2026_10_31.md.
