# Aya CPU decision root, October 17

`Aya_update_cpu_action_policy @ 0x006126E0` now has complete, target-reviewed
source in `src/characters/AyaCpuActionPolicy.cpp`. The callable is 16,032
bytes / 4,097 instructions. The source builds under the existing pinned VC8
profile and remains **nonexact**. No exact or partial byte credit is added.

## Target observations and complete boundary

All evidence uses the original Japanese TH105 1.06a executable SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Aya's RTTI-owned primary vtable starts at `0x006C62D4`; slot `+0x58`, at
`0x006C632C`, points to this root. Existing origin rules already classify it
as authored. The new mapping/source selection does not change ownership or
award matching credit.

Raw traversal closes **every instruction and byte** in
`[0x006126E0,0x00616580)`, with no unreachable ranges, internal callees or
unresolved transfers. The last instruction is RET at `0x0061657F`. Main
switches have 19 action destinations and 21 policy destinations; four nested
sequence switches are part of the same callable. Their six index/destination
tables are validated in `config/giant-action-switches.toml`. The 632 metadata
bytes at `[0x00616580,0x006167F8)` remain separate from authored callable bytes.
There are 152 direct call sites to five existing dependencies: atan2 (5), raw
MT next (1), selector (114), checked sequence (25), and float conversion (7).

Root body SHA-256:
`7efa001552238230ac86c77f48f36a217cc486e847f85cb924527c64e2dc6e09`.

## Strict bridge to the default CPU root

```bash
python3 scripts/audit-cpu-root-bridge.py
python3 scripts/map-giant-action-switches.py aya-cpu-action-policy --json
```

The first command compares two **original target regions**. All 4,069
instructions / 15,910 bytes of the previously reviewed default root correspond
to Aya after explicit address translation. It checks encoded bytes, all
1,111 direct control operands, 150 corresponding calls and 12 switch-data
operands. Every other operand remains identical. All 632 metadata bytes also
agree after translating their 61 destination pointers; byte-index tables and
padding are checked, not masked. Two fallback destinations enter Aya's new
branches before resuming the corresponding default instructions.

The only additional instructions are two 61-byte / 14-instruction blocks:

| Aya entry | Additional ordered conditions, in evaluation order | Effect |
| --- | --- | --- |
| `6142C0` | distance > 320; native selector(1000) <= 20; signed resource word +482 >= 400 | command DWORD +728 = `0x400`; shared policy join |
| `61447C` | distance > 320; native selector(1000) <= 2; signed resource word +482 >= 400 | command DWORD +728 = `0x200`; shared policy join |

The first lies in the both-grounded quadrant; the second has self grounded
and opponent airborne. Distance is the absolute value of the integer-truncated
X-coordinate difference, converted back to float. It is not the raw float
separation: the additional branch starts at truncated distance 321. The RNG
comparison is unsigned, the resource comparison signed, and unordered
comparisons fail before RNG. The source retains this call/order relationship.

**Inference:** this complete correspondence supports transferring the reviewed
default source's existing behavior and physical field model, then implementing
the two observed additions. It does not establish original source spelling,
TU partition, inheritance declaration, or compiler profile. The 0x770 method
view is a prefix model, not Aya's complete object size. A bounded read of the
TH075 policy helpers supplied no corresponding giant implementation; no TH075
address, layout or compiler assumption is imported.

## Source and canonical comparison

```bash
python3 scripts/build.py --unit gpt-web-aya-cpu-action-policy --compare --json
python3 scripts/audit-giant-action-owners.py aya-cpu-action-policy build/match-units/GptWeb_AyaCpuActionPolicy.obj --unit gpt-web-aya-cpu-action-policy --json
```

The build returns 1 for the ordinary mismatch. The full 16,032-byte comparison
first differs at **+0x12E / 0x0061280E**, target byte `6A`, candidate `A3`.
The candidate metadata starts at 16,052, and its section tail is 16,677 bytes.
The physical owner diagnostic is **14/41**, without independent function or
partial exact credit. Candidate comparison-window SHA-256:
`5469429ac8cec4a43cfd73bec917fa0c36a970d269bf9fb2418bc0b4f454c5e0`.

Only a new source file, probe unit and target switch specification are added;
the existing CPU header, default root source, helper ABI, compiler flags,
global/relocation ledger and accepted units are unchanged.

## Native execution and negative controls

```bash
python3 scripts/audit-cpu-policy-paths.py build/match-units/GptWeb_AyaCpuActionPolicy.obj --root aya --cases 5000
python3 scripts/audit-cpu-policy-paths.py build/match-units/GptWeb_AyaCpuActionPolicy.obj --root aya --aya-command-cases
```

There are **zero differences in 5,000 finite cases** and **zero in 470 command
controls**. The original five dependencies execute without helper-result
hooks, including real MT seeding/streams, atan2, checked sequence access and
x87 conversion. Comparison covers the whole 0x7A4 actor prefix, RNG state,
call order/arguments/results, physical conversion inputs, stack and x87
control word through native RET. The finite matrix visits 3,582/4,097 target
instructions and 3,539 candidate instructions. These are sampled controls;
complete gameplay, branch, numerical and exception equivalence remain unproved.

The 470 controls include two target-confirmed positive seed fixtures,
resource words -1/399/400/401/1000, distance/truncation boundaries around
320/321, six genuine seeds, and quiet/signaling NaN and infinite X inputs.
All **28 added target instructions** execute; the tool rejects incomplete
coverage or a positive fixture whose expected command the target fails to
confirm. Input SHA-256:
`36416a41d41cfe53f5ea6a8d34f561b8fec848e208a48a68e472cf96c1e91660`.
The positive seeds are input data, not substituted RNG outputs.

A private source control omitting both additions produces **2/2 differences**
on those positive inputs, including command flags and RNG/call effects. It is
not retained. The generalized probe's default-root mode also passes a focused
200-case regression; no unrelated accepted-unit or aggregate replay is claimed.
The default 16,000-case policy0 coverage result retains its prior checkpoint
scope and was not rerun here.

## Direct Ghidra and retained working state

One direct Ghidra process at a time, capped at two CPUs / 768 MB heap, checks
raw/imported executable identity, entry 68B9D2, Windows x86 target and all
mapped .text bytes before writing metadata. The root name, exact body extent,
void __thiscall ECX receiver with no stack arguments, switch references and
two branch comments are saved and independently read back in a fresh process.
The readback has all 4,097 instructions and the original body hash unchanged.
The existing 27-field CPU prefix view is reused; decompiler output remains a
hypothesis. IDA preflight rejects its different executable and is unused.

Private script: `.analysis/aya-cpu-20261017/ghidra-scripts/Th105AyaCpuRoot20261017.java`.
The attested saved project is returned to the existing primary working project;
the duplicate visible-path project is removed. Generated objects/reports and
analysis databases are excluded from Git.

Local evidence: `build/aya-cpu-target-bridge.json`, `aya-cpu-target-map.json`,
`aya-cpu-target-boundary.json`, `aya-cpu-first-build.json`,
`aya-cpu-first-owners.json`, `aya-cpu-native-finite.json`,
`aya-cpu-native-commands.json`, `aya-cpu-negative-missing-commands.json`, and
`aya-cpu-ghidra-{save,readback}.log`. Fresh final receipts use the
`aya-cpu-final-` prefix. Remaining work is canonical whole-root byte equality,
including the inherited shared control/register/tail layout. Original source
partition and possible LTCG involvement remain unknown, not established causes.
