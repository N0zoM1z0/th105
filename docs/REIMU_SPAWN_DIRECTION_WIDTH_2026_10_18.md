# Reimu: byte-direction view admits the 214 branch recovery

The root now uses a byte-direction call view supported by the complete real
manager and two independently compiled forwarding-wrapper witnesses. This
recovers520/521's instruction/edge diagnostics without20 manual direction
captures and admits214's explicit facing branches inside the original
envelope. The current prefix is81516 bytes,34 below the callable limit.
The complete root remains nonexact at+541; no source-present or exact credit
is assigned to478FA0.

## Target observations and type ambiguity

Target is Japanese TH10.5 v1.06a, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Root `[478FA0,48CE2E)` and its81550-byte SHA-256 remain unchanged:
`dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6`.
IDA preflight rejects the different attached image. This work uses attested
raw PE and normal VC8 compilation, without database or instruction writes.

Observed complete forwarding wrapper465190 is66 bytes, SHA-256
`80aab8cb379377dc179c3e1311599ab890885fa92ffd5ecf075ff6c3df15a7fc`.
It forwards the seven request arguments, dispatches manager vslot+4, then
RET1C. In particular4651A4 loads the direction's full DWORD slot at entry
ESP+10;46519F loads the variant at entry ESP+14. That forwarding alone does
not prove the original formal types are `int`.

The actual Reimu manager vptr6C40FC dispatches slot+4 to4938D0. Its complete
237-byte body, SHA-256
`33cec1265f0607a5fc8ea79307a3246a61d6d042bcde419e21b91904e129b516`,
has the following direction/variant reads and copies:

| Site | Observation |
| --- | --- |
|493972|MOV CL,BYTE[ESP+20], direction at entry ESP+18 after two saved registers|
|493976|MOV DL,BYTE[ESP+24], variant at entry ESP+1C|
|493990|MOV BYTE[object+104],CL|
|4939A8|MOV BYTE[object+33C],DL|
|4939BA|RET24 for nine four-byte argument slots|

No other direct read of either slot occurs in the complete body. The accepted
spawn source uses signed-char facing/unsigned-char variant; the byte copies
themselves do not establish signedness. Both the wrapper and manager already
have separate accepted exact units.

Fresh private normal-COFF witnesses compile the wrapper source with (a) byte
direction/int variant and (b) byte direction/byte variant, changing both its
formal and the corresponding virtual declaration consistently. Each has no
code relocations and reproduces all66 bytes, including RET1C, without a byte
patch, pragma, register force or special compiler flag. The original int view
also freshly passes its existing unit. Thus width remains ambiguous; this is
a bounded binary interface view, not a recovered original declaration.

## Selected source and compiler results

`ReimuActionStateStaging.hpp` changes only the direction formal of both owned
request overloads to `unsigned char`. Their four-byte argument slots, receiver,
return, variant and pointer/count interfaces remain unchanged. Existing request
expressions preserve the distinction between signed facing for coordinates
and unsigned direction bits. No manual captures are added. Probe bindings add
the two corresponding decorated aliases to the real465190 provider; legacy
int aliases remain valid. The accepted wrapper implementation stays unchanged,
and its ledger note now records the demonstrated formal-width ambiguity.

`ReimuActionStateLateLowCases.hpp` expands214's two ternary facing comparisons
into ordinary facing/X branches, preserving the flip, callback and alternate
setter on each path. It retains one resource condition. The prior target has
two physical resource gates; neither their exact duplication nor the original
source is claimed recovered. No inert second gate or volatile read is added.

| Source view | Prefix / payload | Result |
| --- | --- | --- |
|Previous int direction|81544 /82916|Fits;214 has10 reachable indirect sites|
|Int direction +214 branches|81608 /82980|Oversize58/56; never executed|
|Byte direction alone|81460 /82832|Fits;520/521 instruction/edge diagnostics agree|
|Selected byte direction +214 branches|81516 /82888|Fits;214 has14 reachable indirect sites|

The byte-direction-alone control is identical over its entire82832-byte
canonical payload with and without the retained20 full-width captures:
SHA-256 `abfe46df3bc596cf4a138ffaa67234107c8fce43e9321b6102bd3e27882ddec3`.
This is new type-phase evidence; the earlier int-direction controls do not
answer it. Do not infer original source spelling from the equivalence.

