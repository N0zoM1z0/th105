# Practice menu constructor: 826 bytes exact

CMenuPractice construction at 0x00446170 is canonical exact **826/826**,
SHA-256 d6b96b6857e92da2490a7c6b4817725bbeffd518dda38b66be8a7d0436cc0d18.
This adds one source-present, authored and exact function.
Incremental totals are 1547 exact functions / 439428 bytes, 1741 source-present,
1761 authored and 846 review candidates.

## Target evidence

Only the pinned original Japanese 1.06a executable is used. Fresh Factory-native
IDA metadata, entry point and five mapped 16-byte samples were checked against
the raw PE; inventory/disassembly/decompiler/callers/callees probes were retained.
The decompiler is a navigation hypothesis. Raw instructions and the strict COFF
comparison establish the result.

The existing 0x288 CMenuPractice layout is independently anchored by its exact
destructor, render and subcursor methods. Vtable6C1F98, COL6D83FC and type
descriptor6E6CF0 name CMenuPractice. Exact472230 calls this constructor at4722EC.
The body contains227 decoded instructions, including the compared NOP44630F,
and ends at RET4 at4464A7. No partial or loop-only credit is used.

## Ordinary source and lifetime

The real Menu base publishes scene mode22. GuideOverlay at8, the zero texture
handle atB4, tileB8, design160 and ten vector<UiDesignObject*> members at1BC
retain their normal constructor and exception ownership. Owner284 and the
existing practice-settings pointer are assigned before cursor initialization.

The vertical cursor binds active input+3C, count10, zero selection/window/page.
The design loads data/menu/practice/practice.dat. Ten category objects bind IDs
1000,1100,...1900 and become enabled. Their option groups use counts
{0,1,6,4,4,5,2,4,0,0}; each lookup retains its missing-result zero, appends the
pointer, then enables the indexed entry. No new null guard is invented.

The weather texture data/menu/practice/Weather_list.bmp supplies its width
and height. The tile uses the returned handle, full width and height24.
Guide7 becomes visible, stateB0 is cleared, subcursor0 is configured and the
final scene mode22 store is retained.

Two real provider boundaries explain the code generation:
- The already authored MenuCursorState::bind_vertical body preserves the native
  initialization/store schedule before the design virtual call.
- The already authored CDesignBase::find_object body preserves the checked tree
  iterator and output-pointer lifetime inside the option loop.

DesignObjectLookup.cpp now shares that unchanged lookup definition between the
existing design renderer and this constructor. No second handwritten tree
algorithm or fake helper is introduced.

The texture load uses the existing TitleResourceManagerValueView return-by-value
interface already used by the key-config constructor. Its ordinary
TextureHandleResult temporary supplies the real hidden result storage.
An explicit named raw handle produced the wrong stack coloring; the natural
temporary restores saved-this+34, width+30, height+38 and the reused result+2C.
No buffer is resized, no unused storage is added, and no register/ABI is forced.

## Complete cleanup and affected verification

The private COFF relocation audit compares all98 bytes at6B98D0..6B9931:
five unwind actions and the full security-cookie/CxxFrameHandler3 handler.
It also compares all76 bytes of FuncInfo6DF6C0 and its five-entry unwind table.
Only actual DIR32/REL32 fields with explicit native semantic targets are replayed;
unsupported relocation kinds or nonzero addends fail. All bytes match.
This is independent full cleanup evidence, not a relaxation of the public
.text-only body comparator.

Formal command:

    scripts/repo-python scripts/build.py --unit exact-first-practice-menu-constructor --compare --json

Actual include traversal finds only the new constructor and
gpt-web-design-base-render affected by the shared lookup extraction.
All seven accepted design-render functions freshly remain exact. No shared
header or old caller changes, unrelated cold replay or gameplay matrix is used.

Receipts and reproducible private scripts are under
build/frontier-practice-constructor-20261031/ and its .analysis counterpart.
The fresh analysis preflight is under build/frontier-medium-discovery-20261031/.
The origin row is updated incrementally through the existing canonical baseline;
unchanged origin evidence is retained. Progress is regenerated and final CI
and whitespace checks gate the local checkpoint. No remote push is performed.
