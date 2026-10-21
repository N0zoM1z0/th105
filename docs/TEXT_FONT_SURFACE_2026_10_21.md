# Native font surface setter and bounded provider execution

`TextFont_set_surface @ 0x00411760` has a complete45-byte/9-instruction leaf
with private EAX font, ECX surface, stack width/height/pitch and RET12.
The genuine ordinary C++ font member produces49 bytes/10 instructions,
canonical `790f7c9d09cdd1ff8ff573c29c29f8df97a5f19b9e6432c9c93e78364f443d64`.
It remains **nonexact at+1** on its normal ECX/four-stack/RET16 convention.
No register facade or exact credit is introduced.

Only original Japanese TH10.5 v1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. Required target/status/tracking preflights pass; IDA rejects its wrong
open executable, so evidence comes from the hash-attested raw PE. Full target
hash is `04b792ad4009bbc903713029ed02d712df4599ebdad9a2cfc313458837d37b06`.
All45 bytes belong to the reachable leaf through RET12, with no relocations,
EH metadata, hidden helper, cropped extent or padding waiver.

## Observations and source

The target performs five DWORD stores in order: surface to cursor144, the same
surface to base140, width to14C, height to148, then signed pitch to150.
It does not dereference the supplied surface, validate dimensions, convert
pitch units or align addresses. The chain assignment and three direct native
field assignments express the whole operation.

The reviewed tracked-candidate main-instruction census finds one call at412359
in ruby markup411FA0, supplying its local native font. This identifies game
surface ownership independently of proximity to runtime code. Original nominal
spelling/TU and indirect/remote caller completeness remain unknown. The existing
class declaration already matches the four logical parameters; no shared type
or header changes are needed. The real member body is added to the actual font
render/markup source, without forcing the target's compiler-private convention.

The ordinary source adds one load for the surface argument and uses normal
member register/stack cleanup. Recovering the observed private entry remains a
genuine closed-TU/link question. A smaller or equivalent normal member is not
accepted as a match for the45-byte target.

## Focused execution and replay scope

All **480/480** leaf cases execute complete actual target45/source49 instructions
and pass an independent five-write order/full194-byte font specification.
Inputs include null, unaligned and font-interior opaque surface values, full-bit
unsigned dimensions, and signed/zero/max pitch. Each side verifies its real ABI
stack cleanup and saved registers. No actual surface access or font/stack
argument alias is claimed.

All previous nine complete candidate bodies remain unchanged, including
parent1648/445 canonical4137c411, color332, reset161, the five runtime roots and
accepted hex45. Therefore the unchanged full8640-case parent observer sweep is
not repeated. Instead, only the **480 affected ruby-close cases** replay, this
time actually executing the target45/source49 setter at192 calls per side.
All pass, including caller-side surface propagation and the normal private/
ordinary ABI difference. The actual hex45 helper remains installed; other
CRT/STL/font/color providers are abstract observers. This does not extend to
real GDI, parent EH unwinding, allocation failure or arbitrary aliases.

The ten-function font unit cold-builds and compares its complete configured
extents: hex45 remains exact, the other nine candidates remain nonexact.
Only this accepted font unit is affected; no shared headers, flags, partition,
existing data or relocation ledger changes. No unrelated or aggregate exact
replay is claimed. Only authored/source-present ledgers gain this45-byte
function; matches.csv is unchanged.

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-text-font-render --compare --json
python3 scripts/validate-tracking.py --require-target
taskset -c 0 nice -n 10 python3 scripts/ci.py
git diff --check
```

The focused command intentionally exits comparison_failed. Selected evidence
and leaf/parent receipts are in `build/font-surface-20261021/`; private recipes
are in `.analysis/font-surface-20261021/`. Next: blend4127C0 and real font
TU/link/EH closure. Reimu496540 remains nonexact49655F/+31.
