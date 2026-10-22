# Font markup color: complete private-caller LTCG equality

`TextFont_set_markup_color @ 0x00411790` is now canonical **352/352** from
the existing genuine C++ implementation. Its full SHA256 is
`268b8440de095ca5a853314b6f4d2ba8a0b36469d9f7418f0e3cad81646e7e84`.
All111 target/source instructions and both RET16 paths are included. Only
Japanese1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. IDA again rejects the different open executable; evidence comes from
the attested PE, actual compiler/linker outputs and the reviewed source.

## The actual context that resolves the residual

`src/assets/TextFontLinked.cpp` includes the real owner and render definitions
as one pinned VC8 SP1 O2/GL/GS comparison input. The actual renderer is exported;
the actual file-local parser and color function retain their unexported entries.
No source behavior, type layout, artificial caller, library ABI declaration,
padding, assembly or inline directive changes are needed. This is a reproducible
compiler context, not proof of the original nominal class or TU partition.

The exact target call path is renderer412670 -> parser411FA0 at41276A, then
parser -> color411790 at4125DB. The source has one corresponding ordinary E8
edge in each complete caller CFG. The color function itself has a unique
primary-CIL-owned map entry and no export or alias. Its five E8 fields replay
through actual linker identities: array new, Buynode, Incsize and two checked
list-front invalid-parameter calls. No other bytes are normalized.

Private caller visibility naturally gives the target12-byte color frame,
RGB integer homes, unused Buynode receiver removal and constant1/no-stack
Incsize call. The ordinary COFF alternative is332/+2. Forcing an ordinary
export of the same color definition gives343/+0 with an aligned EBP frame;
explicit Ob1 and isolating that definition reproduce the same343-byte result.
An unselected word-channel/narrowing hypothesis gives353/+0. These controls
do not replace the truthful narrow-channel definition.

The color semantics remain the earlier reviewed native list/front policy:
allocate `unsigned[height]`, insert first, fill signed interpolation from
config10C/10E/110, then publish active154. Flat mode writes fallback168 only.
Height0 inserts/publishes without filling; height1 reaches the actual divide
exception after insertion. The prior576-case native execution evidence retains
its original array/node-allocation and Incsize observer scope; it is not newly
claimed as real CRT or unwind execution.

## A bounded caller-path witness, with unchanged callee acceptance

The linked contract adds an explicit `private_from.via` path for one to four
static intermediates in one import-runtime CIL input. Its source file must be
an actual recursive quoted-include dependency, and every caller must retain a
reviewed implemented/matching row for that file. The first caller remains a
configured source-owned export. Intermediates must have unique linker static
entries owned by `CIL library: CIL module`, without aliases or exports.

Every source/target caller closes through its full CFG and supplies exactly
one declared reachable E8 edge. Caller address fields are observed without
normalization: game addresses require attested bindings; source internal
operands require complete mapped data/function roles and exact HIGHLOW field
coverage. Missing, duplicate, wrong-type or control-displacement relocations,
unreachable/truncated callers, cycles, mismapped edges, foreign sources and
exported intermediates fail. These are ownership witnesses, not caller byte,
data identity or EH equality. The existing one-edge contract stays unchanged;
the accepted color still uses the original complete canonicalizer and exact
relocation checks. Six new synthetic tests exercise the positive path and its
negative boundaries; all37 linked-code tests pass.

The selected renderer is335 bytes, canonical
`5268fdd1d1d304783735919f167119b55c3d8f33f14e45e7a66ba50f5034d6f7`,
nonexact+19. The actual CIL parser is1572/frame788 and uses EDX cursor,
ECX height output, stack font/width, unlike the target's EDX font interface.
It receives no exact or EH credit. Actual Incsize is158 bytes versus target154;
only its observed caller interface is recovered. Buynode's existing compiler
exclusion gains no authored credit. Native markup1728/frame788 and glyph624
remain pending under their existing unit/profile. The original source file
is unchanged; native input auditing follows the relocated renderer contract
and keeps both real C/COFF memset spellings.

## Reproduction and checkpoint

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-text-font-color-linked --compare --json
python3 scripts/compare-linked-unit.py gpt-web-text-font-color-linked \
  --address 0x00411790 --json
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-text-font-render --compare --json
python3 scripts/audit-text-font-input.py \
  build/match-units/GptWeb_TextFontRender.obj --output build/font-input.json
taskset -c 0 nice -n 10 python3 scripts/ci.py
git diff --check
```

The first build intentionally reports comparison_failed for the nonexact
renderer; selecting color alone still repeats both complete caller witnesses
and reports exact. Evidence/controls are under
`build/font-color-context-20261022/`, private recipes under the corresponding
`.analysis/` directory. The manifest keeps one selected unit per address:
renderer/color move to the linked unit; the other10 native font comparisons
retain their source/profile. All affected accepted linked units and native
font leaves are cold-replayed serially; no fresh all-unit aggregate is claimed.
The completed affected replay passes **11 units/23 accepted functions**; all10
remaining native font hashes/extents equal the pre-change build. Fresh native
alternatives remain caller324/1daa6415 and color332/471012e5. The relocated
native input audit passes57/57, including its existing guarded-read cases.
Thirty completed unselected control binaries are archived from2028515 to512957
bytes, with every member hash read back before removing loose files; configured
accepted artifacts remain available under `build/match-units/`.
The ledger gains one function/352 bytes:1376 exact functions/233560 bytes,
with authored denominator2135782 (10.94%). Markup, glyph and Reimu496540 remain
open; this bounded result does not imply parent or application reconstruction.
The provisional authored-origin rule is retired in favor of the canonical
match-origin row; authored/source counts and the byte denominator stay unchanged.
