# Tenshi Object update boundary and resume point, 2026-10-25

**Complete source-present/nonexact candidate.** Root64CD50 now has a durable
mapping, a complete28-action/default source, an isolated VC8 unit and a public
whole-payload audit. The first complete body was compared before controls.
No exact row or byte credit was added. Original nominal types and original TU
ownership remain unknown; pointer-only views must never be instantiated.

## Target observations

Original Japanese1.06a SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Primary Object vtable6C670C, slot28 cell6C6734 ->64CD50. Same-owner initializer
657150, slot3C cell6C6748, is separate source-present/nonexact context only.

Main `[64CD50,656D79)` is41001 bytes, SHA-256
`d5ed24f23b4e6e385588593fe81b5e9ec83bd77c402fa7a3d387412823e571b2`.
All9800 instructions decode;9797 reached instructions cover40993 bytes. The
three unreachable alignment instructions are64FFDD:8d4900,65269D:8d4900 and
65561E:8bff (eight bytes). All67 exits are RET0, no escaping branches or tails.

Full `[64CD50,657150)` is41984 bytes, SHA-256
`44fedf398c8bfbf882959b4a8d33f15217a8a4ddca02cdbcb695fd330af82fc4`.
It owns28 tables/195 destination DWORDs,199 remap bytes at656DF0 and alignment
656D79:8d4900 /656EB7:90. Seven leading INT3 bytes separate64CD00's provider.
There is **no trailing INT3 gap**: the last table ends at initializer657150.
Default656D6C calls4351C0 once, ignores AL and performs the aligned RET0 exit.

Nondefault actions:800,801,810,811,815,816,820,821,825,848,850,851,852,853,854,
855,856,857,900,920,930,940,960,961,962,980,997,998. Primary dispatch stops at998.

## ABI facts and interpretation limits

thiscall/RET0, `PUSH EBP; MOV EBP,ESP; AND ESP,-8; SUB ESP,2A8`, then saved
EBX/EBP/ESI/EDI. ESI is the primary receiver. Restore with MOV ESP,EBP/POP EBP.
The cause of source-level alignment is not recovered; do not force it with
padding or inert doubles. Write complete natural source before codegen controls.

The427 direct calls use22 entries.22 virtuals use the primary Object at slots
0C/14/1C/20; their providers45C390/45C220/45C180/45C1A0 are independently exact.
The remaining virtual651AD3 calls **manager slot04**, with ECX from
`parent+658`, nine four-byte argument slots and RET36:
`(0, self[16C], 853, x, y, facing, layer, packet, 3)`.
Do not give that call the primary Object slot/purge contract.

Surface helper434EE0 is stdcall, three float arguments, RET12. Sequence helper
4399C0 is thiscall, one unsigned index, pointer/reference result, RET4; both
callers use parent+55C as receiver and read the first WORD. This generated
std::deque island is excluded from authored progress. All other direct call
contracts are retained in the private Java/stack recipes and ordinary accepted
provider sources; no new callee implementation credit is implied.

Backward tracing from actual packet and count argument slots closes97 requests
(85 unparented,11 parented,one direct factory) with53 bases/652 bytes. No pointer
or count definition remains unresolved under the recorded call/clobber/span
contracts; this is not general alias/path-feasibility proof. Most packets have3
words, but p244/654639 has4, p384/65473F has5, and p520/654AF8 has4. p520 is
also used with count3. Preserve per-call counts and independently initialized
words. There are46 qword stack accesses at relative offsets -680/-672/-664;
the dataflow is not permission to add artificial alignment storage.

## Complete source and first comparison

`src/characters/TenshiObjectUpdate.cpp/.hpp` manually reconstruct all28 actions
and the default. Numeric states, typed offsets and declaration-only call views
remain deliberate. The declaration-only providers receive no implementation
credit. `config/functions.csv` retains41001 callable bytes and inclusive end
656D78; the full audit compares41984 bytes through657150 separately.

The first complete private body compiled under the ordinary VC8 SP1 `/O2`
probe profile with GS disabled, without alignment or register shaping. It
naturally emitted `AND ESP,-8` and frame2B0. Full42068 bytes, SHA-256
`278d5bb4a6c1ea1c1361295568e4b8800d600aa286dd136eaf2cde1d4becbc09`,
compared with39549 unmasked differences; first64CD58, frame allocation2B0
versus native2A8. Receipt:
`build/exact-first-tenshi-object-update-20261025/first-complete.json`.
This is a full mismatch, not a similarity/acceptance claim.

That first comparison's per-action call census identified missing **physical**
trigonometric sites in801/820. The source had chosen a layer before one shared
spawn expression; the native branches evaluate sine/cosine separately in each
layer branch. The selected source preserves those branches, native multiplication
association,801's direct cosine doubling,800's intermediate single-precision
random products and its ordered lower-bound comparison. Other actions' call
censuses already agreed. These are scoped source/dataflow corrections, not an
option/spelling grid or a generic codegen recipe.

