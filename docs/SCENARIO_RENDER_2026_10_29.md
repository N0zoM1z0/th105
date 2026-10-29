# Scenario rendering, JP1.06a

CScenarioData render457F90 now has selected complete930-byte source in
src/battle/ScenarioRender.cpp. Native and source each decode to281 instructions.
The canonical comparison remains nonexact:33 unequal bytes, first+14.
No exact credit is added.

Native SHA256:
4a83363d0de8a6689f8e0e5200af816aec5118290412f001c64a9186aca3a848.
Source SHA256:
bbb50a3988afcba679be595d5bfef8dc812a97c292246defb562709ac7aeabfa.

## Ownership and complete flow

The primary CScenarioData vtable6C2990, RTTI COL6D9474, has457F90 at slot0C
(address6C299C). The full body ends at458331 RET, with no remote code chunk.
Existing lifetime/constructor work independently establishes the524-byte
owner, empty Environment base and real SystemEffectManager at004,
TextFontOwner194 at068, TextFontConfig128 at1FC and CScript at35C.
This TU uses a pointer-only view and never constructs or destroys it.
Its sprite view is genuinely polymorphic; no vptr is written manually.

After setting blend mode1, lists338 and344 render each sprite at(0,0).
One checked-list iterator is reused. The string-keyed map32C is visited twice:
nonzero resource handles with flag0D7 equal0 first, then those with flag0D7
nonzero. Both passes invoke independently exact dynamic render454DA0 and the
ordinary checked map iterator increment435C00.

SystemEffectManager::render_each58BEE0 receives the actual two-DWORD MSVC MI
pointer to SystemEffectObjectBase::render_effect: virtual thunk454F40
(8B01FF600C) and zero this-adjustor. No callback/adjustor facade substitutes
for the C++ member pointer. The generated thunk is not counted as authored.

Blend mode1 is restored. When field324 is nonzero, a nonzero field328 draws
(8,392,632,float(double(field324)*2+392)), using field328 as color and flag1.
If byte50D is set, list350 sprites get scales(1,float(double(field324)/40))
and render at(0,394). With field328 zero and byte50D set, their scales become
(1,1) and positions(0,392). Every path finally calls result render454890 on390.

## Evidence-driven change and residual

The old private source evaluated the window scale before checked sprite
access. Native458220..458233 performs those iterator checks first, then reads
field324. Moving the real sprite pointer acquisition before scale evaluation
reproduces that ordering, including the tail's complete instruction stream.
It reduces the full comparison from82 unequal bytes to33, without adding
checks, padding, barriers or artificial locals. Native and source are identical
from458167 through the final RET; that suffix is diagnostic, not exact credit.

The remaining differences are the EBX/EBP receiver/map/end-value allocation
and the order of publishing the two map-iterator words to the stack. A genuine
map reference covering both passes is byte-neutral and not selected. The old
930/930 private observation was not an accepted match; fresh typed ownership
and focused replay preserve that distinction. Original source spelling and
whole-program allocation context remain unknown.

## Reproduction and validation

scripts/repo-python scripts/build.py --unit exact-first-scenario-render --compare --json

Receipt:build/frontier-scenario-render-20261029/formal.json.
Four new relocation records bind the complete five-byte PMF thunk and three
verified floating literals. Existing relocation records and shared headers
are unchanged; no previously accepted function is modified. The two exact
render callees are pinned as native call witnesses by the authored-origin
rule. Default CI validates the new source selection, ledgers and tooling;
this is not a full cold-corpus rebuild.
