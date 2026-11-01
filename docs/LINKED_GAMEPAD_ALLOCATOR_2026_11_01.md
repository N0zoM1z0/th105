# Actual gamepad-state allocator, original VC8 import context

Native40E000/84 is whole canonical and inventory-unique from the original
std::allocator<RawGamepadState>::allocate emitted by unchanged
src/input/DirectInputGamepadBootstrap.cpp and its real InputManager closure.
Its complete SHA256 is
36502b5f91e3706b5b840d9820c39f62ccba19dc0ba021e32a51a46b21339225.
Only this84-byte compiler/library body is classified; no authored credit.

## Evidence and context

The real source zeroes an80-byte RawGamepadState and assigns the enumerated
unsigned-byte device count to the actual state vector. Existing source asserts
sizeof(RawGamepadState)==80. No synthetic stride record, source edits, private
register convention, noinline, fabricated caller or helper export is used.
Original template code naturally specializes count in ECX, checks overflow
against80, multiplies by80 and reaches the ordinary new/exception/throw entries.

The origin validator builds this existing source with VC8 SP1/O2/GL/GS and
original import CRT. Only the real public enumeration callback and initialization
are exports. The allocator is unexported and uniquely owned by the actual CIL
object. Source closure pins use Git-normalized newlines; four original standard
headers and the compiler are pinned. The original ordinary comparison unit,
source and flags remain unchanged. This separate origin-only build recipe is
recorded in the validator and its proof, rather than replacing that unit.

The earlier static whole-source context did not recover this allocator. The
new import context is motivated by the independently verified private ECX
allocator and actual MSVCR80 imports, not an arbitrary flag grid. Initial linker
errors for five Kernel32 GS-support imports were resolved through already
attested import bindings. No DLL was executed.

## Complete proof

All84 bytes and all reachable instructions are retained. Normal RET and the
terminal CALL to the independently proved noncontinuable CRT throw close every
path. REL32 fields17/57/80 resolve to named operator new689DCB,
exception(char const*&)689F1C and CxxThrowException68A153. HIGHLOW fields62/75
are actual ThrowInfo6E3C18 and stack bad_alloc vptr6C05A0. No masks or unaccounted
absolute fields are permitted. All other bytes are unchanged; the complete
canonical candidate has one hit across the function inventory.

Five source runtime entries must be complete six-byte MSVCR80.dll import
thunks with the correct imported names. Native throw74, exception record32,
noncontinuable flag1 and RaiseException IAT are reattested. Complete bad_alloc
ThrowInfo16, array12, two catchable records28 each and full TypeDescriptors are
canonical. Actual bad_alloc/type_info RTTI, whole destructor401630/11 and
copy402680/25 also pass. Support bodies already owned elsewhere receive no
additional credit.

The shared low-level allocator CFG helper accepts explicit84 in addition to
existing78/85 contracts; its default remains85. The generic linked decoder and
all existing origin thresholds remain unchanged. Fresh byte allocator78/input
owner266 and old static bad_alloc five-body gates pass after this extension.
Eight synthetic tests and nine actual target-byte corruption controls reject
wrong scope, extent, families, metadata, calls, paths and parent identity.

## Honest residuals and validation

The linked initialization is182/native176, not exact. Its complete native hash
and both source/native closed CFGs are checked only as owner evidence. Callback
and parent addresses are not body equality claims. The unchanged ordinary
source freshly replays327/native334 callback and176/native176 initialization
with first mismatch0/+2, respectively. Existing separate axis166 is freshly
exact. No callback-pointer mapping or blanket linked-parent acceptance is added.

Evidence: build/origin-anchors/linked-gamepad-allocator.json and
build/frontier-gamepad-import-20261101/{ordinary-roots,axis,mutations}.json;
byte-regression.log and static-regression.log. The final narrow origin replay,
CI and diff check accompany the checkpoint. Excluded2009/review363; authored
exact1431/443916, authored1655, source1635, mapped1820 and units777 stay unchanged.
Remaining16/32-byte-element allocator candidates are unaccepted.
