# Complete ScenarioData construction, JP1.06a

459C90 now has complete selected source but remains nonexact: source1528 versus
native1527, first mismatch+40 in persistent receiver allocation. No bytes are
added to exact progress. Native full-body SHA256:
959d1263fab6f0a63a75cd27bb45748ab8f43dae63d0fef659686f2a0417192f.
Full source1528-byte SHA256:
efcb7138da57cfef71cf3cd2fddd6721e4e3e1bd42d52d1b60cbbb09171c70f6.
The formal receipt hashes the compared1527-byte prefix as6511c94f7e9e6386ee923c678f6a38456155530cd951cca8cd126590ad36b52a;
its separate section-tail size correctly reports1528, including the final RET.

## Independent ownership and complete body

Exact manager/phase constructors call the entry at 00438D01, 0043926D.
All1527 bytes end at45A286 RET0, with no omitted cold path. COL6D9474 names
CScenarioData at vtable6C2990 and its Environment base at+4. COL6D9428 names
the SystemEffectManager specialization at6C288C, with TObjectManagerBase at0.
The target constructs that manager at+4, font+68, config+1FC, map+32C, three
lists+338/+344/+350, script+35C, result+390 and strings+4B8/+4D4/+4F0.
Unused scalar members are not given invented initialization.

An empty Environment base view naturally reproduces MSVC's+4 base descriptor
while leaving the actual manager member at+4. The same canonical Environment
type descriptor6E6430 also appears in the Character family at+130; this is
stronger layout evidence than the older partial Environment field grouping.
The local view does not rewrite that shared header or claim its nominal source
spelling. Its addition is canonical-code-neutral for both lifecycle bodies.

## Command registry and font

The complete registration sequence preserves each target name, numeric ID and
independently exact CScript factory specialization. In order:
- (default): 1, TCommand1<std::string>.
- Label: 0, TCommand1<std::string>.
- Character: 2, CComCharacter.
- Face: 3, TCommand2<std::string, std::string>.
- Action: 4, TCommand2<std::string, int>.
- Object: 5, TCommand4<std::string, int, float, float>.
- Stage: 6, TCommand2<int, int>.
- Bgm: 9, TCommand1<std::string>.
- PlayBgm: 9, TCommand1<std::string>.
- StopBgm: 10, CCommand0.
- FadeBgm: 11, TCommand2<int, int>.
- CrossFadeBgm: 13, TCommand3<std::string, int, bool>.
- PlaySE: 12, TCommand2<std::string, int>.
- Background: 7, TCommand1<std::string>.
- CG: 8, TCommand3<std::string, int, int>.
- Sleep: 14, TCommand1<int>.
- Next: 15, TCommand1<int>.
- Font: 16, TCommand4<std::string, int, int, int>.
- Color: 17, TCommand1<std::string>.
- Window: 18, TCommand4<unsigned char, unsigned char, unsigned char, unsigned char>.
- Hide: 19, TCommand1<int>.
- Result: 20, CCommand0.
- StaffRoll: 21, CCommand0.
- End: 22, CCommand0.

Both Bgm and PlayBgm deliberately use ID9. The embedded font config then gets
the target Shift-JIS face, height24, alternating255/0 color components,
origin0/8, spacing0/8 and outline1 before the real font configure call.

## Source lifetime and remaining difference

A direct member-access version emits1434 bytes because VC8 retains string
capacity15 in a saved register across all24 registrations. Native instead
retains the real font-config address across those calls. A named config
reference, actively used by the subsequent face/field/configure operations,
restores that value lifetime and expands the body to1528. Pointer and reference
forms are byte-identical; no inert local, flag sweep or register directive is
used. Source keeps receiver/config in EBP/EDI versus native EDI/EBP, and the
EBP-based vptr store costs one additional displacement byte. The original
nominal/TU allocation phase remains unknown; equal roles are not exact bytes.

## Focused replay

scripts/repo-python scripts/build.py --unit exact-first-scenario-data-lifetime --compare --json

Receipt:build/frontier-scenario-constructor-20261029/formal-environment.json.
The same changed-TU replay retains destructor438A70 at411/411 with its existing
19783021... canonical hash. Only the constructor gains source/mapping/origin
selection. All command literals, both native vtable roles and the complete
handler receive independently checked bindings; no shared code or accepted
caller is changed. No broad test expansion or whole-corpus replay is required.
