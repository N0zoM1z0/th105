# SakuyaObject initializer: complete source, nonexact

`0x004E8060` now has complete selected source in
`src/characters/SakuyaObjectActionEntry.cpp/.hpp`. It is an authored RTTI-owned
SakuyaObject primary slot+3C initializer, separate from Fighter input/CPU/control
roots. The receiver uses checked members for fixed offsets and
declaration-only call views for the motion subobject and selector.
Never construct or embed either pointer-only view; complete nominal layout,
original local names, source partition and compiler/TU phase remain unknown.

## Complete comparison and remaining difference

Formal and independent cold builds both produce **6868 bytes**, the complete
target payload length, canonical SHA256
`99097f1b9fbbf0b163de7d2c15d0ae97646bf5a1a169a23b5631c346294e1d05`.
The complete unmasked comparison has **13 differing bytes**, confined to action
803 at offsets `+0x2B3` through `+0x317`. The first difference is at
`0x004E8313` in the virtual selector preparation. The other differences
are in the facing and payload-address preparation for the spawn. The
rest of the callable, both alignment bytes and the complete table data
agree.

The checked-member rewrite produces the same full payload after all 218
relocations are replayed. These separate changes to action 803 also produced
the identical payload: aggregate initialization of the three transmitted
floats, capturing the sequence before the guard, capturing heading and facing
before filling the payload, and naming the selector argument. The target uses
EAX for the virtual selector target and EDX for the later facing argument.
The current object uses EDX for the virtual target and ECX for facing. The
configured unit now includes the destination and byte-index tables in its
strict comparison.

```sh
DISPLAY= WAYLAND_DISPLAY= PATH="$PWD/.tools/factory-bin:$PATH" \
  scripts/repo-python scripts/build.py \
  --unit exact-first-sakuya-object-entry --compare --json
```

The build comparison returns 1 at the recorded callable difference. The
full replay covers all 6,868 bytes and 218 relocations.

## Observed target boundary, ownership and ABI

Only original Japanese 1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. Primary-vtable cell `0x006C48C8` points to 4E8060; existing frozen
Object RTTI/origin anchors establish SakuyaObject ownership independently.
The same table's slot 0C cell `0x006C4898` contains the already exact shared
selector `0x0045C390`. The local word-carrier caller view does not change that
callee's existing implementation or its public int selector declaration.

Raw CFG traversal closes **1772 instructions**, **25 RET 0 exits**, **107 direct
calls**, **25 virtual calls**, and one external tail 4E9990->596370. No unreviewed
remote chunk is absorbed. The 6538-byte callable is 4E8060..4E99E9 inclusive,
SHA256 `18cf2b7f022bf304858d630a6f17d03aad378c78e34db2a3120801701f88afc1`.

| Physical region | Extent / bytes |
| --- | --- |
|Callable|4E8060..4E99E9 /6538|
|Alignment|4E99EA..4E99EB /2, `8bff`|
|Main destinations|4E99EC..4E9A6B /32 DWORDs|
|Selectors 800..999 remap|4E9A6C..4E9B33 /200 BYTEs|
|Following separation|4E9B34..4E9B3F /12 INT3 bytes|

Full 6868-byte target SHA256:
`3323c8c4ac1fa5c9725d0e921b4b343d15e8de8be40277216222b38e0a942c82`.
All 32 destinations land on reviewed callable instruction boundaries. Remap 29
belongs only to explicit empty 998; default remap 31 shares its real 4E99D8 exit.
Actions 804/850 share a destination;817 sets its byte then enters 802's body.

The root receives ECX, has a20-byte frame, and has no EH. Native calls are
27 FTOL2 conversions,21 oriented-motion calls 435160,23 parented requests 4FCA60,
four float atan2 calls 406540,31 independent selector RNG calls 4067D0 and one
unparented request 64CCB0. Each virtual slot 0C call uses a four-byte argument
slot and the native selector target remains unchanged. Heading 2 is checked
with ordered `>0` except 999's unconditional conversion. Two extra conversions
in 815 write signed WORD x/y snapshots. Motion receiver is exactly this+4;
object requests receive this, seven ordinary stack slots and 28-byte cleanup.
Facing loads are unsigned BYTEs; copied float payloads have real counts 3/4.

