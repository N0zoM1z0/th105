# Aya CPU signed counter reads, October 17

`Aya_update_cpu_action_policy @ 0x006126E0` now retains a natural inline
accessor for the signed action counter at +764. Four source paths use that
real field read at their individual predicates. This restores observed WORD
comparison forms and raises instruction/edge-identical physical owners from
14/41 to **17/41**, preserving all fourteen earlier identical owners.
The complete16,032-byte root remains **nonexact**; no authored exact or partial
byte credit is added.

## Observed target and retained source

| Action | Observed counter predicates | Current source result |
| --- | --- | --- |
| 300 | Signed10..90, then otherwise>=90;90 takes the first arm | Complete30-instruction /141-byte owner is instruction/edge identical |
| 305 | Signed65..75 and signed resource>=400 | Complete24-instruction /111-byte owner is instruction/edge identical |
| 320 | Signed0..90 | Both signed guards restored; shared store tail remains different |
| 404–406 | First signed0..10 interval, followed by the existing interval ladder | Lower/upper WORD guards restored; shared x87 cleanup remains different |

The accessor is ordinary `static inline short`, returning the existing
`CpuActionPolicyView::policy_counter_764`. It has no synthetic value, extra
storage, forced-inlining annotation or external address binding. The old
three captured temporaries are removed. Action320's unsigned shortcut is
replaced by the target's explicit signed lower/upper predicates; both forms
accept the same16-bit0..90 set, but only the latter explains these target
instructions. No shared header, offset, ABI or compiler flag changes.

Full canonical relocation replay confirms that the root still calls only
the five original dependencies. The accessor introduces no out-of-line call.
The third newly identical owner is action200: its two edges into the shared
x87 cleanup now agree with the original physical owner and intra-owner offset.
This is not a new function boundary or independently accepted unit.

The original C++ spelling and the compiler pass responsible for the changed
lowering remain **unknown**. The result demonstrates one natural, typed source
explanation; it does not prove the shipped code used this particular accessor.
The helper is not promoted to a general matching recipe.

## Focused canonical result

```bash
python3 scripts/build.py --unit gpt-web-aya-cpu-action-policy --compare --json
python3 scripts/audit-giant-action-owners.py aya-cpu-action-policy build/match-units/GptWeb_AyaCpuActionPolicy.obj --unit gpt-web-aya-cpu-action-policy --json
```

The whole comparison still fails at **+12E /0061280E**, target6A /candidateC6.
Candidate metadata starts at16088, with a16713-byte section tail. The
comparison-window SHA-256 is
`271db482bf39d5657ecc845cf59a396cc6805cc8af0a1e5555abbbf9f3ad971a`;
the complete canonical section-tail SHA-256 is
`03446cc0ddc49438b8753810154a7dbe4d5faf1a7a72e20d9f5beffd2f8261d2`.
Identical owner counts remain a diagnostic, not partial acceptance.

## Native complete-return checks

```bash
python3 scripts/audit-cpu-policy-paths.py build/match-units/GptWeb_AyaCpuActionPolicy.obj --root aya --counter-cases
python3 scripts/audit-cpu-policy-paths.py build/match-units/GptWeb_AyaCpuActionPolicy.obj --root aya --cases 5000
python3 scripts/audit-cpu-policy-paths.py build/match-units/GptWeb_AyaCpuActionPolicy.obj --root aya --aya-command-cases
python3 scripts/audit-cpu-policy-paths.py build/match-units/GptWeb_AyaCpuActionPolicy.obj --root aya --height-cases
```

Fresh results are **0/4164 counter**, **0/5000 finite**, **0/470 command**, and **0/368 height**
differences through genuine RET. They compare the entire7A4 actor prefix,
seeded MT state, native helper order/arguments/results, conversion inputs,
stack cleanup and x87 control word. The original helpers execute without
result substitutions. The finite matrix visits3582/4097 target instructions;
the counter matrix visits255. These are separate sampled scopes, not complete
numerical, exception or gameplay equivalence.

The new counter matrix covers all four actions, negative/endpoint/adjacent
WORD values, all four modes, both facings, eight real seeds, resource399/400/
401 and distance/height boundaries. Four positive store cases are independently
confirmed by native target execution, including action300 at90 taking the
zero-facing/zero-vertical arm. Policy-1 and peer action100 keep later policy
stores from masking those observations. Counter input SHA-256:
`d34b36f0f49ce275b71b2fe13d835d45054ae09d78a1f294939924e956232042`.

A private control changes only the accessor's return type to unsigned short.
All **32/32** mode3 action300 negative-counter cases then differ from the
original. This is a detected semantic regression, not another retained type
hypothesis. The target's signed contract is not inferred from matching size.

## Rejected broader changes and real link context

Replacing all sixteen captured action counters with field-accessor calls
gains some action owners but destroys seven previously identical policy owners;
it is discarded. Replacing the stored policy roll at+76A with repeated accessor
reads reaches19/41 owners, but worsens the large policy-region instruction/edge
differences from113 to160 and moves metadata to16240. It is also discarded.
The higher count alone does not justify changing another source contract.

The selected source is also genuinely linked with the actual94-byte SDK COFF
deque provider and the real engine/CRT dependencies, using the existing guarded
all-float diagnostic. All six switches close, with16056 reachable bytes /
4079 instructions and no alignment gap. The linked provider still replays94
bytes. The root still has119 selector sites versus target114, and five nested
sequence-table destinations versus six. No float control or link partition is
promoted into its acceptance profile. See [the ABI checkpoint](AYA_CPU_LINKED_ABI_2026_10_17.md).

## Working state and remaining work

The target remains original Japanese1.06a SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`,
root SHA-256
`7efa001552238230ac86c77f48f36a217cc486e847f85cb924527c64e2dc6e09`.
Direct Ghidra re-attests target/import identity, entry, Windows/x86 and every
mapped.text byte, saves the four predicate comments and signed764 evidence,
then reads them back in a separate process. Layout,4097 instructions and target
bytes remain unchanged. The verified private project replaces its predecessor;
the duplicate is removed. IDA preflight rejects its other target and is unused.

Reports use `build/aya-cpu-counter-*`; private controls are under
`.analysis/aya-cpu-ranges-20261017/`. The final build and native-tested COFF
objects have identical complete canonical section tails; differing COFF
timestamps are not code differences. Local CI passes180 tests. No unrelated
accepted unit or aggregate cold replay is claimed. Remaining work is original
control/float lifetimes and shared store/x87 tails across the complete root.
