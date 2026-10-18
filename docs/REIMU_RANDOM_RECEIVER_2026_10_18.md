# Reimu: recover the random-range receiver

Reimu's random projectile calls now preserve the observed receiver at actor+4.
This natural calling-interface correction moves the full canonical comparison's
first difference from **+17 to+541**, and restores three physical wave calls.
It does not make the complete root exact: the expanded candidate currently
exceeds the callable/metadata limits and remains read-only.

## Target observations and ABI ambiguity

The target is original Japanese TH10.5 v1.06a, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Root478FA0 owns `[478FA0,48CE2E)`,81550 callable bytes, SHA-256
`dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6`.
The mandatory IDA metadata preflight still rejects the other executable.
This work uses raw attested PE instructions and real VC8 builds/native helper
execution, without analysis database or target instruction writes.

The26-byte range wrapper at4351A0 computes
`lower + selector_random_roll(upper-lower)` and returns with RET8. Its body
does not read ECX. The existing global `__stdcall` producer therefore matches
26/26, but that byte equality cannot distinguish a global function from a
member entry with an unused receiver. Its ledger now records this ambiguity;
the canonical byte producer and accepted exact result stay unchanged.

The original caller supplies the missing evidence. Each random loop computes
EDI=actor+4 and restores ECX from EDI before **both** range calls:

| Action | Range(0,30) | Range(0,5) |
| --- | --- | --- |
|400|47DD26|47DD4B|
|401|47E268|47E28D|
|404|47E9EE|47EA13|
|406|47EFED|47F012|

A full reviewed-CFG reaching-definition packet traces ECX at all eight sites
through the LEA/MOV chain to the entry receiver+4, including loop backedges.
The same proof succeeds at all eight expanded-source sites. The packet is
`build/reimu-random-receiver/receiver-packet.json`. Original class identity and
original source spelling remain unknown.

## Source correction and resulting compiler changes

`ReimuActionStateStaging.hpp` now supplies a nonvirtual receiver-only view and
an ordinary inline accessor for actor+4. The two source range expressions use
that view; case expansion produces the eight observed member calls. There are
no added data members/vslots, changed field offsets, forced registers, asm,
volatile accesses, dummy values or compiler-flag changes. The accessor is a
staging view, not a new original function boundary.

The receiver-aware symbol binds to the same genuine26-byte ordinary provider.
Both interfaces have two stack words and callee cleanup8; the provider ignores
the additional ECX value. The binding preserves actual caller evidence without
inventing an implementation or asserting an original class name.

The former global-call spelling left ECX unchecked and did not keep actor+4
live across the random loop. The corrected interface changes the compiler's
register allocation and restores separate ordinary/random wave tails in
401/404/406. Across all128 nondefault action entries, target/source reachable
direct-call cardinalities now agree. These are static counts, not dynamic
multiplicity, matching ownership or semantic completeness claims.

First difference is now the displacement of JNE at4791BB: target jumps to
489D6A, source to489D79. Both destinations contain the identical eight-byte
epilogue `5F 5E 5D 5B 8B E5 5D C3`. The comparison still includes that field;
it is not normalized away or given partial exact credit.

## Complete object/link checks and current boundary

The fresh ordinary object is SHA-256
`cd8c98ae6027ef3b0b48ef36c60609cd631cc14114a38731c5378a950201432f`.
Its code prefix is81592, payload82964 and frame570h;20353 instructions are
reachable, versus target20243. All11 switches, nine default buffer partitions,
the added550/551 partitions and all five circular preparation contracts pass.

The genuine linked and ordinary payloads agree over **all82964 bytes**,
SHA-256 `589209c9b311765b6d3f5fa689dcd80d9747732cf4f9fce4b98b97625de0944e`.
All2468 fields qualify:1180 E8 calls,1104 numeric operands,14 metadata pointers,
163 code pointers and seven global addresses. The1281 HIGHLOW inventory and
separate12-byte INT3 linker gap remain required.

