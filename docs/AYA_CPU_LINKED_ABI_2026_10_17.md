# Aya CPU linked dependency ABI and switch closure, October 17

Follow-up: [signed counter read sites](AYA_CPU_COUNTER_READS_2026_10_17.md)
now change the selected source and recover three additional identical owners.
The byte-neutral source and linked shape measurements below describe this
earlier ABI checkpoint.

The active root remains `Aya_update_cpu_action_policy @ 0x006126E0`,
16,032 callable bytes /4,097 instructions. Its retained source and ordinary
match unit are unchanged and **nonexact**. This batch closes the distinction
between a genuinely resolved link and a target-compatible dependency ABI.
No authored exact bytes are added.

## Observed dependency specialization

```bash
python3 scripts/probe-aya-cpu-ltcg.py --float-aliases all --deque-boundary visible
python3 scripts/probe-aya-cpu-ltcg.py --float-aliases all --deque-boundary coff
python3 scripts/probe-aya-cpu-ltcg.py --float-aliases preserve --deque-boundary coff
```

With the real deque template visible to LTCG, the all-float control generates
a **79-byte** helper. It receives the deque in **EDI**, specializes the index
to zero and returns without stack-argument cleanup. Its map symbol still
spells the ordinary `std::deque<FighterSequenceSlot>::operator[]` signature.
The original `4399C0` instead has a **94-byte** ECX/index-on-stack interface
and `RET 4`. Mapping the specialized function to that original callee by name
would give the CPU caller the wrong ABI. The linked caller and its private
helper are internally consistent; they are incompatible with that target
callee substitution.

The new `coff` boundary uses an actual explicit SDK template instantiation,
compiled without /GL. An `extern template` declaration suppresses the root's
own instantiation. No facade body or fake caller is supplied. The provider
is compared before linking, then the **complete linked provider** is replayed
again, resolving only its attested `__invalid_parameter_noinfo` calls. Both
comparisons reproduce the original94 bytes. The canonical provider SHA-256 is
`5e6d9bae7c00a857a51b7ca00c03b37c95e1986a9e389d56e35924b205f7491b`.
This is a library witness, not another authored match or a new duplicate unit.

All links continue to use actual accepted MT, selector and strict-FP angle
objects, the real VC8 CRT/SDK libraries and normal DLL CRT startup. The probe
records input hashes and commands, plus the generated provider source/object
hashes. There are no executable ABS bindings, source stubs, unresolved-link
overrides or manufactured callers. The candidate images are not executed.

## Complete linked control flow

The probe now checks the full root envelope rather than inferring progress
from a prologue. All six indirect dispatches require relocated destination
pointers, bounded byte-index loads and index values within their actual
tables. A raw traversal rejects escaping/instruction-interior edges,
unresolved indirect exits, internal calls and unreachable nonpadding code.
The only accepted unreachable gaps are observed1–3 byte VC8 alignment
instructions immediately after a final RET and before four-byte-aligned
metadata. These bytes are reported separately from reachable instructions.
The root itself is **not canonically relocated or accepted** by this probe.

| Source control / deque boundary | Reachable bytes / instructions | Metadata offset | Selector call sites | Deque ABI |
| --- | --- | --- | --- | --- |
| All float / visible | 16,106 /4,045 | 16,108 | 119 | private79-byte, incompatible |
| All float / real COFF | 16,021 /4,069 | 16,024 | 119 | target94-byte, exact witness |
| Retained types / real COFF | 15,850 /4,055 | 15,852 | 110 | target94-byte, exact witness |
| Original target | 16,032 /4,097 | 16,032 | 114 | original94-byte |

Each candidate has25 deque,7 conversion,5 angle and1 raw-MT call sites.
All three close through six switches. The actions410/412 sequence table has
**five** candidate destinations against **six** original destinations; its
13 byte indices are validated against the five actual entries, not padded
with an invented sixth destination. Thus the caller's source/control and
sharing differences remain visible even after the dependency ABI is restored.

The all-float/COFF control reproduces the original first16 bytes, including
the12-byte frame and entry EBX/ESI/EDI saves. This is only a short entry
observation. EBP is saved later in the dispatcher: target+148 versus
candidate+139. Constant materialization also differs, and full instruction/
edge diagnosis still retains only14/41 identical physical owners. The private
diagnostic compares literal read widths/bits and named callees; it is not
canonical root replay and earns no partial byte credit.

## Rejected controls and remaining work

Private /Os controls change the required primary-switch topology and are
rejected. Eliminating constant aliases alone leaves the retained-type linked
shape unchanged; eliminating value aliases changes it without restoring the
target. Eliminating both produces the same measured shape as the all-float
control. None of these type, expression, flag or partition experiments is
promoted into the retained root source or its acceptance profile.

The original source's exact local lifetimes, interval-test lowering and
shared x87/store tails remain unknown. The evidence supports a genuine,
target-compatible opaque template boundary for further experiments; it does
not identify the original TU partition or prove that this CPU root used LTCG.
The next matching work must recover those control/lifetime facts across the
whole root, preserving the verified helper ABI.

## Verification and working state

The target remains original Japanese1.06a SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`;
root SHA-256
`7efa001552238230ac86c77f48f36a217cc486e847f85cb924527c64e2dc6e09`.
The mandatory IDA preflight rejects its different target and is unused.
No target metadata, shared header, compiler profile or accepted unit changes.
The prior native root checks retain their earlier checkpoint scope; no new
native/gameplay or aggregate cold replay is claimed for this probe-only change.

Fresh focused dependency builds pass their existing canonical comparisons.
Three new target-independent regression cases reject a missing switch
destination, a same-named helper with a different receiver/cleanup, and an
unattested runtime call. Local CI passes180 tests. Receipts are below
`build/aya-cpu-ltcg-probes/{all,all-coff-deque,preserve-coff-deque}/`; summary
reports use `build/aya-cpu-shape-*.json`. Private controls are below
`.analysis/aya-cpu-linked-shape-20261017/`. Discarded private binaries are
removed; source, commands and reports retain the experiment record.
