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

## VC8 runtime archive replay

For the static CRT, scan the SHA-pinned `libcmt.lib`/`libcpmt.lib` archives
before rebuilding or manually decompiling runtime functions. Partition the
ledger by address, let evidence workers emit read-only candidate packets, then
have the coordinator exclude every target with competing COFF symbol
identities. Group accepted targets by canonical archive member and rerun every
`msvc_prebuilt` unit from the repository build path.

This method produced 74 symbol-unambiguous exact functions and 6,862 bytes in
one breadth wave. It also exposed the dominant next blockers—runtime globals,
SEH tables, imports, and shared REL32 callees—without weakening the comparator.
Identical code is not enough to choose among `__CI*` helpers or other aliases;
leave those targets unresolved until independent call-site evidence selects a
symbol. Preserve compiler/register ABI helpers as documentation shims rather
than inventing ordinary C prototypes.

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

The target has useful `OggS`, `vorbis`, and `ov_*` fingerprints but no verified
embedded release string. The `vorbis_info_init` allocation size and
`ov_time_seek` control-flow fingerprints establish libvorbis v1.0.1; the
SHA-256-pinned official Windows SDK supplies the authoritative COFF codegen.

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

The v1.0.1 candidate initially gave three strict exact functions (44 bytes)
under VC8, while nontrivial bodies differed. The historical Win32 project files
explain why: release builds contain Intel compiler flags such as `/O3`, `/QaxK`,
`/Qsox-`, and `/Qip`. The archived official SDK resolves that configuration
gap directly. Its SHA-256-pinned prebuilt `info.obj`, `vorbisfile.obj`,
`framing.obj`, and `bitwise.obj` match nontrivial target bodies and enable a
translation-unit fan-out without guessing a modern compiler profile.

Reusable rule: after source release identification, search historical official
SDKs before hand-tuning compiler flags. Treat the SDK archive SHA, COFF member,
and strict comparator as separate gates; never promote the whole archive from
one exact anchor.

For a COMDAT-heavy official SDK object, a relocation-masked scan is an efficient
mapping pass, not acceptance evidence. Match each object section against ledger
sizes while masking only its recorded four-byte relocation fields. Then read
the linked REL32/DIR32 destinations back from the exact target, verify static
data prefixes in both object and image, and replay every relocation through the
strict comparator. This converted the libogg scan into 33/33 exact functions:
24 retained `framing.obj` bodies and nine retained `bitwise.obj` bodies. It also
exposed the linked CRT aliases (`_malloc`, `_free`, `_realloc`, `_memmove`, and
`_memchr`) without conflating them with pre-existing source-facing aliases.

Linked target addresses, not object-symbol occurrences, are the progress
identity. Different SDK objects can contain contextual static helpers with the
same code and the linker can fold them onto one target address. Keep one
canonical match-unit owner for that address, retain the other COFF spellings as
known aliases, and use a function-local relocation override when one object
uses an ambiguous helper name. The `floor1.obj`/`res0.obj` shared `ilog` and
the `floor1.obj`/`mapping0.obj` `ilog2`/`ilog` pair are the regression cases:
36 object-function mappings become 34 unique ledger functions, not 36 progress
credits.

Once several objects prove the release and code-generation identity, fan out
independent address-bounded scans in parallel. A masked scan may propose a
mapping, but the coordinator must audit every referenced callee, constant, and
table addend and rerun the strict comparator before updating the ledger. This
sequence closed a 52-function, 16,697-byte wave across psychoacoustic,
shared-book, bitrate, envelope, FFT/MDCT, floor0, LSP, lookup, and floor1 code.
It is substantially faster than hand-decompiling each library function while
preserving the same acceptance gate.

After the breadth wave, rescan unresolved ledger rows against function symbols
in objects that are already proven. Static helpers omitted from the first
candidate index can still be exact, and solving their table/constant
relocations may unlock large callers immediately. The first Xiph tail pass
found nine additional functions and 7,316 bytes. A second pass then corrected
six archive-call identities and audited their CRT, constant, and pointer-table
relocations, adding another 926 exact bytes. Only `res0_free_look` (54 bytes)
retains a real non-relocation difference.

Do not infer an unresolved function's archive identity from address adjacency
or a preliminary object label. Resolve its linked call destinations and exact
COFF symbol first. The Xiph regression cases are `drft_init`, `drft_clear`,
`mdct_init`, `mdct_clear`, `_vorbis_window_get`, and
`_vorbis_apply_window`: all six initially looked like residual divergence, but
strict relocation replay proved the official SDK bodies exact.

Do not assume one source file per archived object when historical IPO is in
use. In the official SDK, functions from `lookup.c` were emitted into
`lsp.obj`. Keep the upstream source path in the function ledger, record the
actual archive member in the match unit, and give each generated object a
distinct output name if two units extract the same member.

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
