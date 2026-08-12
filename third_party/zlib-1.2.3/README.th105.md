# zlib 1.2.3 reconstruction source

This directory contains the unmodified core sources needed to reproduce the
statically linked zlib island in the original Japanese TH10.5 v1.06a target.

- Upstream: `https://github.com/madler/zlib`
- Tag: `v1.2.3`
- Commit: `abf180a067223611620dd97dd5681df7c7fa7c9b`
- Probe compiler: Visual C++ 2005 SP1, `/O2 /GS- /MT`
- Target island: `0x00664FA0..0x0066AC2D`

`README.upstream` contains the original release notes and zlib license. The
vendored files are byte-identical to the named upstream commit; SHA-256 and
strict function-comparison evidence are recorded in the repository ledger and
match-unit manifests.

This directory is external source, not authored TH10.5 progress. Exact
functions remain `status=library` and contribute only to separately reported
reproducible-library bytes.

As of 2026-08-12 the four canonical match units reproduce 33 of the island's
44 functions exactly: 10,211 of 21,553 bytes. Eleven functions and 11,342
bytes remain for configuration/source-shape investigation.