**Observed source distinctions:**813 uses <=5 before its independent R90,
three R11, two R5, R9 and R10 draws.852/855 draw R100 before R50; their 180-degree
term is an ordinary integer converted through native x87 evaluation, not a
byte wrap or forced double local.855 also writes heading 1=60 before R40 and
heading 0.901 uses actual repeated sequence tests and its 7/8 heading epochs;
900 emits action 856's payload.859/901 perform three separate facing 1 requests.
858 retains the native fourth initialized array element even in its count 3
branch, then uses the separate count 4/layer1 unparented request in sequence 2.
980 is only the existing shared continuation tail. No asm, copied code bytes,
inert locals, synthetic padding or fabricated helper implementation is used.

## Early whole comparisons and finite trials

Every trial compiles the complete body with the unchanged VC8 SP1 O2 profile. The
first complete source was compared before local tuning. These private artifacts are
not committed.

| Trial | Whole-function evidence and decision |
| --- | --- |
|00|Complete 6868-byte source; all physical calls agree. Frame 28 versus 20 and one missing metadata group prevent equality.|
|01|Observed overlapping payload/double storage expressed as a used union restores frame 20. Full 6884; no exact claim.|
|02|Explicit empty 998 with explicit default return is byte-neutral. Retain receipt.|
|03|Implicit function-end default preserves the native distinct 998/default remap entries:32 destinations/200 bytes. Full 6888.|
|04|Remove unobserved float captures from three double consumers. Full 6864; correction-literal widths still differ.|
|05|Use observed <=5 instead of <6 in 813. Native constant 5 lifetime, including 816's byte output, returns. Full 6868.|
|06, rejected|Float result carriers keep correction width but add three rounding spills. Full 6892.|
|07|Limit actual payload arrays to their case scopes; ordinary lifetimes naturally recover the 596370 tail and frame 20. The used union is no longer needed. Full 6868.|
|08, rejected|Single expression with float-return wrappers grows frame 24. Full 6880.|
|09|Single direct unsigned/float expressions preserve R100-before-R50 and the three native DWORD correction loads without spills. Full 6868.|
|10/11, rejected|A float heading snapshot preserves 901's read epoch but forces an unobserved spill. Full 6880; retained as diagnostics.|
|12, selected shape|A used double preserves the exact input float across 901's byte write without a new float spill. Full 6868;13 differing bytes remain in 803.|
|13, rejected|Existing shared selector's public int form changes scheduling at all 25 calls. Full 6868, first+C0; does not resolve 803.|
|14, selected ABI view|The existing target-backed signed-WORD caller carrier with actual int return is canonically byte-identical to 12. No shared declaration changes.|
|15, parked|An explicit used WORD conversion carrier only in 803 is canonically byte-identical to 14. Preserve both neutral receipts and switch representative.|

The residual establishes neither a unique original source spelling nor an
LTCG impossibility. Reopen it only with new independent target/compiler evidence.

## Targeted heading-epoch execution

The two 901 sequence 7 inputs run the real native motion, quantized math and
conversion code to the actual parented-spawn entry. The spawn and all later
behavior are outside this prefix. The normal heading buffer and a deliberately
aliased heading 0/BYTE184 buffer distinguish the read/write epoch. The initial
root reset makes aliased heading 0 exactly 1.0. Target reads it, writes BYTE184=1,
and publishes the old 1.0 to 12C; a late read would publish 1.0000001192092896.

Both selected prefixes agree on actor bytes, real motion arguments, spawn
arguments/payload and x87 control/TOP/tags. Native target independently confirms
heading 1.0 and exactly one motion call. Old probe 09 fails the alias case and
passes the separate-buffer case; it is a negative control, not a second accepted
source. This small diagnostic resolves a concrete ambiguity and is not a
whole-function behavioral proof or exactness result.

## Analysis provenance and resource limits

The mandatory IDA preflight rejects GUI SHA256
`10350095bcf95edb59e03bee9849a2dc8a7714b4927ad5909c569c550fce6822`.
No IDA semantic query or metadata write is used. Two serial direct read-only
Ghidra runs attest imported file/hash, Windows x86 language/compiler, imagebase,
entry 68B9D2, all raw-backed mapped sections and root hash. The first exposes
missing helper call parameters; the second applies temporary known call views
and the target-proven tail flow override to avoid absorbing596370's body.
Readbacks verify every temporary view; the transaction is rolled back and all
nine primary database file hashes remain unchanged after each run. Raw target
bytes are never patched. Decompiler output stays a hypothesis, including its
incorrect double/uint interpretation of the actual float payload array.