The initially configured source and an independent fresh build both emit42916
bytes, SHA-256
`2391a745177fb117c358ee4560c00d24412cdf4f8f8f2e6322a321b61a657083`.
Full comparison has40643 unmasked differences, first64CD58; the selected
natural aligned frame is2C0 versus native2A8. It has83 RETs versus67.
All28 per-action direct/indirect call censuses agree, but this does not prove
execution equivalence, packet values, source ownership or exactness.

The native six physical frame-call sites have these owner groups:

- the main common exit for21 actions;
- 810/820/850;
- 816/961;
- 848;
- 960;
- default, which ignores AL.

The initial object has five: its main group also owns816/960;825 merged with
the default. The825 correction below moves825 to the common conditional exit
and leaves default alone.810/820/850,848 and961 remain separate. A call count
alone cannot substitute for the complete physical-owner audit.

## 825 frame-return correction

A subsequent raw-exit review found an actual source error: native65024F sends
825's nonzero substates to64D23A, where4351C0's AL is tested before decrementing
+330. The first candidate incorrectly ignored AL, merging825 with the default.
The source now takes the common conditional exit;825's zero-substate early RET
and the default's ignored return remain distinct.

`scripts/audit-tenshi-object-update-paths.py` executes eight full-root inputs:
825/default799, ready/nonready frame, modes0/1. It runs the real4351C0,
45C1A0/45C220, frame-apply and sprite helpers against a readonly one-block
animation fixture, without injected helper results or transfers. The old object
fails exactly one:825/mode0/ready retains lifetime10 versus native9. The corrected
object passes8/8 with the same actor bytes, helper trace, real RET0 stack cleanup
and x87 control/top. This fixture establishes only the scoped behavior, not
real-game graph reachability or whole-function equivalence.

The correction changes only the four displacement bytes at candidate65035C..F.
Full42916 size, frame2C0,83 RETs and40643 differing bytes stay unchanged; the
canonical SHA becomes
`f010343c86c5fe1d36512882fe89caaa1524da64cc03548e80a265d045ce8b55`.
This is a semantic correction despite an unchanged aggregate mismatch count.
Formal/current and independent fresh comparisons use the complete41984 target.
No exact credit is added.

```bash
scripts/repo-python scripts/audit-tenshi-object-update-paths.py
# Negative control: old complete object fails one native input.
scripts/repo-python scripts/audit-tenshi-object-update-paths.py --object build/exact-first-tenshi-object-update-20261025/selected.obj
```

Receipts: `frame-return-build.log`, `frame-return-full-audit.json`,
`frame-return-cold-build.log`, `frame-return-cold-full-audit.json`,
`frame-return-native-paths.json`, `frame-return-negative-paths.json`.

## Specific semantic limits

**Observed:** 821's native x87 calculation at64FD93..64FDAE adds parent-y and100
before adding the sine product. The worksheet's flattened association is not
source authority. The source retains the observed association. Repeated calls
and receiver/heading capture epochs remain visible.

**Observed ambiguity:** 900's selector-zero branch653294 only assigns the
lifetime60. At65329F..6532A3, burst interval and limit reload a scratch home;
other selectors1/2/3 set interval60, lifetime180/240/300, limit2/4/5 and
burst-count10/12/16. The out-of-range selector branch also lacks initialization.
The candidate retains ordinary uninitialized controls rather than inventing
values. Native executions may observe scratch reuse; deterministic behavior on
those paths and original source intent are **unknown**. No equivalence proof or
exact claim covers them.

`g_update_selector` is deliberately temporary: absolute DWORD6FA894 already has
repository `g_match_identifier` provenance. Its gameplay meaning has not been
recovered here; calling it difficulty would be an inference. Weather reads are
DWORD6FA890 and mode reads are BYTE6FA88F. Each new literal/global binding is
isolated in `_tenshi_object_update_*`; no existing accepted unit, shared header,
compiler flag or relocation binding was changed.

## Reproduction and next bounded question

```bash
scripts/repo-python scripts/build.py --unit exact-first-tenshi-object-update --compare --json
scripts/repo-python scripts/audit-tenshi-object-update.py --target-only
scripts/repo-python scripts/audit-tenshi-object-update.py
```

The first and third commands currently return nonzero for the measured mismatch.
The full audit replays every section relocation, verifies both target hashes,
closes the complete CFG, verifies all28 tables/199 remap bytes, the aligned
default exit, adjacent independent initializer and exact unreachable alignment.
It also records per-action and physical call ownership separately. Synthetic
negative controls exercise metadata truncation, escaping destinations, default
restoration and the distinction between per-action counts and physical sharing.

Receipts are in `build/exact-first-tenshi-object-update-20261025/`:
`formal.log`, `formal-full-audit.json`, `cold-build.log`,
`cold-full-audit.json`, `target-audit.json`, plus the first complete comparison.
The private recipes retain the raw facts, attested Ghidra worksheet, first body
and branch-control source. Reports and private material are not committed.

Next investigate one observed lifetime/transfer difference or one real shared
exit. Do not reduce the frame with padding, inert locals or forced alignment.
Do not rerun spelling/carrier grids after byte-neutral controls; retain receipts
and switch candidates when the scoped question is exhausted. None of these
standalone differences proves LTCG impossibility.
