# Iku glide exit ownership and lookup lifetimes

Selected Iku620920 source now keeps animation selection in the observed facing
arms and preserves the four final sequence8 exit leaves. Action214 has19
sequence-selection and five frame-restoration sites, matching the target
counts. Whole-root register CALLs rise166 ->176 against177 target; RETs rise
128 ->131 against131 target. Canonical59038 comparison remains
**nonexact+0x64 /620984**. These are source/ABI/CFG improvements, not exact or
partial authored credit.

## Target observations

Target is original Japanese TH10.5 v1.06a, executable SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Root `[620920,62EFBE)` SHA-256:
`abc831c6ccd95986bed811694f532ad8c8b92cb49702a7f6ce4de100b8a73dea`.
Wrong-image IDA was rejected; this bounded work uses hash-attested raw bytes.

Action214 occupies the internal interval62227D..622B41, not a separate
function. Its exit handling reads facing and uses ordered peer-X comparisons.
The positive-facing and other-facing arms select their exit sequence inside
the arm, after any facing/velocity reversal. Sequences1/2,3,4/5 and6/7 retain
their independent tests; later tests re-read the sequence after virtual calls.

Sequence3 saves WORD frame140 to730, selects9 and restores frame through
vslot1C. Its two facing selection sites join one physical frame CALL622889.
The terminal sequence8 path has four separate selection/frame/return leaves
at622A06/622A17,622A26/622A37,622A73/622A84 and622A95/622AA6. Each runtime path
still selects/restores once. The target's252-byte interval
`[6229B4,622AB0)` hashes to
`0af74f0cd2b739daaaadd813fea391d30fb824f7bb5bd1cb699f3d53058b9fe3`.

The earlier source materialized a flip boolean and selected after a common
face helper. It generated12 action214 vslot0C sites and two vslot1C sites.
An unselected control that merely expanded that boolean into facing branches
shrinks the section by28 bytes but retains those12/two sites. The selected
source combines facing and sequence selection in a private forced-inline
helper and preserves explicit final leaves. No vtable order, public ABI,
fake call, helper-return value, assembly or storage padding is introduced.

Both genuine lookup entries return ST0 loaded from a binary32 table. Raw
CALL6225AA and6225C4 are followed directly by FMUL speed73C; the sine product
is rounded afterward before its retained field/ceiling-test use. Target
`[6225A0,6225E0)` is64 bytes, SHA-256
`cce79be4243c6cc89f943cd588098056aef8a2e72fe1cf9a61439b93b5afd0b8`.
Source previously narrowed each double carrier before multiplication, causing
two extra FSTP/FLD pairs. Moving the casts to the final products recovers direct
ST0 consumption and removes four instructions/16 bytes. Final binary32
rounding remains. The double carrier declaration is unchanged and does not
establish the original lookup return-type spelling.

## Whole-root and native results

Current CRLF source SHA-256:
`d4a67cae637af672090f736282e783855d8e43bcf5b64f78b7bfd90412ebd431`.
Complete59774-byte ordinary normalized section SHA-256:
`8d1b309ebf7a582a63552820a41315d1662939d1629d21278f8cf6ea6096ef00`.
It has58618 callable-span bytes,15091 reachable instructions/58615 instruction
bytes, three internal compiler alignment bytes and1156 following metadata/
alignment bytes. All33/42/35 tables, frame400hex and zero local CALLs remain.
The seven prior identical physical-owner diagnostics survive; they remain
7/109, with no callable or partial-match credit.

Fresh whole-entry native checks for the final selected action214 source pass
**0/1034 mismatches**:451 genuine RETs,534 sequence-backend entries,19
action-backend entries and30 cosine entries for nonfinite headings. They
visit475 target-root instructions and run genuine prelude, lookup math,
conversion and helper code without injected returns. The native object and
configured unit replay to identical full59774-byte sections.

- Input SHA-256:
  `2907ac977abf0ad7b4916ab8ea79b69769476d172c81b8a5644fa31064bb0a78`.
- Target-output SHA-256:
  `a2e704a711010173c9bca362cedfafd4ba4be069be22fe1271ebd36a16fb8d81`.

The updated unordered-face calibration targets only the two glide source
regions, leaving other facing comparisons alone. Replacing the four ordered
tests with negated <= conditions is detected in28/48 qNaN-peer cases. All28
cases that reach genuine sequence entry differ;20 RET cases remain equal.
This validates sensitivity to losing ordered rejection. Post-selector frame
execution, backend/exception continuation and whole-game behavior remain
unproved; frame-site qualification is separate static ABI evidence.

The action/payload partition audit remains a conditional84-home bijection with
59 identity offsets and no issues. Aggregate homes and frame are unchanged.
Ordinary CALLs remain867 against865 target, including58 effects versus54 and
five action730 face sites versus four. Action214 still has four possible
action-setting sites versus three, because its shared-site ownership differs.
Raw target62271B..622757 also contains a repeated exit gate absent from the
current lowering; no redundant source guard is fabricated to force it.

## Genuine link and reproduction

The current real link reuses41 provider objects and rebuilds only three root-
unit inputs. SDK4399C0/42D1B0 remain94/100 exact before/after linking; the prior
five nonexact game providers and provisional406330 adapter retain their scope.
Full59776-byte linked replay closes all901 HIGHLOW fields and867 ordinary
CALLs. The59774 shared bytes differ from ordinary in only22 bytes, at offsets
53466..53480 and53481..53489: the same action730 mode-read/Y-store scheduling
change seen earlier. Two extra INT3 alignment bytes remain explicit.

Linked full-envelope SHA-256:
`a2af3a8190dc777eab361e197a495b100eeea159b2ca7b85014e032319a50733`.
Linked first59774 bytes:
`516a38fedb8a2196cd3fb350700a6e90acd1bd44077ece08e9c740ba0b9140fd`.
Linked fixed59038-byte target comparison:
`9803ff6b316225c69708c546fd9032c7358b9091ba483e89378fa1a67cb6c496`.
Its first mismatch is still620984; the image is not executed by the link probe.

```sh
python3 scripts/build.py --unit gpt-web-iku-action-state --compare --json > build/iku-glide-final-compare.json
python3 scripts/probe-iku-upper-actions.py --output build/IkuGlideFinalNative.obj --all-actions --smoke --whole --actions 214 > build/iku-glide-final-native.json
python3 scripts/probe-iku-upper-actions.py --all-actions --smoke --whole --actions 214 --control unordered-face --output build/IkuGlideUnorderedControl.obj > build/iku-glide-unordered-control.json
python3 scripts/audit-iku-full-root.py --object build/match-units/GptWeb_IkuActionState.obj --native-object build/IkuGlideFinalNative.obj > build/iku-glide-final-facts.json
python3 scripts/audit-iku-call-sharing.py --object build/match-units/GptWeb_IkuActionState.obj --partition-payloads > build/iku-glide-final-payloads.json
python3 scripts/probe-iku-action-ltcg.py --reuse --ordinary-object build/match-units/GptWeb_IkuActionState.obj > build/iku-glide-final-linked.json
python3 scripts/ci.py
git diff --check
```

The canonical build and deliberately wrong calibration intentionally exit1.
No shared header, accepted compiler flag/profile, global ABI, source partition
or relocation binding changed. Older native matrices and unrelated accepted
units are not replayed. Superseded variant objects/source copies are removed;
retain the current small link cache. Continue joint argument/suffix ownership,
including the four extra effect sites and remaining action-call sharing.
Original source/TU/inheritance, compiler phase and exceptional timing remain
unknown; no standalone/LTCG barrier or cold aggregate result is claimed.
