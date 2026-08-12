# zlib 1.2.3 reconstruction source

This directory contains the unmodified core sources needed to reproduce the
statically linked zlib island in the original Japanese TH10.5 v1.06a target.

- Upstream: `https://github.com/madler/zlib`
- Tag: `v1.2.3`
- Commit: `abf180a067223611620dd97dd5681df7c7fa7c9b`
- Probe compiler: Visual C++ 2005 SP1, `/O2 /MT`, with `/GS` selected per
  translation unit according to exact target evidence
- Target island: `0x00664FA0..0x0066AC2D`

`README.upstream` contains the original release notes and zlib license. The
vendored files are byte-identical to the named upstream commit; SHA-256 and
strict function-comparison evidence are recorded in the repository ledger and
match-unit manifests.

This directory is external source, not authored TH10.5 progress. Exact
functions remain `status=library` and contribute only to separately reported
reproducible-library bytes.

As of 2026-08-12 the canonical match units reproduce all 44 island functions
exactly: 21,553 of 21,553 function bytes. The `trees.c` and `inftrees.c` units
use `/GS`; only their vulnerable local-array functions emit security-cookie
code. The two adjacent 1.2K targets were identified by cross-comparison as
`inflate_fast` at `0x00668560` and `inflate_table` at `0x00668A20`.
