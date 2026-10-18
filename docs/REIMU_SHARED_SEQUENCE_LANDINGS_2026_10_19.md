# Reimu: recover the 197/658 and 198/608 shared sequence landings

The selected source now recovers both target landing memberships. Height,
motion clearing, sequence callbacks and returns group 197/658 and 198/608,
rather than the previous 197/608 and 198/658. The complete vslot+C partition
now agrees. No previously equal complete partition regresses. The root remains
nonexact, with no source-present or exact credit added.

## Observed target and inferred source

Target is original Japanese TH10.5 v1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Authored root 478FA0 is `[478FA0,48CE2E)`, 81550 bytes, SHA256
`dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6`.
Its ledger state remains unclassified/declaration-only.

197 loads EDI=2 at 47A63D and branches from 47A67F to 48A701. 198 loads
EDI=2 at 47A799 and branches from 47A7DB to 488FD5. The receiving high arms
608/658 hold EDI=3. Both shared tails query surface height, store Y, clear
motion, push EDI and call vslot+C, then return. The low incoming edges enter
the height CALL after preparing ECX; the high arms fall through its setup.
These are raw PE observations, independently confirmed by bounded Ghidra
readback after executable, entry, compiler/language, mapped .text and full-root
attestation. No saved database write occurs; all nine primary DB hashes agree.

The source inference carries the actual callback parameter in one local
`int landing_sequence`. It is 2 on the two low incoming paths and 3 in the
receiving high actions. Ordinary C++ gotos express the observed shared exits.
The int agrees with the existing `set_sequence(int)` interface and full-width
target PUSH. A private short-valued control recovered the groups but emitted
two additional MOVSX operations; it is not selected.

`ReimuActionStateDispatch.cpp` enables these complete-root exits.
`ReimuActionStateMovementAttackCases.hpp` retains the local landing body for
the independent movement and low staging methods, whose high arms are absent.
The two labels live in `ReimuActionStateHighMiddleCases.hpp` and
`ReimuActionStateHighLateCases.hpp`. No class layout, interface, compiler flag,
object partition, binding or accepted match unit changes. Labels do not claim
new original callable boundaries. Original source spelling remains unknown.

## Complete byte and ownership correspondence

Fresh ordinary object SHA256 is
`f1096e59b4c8f07b8f3fd38e8d6f16dfdbc052e7bac3a1d68854b91ca01587be`.
Generated source SHA256 is
`8020a8c37cd98566d534663bcd4c47258e34b3c6a28e656c7f270096da048e30`.
All 82808 canonical ordinary and genuine-linked payload bytes agree, SHA256
`9a97f6f55a43cf79142eabf22cf738406f8ad68c7a55732b200219e80a2dcbd4`.
The private int-valued control agrees with this entire payload as well.

A rebuilt previous source from 332fe62 reproduces its prior 82808-byte payload
`967ab8fdda07897afedf43e034bd85e0d5d756afdc915b05394f9a6977ede6c5`.
Only two eight-byte windows change: source 47A69C..47A6A4 and
47A7F8..47A800. Each retargets the taken JNE and moves its fallthrough ECX
setup. All other 82792 payload bytes remain identical, including metadata and
all seven previously recovered FIMUL sites. The new incoming branches enter
the shared ECX setup, whereas the target enters the CALL. This remaining
scheduling difference is not solved by the correct memberships.

| Complete group | Operation | Target / selected source |
| --- | --- | --- |
| 197/658 | Height | 48A701 / 48A688 |
| 197/658 | Clear motion | 48A70E / 48A695 |
| 197/658 | Sequence callback | 48A71B / 48A6A2 |
| 198/608 | Height | 488FD5 / 488F54 |
| 198/608 | Clear motion | 488FE2 / 488F61 |
| 198/608 | Sequence callback | 488FEF / 488F6E |

All 32 direct-callee partitions, candidate virtual-slot domains, aggregate
indirect sites and RETs are compared with complete membership and multiplicity.
The only membership changes are the two recovered pairs. Owned 243/243, wave
77/77 and the recovered 202/203/225/226 action10 landing remain correct.
Indirect physical counts stay 220/219; per-action deficits remain 410/416.
The six differing direct partitions remain 4351C0, 435240, 435D60, 45AF40,
473DD0 and 478EE0. Height/clear partition differences now concern low9 alone.

Prefix 81436, frame 570h, 20251 source reachable instructions, all 11 switches
and all 15 stack/request contracts remain qualified. All 2471 relocation fields
replay, as do 1281 HIGHLOWs and the separate eight-byte linker alignment gap.
Strict target comparison still first differs at +541=4791BD, in JNE4791BB.
Whole-root equality, original compiler/TU context and remaining sharing are open.

## Focused execution and reproduction

Affected execution is **0/2548 differences**: 197=384, 198=384, 608=1370 and
658=410. Stops are 2440 RETs, eight effect requests and 100 owned-object
requests. Each action executes the actual height/clear helpers, with equal
target/source counts. The existing action-family checks include their required
branch witnesses. Returning world callbacks and later volleys remain outside
this proof; no callback result is fabricated.

Root integration/default/common/unresolved740/nonflat-surface cohorts pass
0/1829. Rebuilt independent movement and low staging methods pass 0/99 and
0/59 smoke cases. No full historical matrix or all-unit replay is performed.

```bash
nice -n 10 taskset -c 0 python3 -B scripts/probe-reimu-action-ltcg.py
nice -n 10 taskset -c 0 python3 -B scripts/audit-reimu-call-sharing.py build/reimu-ltcg/ordinary.obj
nice -n 10 taskset -c 0 python3 -B scripts/audit-reimu-void-root.py build/reimu-ltcg/ordinary.obj \
  --cohort integration --cohort defaults --cohort common_return \
  --cohort unresolved740 --cohort surface_inputs
```

Private recipes, baseline rebuild, native adapter and receipts are under
`build/reimu-sequence-landings/`. The affected adapter is `native-affected.py`;
its SHA256 is `01910d4f3afc809344c9badc70367b90bdc4cf88c2fe34b4d0dc7f6b4eef8dee`.
Run it with the selected ordinary object as its positional argument. Inputs
come from the complete existing movement/high-middle/high-late family generators,
filtered to the four affected actions and excluding inherited integration cases.
Recipes and reports are private evidence, not committed acceptance units.

Heavy work stays serial on CPU0/nice10. Genuine production peaks 313 MiB;
bounded Ghidra uses a 128 MiB heap and takes 9.90s, peaking 311 MiB. Disposable
control products are removed after qualification: 38 files / 2.13 MiB. All 164
current genuine-cache files and the primary Ghidra project are preserved.
CI-created bytecode is separately disposable. See the handoff for the final gate.
