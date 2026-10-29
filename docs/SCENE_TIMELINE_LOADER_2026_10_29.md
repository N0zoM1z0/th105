# Complete Opening/Ending timeline loader

4540F0 now has complete selected source for the18 registered command IDs,
including all three native switches. It remains nonexact and adds no exact
bytes. Source ownership is independently established by exact Ending entry
41E790 calling at41E7AF and exact Opening construction41F970 at41F9D2.

## Complete target boundary

Hash-attested raw PE analysis decodes all482 instructions and reaches every
instruction in the1584-byte callable through45471D RET4. The dispatch at454183
uses nine targets plus an18-byte command-index map. Sampler dispatch45427B has
four targets and texture-anchor dispatch454325 has five. No indirect jump is
left unqualified.

The callable SHA256 is:
efccda2b957a6bdc376a7dfad705583f8363e1a5b1b413a2ccbafce4eff6a00b.
The complete1676-byte payload extends through45477C, including92 table/alignment
bytes; the next four bytes are INT3 padding before454780. Payload SHA256:
b6bb1b77c0258c4c24bf3ff0eeec71ea11409e7f1af88d4d91e0dc13fe1af973.
These extra data bytes are checked independently, not added to callable credit.

## Source behavior

The loader first calls the script reader with option0 and returns false on
failure. Success sets BPM120 and clears previous/accumulated timing, then reads
commands until exhaustion. It does not invent object/container resets.

- BPM0 accumulates unsigned32-bit tick delta *60000 / BPM, then publishes the
  new tick and BPM. BGM2 assigns the stored music path.
- Picture1 ignores an empty filename. Otherwise it reuses the object-ID entry
  or appends a real7C RenderTimelineEntry and inserts its address. Four sampler
  choices set1/3 modes. Texture tokens enter the actual unsigned deque000;
  fresh CSpriteEx values enter deque014. Five anchor choices use zero, half,
  bottom-left, top-right or bottom-right offsets, followed by the requested
  blend mode. Unknown sampler/anchor values keep the target's existing behavior.
- Float commands3/4/5/6/11/12/13 and color commands7/8/9/10 require an existing
  object ID. They compute start/end from real float tick/BPM/time conversions,
  double60000 arithmetic and unsigned result conversion; then insert the full
  command into the start-time-ordered multiset. Float and integer target
  storage retain their native widths.
- Interval14 updates the existing record's duration. Notify16 inserts equal
  start/end times with type16. Its other record fields are not initialized by
  native code and remain unfilled in source. End17 sets the overall end time.
  Registered play15 and unknown IDs have no loader action.

Completion clears start_tick004 and event_flag08C, then returns true in AL.
The containing94-byte source view is pointer-only; it is not allocated or
constructed. Real command subclasses, records, checked containers and sprite
lifetimes are reused. There are no manual vptrs/nodes, defensive input guards,
register annotations or synthetic runtime calls.

## First comparison and residual

The first complete source compiles before any spelling controls. It emits1590
callable bytes plus two alignment bytes and92 table bytes:1684 total. Native
code/payload are1584/1676. The full comparison has1466 unequal overlapping byte
positions, beginning+51 where this/zero registers are exchanged. An eight-byte
payload-size difference does not mean only eight bytes differ.

Source payload SHA256:
3fe89dd318f686b0dfdc28bb4cbb35642d667d09c6f1006f5f5e82687481cd77.
The ordinary unit report hashes the first1584 compared source bytes as:
6f712f2fa95fc1d9199fda2779130d38e2fa31adde8c139c58679c003463c68c.
Neither hash is an exact result. The separate FormalPayload.json comparison
replays every relocation across all1684 emitted bytes, including all switch
entries. Observed sampler-store order is retained; that single control is
byte-neutral. Receiver allocation, temporary homes and scheduling remain open.

## Reproduction

scripts/repo-python scripts/build.py --unit exact-first-scene-timeline-loader --compare --json

Source:src/ui/SceneTimelineLoader.cpp.
Receipts:build/frontier-scene-timeline-loader-20261029/formal.json,
FormalPayload.json and native-boundary.json. Two new relocation keys bind the
full native handler and double60000 literal. Existing headers, accepted caller
sources and their receipts are unchanged. Default CI validates selection,
tracking and progress; no cold-corpus or runtime-equivalence claim is made.
