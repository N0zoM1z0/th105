# Common Fighter action initialization: 2026-10-25

`CommonFighter_initialize_action_entry @ 0x00477830` now has complete selected
ordinary C++ source. The formal VC8 build emits5305 bytes against the full5521
target payload and remains nonexact, first difference+0x14. No exact credit.
All physical direct-call counts, seven zero-motion tail sites, three table
dimensions and336 remap bytes agree. Independent cold compilation reproduces
the selected payload. This is a source-present checkpoint, not acceptance.

## Observed target and ownership

All evidence uses the Japanese1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
IDA preflight still rejects the GUI database's different executable. No IDA
read/write or Ghidra session is used for this scope. All1272 linear main
instructions were read from the hash-attested PE.

The main `[477830,478B21)` is4849 bytes, SHA256
`dada4fa5c18e788409cb4ccf88e313b61aff32de4936d602cd8f8c24895a0181`.
Resolving all three indirect switches closes1268 reachable instructions,
4830 reachable bytes and46 RET0s. The19 unreachable bytes are alignment LEAs/
NOPs at477D48..477D4F and477F15..477F1F. The only external normal jump target
is the real zero-motion helper45AF40, reached through seven physical tails.
There is no GS/EH frame. PUSH ECX reserves a real four-byte temporary; EBX,
ESI and EDI are saved, and ECX is the receiver. A void source view preserves
the observed callable use without claiming an original nominal declaration.

Full `[477830,478DC1)` is5521 bytes, SHA256
`2c1fe83f0501890e1eae9507b1a27c3a0a6d5d99577d4d341d706872162b2b49`.
It includes the main, four alignment bytes and this complete metadata:

| Destination table | DWORDs | Input range | Remap start/bytes |
| --- | ---: | --- | --- |
| 478B24 | 50 | 0..226 | 478BEC /227 |
| 478CD0 | 16 | 100..115 | direct; no remap |
| 478D10 | 17 | 691..799 | 478D54 /109 |

The83 destination words contribute332 metadata bytes; remaps contribute336.
The next candidate478DD0 and padding after478DC1 are outside this payload.
Metadata is compared, but does not extend callable/authored code credit.

Actual Alice4F9850 default tail4F9E55 (`e9d6d9f7ff`) and Reimu491C40 default
tail492B04 (`e9274dfeff`) enter477830. Alice is accepted exact, Reimu complete
source-present. Game action/input/card-level/effect policy and these real
incoming edges establish authored common Fighter behavior independently of
library callees. The new origin rule pins the main hash and both edges; the
full comparator separately pins the complete payload hash, including metadata.
No aligned477830 pointer was found in `.rdata` or `.data`; a particular RTTI
class identity is not established.

## ABI and complete source review

The pointer-only `CommonActionEntryView` has the observed slot8 action setter
and declaration-only helpers; it is never instantiated or embedded as a full
owner. `CommonEntryCardSlot` describes only the returned short prefix.
The deque view is used only at receiver+55C, with actual4399C0 returning the
slot reference for index0. No container implementation credit is claimed.

Physical CALL counts are435240 effect22,4359D0 scalar2,4359F0 event4,
4399C0 deque1,45AF40 zero-motion20,45DEB0 sequence-window6 and473F90 secondary
effect-cycle4. There are three virtual action calls and seven45AF40 JMPs.
Every declared target is explicitly bound to its observed address.

Width evidence is independent of root code generation: manager6C1490 slot0C
points to437C00, which reads direction as a byte at437C3F. Actual EffectObject
vtable cell6C14C4 points to435200, whose first instruction reads a short from
the argument stack before storing action13C. Ordinary C++
`scripts/native/common_effect_width_forwarder.cpp` forwards short action,
float coordinates, byte direction and trailing integer with real this context.
Independent compilation matches all52 bytes of435240, SHA256
`766e73525d2dfc9742f5e6e054a58e61f65b5def458e9c42a3aff78b2c075fd8`.
This is an ABI witness; no extra helper match/implementation is recorded.

Review retained several differences from the related Reimu initializer:

- Actions6/7/8 test unsigned nonzero32-bit6C8, signed6B8 and facing/input
  product, not a signed positive counter. Their fallback conditionally zeros
  motion and always clears gravity100.
- Actions76/77 convert existing shorts7A0/7A2 into108/10C.76 publishes scalar2,
  and78's five201 effects use current Y while its38/59 effects use Y+100.
  Actions89/97 similarly retain their distinct current/shifted Y packets.
- Action149 leaves12C unchanged.158 clears732 while167 does not.200's47E
  write falls into201..203.223 writes47E;224..226 do not.795 only clears730.
