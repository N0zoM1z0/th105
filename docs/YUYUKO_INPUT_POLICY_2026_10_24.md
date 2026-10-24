# Yuyuko input policy: complete exact family peer

## Accepted result

Yuyuko Fighter primary slot `+0x50 @ 0x0056DEB0` accepts **6,180 callable
bytes** and the full **6,216-byte emitted payload**, including every switch
entry. Formal and separate cold builds replay all **125 relocations** and
produce zero differences. Only callable bytes earn authored credit.

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit exact-first-yuyuko-input-policy --compare --json
python3 scripts/audit-yuyuko-input-policy.py
```

Run both commands. The full audit requires exact section-tail length and all
payload bytes through the public strict COFF owner/relocation/literal checks.
The first formal object/provenance is retained; only this new unit's active
object/provenance is removed before the independent cold compile and both
comparisons. The pinned VC8 SP1 `/O2` profile is unchanged.

Callable SHA256:
`5efa57790a078b1726fbde2de335e1264a9f069ed829719cbc3c6ed5990323b6`.
Complete canonical SHA256:
`7fd52536151126351f5ec2fd4d7f9464d2316f912e25607c89700a9f8d0efe87`.

The source is one ordinary complete body in `src/characters/YuyukoInputPolicy.cpp`
with declaration-only pointer views. Never construct or embed those views.
Original names, complete owner layouts and original ignored-return declarations
remain unknown. Declaration-only callees earn no new implementation or exact
credit. No assembly, target array, padding, fake return, inert local, ABI/register
forcing or compiler/profile search was introduced.

## Observed target and independently reviewed differences

Only original Japanese 1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. The frozen roster RTTI anchor binds cell `0x006C569C` to Yuyuko primary
slot+50; an independent raw pointer scan reads the same destination. Authored
ownership is unchanged; this accepted row's origin evidence becomes the generated
`canonical-exact-authored` baseline.

Raw CFG traversal closes **1,773 instructions**, **36 RETs**, **seven external
tails**, all direct/internal edges and all nine switch destinations. The
callable ends exclusively at `0x56F6D4` after an external tail JMP. The table
immediately follows at `0x56F6D4..0x56F6F7`, with no alignment gap. Its bytes earn
no authored credit. The frame reserves eight bytes and saves EBX/EBP/ESI/EDI.

There are138 physical calls:107 direct and31 virtual action-slot+08 calls.
Direct calls comprise five stage predicates, six deque subscripts, two front
predicates, eleven finalizers,49 window queries,25 packed-input initializations
and nine other gates. External tails go once to45DDA0, once to464200 and five
times to4633A0. The object has114 REL32 and eleven DIR32 fields: one float,
one table base and nine destinations. The existing180.0f binding at `0x006D6EDC`
is independently checked and consumed by FCOMP at `0x56EFB4`; no shared mapping
or accepted header changes.

[Sakuya's accepted source](SAKUYA_INPUT_POLICY_2026_10_24.md) is a hypothesis,
checked against complete raw bytes/edges/argument widths. An attested Ghidra
view corroborates the interpretation; its expressions are not pasted as source.

| Surface | Yuyuko behavior retained from target instructions |
| --- | --- |
| Shared air gate |4941D0 receives minimum1;4940E0 still receives2. The actual mode count remains `(mode==10)+2`. |
| Queued commands | Ground records200..208 finalize600..608. Air selector reads the front once after its repeated bounds checks, then201-to651 or207-to657. |
| Ground masks400/200 | +60B566/561 and565/560 through flag+757. |
| Ground masks4000/2000 | +60A546/541 and545/540 through flag+756; these are actual4000/2000 masks. |
| Ground masks40/20 | +60C511/510, +608506/505, then501/500 through flag+754. |
| Ground masks4/2 | +609>=1 queries525 for both groups. The521/520 fallback requires both signed bytes+609 and+60D to equal zero. |
| Air masks40/20 | +60C513/512, +608508/507, then503/502 through flag+754. |
| Air masks4/2 | Both+609/+60D must be zero, then523/522 through flag+755. |
| First normal group | Uses180.0f; no321-to322 shortcut. Air UP308 has one query, without the peer's separate UP/FORWARD308 attempt. |
| Later normal groups | Retains repeated ground400 and412 attempts. Air group+6F8 omits the peer's neutral/forward404 pre-attempt; UP406 retains its resource-failure skip before404 fallback. |

No +12C clear, +730 reset, extra sequence call or mode replacement from another
character is added. Actual signed widths, repeated calls and post-call field
reads are retained.

The first complete source emits the correct6,216-byte payload with exactly one
wrong byte: it copied4941D0's final argument2 from the peer. Native `PUSH 1`
at `0x56DFE8` establishes the correction. Changing that one genuine argument
yields strict complete equality in probe01. No code-generation adjustment was
needed; probe00 remains as negative evidence.

## Validation and retained evidence

IDA's required preflight rejects the other executable still open there; no
semantics or writes from that session are used. One read-only Ghidra process
independently attests file/program identity, language/compiler, image base,
entry `0x68B9D2`, every raw-backed section and root hash. Temporary function,
ABI, observed-tail and action-call metadata is read back and rolled back;
pinned primary database files remain byte-identical. Analysis uses CPU0/nice10
and384 MiB configured heap; builds are serial on CPU0/nice10.

Private recipes and both full source snapshots remain under
`.analysis/exact-first-yuyuko-slot50-20261024/`. The corresponding `build/`
directory retains raw facts/disassembly, whole CFG/table closure, attestation,
formal/cold comparisons, first object/provenance, relocation counts, original
origin row and input hashes. The generated-table negative is rejected at
`+0x1824 / 0x56F6D4`, targetF9/sourceFA; the target is untouched. Previous source
inputs remain unchanged. No broad runtime matrix or aggregate cold replay is
claimed. Continue other complete peers; Marisa's neutral controls remain parked.
