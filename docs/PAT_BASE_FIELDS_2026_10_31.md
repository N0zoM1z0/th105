# PAT base-field widths and implicit assignment

The whole305-byte PatRecord88 assignment at460DD0 is reproduced by VC8's
implicit operator=. No assignment implementation was transcribed or written.
The probe merely takes the ordinary member-function address using the actual
shared type declaration.

## New independent layout evidence

Native assignment copies eight WORD fields at04/06/08/0A/0C/0E/10/12, the single
byte14, and the pointer18. It does not copy bytes15..17. The prior neutral
FrameData view used four DWORD members and a DWORD/byte union at14, including
explicit padding bytes. That view preserved the constructor's bulk zeroing,
but its generated assignment was295 bytes and first differed at+8 on a DWORD
load instead of the native WORD load.

The shared view now represents eight raw16-bit fields, byte tag14 and natural
alignment before pointer18. Original signed meanings remain unspecified;
these raw fields assert storage width, not gameplay names. Size remains1Ch,
and offset assertions cover the first/last WORD, tag and payload pointer.
No layout size, vtable, vector stride or allocation extent changes.

The optimized derived construction retains its independently observed20-byte
base-field clear at+04, explicit tag14 publication and pointer18 initialization. All five exact record/
base lifetime roots still match. The declared out-of-line base copy constructor
is unchanged; the existing311-byte generated record-copy proof also still passes.

## Complete comparison and provenance

The generated assignment copies the existing typed derived fields and invokes
the real vector assignment providers at460AD0 (twice) and460980. Canonical
whole-body comparison, including all three call operands, is exact305/305:

887079406c65a5624d4dbcf05cfb5bc56230624d17888f9ebdf51133850adb1d.

The generated-origin validator independently finds a unique full-inventory
fingerprint with293 invariant bytes, no alignment tail, pinned compiler and
native body hashes, and unchanged coverage gates. This is compiler-generated
ownership, not authored game progress. No hand-written container body, forced
register, explicit padding member, assembly or prefix-only match is used.

Public source probe: scripts/probes/PatRecordAssignmentOrigin.cpp.
Public unit: vc8-pat-record-assignment-origin.
Origin anchor: config/vc8-pat-record-assignment-origin-anchors.toml.

## Affected checks

Dependency discovery finds seven source units. All11 accepted authored
functions in their four accepted cohorts freshly remain exact. The other three
candidate-only units still compile; they gain no exact credit. Additionally,
all32 previously excluded generated bodies in five header-dependent origin
rules freshly pass their native validations. The new305-byte rule passes too.
Unchanged unrelated origins are retained, not globally rebuilt.

The old295-byte assignment is negative layout evidence, not an alternative accepted
implementation.

Exclusions increase to1,641 and review decreases to614. Match units become746.
Authored exact remains1,555 /441,708 bytes; source1,752, authored ownership1,772
and mapped1,779 are unchanged.

Default CI passes192 tests; generated progress and whitespace checks pass.

## Natural base-copy boundary after the field correction

A follow-up removes the provisional user-declared FrameData copy constructor.
With the corrected fields, VC8 now naturally emits the implicit base copy at
421B30, exactly91/91, and naturally keeps the existing derived copy constructor
460C90 at311 bytes with its real out-of-line base call at460CBE. The earlier
explicit declaration had compensated for the old coarse field view; it is no
longer needed to obtain the observed source partition. No inline/noinline
directive, out-of-line hand-written implementation or alternate ABI is added.

Base copy native/canonical SHA-256:
10efb600913c42cb24cd2fa09f5def3b73b42a044faf3f2888eb9f96ea80286b.
The entire body, including the independently known FrameData vtable6C0908,
matches. The new origin rule checks full-inventory uniqueness, native hash,
the real derived-constructor call and the vtable's native destructor entry.
Its87 non-relocation bytes and complete91-byte canonical replay are separate
proofs; no prefix-only result is promoted.

The existing pat_record_copy_generated.cpp probe supplies the real derived
copy context. All33 prior header-dependent generated-origin bodies again pass.
All11 affected authored roots again remain exact, and the three candidate-only
units still compile. The305-byte assignment also freshly replays exact.
The new91-byte copy is compiler-generated, not authored game progress.

New public unit: vc8-pat-base-copy-origin. Exclusions become1,642, review613 and
match units747. Authored exact, source and ownership totals remain unchanged.

The subsequent shared-construction model uses ordinary whole-object28-byte
zeroing and naturally reproduces those optimized derived stores while preserving
the complete effect-loader payload. See FRAME_CONSTRUCTION_CONTEXT_2026_10_31.md.
The earlier20-byte source expression was not unique original-source evidence.
