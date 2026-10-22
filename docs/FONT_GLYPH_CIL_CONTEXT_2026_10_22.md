# Glyph: real CIL context and project-option controls

Scope is the complete624-byte glyph body at411B80 in Japanese1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The previous turn accepted color411790, not glyph. Fresh target/status/tracking
preflights pass; IDA again rejects the other executable. No source, header,
profile, mapping or acceptance row changes in this checkpoint.

## Actual CIL body and the complete residual

The configured `gpt-web-text-font-color-linked` image is independently rechecked
through its accepted color result, including full build provenance and actual
renderer -> parser -> color witnesses. Its actual private glyph at100019A0 is
624 bytes/189 instructions. The renderer has one corresponding E8, with the
observed EAX font and three stack words; it does not force-export a synthetic
copy of glyph. Original nominal method/TU spelling remains unknown.

Replaying only its three actual named E8 fields gives the same complete glyph
payload as the native O2/Ob1 source:
`a1f0b4e58a76926fa837cdd852256122752fea9e5c9226332fc02139a8ac7806`.
Target hash remains
`3e67460ec4d76b1bdf2e30566a9dc74d44c3d34116e847e49ea78667bfb93630`.
Exactly14 bytes differ in+89..103, inside the same16-byte calculation window:
target starts with ascent and adds cached cursorY, while source starts with
cached cursorY and adds ascent. Every byte outside this window agrees.
This concrete real CIL context does not resolve the arithmetic scheduling gap;
it is not a general standalone-object or LTCG impossibility claim.

Both full bodies decode189 instructions with187 normally reachable. The7-byte
LEA at+158h and1-byte NOP at+15Fh are skipped by the same internal branch and
remain in the full comparison. The linked canonicalizer correctly rejects
unaccounted unreachable instructions; it is unchanged. This diagnostic retains
all624 bytes, proves both normal CFGs and their identical skipped instructions,
attests absolute bindings/HIGHLOW coverage, and resolves actual linker call
identities. It does not crop those eight bytes or qualify a new exact unit.

## Independent cached-field and compiler controls

The cached ascent and cursorY fields are physically32 bits; observed arithmetic
does not establish their original signedness. Each unsigned-field hypothesis
therefore changes only its one private header declaration, with the genuine
0x194 layout assertions intact, and compiles the complete current source.

| Private control | Complete glyph | Other11 comparison bodies |
| --- | --- | --- |
| Unchanged source/header baseline |624, a1f0b4e5, nonexact+89|Current hashes/extents|
| Unsigned cached ascent13C |Same624/hash/+89|All unchanged|
| Unsigned cursorY138 |Same624/hash/+89|All unchanged|
| O2/Ob1 plus COFF debug information `/Z7` |Same624/hash/+89|All unchanged|
| O2/Ob1 plus `/arch:SSE` |Same624/hash/+89|All unchanged|
| O2/Ob1 plus `/arch:SSE2` |624,13108c90, nonexact+14|Only accent411DF0 also changes|

The target's actual RSDS record again identifies `th105.pdb`, age2. That record
motivates a debug-information control but does not prove original compiler
flags. `/Zi` fails before producing a comparison with C1902, Program database
manager mismatch. Both installed manager families are read back: SP1 DLL/core/
server report8.0.50727.762, RTM counterparts8.0.50727.42, with six recorded hashes.
The failure's runtime cause is not established by those file versions. No
successful `/Zi` compilation or equivalence claim follows; `/Z7` is a separate
successful control, not a substitute result for `/Zi`.

Successful controls record the actual cl command and pinned tool/header inputs.
They are private experiments rather than public-profile provenance. No unsigned
field, debug switch or SSE option is selected. The current source SHA256 is
`76e86737670ca41893c2b1940ae77e9f4254e863ae2424971a273634be3f66ca`.
All12 baseline comparisons include the native caller324 and color332 diagnostic
alternatives; selected native font leaves45/45/289 remain exact. There is no
new runtime/GDI, allocation-failure, aliasing or unwind claim.

## Receipts and next action

Private recipes are `capture_context.py`, `cache_types.py` and
`project_options.py` in `.analysis/font-glyph-cil-20261022/`. Complete reports
and logs are under `build/font-glyph-cil-20261022/`: `linked-context.json`,
`cache-types.json`, `project-options.json`, `debug-manager-identities.json`,
the failed `pdb-zi-compile.log`, and full target/source disassemblies. Only the
configured color result is strict linked acceptance; the glyph comparison is
explicitly diagnostic. Six finished private COFFs are archived and every member
hash is read back before removing loose copies; public objects remain present.

The successful field, debug and SSE controls close these specific hypotheses
without changing the14-byte residual. Preserve the selected source and avoid
further equivalent-expression enumeration without a new ownership/lifetime
lead. Next return to Reimu496540's actual call-surface differences and reconcile
target/source behavior rather than inferring correctness from total call counts.
Strict totals stay1376 functions/233560 bytes. This is no new all-unit cold
replay claim; the preceding11-unit/23-function replay retains its actual scope.
