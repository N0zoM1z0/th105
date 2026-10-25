# YukariObject update58DB80: complete source and early comparison

`YukariObject_update_action_state @58DB80` now has a complete manual source
hypothesis in `src/characters/YukariObjectUpdate.cpp/.hpp`, covering32 nondefault
actions and the default exit. It is source-present, **not canonical exact**.
The first complete compile is compared before source-shape controls. Formal
and independent cold compilations reproduce the selected34600-byte complete
section, replaying970 relocations. It differs from the34800-byte target at32568
unmasked positions, first58DB82/+2: source frame0x264 versus native0x260.
Complete canonical SHA256:
`4f166c483d8ec0535feea45eff69999ee49a766a4adfb03fdfb90cb0e13b2c21`.

All20 destination-table dimensions/157 DWORDs and200 action-remap bytes agree.
Those observations establish neither byte nor execution equality. No exact
credit, shared header/profile change or aggregate cold claim is added.

## Observed target and boundary

Only original Japanese1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. Primary Object vtable6C5844 slot28 cell6C586C names this update.
The same owner's initializer5964C0, cell6C5880, is separately source-present
and nonexact. It supplies a family hypothesis, not acceptance of this root.

| Region | Reviewed extent |
| --- | --- |
|Leading separation|58DB7C..58DB7F /four INT3 bytes|
|Callable|58DB80..596033 inclusive /33972 bytes|
|Primary destination table|596034..5960B7 /33 DWORDs|
|Actions800..999 remap|5960B8..59617F /200 BYTEs|
|Secondary tables|596180..59636F /19 tables /124 DWORDs|
|Next independent helper|596370 /accepted323-byte shared action980 helper|

There is no remap alignment byte or separating INT3 after the complete payload.
Do not extend this update into596370 merely because the next helper is adjacent.
Its independent323-byte SHA256 is
`1ae566c8e8a9230cc7ce1ff75a2b472ef0b4886b1f63786506b2735dadecd7bc`;
its implementation belongs to `ObjectAction980.cpp`/`gpt-web-object-action-980`.

Callable SHA256:
`8b43493cedfa766b141c4834245b7a8c2d68a63900d0da6734657ba3dde5678e`.
Complete34800-byte payload SHA256:
`d809538c763402e688b3a7ebf53c58ab67ebec0ac5e552b745495947c334ee64`.
Raw CFG traversal reaches all7985 instructions/all33972 callable bytes,
including88 RET0s,272 direct calls to24 entries and45 virtual calls. There
are no unreachable instructions, external branches or tails in this reviewed
root. Every destination DWORD points to a decoded instruction start.
The secondary table sizes in address order are4,9,5,6,9,7,12,7,5,5,5,5,6,6,14,6,4,5,4.

The default entry596024 calls4351C0, ignores AL, restores EDI/ESI/EBP/EBX and
ESP0x260, then RET0. It does not decrement lifetime330. This differs from
other giant roots' common retirement/default policies. The target audit
checks the actual instruction sequence; synthetic controls reject an added
AL test, a lifetime write or the wrong callee.

```sh
taskset -c 0 nice -n 10 scripts/repo-python \
  scripts/audit-yukari-object-update.py --target-only
scripts/repo-python -m unittest discover -s tests \
  -p test_yukari_object_update_audit.py -v
```

The ten synthetic tests also cover all20 tables, the last action999 remap
byte, an invalid last index, metadata destinations, truncated tail, escaping
CFG edges and exact unreachable-byte accounting. Fixtures contain no game
bytes. Target-only success is observation evidence, never source acceptance.

## Analysis provenance and ABI

`scripts/check-ida-mcp.py` rejects the GUI session because its SHA256 is
10350095... rather than the required56350024.... No GUI analysis or writes
are used. Raw disassembly comes from the independently hash-attested PE.

One serial readonly/noanalysis direct Ghidra hypothesis run uses384MiB heap,
one pinned core and the existing target-imported project through a temporary
alias. Executable/import hashes, entry68B9D2, all mapped PE bytes, root extent
and temporary metadata readbacks are checked. The first run fails on an
undeclared4065A0 cdecl view and rolls back. After adding its independently
reviewed8-byte provider signature, the next run succeeds with sentinel
`YUKARI_OBJECT_UPDATE_READONLY_ATTESTED`. All nine primary database hashes
remain unchanged after both runs; temporary root/provider entries are removed
and read back. The3826-line decompile and offset-reading worksheet remain
private hypotheses and are never compiled or promoted mechanically.

