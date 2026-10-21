# Ogg PCM count and value lifetimes

`fill_ogg_pcm_block @418B70` has corrected source facts and remains nonexact:
the complete selected body is **251/252**, first difference **418B70/+0**.
No exact, origin or aggregate progress is added. The older255-byte/default-FP
source was an incomplete hypothesis despite its earlier semantic-closure prose.

## Target observations

The canonical Japanese 1.06a SHA256 is
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
IDA attestation still fails; these facts come from raw PE instructions.
The complete252-byte target decodes to91 instructions, five calls, and two
RET8 exits at418C45/418C69. All direct internal edges stay inside the body;
INT3 padding starts at418C6C. Both caller instructions402CDC/40319A freshly
resolve to418B70. Existing Xiph callee provenance and game-audio ownership
classification are unchanged.

Three source properties are corrected:

- There is no initializer for the bitstream out-parameter. The bitstream argument
  passes the actual local slot; the old source added a zero write.
- Remaining count is unsigned. Target418B90 uses JB after subtracting the
  unsigned total from8000h and comparing against1000h. The callee retains its
  actual int length parameter; the clamped argument fits that width.
- The zero-read branch precedes the nonzero-read loop-boundary branch. Both
  paths still call ov_time_tell before deciding whether to seek or finish.

The target stores ov_time_tell's ST0 result as a qword at418BB5 before either
branch. Default FP retained extended x87 state in the old source. Strict FP
with exceptions off reproduces the real double current_time boundary and the
target's zero/comparison shapes. This is a value-lifetime correction, without
a claim about which overprecision states the actual SDK can return or an
end-to-end numerical regression result.

The source retains the actual loop policy: a zero read ends only when loop_end
is ordered equal to zero, otherwise seeks to zero. A nonzero read may seek to
current_time-loop_end+loop_start. Read counts accumulate as unsigned values;
8000h completes the block, and a short ending zero-fills its remaining suffix.
No additional error policy is invented. File+10 and loop qwords+12E8/+12F0 now
have compile-time offset guards in this one source file.

## Compiler limits and reproduction

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py --unit gpt-web-ogg-pcm-runtime --compare --json
python3 scripts/validate-tracking.py --require-target
```

The focused build intentionally exits1 for the complete nonexact comparison.
Its VC8 SP1 O2/GS-off profile now selects strict FP, with local exception
scheduling off. Only this unit's source/profile changes. Shared headers,
runtime declarations, callee bindings and accepted units remain unchanged.
No unrelated or aggregate replay was needed.

The target uses a12-byte ESP frame and retains EBP as its destination pointer.
The candidate naturally aligns a real EBP frame to64 bytes and assigns that
pointer differently. Size-oriented O1/Os controls remove alignment but change
the register/call/branch arrangement. Zp4 retains the aligned candidate;
turning speed optimization off likewise fails to recover the target. These
controls are unselected. No fake local, artificial alignment or size-only
acceptance is introduced. Frame/TU provenance remains open.

| Selected artifact | SHA256 |
| --- | --- |
|CPP|`6b3c7a7ae79c627b21d28ecbd0b69c8029fc85e84858059da42281901dd194cc`|
|Formal COFF|`a53fdd024ea52861d55c9603456fb6e98471bb133962ca6e6decb3a140b91b4e`|
|Canonical source251|`aca14b4149974f7233630bf995e74666401f62e50023398ac2f06676dfd84089`|
|Target252|`0dc9e4a97d421f4a70c85adc63d05400cd89dd4d910cef847f80771eb0439d0d`|

Private target/caller packets, baseline, compiler controls and formal comparison
reside in `build/ogg-pcm-values-20261021/`. `selected.cpp` and `selected.obj`
preserve the tested epoch independently of later match-unit builds. Rejected
controls may be restored from their SHA-checked gzip receipts. The preceding
[CNumber frame audit](NUMBER_FRAME_AUDIT_2026_10_21.md) uses the Ogg source
pinned before this correction; its recipe now names that commit explicitly.
