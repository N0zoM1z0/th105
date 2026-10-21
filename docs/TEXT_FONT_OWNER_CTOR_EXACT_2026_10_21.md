# Native font owner construction: complete138/138 exact

`TextFontOwner194::TextFontOwner194 @ 0x00411430` is canonical **138/138 bytes**,
all29 reachable instructions, from genuine C++ GL/LTCG source. Ordinary COFF
from the same selected source is142 bytes/33 instructions, nonexact+1. The
compiler phase, rather than a fabricated receiver declaration, resolves it.

Only original Japanese TH10.5 v1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. Target/status/tracking preflights pass. IDA rejects its wrong open
executable; raw PE instructions and pinned compiler/linker evidence supply the
new facts. No database semantics/writes or original-byte patches are used.

## Independent boundary, layout and ownership

The hash-attested target closes all138 bytes through its single RET4114B9;
six following INT3 bytes are outside the body. Complete target and canonical
source SHA256:
`de916b659088e2537ea0915c832bd7df93a934638ac508840ae8260a018ef6ee`.
Exact PlayerSlotRecord431440 and NetworkSessionResult44DCB0 independently call
the constructor at431482/44DCF4, before configuring and drawing through the
same physical owner. No IDA candidate size alone establishes this boundary.

Real native source has:

- A0x128 configuration subobject at00C. Its default constructor writes weight400,
  three zero style bytes, zero origins/spacings and the observed100000 word,
  while leaving uninitialized fields untouched. Actual CreateFontA begin calls
  independently establish font use of the style offsets. Historical count/
  duration labels in other source views are working names, not original API names.
- `std::list<unsigned *>` at15C, with the ordinary native sentinel allocation,
  head160 and count164. Its initial allocator bytes are not a debug proxy.
- `std::string` at170, with the target empty SSO size184/capacity188/buffer174
  publications. No hand-written string/list layout or lifecycle replaces it.
- A normal constructor body clearing DC000/font004/original-font008,
  destination144 and active/base-color154/158, then the compiler's normal
  EAX=this return. No manual vptr store, fake return or synthetic initialization
  of target-unwritten state is introduced.

The0x194 source view and its00C/15C/170 offsets are compile-time guarded and
corroborated by exact caller storage and observed markup accesses at18C/190.
Natural C++ alignment supplies the config gaps; no extra alignment array or
forced stack storage is added. This establishes a faithful source view for
the observed ABI. Original nominal class spelling, original TU and any
unobserved original-type details remain unknown.

## Why the ordinary and linked forms differ

Ordinary COFF retains a separate list receiver in EDI and prepares ECX for the
native `_Buynode` call. Those extra setup/save instructions and shorter EDI-relative
stores yield142 bytes. Genuine GL/LTCG can inspect that same native helper,
remove its unused receiver preparation and retain the source owner's ESI-relative
stores. The entire constructor then agrees with all138 target bytes.

The sole target call is411474 ->4040B0. It resolves to the unique real CIL
`std::list<unsigned *>::_Buynode` map identity. Source is not modified to declare
an external register-private allocator or call a fake provider.

The helper is already excluded by its independent handle-manager/container
ownership rule. Its target26 bytes/11 instructions have SHA256
`51243f7677d4ddc7fee890ea0c868b516ac40dfcf9644172bef7bbb3083caaa6`.
An independent current-source PE/map check verifies all26 bytes after its sole
named allocation REL32 replay. The real source call reaches a linker thunk
whose import is `MSVCR80.dll!??2@YAPAXI@Z`, corresponding to original scalar
operator new689DCB. The first ECX use is LEA of EAX+4, defining scratch before
any read; no incoming receiver value is needed. This validates the removed
setup rather than assuming register independence from size alone.

That helper receives **no new authored source, origin or exact credit**. Its
byte shape is not an origin fingerprint: the already-documented authored
collision-list sentinel can share the same bytes. Existing caller/container
provenance remains the exclusion basis; the new full hash and exact constructor
edge strengthen the existing rule without broadening it.

## Reproducible full comparison

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-text-font-owner --compare --json
```

Selected source SHA256:
`88a150c957b583a2d9e865ec2ae4501ac13ad22f06bbe43d8bf2d76452c948f4`.
The unit uses the existing `linked_candidate` / `vc8-sp1-ltcg-o2` contract,
GS enabled, and the real normal constructor export. Complete source symbol/CFG
ownership and exact target bytes close; only the one named sentinel E8 field
is replayed. There are no root absolute data references, native vtables,
cleanup-EH surfaces, warning exceptions or partial-prefix selectors.

Five already-attested GS-report runtime IAT keys resolve genuine support-library
code. An initial link without them correctly failed unresolved-symbol checks;
no linker warning/error gate was waived. Their existing global bindings are
unchanged and none is a new root data operand or game-code implementation.

Repeated complete builds and a fresh accepted-unit cold replay all report
138/138 exact. Receipts and source/PE/map/provenance snapshots are under
`build/font-owner-20261021/`; private recipes are under
`.analysis/font-owner-20261021/`. No source/body cropping, assembly, byte arrays,
inert local, forced prologue or register ABI is used.

## Ledgers, scope and remaining work

Only411430 is newly exact: **one function /138 authored bytes**. It moves from
the old manual family-origin rule to the canonical exact baseline. That manual
rule now selects only destructor4114C0 and configure4115A0, preserving their649
bytes, eight exact caller edges and complete hashes. The two remain source-absent
and nonexact; they are not inherited into constructor acceptance.

Every predecessor accepted unit definition is unchanged. The new isolated
constructor file adds no shared header, compiler-profile or relocation-ledger
change, so only the new unit needs a cold replay. Existing exact caller sources
and the nonexact font traversal/begin/end/texture units are untouched. No full
aggregate cold verification is claimed; generated progress is a ledger snapshot.

```bash
python3 scripts/validate-tracking.py --require-target
taskset -c 0 nice -n 10 python3 scripts/ci.py
git diff --check
```

Next: real owner destruction/configuration and glyph/markup/blend closure for
an honest complete font TU. Constructor exactness does not resolve begin's
56/64-byte frame difference, end's EDI save scope, text entry's aligned EBP
frame or the larger Reimu root. Those remain explicitly nonexact.

## Complete native destructor follow-up

[The destructor checkpoint](TEXT_FONT_OWNER_DTOR_EXACT_2026_10_21.md) adds real
owner destruction in this TU at210/210. Current source hash changes to635607c5,
while constructor138/de916b65 remains exact on the affected-unit cold replay.
Earlier source hashes and independent-unit scope above describe the frozen
constructor-only checkpoint. The native71-byte list cleanup is separately
qualified as a compiler witness/exclusion, with no authored credit. Only
configure439 remains in the manual family rule and without selected source.
