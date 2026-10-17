# Reimu actions0..10: staged source and real helper execution

This continues `Reimu_dispatch_action_state_vslot28 @478FA0` against Japanese
TH1051.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The complete81550-byte root/eleven-switch boundary remains as documented in
[the entry record](REIMU_ACTION_ENTRY_2026_10_17.md). Root status remains
unclassified/declaration-only; no authored exact bytes or root implementation
credit is added by these staging helpers.

## Source recovered from the target

The physical low0..10 owners occupy479205..479790 (1419 bytes), with shared
returns/tails outside individual owners. Every instruction, comparison and
outgoing edge in this cohort was read from the hash-attested PE. The source
is `ReimuActionStateLow.cpp`; its bool reports whether it handled a known
low action. `ReimuActionStateStaging.hpp` shares the typed prefix with the
existing entry phase and asserts all new field offsets. These are semantic
staging boundaries, not proposed original compiler functions.

| Actions | Observed behavior |
| --- | --- |
|0..3|Resolve surface state. With BYTE+47E nonzero, subtract/add double0.5 from positive/negative X velocity, round to float and clear all four motion fields only after strictly crossing zero. Action0 also clears+47E when entering with zero velocity; action2 does not. Actions1/3 switch to2/0 only after advancement reports completion and WORD+140 is zero.|
|4/5|Resolve surface state, set absolute X velocity+4.5f/-4.5f, then advance. Facing does not select the sign.|
|6..8|Resolve surface state only at sequence0; clear motion at sequence0 if+47E is zero. Only signed sequence>0 subtracts acceleration from Y velocity and checks crossing. A crossing calls action10, obtains the actual surface height, sets Y and clears motion. Otherwise advance, then re-read sequence/counters: at sequence1 and zero DWORD+144/WORD+142/WORD+140, initialize VX0/+4/-4, VY15, AY0.55f and clear+47E.|
|9|Install0.6f gravity only when AY compares equal to zero, then update VY. A crossing uses the same action10/height/motion-clear tail; other paths advance. NaN does not count as zero.|
|10|Resolve surface state, clear motion and advance. Completion selects action0 for DWORD+6B8 zero, otherwise action2.|

The selected action is captured before any helper. A landing helper can change
the live action to9 before the original case finishes; re-reading that field
to choose a later case-specific constant is incorrect. Separate post-helper
sequence/counter reads are preserved where the target actually reloads them.

No existing accepted header, compiler profile or relocation ledger changed.
The new header is private to the two Reimu staging source files. Extracting
the entry declaration/layout preserves its **530-byte raw text and every
relocation identity** (text SHA256
`663a5e72281b78333cb6eb56e71f281db9d8426581158fca878a519b16366f76`).
A fresh **0/10584** entry replay retains the earlier proof scope.

## Native differential proof

```bash
scripts/compile-unit.sh src/characters/ReimuActionStateLow.cpp build/reimu-low-actions/ReimuActionStateLow.obj
python3 scripts/audit-reimu-low-actions.py build/reimu-low-actions/ReimuActionStateLow.obj
```

Fresh VC8 SP1 `/O2 /GS- /GR /EHsc /MT`, default FP, gives low-source CRLF
SHA256 `a4b69f302fbc5573a1547df58e72afb02fba0b40a7592546ca7a4a09700208cf`
and object SHA256
`839a70c07d516798449daeea64642b6b9f73606b8c33fc91fd75e3e8dcf29c7c`.
The shared-header SHA256 is
`9a29d5c115342b6469800fc3a669eea559946eb60b461623e059d90e0f9d6c9d`.
The separate manual build receipt supplies compiler/source identities; the
native oracle itself does not attest a build or award matching credit.

**0/10700 differences** cover:

| Cohort | Controls |
| --- | ---: |
|0..3 friction, zero flags and landing heights|3072|
|4/5 fixed velocities, both facings and animation contexts|384|
|6..9 signed sequence, velocity/gravity pairs and heights|6144|
|actual unexpired/frame/block/terminal transitions|896|
|post-advance WORD/DWORD counter conditions|192|
|entry-action preservation across real callbacks|12|

Velocity inputs preserve raw bits, including signed zeros, subnormals,
infinities, signaling/quiet NaNs, opposite-sign NaN pairs and adjacent values
around0.5. The matrix uses masked PC53/PC64 and includes signed sequence-1,
both movement-flag states, height0/5/6/100 and full DWORD+6B8 values0/1/65536/-1.
Target fixture checks require the advertised frame/block transitions and
completion action arguments. All three launch sites are actually entered
20 times each. The capture cases require target action history9→2 after
entering case1, instead of assuming the callback leaves the action unchanged.
Input SHA256 is
`7a14e87394962c440e01e925204886a3ba3acef1b522cec7e8fd70fd3b15415f`.

Both programs reach genuine native RET with stack delta4, preserved
EBX/ESI/EDI/EBP, empty x87 stack and unchanged control word. The comparison
includes all4096 bytes of the supplied actor region, ordered helper calls,
receivers, callback arguments and physical x87 conversion inputs. It visits
439 original root instructions and216 staging instructions. This is sampled
execution, not complete branch, numerical, exception or gameplay coverage.

Actual action setting45BFE0, base action435200, sequence reset45C460,
Reimu finalization491C40 and CharacterEx finalization477830 execute unchanged.
Each setter/finalizer is entered2672 times in each program. Real next-frame
and next-block helpers run828/556 times. Event-member4359F0, dispatch43B1A0
and sound-handle401D50 each execute248 times, taking the original zero-handle
path. No helper return is replaced or skipped by a result hook.

The supplied read-only graph contains eleven action keys0..10 in a valid
balanced red-black tree, four linked sequence blocks per action, and one/two
frames per block. Texture handles are zero and render mode-1 follows the
native non-transform path. The original flat surface and zero event handles
are verified before execution. Source-side entry words are preset to their
verified entry-phase outputs; entry-counter/gate paths are tested separately.
The4096-byte actor buffer is fixture storage, not a recovered class-size claim.
Writes outside actor/stack or execution outside the admitted original bodies
fail. Textured/audio backends and other world contexts remain outside scope.

An early private fixture overlapped map nodes with the texture vector and
adjacent two-frame arrays. Those input-model errors were corrected before the
retained matrix. The new pure `reimu_animation_fixture.py` and three unit tests
check tree order/parents/red-black heights, disjoint storage and terminal/next
links so the mistake does not silently recur.

## Calibrations, Ghidra and continuation

Three separate wrong-source controls are compiled and rejected by the88-case
smoke matrix:

- Clearing zero-velocity+47E for action2 as well as0 fails1/88: it incorrectly
  clears the flag and the other motion fields.
- Re-reading live action after callbacks to choose case1's completion fails
  1/88: target9→2 becomes9→0, changing action and animation resource pointers.
- Using sequence!=0 instead of signed sequence>0 fails3/88: sequence-1 in
  actions6/7/8 incorrectly updates VY and performs the crossing check.

One direct read-only Ghidra clone at768MiB/twoCPUs attests executable/import
identity, entry, all mapped `.text` and full root hash, then decodes the
bounded entry/low cohort. Readback confirms the zero-flag distinction, signed
sequence guard, post-advance counters, jump constants, gravity default,
landing tail and DWORD+6B8. All nine primary database files remain
hash-identical; the clone was removed. No IDA semantics, factory adapter or
target-byte patches were used.

Small reports/recipes live in `build/reimu-low-actions/` and
`.analysis/reimu-low-actions-20261017/`. Next recover the low71..78 family
and its shared tails from the same81KB root. Complete remaining action source
and a strict whole-root canonical comparison are still required.
