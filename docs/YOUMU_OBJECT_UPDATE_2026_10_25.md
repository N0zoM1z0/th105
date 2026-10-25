# YoumuObject complete update `0x0053CEA0`

## Observed target facts

This packet covers the original Japanese 1.06a executable only, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Run the read-only raw audit:

```sh
taskset -c 0 nice -n 10 scripts/repo-python scripts/audit-youmu-object-update-target.py
```

RTTI-owned YoumuObject primary vtable `0x006C50BC`, slot28 cell `0x006C50E4`,
points to this entry. The next slot3C initializer cell `0x006C50F8` points to
`0x00543670`, immediately after the complete update payload. It is a separate
previously parked scope.

The callable range is `0x0053CEA0..0x005433F7`, 25944 bytes, SHA256
`c3334cf4f772931661dfddf7ffd6adb702b99aedf369809f11e8ec1d0171492e`.
The complete range through its switch metadata ends exclusively at `0x00543670`,
26576 bytes, SHA256
`4cc99136a6fc0fc7238c89bde5509d3504be026086b5f35a97cf219973a5911b`.
The raw traversal closes 6233 reachable instructions out of 6236 decoded,
49 RET0 sites, 224 direct calls to 20 entries and 30 primary-vtable calls.
Every direct branch and switch destination stays inside the callable range;
there is no external direct tail jump. The three unreachable instructions
are alignment LEAs at `53EE2A`, `5420DA` and `542F29`, totaling 19 bytes.
They remain part of the physical comparison extent.

The prologue aligns ESP to eight bytes and allocates `0x48` bytes, saving
EBX/EBP/ESI/EDI below that frame. It keeps the ECX receiver in ESI. Do not copy
Remilia's smaller frame or assume its four-float parameter packets: Youmu's
first action already passes five floats. The working no-argument member view
has RET0; the original source return type and full owner layout are unknown.

The metadata has no intervening gap or separator. Its 632 bytes partition as:

| Address | Contents |
| --- | --- |
| `5433F8` | 29 DWORD destinations |
| `54346C` | 200-byte remap for actions800..999 |
| `543534` | 5 DWORD destinations |
| `543548` | 6 DWORD destinations |
| `543560` | 5 DWORD destinations |
| `543574` | 13 DWORD destinations |
| `5435A8` | 4 DWORD destinations |
| `5435B8` | 4 DWORD destinations |
| `5435C8` | 6 DWORD destinations |
| `5435E0` | 9 DWORD destinations |
| `543604` | 11 DWORD destinations |
| `543630` | 8 DWORD destinations |
| `543650` | 8 DWORD destinations |

Primary cases are800,801,810,811,812,813,815,817,818,820,821,823,
848,850..857,899,900,901,902,930,980,999. All other remap entries
select the default continuation `5433EB`. Case848 is physically after899.
There is no903 case. The audit emits all remap destinations, the exact call
sites and the independently inspected virtual slots0C/14/1C/20.

## Callee interfaces under review

These are declaration-only working call views, not new helper implementation
or exact credit. The current ledgers already accept17 of the20 direct callees;
the two quantized trig lookups remain source-present, and `68A1A0` is compiler
conversion support. Call counts constrain the complete source review.

| Entry | Calls | Working view / evidence |
| --- | ---: | --- |
| `435160` | 18 | receiver+4, two floats, RET8 |
| `45C030` | 13 | owner dispatch, unsigned index, RET4 |
| `64CCB0` | 58 | unparented spawn, seven stack words, RET28 |
| `5575C0` | 8 | repeated emitter, three ints, AL result, RET12 |
| `4063D0` | 10 | cosine lookup, float input, ST0 result |
| `4351C0` | 16 | frame continuation, AL result, RET0 |
| `68A1A0` | 8 | compiler float-to-integer support |
| `4FC710` | 3 | bounds descriptor, four ints/three shorts, RET28 |
| `435240` | 1 | effect code/two floats/direction/trailing, RET20 |
| `5B0400` | 4 | relative-position helper, two ints, RET8 |
| `4963A0` | 10 | six-counter conditional continuation, limit, RET4 |
| `4067D0` | 49 | RNG limit, integer cdecl result |
| `64CD00` | 4 | phase continuation, limit, RET4 |
| `406360` | 11 | sine lookup, float input, ST0 result |
| `406540` | 3 | atan2, two floats, ST0 result |
| `53CDF0` | 1 | owner-history record application, unsigned index, RET4 |
| `4E0BF0` | 1 | heading turn, three floats, RET12 |
| `406580` | 3 | square float, float cdecl/ST0 result |
| `53CBC0` | 1 | ping-pong motion and periodic spawn, RET0 |
| `435D60` | 2 | ECX receiver, no stack input, ST0 height, RET0 |

