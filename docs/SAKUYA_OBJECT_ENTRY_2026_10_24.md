# SakuyaObject initializer: complete source, nonexact

`0x004E8060` now has complete selected source in
`src/characters/SakuyaObjectActionEntry.cpp/.hpp`. It is an authored RTTI-owned
SakuyaObject primary slot+3C initializer, separate from Fighter input/CPU/control
roots. Numeric states, offsets and declaration-only call views are intentional.
Never construct or embed either pointer-only view; complete nominal layout,
original local names, source partition and compiler/TU phase remain unknown.

## Complete comparison and remaining difference

Formal and independent cold builds both produce **6868 bytes**, the complete
target payload length, canonical SHA256
`99097f1b9fbbf0b163de7d2c15d0ae97646bf5a1a169a23b5631c346294e1d05`.
The complete unmasked comparison has **13 differing bytes**, confined to action
803 at offsets+2B3..317. First mismatch `0x004E8313`: targetCE/source53 in the
virtual-selector preparation. Its call-register choice also changes the later
facing/payload-address schedule. All remaining callable bytes, alignment and
all330 bytes after the callable agree. No partial exact credit is awarded.

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit exact-first-sakuya-object-entry --compare --json
python3 scripts/audit-sakuya-object-entry.py
taskset -c 0 nice -n 10 python3 scripts/audit-sakuya-object-entry-prefix.py
```

The first two commands return1 with the recorded nonexact result. The prefix
audit returns0. Both audits accept `--object` for an independent object or
negative control. The full audit replays every emitted relocation, compares
all6868 bytes and requires full length equality. `matches.csv` is unchanged.
No new exact function or authored byte is claimed.

## Observed target boundary, ownership and ABI

Only original Japanese1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. Primary-vtable cell `0x006C48C8` points to4E8060; existing frozen
Object RTTI/origin anchors establish SakuyaObject ownership independently.
The same table's slot0C cell `0x006C4898` contains the already exact shared
selector `0x0045C390`. The local word-carrier caller view does not change that
callee's existing implementation or its public int selector declaration.

Raw CFG traversal closes **1772 instructions**, **25 RET0 exits**, **107 direct
calls**, **25 virtual calls**, and one external tail4E9990->596370. No unreviewed
remote chunk is absorbed. The6538-byte callable is4E8060..4E99E9 inclusive,
SHA256 `18cf2b7f022bf304858d630a6f17d03aad378c78e34db2a3120801701f88afc1`.

| Physical region | Extent / bytes |
| --- | --- |
|Callable|4E8060..4E99E9 /6538|
|Alignment|4E99EA..4E99EB /2, `8bff`|
|Main destinations|4E99EC..4E9A6B /32 DWORDs|
|Selectors800..999 remap|4E9A6C..4E9B33 /200 BYTEs|
|Following separation|4E9B34..4E9B3F /12 INT3 bytes|

Full6868-byte target SHA256:
`3323c8c4ac1fa5c9725d0e921b4b343d15e8de8be40277216222b38e0a942c82`.
All32 destinations land on reviewed callable instruction boundaries. Remap29
belongs only to explicit empty998; default remap31 shares its real4E99D8 exit.
Actions804/850 share a destination;817 sets its byte then enters802's body.

The root receives ECX, has a20-byte frame, and has no EH. Native calls are
27 FTOL2 conversions,21 oriented-motion calls435160,23 parented requests4FCA60,
four float atan2 calls406540,31 independent selector RNG calls4067D0 and one
unparented request64CCB0. Each virtual slot0C call uses a four-byte argument
slot and the native selector target remains unchanged. Heading2 is checked
with ordered `>0` except999's unconditional conversion. Two extra conversions
in815 write signed WORD x/y snapshots. Motion receiver is exactly this+4;
object requests receive this, seven ordinary stack slots and28-byte cleanup.
Facing loads are unsigned BYTEs; copied float payloads have real counts3/4.

**Observed source distinctions:**813 uses <=5 before its independent R90,
three R11, two R5, R9 and R10 draws.852/855 draw R100 before R50; their180-degree
term is an ordinary integer converted through native x87 evaluation, not a
byte wrap or forced double local.855 also writes heading1=60 before R40 and
heading0.901 uses actual repeated sequence tests and its7/8 heading epochs;
900 emits action856's payload.859/901 perform three separate facing1 requests.
858 retains the native fourth initialized array element even in its count3
branch, then uses the separate count4/layer1 unparented request in sequence2.
980 is only the existing shared continuation tail. No asm, copied code bytes,
inert locals, synthetic padding or fabricated helper implementation is used.

## Early whole comparisons and finite trials

Every trial compiles the complete body with the unchanged VC8 SP1 O2 profile.
The first complete source was compared before local tuning. Private frozen
sources/recipes are under `.analysis/exact-first-sakuya-object-entry-20261024/`;
generated objects, normalized bytes and reports are under the corresponding
`build/` directory. These private artifacts are not committed.

| Trial | Whole-function evidence and decision |
| --- | --- |
|00|Complete6868-byte source; all physical calls agree. Frame28 versus20 and one missing metadata group prevent equality.|
|01|Observed overlapping payload/double storage expressed as a used union restores frame20. Full6884; no exact claim.|
|02|Explicit empty998 with explicit default return is byte-neutral. Retain receipt.|
|03|Implicit function-end default preserves the native distinct998/default remap entries:32 destinations/200 bytes. Full6888.|
|04|Remove unobserved float captures from three double consumers. Full6864; correction-literal widths still differ.|
|05|Use observed <=5 instead of <6 in813. Native constant5 lifetime, including816's byte output, returns. Full6868.|
|06, rejected|Float result carriers keep correction width but add three rounding spills. Full6892.|
|07|Limit actual payload arrays to their case scopes; ordinary lifetimes naturally recover the596370 tail and frame20. The used union is no longer needed. Full6868.|
|08, rejected|Single expression with float-return wrappers grows frame24. Full6880.|
|09|Single direct unsigned/float expressions preserve R100-before-R50 and the three native DWORD correction loads without spills. Full6868.|
|10/11, rejected|A float heading snapshot preserves901's read epoch but forces an unobserved spill. Full6880; retained as diagnostics.|
|12, selected shape|A used double preserves the exact input float across901's byte write without a new float spill. Full6868;13 differing bytes remain in803.|
|13, rejected|Existing shared selector's public int form changes scheduling at all25 calls. Full6868, first+C0; does not resolve803.|
|14, selected ABI view|The existing target-backed signed-WORD caller carrier with actual int return is canonically byte-identical to12. No shared declaration changes.|
|15, parked|An explicit used WORD conversion carrier only in803 is canonically byte-identical to14. Preserve both neutral receipts and switch representative.|

The residual establishes neither a unique original source spelling nor an
LTCG impossibility. Reopen it only with new independent target/compiler evidence.

## Targeted heading-epoch execution

The two901 sequence7 inputs run the real native motion, quantized math and
conversion code to the actual parented-spawn entry. The spawn and all later
behavior are outside this prefix. The normal heading buffer and a deliberately
aliased heading0/BYTE184 buffer distinguish the read/write epoch. The initial
root reset makes aliased heading0 exactly1.0. Target reads it, writes BYTE184=1,
and publishes the old1.0 to12C; a late read would publish1.0000001192092896.

Both selected prefixes agree on actor bytes, real motion arguments, spawn
arguments/payload and x87 control/TOP/tags. Native target independently confirms
heading1.0 and exactly one motion call. Old probe09 fails the alias case and
passes the separate-buffer case; it is a negative control, not a second accepted
source. This small diagnostic resolves a concrete ambiguity and is not a
whole-function behavioral proof or exactness result.

## Analysis provenance and resource limits

The mandatory IDA preflight rejects GUI SHA256
`10350095bcf95edb59e03bee9849a2dc8a7714b4927ad5909c569c550fce6822`.
No IDA semantic query or metadata write is used. Two serial direct read-only
Ghidra runs attest imported file/hash, Windows x86 language/compiler, imagebase,
entry68B9D2, all raw-backed mapped sections and root hash. The first exposes
missing helper call parameters; the second applies temporary known call views
and the target-proven tail flow override to avoid absorbing596370's body.
Readbacks verify every temporary view; the transaction is rolled back and all
nine primary database file hashes remain unchanged after each run. Raw target
bytes are never patched. Decompiler output stays a hypothesis, including its
incorrect double/uint interpretation of the actual float payload array.

A live foreign Java/Ghidra process briefly caused the launch guard to refuse
one attempt. It was not killed or duplicated; the next process check found it
terminal before the second serial run. Both owned runs completed successfully,
with384MiB heap, CPU0/nice10 and no database writes. Builds and native prefix
checks are also serial CPU0/nice10. Two newly witnessed literal bindings are
0x6C4A00 = double(float1.7), bytes000000403333fb3f, and0x6C3E40 = float0.9,
bytes6666663f. No existing binding, shared header, compiler flag, accepted
source, exact unit or authored-origin denominator changes. No aggregate cold
exact claim is made.
