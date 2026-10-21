# Application scene handoff and retirement

## Observed target

Only original Japanese TH10.5 v1.06a was used, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Raw complete CFGs close the following return-terminated callables without gaps
or outgoing branch exits:

| Entry | Instructions | Bytes | Body SHA-256 |
| --- | ---: | ---: | --- |
| `Application_commit_pending_scene @ 408080` | 40 | 148 | `f8f0ee2b0f90eff8040c8263a995b83af56da12463581a95dea52bdd3a0dce5c` |
| `Application_scene_disposal_thread_entry @ 408870` | 90 | 281 | `a104fd62f975c4a5b345d769dd7bc6bc9c2786bbd8c387e2ee405210550ac54d` |

Source-present control worker `4081E0` calls handoff at `4083C8`, with no register
receiver or explicit arguments. Bootstrap `407DA0` supplies disposal callback
`408870` to CreateThread at `407F36`, storing the handle/id at application+6C.
Exact shutdown signals event+90 before joining that thread. Those game-owned
scene/thread lifetimes establish authored ownership independently of comparison.

## Complete behavior and native container

Handoff returns immediately when pending scene+80 is null. Otherwise it enters
native scene critical section+98, saves previous scene+7C, publishes pending as
previous, clears pending and leaves the lock. An old scene receives
on_scene_exit(requested+B0), is appended to retired list+84 and causes event+90
to be signaled. The new previous scene, if present, receives
on_scene_enter(active+B4); active then becomes requested. Existing IScene
slots+14/+10 describe those ordinary thiscall hooks.

The disposal callback is ordinary Win32 stdcall with one unused pointer and
zero return/RET4. Failed CoInitialize skips all work. Success creates an
unnamed automatic-reset event at+90, then waits indefinitely while running+4C.
Each wake drains retired scenes: if front is nonnull, virtual-delete it and
write front=null, then pop_front. The source intentionally repeats native
front() accesses; allocator/virtual calls and checked-iterator failures can
require the target's reloads. The callback checks running after draining,
calls CoUninitialize, then closes the event. It adds no null-event guard, lock,
extra final drain or event-pointer clearing.

The target's list fields are proxy+84, head+88 and size+8C, followed by event+90.
Real VC8 checked `std::list<IScene*>` has the observed12-byte header. Its native
front/pop_front operations regenerate the safe-iterator checks, scalar-deleting
virtual call, link updates and node deletion. The same source models both
producer and consumer in `src/platform/ApplicationSceneLifecycle.cpp`, with
offset/size assertions and no shared-header change. The full application class
size and original source names remain unknown.

Private insertion helper `4089C0` closes53 bytes / 26 instructions. The caller
supplies EAX=&old_scene and a stack container pointer; the helper reads that
value, calls independently compiler-classified51-byte node allocator `4129E0`,
invokes `40C6D0`, links the node and returns RET4. The pinned list header's
push_back/_Insert/_Incsize sequence corroborates those operations. Raw154-byte
`40C6D0` checks `3fffffff - size < 1`, builds the list length error on failure,
otherwise increments size by1 and returns without a count argument. These
private entry shapes differ from ordinary standalone template methods.
Both helper origin rows remain in review; semantic corroboration alone is not
new exclusion or authored credit.

## Canonical result and compiler-phase evidence

The initial ordinary COFF producer/consumer candidates are186/148 and278/281.
The consumer already has148 consecutive central bytes identical to the target,
but its prologue/epilogue and loop alignment differ. A complete static insertion
wrapper is naturally inlined and leaves the producer unchanged; no noinline
attribute, fake external private ABI or forced alignment is retained.

A genuine `/GL` plus resolved `/LTCG` build naturally produces the consumer's
eight-byte-aligned frame, saved frame-pointer/EBP=1 lifetime and the complete
**281/281 canonical exact** body. Target and canonical linked-body SHA-256 are
identical to the table above. Five named CRT REL32 fields (four invalid-parameter
calls and operator delete) replay; all absolute data/IAT references are checked.
The named linked extent and complete CFG independently agree on281 bytes.
The source producer remains **189/148 nonexact**, including a different frame
and inlined insertion ownership. Original producer TU/inline context remains open.

### Bounded visibility controls

