# Iku conditional exits and live surface-height argument

This is bounded source-shape evidence for the selected JP1.06a Iku root
`Iku_dispatch_action_state_vslot28 @ 00620920`, not exact acceptance.
The target executable SHA256 is
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`;
the complete `[620920,62EFBE)` root SHA256 remains
`abc831c6ccd95986bed811694f532ad8c8b92cb49702a7f6ce4de100b8a73dea`.
The wrong-image IDA preflight was rejected. No analysis database was used or
changed; the observations below come from the hash-attested PE and real COFF.

## Target observations and source selection

Action10 at `[62105E,6210A1)` calls the real frame dispatcher, tests AL, and
then has separate vslot08/RET leaves: vertical input zero selects action0,
otherwise action2. Action200 at `[6213BC,6215D6)` similarly retains separate
leaves for action212 when facing times horizontal input is positive, and
action211 otherwise, under negative vertical input. The source now expresses
these actual leaves instead of passing a conditional expression to one common
call. Each executed path still calls the backend once. These internal inline
helpers are source organization, not recovered standalone functions.

Action412 at `[626011,626299)` compares frame140 with EBX=2 using JGE;
the selected expression is now `frame_index_140 >= 2`. The equivalent previous
`> 1` expression used the candidate's constant1 register. This change alone
does **not** recover the target's landing-tail sharing with action418 at
`[6271E5,6272E2)`. Target height call626087 belongs to412/418; the candidate
still places418 in a different shared landing tail.

Target ring argument preparation `[62622F,62627E)` pushes count/payload/
variant/direction before calling the real height lookup435D60 at62625D. It
consumes ST0 directly into the outgoing binary32 Y argument, then stores raw
actor X and calls object802 spawn465190. The selected `middle_ring` helper now
places the height expression directly in the spawn argument. At candidate
626288 the real height result likewise feeds outgoing `[ESP+4]` directly;
the prior temporary FSTP/reload is gone. The float return ABI is unchanged.
StageGeometry's already accepted435D60 reads the height table and does not
modify actor position or facing. No double-return alias was introduced.

Other callers301/302/304/505/506/520/521 use actor Y directly. A private local
double-Y control did not recover the target preparation and increased the
section to59854 bytes; it is unselected. The direct argument and constant2
controls individually retained the prior59774-byte section; explicit opening
exit leaves account for the final16-byte section increase. Storage size or
physical call counts alone are not selection criteria.

Raw interval hashes, in the order above:

| Interval | SHA256 |
| --- | --- |
| `[62105E,6210A1)` | `d3ba272383d2a39bf4db137087d882169616fddb43c25532da03acfc1624a296` |
| `[6213BC,6215D6)` | `ec1ba88ea00298665b9eade6597f2491619c09822c606d17a248a612c968010c` |
| `[626011,626299)` | `0d8c439c43f8cb05b7937cf537e2d4f08ec41634144e56a25f4c140df121818e` |
| `[6271E5,6272E2)` | `cbc7f450f416975a141131d86d77e3fcf211eaba9976dc0d2458db27a9c78ced` |
| `[62622F,62627E)` | `5dbdcdce2ae11e04b4d480e9ab90e7c5baf9ceb61ee7377dba1c123476bab51a` |

## Reproduction and limits

```sh
python3 scripts/build.py --unit gpt-web-iku-action-state --compare --json
python3 scripts/probe-iku-upper-actions.py --opening-branches --output build/IkuLandingFinalNative.obj
python3 scripts/probe-iku-upper-actions.py --middle --whole --actions 301 302 304 412 418 505 506 520 521 --output build/IkuLandingFinalNative.obj
python3 scripts/probe-iku-upper-actions.py --opening-branches --control positive-steer
python3 scripts/audit-iku-full-root.py --object build/match-units/GptWeb_IkuActionState.obj --native-object build/IkuLandingFinalNative.obj
python3 scripts/audit-iku-call-sharing.py --object build/match-units/GptWeb_IkuActionState.obj --partition-payloads
python3 scripts/audit-giant-action-owners.py iku-vslot28 build/match-units/GptWeb_IkuActionState.obj --unit gpt-web-iku-action-state --json
```

Comparison and the deliberately wrong control exit1 as expected. Current
configured source CRLF SHA256 is
`7d8615e70885911f496bb287fb82884f53a5c29d7e80e072ecf939840d5abf2c`.
The full59790-byte normalized section SHA256 is
`0bfac4bd1cd00be448bbc61139f3456e7dc6e4743f8672e35db9575e65fff6f5`;
the native object normalizes identically. Candidate reachable instructions
15102, instruction bytes58631, callable span58634, internal alignment3,
following metadata/alignment1156;133 RETs and867 ordinary/178 register CALLs.
Target remains15132 instructions/59038 bytes/131 RETs/865 ordinary/177
register CALLs. Strict59038-byte equality still fails at+0x64/620984.
Physical-owner diagnostics remain7/109, not partial or exact credit.

The720-case new whole-entry profile passes with zero differences:412 real
action-backend entries and308 RETs,100 target-root instructions. It exercises
action200 negative/zero/positive vertical/horizontal input, both facings,
signed-short counter boundaries and both PC53/PC64 x87 control words.
Its20 action10 cases stay below the genuine frame limit and return; **the
action10 end-of-animation leaves are static evidence only**. Allowing the
real frame callback to continue reaches current-frame application436760,
which needs valid animation/render resources. No dummy callback or forced
advance result was substituted. The `positive-steer` calibration changes
`> 0` to `>= 0` and detects56/720 differences, all action200 at the genuine
action backend with zero horizontal input.

Opening profile input SHA256:
`4d4c70959a3e5d59527446f7b43d1a52daa7d918650d2c37e616a539b3d89c6d`;
target output SHA256:
`f898d49175070731112169bb882e3598885ed70d1fe4a1875260c22521a51f49`.
The focused nine-action ring/landing profile passes0/3852: 321 0x45bfe0, 13 0x45c220, 10 0x45c390, 253 0x465190, 3255 ret,
983 target-root instructions. It executes real root/prelude/helpers and stops at RET or
the first genuine backend. In412 the first object802 spawn precedes the ring,
so this native result does **not** execute412's later ring height call. Its
packing change remains static COFF/target evidence; no spawn result or manager
was faked to reach it. Other ring callers reach their genuine first spawn.
Input SHA256:
`fa813e6405e00393b5ff19547531197c0ab92fce0b305227fe3bb698b5bac432`;
target output SHA256:
`6e4356fc123907b3cbc27d6bb6f95a077aa90dbe52c737bdc25ab19d5e0d36b2`.

The action/pointer audit still closes182 physical spawn sites/190 action-site
records per image and84 singleton bijective home constraints under equal
action-group/physical-ordinal pairing,59 identity. Candidate dataflow now
visits14836 unique pre-epilogue PCs/16888 states; target14870/16959.
These constraints prove neither payload values nor feasible paths.

Generated reports are `build/iku-landing-final-{compare,branches,ring-native,
control,facts,payloads,owners}.json`. The preceding genuine link and action214
native checkpoint belong to the earlier source in
[glide exit ownership](IKU_GLIDE_EXIT_OWNERSHIP_2026_10_17.md); they were not
replayed or promoted to current-source evidence. No accepted unit, public
header/layout, compiler profile, relocation ledger or exact ledger changed.
Post-first-backend execution, exceptional timing, original source/TU and
compiler-phase provenance remain unknown.