- Action690 resets730/732 then uses signed byte55A>0 to guard deque access,
  I180=1, zero-motion and the16-way card update. Otherwise existing738 is used
  without those changes. Each signed byte increment preserves native narrowing,
  zero-to-one correction, signed upper clamp4 and three same-column -1 stores.
  The following effect consumes signed byte `[this+5C0+S738]+130`, narrowed to
  a short; the sequence-window packet is `(0,1,60)`.
- Actions692/693/694 retain independent source copies of effect/reset/window
  policy. Action704 changes ordered zero gravity to0.5; NaN skips the write.

## Whole comparisons and finite controls

Private receipts live in `build/exact-first-common-action-entry-20261025/`;
rejected source/context inputs remain in
`.analysis/exact-first-common-action-entry-20261025/`.

| Control | Full bytes | Canonical SHA256 | Result |
| --- | ---: | --- | --- |
| First complete source | 5317 | b7eefdbbcc69cdc36e2f2c4ceeeb290b37a43895dcd994e101484f2b4542ca08 | nonexact+14 |
| Action6 explicit negative guards, selected | 5305 | 2b5e64188dc23b84678c864f0be04e49f92a843e54f95d77b398651ce43945cd | nonexact+14 |
| Regional690 two-switch control | 5305 | bdf3c395d7d7faa7cd116039002ed3b9853570cdd4afcf88d94c41ee62e442af | unselected |
| Genuine same-TU Reimu caller visibility | 5305 | 2b5e64188dc23b84678c864f0be04e49f92a843e54f95d77b398651ce43945cd | whole-payload neutral |

The regional control changes five payload bytes at+F36..F3A; it is not
byte-neutral. It does not resolve the shared-return/call-copy residual. Selected
source has39 RETs versus46 and first-table offset4636 versus4852. Full unmasked
comparison differs at3962 positions including216 missing tail bytes.

The visibility control uses actual complete Reimu source and the recovered
common implementation in one ordinary TU, replacing only Reimu's default
declaration-only call with this real receiver's common method call. No fake
caller, extra input, register ABI or private export is added. Both full
payloads are unchanged: common5305/2b5e6418 and Reimu4702/e14c2c80. The private
Reimu comparison explicitly binds the now-local common method symbol to477830.
This closes that normal-TU visibility question; original source partition,
shared-tail optimization and FP scheduling remain unknown. It proves no
LTCG impossibility. Preserve receipts and switch representative absent new
independent evidence, rather than repeating context or spelling trials.

## Scoped execution evidence and reproduction

The optional diagnostic runs432 actual-root guard inputs, varying actions6/7/8,
their bit gates,6C8 values0/1/FFFFFFFF, signed vertical/horizontal inputs,
facing and47E. It executes the real27-byte zero-motion helper96 times per side,
checks actual RET0 stack/nonvolatile restoration, or stops before the real
virtual set_action call and compares its packet and complete0x900 owner bytes.

The96 card checks start at the observed16 direct table entries with the actual
ESI/EBX/EDI/EAX/738 phase preconditions and six signed-byte seeds per slot:
-128,-2,-1,0,4,127. They execute increment/clamp/column stores through preparation
of the next five-argument effect call, then stop before that provider. No
provider return or substitute callee is supplied. All528 bounded diagnostics
pass; this does not establish whole-root execution equivalence or exactness.

Run these commands serially with CPU0/nice10:

```sh
taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py --unit exact-first-common-fighter-action-initialization --compare --json
TH105_ENABLE_GS=0 TH105_FP_MODE=default TH105_INLINE_MODE=default \
  taskset -c 0 nice -n 10 scripts/compile-unit.sh scripts/native/common_effect_width_forwarder.cpp build/common-width-witness.obj
taskset -c 0 nice -n 10 scripts/repo-python scripts/audit-common-action-initialization.py \
  --width-witness build/common-width-witness.obj --scoped-native
TH105_ENABLE_GS=0 TH105_FP_MODE=default TH105_INLINE_MODE=default \
  taskset -c 0 nice -n 10 scripts/compile-unit.sh src/battle/CommonFighterActionInitialization.cpp build/common-entry-cold.obj
taskset -c 0 nice -n 10 scripts/repo-python scripts/audit-common-action-initialization.py --object build/common-entry-cold.obj
```

Full comparison commands intentionally return1 while nonexact. Five target-free
fixtures cover the direct/remapped switch mixture, corrupt final indices,
metadata destinations, truncated remaps and missing CFG edges. Their direct
table fixture caught and fixed stale preceding-remap detection: a remap must
belong after the current switch's bound comparison.

Only new source-local interfaces, a new unit and22 exclusive relocation keys
are added; accepted source/header/compiler profiles and existing bindings are
unchanged. Source-present1546/mapped1565, authored1596/review1010, units585.
The exact ledger remains1403/359740 bytes; no new aggregate cold replay is claimed.