Do not infer a bool domain for `4351C0`: it returns AL from a virtual callback
on its nonzero exit. Likewise, `64CCB0` forwards its complete direction DWORD
through a virtual manager call. A byte load at one call site does not prove
that changing all directions to byte parameters is safe. Each caller's
signed or unsigned extension must be preserved.

## Optional analysis hypothesis

IDA preflight still rejects the GUI's different executable SHA256
`10350095bcf95edb59e03bee9849a2dc8a7714b4927ad5909c569c550fce6822`.
No IDA data or writes are used.

A single direct Ghidra headless process ran readonly/noanalysis, CPU0/nice10,
one CPU and384MiB heap. Before decompilation it independently attested the
imported SHA256, PE image/entry/language/compiler and all four mapped sections,
then the complete raw callable hash above. Temporary entry/body and ABI views
were read back; root metadata was removed/restored in a rolled-back transaction.
All nine primary project-file hashes agree before and after. The initial pass
stopped because the working DB lacked the already accepted `406580` entry;
its transaction rolled back and project hashes remained unchanged. The second
pass added that target-bounded temporary view and completed. No new import or
analysis process was launched concurrently.

Private receipts live under
`build/exact-first-youmu-object-update-20261025/`: `raw-facts.json`,
`target-audit.json`, `ghidra-receipt.json`, `ghidra.log`,
`primary-db-before.json`, `primary-db-after.json`, and `decompile.txt`.
Decompiler output is only a hypothesis. It does not establish signedness,
rounding, callback read epochs or source lifetimes without instruction review.

## First complete source and early comparison

The complete manual compiling hypothesis is now retained in
`src/characters/YoumuObjectActionState.cpp/.hpp`, using numeric states,
typed offsets and declaration-only helpers. It includes all28 non-default
actions plus the default continuation; it is not pasted decompiler output.
The durable role mapping is `YoumuObject_update_action_state`. The ledger
remains `identified`: further instruction/source-shape review is required
before selecting it in `implemented.csv`. There is no source-present or exact
credit from this checkpoint.

```sh
scripts/repo-python scripts/build.py --unit exact-first-youmu-object-update --compare --json
scripts/repo-python scripts/audit-youmu-object-update.py
scripts/repo-python scripts/audit-youmu-object-update-paths.py
```

The build succeeds. Both strict comparison commands return1 for the current
nonexact body; that expected result is separate from the mandatory CI gate.
The payload audit replays every section relocation, including any candidate
tail beyond the target length. It compares every byte, without masking or
rebasing jump destinations. Ten new literal keys are pinned to actual loads
and current target bytes; existing mappings and accepted source are unchanged.
A read-only inventory of all515 cached accepted-unit objects finds these new
keys only in the mixed `gpt-web-reimu-object-action-state` object. A fresh build
and accepted-only replay retain its sole accepted member4963A0 at66/66 bytes,
SHA256 `ad12b782ed5fc99007456fc66a9615951cee34178850a308316409c5245bb156`.
Receipts are `new-literal-impact.json` and `affected-exact-replay.json`. This is
an affected-unit replay, not a new aggregate cold-total claim.

The first complete object was compared immediately:26800 emitted bytes,
canonical SHA256 `6ec1e75eb500a0c564d4744c2fb3a3b2d3147953f5e579c982bf94d2139b6dfa`.
Its200-byte remap was already equal and19 of20 direct-callee counts agreed.
This exposed one duplicated virtual sequence-block call. Reviewing its target
edges showed that857 must join902's sequence transition and immediately return;
the first hypothesis incorrectly continued into frame advancement. The natural
shared exit restores30 virtual calls and removes that semantic error.

