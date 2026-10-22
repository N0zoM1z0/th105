# Select the ReimuObject owner context for the update root

The selected source for `ReimuObject_dispatch_action_state_vslot28 @496540`
now uses an isolated17-slot runtime owner view. It restores the target's
29-byte908 float-before-integer addition and passes its2,240 live x87 checks,
while retaining800/804/869/902's scoped behavior and the other199 normal action
graphs. The full root remains **nonexact at49655F/+31**. No authored exact
function or byte is added.

## Observed target and bounded source result

Only original Japanese1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. Target/status/tracking checks pass; IDA again rejects its other image.
No IDA semantics, metadata writes or target patching are used.

The target's actual908 post-wave window is4A076A..4A0787, exclusive end:
FLD angle374, MOVSX short366, write the integer temporary, FILD, FADDP, then
FSTP angle374. Its two live x87 values before addition differ from the previous
selected27-byte FILD/FADD-memory form, despite equal tested final outputs.
The [earlier908 work](REIMU_OBJECT_908_OWNER_2026_10_22.md) records the exact
bytes, incoming-frame preconditions and callback boundaries.

The previous complete real-owner context already emitted all29 bytes, but was
private and depended on its own hierarchy headers. The new
[`ReimuObjectOwnerView.hpp`](../src/characters/ReimuObjectOwnerView.hpp)
reconstructs that runtime field/call context using namespaced view types and
existing public base storage. Existing global headers and their interfaces
are unchanged. Size/offset assertions retain owner388, parameters340,
parent34C, children350, short-work364..36C, floats370..37C and counters384/386.
Sprite position/motion/facing offsets are independently checked.

The root body now belongs to
`th105::reimu_object_model::ReimuObject`. Sprite/motion, float storage and the
actual340 pointer use the primary owner; unresolved scalar/parent fields retain
the existing staging view. Thus this is a selected runtime model, not recovery
of unique original nominal declarations, member grouping, lifecycle or RTTI.
No owner is artificially constructed or substituted as an execution witness.
The new view provides declarations and storage; it grants no constructor,
destructor, vtable-body or original RTTI exact credit.
The descendant-container specialization is a reproducing model choice; the
update does not qualify that container's original declaration or lifecycle.

The complete45,696-byte native COFF payload, including868 bytes of switch
metadata, has canonical SHA256
`4b565d714737cf5ddfdaf8ae5d9944369071899fccb70223f86f572b55a65bf2`.
It exactly reproduces the prior corrected owner payload. Public source SHA256
is `35b06db0de104e9e5bcdb12b89dbb906a18ad8b532514071c08345fe1c47b7f8`;
owner-view header SHA256 is
`c1ef76996d311670e1903cdb23052ca43703a628b1e3c4695d8ca4a59fb76874`.
Counter4963A0 remains66/66, canonical
`ad12b782ed5fc99007456fc66a9615951cee34178850a308316409c5245bb156`.

The provisional39853-byte candidate and reviewed target byte ownership are
unchanged. The complete comparison retains46138 target bytes, including46128
code bytes and10 alignment bytes. Source switch metadata is not a reason to
enlarge the target callable boundary or count a partial root as exact.

## New field observations and rejected local contexts

The complete reviewed target ranges contain93 direct, nonindexed ESI accesses
at370/374/378/37C, all four bytes and all x87 memory operations:

| Offset | Direct observations |
| --- | ---: |
|370|63|
|374|17|
|378|8|
|37C|5|

The width audit now covers26 selected fields/1251 direct operands. No direct
380 access is observed in this root. The primary model therefore keeps380 as
four unknown bytes. That is a limit of these observations, not proof that no
other function or indirect access uses it. Width/use evidence does not uniquely
determine original source grouping or base ownership.

New isolated controls start from the selected77fe73a4 predecessor with identical
ordinary flags,388 layout and real root/counter. They do not recover908:

| Private context | Full payload SHA256 prefix / bytes | Result |
| --- | --- | --- |
| Separate primary float-storage view |7afe637c /45696|Still27-byte integer-first908|
| Same, removing unsupported unused380 float declaration |Same|Still27 bytes|
| Secondary scalar-counter view |854db777 /45696|Still27 bytes; reproduces prior scalar-owner negative|
| Existing sprite reference at this+4 for177 facing accesses |9e0e7b68 /46044|Unsupported extra entry LEA; still27 bytes|
| Existing animation-member view for the same facing accesses |4d0ac180 /45696|Entire predecessor payload unchanged|
| Isolated complete owner context |4b565d71 /45696|Selected;29-byte target window|