A live foreign Java/Ghidra process briefly caused the launch guard to refuse
one attempt. It was not killed or duplicated; the next process check found it
terminal before the second serial run. Both owned runs completed successfully,
with 384MiB heap, CPU 0/nice10 and no database writes. Builds and native prefix
checks are also serial CPU 0/nice10. Two newly witnessed literal bindings are
0x6C4A00 = double(float 1.7), bytes 000000403333fb3f, and 0x6C3E40 = float 0.9,
bytes 6666663f. No existing binding, shared header, compiler flag, accepted
source, exact unit or authored-origin denominator changes. No aggregate cold
exact claim is made.

## Real all-CIL and bounded source controls, 2026-10-30

The selected ordinary root still has the full 6868-byte payload 99097f1b and
only the same 13 mismatching bytes in 803. No partial acceptance is added.

A new closed provider graph contains the actual root, parented/unparented
spawns, oriented motion, shared 980 continuation, quantized lookups, atan2,
selector RNG and MT implementation. All eight translation units are /GL CIL;
there is no native authored-COFF companion, code-address binding, symbol alias,
fake callee or target execution. The real spawn methods use a typed slot 1
polymorphic manager view and the caller's byte-facing ABI. Independent complete
COFF replays match their 77/78-byte native bodies. The corresponding normal
motion and continuation definitions independently match 57/323 bytes too.
These are alternative witnesses for existing accepted helpers, not new credit.

With normal source exports and Ob1 on the CIL units, the link resolves through
pinned CRT libraries. Actual atan2 retains its separate strict-FP producer
setting. The resulting root has an aligned EBP frame and 18h local allocation,
unlike native's14h allocation without that frame. Its last pretable RET is
10002981; the main 32-DWORD table begins 10002984 and the 200-byte remap ends
10002ACC. That emitted 6860-byte envelope is not the native 6868-byte payload.
The next MAP symbol's6864-byte span is deliberately not treated as ownership.
The source atan2 also derives a different aligned frame in CIL. These are
observations, not proof that one specific provider caused the root difference.
No old private Aya script using authored COFF providers or /alternatename is
reused as an acceptance route.

Raw RTTI confirms Sakuya's eight-base hierarchy at COL 6DA0F4/CHD6DA108:
SakuyaObject, CharacterObjectEx<Sakuya,SakuyaObject>, CharacterObject,
CObjectBase(+330), AttackObject, AnimationObject, AnimationObjectBase(+4)
and Environment(+130); the other PMD member offsets are 0 and every vbptr
field is-1. A narrow inherited selector-prefix view preserves this zero-offset
method relationship without claiming the full object layout. It is byte-neutral.

Three ordinary payload lifetime controls are also completely byte-neutral:
803's actual three-word payload extent; minimum written/transmitted extents in
all 13 three-word cases while preserving both four-word cases; and placing 803's
payload inside its actual post-selector guarded use. Every complete audit keeps
payload 99097f1b and the same 13 differences. No new padding or local is inserted.

A separately pinned cached VC8 RTM 14.0.50727.42 compiler/front end/back end,
with unchanged SP1 include inputs and selected root source, also emits exactly
the same full payload 99097f1b. The three binary hashes, version fields, command,
source and object hashes are recorded. This is a compiler-release control, not
a new public build profile or evidence of the target's original patch release.

## Action 803 depends on allocation across the switch

The exact 801 path already pushes the conversion result before loading
the virtual target into EAX. In the full candidate, 803 instead loads that
target into EDX and later puts the payload address in EAX and the facing
byte in ECX. Removing only 800 or only 801 in scratch, with 803's source
untouched, restores all three original register choices and the native
instruction order in 803. These local disassemblies agree after accounting
for shifted intra-function branches. Removing 805, 811 or 930 leaves the
rebuilt register choices intact.

At `c2.dll:0x10C0743C`, the indirect call and payload address use
unassigned virtual registers. Immediately after `0x10BDA210` returns
to `0x10C07442`, the full input has EDX for the call and EAX for the
address. The input with 801 omitted has EAX for the call and ECX for the
address. The facing arguments also differ at this point. In both inputs
the conversion-result push still precedes the virtual-target load.
Later scheduling can move the full build's load before that push.
Both traced objects reproduce their respective complete ordinary builds.

The 800/801 payload-scope, branch and switch-exit controls all reproduce
the selected candidate. Making the exact oriented-motion callee visible
in 803 also preserves the full bytes and the call. Using the shared int
selector declaration in 803 leaves the EDX allocation and changes three
scheduled bytes.

Typed inline helpers now carry the sequence selection and child-spawn
arguments. The complete canonical payload is identical to the preceding
build. Moving the motion-view cast into a third inline helper grew the
payload by 16 bytes, so the motion macro remains in the selected source.
