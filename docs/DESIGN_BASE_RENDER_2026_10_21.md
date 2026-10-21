# Complete CDesignBase render exact

Target: original Japanese TH10.5 v1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
`CDesignBase_render @ 0040BC80` is complete canonical **135/135** under:

```bash
python3 scripts/build.py --unit gpt-web-design-base-render --compare --json
```

Target and source canonical SHA256:
`444a0a976e2fb28a6de4f0f9808eeab071c8c207c5d221d0514c97e2355fd655`.

## Observed boundary, ABI and behavior

RTTI `.?AVCDesignBase@@`, COL `6D7594`, and primary vtable `6C08AC` own slot
+24 at `6C08D0`, pointing to `40BC80`. All 54 instructions in
`40BC80..40BD06` are reachable and close through the one ordinary RET.
Following nine CC bytes precede the next candidate `40BD10`; they are excluded.
ECX is the recovered 34h design owner and no argument is popped.

The function compares its checked **member** iterator at +2C/+30 with the
native list at +14's end. It validates ownership/dereference, calls each
object's vslot +14, validates/increments the member iterator after the
callback, then assigns `objects.begin()` back to that member. The function
does not initialize the member to begin before traversing: resuming the
current position is part of the observed behavior. The new C++ source uses
the native list and real member iterator directly.

## Complete compiler comparison

An ordinary VC8 SP1 O2 COFF build of the same source emits 124 bytes with the
same traversal and final reset, but omits the target's eight-byte-aligned
frame. A resolved `/GL /LTCG` build naturally emits all 135 target bytes,
including the frame and loop alignment. No aligned local, unused object,
attribute, assembly, fabricated register interface or copied instruction is
introduced. This is positive evidence for this function's compiler phase;
it does not settle other functions' frame mismatches or original TU partition.

The formal linked comparator independently bounds the source function from
its unique CIL-owned export/map entry and closed CFG. It resolves the five
invalid-parameter calls through the actual pinned VC8 runtime import library,
then replays their named REL32 fields to target `68A143`. All other bytes must
agree. There are no absolute game-data references, vtable stores, or internal
image-address substitutions.

The linked unit explicitly declares `link_data_targets = []`. Contract
validation now accepts this truthful empty list; omission and unbound absolute
game addresses still fail. The new workflow test exercises that distinction
and a data-free virtual dispatch. No unused data binding is invented to satisfy
the former nonempty-list restriction. The four predecessor linked units were
rebuilt serially and all five of their accepted functions remain exact:
scene retirement, packet-pool destruction, shared token release, and both
package-archive lifecycle functions. No unrelated ordinary COFF unit changed.

## Durable state and remaining unknowns

`src/ui/DesignBaseRender.cpp` and `gpt-web-design-base-render` are selected.
The function, origin, mapping, implementation and exact ledgers record one
new complete function/135 bytes. All 198 predecessor origin-rule selections
are unchanged and disjoint; no broad anchor replay or cold aggregate claim is
needed. The shared layout header and existing relocation ledgers are unchanged
from the preceding native-vector checkpoint.

Raw target facts, ordinary/linked controls, full formal comparison, acceptance
receipt and predecessor replays are in `build/design-base-render-20261021/`;
private drivers are in `.analysis/design-base-render-20261021/`. IDA preflight
again rejects the attached wrong-target session; no database semantics or
metadata changes were used. Builds ran serially on CPU0 at nice10.

Original source spelling/TU context and the rest of CDesignBase runtime remain
open. In particular, the identified 2666-byte `40B000` loader still has no
selected provider source or exact result. Reimu496540 also remains nonexact;
this checkpoint does not change its status.
