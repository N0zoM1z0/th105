# Natural shared atan2-degrees recovery

## Accepted result

Target `0x00406540`, 63 bytes, original Japanese TH105 1.06a SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
`src/engine/AngleAtan2.cpp` reproduces the complete canonical body using
official VC8 `math.h` `atan2f` and ordinary float degree conversion.
The dedicated `gpt-web-angle-atan2-natural` unit uses the existing strict-FP
profile: **63/63 exact**. Other angle lookups retain their previous profile.

```bash
python3 scripts/check-ida-mcp.py
python3 scripts/build.py --unit gpt-web-angle-atan2-natural --compare --json
```

Local report: `build/angle-natural-formal.json`. The relocated candidate and
target callable both hash to
`c6e3d63c7180373f7cdda0c68622c1fedbdcb700e55db0571986eb47834946b0`.
This replaces an already credited function and adds no exact-count credit.

## Target observations and compiler explanation

The target widens two float arguments for CRT `atan2 @ 0x0068BB70`.
Two distinct m32 store/reload pairs precede multiplication by float 180 at
`0x006D6EDC` and division by float pi at `0x006CD204`; a final m32 pair
precedes RET. The official float CRT wrapper and strict-FP expression
conversion explain these instructions naturally. The previous volatile
constants, pointer and self-assignment are removed, not treated as original
source evidence.

The overloaded C++ `atan2(float,float)` adds another wrapper layer and emits
71 bytes, including a non-target integer copy. Direct `atan2f` emits the
required 63 bytes. The default profile instead uses the intrinsic CRT call
path and does not match. The shared declaration is now
`float(float,float)` in `src/engine/AngleAtan2.hpp`: a coherent recovered
contract, not proof of unique original source spelling or TU partition.
The callee's final m32 store alone would not establish that contract.
IDA's prototype was updated and read back as float return / two float
arguments; `config/functions.csv` is the durable ABI record.

## Independent caller checks

`python3 scripts/audit-x87-return-sites.py 0x00406540` identifies 339 canonical
E8 calls. This is not complete return-value dataflow or indirect-call coverage.
Three accepted functions provide focused source/compiler witnesses:

| Caller | Result with the shared float contract |
| --- | --- |
| `0x004FC7C0` Alice flight state | 319/319 exact, no body change |
| `0x004FC900` Alice owner tracking | 343/343 exact, no body change |
| `0x004E0BF0` shared heading adjustment | 314/314 exact, retaining double negation then float narrowing |

A declaration-only change in the heading caller removed an observed m32
materialization: 306 bytes, first mismatch +0x5F. Explicitly widening before
negation and narrowing into `y_offset` preserves its previous double
arithmetic and target rounding without misdeclaring the callee.

Reproduction units: `cross-v106a-alice-flight-state` and
`cross-v106a-character-heading`. Local reports:
`build/angle-alice-flight-float-comparison.json`,
`build/angle-alice-tracking-float-comparison.json`, and
`build/angle-heading-float-widen-comparison.json`.

Nonexact CPU/Aya/Youmu probes use the same header and updated REL32 symbol.
They receive no exact credit from this correction. Their bodies are not a
new completion goal; continue the shared Fighter bosses.
Focused formal builds remain nonexact: CPU `0x005F1F80` first differs at
+0x12E (16,453-byte section tail), Aya `0x0061F0B0` at +0xDF (4,859),
and Youmu `0x00543670` at +0x80 (5,488). No unrelated modules or aggregate
cold replay were rerun for this correction.