The complete root is **42 bytes over the callable limit and40 over the
metadata envelope**. The expanded object and linked DLL are never executed.
Bounds are not extended, bytes are not clipped, and execution guards stay
unchanged. Current returning-manager auditors must wait until strict fit is
restored; earlier full-backend results belong to the preceding source version.

The fresh sharing census identifies remaining physical differences:

- 300/320 still merge the whole source body; target duplicates their prefix.
- 215/797 share target advancement; source instead joins310/797.
- 522/523 share the source's last request/wave/advance tail; target keeps them separate.
- 410/414/416 share one source effect site where target retains three.

The last two explain the remaining one-wave/two-effect physical deficits.
All per-action callee cardinalities agree despite these incoming-set differences.
214's redundant target resource gates also remain unexplained; this is not
permission to add volatile reads or inert duplicated conditions.

## Native validation and controls

The bounded compact void witness is50784 bytes and is separately qualified
for execution. Its object SHA-256 is
`0b6c41487ff4c3bb1dc41609bcabb104318f2ffd4adcd4a72e26b0da23f476a4`.
The inherited projectile helper check now requires **actual ECX=actor+4** at
4351A0 entry, in both target and candidate, before executing the real helper.

The new480-input cohort covers four actions, five raw facings, PC53/64, three
MT seeds, two shot counts and ordinary/random modes. All480 comparisons pass;
the240 random inputs execute480 real range/MT calls per side. Target checks
require the object800 request and the actual `(0,30),(0,5)` argument sequence.
Actor, MT state/index, FP control, call observations and request payloads remain
unmasked. The aerial fixtures stay above the surface with zero acceleration
so real landing does not bypass the requested firing path.

An additional2128 cases pass:1010 integration,510 defaults,600 aiming-lifetime
inputs and eight guarded740 indeterminate-read boundaries. This is **0/2608**
focused comparisons, not a replay of the historical full matrix. World calls
still stop at their real entry; no returning-world result is invented.

A compiled actor+8 accessor control fails immediately at4351A0 with
`unreviewed receiver`, despite the callee's unused ECX. The selected source
stays at+4. This closes a caller-input hole that output-only range checks missed.

An earlier compiler-only RTM42 control used the preceding receiver-free source
and unchanged SP1 headers/flags. It produced prefix81576/text82948, retained
first+17 and exceeded the callable limit26; it was never executed. The
RTM/SP1 cl/c1xx/c2 file versions and hashes are recorded under
`build/reimu-compiler-versions/`. This is phase-scoped negative evidence, not
identification of the original compiler patch or a full RTM library profile.

## Reproduction and continuation

Run heavy commands serially on CPU0 at nice10:

```bash
nice -n 10 taskset -c 0 python3 -B scripts/probe-reimu-action-ltcg.py
nice -n 10 taskset -c 0 python3 -B scripts/probe-reimu-action-source-shape.py --compact --void-root --output-dir build/reimu-random-receiver/compact
nice -n 10 taskset -c 0 python3 -B scripts/audit-reimu-void-root.py build/reimu-random-receiver/compact/ReimuActionStateDispatch.obj --cohort projectile_receivers
nice -n 10 taskset -c 0 python3 -B scripts/audit-reimu-void-root.py build/reimu-random-receiver/compact/ReimuActionStateDispatch.obj --cohort integration --cohort defaults --cohort unresolved740 --cohort aim_argument_lifetimes
```

`build/reimu-random-receiver/` retains receipts, source/target packets, the
fresh sharing census and focused native reports. The+8 control copies the
compact source/header, changes only the accessor's unique+4 to+8, and compiles
with the ordinary recipe before running the receiver cohort; expected exit2.
Large duplicate sources, objects and temporary reports are cleaned afterward.
All9 primary analysis database files hash unchanged by streamed reads.

Root remains unclassified/declaration-only with no new exact/source-present
credit. Continue reducing the supported lifetime/physical-sharing differences
and restore full callable/metadata fit before executing the expanded root.
