# Profile deck editor constructor 44AAC0

Actual global CSprite (nine slots) and CTile now replace the local views below.
Fresh current measurements and initialization corrections are recorded in
PROFILE_DECK_REAL_SPRITES_2026_11_02.md; older slot/prefix descriptions are historical.

Complete constructor source is now present in ProfileDeckConstructor.cpp.
The latest full root remains nonexact 2132/native2136, first+1127/44AF27.
See the October 31 real-provider follow-up below; earlier control sizes are historical. Two separately
bounded number-adapter virtuals are canonical exact 7/15; only those 22 bytes
enter matches.csv. Unit: exact-first-profile-deck-constructor.

## Native ownership and boundaries

Exact character-select update 4485B0 calls the constructor at 44863D for the
6B0-byte menu. The body publishes vtable 6C222C, COL 6D8610, type descriptor
6E6DDC naming CProfileDeckEdit. Its four slots own the existing destructor,
no-op, update and render. Native main SHA-256:
676347f8efb9b309b9813cad58a5acad51732fc7573a85f3dfe8a3ffb2a14012.
577 instructions decode;2133 bytes are reachable. The remaining three bytes
at 44AF2D are LEA ECX,[ECX] alignment, included in the strict 2136-byte comparison.
RET 12 ends at 44B317. The GS frame is 66C; handler 6B9FBA is 46 bytes, with
FuncInfo6DFB14 and twelve unwind entries at 6DFB38.

The existing isolated Ghidra project was opened read-only. Executable hash,
entry 68B9D2, language/compiler and every mapped text byte were independently
attested before decompilation; all metadata changes were discarded. Correct
callee purges and the two actual virtual-call signatures repair the navigation
output's initial stack confusion. Raw instructions, not that output, establish
the source contracts. No primary analysis project or target bytes changed.

## Recovered source and type facts

- Real Menu, design, polymorphic sprites/tile, resource owner, checked map/deque
  and four guide lifetimes generate construction/EH naturally. There are no
  copied instructions, handwritten vptr stores, artificial locals or manual
  container nodes in this constructor.
- The constructor saves the incoming stand-sprite pointer at+0C. This scoped
  constructor view does not alter the older unused scalar label in the shared
  runtime header. Original complete source declaration/TU spelling is unknown.
- The actual local buffers are 260-byte resource path and 1024-byte formatted
  text, beside a real 128h-byte font configuration and std::string. Resource
  loading supplies width/height to the actual sprite texture virtual.
- Digit text is formatted ten times and appended with its real lengths, then
  a38-byte grey disabled label is appended. Font height 14/weight300, color
  bytes, outline/wrap flags and 256-square text atlas match native values.
- Design bindings preserve the three enabled controls, two five-item groups,
  five checked map lookups and the three numeric value owners. Their deletion
  uses operator delete, as the actual INumberValue interface has no destructor
  slot. Constructor common-resource colors are 96,96,255; do not copy the
  destructor's different 255,96,96 order.
- The spell filter, current deck import, first-record display, horizontal-input
  cursor and guide IDs13/14/2/10 retain their actual ordering and guards.

RTTI corrected two initial declaration hypotheses before selection: CTile has
only four virtual slots, unlike CSprite's eight; its texture wrapper here is
nonvirtual. The numeric adapter is TNumberValue<char*> (PAD), not unsigned-char
PAE. Native getters sign-extend the byte. The final constructor view therefore
uses char-valued bindings and the existing real CNumberRuntime.hpp template.
Main constructor bytes are unchanged by these type corrections, but the signed
leaf bodies and table contracts are independently validated.

## Independent exact leaves

Vtable 6C21A4, COL 6D85C4, type descriptor 6E6DB8 names the custom application
TNumberValue<char*> class. Its slot 0 is 448B20 and slot 4 is 448B30. Both are
fully reachable through RET 0, with no relocations or helper assumptions:

- Integer getter 7/7, SHA 79b5fefc8a033d9d48471853b2dc9fc1652a9cfed1c76623683afd1548eb89df.
- Floating getter 15/15, SHA 57f1ba7118a25bab763c7a7e92cb75155589d82cd7fc08a3ecea15503aa8658d.

They are authored application value-adapter methods, not standard-library
ownership inferred from a generic template name. Constructor binding sites,
native RTTI and the observed byte-pointer dereference establish their role.
The larger constructor and other providers inherit no equality from them.

## Complete comparisons and limits

Initial full 2151-byte canonical constructor SHA:
41b1494cc09e6af1a3fed1c035d18ddac7e220fdb9d9f2e3445d17d98bb3c60e.
The later input-axis correction below supersedes that candidate.
There are 1125 unequal positions including length;15 extra bytes does not mean
only 15 byte differences. All 62 direct-call destinations/order agree. The first
391 bytes agree, including the member construction prefix. Remaining width/
height/result stack homes and checked-lookup/loop lowering stay unresolved.

The first full source was compiled before controls. Native literal-store order
is retained. A class-return call-site alternative shrinks the frame to 668 and
is unselected; explicit lookup branches grow the body to 2187; pointer-walk
loops and paired dimensions remain 2151 without closing the first residual.
Do not add padding, dummy liveness or force register placement to close them.

All new data bindings are isolated and fingerprinted, including complete target
strings, the role-local font receiver, owned vtables and full handler. Existing
headers, aliases and accepted consumers remain unchanged. The ordinary formal
report compares the 2136-byte ledger body; the private complete comparison also
replays every relocation in the 2151-byte source, including its later cookie
call. Neither report grants constructor credit.

Receipts and raw facts: build/frontier-profile-deck-constructor-20261029/
formal-build.json, native-facts.json, number-getters.json and compare.json.
The read-only Ghidra logs and negative controls are in the same scope. Private
manual source and replay scripts are retained under its .analysis counterpart.
Default CI and diff checks run after final tracking/progress changes; no cold
corpus replay is needed for this new isolated unit.

## Input-axis correction after filter recovery

Native 44B277 adds 38 to the InputManager pointer. The actual shared layout
places horizontal at 38, vertical at 3C and button 0 at 40. The earlier constructor
used vertical, a semantic error now corrected to horizontal. This category
cursor differs from the card-list vertical cursor recovered in 449E90.

Whole source remains 2151/native2136, first+391, SHA
d15195f10de8db59e60b9cc23d1e050536225e099374a90ff74a58bd16b60774. Both selected
signed-char getters replay 7/7 and 15/15 unchanged. No exact credit is added.

## Real lookup and returned-handle context, 2026-10-31

The successful practice-menu constructor supplied independent evidence for the
actual design lookup body and the ordinary TextureHandleResult temporary.
Applying both to this complete constructor closes its earlier frame/texture
homes and lookup differences: the new full candidate is 2132/native2136, with
first difference at 44AF27 (+1127). No prefix or byte credit is awarded.

DesignObjectLookup.cpp replaces the declaration-only tree-query facade and
handwritten per-site lookup expansion. The existing return-by-value texture
interface supplies the real hidden temporary instead of the named raw handle.
No shared headers or helper implementations change. The old nominal source
partition is not claimed.

The first residual is now EDI/EBP assignment across the two five-item binding
loops; a real pointer-walk control leaves 2132 bytes and merely moves the first
difference to 44AF26, so the simpler indexed loops remain selected. Do not add
dummy lifetimes, register constraints or padding.

The exact signed-byte adapter methods 448B20/448B30 still replay 7/15. This is the
only consumer of the changed constructor source, and unrelated exact receipts are
preserved.