Fresh genuine ordinary object SHA-256:
`09e442597b0ea4fac158b94a08124febff8b796fc80254d6788337ac99cb9992`.
All82888 linked/ordinary canonical payload bytes agree, SHA-256
`4397250750a2439691766571524b2eccdb0fb218d31454a1ff6b875d7329dc5e`.
Frame570h,20304 source reachable instructions,11 switches and all15 request
buffer/preparation contracts qualify. All2476 relocation fields replay:
1188 calls,1104 numeric,14 metadata,163 code pointers and7 globals;1281 PE
HIGHLOWs and the separate12-byte INT3 gap also qualify. The DLL is not executed.

The strict first target difference remains+541=4791BD: JNE4791BB targets
489D6A versus candidate489D4B. Full primary520/521 spans881/794 preserve
encoded instructions and owner-relative edges in the diagnostic. This is not
canonical or partial exact credit.522/523 still have different landing and
advance exits, and eight direct-callee complete partitions still differ.
All128 per-action direct-callee counts agree; even the matching aggregate1188
direct calls does not close these ownership questions.

One previous distinction does recover naturally: the complete advancement set
215/797 agrees at target47BFB2/source47C025, while310 separately agrees at
47D94A/47D9F9. The subsequent slot8/RET remains shared differently:
target215/412/797 versus candidate215/412/616/797. Equal direct sharing must
not be promoted to a complete terminal-tail ownership claim.

The fresh indirect census has target220/source222 physical sites.214 and414
now have equal aggregate reachable counts. Six aggregate action deltas remain:
73(3/2),75(5/4),88(3/2),200(3/2),410(4/3),416(5/4).
Complete partitions and uncertain slot domains remain distinct from dynamic
behavior. See [the census contract](REIMU_INDIRECT_CALL_SHARING_2026_10_18.md).

## Focused validation and remaining work

```sh
nice -n 10 taskset -c 0 python3 -B scripts/build.py --unit fighter-owned-object-spawn --compare --json
nice -n 10 taskset -c 0 python3 -B scripts/probe-reimu-action-ltcg.py
nice -n 10 taskset -c 0 python3 -B scripts/audit-reimu-root-stack.py build/reimu-ltcg/ordinary.obj --action 520 --action 521 --action 522 --action 523 --native --require-contracts
nice -n 10 taskset -c 0 python3 -B scripts/audit-reimu-void-root.py build/reimu-ltcg/ordinary.obj --cohort integration --cohort steering --cohort flight_exit --cohort surface_inputs
nice -n 10 taskset -c 0 python3 -B scripts/audit-reimu-trajectory-returns.py --output-dir build/reimu-direction-contract/current-trajectory
nice -n 10 taskset -c 0 python3 -B scripts/audit-reimu-owned-returns.py --output-dir build/reimu-direction-contract/current-owned
nice -n 10 taskset -c 0 python3 -B scripts/audit-reimu-call-sharing.py build/reimu-ltcg/ordinary.obj
```

Current focused native checks pass0/1888 for520..523 buffers/first requests
and0/2015 for1010 integration,432 steering,288 flight exits and285 nonflat
surface cases. The void-root adapter now exposes the existing two214 cohorts
without replaying their unrelated historical families. Every exit input must
execute actual resource consumption and RET; all four original facing/X
comparison branches47BD95/47BDDD/47BE39/47BE8D are required across the cohort.
The current complete trajectory comparison passes0/320 with1600 objects per
process, real callbacks/destruction and identical full unmasked snapshots.
Other returning object families pass0/800 with3920 objects per process;
focused circular0/5/99 objects and effect0/40 smokes also pass. All nine primary
database hashes are unchanged. No full historical matrix was repeated.

Receipts, exact target access packet and phase-specific control recipes are
under `build/reimu-direction-contract/`. Heavy jobs remain serial, CPU0/nice10;
the genuine producer peaks at320972KiB (about313MiB). No shared compiler
profile, accepted unit source, layout or exact ledger changes. No aggregate
cold replay is claimed. Rejected/duplicate binaries and snapshots are removed
after recording hashes, preserving the current genuine provider cache.

Next recover the complete522/523 landing/advance sets and the remaining six
indirect action deltas within this source phase. Formal-width ambiguity,
original TU/visibility, complete whole-root equality, arbitrary resources and
exception/returning-world coverage remain open.