Declaration-only pointer views preserve these call interfaces without claiming
complete original classes, storage layout, inheritance identity or source names:

| Direct entry | Observed calls | Local interface |
| --- | ---: | --- |
|5575C0|21|thiscall uchar emit_repeated(int,int,int), RET12|
|520860|13|thiscall void release_auxiliary(), RET0|
|435160|23|this+4 motion set_components(float,float), RET8|
|5B0400|13|thiscall pointer position_relative(int,int), RET8|
|4351C0|15|thiscall uchar advance_frame(), RET0|
|496420|4|thiscall void replace_secondary(int,float,int,int,int), RET20|
|4963A0|13|thiscall uchar advance_six(int), RET4|
|4067D0|39|cdecl int selector_random_roll(int)|
|64CCB0|52|thiscall pointer spawn_unparented(int,float,float,int,int,const unsigned*,int), RET28|
|4963F0|1|thiscall void release_secondary(), RET0|
|496370|1|thiscall void set_secondary_alpha(uchar), RET4|
|435D60|10|thiscall float stage_surface_height(), RET0|
|4359D0|2|thiscall void publish_layout_scalar(float), RET4|
|45C030|15|thiscall void dispatch_character_wave_handle(unsigned), RET4|
|4063D0|19|cdecl double lookup_orientation_cosine_quantized_abs(float)|
|406360|15|cdecl double lookup_orientation_sine_quantized_abs(float)|
|4E0BF0|1|thiscall void turn_heading(float,float,float), RET12|
|4FCA60|4|thiscall pointer spawn_parented(same seven arguments), RET28|
|406540|2|cdecl float atan2_degrees(float,float)|
|406580|2|cdecl float square_float_value(float)|
|4065A0|1|cdecl int square_int_value(int)|
|406480|2|cdecl float lookup_orientation_sine(int)|
|64CD00|3|thiscall uchar advance_phase(int), RET4|
|53CBC0|1|thiscall void update_ping_pong_motion(), RET0|

Primary virtual slots0C/14/1C/20 are separately supported by45C390/45C220/
45C180/45C1A0. The low-word selector and frame arguments occupy four-byte
stack slots. This local facade uses short carriers admitted by the reviewed
providers, without asserting their original nominal type. Four slot0C calls
use owner348, at590F13/5912BC/5943D7/59483B; all other observed virtual calls
use the current primary object. No auxiliary virtual call is invented.
No inline float-to-byte conversion is replaced with an absent runtime call.

## Consumed packets and scalar epochs

The target reserves608 local bytes without a frame pointer or ESP realignment.
Backward dataflow through the full CFG follows the actual packet argument
slot at CALL_ESP+20. It checks all incoming predecessors, register definitions,
explicit overlapping stack writes, caller-saved register clobbers and known
callee argument spans. It finds48 distinct packet bases, four of four words
and44 of three words, accounting for592 bytes. The remaining16 bytes are
available to scalar/spill lifetimes; that arithmetic does not recover original
C++ declarations or prove allocation equivalence.

A nearest-LEA-only reading misses six consumed packet bases at shared calls:

| Call | Native incoming packet bases relative to entry ESP |
| --- | --- |
|58F196|-460 and-484|
|58F2B0|-60, -276 and-132|
|5951A8|-424, -508, -496 and-472|

The manual body retains all48 used packet views and their real stores. It
adds no inert arrays, unions, padding or stack offsets to force the allocator.
The private dataflow script is bounded evidence under the recorded calling
conventions, not a general alias or path-feasibility proof.

Target58F1E9/593651/595230 explicitly rounds18.0-field370 to float before
adding that value to itself. The source now uses float width temporaries at
all three sites. Initial double temporaries omitted this observed rounding.
The natural default x87 compiler path already retains all three pre-height
qword capture/comparison pairs:58E88E/58E897,591294/59129D and5923CC/5923D5.
No declared aligned double or artificial spill is introduced to force them.
821 also retains the y-square/x-square/int-square sequence and the saved
heading pointer across its first opaque atan2 call.851 uses the observed
absolute-distance operation. Trig-position requests capture their passed
facing before both opaque trig calls and reload signed facing later for
horizontal arithmetic, matching the distinct native epochs.

