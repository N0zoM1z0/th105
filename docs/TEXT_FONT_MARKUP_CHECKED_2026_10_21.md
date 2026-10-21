# Font markup: complete checked-character comparison and live stack facts

The real checked-character operation called by markup411FA0 now reproduces
**all33 bytes /14 instructions at412920**, canonical SHA256
`9a726759df76947994237e1bf64c917c2581fbfe91fbc4e851c9b7076940121a`.
It is configured in the same font-render unit and has six actual parent calls.
The candidate is identified but its origin remains review: no authored mapping,
source-present entry, matches row or progress credit is added.

Parent source is now1728/455, canonical
`a3c2e09c65e0af2c63da0a20950896721a938a3299bc3cf12b4ed600f99296ff`, versus
target1744/463. It remains nonexact411FB0/+16, frame788 versus796. Native
EDX font/ECX height output/two-stack-word/RET8 entry is retained. Ten other
complete font bodies are unchanged, including the323-byte render caller.

Only original Japanese TH10.5 v1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is analyzed. Required target/status/tracking preflights pass. IDA rejects its
wrong open image, so this work uses the hash-attested raw PE and compiler output.

## Observed operation, source model and ownership limit

The complete target helper saves ESI, takes native string in EAX and unsigned
index in EDI, compares size14 against index, calls the native range-error
function on failure, chooses SSO4 or heap-pointer4 using capacity18, and returns
the character address in EAX. Both normal paths restore ESI and RET without
stack arguments. All33 bytes are reachable; there is no EH frame, internal
alignment, data relocation, cropped tail or copied implementation.

The only direct callers in tracked main instruction streams are the six
markup hex-character accesses. A real typed file-local operation
`return text->at(index);` through the unmodified pinned VC8 native header
naturally emits the complete target EAX/EDI body. Cdecl/stdcall controls emit
identical code and caller ABI. The selected C++ spelling is ordinary cdecl;
there is no fabricated fastcall declaration or register facade.

Previously, ordinary string-member calls used ECX plus a stack index in the
source parent. Those preparation sequences did not represent the target's
private EAX/EDI calls. The new operation preserves the observed checked access,
including the failure boundary, while retaining all six real calls under the
existing local O2/Ob1 profile. No original wrapper name/type/TU is established.

The original function could be an authored wrapper around this native operation
or a compiler-specialized library method. The library skill explicitly says
to “Leave the row in review when evidence cannot distinguish authored code
from a library”. That [stop rule](../.agents/skills/th105-library/SKILL.md)
applies to origin/credit here. Native operation equality alone does not resolve
that ownership question. Upstream source is neither copied nor modified.

`functions.csv` records the provisional role, complete boundary, ABI and
evidence; `reccmp-functions.csv`, `implemented.csv`, `matches.csv` and the
unknown origin row stay unchanged. The manifest gains one diagnostic function
(538 units /1507 configured functions), with the original three accepted
font leaves retained. A zero-difference function report in a mixed unit is not automatic
authored acceptance.

## Runtime identity checked beyond the old IDA label

The target412928 call reaches665B33. It is a complete63-byte native range-error
body, rather than an import thunk. The old runtime exclusion rule relied only
on IDA names. Fresh corroboration uses pinned VC8 SP1:

- `libcpmt.lib` SHA256
  `e1b17cb213bfcf77e3c0988f8cb33ec8be143872d1c52de62c5da07ea1eb8031`;
- member `build/intel/mt_obj/string.obj`, SHA256
  `b2c7c0bc31c4e276c1657300d954990d5766d0e18509b76692ca80d5689df521`;
- its defined native `_String_base::_Xran` and `_Xlen` symbols, both63 bytes;
- all31 nonrelocation bytes in each corresponding target body;
- target messages `invalid string position` / `string too long`, independent
  out_of_range / length_error RTTI, and native string/logic_error construction,
  vtable, throw-info and CxxThrowException relocation roles.

The existing two-function runtime rule now requires full target body hashes
and documents this archive/literal/RTTI evidence. Its classification/counts do
not change. This is positive runtime identity corroboration, not a canonical
full EH/metadata comparison or actual C++ exception execution. No runtime exact
or new exclusion credit is claimed.

```bash
python3 scripts/extract-msvc-library-object.py --library libcpmt \
  --object string.obj --output build/font-markup-stack-20261021/vc8-string.obj
```

## Stack values and bounded execution

Six actual parent runs (br, ruby-close and color on both sides) retain fixed
frame stack reads/writes and call checkpoints. Target preserves original token
length on stack and length+1 in EBP; source caches length+1 and keeps original
length in EBP during allocation. At strncpy_s, pending outgoing arguments are
16 versus20 bytes because source delays cleaning the allocation argument.
Token context and later color bytes occupy different reused slots. These are
observed value/lifetime differences; vacant slots do not prove extra fields or
an original sizeof. No frame filler or unproved type-size change is selected.

Two additional natural controls, implicit token conversion and a font-reference
parameter, both emit identical1728-byte parent code. Neither explains the frame
residual. Source/target four-state EH graphs still agree; handler, funclet,
destructor-state and metadata differences remain unqualified.

All **92/92** independent actual-helper cases pass:27 normal SSO/heap character
references and65 unsigned full-bit range boundaries. Checks cover return
address/byte, saved ESI/EDI, ESP and the scratch registers actually preserved by
the body. Invalid inputs stop at the actual Xran entry; they do not execute
platform exception construction or unwind runtime.

Only **2400 affected parent cases** replay: two valid hex colors, a short hex
token, a missing color argument and a missing terminator, crossed with the
previous dimension/state/string/output modes. All pass, executing real hex45
and checked-character33, the latter6720 times per side;480 cases reach the
native Xran boundary. The setter is loaded but not executed in this scope.
Other CRT/STL/font/color providers remain explicit observers.

Complete old/new instruction/CFG comparison proves373 instruction pairs and36
internal edges unchanged outside color-call setup and natural strlen-loop
alignment. All nonrelative instruction bytes outside that window agree; branch
destinations are checked against surviving control entries. That proves the
scope for retaining earlier br/ruby/accent evidence without repeating8640
cases. The full render caller hash99116ccc is unchanged, so its280 cases are
not replayed. No GDI, actual throw/EH, allocation-failure, arbitrary-alias or
protected-page claim is made.

## Focused build, artifacts and next work

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-text-font-render --compare --json
python3 scripts/function-origins.py --check
python3 scripts/validate-tracking.py --require-target
taskset -c 0 nice -n 10 python3 scripts/ci.py
git diff --check
```

The font command reports comparison_failed with eight nonexact functions,
three accepted exact leaves (setter45/hex45/blend289) and the uncredited
checked-character33 comparison. All twelve extents resolve without failures.
Only this accepted unit rebuilds: no header/layout/profile/existing data alias,
other accepted unit definition or object partition changes. Manifest bookkeeping
changes its conservative global digest; other units' source/flags stay the same.
Ten prior full bodies,
including the433-byte accent tail, are unchanged. Aggregate replay is separate;
authored exact counts and SVG remain unchanged.

Selected COFF, full canonical/target code, actual-call witness, stack/CFG/EH
facts, library packet and execution receipts remain under
`build/font-markup-stack-20261021/`. Private recipes/controls are under
`.analysis/font-markup-stack-20261021/`. Completed unselected outputs are
compressed only after per-file SHA256 archive readback; no binary/report is
committed.

Next: original-length/allocation-size lifetimes, outgoing stack cleanup,
destructor-state scheduling and the8-byte frame residual. Glyph coordinate
ordering and Reimu496540/nonexact49655F/+31 remain open.