The eight native930/3 prefixes then rejected the positive-only bounds spelling
on NaN: the target continues into the frame callback, whereas the hypothesis
retired. Target820 and both930 movement-bound sequences use ordered outside
comparisons; those three locations are separately checked against their x87
flags/branches. The corrected hypothesis retains the target continuation.
Ghidra's positive-inside spelling was not reliable evidence for this behavior.

The first retained complete hypothesis had26780 bytes, canonical SHA256
`cb35d0d8d48b2a2c942458a8584d1f783696440dfbe89b3ead331e40236c10cf`.
Formal and independent fresh-object payload audits reproduce it. The first
difference remains+8: frame `0x40` versus target `0x48`. There are24446 unequal
byte positions including the204-byte size difference; this is not a matching
percentage. Physical inventories remain:

| Property | Target | Hypothesis |
| --- | ---: | ---: |
| code/alignment before first destination table | 25944 | 26164 |
| metadata bytes | 632 | 616 |
| destination tables | 12 | 11 |
| RET sites | 49 | 57 |
| frame-advance calls4351C0 | 16 | 13 |
| other19 direct-callee counts | reviewed | all equal |
| virtual calls | 30 | 30 |
| action remap | 200 bytes | byte-equal |

The missing four-entry dispatch table belongs to899's second identifier
switch. A finite control giving its period a separate local emits26784 bytes,
SHA256 `32c2878cf104ece39a93ea195dac11eba199f1d8f2d7ece1fa20d33e70555ac1`,
and still has11 tables/the same call-count differences. It is unselected.
This is not byte-neutral and does not close the original source/context question.
Do not repeat that same local-period spelling as a new experiment.

## Scoped native evidence and remaining work

The public native diagnostic executes original square/trig instructions up to
the first spawn or frame call. It injects no helper results, instructions or
transfers. Four explicit coordinate pairs use the mapped PE's zero-initialized
lookup fixture under both53-bit and64-bit x87 precision: boundary
`(0,50)`, just outside `(0.01,50)`, just inside `(0.01,49.99)` and quiet NaN.
Another three pairs use an axis lookup fixture: table6FE8B0 index0 is1.0,
index900 is0.0, so actual cosine0/sine0 instructions yield1/0. With dx1000,
dy50 and49.99 hit; the next representable float above50 does not hit.
This avoids relying only on an uninitialized runtime lookup table. All14
prefixes agree in boundary, owner bytes, helper trace, spawn arguments and
parameter bytes. This is not full-function execution proof.

Raw930/3 stores the first squared value and square sum as double, then retains
the sine product across the cosine lookup. Those consumed values are expressed
as real locals. A clean negative control changes only the square-sum local
from double to float. Its canonical SHA256 is
`babbd384e787e080f6e5c369f45edaea5189f413262e8731da7afb27445ba1bd`.
It fails exactly2 of the original8 prefixes: `(0.01,50)` wrongly spawns under
both precision modes. It also fails the two axis-fixture prefixes with
dx1000/dy just above50: rounding the square sum before subtracting the projected
square causes a false hit. The extended result is4/14 failures. The earlier
negative object also contained the now-rejected inside guard and is not the
isolated precision receipt.

Receipts under the build scope include `first-source-preview.json`,
`shared-block-exit-preview.json`, `outside-guards-preview.json`,
`separate-period-preview.json`, `formal.json`, `formal-payload.json`,
`formal-paths.json`, `cold-payload.json`, `cold-paths.json` and
`float-distance-only-negative-public-paths.json`.
The initial8-prefix receipts are retained with a `-zero-` label; the public
commands now cover all14 prefixes including the axis fixture.

## Finite controls, corrected expressions and parked hypothesis

The target frame-call memberships locate all three missing physical copies.
Target813/852 share53DBF9, but the candidate folds them into the main frame tail.
Target811/820/850 retain53D90E/53E394/53E87B, whereas the candidate shares one.
These memberships are CFG diagnostics that ignore branch predicates, not a
full execution-equivalence proof. A normal break exit for813/852 and independent
negative post-frame return guards for820/850 each reproduce the entire old
26780-byte `cb35d0d8...` payload. Both questions are closed absent new evidence;
do not repeat the same break/return or guard-polarity controls.