The float-only control is freshly executed through the2,240-case908 audit and
fails every live snapshot, as does the predecessor. Simple field spelling or
a local view is therefore insufficient in these measured contexts; the
complete owner preserves the needed optimizer context. This does not establish
an impossibility for all other source/compiler contexts. No fake return,
padding, inert local, register facade or compiler flag change is introduced.

## Fresh actual-instruction regressions

The new compiled owner and later selected public object receive the existing
target execution matrices under their documented scopes:

| Audit | Cases | Qualified behavior |
| --- | ---: | --- |
|800 prefix|2240|Actual5575C0 gate to real435160 entry, parameter-first x87 lifetime|
|804 lifetime|5120|Real animation, bounded full-RET paths, velocity/live x87 states|
|869 prefix|3072|Parameter-first addition and explicit alias case|
|902 products|1792|Five facing-first products;768 real atan2 returns,512 RET paths,256 spawn-entry stops|
|908 window|2240|All29 bytes, live x87/tags, ordered writes and FPSW|

All14,464 primary cases pass. The old public object's908 contrast retains its
2,240 snapshot differences. The908 experiment starts at an independently
specified arithmetic entry with ESI owner, writable ESP+20, empty x87 and
masked control word; it does not fabricate a return from the preceding spawn
or wave call. None of these receipts establishes unmasked exceptions,
arbitrary incoming x87, returning opaque callbacks or whole-root equivalence.
Binary execution packets do not themselves verify source-to-object provenance;
the actual build receipts and matching full payload are checked separately.

Fresh source-to-source graph comparison preserves the dispatch prefix and199
non908 action entries plus default:9,344 paired semantic nodes. It contracts
only direct JMP and identity register LEA/NOP, preserves labels/edge counts
and checks switch index bytes. This is normal source regression evidence,
without a target-matching or EH waiver. The ordinary full comparator retains
every byte and remains nonexact. Physical source428 calls/63 RETs versus target
433/68 and their tail sharing remain unresolved.

## Selection, tooling and reproduction

The unit selects the new namespaced source symbol. Two direct-member aliases
bind the same observed helpers at4359D0 and5F9310; the legacy view aliases remain
for explicit old-object diagnostics. They introduce no replacement provider.
The shared execution auditor reads its default symbol from the configured
496540 function instead of assuming a historical C++ class name. Archived old
objects remain usable with explicit `--symbol`/`--contrast-symbol`.

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-reimu-object-action-state --compare --json
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-908-window.py \
  build/match-units/GptWeb_ReimuObjectActionState.obj
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-800-prefix.py \
  build/match-units/GptWeb_ReimuObjectActionState.obj
python3 scripts/audit-reimu-object-member-widths.py > build/reimu-object-member-widths.json
```

The build/comparison deliberately exits1 for the pending root, while separately
recording the accepted66-byte helper. Primary execution audits pass. Reports,
complete body/window packets, source/object/tool fingerprints, graph receipts
and private controls are in `build/reimu-object-908-access-20261022/`;
recipes are in `.analysis/reimu-object-908-access-20261022/`. Finished private
artifacts are archived after every member hash is checked. Six root controls
shrink484631 ->149774 bytes; seven font-control files shrink467139 ->117488.
Selected public inputs, the active baseline contrast and recipes remain loose.
Restore controls before re-reading their objects/images:

```bash
tar -xzf build/reimu-object-908-access-20261022/completed-controls.tar.gz \
  -C build/reimu-object-908-access-20261022
tar -xzf build/font-accent-pixels-20261022/completed-controls.tar.gz \
  -C build/font-accent-pixels-20261022
```

The preceding accent store/advance experiment is closed without source
selection: native and genuine CIL both give416/4275dddb, nonexact+6. Its six
other native bodies stay unchanged. Receipts/recipes are under
`build/font-accent-pixels-20261022/` and `.analysis/font-accent-pixels-20261022/`.
The selected accent remains417/5a5cbf13 with its existing scope.

Exact ledgers remain1381 functions/234914 bytes, authored denominator2136806
(10.99%). Only the affected root unit/accepted helper requires cold replay;
unmodified global layouts/profiles and other accepted units are unaffected.
No new all-unit cold replay, complete class lifetime or root exact claim follows.
