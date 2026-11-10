# Complete Boost parser code and compact-switch metadata

Two additional original Boost release parsers are fully canonical exact,
including every source COMDAT byte rather than merely a code prefix:

- parse_perl_extension6B04E0:2478 code bytes and107 suffix bytes,2585 total.
  Complete payload SHA-256:
  c04eff569ee473d888d037b45e445cf1a6af9cccc65a919285cd13d7b1abcf29.
- parse_extended_escape6AF880:1407 code bytes and128 suffix bytes,1535 total.
  Complete payload SHA-256:
  16946d68fb558c1a76a9902c29f863b1f9d6a4b59f3ddd18f129954a6f937326.

The original Japanese v1.06a executable remains
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.
Only the unchanged verified Boost instance TU with its established NDEBUG
configuration is compiled. No library implementation or compiler flags change.

## Why the earlier section lengths were not codegen mismatches

The source2585/native2478 and source1535/native1407 comparisons mixed total
COFF section lengths with native callable lengths. Direct inspection shows
all code bytes agree after relocation replay. The remaining source bytes are
actual compact-switch metadata, not an omitted code tail:

- First parser: two-byte8BFF alignment,13 jump words,53 index bytes.
- Second parser: one-byte90 alignment,21 jump words,43 index bytes.

Every jump target is a decoded instruction inside the complete code extent,
and every code instruction is reached by the closed CFG including the switch
cases. The metadata ends before the next candidate entry. None of those235
suffix bytes is counted as authored or library callable code.

## Narrow complete-payload verification

coff_switch_payload.py accepts only one fully bounded compact switch suffix.
Its exact contract records complete payload size/hash, code-relative load/jump
sites, table/map offsets/counts and actual alignment bytes. The entire fresh
canonical COFF tail must equal the entire target payload, including alignment,
all jump destinations and every index byte. Truncation or extra source bytes
fail; no region is masked or skipped.

The verifier additionally requires:

- Exactly the declared partition: complete code ending in RET, supported
  zero/one/two-byte alignment, all jump words, then the complete byte map.
- Actual MOVZX byte-map load and matching indexed JMP, with local COFF DIR32
  fields. Every table word has exactly one local DIR32; no map/alignment
  relocation or externally aliased local label is accepted.
- A matching32-bit unsigned CMP/JA range guard. One observed intervening
  MOV of a byte register to an ordinary stack byte is allowed because it
  changes neither flags nor index. Other intervening instructions are rejected.
- Map indices cover and stay within all declared table entries. Destinations
  are owned instruction boundaries; branches cannot bypass the guard, escape
  code, enter metadata or introduce another indirect jump. All code is reached.
- The exact fixed-base, relocation-stripped target profile. This original EXE
  has no base-relocation directory; source COFF relocation proof is retained
  rather than inventing target HIGHLOW records that do not exist.

Normal unit comparison now runs this additional proof whenever switch_payload
is configured, in JSON and text modes. A code-prefix match with failed suffix
proof becomes blocked, never exact. Existing-object comparison uses the same
gate. The metadata contract and verifier are included in input hashes. Other
ordinary and owned-extent comparison paths are unchanged.

The origin validator also runs the mandatory complete proof before its existing
full-inventory code fingerprint/coverage check. Its old alignment-only path and
single-occurrence REL32 anchor rules remain unchanged. Separate payload call
bindings replay repeated parser calls through the ordinary canonical comparator;
they do not broaden the old provenance mapping syntax.

## Validation and accounting

Twelve new tests reject wrong sizes/hashes, byte changes, unowned/invalid cases,
index/guard changes, unsupported intervening instructions, missing/extra/foreign
relocations and additional indirect jumps. Build-level tests require failure
in JSON/text modes and retain successful full-payload receipts.

The public boost-regex-release-library-origin unit now passes six functions:
4800 code bytes plus235 parser metadata bytes. Both new full-inventory origin
anchors pass. All15 previously accepted connect/narrow/effect-deque canonical
roots freshly pass, as do eight prior origin rules covering244 physical bodies.
Default CI223 and whitespace checks pass. No cold whole-corpus reconstruction.

New rule: boost-release-switch-library-106a. Anchors:
config/boost-release-switch-origin-anchors.toml.

Two library exclusions add3885 code bytes only: excluded1710, review524.
Authored exact1576 /448613 bytes, source1773, authored1793, mapped1800 and
units759 stay unchanged. No authored or helper-byte inflation.

## Four more envelopes through the unchanged gate

A bounded discovery pass over both already-verified original instance objects
found four more complete compact-switch candidates. Discovery was explicitly
non-acceptance: their actual source objects subsequently passed full canonical
replay and the same closed-code/table/index-map verification:

- fixup_pointers6A0DC0:118 code /154 payload,5 jump entries/14 indices.
  SHA-2563b20771b36e09d652b866d77c022f954e39efa0d9e20c56f449d276d99061fc4.
- probe_leading_repeat6A0EE0:84 code /126 payload,4 entries/26 indices.
  SHA-256c8cac4ec2f944f3f63d7c3a6d7854bf523a951731f093a4e66b4225b8e6698b2.
- calculate_backstep6A2C40:196 code /255 payload,8 entries/27 indices.
  SHA-256b7c69efa4a770cc96bc756ef49eea4b2900c683f86c00f7caeb782d4e7092a72.
- parse_repeat6A7C90:546 code /583 payload,2 entries/27 indices.
  SHA-256c3602e59ffd86be47c4c5e6592f9bd7eca91ffc07e3ae6fedf5fdf57849355ff.

All944 code bytes and174 metadata bytes pass. The first two reproduce under
both reference assertion configurations, so their equality does not distinguish
the original assertion macro. Public reproduction retains the same dedicated
release wrapper. No source, compiler flags, verifier or tests change here.
The two remaining append_set reference sections remain genuinely nonmatching
in both configurations; section-size similarity is not accepted as equality.

The expanded full-inventory switch rule passes all six physical bodies/4829 code
bytes, each with its entire canonical payload. Only the four newly reviewed rows
change classification; the previous two are not counted again. The public release
unit now passes ten canonical roots:5744 code bytes plus409 metadata bytes. Default
CI223 and whitespace checks pass.

Excluded1714/review520; exact1576 /448613, source1773/authored1793/mapped1800
and units759 remain unchanged. No authored credit or table truncation.
