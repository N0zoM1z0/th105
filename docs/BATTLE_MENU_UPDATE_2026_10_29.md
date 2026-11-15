# Battle pause-menu update

`CMenuBattle::update` (0x4407E0, 797 bytes) is exact, together with its owned
suffix: alignment, a four-entry state dispatch table, a 42-byte state remap
and a five-entry action table. The CMenuBattle vtable 0x6C1A5C owns slot 08 at
0x4407E0; the exact render 0x440780 and deleting destructor 0x440F00 share the
table.

## Behaviour

A pending owner transition at +0x84 returns true at once. State 0 runs the
main menu with the vertical cursor and input events 39/40/41.
- Entry 0 closes the menu.
- Entries 1/2 open the 330-byte `CProfileKeyConfig` for player 0/1, keeping
  the allocation-failure and cleanup paths.
- Entries 3/4 request owner transition 1/2. In a session with option 1:
  - with auto-save, the menu refreshes the continue state first;
  - otherwise it asks the replay-save question instead (state 30/40).

States 30/40 handle the replay-save prompt.
- Result 2 cancels and clears the state.
- Result 3 advances to 31/41, saves the replay and shows the saved message.
- Result 4 applies the requested transition and falls through to the result 2
  reset.

States 31/41 set transition 1 for 31 and 2 otherwise once the confirmation
completes.

## What made it exact

- The three outer cases end with `break;` before one trailing `return true;`,
  so VC8 loads the constant 1 into EBX once at the switch head.
- The auto-save branch repeats the outer `if (ENTRY == 3) end = 1; else end =
  2; return true;`. VC8 cross-jumps the outer copy into it, so the session
  check jumps into the auto-save tail and the message branch is laid out
  after it, as in the target. With a single shared tail the message branch
  stays in source order.
