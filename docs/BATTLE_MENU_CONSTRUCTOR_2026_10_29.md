# CMenuBattle constructor, JP1.06a

440B50 now has complete 800-byte source selected. It is nonexact: six byte
positions differ, all stack-home displacements. No 800-byte exact credit is
awarded, and no matching-prefix credit is inferred.

Native SHA256:bfad683902476e8223dda0facf17873bb1a3817ac23971f6ffbb2b0de1004e3c.
Source SHA 256:89bfe7afd829bd1bcb5fe79e2cb75e2410e17678eff95d0e4ad9a32bfcad80fa.

## Ownership and complete behavior

Exact callers 470BC0,471340,472230 and 472B20 construct this 78-byte menu. The
472230 caller reaches it at 472310. Vtable 6C1A5C, COL 6D8168 and type descriptor
6E6BDC name CMenuBattle. Its four slots are destructor 440F00, noop41F890,
update 4407E0 and render 440780. Native publication is at 440B92.

The real Menu base sets scene mode 22. CDesignBase is constructed at+8, the
vector at+64 and owner pointer at+74. The constructor clears the vector,
retaining native checked begin/end and erase behavior even though it is new.

Repeated get_game_mode calls retain short-circuit order. Modes 0/1/2 load
data/menu/battle/pauseStory.dat with entries 0/1/3/4. Mode 7 loads
pausePractice.dat with entries 0/1/4. Other modes load pause.dat with 0/1/2/3/4.
Each branch binds its own control loop to IDs100,110,... and enables them.
The vertical cursor uses InputManager+3C, vector count, zero selection/window
and zero page size. State byte+4 is cleared last.

Raw CFG covers 236 instructions and 797 bytes. Three internal alignment bytes
at 440C7D are compared strictly; the complete 800-byte body ends at RET4.
The full 27-byte EH handler 6B90DE points to FuncInfo6DF0AC with three states
and unwind map 6DF094: base, design+8 and vector+64 cleanup.

## Residual and bounded controls

Native saves this at stack+14, the clear end iterator at+18 and erase return
temporary at+1C. Source chooses+1C,+14,+18 respectively. The same two later
this reloads account for the remaining displacement differences. All other
bytes, branches, calls, loop alignment and constant stores agree.

Owner initialization in the initializer list, explicit erase(begin,end), and
the existing owner's vector<int> element type leave those six differences
unchanged. The selected source keeps vector<int>, natural clear and owner
initialization. The initial GS-off probe was 783 bytes; native EH-cookie
prologue establishes the standard GS-enabled profile used for the 800-byte
comparison. No artificial stack locals, alignment, lifetime extension or
register forcing is added.

No shared header or accepted caller changed. The constructor-facing source
uses the existing real CDesignBase and MenuCursorBindings definitions. Native
data/RTTI/handler aliases are isolated, with all bytes fingerprinted.

Focused command:
scripts/repo-python scripts/build.py --unit exact-first-battle-menu-constructor --compare --json

Receipts and raw facts are under build/frontier-battle-menu-constructor-20261029/.
Default CI and whitespace checks cover final tracking/progress changes.

## Independently exact Menu base destructor

The real Menu.hpp destructor emitted by this constructor matches 440730 at
17/17, SHA 041143495bbeacdd9c97700dd1b4986e311b93024ef1cfa92b904e0659c9ccbc.
It republishes RTTI-owned Menu vtable 6C196C and sets authored scene mode 22.
Native constructor cleanup 6B90C0 tail-calls440730; the existing exact scalar
deleting destructor 440750 independently contains the same destruction policy.
This is an authored base-class lifecycle action, not an empty generated thunk.

The complete 17-byte symbol has no suffix and grants 17 new bytes only.
The 800-byte constructor remains unchanged with six differences. Receipt:
formal-with-menu-base.json in the same evidence directory. No source or
shared header edit was required to emit this already-defined method.
