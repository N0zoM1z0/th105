# Komachi action-state candidate, JP 1.06a

## Status and scope

0x005E20E0 has a complete 108-action C++ candidate and focused replay unit.
It is **unselected and nonexact**. No implemented.csv, matches.csv, function
status, or accepted byte total changes.

The complete candidate emits 64,884 bytes versus 65,176 target bytes.
The stack allocation now equals native 0x490. First difference is +42 at
0x5E210A, constant materialization/save ordering after an identical prefix.
Near-equal lengths do not imply near-exact instructions.

Only the new unit was built. Shared accepted implementations and their
previous acceptance receipts remain unchanged; no cold full-corpus run.

## Current-target evidence

Factory-native IDA metadata hashes/size, entry 0x68B9D2, inventory probe
0x401000/52 bytes, and five mapped 16-byte samples matched the original
Japanese 1.06a target at 04:14–04:15 UTC on October 28. The full decompiler
artifact returned at 04:17; it is a semantic hypothesis, not source proof.
The legacy local check-ida-mcp.py still lacks mcp==1.26.0. No package
installation was used and that legacy command is not recorded as passing.

Raw hash-attested CFG:
- Callable: 0x5E20E0..0x5F1AD9, 63,993 bytes.
- All 16,310 instructions / 63,993 bytes reachable; no alignment holes.
- 136 RETs; 915 direct call sites to 30 targets.
- Seven resolved tables; no unresolved indirect exit.
- Three action tables: low 34, mid 41, high 31 physical destinations.
- A two-destination card gate with nine remap bytes.
- Three four-entry difficulty tables (first has three unique destinations).
- Direct actions 300, 540, 795, 797, 798 are outside the sparse tables.
- Full payload ends 0x5F1F78, 65,176 bytes; next callable starts 0x5F1F80.

Callable SHA-256:
bb737abb720d627a985ae38f3b3f11f0cabf31b7ad0b7f89ab7a6f809ea9b8bd

Full target SHA-256:
20d83eff7214346536177a1391fa993ccf62081c1b9ebc5aa048edc005094204

## Source and data-flow findings

The pointer-only view is not a complete recovered Fighter class.

All forty native crossed-surface consumers test AL. All twenty-four native
on-surface consumers also test AL; one loads a vtable pointer before TEST,
which the generic immediate-consumer summary does not recognize.

The native and candidate each have 94 resolved spawn-payload homes and no
unknown payload-pointer sites. Their sorted offset sets are identical:
56..1172, step twelve. This is an offset-set observation, not proof that
each action owns the same home. Native/candidate frames now both equal 1168 bytes.
Candidate physical return sites are 137 versus 136; virtual call sites
191 versus 192.

Three native virtual calls belong to the peer at receiver+0x170, not self:
0x5EED38, 0x5EF5B3, 0x5EFD89. The private stack diagnostic admits those only
after proving the local peer load, vptr load and slot+8 target chain, with
the normal four-byte argument purge. It does not accept arbitrary unknown
virtual receivers.

Recovered distinctions include:
- 540 applies the skill-606 peer cooldown before surface rings; 542 applies
  skill-60A cooldown afterward. 541/543 have their own skill-606 extra ring.
- 550 advances before clearing field 180; 551 clears before advancing.
- Only 203 clears frame_timer_142 on the shared air-dash landing path.
- 600 returns after successful advance/reset; 603 continues its entry logic.
- 710 preserves the original check of the old field 740 before replacing Y.
- 604 preserves its two peer/self health conversions and separate packet
  lifetimes rather than replacing them with an integer swap.
- Twenty-four ring layer predicates use ordered [0,180] membership. Native
  unordered comparisons take the negative-layer arm. The decompiler's
  apparent '<0 || >180' loses that behavior; the candidate now uses the
  actual ordered condition and complete per-arm argument preparation.

## Bounded byte-direction interface view

The candidate spawn declaration uses unsigned-byte direction with the same
four-byte ABI slot. This is supported by the real Komachi manager, not by
instruction matching alone.

The complete canonical manager 0x5F78C0 is 237 bytes, SHA-256
5facf0036e53de10e5916c20f880aa1bdff879ffd6212996a6f311072921bb80.
It reads only BYTE direction at 0x5F7962 (ESP+20 after two saves) and BYTE
variant at 0x5F7966 (ESP+24), stores them at object+104/+33C, and returns
RET24. The accepted roster spawn source uses byte formals.

