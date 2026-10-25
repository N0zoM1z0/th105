# Rectangle primitive4012A0: independent complete review

The complete rectangle provider is **nonexact**. The current source emits394
bytes against395 target bytes; complete canonical relocation replay finds85
unequal positions in the common394-byte range, first at4012A9. Its finite
source-lifetime lane is closed after two whole-payload byte-neutral controls.
No implemented.csv or matches.csv row is added.

## Observed target evidence

Only original Japanese1.06a SHA
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
was inspected. Fresh target/tracking checks passed. IDA preflight again rejected
the10350095 target; no semantic information or writes from that session were
used. Raw PE decoding and the execution checks below are independent of IDA.

The whole callable is4012A0..40142B exclusive,395 bytes, SHA
`71aa186253ca2f14ce6ffc30ac72ef5a5ff29b01f2e2e85e3493c4f6d113b347`.
All128 decoded instructions are reachable. Both RET24 sites,401351 and401428,
close inside this extent; there are no escaping direct edges, indirect jumps
or unaccounted alignment operations. Five following INT3 bytes separate401430.
The scalar local arena is50 bytes; ESI/EDI are saved, without EH/GS setup.
The existing authored-origin rule independently pins the primitive chain and
eight exact rectangle callers. New exact debug callback45E950 is corroborating
caller evidence, not an exactness claim for this provider.

The low byte of argument six selects the paths. Zero calls401180 four times,
in this order: left edge top-to-bottom, right edge top-to-bottom, top edge
left-to-right, bottom edge left-to-right. The receiver and packed color are
forwarded; EAX from the fourth call reaches the return.

Any nonzero selector builds four20-byte XYZRHW/color vertices, in strip order
left/top, right/top, left/bottom, right/bottom. Each X/Y subtracts the canonical
**float0.5 at6CD140**. The eight subtractions remain distinct x87 operations;
their results are stored into float fields. A retained0.5 x87 value supplies
**all four Z fields**; RHW is1.0 and all four colors are the input color.
The original first source incorrectly used Z0.0; this was corrected from
complete x87-stack tracing and separately confirmed by native execution.

The filled path clears texture handle/stage0 through404DF0 with ECX702798,
then calls device slots164/14C: SetFVF44, DrawPrimitiveUP(type5, count2,
vertex pointer, stride20). The device field at receiver+4 is loaded again
after SetFVF. Its final EAX reaches RET24. This review adds no exact/origin
credit to the line or texture-binding providers.

## Source and complete comparisons

`src/engine/RectanglePrimitive.cpp` is a complete hypothesis using the existing
RenderModeManager/Title declarations and a declaration-only line receiver view.
It does not change shared headers, compiler profiles, prior bindings or data
relocation rows. The line view is never instantiated. All actual vertex fields
and both returns are represented; no fake return, padding, assembly or inert
locals are used.

| Complete trial | Bytes | Result |
| --- | ---: | --- |
| first complete source |400 | Compared immediately; first4012A9, incorrect Z0 |
| observed Z0.5 correction |404 | Nonexact; default compiler folds/reuses coordinate results and promotes the subtraction constant |
| local fenv_access(on) |394 | Native distinct single-precision operand/subtraction/store graph; full canonical85 unequal positions |
| actual common result across branches |394 | Whole canonical payload identical to preceding source |
| ordinary draw_line declaration on the same receiver in a private copied header |394 | Whole canonical payload identical; public header unchanged |

The two neutral controls are retained privately; this finite return/receiver
lane is closed. No option/spelling/type grid was run. The local fenv hypothesis
is supported by native repeated operations/operand width and tested over the
whole function; it does not identify original pragmas or establish exception
environment equivalence.

Two independent public builds (`formal-first.json`, `formal-second.json`) and
the full COFF-section audit reproduce394 bytes with canonical SHA
`c5f8d5e4a581b0774a2b4579f93a2e20e94db915c7d6b088ce10618510bfa3dd`.
Both REL32 providers and all DIR32 operands are replayed normally. There are85
unequal positions plus one absent target byte. The target saves EDI before the
branch, whereas this candidate saves it only on the outline path. Filled-path
argument/color scheduling and stack displacements also differ. An equal local
instruction sequence or these small sizes do not establish canonical equality.

## Focused execution evidence and limits

`scripts/audit-rectangle-primitive-target.py` pins the entire target and its
closed CFG, then executes the complete body in the pinned Unicorn environment
with typed observers for the external line, texture and D3D calls. Three finite
cases select0,1,255. These resolve the concrete x87 depth ambiguity and check
line order, coordinates/color, vertex order/Z/RHW, argument cleanup, saved
registers and final drawing result. SetFVF's observer changes receiver+4 to a
different device, proving the later DrawPrimitiveUP reload under that case.
The corrected candidate produces identical observations in all three cases.
The first complete Z0.0 source is a retained negative control: the same audit
rejects it with `filled coordinate/depth/rhw/color changed`.

These are call-observer cases, not implementations of D3D/resource services,
a general equivalence proof, or a broad behavior matrix. NaNs, unusual FP
environments, precise exception timing, original nominal types/source spelling,
and original TU/backend context remain unknown. Do not infer LTCG necessity
from this standalone mismatch. Resume the closed lane only with new independent
evidence; return to a complete medium/large frontier candidate next.

## Reproduction and retained receipts

```bash
scripts/repo-python scripts/build.py --unit exact-first-rectangle-primitive --compare --json
scripts/repo-python scripts/audit-rectangle-primitive-target.py
scripts/repo-python scripts/audit-rectangle-primitive-target.py --object build/match-units/ExactFirst_RectanglePrimitive.obj
```

The build and object audit currently exit1/nonexact; target-only audit exits0.
Receipts are below `build/rectangle-4012a0-20261026/`; first/control sources and
private target/COFF recipes are below `.analysis/rectangle-4012a0-20261026/`.
All heavy jobs use CPU0/nice10 and run serially. Available memory remained over
10GB; swap stayed134MB during the focused work.
Fresh `cold-all.log` passes all526 accepted units/1414 functions under the new
manifest. Exact totals remain1414 functions/385903 bytes; this rectangle adds
no exact bytes. `origins-check.log` and `literals-check.log` also pass.
