# CMenuBattle constructor, JP1.06a

440B50 now has complete800-byte source selected. It is nonexact: six byte
positions differ, all stack-home displacements. No800-byte exact credit is
awarded, and no matching-prefix credit is inferred.

Native SHA256:bfad683902476e8223dda0facf17873bb1a3817ac23971f6ffbb2b0de1004e3c.
Source SHA256:89bfe7afd829bd1bcb5fe79e2cb75e2410e17678eff95d0e4ad9a32bfcad80fa.

## Ownership and complete behavior

Exact callers470BC0,471340,472230 and472B20 construct this78-byte menu. The
472230 caller reaches it at472310. Vtable6C1A5C, COL6D8168 and type descriptor
6E6BDC name CMenuBattle. Its four slots are destructor440F00, noop41F890,
update4407E0 and render440780. Native publication is at440B92.

The real Menu base sets scene mode22. CDesignBase is constructed at+8, the
vector at+64 and owner pointer at+74. The constructor clears the vector,
retaining native checked begin/end and erase behavior even though it is new.

Repeated get_game_mode calls retain short-circuit order. Modes0/1/2 load
data/menu/battle/pauseStory.dat with entries0/1/3/4. Mode7 loads
pausePractice.dat with entries0/1/4. Other modes load pause.dat with0/1/2/3/4.
Each branch binds its own control loop to IDs100,110,... and enables them.
The vertical cursor uses InputManager+3C, vector count, zero selection/window
and zero page size. State byte+4 is cleared last.

Raw CFG covers236 instructions and797 bytes. Three internal alignment bytes
at440C7D are compared strictly; the complete800-byte body ends at RET4.
The full27-byte EH handler6B90DE points to FuncInfo6DF0AC with three states
and unwind map6DF094: base, design+8 and vector+64 cleanup.

## Residual and bounded controls

Native saves this at stack+14, the clear end iterator at+18 and erase return
temporary at+1C. Source chooses+1C,+14,+18 respectively. The same two later
this reloads account for the remaining displacement differences. All other
bytes, branches, calls, loop alignment and constant stores agree.

Owner initialization in the initializer list, explicit erase(begin,end), and
the existing owner's vector<int> element type leave those six differences
unchanged. The selected source keeps vector<int>, natural clear and owner
initialization. The initial GS-off probe was783 bytes; native EH-cookie
prologue establishes the standard GS-enabled profile used for the800-byte
comparison. No artificial stack locals, alignment, lifetime extension or
register forcing is added.

No shared header or accepted caller changed. The constructor-facing source
uses the existing real CDesignBase and MenuCursorBindings definitions. Native
data/RTTI/handler aliases are isolated, with all bytes fingerprinted.

Focused command:
scripts/repo-python scripts/build.py --unit exact-first-battle-menu-constructor --compare --json

Receipts and raw facts are under build/frontier-battle-menu-constructor-20261029/.
Default CI and whitespace checks cover final tracking/progress changes.
