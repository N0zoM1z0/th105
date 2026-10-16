# Aya CPU policy tails and the real roll100 endpoint

The retained `Aya_update_cpu_action_policy @ 0x006126E0` source is unchanged
from the signed-counter checkpoint:17/41 diagnostic owners, whole16,032-byte
comparison nonexact+12E, metadata16088 and section tail16713. This batch
identifies the remaining selector-tail sharing and closes a real input-domain
gap. No authored exact bytes are added.

## Observed target and native endpoint

The selector uses unsigned division by `UINT_MAX / limit`, not modulo.
With limit100 it can return **100**. The previous seed corpus covered only
0..99. Instruction coverage alone had not exercised every candidate call site.

A private host-side integer seed search finds **seed1472677**. This is an
input search, not a replacement RNG implementation in the oracle. The original
target seed/next/selector instructions independently confirm:

```text
discard one seeded draw
root's selector(1000): next draw
policy0 selector(100): third seeded raw = FFFFFFB6, result = 100
```

The corpus keeps the original hundred seeds in order and appends this genuine
seed at index100. Each expected roll is still confirmed by target execution;
no return value, RNG state word or helper result is injected. A native endpoint
trace retains the actual raw value and caller stack return addresses.

```bash
python3 scripts/audit-cpu-policy-paths.py build/match-units/GptWeb_AyaCpuActionPolicy.obj --root aya --selection-cases
```

The current command runs **16160 cases**, including all101 native roll outcomes
across the existing geometry/facing matrix. Result: **zero differences** through
genuine RET; all **1486 reachable target instructions /4879 bytes** in policy0
are visited, and both executions observe0..100. Input SHA-256:
`bb6b26c3b92de692ab6d927f74df3f1f6e8754b4d5b2e024cee49f955e769fd0`.
The earlier16000-case result remains a separate, narrower checkpoint.

This retains the existing actor/RNG/native-call/conversion-input/stack/control-
word checks and their masked-PC53 fixture scope. Numerical, branch, exception
and complete gameplay equivalence remain unproved outside these sampled inputs.

## Observed caller sharing

The oracle now decodes valid root E8 sites before recording a selector's native
return address. It pairs caller sites by ordinal and argument only when the
entire existing output/call comparison agrees. Invalid instruction boundaries,
different trace lengths and different arguments fail closed. Candidate sites
below are rebased COFF coordinates, not durable names for target instructions.

Static selector calls remain **114 target /119 candidate**. All five net extra
calls belong to the large physical policy owner:35 versus40 there. Its
limit10 sites are2 versus6, and limit40 sites are2 versus3. Equal counts for
other arguments do not imply equal sharing.

The complete native matrix observes **38 target /43 candidate selector sites**,
including the mandatory pre-policy selector(1000). It records **46420 call
observations across49 site pairs**. The formerly unvisited candidate61556F
executes with roll100 and corresponds to target615A74 in sampled paths.

| Target completion | Argument | Observed candidate sites |
| --- | ---: | --- |
| `6153E9` | 10 | `61512B`, `615E10` |
| `615A74` | 10 | `61526C`, `61556F`, `61567D`, `615A31`, `615E10` |
| `616269` | 40 | `615CE0`, `616041` |
| `6161DE` | 30 | `615397`, `6153D9`, `616071`, `6160BD`, `616195` |

Candidate615E10 also merges both target10-limit sites. Several30-limit
candidate sites merge distinct target completions, while target61579D splits
between two candidate sites. Thus the correspondence is **many-to-many**.
It explains the net count difference without supplying a static bijection or
authorizing call-site masking in canonical comparison. The complete mapping
and observation counts remain in the native report.

## Rejected source explanations

Four bounded controls have identical complete **16713-byte canonical section
tails**, SHA-256
`03446cc0ddc49438b8753810154a7dbe4d5faf1a7a72e20d9f5beffd2f8261d2`:
an actual inline timer setter at the10-limit fallback, the same setter at all38
random timer assignments, lifting the40-limit fallback, and lifting both
fallback joins out of the nested quadrants. These controls are discarded;
their spelling and lexical placement do not explain the compiled ownership.

A float Y-field accessor raises metadata to16208 and worsens large-region
instruction/edge differences without a new identical owner. An ordinary
grounded predicate leaves an unbound out-of-line helper; no target alias is
supplied. Forcing that real predicate inline changes metadata to16044 but
still recovers no additional owner. Neither height control is retained.

The next source work must reconcile interval and x87 lifetimes with the joint
split/merge completion graph. Original local lifetimes, source spelling and
TU/LTCG ownership remain unknown; no standalone/LTCG impossibility is claimed.

## Reproduction and working state

The target is original Japanese1.06a SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`;
root hash remains
`7efa001552238230ac86c77f48f36a217cc486e847f85cb924527c64e2dc6e09`.
The ordinary root comparison is freshly rebuilt; its canonical window remains
`271db482bf39d5657ecc845cf59a396cc6805cc8af0a1e5555abbbf9f3ad971a`.
The native receipt now also fingerprints the complete canonical candidate
section tail, independently of COFF timestamps. Build provenance is still
reported separately, without being inferred from a hash or a native pass.

Direct Ghidra re-attests executable/import identity, Windows/x86, entry and
all mapped.text bytes, then saves and independently reads back the four call
comments and signed768/76A method-view fields.4097 instructions, layout and
target bytes remain unchanged. IDA preflight rejects its other executable
and is unused. Temporary Ghidra copies and discarded probe binaries are removed.

Reports use `build/aya-cpu-tail-*`; private controls and the seed finder are
under `.analysis/aya-cpu-tails-20261017/`. Local CI passes183 tests, including
three caller-identity/trace-pairing regressions without proprietary input.
Earlier native counter/finite/command/height results retain their prior
checkpoint scope. No unrelated accepted-unit or aggregate cold replay is claimed.