Mutable float bounds6FBD1C/6FBD24/6FBD20 remain external runtime storage,
not constants.104 address/width-pinned floating aliases and three bound aliases
are exclusive to the new unit. The existing int match selector6FA894 binding
is reused unchanged. No accepted unit's mapping or header is changed.

820's nine-way phase table maps phase4 to58FCCB, whose native comparison is
still against5; phases5/6 go directly to the common continuation. The source
keeps the observed unusual comparison instead of silently moving its scale
operation to5. The original TU/context explaining this condition is unknown.
940's interval is only assigned for global selector0..3. Valid-domain proof
and behavior for other selector values remain unknown; no fake default value
or return is added to pretend the ambiguity is resolved.

## Complete comparisons and controls

Artifact prefix: `build/exact-first-yukari-object-update-20261025/`.
Private source/recipes: `.analysis/exact-first-yukari-object-update-20261025/`.
All comparisons use the complete normalized section including metadata;
there are no masks or separately accepted actions.

| Complete candidate | Bytes / canonical SHA256 prefix | Result |
| --- | --- | --- |
|first-complete|34628 /90b755ed|First whole comparison;32507 differences/+2, before controls|
|shared-ring|34412 /38171b2e|Unselected: merging both trig computations loses one physical sine and cosine call|
|rounded-width|34652 /355b4365|Retains three target-observed float rounding points|
|shared-call|34532 /9161de55|Independent trig paths, shared final812 spawn/event; remaining epoch review needed|
|scalar-epochs, selected|34600 /4f166c48|Retains passed-facing/heading epochs and native abs;32568 differences/+2|

Native812 arms have independent trig calculations but share only their final
spawn58F196 and event58F1A3. The selected source expresses precisely that
continuation. It preserves52 unparented requests,15 events and19/15 cosine/
sine calls. Sharing more of the ring calculation is rejected from direct
instruction evidence, regardless of its smaller output.

Selected source has269 direct calls versus272,44 virtual calls versus45,
98 RETs versus88 and frame0x264 versus0x260.22/24 direct-callee physical
counts agree; emit_repeated20 versus21 and advance_frame13 versus15 remain.
Per-action static reachable-call inventories differ for800 (emit2 versus3),
816 (virtual2 versus1) and852 (virtual1 versus2). Other actions' counts agree.
These counts do not establish path feasibility, side-effect ordering or
behavioral equivalence. They identify physical sharing/return investigations;
no size/count score is used for acceptance. No compiler flag/register grid,
large runtime matrix or original-LTCG-impossibility claim is made.

Reproduce formal callable and full-payload results:

```sh
taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py \
  --unit exact-first-yukari-object-update --compare --json
scripts/repo-python scripts/audit-yukari-object-update.py
```

Both correctly return1 for the recorded nonexact result. Independent cold:

```sh
TH105_ENABLE_GS=0 TH105_FP_MODE=default TH105_INLINE_MODE=default \
  taskset -c 0 nice -n 10 scripts/compile-unit.sh \
  src/characters/YukariObjectUpdate.cpp \
  build/exact-first-yukari-object-update-20261025/cold.obj
scripts/repo-python scripts/compare-unit-object.py \
  exact-first-yukari-object-update \
  build/exact-first-yukari-object-update-20261025/cold.obj --json
scripts/repo-python scripts/audit-yukari-object-update.py \
  --object build/exact-first-yukari-object-update-20261025/cold.obj
```

The existing-object comparison honestly reports build provenance unverified;
the separate compile command/log supplies that provenance. Formal and cold
full audits agree on34600/4f166c48 and32568 differences. Receipts are
`formal.log`, `formal-full-audit.json`, `cold-build.log`, `cold-compare.json`
and `cold-full-audit.json`. Target provenance is in `target-audit.json`,
`raw-facts.json`, `packet-predecessors.json` and the two Ghidra receipts;
`control-receipts.json` records source/header/object/report hashes.

Next inspect the actual scalar/frame and physical800/816/852 sharing evidence.
Do not force the missing four frame bytes or retry a broad shared-ring/flag
search. A follow-up requires an independently observed question and another
complete comparison. Current tracking is mapped1581/source1562,601 units/
1569 configured functions. Accepted1412/381108 bytes/524 units stay unchanged;
the latest aggregate cold receipt remains the prior Remilia checkpoint,
`build/exact-first-remilia-action-entry-20261025/cold-all.log`.
