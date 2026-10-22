# ReimuObject member storage and action800 prefix, 2026-10-22

The private real-owner model can remove its remaining whole-self/parent
staging view and reproduce the entire selected native payload. This does not
recover unique original field grouping: five separate short members change
action800's floating lifetime, whereas a five-short array restores it but
retains the selected source's908 discrepancy. No private model is selected,
and no authored exact count changes.

## Target observations

All observations use the hash-attested original Japanese1.06a executable,
SHA256 `56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
IDA preflight again rejects its unrelated `10350095...` image; none of its
semantics or metadata are used.

`scripts/audit-reimu-object-member-widths.py` checks the reviewed physical
code ranges of496540. It finds1,158 direct, nonindexed ESI memory operands
at22 selected offsets, with these consistent access widths:

| Owner-relative offsets | Observed width |
| --- | --- |
| 110,111,112,113 | 1 byte |
| 13C,13E,140,142 | 2 bytes |
| 144,170,180,330,348,34C | 4 bytes |
| 174,364,366,368,36A,36C | 2 bytes |
| 184,33C | 1 byte |

The complete decoded ranges write ESI only through one `MOV ESI,ECX` and68
`POP ESI` exits. This supports interpreting the listed direct operands as
owner-relative accesses. It does not establish unique C++ types, signedness
for every use, original nominal base ownership, indirect accesses, or the
parent's complete dynamic identity.

The action800 sequence0 parameter window is `496656..496684`, exclusive end,
46 bytes. After the heading store, target instructions load parameters[1]
before converting the signed short at364, multiply that integer by the double
representation of0.1f, add the two live x87 operands, round through a float
temporary, and prepare the actual435160 call. Target bytes and stack stores
are retained in the generated audit report.

## Private owner experiment

Start from the preceding corrected real-owner source, SHA256
`db69ca1a2886422e248504435e928dc714934404613b6b98845cca9bfbec5d92`.
Its existing17-slot hierarchy and388h object size remain unchanged. Expose
animation state in the existing environment storage and use actual inherited
attack/object members, existing byte color storage, owner/parent pointers,
and observed short state storage. Compile-time checks verify the member
offsets, widths, nested attack offsets, parameter pointer and total size.

This replaces1,430 self accesses in22 groups and17 parent accesses in seven
groups, removing the root staging-view type/include and the whole-object
`_root_state` reference. The parent accesses cover position, sequence, time,
parameter pointer, short state and heading. Byte views of color storage and
a corresponding signed view of the existing unsigned phase storage remain.
Those are storage interpretations, not proof of original declarations.

Every ordinary SP1/O2 control below emits45,696 bytes, differs first at
49655F/+31, and retains helper4963A0 at66/66:

| Private source storage | Canonical payload SHA256 prefix | 800 / 908 arithmetic |
| --- | --- | --- |
| Five scalar shorts and five scalar floats | 854db777 | Integer-first / integer-first |
| Same, with signed lifetime-counter storage view | 854db777 | Unchanged |
| Five scalar shorts, five-float array | 854db777 | Unchanged |
| Five-short array, five scalar floats | 4d0ac180 | Target800 / integer-first908 |
| Five-short and five-float arrays | 4d0ac180 | Unchanged |
| Five-short array plus a used908 short reference | 4d0ac180 | Unchanged |

The arrays represent observed scalar state storage, with the same offsets
and existing alignment. They contain no instructions or machine-code bytes.
These controls test source aggregation; none establishes original grouping.
The used908 reference names the existing counter through its tests, update
and resets, without caching its value across callbacks. It is byte-neutral.

The five-short-array model's full canonical payload equals current selected
source, SHA256
`4d0ac180cace3180285c26ccfb94a48d3f05d70037761cdbd4f1d7f07c947a50`.
Both full runtime packets relocated to800000 also agree in all45,696 bytes,
SHA256 `7ac15a2e5b4a1edf785b5693948d24eac119ed0636af545eb413199d6c004f66`.
This is candidate-to-candidate equality, not target acceptance.

The scalar-member model passes the existing804/869/902 execution matrices
(5,120 /3,072 /1,792 cases) but fails all2,240908 logical x87 snapshots.
The earlier corrected owner still provides the observed float-first908
control. Its remaining overlay cannot be removed under these tested source
forms while retaining both target windows.

## Real action800 prefix execution

`scripts/audit-reimu-object-800-prefix.py` begins at the actual root entry,
executes the original200-byte5575C0 effect gate and stops at the first real
435160 orientation entry. The owner action150 makes that gate return zero
through its own instructions. No callback or helper return is fabricated.
Sequence0, phase0 and timer/counter1 avoid the separate renderer setup path;
parameters are external, with heading37.25f.

The2,240 cases cross20 parameter float bit patterns,14 incoming signed-short
states, PC53/64 and all four rounding modes. They include signed zeros,
subnormals, finite boundaries, infinities, signed quiet/signalling NaNs and
the target word increment wrapping32767 to-32768. The audit checks complete
fixture outputs, ordered owner/parameter writes, actual pending call receiver
and float words, logical x87 before multiplication and before/after addition,
and final FPSW. Each run must visit all snapshots once and execute the gate.

| Compiled root | Outputs / writes / FPSW | x87 snapshots | Parameter window |
| --- | --- | --- | --- |
| Fresh selected public source | Equal in2,240 | Equal in2,240 | 46/46 |
| Private five-short-array owner | Equal in2,240 | Equal in2,240 | 46/46 |
| Prior corrected real owner | Equal in2,240 | Equal in2,240 | 46/46 |
| Private scalar-member owner | Equal in2,240 | Different in2,240 | 44 bytes |

The scalar control folds the parameter read into a memory FADD after integer
conversion/multiplication. This loses a live x87 value even when final output
agrees. The audit covers this prefix only: no orientation return, later
spawn, full-root RET ABI, unmasked exceptions, arbitrary incoming x87 or
canonical whole-function equality is established.

## Reproduction and retained evidence

Public target-width and selected-source checks:

```bash
python3 scripts/audit-reimu-object-member-widths.py > build/reimu-object-member-widths.json
python3 scripts/build.py --unit gpt-web-reimu-object-action-state --compare --json > build/reimu-object-member-selected.json
python3 scripts/audit-reimu-object-800-prefix.py build/match-units/GptWeb_ReimuObjectActionState.obj > build/reimu-object-member-800.json
```

The build/comparison intentionally exits1 for the unaccepted root; its
report independently records the exact66-byte helper. The prefix audit
passes for selected source. Use `taskset -c 0 nice -n 10` for bounded CPU use.
The prefix tool accepts `--symbol`, `--contrast-object` and
`--contrast-symbol` for ordinary private owner COFF inputs. Reports pin their
objects, target and comparison dependencies but explicitly do not attest
those objects' source/build provenance.

Private recipes/trees remain under `.analysis/reimu-object-members-20261022/`;
reports and retained COFF inputs are under `build/reimu-object-members-20261022/`.
`prepare.py`, `build.py`, the separate array/reference build recipes,
`member-map.json`, comparison receipts, `target-member-widths.json`,
`runtime-equality.json`, `selected-800.json`, `words-800.json` and
`prior-owner-800.json` record the controls. `members-804/869/902/908.json`
retain the other bounded execution results. The scalar source SHA256 is
`a689211c4449c91615f198b303153e11a2880b6f49589dde65e0c1d6de8d71d8`;
the five-short-array source is
`614bd6c063653d946d294d339f43c583f34e9085830792bfa3d83bb772910b4f`.
Four completed duplicate COFF controls are in `completed-controls.tar.gz`;
`retention.json` records hashes verified before removing the originals
(323,037 to99,842 bytes). Selected/scalar/short-array active inputs and the
preceding real owner/provider graphs remain available. Restore archived
controls with `tar -xzf completed-controls.tar.gz` in that build directory.
Selected source remains77fe73a4; no shared interface/layout/profile/binding,
source selection, origin or match row changes.

The next discriminator is the source/compiler context behind simultaneous
800/908 lifetimes and physical tail sharing. Observed widths and nominal
hierarchy agreement do not resolve it. Exact ledgers remain1,379 functions /
234,584 bytes, authored denominator2,136,806 (10.98%); no new global cold
replay claim follows.
