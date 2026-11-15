# WeatherEffectObject update 663B70: complete nonexact source

The entire 4381-byte target now has a complete compiling source hypothesis,
src/battle/WeatherEffectUpdate.cpp, configured as exact-first-weather-effect-update.
It is **not exact**: source 4353 callable/full4730 versus native 4381/full4758.
Both focused canonical comparison and the full-tail audit report mismatch at+9.
No matches.csv row or exact bytes are added. Weather entry 664E10 remains exact.

## Observed identity, boundary and authorship

Canonical original Japanese 1.06a SHA256:
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.
RTTI WeatherEffectObject primary vtable 6C1444 slot 28 cell 6C146C points here.
COL 6D7DBC, descriptor 6E67EC and four target-pinned calls independently establish
the authored virtual body. Merely selecting source is not authorship evidence.

All 1070 instructions are reachable;12 RET 0 exits close the 4381-byte body.
First 19-entry table 664C90 maps the signed transition byte into categories.
Second 32-entry table 664CDC and 170-byte index map 664D5C cover 32 handled action
IDs. Callable end 664C8D is followed by three NOPs. Metadata ends 664E06; ten
INT3 bytes isolate the accepted initializer 664E10. No remote chunk or unresolved
indirect destination is omitted.

Code SHA256:
c8c8469690b7bc72a481c4d36d5ec48def02e7b2380e987091ab3aca6ae1f107.
Full target SHA256:
1218b50586e3ea8397aa0f672cc72a6c065ef382dd04ec2413346ee2cdc33507.
Selected complete candidate SHA256:
e18a4adcf06170ddea9c6a22688d585485a45861250acc2f81b6b889da8b028e.

The selected source retains all 37 physical calls: sine 406480 fifteen,
animation 4351C0 nine, cosine 4064B0 one, RNG 4067D0 two, UV 435520 three,
angle sine 406360 three, angle cosine 4063D0 three, and motion 435160 one.
All 174 candidate relocations resolve:37 REL32 plus 137 DIR32. A matching call
census supports review but is not exactness evidence.

Factory-native IDA target metadata, entry 68B9D2, mapped entry bytes and function
inventory were independently reattested. Raw PE is authoritative for operands
and boundaries; decompiler text is a hypothesis. Updated name/void-thiscall
prototype was read back; no target bytes changed. Direct launcher still lacks
its mcp/uv runtime. Receiver views are pointer-only, not complete owner layouts.

## Complete policy retained

Numeric actions remain explicit, with independent repeated arms.
Mode 4/6/14/16 maps to category 1, mode 5 to 2, explicit remaining recognized modes
to 0, and unhandled modes preserve initial 0. The global is interpreted signed
for the native MOVSX and unsigned range guard; the derived category is short.

- Actions 1..5 and 82..86 retain different alpha publication, sine modulation,
  X movement and animation timing. Both animation completion and age 180 may
  decrement 158 in one update; they are not made mutually exclusive.
-11 applies the native -100 sine/cosine drift and separate age/height fading.
  The fade condition is age>=180 OR y<480, preserving unordered behavior rather
  than replacing it with the negation of a decompiler >= test.
-41/42 retain distinct collision thresholds, unsigned RNG 100<=30 guards,
  bounce coefficients, sequence/reset fields 140/142, and gravity/fading.
  Bounce returns immediately, before position and animation updates.
-61/101/131 share UV offset patterns but differ in fade rate, offset direction
  and whether animation advancement occurs. No common helper is invented.
-62/63 and 132 retain different alpha caps and X drift;133 is not a handled ID.
-71/72 retain their own sine amplitude, phase 4*age, signed facing 104 and height
  cutoff.72 additionally advances its angle.
-81/151 retain their own retirement conditions;151 checks captured 174 against
  current event state. Mode/state tests remain short-circuited.
-91/111/141 keep separate trigonometric calls, speeds and facing behavior,
  initial alpha ramp, and independent age/height fade after animation.
-121 calls motion with ECX=this+4 (raw LEA 6647EF), then checks X>1880 and updates
  X/Y without advancing animation. UV 435520 calls instead use the whole receiver.
-152..155 retain independent event-state/mode tests, angle/scale updates and
  alpha publication.155 publishes computed alpha after angle and scale.
-170 fades alpha by 3 and advances animation; default does nothing.

No runtime gameplay, random, rendering or hardware execution is claimed.
Existing global identities 6FA88F and 6E90EC are reused; no new literal binding,
shared header, ABI, compiler flag or accepted unit is changed.

## Bounded complete-source trials and remaining unknowns

First full candidate 4718 used a compressed category table. Reordering its source
cases alone did not resolve it. Giving the independently specified zero-category
arms their own ordinary assignments recovers the native direct 19-entry table.
Splitting the category 1 arms is byte-neutral; that lane is closed.

An initial separate-if translation of the retirement conditions unnecessarily
continued later tests after retirement. A ternary control materialized booleans.
Normal short-circuited if/else-if tests restore the actual branching policy.
Native low-alpha-first ramp order and real alpha temporaries for actions 4/85/155
recover their publication order and all nine physical animation calls.

The selected source still differs in zero-constant promotion (native EBX versus
source immediate/test), corresponding frame offsets and shared branch layout.
Its 28-byte body shortfall remains a genuine failure. Do not force registers,
add inert values, mask differences or call this an LTCG impossibility. Further
work needs independent compiler/source-context evidence, not a spelling grid.

The original write_source.py generates the first candidate only; do not use it to
overwrite the selected later source.

## Reproduce

- scripts/repo-python scripts/build.py --unit exact-first-weather-effect-update --compare --json
- scripts/repo-python scripts/validate-tracking.py --require-target
- scripts/repo-python scripts/ci.py

The first two commands are expected to exit 1 with mismatch, not blocked.
Only this new unit is rebuilt; prior accepted receipts are retained. Totals
remain incremental. Final local CI is pending at writing; its terminal exit/log
is the commit gate, with no post-gate source/doc edits.

## Shared typed state, 2026-11-10

The complete update now uses the shared weather-specific observed state rather
than raw member-offset macros. All 463 accesses preserve their field widths and
branch policy. Fresh full-object contents/relocations are unchanged, including
the 4730-byte canonical payload and +9 nonexact residual. See the typed-state
section of `WEATHER_EFFECT_ENTRY_2026_10_27.md` for both-unit evidence and scope.
