# Replay browser

`ReplayBrowseRuntimeView::update_browse_state` (0x446860, 511 bytes) is exact.
The exact dispatcher 0x446C90 tail-jumps to it at 0x446D05.

## Policy

One input-record pointer supplies the horizontal, confirm and cancel state.
- Horizontal +1/-1 pages forward or back. Only the other branch calls the
  vertical cursor update. Each successful movement emits event 39.
- Confirm emits 40.
  - On a directory row it pushes the old selection onto the checked
    `list<int>`, enters the directory and refreshes the file list.
  - On a file row it looks the row up twice, as the target does, capturing the
    name before the current directory. It formats a 260-byte `wsprintfA` path
    and passes it to the replay loader 0x42C5C0; a successful load sets scene
    mode 6.
- Cancel emits 41 and asks the file list for its parent.
  - At the root it clears state 4 and recolors the item pointers at F4/F8
    white.
  - Otherwise it restores the previous selection from the list's back,
    pops it and refreshes.
- The result is always 1.

## What made it exact

The confirm branch ends with its own `return 1;` before `else if (cancel)`;
the function keeps its trailing `return 1;`. With only the trailing return,
VC8 kept the constant 1 in BL and duplicated the GS epilogue on three paths
(559 bytes). With the extra return, every path jumps to one epilogue that loads
`mov al, 1`, as in the target. Returning from every branch is worse, and so is
splitting the `else if` into a separate `if`.

Direct owner-member accesses are needed for the 0x108-byte frame. A
function-wide set of named cursor/list references hoists receiver lifetimes and
gives a 0x10C frame.
