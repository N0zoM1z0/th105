# PNG loader: complete703-byte source, one byte remains

CBitmapData::load_png41A910 now emits703 bytes in the real bitmap/reader/PNG/zlib
CIL. Full canonical replay differs only at41AAAD: target3B, source1F. These are
the base/index fields of the row-address LEA. The handler, cleanup funclet,
FuncInfo and unwind map all independently match. The function remains nonexact
and earns no callable, prefix or EH-only credit. Totals remain1539 /436171.

## Target-backed source recovery

The native width publication reads info->width once, writes object+10 and then
object+8. Chained assignment preserves that actual read/store epoch rather than
reloading through a potentially aliased pointer. The row scale is truncated to
one byte and then held as an int; the original source held it as a byte for too
long, losing the observed register lifetime and independent cleanup branch.

Native24/32 format dispatch is reproduced by the two-case switch. Both height
entry guards compare the unsigned PNG dimension strictly greater than zero.
These changes recover the complete code layout without inert storage, forced
registers, new safety behavior or modified exception semantics. The old ordinary
680/703 and initial real-CIL671 results are superseded; the earlier assertion
that only FileReader late-inline/EH remained was incomplete.

Raw calls still pass the actual string1.5.2 at6D6E04. The embedded provider's
provenance is libpng1.2.5. Neither is silently changed to make them agree, and
this work does not claim native runtime decode success. The24-bit row scratch
ownership and all original success/failure paths are preserved as observed.

The first width/lifetime correction emitted700; format switch emitted703.
Positive unsigned height guards removed the two branch-opcode differences.
A signed row-offset control and indexed-address spelling were byte-neutral;
neither supplies new evidence about original source spelling. The selected
source retains its original unsigned offset and pointer expression. Do not
waive the remaining SIB byte or infer an LTCG impossibility from these controls.

## Real callback pointer witness

The native loader passes game callback41A8E0 to png_set_read_fn. Before replaying
that pointer, link_png_read_callback=true requires the original PNG provider
graph, unique actual CIL function ownership, its existing target anchor and
complete33-byte callback equality, including the real png_get_io_ptr call.
Only a PUSH of that verified code pointer is supported. This is not an arbitrary
code address disguised as data; altered code, aliases, foreign ownership, missing
provider proof and unsupported address uses fail. The callback was already exact
and is not counted a second time.

The PNG descriptor moved from the ordinary bitmap unit to
exact-first-csv-file-loading, where the real normal-ABI method is exported and
its full EH is checked. Its callback remains selected in the original unit and
is additionally verified in this image solely to establish the pointer role.
The native scalar destruction and libpng functions are real providers, not stubs.

## Validation

Both affected units rebuilt and all17 previously accepted functions remained
exact, including newly accepted DDS696. Complete current PNG comparison has no
unresolved relocations and reports one byte mismatch; complete cleanup records
and callback code are in the same report. A whole-byte census reconstructed
from the comparator's own recorded relocations is checked against its canonical
SHA256 before enumerating differences. It is diagnostic only, not alternate
acceptance. No full-corpus replay or behavior matrix was introduced.

Private source, object, full report and difference census are in
build/frontier-png-loader-20261030 and the matching .analysis folder.

Reproduce with scripts/repo-python scripts/build.py --unit
exact-first-csv-file-loading --json, then scripts/repo-python
scripts/compare-linked-unit.py exact-first-csv-file-loading --address 0x0041A910
--json. Expected result is mismatch at413, not exact, despite equal703-byte size.
