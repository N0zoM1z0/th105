# WeatherEffectObject action entry, 0x00664E10

The first complete source accepts **1383/1383 callable bytes** and the entire
**1630/1630-byte COFF payload** under pinned VC8 SP1 O2/GS-. The additional247
bytes comprise one alignment NOP,76 destination-table bytes and170 index-map
bytes; these are compared but receive no authored-code credit.

## Observed target and boundary

Original Japanese1.06a SHA256:
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.
All356 decoded instructions are reachable through the native19-entry table.
There are16 RET0 exits and23 direct calls: RNG4067D0 nineteen times, cosine
4063D0 twice and sine406360 twice. All107 COFF relocations replay strictly:
23 REL32 and84 DIR32. No remote code chunk or unchecked indirect destination.

Callable range664E10..665377 exclusive, then NOP665377, table665378..6653C4,
index map6653C4..66546E. Two INT3 bytes isolate the next callable665470.
Callable SHA256:
7515fe98526a2d5822cfd9f19b4bb06db3eb11d8a9be0dd7f9b13b541be39dc3.
Full payload SHA256:
23d1f5b93cf37c0634ce56166095dc9c734b1d580baeb33ef68606fa33db04a5.

The primary vtable6C1444 slot3C cell6C1480 points here; its COL6D7DBC has
zero object offset and type descriptor6E67EC naming .?AVWeatherEffectObject@@.
ECX is the receiver, no explicit stack arguments, void RET0. The source view
is pointer-only and never instantiated or embedded as a complete owner.
The neighboring update663B70 has independent ownership and no inherited credit.

Factory-native IDA metadata/hash, entry68B9D2, inventory401000/52 and mapped
entry bytes e8ca9f0000e916feffff were reattested against the local PE.
Direct IDA launcher still lacks mcp/uv; no target mismatch was observed.
The supported name and void prototype were written and read back. Target
bytes were never patched. Raw PE supplies the instruction and boundary facts.

## Complete behavior and floating-point precision

The entry always clears float178/17C and integer170/174. Its signed-short
action13C dispatch contains32 handled IDs; remaining IDs retain these resets
without additional effects. Numeric actions and offset names are deliberate.

- Actions1..4/11/82..85 clear alpha113 and set angle12C to10.
- Independent41 and42 compute80 minus RNG25, then cosine/sine velocity pairs
  scaled by60/-60 and50/-50 respectively.
- Action61 clears alpha/state and sets angle180 only when yF0 >=480.
  Native FCOMP/TEST AH,1 rejects unordered as well as less-than.
- Distinct62/63 and132/133 arms draw separate X/Y scales and clear integer170.
  The compiler naturally shares only the native late conversion tail.
- Actions71/72 retain float-rounded random products before double velocity
  offsets, plus one shared X/Y scale. Draw limits and offsets differ.
- 81/131 clear alpha and state;86 only state;101 additionally sets X scale1.5.
-91 resets state, computes95 minus RNG10, clears alpha and shares random scale.
-111 and141 retain independent RNG15+30 calls with native shared late tail.
-121 shares scale then sets angle-10.151 clears alpha, sets Y scale2 and
  captures the existing event-runtime integer6E90EC into174.
-152..155 draw angle RNG50-25 then float178=RNG10*0.01f.
-170 sets X/Y scales3 and1.5.

Unsigned RNG conversion is explicitly to float before arithmetic, reproducing
native FILD and FADD single-precision2^32 correction. Float0.01f/0.1f retain
their promoted binary values. The decompiler's apparent extra unsigned branch
and incorrect discarded trigonometric return are not copied as semantics.
Normal typed calls use their returned doubles.

Only two new literal bindings are appended: double-3 at6C4C90, witnessed by
FSUBR6650EA; double95 at6C0868, witnessed by FSUBR665153. Both actual COFF
literal bit patterns match. Existing globals/ABI/headers/relocations are unchanged.

## Reproduction and scope

- scripts/repo-python scripts/build.py --unit exact-first-weather-effect-entry --compare --json
- scripts/repo-python scripts/audit-weather-effect-entry.py
- scripts/repo-python scripts/validate-tracking.py --require-target
- scripts/repo-python scripts/check-match-literals.py --require-target
- scripts/repo-python scripts/ci.py

First complete private source and formal public unit both match immediately.
The full-tail audit uses the canonical comparator, not masking or normalization
beyond its validated relocation replay. Receipts and full raw decode/CFG facts
are in build/frontier-664e10-20261027/. No source-shaping grid was needed.

Only this new independent unit is built. Prior exact receipts remain retained;
totals are incremental rather than a new whole-corpus replay. Final local CI is
pending at writing; its terminal log and exit code are the commit gate.
No actual gameplay, RNG, rendering or hardware execution is claimed.
