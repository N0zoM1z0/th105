# Shared native font class and markup lifecycle evidence

Font construction, configuration and rendering now use one actual native
194-byte C++ class. The runtime spelling `TextTextureFontView` is a typedef of
`TextFontOwner194`, rather than a separately declared prefix. All four existing
authored exact roots remain canonical: config constructor67, owner constructor
138, destructor210 and configure439. Compiler cleanup71 remains an excluded
witness. This checkpoint adds **no exact functions or bytes**.

Only original Japanese TH10.5 v1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. Preflights verify target/status/tracking; IDA rejects its wrong open
executable. Raw PE observations, pinned native compiler products and strict
full comparisons supply the evidence.

## One real class for local object lifetimes

`src/assets/TextFontOwner.hpp` owns the existing native128-byte config and
194-byte owner declarations, natural configuration/list/string lifetimes and
compile-time layout guards. Owner implementations stay in TextFontOwner.cpp.
The shared class retains config0C, list15C, native string170 and saved18C/190
coordinates. Runtime field expressions now refer to the real nested config;
no offset or behavior changes, duplicate fields, unions or vptr stores are
introduced. Method declarations are normal C++, with no private-register facade.

This is needed by actual markup411FA0: the ruby-close path constructs a full
local owner, configures it, recursively renders its stored text and destroys
it. The previous runtime prefix could not represent that genuine C++ lifetime.
The shared class lets the native compiler own the local string/list/EH behavior
instead of inventing a temporary buffer or fake owner constructor.

The runtime typedef retains existing source-view spelling, while VC8 decorated
identities correctly use the underlying TextFontOwner194. Only the two focused
runtime unit symbol bindings change names; their target addresses are identical.
Full native relocation replay confirms all five runtime bodies remain byte-
identical: begin291/728a7bf3, end168/e1daa198, text322/7087f023, glyph645/51eb276d
and accent433/d0a47cc5. Both texture candidates also remain110/50731d79 and
264/15555b85. All remain nonexact. Existing semantic regressions are retained;
identical complete programs do not require repeating those large case sets.

## Actual config constructor replaces the old facade

4113E0 is complete67 bytes/12 instructions, canonical SHA256:
`8cd7985057e9d272ac2e150bc51a39fbc459a16d77f728d5daf0148408f28cff`.
A genuine native TextFontConfig128 constructor emitted by the markup probe is
independently67/67. Its ordinary public ECX constructor also reproduces67/67
through real GL/LTCG in the owner unit, alongside the three existing owner roots.
It returns this naturally in EAX.

Its accepted name is now `TextFontConfig128_ctor`. Existing67-byte credit moves
from the retired cross-v106a-scenario-effect-config-default facade unit into
gpt-web-text-font-owner. There is one match row and no duplicate credit. The
old retained source stays an unselected hypothesis; its duration/interval/mode
labels are not adopted as original semantics.

Observed font CreateFontA/begin and ruby accesses identify config10C as weight,
110/111/112 as italic/outline/wrap,118/11C as origin and120/124 as spacing.
Thus the400 store is **weight400**, not an established duration. Config114
is initialized100000 but its nominal meaning remains unknown. Original class
spelling and TU partition remain unknown. Font functions now consistently use
the repository's `render` module taxonomy; that is not an original-TU claim.

## Full markup main-body audit

Raw traversal reaches all1744 bytes/463 instructions through RET8 at41266D.
Main-body SHA256:
`6343d2d6639459aaeadb9de2acd74ecbb0be02f8a908e4b84af385f1daeccebb`.
Actual font entry412670 calls at41276A with EDX font, ECX height_out, and
cursor/width_out on the stack. Return EAX advances the caller's text offset.
GS/EH handler6BE2A8 and associated metadata/funclets remain unqualified for
strict whole-source matching; the closed main CFG alone does not prove them.

Target-owned tokenizer delimiters are space, equals, tab and newline at6D6BE8.
The complete observed tags are:

| Literal address | Tag | Observed policy |
| --- | --- | --- |
| 6D6BF0 | br | reset X to origin+outline, advance Y by height+spacing |
| 6D6BF4 | ruby | save18C/190, assign token1 to string170, set flag16D |
| 6D6BFC | /ruby | construct/configure/render/destroy local owner, clear flag |
| 6D6C04 | accent | set16C |
| 6D6C0C | /accent | clear16C |
| 6D6C14 | color | parse six hex positions and invoke color411790 |
| 6D6C1C | /color | invoke reset4118F0 |

The target finds '>', allocates/copies/terminates a temporary char array,
tokenizes it and creates28-byte string element lifetimes in a20-byte local
container. Pinned native probe symbols/operations corroborate the interpretation
as deque<string>; nominal source spelling remains an inference. Missing '>'
returns strlen of the remaining cursor. No empty-token or short-color-string
guard is invented: the observed checked native accesses and exceptions must
be recovered rather than silently improved.

Ruby height is signed parentHeight/3. A native default config gets copied face,
flat parent start RGBs and the smaller height. When savedY>=rubyHeight,
destination is parentBase+((savedY-rubyHeight)*pitch+savedX); surface dimensions
and pitch are inherited. For a positive parent span, character counting uses
the actual SJIS lead ranges81..9F/E0..FE. Spacing uses the **byte length** width
estimate: `(span - byteLength*rubyHeight/2)/(characterCount+1)`. Both originX and
spacingX receive that gap, with originY/spacingY zero. Same optional dimension
outputs are passed into recursive text rendering. These are raw observations;
no full runtime/range/exception-domain test is claimed here.

The new identified name is `TextFont_parse_text_markup`. It has no source-file
selection, implemented row or exact row. Observed game policy, pinned body/hash,
actual incoming edge and five lifecycle E8s establish authored ownership, with
no inherited credit for CRT/STL callees or EH support.

## Diagnostic native source and next work

A private complete natural C++ prototype uses deque<string>, real owner/config,
ordinary typed provider declarations and no fake definitions. It compiles1682
bytes with a788-byte local reservation, versus target1744 and796. Its normal
ECX member/RET12 differs from observed EDX+ECX/RET8. No canonical comparison or
link is claimed: private provider contracts, evaluation/lifetime details and
GS/EH ownership still require work. The prototype remains private and is not
selected as reconstructed source or used to inflate progress.

The prototype naturally emits the target's broad native container/string
operation roles, including the first two inline comparisons and later standard
string equality calls. This is evidence for future ownership qualification,
not permission to silently reclassify previously accepted helper412A20 from
its byte shape alone. Runtime/library ownership needs its own positive audit.

Next: integrate real markup/private caller context and real color/reset/hex/
setter/blend providers, then qualify complete EH/link behavior. Reimu496540
remains nonexact at49655F/+31.

## Scope and checks

The two predecessor accepted units are covered by the replacement owner unit:
all four authored roots /854 bytes and compiler71 are cold-rebuilt exact after
final ledger edits. No other accepted source dependency/unit definition or
relocation ledger changes. Full runtime/texture programs retain prior hashes.
No aggregate cold replay is claimed.

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-text-font-owner --compare --json
python3 scripts/validate-tracking.py --require-target
taskset -c 0 nice -n 10 python3 scripts/ci.py
git diff --check
```

Frozen source/header/objects, old-unit recipe, full native inspection, markup
facts/prototype and final receipts are under `build/font-native-class-20261021/`;
private recipes are under `.analysis/font-native-class-20261021/`. Exact totals
are unchanged. The SVG's authored denominator grows by newly classified1744
markup bytes, so its provisional ratio changes10.91%->10.90% without any loss
of exact bytes. Origin review advances by one candidate.
