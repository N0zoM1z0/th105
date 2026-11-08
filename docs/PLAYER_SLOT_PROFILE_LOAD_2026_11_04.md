# Player-slot profile load refinement

The original `0x00431AC0` function loads a profile string and fixed blocks, then
reads 20 card decks. The source now accesses the actual 20 deque members by
index in the natural loop, instead of carrying an incremented deque pointer.
The target's complete 728-byte body is SHA-256
`eb6b0f3cd77778190614684696f4b3b12f608e146dc2b3f88ce625f65cf43a61`.

A pinned VC8 /GS build emits 728 bytes, with resolved target comparison hash
`d9803d674411bd515e852adb1cb89775be7d8fec8833f47a474c42fc8fc16439`.
The complete resolved comparison has two unequal bytes, at +540 and +543:
the two inputs to one checked-deque bound addition are loaded in the reverse
order. The previous 723-byte pointer-loop candidate omitted a checked end
validation. Both field reads and the iterator check are retained naturally,
without synthetic guards or forced registers. This is nonexact and adds no
exact bytes. The remote EH comparison is now complete. The later real-reader change below
also verifies its five method bodies and table roles; the RTTI type name still
differs from the target, and live file behavior has not been tested.

Reproduce with `scripts/repo-python scripts/build.py --unit
exact-first-player-slot-profile-load --compare --json`.


## November 8: complete remote EH comparison

The emitted cleanup/handler section now matches all 64 bytes at `0x006B8130`,
including the handler at `0x006B8148`. The unwind table and FuncInfo match all
60 bytes at `0x006DE35C`; FuncInfo begins at `0x006DE374`. Every code and data
relocation was resolved and compared, with no masked fields.

The three unwind actions destroy the profile-path string at frame -0x2c,
temporary concatenated string at -0x48, and file reader at -0x60. Their state
chain is `[-1, 0, 0]`. The main entry references this handler, and the two cookie
checks and final CxxFrameHandler3 tail agree with the original. The reader
cleanup emitted by the local view also matches the entire existing 21-byte
CFileReader destructor at `0x0040CEB0`, including its vtable and CloseHandle
operands.

Target and candidate SHA-256 values are equal for each completed region:

- EH code: `bff449ec6cd73d1d7a68d45209b7f3eb7980e3cba7d08c0c2f63a5f5613c0a48`
- EH metadata: `83f967c610fc4d4328e1b7e12732dcee94e24b46d306762a86d43e83336bcc03`
- Reader cleanup: `dad42cb5e1a8ff41065fb7bf4b6b2a99bd227e762aa254687db8b6358ac925a8`

The fresh main-body comparison still has precisely the two differences at
+540 and +543. Matching these support regions does not promote the root or
add authored exact bytes. This removes the EH uncertainty and narrows further
work to the main body's checked-deque load order and the real reader type.

Reproduction: build the configured unit, then run
`scripts/repo-python .analysis/frontier-profile-load-context-20261108/check-eh.py`.
The private check verifies current source/compiler/object provenance, complete
section ownership, all relocation roles, the unwind state chain and every
cleanup/handler boundary. Results are in
`build/frontier-profile-load-context-20261108/baseline.json` and `eh.json`.


## Use the existing CFileReader provider

Profile loading now constructs the real `CFileReader` and calls its `read`
method. The duplicate reader class and its undefined seek/size declarations
are removed, along with the vtable alias in the match recipe. The translation
unit includes the existing reader implementation, as the repository already
does for CSV loading, battle recordings and the connect address list. A narrow
read-only handle view remains solely for the open test; no shared reader
header or layout changed.

The entire 728-byte main candidate retains its previous hash and two
mismatches, so using the real provider does not close the deque scheduling
residual. The complete 64-byte EH code, 60-byte metadata and 21-byte destructor
also keep their equal hashes. The five native method slots at `0x006C0F34`
now have actual emitted source, all locally byte-equal with their relocations:

- Scalar deletion `0x0041B890`, 45 bytes. The COFF weak slot resolves to this
  emitted scalar destructor.
- Read `0x0040CED0`, 35 bytes.
- Last read size `0x00407C40`, 4 bytes.
- Seek `0x00407C50`, 25 bytes.
- File size `0x0040CF00`, 13 bytes.

The source RTTI string is `.?AVCFileReader@th105@@`, while the target string is
`.?AVCFileReader@@`. Their names do not match, even though the method bodies
and resolved twenty-byte table agree. This is a remaining whole-object
identity issue, not a reason to alter target bytes or mask a comparison.

Final receipts are `real-reader-final.json` and `real-reader-eh.json` in the
same evidence directory. The private check now uses the actual reader symbols
and verifies the weak-slot fallback and all five complete method bodies.
No new authored exact functions are recorded.
