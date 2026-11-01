# Complete Arcade round finalization source

The existing CBattleManagerArcade::finalize_arcade_round_473110 is now formally
authored/source-present. No C++ statement, header, compiler flag or helper
implementation changed. It remains nonexact.

## Complete extent and independent owner

The original Japanese 1.06a body [473110,47321E) contains all 89 reachable
instructions, 270 code bytes and the RET0 at 47321D. Code SHA256:
495bd0881bdb435fe31e51bbba69266cdbbeee050b655f2ac7e63e2a17e858d1.
The nine-entry switch table at 473220 is separately bounded by the unsigned
CMP 8 / JA guard. Every entry reaches an instruction in this body; all code is
reachable after accounting for those table edges. The 36-byte table and two
alignment bytes are not added to authored code credit.

Fresh exact Arcade transition 473250/231 calls the function at 473300.
The existing setup override 473520/842 in the same source also freshly passes.
The scoped authored-origin rule validates the complete target hash and exact
owner edge. This is game policy, not a generated container implementation.

The source reads the real checked opponent-list front at +5B4, publishes the
opponent character and alternate costume into MatchSetup, chooses stage/BGM
from ScoreData flag 100 and the player's character or the current round's
nine-entry stage policy, applies character-six stage override, configures
PlayerSlot input payload, and requests scene four. It neither erases the
opponent nor advances the round counter.

## Whole source and unchanged limitations

Fresh source emits 264 code bytes / 87 reachable instructions, followed by its
36-byte table. Its 300-byte section tail must not be mistaken for code size.
Source code SHA256:
e3bee97dcc1570cc7835b44751b637889a13f1cf9d8e95aa8d565876a789c0a0.
Canonical complete source payload SHA256:
3595608b3c2a9024b3560a3ccdd6783b23e1cbc956bfeacc307d2af85b14f843.

The formal comparator first differs at entry: native saves EDI, source EBP.
In both dynamic stage/BGM paths the source coalesces two real cdecl stack
cleanups into one ADD ESP,8; the original uses two ADD ESP,4. These known
register/TU differences remain. No controls were retried and no artificial
barrier, volatile storage, register assignment or assembly was introduced.
The mixed unit's mismatch result is expected, not a whole-unit exact pass.

Reproduction:

    taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py --unit cross-v106a-battle-manager-arcade-setup-override --compare --json
    taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py --unit cross-v106a-battle-manager-arcade-transition-override --compare --json

Receipts: build/frontier-arcade-finalize-source-20261101/formal.json,
transition.json, boundary.json and native.txt/source.txt. The private audit
checks both complete CFGs and actual switch entry ownership.

Source1786/authored1806/mapped1813/excluded1798/review423/units765.
Exact1585/449721 authored bytes stays unchanged. matches.csv is unchanged.
