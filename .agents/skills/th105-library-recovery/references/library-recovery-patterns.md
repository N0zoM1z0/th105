# TH105 library-recovery patterns

This reference records empirical patterns for reconstructing external code in
the original Japanese TH10.5 v1.06a target. Re-run every command against the
current ledger and target; these observations are evidence seeds, not a waiver
of strict comparison.

## Progress semantics

`scripts/progress.py` intentionally excludes rows whose status is `library`
from the authored-game matching denominator. Therefore external recovery has
two distinct outcomes:

- it removes unresolved implementation/linkage work from a future complete
  executable;
- it increases a separate reproducible-library byte count, not the authored
  matching headline.

For an exact external function, retain `status=library` and use
`match_percent=100.00` with a source path, owner, and reproducible strict
comparison evidence. Never change it to `matching` merely for statistics.

## Audited island census (2026-08-12)

The fail-closed rules in `config/function-origin-rules.toml` currently identify:

| Island | Functions | Function bytes | Address range |
|---|---:|---:|---|
| zlib 1.2.3 | 44 | 21,553 | `0x00664FA0..0x0066AC2D` |
| Xiph Ogg/Vorbis/Vorbisfile | 151 | 52,055 | `0x0066BFD0..0x0067AFCF` |

These 195 functions total 73,608 bytes. At the audit date, all were already
classified `library`; thus their classification had already removed them from
the authored denominator.

Across the third-party islands, the largest 10 functions contain about 30% of
the bytes, the largest 50 about 71%, and the largest 100 about 91%. First solve
release/configuration anchors breadth-first, then prioritize large functions
whose remaining failures are only audited relocations.

## zlib 1.2.3 pilot

### Provenance facts

- Target strings contain `deflate 1.2.3`, `inflate 1.2.3`, and `1.2.3`.
- Official zlib tag `v1.2.3`, commit
  `abf180a067223611620dd97dd5681df7c7fa7c9b`, was used for the pilot.
- VC8 SP1 `/O2 /GS- /MT` produced multiple exact target functions without
  editing upstream source.

### Strict exact wave

The original seven no-or-low-relocation anchors expanded into canonical
translation-unit match units. They now reproduce all 44 functions and all
21,553 bytes exactly. This resolved `inflate`, `deflate`, `deflateInit2_`,
`_tr_*`, `lm_init`, `crc32_little`, all tree helpers, and the independent
Adler/inflate-fast/inflate-table translation units.

```bash
python3 scripts/build.py --unit zlib-inflate-anchors --compare --json
python3 scripts/build.py --unit zlib-deflate-anchors --compare --json
python3 scripts/build.py --unit zlib-crc32-anchor --compare --json
python3 scripts/build.py --unit zlib-zutil-anchors --compare --json
python3 scripts/build.py --unit zlib-inffast-anchor --compare --json
python3 scripts/build.py --unit zlib-inftrees-gs-anchor --compare --json
python3 scripts/build.py --unit zlib-adler32-anchor --compare --json
python3 scripts/build.py --unit zlib-tree-anchors --compare --json
```

The main reusable discovery is that one COFF data symbol may encode several
table-element addresses through raw DIR32 addends. Record independently
verified entries such as `_configuration_table+0x2` or `_crc_table+0x800` in
`config/reccmp-relocations.csv`, then select the exact addend key in the match
unit. Never map every addend to the table base.

The accepted fan-out also demonstrates the high-yield order for a known
release: solve public anchors, verify allocator/string/table DIR32 data,
promote direct helper callees, then expand to the large callers. Do not update
a ledger row from this historical note alone; rerun its canonical unit and
require an exact result.

Do not assign adjacent library identities by nearest size. The two approximately
1.2 KiB candidates initially appeared to be `inflate_table` then `inflate_fast`;
cross-comparing their prologues, `/GS` behavior, relocations, and complete bytes
proved the reverse mapping: `inflate_fast` at `0x00668560` and `inflate_table`
at `0x00668A20`. Candidate matrices should test every plausible source symbol
of similar size before naming the ledger row.

One original translation unit may be compiled globally with `/GS` while only
functions containing compiler-recognized vulnerable arrays emit cookies. In
`trees.c`, the same `/GS` object leaves seventeen accepted bodies unchanged and
makes `gen_codes` exact because its local 32-byte code table triggers the
cookie. Prefer one truthful TU configuration when it reproduces every member.

### Completed configuration/source-shape candidates

The former `inflate_fast`, `inflate_table`, `adler32`, and large `inflate`
candidates are now exact. The apparent size deltas were six-byte section-tail
padding, swapped target identity, `/GS` selection, and unresolved relocation
tables/strings—not source divergence.

## Xiph Ogg/Vorbis strategy

The current target has useful `OggS`, `vorbis`, and `ov_*` fingerprints but no
verified embedded release string. Exact release is unresolved.

Do not manually decompile all 151 functions first. Instead compile a small tag
matrix of official releases around the target era and compare public anchors:

- `ov_clear`
- `ov_open_callbacks`
- `ov_info`
- `ov_time_seek`
- `ov_time_tell`
- `ov_read`

Score each tag by exact COFF symbol size, constants/strings, public call graph,
and strict byte-prefix behavior. Promote a release only after several
independent anchors agree. Then fan out per translation unit.

The first matrix pass produced two reusable lessons:

- An allocation immediate can be a stronger release fingerprint than an API
  name. TH105 `vorbis_info_init` allocates `0xE80` bytes, matching the official
  v1.0.1 `codec_setup_info`; v1.1.0 through v1.2.3 allocate `0xE50`.
- A library island can be split by the linker. The 151-row libvorbis/file
  range calls a separate 33-row libogg framing/bitwise island at
  `0x006A2FB0..0x006A3DD7`. Follow semantic call edges before declaring the
  surrounding mixed address neighborhood authored or runtime code.

The v1.0.1 candidate currently gives three strict exact functions (44 bytes).
Nontrivial `ov_*` bodies remain configuration/source-shape work; do not fan out
their 100% status from release evidence alone.

## Failure taxonomy and next action

| Result | Meaning | Next action |
|---|---|---|
| exact | accepted comparator reports 100% | record command/report and exact library bytes |
| relocation-gated | bytes agree outside a named relocation | verify callee/data identity; map narrowly |
| configuration-gated | likely source release, different code shape/size | vary one macro or compiler flag |
| release-gated | upstream tag is not established | build a public-anchor version matrix |
| source-divergent | configuration cannot explain differences | search official patches or bundled forks |
| identity-unresolved | target boundary/address is uncertain | reconcile IDA with ledger and raw bytes |

## Handoff template

```text
Island/range:
Origin rule and evidence:
Upstream repository/tag/commit:
License/source placement:
VC8 flags and translation unit:
Exact functions/bytes:
Relocation-gated functions:
Configuration/release/source blockers:
Strict comparison commands or reports:
Ledger/source files changed:
Claims released or updated:
Validation commands:
```
