# Three complete design-object virtuals; genuine texture-provider hypothesis

Target: original Japanese TH10.5 v1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
This checkpoint accepts **three distinct functions/nine bytes**. The larger
design loader and gauge initializer remain nonexact.

## Observed identity and exact result

CDesignObjectBase RTTI owns primary vtable6D6A60. Its seven cells are
40AE80/40AE70/40AE70/40AE70/40AE50/402810/40AE60. The real tag1 loader factory
constructs this18-byte type, including its concrete empty virtuals. Current
`DesignBaseLoad.cpp` already contains their genuine inline definitions and
materializes their COMDATs; no source instruction, dummy implementation or
forced emission is added.

| Entry | Ownership and behavior | Complete result |
| --- | --- | --- |
|40AE50|Base render-offset slot10; ignores two floats|3/3 exact; RET8|
|40AE60|Base parameter slot18; also inherited by CDesignGage and CDesignNumber|3/3 exact; RET12|
|40AE70|One physical body shared by the three base color slots4/8/C|3/3 exact; RET4|

Each body is one complete instruction followed by13 alignment INT3 bytes.
Only the three-byte callable is credited. The representative set_color source
symbol accounts for40AE70 once; its color-array and multiply aliases do not
receive additional functions or bytes. The source-facing three-word parameter
signature is compatible with the related sprite setter; the first two nominal
semantic types and unique original API/source spelling remain unknown.

```bash
python3 scripts/build.py --unit gpt-web-design-base-load --compare --json
# Three exact3/3 results; expected overall exit1 for the two pending functions.
```

The same fresh receipt retains40B000's unqualified local EH failure and
41B280's360-byte nonexact+5 result. They receive no exact credit. Selected
loader source SHA256 remains
`0702b0758d231a105cf3dd7aa59d3e4f13bef26f79353bc370e985cca2efbec3`.
The canonical ledgers and native vtable ownership establish authored context;
all199 predecessor origin selectors remain unchanged and disjoint. There is
no shared header, existing source or relocation-ledger change. Only this
affected unit needs replay; no aggregate exact replay is claimed.

## Genuine texture provider, deliberately unselected

`src/ui/TextureHandleRuntime.cpp` retains a complete C++ alternative for
public release404D70, native token recycling405200 and normal lookup417800.
It uses actual native deque/vector/list storage, the generation token,
critical-section operations, RAII lookup lifetime and typed COM release/cache
dispatch. Guarded offsets reproduce the64-byte token-manager prefix. The
existing84-byte raw owner is viewed through that prefix; original nominal
class/template spelling is inferred. No assembly or external private-register
declaration is used.

The actual public release definition and member callee are compiled together.
LTCG naturally places the recycling receiver inEAX. Its complete167-byte
diagnostic, including all four named REL32 fields and both IAT references,
equals target SHA256
`f225dfcb190c5b55cba3f65a784ba7a244a15da3670549afac6573f6c4166421`.
That is **not new accepted credit**:405200 already has an independent accepted
unit, and the alternative caller source is not selected in the ledger. The
formal private-caller gate correctly refuses that missing selection; no gate
is waived to create a new exact claim.

Public release remains119/115 nonexact at404D78/+8 in both ordinary and linked
contexts. Register-save placement on the null-handle path and loop alignment
differ. A genuine outer-if return control gives113 bytes and a byte-result
local gives108; neither matches. A file-local static helper also loses unique
CIL-file identity in the linker map. The retained ordinary member definition
keeps actual ownership visible, without an invented calling convention.

The provider is therefore **unselected source**, not a replacement for an
accepted function. Existing accepted release/recycling sources and units are
unchanged. The normal lookup's GS/EH and private vector-at boundary remain
unqualified in this alternative context; it is not canonically accepted.
Provider source SHA256:
`6c22a79d2a9a4ce1c04966f5b70607d16854c13646348aedc606e67304c71303`.

## Evidence and remaining work

Fresh preflights and the target/vtable/CFG acceptance recipe are under
`build/design-object-empty-virtuals-20261021/` and its corresponding `.analysis/`
scope. Texture-provider controls and source-owned linked images are under
`build/texture-release-cpp-20261021/`, with the retained source build in
`retained-provider/`. The complete public119-byte mismatch and167-byte
diagnostic are separate receipts. Generated products are not committed.

IDA again fails wrong-image attestation; new facts come from the canonical PE.
Builds remain serial on CPU0 at nice10. Next: resolve public release's genuine
source/TU behavior before using this provider to close CDesignBase cleanup or
the loader; continue gauge/reconstruction work without counting diagnostic
equality as acceptance. Reimu496540 remains nonexact at49655F/+31.
