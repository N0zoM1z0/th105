# Iku steering face-call contexts, 2026-10-17

Target is original Japanese1.06a, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Complete root620920..62EFBE remains59038 bytes, SHA-256
`abc831c6ccd95986bed811694f532ad8c8b92cb49702a7f6ce4de100b8a73dea`.
The mandatory IDA preflight rejected its wrong image. Observations use the
attested PE and direct read-only Ghidra. Selected C++ remains unchanged;
this checkpoint adds evidence and native-observer coverage, not exact credit.

## The extra physical call

Action730 has four target calls to478E60:62DC18 after the mode-dependent
clamps,62DD68 after fixed clamps,62DDD1 after successful advancement/action700,
and62E334 at sequence7 entry. The ordinary candidate has five. The extra site
is inside the first clamp continuation, not another recovered source statement.

Target62DBDE compares the lower bound in ST0 with Y velocity. The taken-store
path executes FSTP DWORD[ESI+F8] at62DBEB and jumps to62DC16; the other path
executes FSTP ST0 at62DC14 and falls through. Both then set ECX and call62DC18.
Candidate instead duplicates the ECX/cleanup/CALL tail:62D953 after the Y
store,62D97F after discarding ST0. Fixed clamps call62DAD1; the other two
ordinary730 sites are62DB4A and62E0BE.

The185-byte target interval62DB64..62DC1D has SHA-256
`750b4c87eda9cdf65581666da076ebbc05f01ce93e0949b7ba9642ddbb90c41b`.
One read-only Ghidra clone,768MiB/two CPUs, independently attests file/imported
identity, entry, full mapped.text, language/compiler/root and this interval.
It reads back conditional stores/discards, the common call and all four
target sites. Nine primary project files remain hash-identical; clone removed.

## Actual entry contexts

`UpperProbe` now observes the actual478E60 entry for regular steering cases.
It validates the saved return address against a real E8 CALL, normalizes the
candidate caller to the root base and records raw X/Y velocity, direction,
sequence, x87 control word, TOP and six sticky exception bits. Caller addresses
are diagnostic metadata; the recorded states and call multiplicity are
compared independently of those addresses. No executable/vtable byte, return
value or dependency is replaced. Invalid native reads fail the observer.

Fresh selected-source `--steering-clamps` passes **0/4960 mismatches**, with
zero entry-context differences.3840 cases reach exactly one genuine face call;
1120 exceptional-geometry cases stop at actual atan2 entry before any face call.

| Continuation | Target entries | Candidate entries |
| --- | --- | --- |
| Mode-dependent Y lower store |62DC18, shared total1920 |62D953:96 |
| Mode-dependent discard |same62DC18 |62D97F:1824 |
| Fixed clamps |62DD68:1920 |62DAD1:1920 |

Thus both candidate exits are exercised with matching pre-call state, including
TOP0 and sticky exceptions. This establishes bounded runtime agreement across
the physical split; it does not establish all730 paths or original optimizer
behavior. The two post-advance/sequence-entry face sites remain outside this
fixture. Actual outcomes per side:3312 RETs,528 sequence-backend entries,
1120 atan2 entries;252 target-root instructions visited. Unmasked exception
delivery, final backend execution and whole-game behavior remain unproved.

`--control steering-face-count` deliberately calls the real face helper twice
after nonfixed steering. All1920 selected sequence7/8 cases differ, including
1920 entry-context/multiplicity differences. Target makes1920 calls; source
makes3840. Both recorded examples finish with identical actor memory despite
their extra call, illustrating why call/state history is checked. This is an
unselected negative control, intentionally exit1, not a matching technique.

| Profile | Input SHA-256 | Target-output SHA-256 |
| --- | --- | --- |
| Positive |55ce43b0a4164e125b5e8fd41b27605b6a3d53f27ff9aba55882362120158653 |ccd9c0d9cb9c5d4f3d0969929e53077f1df404a857431fddfd184c1b50f85290 |
| Duplicate-call control |87d424c8af254b9319eef125dd1002c1a6ca08ee99f1401ad91c357ace00554e |c0ac22613ef80a5230570d4dfcd127d81ad783da37fed8b9f911295d4c1eb07d |