Fresh resolved links of the same source, hash
`5cc6d01abe5462ae539a2f0feaa2754d21dc137f4ebe46e6e14a647d5394ab67`,
tested three independent compiler properties after the accepted checkpoint.
These are diagnostic main callable extents, not canonical acceptance results
or claims about ownership of remote EH chunks:

| Compiler control | Scene commit | Retirement callback | Native `_Incsize` |
| --- | ---: | ---: | ---: |
| Accepted `/O2 /GL /GS-` baseline | 189 | 281 | 133 |
| Baseline plus `/Os` | 167 | 255 | 136 |
| Baseline plus `/Ob1` | 189 | 281 | 133 |
| Baseline with `/GS` | 189 | 281 | 153 |
| Original target | 148 | 281 | 154 |

Every diagnostic used the same actual VC8 import libraries, original data/IAT
bindings and resolved link without `/FORCE`. Input hashes, commands, maps,
logs and disassembly were recorded below
`build/application-scene-visibility-20261016/`; private drivers are below
`.analysis/application-scene-visibility-20261016/`. The `/Os` output is densely
packed and does not outline the observed insertion helper. `/Ob1` leaves the
two authored extents unchanged. `/GS` restores a cookie-bearing `_Incsize`,
but its frame, saved ESI and string-construction call contract still differ.
A near-sized helper is not a match. None of these controls resolves the
producer's private insertion boundary; no source/profile change was retained.

Raw E8 discovery followed by instruction/CFG verification identifies shared
`40C6D0` calls from `4036E0` (three), `403B90`, `403CE0` (two), `4089C0`,
`411790`, `414CB0` and `419350`. The latter two are independently source-present
device-reset and audio-event list producers, using different pointer element
types. This supports shared pointer-list growth code, without proving whether
COMDAT folding, template ownership or another compiler phase produced it.
At the time of this audit, the additional raw E8 candidate at `40B9DC` had not
been reached by the bounded `40B000` inspection. The subsequent
[complete CDesignBase loader audit](DESIGN_BASE_NATIVE_VECTOR_2026_10_21.md)
resolves the switch and reaches all860 instructions, including this call to
`40C6D0`. Count that caller edge as verified; generic-helper source ownership
remains open. The earlier receipt is
`build/application-scene-visibility-incsize-callers.json`.

The insertion helper `4089C0` still has only the independently verified scene
handoff call at `4080DF`. The target's reference-in-EAX/list-on-stack boundary
is not a license to declare an external standard-ABI substitute. Retain the
native list source and recover original visibility/call context before further
source shaping. Both helpers remain in origin review, with no new credit.

The new [linked comparison contract](LINKED_PE_MATCHING.md) pins the compiler,
linker, header trees and real VC8 import libraries, rejects unresolved links,
and never executes the comparison image. Early `/FORCE` inspection artifacts
are diagnostic only and are not the accepted evidence. Absolute code-symbol
bindings are rejected; no fake callee bodies are used. Fresh builds with the
CI and development decoders both reproduce the same full consumer hash.

```bash
python3 scripts/audit-candidate-boundaries.py 0x00408080 0x00408870 0x004089C0 --json
python3 scripts/build.py --unit cross-v106a-application-scene-lifecycle --json
python3 scripts/compare-linked-unit.py cross-v106a-application-scene-lifecycle --address 0x00408870 --json
```

Reports are `build/application-scene-lifecycle-boundaries.json`,
`build/application-scene-lifecycle-linked-formal.json` and the accepted selected
report `build/application-scene-disposal-formal.json`. Full-unit comparison
still reports the producer mismatch. Only the consumer enters matches.csv;
the producer has an independent hash/edge/data-backed authored-origin rule.
Unrelated origin fingerprints are preserved after scope/overlap checks.

Direct Ghidra sessions independently attest executable/program SHA, image/entry,
x86 Windows identity and every mapped .text byte before saving and freshly
reading back both names, complete extents, return/parameter widths, cdecl0 versus
stdcall4 and body hashes. Scripts stay under
`.analysis/application-scene-lifecycle-20261016/ghidra-scripts/`; logs stay under
`build/application-scene-lifecycle-ghidra-*.log`. Processes use768MiB and two
active processors; no failed IDA session or factory adapter supplies analysis.
