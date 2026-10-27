# Weather emission policy, 0x00660B30

Complete source accepts **12198/12198 callable bytes** and **12348/12348 full
payload bytes**. All756 COFF relocations replay:208 REL32 and548 DIR32.
Source src/battle/WeatherEmission.cpp, unit exact-first-weather-emission.
The150-byte alignment/table tail is compared but not credited as authored code.

## Target, boundary and ABI observations

Original Japanese1.06a SHA256:
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.
All3355 decoded instructions are reachable. Twenty-one RET0 exits and two
fully bounded indirect switches close the complete body; no remote chunks.
The callable ends exclusively663AD6, followed by two NOPs,19-entry category
table663AD8/76 bytes and18-entry event table663B24/72 bytes. Payload ends663B6C;
four INT3 bytes isolate the independent WeatherEffectObject update663B70.

Code SHA256:
502901a370f968b6f8a2efa3e072151c2eeb12a1cf1dd717257d262cf7de82c7.
Full payload SHA256:
598abdd1b31a7e9075e52ef26dc6f075dbe37bcebfea0e97452b94bbcd0f8dd4.
Physical calls:98 effect emissions665470,102 selector-RNG4067D0,8 indexed
events43B1A0. No helper inherits an origin or exact claim.

The raw caller466FBE loads event-state pointer6FBCAC, pushes its event id and
calls at466FC6; it then performs unrelated floating-point work and drops the
argument at466FD7. No return-value use is observed. The complete source is
void cdecl with one int argument, naturally reproducing all incidental EAX
values without fake returns. This is an emission controller, not a virtual
initializer despite its proximity to other effect-family functions.

The45-byte helper665470 takes five cdecl arguments, loads6FBCAC and calls the
independently accepted EventEffectState::emit_effect4695B0. Its ordinary int
return declaration reflects the forwarded return; this root ignores it.
Helper665470 and caller466F40 remain independently unselected.

Factory-native IDA hash/metadata, entry68B9D2, mapped entry bytes and inventory
were freshly attested. Raw PE supplied ABI/boundary/constant facts. Supported
name/prototype metadata was updated and read back; target bytes were not edited.
Direct IDA launcher still lacks its mcp/uv runtime, not a target mismatch.

## Complete authored policy

The controller increments6FD390 before checking the incoming event. A changed
event publishes6E90EC and resets the counter to0. Modulo periods use unsigned
interpretation of that counter, preserving high-bit behavior. Existing global
symbols retain their established types/identities; no shared declarations change.

A signed mode-byte switch assigns short categories0/1/2. Explicit zero-category
arms remain independent assignments; default leaves the initialized zero.
The event switch contains all18 IDs0..17, with event16 physically first and17
between9 and10 in source, matching the target's actual dispatch owner ordering.

The repeated category2 branch is intentionally not factored into a shared
helper or hoisted outside the event switch. It publishes -0.5/-0.5/negative-zero
background targets, emits151 at counter0, then152/153/154/155 at unsigned
period180 residues0/45/90/135 with independent RNG640+320 X coordinates.
Event14 also permits category0 for this path;15/16 never enter it.

Other policies preserve their distinctions:
- Event0 always clears background targets outside category2, emits5 at0, and
  adds1..4 at period180 quarters only for category0.
-1 and9 do nothing for category1; category0 dispatches100 at0 and emits11 at
  period90, or91 at period3 with random facing and height.
-2 uses -0.03 targets only for category0;3/5 clear targets outside category2.
-4 uses -0.1, dispatch105 and alternates41/42 at period4 residues0/2.
-6 permits category0 or mode16, uses +0.05, initial61, then62/63 at period30
  residues0/15 with independent X/Y draws.
-7 uses -0.1, initial151, then71 at period6 with random facing and72 at period90.
-8 category0 dispatches101 and emits81/86 at0, then82..85 at period240 quarters;
  category1 leaves prior state unchanged.
-17 category0 uses0/0/-0.15, dispatch104 plus101 at0; category1 clears all targets.
-10/13 category0 dispatch104, use -0.1/-0.2 and emit111/141 at period20.
  RNG640+556 is integer addition before unsigned-to-float conversion.
-11 category0 dispatch104 and emits121 at period15. Its RNG640-180 remains
  unsigned integer subtraction before float conversion, including wraparound.
-12 uses -0.05, initial131 and period90 effect132 with two separate random
  branches controlling signed Y/layer.15/16 clear all three background targets.
Unhandled event IDs only retain the initial counter/state update.

Repeated global-pointer loads are retained naturally through a pointer-only
offset access view. Negative zero is a real native literal, not replacement0.
Unsigned RNG results convert to float before subsequent arithmetic; integer
offset exceptions above are preserved.

## First complete build and supported corrections

First complete source emits12188 bytes. Native call ownership exposes the
important source-context errors before any register tuning:
1. Temporary Y values evaluate before constant arguments, unlike the native
   nested-call argument preparation. Expressing real Y draws inside the effect
   call restores the VC8 right-to-left call sequence, yielding12140 bytes.
2. Random-facing/layer cases7/9/12 physically duplicate RNG calls on their two
   paths. Separate ordinary source if/else emission calls restore those physical
   owners; a synthesized ternary plus shared random body was not the native
   context. The full candidate becomes12348 bytes.
3. Event16 owns the initial zero-target block before event0. Moving that actual
   case to the beginning of the source switch yields zero differences across
   all12348 bytes, without altering semantics or compiler settings.

No assembly, byte arrays, inert locals, fake values, padding, register forcing,
masked comparison or copied decompiler pseudo-return is used. Original source
spelling and nominal function name remain inferred rather than claimed recovered.

Ten append-only floating literal bindings are pinned by absolute target operands
and actual emitted COFF bytes: negative0,1980f,1560f,-0.03f,1560double,860f,
2400f,-0.05f,-240f,-0.2f. No existing binding is modified.

## Reproduce and verification scope

- scripts/repo-python scripts/build.py --unit exact-first-weather-emission --compare --json
- scripts/repo-python scripts/audit-weather-emission.py
- scripts/repo-python scripts/validate-tracking.py --require-target
- scripts/repo-python scripts/check-match-literals.py --require-target
- scripts/repo-python scripts/ci.py

Formal focused comparison and full-tail audit both pass. Complete-source
controls, target assembly/CFG/call counts and receipts are retained in
build/frontier-660b30-20261027/ and its corresponding private analysis directory.
The source generator represents the first trial only, not the selected source.

Only this new unit is built; no shared header, compiler flags or prior mapping
changed. Previous exact receipts are retained and totals are incremental, not a
fresh full-corpus replay. Final local CI is pending at writing; its terminal
exit/log is the commit gate. Actual game/RNG/emission execution is not claimed.
