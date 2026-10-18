# Reimu: nonflat surface inputs and real height-provider visibility

The current root passes285 nonflat-surface inputs covering actual root height
queries in all38 actions whose height-call sharing differs. A compiled missing
Y-assignment control passes76 flat landing inputs but fails nine new nonflat
cases. Separately, real height-provider IR changes the giant caller's frame
from570h to568h while the getter itself still matches89/89. The changed caller
is not selected; root exactness remains unproved.

## Target and current candidate

Target SHA-256 is
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Root478FA0 owns81550 callable bytes, SHA-256
`dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6`.
The rejected IDA session supplies no semantics. Observations use raw attested
PE, actual helper execution and genuine VC8 compilation/linking.

The current diagnostic ordinary object is unchanged:
`710094fe7ca95169efd3e53b66a41a8ab1f6ef1f44e83a9f4caea14ac920eca7`.
Its prefix81544/payload82916/frame570h and canonical payload
`a6dc1ccf19322b8ab5c431671d0d204d7b26b29c2c3f8c47292a1d332d44a6bc`
retain first strict difference+541. Default C++ source, layouts, flags,
bindings and acceptance ledgers remain unchanged.

## Actual height-query inputs

Getter435D60 reads actor X at+EC and indexes1280 floats at6FA898, with the
reviewed endpoint clamps and float return. The fixture checks the attested
global binding and that the entire5120-byte array is writable PE data.
Only emulated data changes; the target file and instructions remain untouched.

`surface_inputs` supplies the exact binary32 pattern
`height[i] = 5 + ((i % 17) - 8) / 8`, ranging from4 to6. Pattern SHA-256 is
`109ccfb88bce7354ccb29921cbf379120c55df8e74cfef2cf2e54055334a0294`.
Its285 inputs comprise209 existing integration inputs for the38 actions and
76 explicit landing inputs, one per action at PC53/64.414/416 use their actual
falling-frame gates;795/797/798 use sequence0. The fixed surface values at
X640/480/800 are5.375/4.5/4.125, and target self-checks require those final Y
values for the corresponding high landing inputs.

At every actual435D60 entry in this cohort, the observer requires ECX=actor
and records the current raw X bits. It distinguishes root calls using the
actual return address and verifies the preceding E8; physical addresses are
reported separately rather than compared as semantic inputs. Original getter
instructions execute through RET. No result or register is substituted.

Each side executes381 actual height queries,90 from the root, covering all38
actions. The sampled root sites are12 target/10 source; this is focused dynamic
coverage, not the complete56/54 static inventory or ownership equality.
All actor bytes, supplied MT state, FP control, bounded world word, ordered
calls/query-X bits and requests agree. World requests retain their existing
real-entry stop boundaries.

The flat initial array is restored before every other cohort and checked
after execution. The combined285 surface plus192 falling-return cases pass
**0/477**. Legacy falling landings explicitly require final Y=+0, proving the
nonflat data did not leak into the following fixture. Input SHA-256 is
`c8166dae41877540eb6f18820f3f300ada3fead05d65d40345fa1598fec55092`.

```sh
nice -n 10 taskset -c 0 python3 -B scripts/audit-reimu-void-root.py build/reimu-ltcg/ordinary.obj --cohort surface_inputs --cohort falling_returns
```

## Compiled controls and the flat-data limitation

The old comparator is preserved fromd9868f9, changing only its repository ROOT
path for a private copy. Its argument/state checks are not removed or masked.

Moving the797/798 X assignment after the real height query is **already caught**
in6/285 flat cases by the old `ftol2` operand trace, despite identical final
actor bytes. Flat data did not hide that input-order error from the old oracle.

The independent negative instead keeps the real height call, X assignment
order and all other operations, but discards its result instead of assigning Y
in795/797/798. It is an ordinary compiled compact void witness, SHA-256
`84c0e762664e4c3b5cfd20f0390f08183c168b20d6cc3d0feb356b1058516bdf`,
admitted by the existing bounded compact guard. It receives no source or
matching credit.

| Missing-Y-assignment control | Cases | Differences |
| --- | ---: | ---: |
|Unmodified legacy oracle, flat data, all landing inputs|76|0|
|Current oracle, nonflat data, complete surface cohort|285|9|

The shown nonflat failures retain identical ordered call traces and differ
only in actor Y bytes. Thus changing the input data adds observable state
evidence even when call/input logging alone is insufficient. Both negative
sources and all helper code are genuine compiled C++/target execution; no
callback result is fabricated. The flat76 input SHA-256 is
`44708d2cf8db61d9e98b67a99850f851e3933eca1e591adddde16544d2ba62e0`.

## Real provider IR changes the caller, not its sharing partitions

A separate read-only link experiment uses the complete genuine StageGeometry
TU with /GL. Fresh ordinary comparisons retain all four accepted anchors,
including435D60 at89/89. The root's true direct calls use the actual
`stage_surface_height_at_x(Fighter*)` symbol; the facade-alias control remains
separate. Both source variants have the same entire82916-byte ordinary
canonical caller payload before linking, isolating visibility from declaration
or pointer-adjustment changes.

The two linked getter bodies independently normalize to all89 target bytes,
SHA-256 `4896deab933804203efe263ac8d771c5a471cc54e11b56fa25a6ed2134550895`.
The normalizer classifies the actual four HIGHLOW fields using the named
source array and immutable0.5 literal, and the FTOL call by MAP identity.
It does not borrow old caller relocation offsets.

| Linked caller | Frame | Code / payload | Reachable instructions |
| --- | --- | --- | ---: |
|Facade calls, genuine provider IR|570h|81544 /82916|20334|
|True direct calls, same genuine provider IR|568h|81480 /82852|20333|

The alias caller replays identically to the normal producer. The direct caller
already differs at prologue byte+8 and cannot use the old ordinary caller's
position ledger. Independent PE metadata/CFG analysis at its actual address
closes all11 switch tables and128 action entries, derives the entire payload
and separate12-byte INT3 gap, and checks virtual cleanup/stack traversal.
It is a read-only observation, not full caller canonicalization or admission.

Both retain1176 E8 calls,54 height calls and the identical complete source
call-sharing multiset for all32 callees. The same eight target partition
differences remain. Both small forwarders are nine-byte MOV/JMP sequences;
their behavior supplies no positive inlining witness. Callee byte equality and
unchanged call counts do not imply unchanged caller code generation. The
precise source-visibility/lifetime cause is still an inference to investigate,
not an original TU or inlining-threshold identification.

No private DLL executes, and the normal producer's provider-IR guard stays
unchanged. An additional explicit actor+4 cast replacing the staging RNG
getter also gives the identical entire ordinary payload and is not selected.

Receipts and compact evidence are below `build/reimu-height-inputs/`. Measured
477-case peak RSS is188384KiB; read-only IR analysis is276984KiB. Heavy jobs ran
serially on CPU0 at nice10. Primary database hashes remain unchanged; duplicate
objects/images/input snapshots are disposable after their receipts are retained.
No full historical or aggregate replay is claimed. Continue with the complete
caller sharing/lifetime differences while retaining the570h opaque-provider
candidate and all strict acceptance guards.