## Unselected source and link controls

- Making only clamp_y's bound parameters double is whole-section neutral.
- Commuting its lower comparison introduces double literal
  `__real@c018000000000000`, unlike the target float-bound loads. The canonical
  comparison rejects its unmapped DIR32; no completed canonical result is
  claimed and no mapping is invented to admit it.
- Sharing only the final Y lower-bound carrier, while leaving branch-local
  X clamps and Y upper tests, grows the section16 bytes to59474/14996 reachable
  instructions. SHA-256884bf0300032bd2c05130ccd884325696342d1be752936838ef02961669b957a;
  it retains five730 face sites and remains nonexact+64. It is unselected.
- A private header replaces the existing unknown prefix bytes with five
  observed float fields at EC/F0/F4/F8/100, keeps FC unknown, and preserves
  byte104. Direct member access replaces608 coordinate/velocity expressions.
  Offset and bounded-view-size0x174 assertions pass. The entire canonical
  section remains identical. This does not establish original class spelling,
  full object size or declarations; no shared header change is selected.
  An earlier offset-switch accessor variant was stopped before producing COFF
  when superseded by direct members; it has no comparison result.

A fresh genuine `/GL` root / `/LTCG` link retains real game providers and
pinned SDK/CRT.41/44 compilation steps are reused; root/provider/float-adapter
objects rebuild.47/52 selected dependency addresses compare exact; five
registered nonexact dependencies and the provisional nonexact abs adapter
remain explicit. This is not an accepted-unit replay or an executed image.

The59472-byte normalized envelope includes14 trailing INT3 alignment bytes.
Of59458 bytes shared with the ordinary object, only22 differ, in ranges
53141..53155 and53156..53164: mode MOV/CMP schedule earlier around the Y
FADD/FSTP. All five face CALLs lie outside these ranges and remain unchanged.
Linked shared-section SHA-256:
`b2257a0f6ce9c42bfdd1e1ae6052e5c8a8ac4747ced7a4ad776ded6e96f49cb5`;
complete envelope SHA-256:
`f07cb697914f56236d677a05d965df74556a1b2c0089df2e3538db3563273b85`.
All switches and898 HIGHLOW/862 direct CALL relocations replay. Strict59038
comparison still first fails+64/620984. This tested context proves no general
LTCG/standalone barrier or original TU ownership.

## State and reproduction

Selected CRLF source SHA-256 remains
`1bf7fcd437528a871e5297100389420fc000e791b6c0bdd54bd281303178a503`.
Native/configured whole59458-byte sections agree at SHA-256
`347e4d6cf2820eef3559e53f6dd2bab14cffe2065343113d4863875ffd00917b`.
All canonical bytes and existing8/109 owner diagnostics remain unchanged;
no exact/partial authored credit, public type/layout/profile/relocation change
or aggregate cold replay. Reports live under `build/iku-facing-tail/`, private
recipes under `.analysis/iku-facing-tail-20261017/`. Delete obsolete objects,
private source controls, linked images/clones and caches; retain current proof
objects and the small genuine-provider cache.

```bash
python3 scripts/build.py --unit gpt-web-iku-action-state --compare --json
python3 scripts/probe-iku-upper-actions.py --steering-clamps --output build/iku-facing-tail/IkuFacingPathsNative.obj
python3 scripts/probe-iku-upper-actions.py --steering-clamps --control steering-face-count --output build/iku-facing-tail/DoubleFacingNative.obj
python3 scripts/probe-iku-action-ltcg.py --reuse --ordinary-object build/match-units/GptWeb_IkuActionState.obj
python3 scripts/audit-iku-full-root.py --object build/match-units/GptWeb_IkuActionState.obj --native-object build/iku-facing-tail/IkuFacingPathsNative.obj
```

Continue with joint compiler/source sharing and scalar lifetimes. The initial
constant1 hoist, effect outgoing join,310/409 sharing, original C++/TU/
inheritance/optimizer and full post-backend equivalence remain unresolved.