The899 second switch has four target destinations, three pointing to one
120 assignment. Writing independent case1/2/3 assignments, rather than stacked
labels, restores that fourth-entry table without changing any values or adding
behavior. Its separate control is26796 bytes/SHA256
`3d93e5385b818fd66433e5788063f141ec991d3af9096bdd94cccbf01e4ae043`.
All12 table lengths now agree:29,5,6,5,13,4,4,6,9,11,8,8. The metadata is632 bytes
again. Destination byte equality is still required by the full comparator.

The whole-function operand review also catches two unsupported expressions:

- At53D1F3 the cosine result feeds `FADD [this+374]` directly, with no intervening
  float store/reload. Removing the hypothesis's extra float cast recovers that
  flow. The independent control is26784 bytes/SHA256
  `dc1d17832632c5a6345d2df04bfd3065577b86c9b814e961cc4b85777d5cc401`.
- At540EEA the returned cosine is multiplied by `field11C*300`, then signed
  facing, then added to x. The hypothesis had multiplied facing into field11C
  first. The correction restores the target arithmetic instruction order;
  its independent control is26800 bytes/SHA256
  `b26182f0dc837f5892e8077cf689ddc4d9a5fd49e2202c29181fb56f33370c8c`.
  It is retained for target-backed expression fidelity, not a smaller byte count.

The combined retained hypothesis is26784 bytes/SHA256
`73359b445ada254b7454615891c98ab28be4bee943cd53d2668681dcfd3a5ec8`.
Formal and independent fresh-object audits agree. It remains nonexact+8,
with24412 unequal positions including the208-byte size difference. The frame
is still0x40 versus0x48, physical frame calls13/16 and RETs57/49. All12 table
lengths, all200 remap bytes, the other19 direct-callee counts and30 virtual
calls survive. These inventories are diagnostics, not an exact claim.

The original14 scoped930 prefixes still pass. An additional four900/0 prefixes
execute actual bounds publication, six-state/phase, cosine/sine/FTOL and atan2
instructions to the first spawn. They use a preallocated bounds descriptor,
axis lookup data, facing1/FF and both x87 precisions. Boundary, owner, bounds,
helper trace, spawn arguments and payload bytes agree without injected returns
or edges. Run this focused new check with:

```sh
scripts/repo-python scripts/audit-youmu-object-update-paths.py --point900
```

Current receipts have the `expressions-` prefix under the same build scope;
the finite controls retain their own named source/preview/inventory receipts.
The two byte-neutral frame controls and remaining stack/callback layout gap
justify parking this full hypothesis and selecting another complete authored
representative. It remains unselected in `implemented.csv` and absent from
`matches.csv`: remaining instruction/source/default-arm review is incomplete.
Identifier values outside0..3 reach target arms without explicit period/count
assignment; their domain/default behavior is still unknown. Original source,
complete owner layout and original TU/compiler ownership remain unknown. No
standalone TU/LTCG impossibility is established. Remilia557690 stays parked.


## Independent trig return-width control

After the Tenshi transfer-width review, a fresh build of the retained complete
Youmu hypothesis reproduces26784 bytes, SHA256
`73359b445ada254b7454615891c98ab28be4bee943cd53d2668681dcfd3a5ec8`,
24412 unmasked differences and the first mismatch at53CEA8 (frame40/48).
The native406360/4063D0 exits load one float table entry into ST0. This does not
uniquely distinguish a source float return from an exactly promoted double
return; the existing public AngleLookup implementation is also a hypothesis.

A separate complete source/header control changes only the two local trig
return declarations from double to float. All26784 canonical bytes, including
the tail tables, reproduce the retained payload SHA256 exactly. No public
source or relocation binding changes. This independently closes this width
question for the current caller and compiler context; do not repeat it without
new evidence. Baseline and override receipts are
`return-width-baseline-build.log`, `return-width-baseline-audit.json`, and
`trig-return-float-full-audit.json` in the existing build scope. The isolated
source/header/object remain in the corresponding private analysis/build scopes.

The status report's source=0 means no selection in implemented.csv. This root
already has a complete public compiling hypothesis and a closed raw CFG;
it must not be treated as an unwritten function. The remaining instruction,
default-domain, stack and physical-call-group questions stay parked. No new
source-present or exact credit is recorded.
