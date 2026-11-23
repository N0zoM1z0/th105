# VC8 moves the common Fighter sequence tail before x87 lowering

The target places the sequence tail of common Fighter `0x004740C0` at
`0x00474992`, inside action 73. Actions 75 and 88 jump to it with an x87
zero live. In the current source the three actions also share one tail.
VC8 initially keeps it in the source position, then moves it to action 88
before lowering the comparison to an x87 `fcomp`. Tune the block placement
before changing the comparison or the virtual call's register choice.

## Read-only compiler trace

The trace uses the repository's VC8 SP1 14.00.50727.762, `/O2 /GS- /GR
/EHsc /MT`, and the same game-specific Wine prefix. Wine/GDB runs headless.
The on-disk `c2.dll` hash is pinned at
`497d1ffe57f75db8b458167bdea475f3962829e139b355a2672a4ef51c716413`.
The loaded image is at `0x10B00000`. A breakpoint at its wide compiler-pass
entry confirms that CL passes `-Og -Ob2 -Gy -EHs -MT`. The listing adds
`/FAcs`. Complete relocated equality against the ordinary build verifies
that the listing and breakpoints preserve the generated function and tables.

The node stamped with the source line of the horizontal-velocity test
keeps its identity across the following observations in each process.
Addresses in the table belong to this build of `c2.dll`.

| Observation | Where the horizontal-velocity test appears |
| --- | --- |
| `0x10C064F9`, after reading the function's intermediate language | In action 73, before the action 75 and 88 guards |
| `0x10C06C53`, before the call to `0x10B26CA0` | Still in action 73 |
| `0x10B26CA8`, before `0x10B281E0` | Still in action 73 |
| `0x10B26CAE`, immediately after `0x10B281E0` | After the action 88 guard |
| `0x10C065F8`, after the call to `0x10C07400` | Lowered to an x87 compare node in the new position |
| `0x10B2419F`, after native instruction encoding | `fcomp [esi+0xF4]` at function offset `+0xDD5`. The two earlier cases branch there from `+0x8D0` and `+0xAA7`. |

For the graph reads, follow the first instruction through
`dword(dword(dword(function + 8)) + 0x1C)`. Each instruction record starts
with its next pointer, has its opcode at `+4`, and stores a relative
source line as a word at `+0x14`. The original source lines 466, 468, 539
and 619 identify the 73 guard, the moved comparison, the 75 guard and the
88 guard. `0x10B281E0` walks a reverse block order rooted at `[graph+8]`,
following each block's `+0x10` pointer. It calls `0x10B28270` to write the
physical successor and splice the instruction list. The input order
already puts selection after action 88. The baseline has the selection
test at reverse index 439 and the final action-88 guard at 441. Omitting
action 88 in scratch puts the selection test at 451 and the final action-75
guard at 454. Track the predecessor that contributes the selected order
when preparing a variant that preserves all three actions.
The COFF encoder's return at `0x10B2419F` exposes the current
instruction record in EDI, the output offset at `[ESI+0x18]`, the encoded
length in EAX, and the bytes at `[ESP+0x48]`. The raw target and the fresh
owner audit supply the native and candidate offsets independently.

## Source and translation-unit controls

Making the exact `classify_fighter_x_boundary` definition visible in the
carrier left its standalone body exact at `0x00435910` (59/59 bytes).
The giant root retained 18 of its 30 calls, shrank to 9,145 bytes including
tables and no longer kept the same action-entry topology. This is a
measured effect of definition visibility under the same profile. Retain the
declaration-only boundary in this carrier while the native calls remain
present. The control uses the body from `StageGeometry.cpp`, which reads
the typed X coordinate and compares it to the stage thresholds.

Using explicit zero comparisons in the three actions, spelling the byte
conversion at the landing predicate, and naming the selection label make
the shared behavior visible in the source. The rebuilt complete envelope
is identical to the previous 10,801-byte baseline after all 396 relocations
are replayed. Duplicating the selection tails regresses the owner
diagnostic from 53 to 51 out of 66. Moving action 73's ordinary motion to
the guarded arm ahead of selection is byte-neutral. In action 88, splitting
the float guard from the integer guards or putting the motion return first
is also byte-neutral. Duplicating just its selection with a reversed
velocity test loses the previously matching action 799 owner.

The complete target envelope is 10,736 bytes, including 66 jump words,
241 remap bytes and one alignment byte. The ordinary build still reports its first
callable difference at `+0x14`. There are eight register-indirect tail jumps
at `0x474703`, `0x47486D`, `0x474A7B`, `0x475584`, `0x47563B`,
`0x476037`, `0x4760BE` and `0x476203`. Each loads virtual slot `+0x14`
and restores the caller frame before jumping. In all fifteen roster vtables
that slot points to the exact 138-byte `next_sequence_block` at
`0x0045C220`. The current compact-switch verifier will need to recognize
these virtual exits for final strict acceptance.

The focused build and owner commands are in the
[giant root review](GIANT_ROOT_REVIEW_2026_11_23.md#reproduce-the-selected-baselines).
The private driver and retained trace inputs are under `build/common-vc8/`.
