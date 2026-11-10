# Global file-writer identity and complete save cleanup

The original Japanese TH105 1.06a executable identifies `CFileWriter` as a
global class, with RTTI name `.?AVCFileWriter@@`. Its declaration now uses
that identity. A using declaration preserves existing `th105::CFileWriter`
source references without creating a separate type. The file-handle and size
typedefs remain in `th105`; layout, ownership and virtual signatures are unchanged.

## Complete object evidence

The real GameConfig save object emits all four slots of the native vtable at
`0x006C0F4C`: scalar deletion, write, last-write size and seek. The emitted
vector-deleting weak symbol resolves to the actual scalar destructor. All five
complete method bodies, including the ordinary destructor, compare equal:

- `0x00407BF0`: destructor, 21 bytes.
- `0x00407C10`: write, 35 bytes.
- `0x00407C40`: last-write size, 4 bytes.
- `0x00407C50`: seek, 25 bytes.
- `0x00407C70`: scalar deletion, 45 bytes.

All six records in the RTTI graph compare equal, totaling 98 bytes. They cover
the type descriptor at `0x006FA420`, base descriptor, base array, hierarchy,
complete-object locator at `0x006DC9D8`, and the vtable's locator pointer.
The checks resolve every relocation and compare the full type name.

GameConfig save also has complete local equality for its 35-byte cleanup/EH
code at `0x006B7A30` and 44-byte unwind/FuncInfo section at `0x006DDB80`.
The destructor action, security-cookie check, handler entry and CxxFrameHandler3
tail all have the native ownership and destinations. The main body remains
877 bytes with exactly the existing two differences at +579 and +582: reversed
loads of the two checked-deque bound operands. Global writer identity does not
explain that residue, and no new authored exact function is recorded.

## Affected comparisons

The shared-header dependency closure contains 29 configured units. All 44
previously accepted roots replay exact, including the fourteen CSV linked roots
selected separately from that unit's already-blocked members. Every comparable
candidate retains its prior canonical hash, and the existing comparison blockers
are unchanged. The four actual writer consumers are profile data, GameConfig
save, Score persistence and replay input saving.

The three executable-source-pinned BGM list-growth, CSV deque-copy and wave
pointer-back origin proofs also pass after updating the changed header hash.
Changed TOML and relocation CSV inputs parse, and the source diff passes the
whitespace check. No broad suite or whole-corpus replay was needed for this
bounded identity correction.

Reproduce the focused builds with `scripts/build.py --unit UNIT --compare --json`
through `scripts/repo-python`. The writer check verifies current source, compiler
and object provenance before comparison.
