# Complete Ogg PCM wrapper in its real service graph

The unchanged ordinary C++ PCM wrapper418B70 now matches all252 bytes:
SHA2560dc9e4a97d421f4a70c85adc63d05400cd89dd4d910cef847f80771eb0439d0d.
It is selected in exact-first-bgm-load-service, not as an exported standalone
PCM root. No C++ source, floating-point pragma, compiler flag, SDK provider or
calling-convention declaration is changed. The real CIL context recovers the
native layout naturally. No copied bytes, fake frame or partial credit is used.

## Complete native scope and fresh source evidence

The original Japanese1.06a function is [418B70,418C6C),252 bytes. All normal
exits have RET8. Its five direct calls are the named original providers:
ov_read, ov_time_tell, two ov_time_seek calls, and memset. There are no absolute
data references in this body. Every instruction and all five E8 displacements
are compared after actual symbol relocation; no byte is masked or discarded.
The prior qword current-time lifetime and scoped precise source remain intact.

A retained-image scan first found the252-byte shape in the actual service
source graph. That was only a lead. A fresh configured build of
BgmServiceLoad.cpp, including BgmStreamRuntime.cpp and the real pinned providers,
reproduces it while preserving service play4036E0/351 and preparation402960/159
as canonical exact. The earlier exported PCM shape was251/252; exporting this
private body is not necessary to verify it and would change its compiler context.

The leaf contract is moved, not duplicated, between the two existing units.
Removing the old PCM export preserves all three accepted stream-context bodies:
Ogg open418A10/291, SFL418D10/484 and DirectSound stop4185E0/45 freshly pass.
No other stream function is accepted as a side effect.

## Exact-rooted bounded graph proof

The separate stdcall_graph contract is rooted in a fresh whole exact replay of
service play4036E0. Source and target have the same complete direct call graph:

-4036E0 ->402A00 at4037AB;
-402A00 ->402C10 at402B33 and402B58;
-402A00 ->402FC0 at402B25;
-402C10 ->418B70 at402CDC;
-402FC0 ->418B70 at40319A.

That is five graph nodes, five edges and six physical direct calls. The three
intermediate methods are not byte-exact: this source graph emits339/358 start,
918/943 update and741/806 handoff. Those are complete caller provenance/edge
observations, not semantic or byte-equivalence claims about the intermediates.

All graph nodes must have reviewed source in the actual quoted-include closure
of the same CIL input. Each private node needs one unaliased, unexported MAP
identity owned by that source object. Both complete caller CFGs are decoded;
all actual calls between graph nodes must agree with every declared site set,
including detection of additional or missing calls. Source-only caller address
roles are independently classified by the existing machinery. The graph must
be bounded, acyclic, root-reachable and leaf-reaching, with no unrelated nodes.
The exact root must map each actual first-level callee and its current full
source/native hashes must agree with the fresh canonical root report.

The leaf remains ordinary unsigned-return stdcall source. Every source/native
return has the declared observed cleanup8; external tails, absolute/segmented
state, exception-registration state and leaf PE address relocations are rejected.
The final canonical comparison permits only fully named call relocations and
no data-reference rewrites. It still requires zero differences over the whole
252-byte function. A call-graph witness alone cannot make a mismatching leaf exact.

This is a new narrow proof, not a relaxation of source_only_caller. That prior
constructor/stdcall-plus-EH path is unchanged and still rejects a no-EH leaf.
Twelve tests cover the positive graph plus wrong ABI/scope, false exact root,
cycles/disconnected nodes, missing/additional/wrong calls, absent source,
foreign/aliased/exported nodes, cleanup mismatches, address/EH references and
replay restrictions. The new module is included in the build-input digest.
No private register ABI is written into the source or manifest declarations.

## Reproduction and accounting

    taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py --unit exact-first-bgm-load-service --compare --json
    taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py --unit exact-first-bgm-stream-runtime --compare --json
    scripts/repo-python scripts/compare-linked-unit.py exact-first-bgm-stream-runtime --address 0x00418A10 --address 0x00418D10 --address 0x004185E0 --json
    scripts/repo-python -m unittest discover -s tests -p test_linked_stdcall_graph.py

The service unit has three exact functions. The stream unit still has four
nonexact comparisons, so its aggregate comparison_failed status is not called
an exact pass. Reports and controls are retained under
build/frontier-pcm-real-caller-20261101: fresh discovery/formal.json, graph.json,
canonical-diagnostic.json, formal-graph.json, stream-focused.json, the final
current-input replays and CI logs. No generated DLL executes.

Only252 authored bytes and one exact function are added:1584 exact functions /
449606 bytes. Source1783, authored1803, mapped1810, excluded1798, review426 and
765 units remain. The old Ogg authored-origin rule skips PCM now and retains
only the591-byte scheduler. No global origin rewrite or cold corpus build.