The shared 66-byte forwarding wrapper 0x465190 forwards full DWORD slots,
which does not establish int formals. Independently exact int and byte
forwarding witnesses are already recorded in
[REIMU_SPAWN_DIRECTION_WIDTH_2026_10_18.md](REIMU_SPAWN_DIRECTION_WIDTH_2026_10_18.md).
Those accepted sources are not modified here. Original signedness/type
spelling remains ambiguous; this is a supported binary call view. The
variant remains int in this candidate. No register or manual-stack facade.

Runtime boundary globals 0x6FBD24 and 0x6FBD1C are address bindings with
loader-zero contents, not numeric constants.

## Comparisons and remaining differences

Whole candidates were compiled before refinement:
- First complete int-direction candidate: 64,596 bytes, first +8.
- Ordered ring arms and separate virtual argument branches: 65,428, first +8.
- Byte-direction view: 65,156, first +8.
- Explicit wind turn branches: same length; final SHA below.

All mapped per-action floating arithmetic counts agree except 567, whose
native first 824 shot has two identical argument arms guarded by field 738.
Raw 0x5EE24F branches to separate calls 0x5EE2AD/0x5EE2F6 using the same
packet; the candidate coalesces them. Do not insert an inert branch to force
the duplicate physical sites.

Other physical-call diagnostics: 603 has eight/seven RNG call sites;
720 has seven/four spawn sites and six/three wave sites. These are reachable
physical sites, not dynamic execution counts. Shared tails/argument epochs,
constant materialization and exact instruction ownership remain unresolved.
Low 209/212 merge to one candidate owner, leaving 33 rather than 34 low
destinations. Source behavior and complete execution equivalence are not
claimed verified solely by these structural diagnostics.

The native flight 214 repeats the same resource gate twice without an
intervening write/call. The candidate keeps its logical condition once;
no volatile or inert duplicate gate is added.

## Reproduction

    taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py --unit exact-first-komachi-action-state --compare --json
    scripts/repo-python scripts/audit-komachi-action-state.py
    scripts/repo-python scripts/ci.py
    git diff --check

Both comparators correctly report mismatch. The complete-payload audit
rechecks target identity, all seven tables, reachability, length and unmasked
bytes. Final candidate SHA-256:
5ac7b06797104542570da85ab2029169a844efbcfa0f6bba55c766af74cd5771

61,429 positional differences including missing tail bytes are diagnostic,
not a completion percentage.

Receipts: build/frontier-5e20e0-20261028/formal-frame.json and formal-frame-audit.json.
Private raw/source diagnostics are in that build directory and
.analysis/frontier-5e20e0-20261028/. Checked-in source is authoritative.


## Scalar frame and request preparation refinement

The private VC8 source listing identifies the extra eight-byte allocation:
tv26973 is a qword temporary following all 94 arrays, holding jitter+180
hoisted out of action 730's difficulty-three loop. It is not an extra packet.
Changing packet sizes or adding padding would not explain it.

Native 0x5F0DEF writes the angle to a DWORD home while retaining the x87
value, then adds jitter and 180 before writing the packet at 0x5F0DFD.
A float trajectory source expresses the observed scalar copy and removes the
extra hoisted qword. Angle-only control emits 65,188 bytes with frame 0x490
and first difference +42. This isolates the frame change from the separate
request-preparation edits.

The inference is bounded: actual loop indices are 0..11, base is roll(360),
steps are 30/45/60 and the optional offset is 22.5. Jitter is roll(20)-10.
All angle values here are small integer/half-integer values exactly
representable in binary32. This is not permission to narrow arbitrary x87
intermediates elsewhere. The compiler's extra store/reload around the angle
still differs from native's FST-retained-value sequence, so the original
expression is not claimed recovered byte-for-byte.

801 and 902 circular emissions now calculate X/Y in their ordinary call
arguments instead of materializing both named coordinates before preparing
the request. The native pushes count/pointer/layer/direction before sine,
prepares outgoing Y before cosine, then calls spawn. The selected expression
restores that lifetime shape. Standalone controls emit 64,932 and 64,852
bytes respectively while retaining frame 0x498; neither alone explains the
frame recovery. The combined selected candidate is 64,884 / frame 0x490.

The unrelated dust-base narrowing hypothesis was explicitly rejected:
0x5E2D08 stores the captured X+50 as QWORD before RNG. Its existing double
capture is retained. No artificial local, register assignment or byte patch
was used.

Final stack audit still resolves all 94 payload homes; its offset set remains
56..1172 step twelve, unchanged from native. Physical call and arithmetic
residuals remain those described above. The preceding checkpoint is retained
in Git; none of these structural improvements adds exact byte credit.
