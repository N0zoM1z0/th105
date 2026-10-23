# Aya801 context retry and852 conversion-placement controls

## Observed outcome

Japanese1.06a target SHA256:
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Target/status/tracking checks pass; IDA remains rejected for wrong-image
identity. Observations use the hash-attested PE and serial native VC8 builds
of root61A290. Current game source remains74e0949's selected version.

The new807/854 lifetimes justify retrying801's target-observed sequence snapshot.
The retry still changes other actions, and the full payload grows136 bytes.
Its outside801 strict graph fails. Private diagnostics identify changes in
817/820/826/852/853/861, including floating operand order and branch sharing;
the diagnostic loses alignment at a shared alpha predicate and is explicitly
incomplete. It is not used as an equivalence proof. Earlier852 and scale
execution audits therefore do not close this new control's full impact.

The801 source control remains unselected. This does not prove the snapshot is
wrong, an original compiler boundary is impossible, or LTCG is required. It
establishes that adopting this spelling in the present source context still
needs more evidence than the already-tested852/853/861 windows.

## Exact852 window facts

The target's owner-facing product has a closed local window from CMP actor
facing=-1 at61C98C to FSTP owner+6AC at61C9C4. It is62 bytes/14 instructions.
The nested facing is read as one signed byte and sign-extended to EDX **before**
the direction branch. Its integer-to-x87 conversion is separately placed in
each arm: negative uses FILD/FLD/FCHS/FMULP; positive uses FILD/memory FMUL.

`scripts/audit-aya-object-852-facing-lifetimes.py` now emits a reproducible raw
instruction packet for that window and any supplied COFF controls. It verifies
the target identity, unique owner+6AC store, facing guard, nested byte capture
and closed local branch destinations, and lists every instruction encoding.
It reports capture width, sign-extension sites, FILD regions and FIMUL use.
These are diagnostic observations, not original C++ type or exact-root claims.

| Source form | Full payload |852 window bytes / instructions| Capture | FILD placement |
| --- | ---: | ---: | --- | --- |
|Selected signed-char local|20132|67 /16|MOV byte, later branch-local MOVSX|Both arms|
|Use float rather than double casts in multiplication|20132|67 /16|Same complete payload as selected|Both arms|
|Promoted int local|20120|56 /12|MOVSX32 before branch|Positive only; negative becomes FIMUL|
|Converted double local|20120|54 /12|MOVSX32 before branch|One common FILD before branch|
|Target|—|62 /14|MOVSX32 before branch|Both arms; no FIMUL|

All these locals hold genuinely used values; none adds inert operations or
changes the byte-width field access/ABI. The two promoted-local variants keep
4267 strict graph nodes outside852 identical to selected code. They recover
the early sign extension but change conversion placement and arithmetic form.
Neither is selected merely because its whole object is smaller.

The int-local control and the selected object were executed through6528 actual
root returns with original math/frame helpers and signed facing boundary,
nonfinite speed and masked x87 matrices. Both have zero observed differences,
including6400 owner-product write snapshots. See the
[852 execution scope](AYA_OBJECT_852_NATIVE_CONTROL_2026_10_23.md) for limits.
This does not make the int-local instructions match target. The double-local
control was inspected statically; no execution agreement is claimed for it.

## Reproducible constraints and next work

The remaining852 source/context problem is now precise: retain one promoted
signed-byte capture before the branch while preserving two branch-local FILD
conversions and the target multiplication forms. A plain int local triggers
FIMUL; a plain double local hoists FILD. Simply swapping float/double casts is
byte-neutral. Repeating those local controls without new context adds no evidence.
Original expression/visibility, branch ownership and whole-frame scratch homes
remain open. The packet exposes the instruction lifetimes needed to assess
another independently supported source-context change.

The selected source was restored and freshly rebuilt. Its full20132-byte
canonical SHA256 remains
`17585ff8bc4fadd5f63619d3d52d470440955256a820ac76ca97daa7ee31f88f`,
metadata19664. Canonical19522 comparison still fails at hex offset22,
target0F/source9B. Accepted counts and all public game source/ABI/flags/ledgers
remain unchanged; no new aggregate replay or exact credit is claimed.

Control full canonical SHA256 values:

- 801 sequence snapshot,20268 bytes:
 `110214dac416470c33335da85cb164e74b46277e4d0e43bf703a80dd946b6309`.
- 852 int local,20120 bytes:
 `dd57c6cf69859f1fee762cbaf68320fe61482052c7fbadb302867b76a78a3c5e`.
- 852 double local,20120 bytes:
 `0fdbaaed382ff3da57353c4c81c4d2c9efc4c8fb0dbdc961300ef52e6581b336`.

```sh
# Configured root remains nonexact; no acceptance follows from a successful build.
taskset -c 0 nice -n 10 python3 scripts/build.py --unit gpt-web-aya-object-vslot28-full-root --compare --json
python3 scripts/audit-aya-object-852-facing-lifetimes.py --output build/aya-801-sequence-20261023/selected-facing-facts.json
# Frozen controls may need restoring from this scope's integrity-checked archive.
python3 scripts/audit-aya-object-852-facing-lifetimes.py --object build/match-units/GptWeb_AyaObjectActionState.obj --object build/aya-801-sequence-20261023/852-int.obj --object build/aya-801-sequence-20261023/852-double.obj --object build/aya-801-sequence-20261023/snapshot.obj --output build/aya-801-sequence-20261023/facing-facts.json
python3 scripts/audit-aya-object-predicate-widths.py
python3 scripts/validate-tracking.py --require-target
taskset -c 0 nice -n 10 python3 scripts/ci.py
git diff --check
```

Reports, formal build commands, frozen source and native receipts remain under
`build/aya-801-sequence-20261023/`. The exploratory alignment recipe under
`.analysis/aya-801-sequence-20261023/` is private, incomplete and untrusted for
acceptance; the public strict graph checker was not modified or weakened.

Three completed control objects were archived after verified SHA256 round trips,
120787 to36165 bytes. `retention.json` records member/archive
hashes and unchanged target/source/current/previous-object pins. Restore from
the repository root with `tar -xzf build/aya-801-sequence-20261023/completed-controls.tar.gz`.
Current selected objects, frozen source and receipts remain directly available.
