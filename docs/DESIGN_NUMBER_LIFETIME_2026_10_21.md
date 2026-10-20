# CDesignNumber complete lifetime match

`CDesignNumber_scalar_deleting_destructor @40BB00` is **61/61 canonical
exact** in `gpt-web-cnumber-lifetime`. The sole affected source unit also
freshly reproduces its five existing CNumber bodies at40/11/11/11/60 bytes.
Only the new61-byte body receives new acceptance. ReimuObject496540 remains
nonexact49655F/+31; no aggregate cold replay or percentage is claimed.

## Observed target and ownership

Only the original Japanese TH10.5 v1.06a executable is used, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Target and tracking preflight pass. IDA again rejects10350095... and supplies
no semantics. There is no Ghidra process, database write or target patch.

Vtable6D6AC0 has COL6DCAB0 and type descriptor6FA478, naming
`.?AVCDesignNumber@@`. Its hierarchy contains the zero-offset, nonvirtual
CDesignObjectBase and IColor bases. Slot00 points to40BB00. The independently
observed factory path starts40B7ED: scalar new allocatesE4 bytes, primary
vptr6D6AC0 is published at40B809, CNumber vptr6C1B60 at whole+18 is published
at40B814, and CTile vptr6C0718 at whole+40 at40B81E. The owned-value pointer
at whole+3C is cleared at40B825. The allocation and actual member lifetimes
support prefix18 + CNumberCC = completeE4, rather than deriving a class layout
from the candidate instruction count.

The complete callable is `[40BB00,40BB3D)`:21 reachable instructions, two
conditional branches, two direct deallocator calls and one RET4. Every local
edge closes inside the body; three following INT3 bytes isolate its end.
The preceding accepted64-byte CDesignGage lifetime ends exactly at40BB00;
there is no preceding alignment gap. Its RTTI-owned virtual slot supplies
independent entry evidence. The full target and relocated object SHA256 is:

`57f8ee280707b10beb3dc422a404275ad1aa281b69078f8c2bbd5dec7c733336`.

ECX is the receiver, ESI preserves it, and EAX returns the original receiver.
The body publishes the member's CNumber vptr, conditionally releases the
owned pointer at+3C through6898EA, then restores IColor vptr6C0624 at tile+40,
number+18 and outer+00 in that order. It tests bit0 of the flags argument and
conditionally releases the complete receiver through the same deallocator.
No remote tail, switch table or EH region is owned by this61-byte callable.
The target contains the game's nontrivial owned-value cleanup, as do the
already accepted CNumber/CDesignGage lifetime bodies; it is not classified
from the optional receiver-free scaffold alone.

## Source and focused acceptance

`src/ui/CNumberLifetime.cpp` adds a private CDesignObjectBase lifetime view
and CDesignNumber owner containing the existing CNumberLifetime at+18. Its
ordinary implicit destructor destroys that real member before its base.
No manual vptr stores, custom ABI, padding for code generation, inert locals,
assembly or fabricated return is used. Assertions guard18/CC/E4 extents and
the consumed member/value/tile offsets. The constructor expresses the
factory-observed base initialization and emits the ordinary class lifetime;
constructor machine bytes and complete runtime virtuals are not accepted.
Original declaration spelling, full base data ownership and original TU
partition remain open.

The unchanged ordinary VC8 SP1 O2, GS-off profile naturally emits exactly61
bytes. The normal comparator replays both real deallocator REL32 fields and
all CNumber/IColor DIR32 fields using existing bindings. No external binding,
shared header, compiler flag, accepted function partition or prior signature
changes. The five existing complete functions remain exact after the source
extension. No native fixture is substituted for the full canonical result.

| Formal artifact | SHA256 |
| --- | --- |
|CRLF source|`04da04d28b19ec7c01c7233b0addfaffaa2c09ab08ebc86db41be822152bea2d`|
|COFF|`c16db61d34a7c3ddbba0cb79c209f2eae8faabdf17ead732d97f20ec2df227e8`|

The candidate, durable name, source-present row and match row are updated
together. The official origin `baseline()` supplies the new row. All196
explicit origin-rule selections are checked before/after, remain identical
and exclude this address; the origin-rule file is unchanged. This bounded
acceptance does not claim a fresh complete library-anchor replay.

`build/design-number-lifetime-20261021/` retains the baseline, frozen selected
source/object, full target packet, private probe and formal build report.
Recipes and acceptance checks are in the matching `.analysis/` directory.
Builds run serially at CPU0/nice10; no unselected large products are created.
The new source is used only by the six-function affected unit.

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-cnumber-lifetime --compare --json
python3 scripts/build.py --check
python3 scripts/validate-tracking.py --require-target
taskset -c 0 nice -n 10 python3 scripts/ci.py
git diff --check
```

The focused command must report40/11/11/11/60/61 exact. Existing runtime
initialization414E40 and other CNumber source files retain their prior state.

## Rendering lead retained for continued reconstruction

The same raw packet closes CDesignNumber's render entries40AF80/40AFC0 at
55/63 bytes and37-instruction private helper414EB0 at95 bytes. Both callers
load `this+18` into EAX;414EB0 preserves that pointer in ESI and consumes the
two float stack words with RET8. The complete raw E8/E9 encoding scan finds
only the two caller sites40AFB0/40AFF7, both validated at instruction boundaries.
No aligned .rdata/.data pointer names414EB0. This bounds the observed direct
and data surfaces; it does not exclude every computed edge.

The helper selects a value-adapter virtual slot based on member+1C. Its
integer path calls the accepted ordinary CNumber renderer414F10; the floating
path calls415050 with its owner live in ESI. A fabricated external normal
thiscall declaration would hide that private continuation contract. These
three rendering bodies, the floating continuation, their source context and
unique original types remain unselected and nonexact. The new lifetime match
confers no rendering acceptance.
