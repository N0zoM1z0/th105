# Iku sequence exits and compiler duplication witness

This bounded investigation retains the selected Iku root source unchanged.
It adds current-source native coverage and rejects local source changes that
did not recover target sharing. No canonical exact credit is added.

Target is Japanese1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Root620920 `[620920,62EFBE)` is59038 bytes, SHA256
`abc831c6ccd95986bed811694f532ad8c8b92cb49702a7f6ce4de100b8a73dea`.
The wrong-image IDA preflight was rejected; no database was used or changed.
Observations below use the attested PE and fresh private VC8 controls.

## Shared virtual exit

The target's vslot14 CALL626C47 and RET626C50 are reached by actions
416/417/547/562/563/565/566/567/568/603/609/610/660/730/780. This extends the
six-action [effect62 continuation](IKU_EFFECT_SHARED_CONTINUATION_2026_10_17.md):
other callers enter after the effect call. `[626C40,626C51)` is17 bytes,
SHA256 `2c5e21be5284808b35f6536113e9573e0a5df021fefccccc58894c6dfac525c5`.
It loads the actual receiver's vtable, calls slot14 with no stack arguments,
restores the root frame and returns. There is no subsequent actor logic on
these normal target paths. Exceptions/backend behavior remain separate.

The selected candidate instead puts562/563/730 at628F22 with560/561; the
remaining12 target actions share62B4C2. Each of562/563/730 has exactly one
physical vslot14 call in both images. Its source already calls the method
and returns at the appropriate gates; no missing post-call return was found.
The header already uses native C++ virtual declarations, so replacing a
manual vtable-forwarding facade is not an applicable remedy.

A private control names one `advance_sequence_exit` label immediately after
the shared effect call and branches562/563/730 to it. VC8 still emits separate
call/RET tails. Its `[628F1B,628F2C)` and `[62B4BB,62B4CC)` are byte-identical
17-byte sequences, SHA256
`9b42e8e49a496dd805b9b7aa8d40dcbbe9b802307fd2df72cda9d75fc76c927b`.
They contain no relocations or masked bytes. Despite a single C++ continuation,
the target15-action incoming group is not recovered. The private full section
stays59502 bytes; callable span58346 versus selected58347; register CALLs175
and RETs129 remain unchanged. Its canonical section SHA256 is
`08ff79baf561ee85e931b45c6f01acea686fca4d4cf7a018ae2571affae7a6b6`.
This control is unselected. Byte-identical duplicate suffixes demonstrate
compiler output behavior, not original source spelling, a particular internal
compiler pass, or a proof that LTCG is required.

## Steering controls

The target mode-dependent clamp interval `[62DB64,62DC1D)` is unchanged:
mode3/0/other tests the X upper bound inside its branch with limits6/4/5,
then carries both limits in x87 into the shared X-lower/Y-upper/Y-lower work
and face call62DC18. Hash
`750b4c87eda9cdf65581666da076ebbc05f01ce93e0949b7ba9642ddbb90c41b`.
The selected candidate has two face calls after its Y-lower split and five
physical action730 face sites overall, versus four target sites.

After the independently selected effect-sharing change, a renewed branch-local
X-upper/shared-float-bounds control still has five face sites, grows the
section59502 ->59534, and remains nonexact+0x64. A double-carrier control
introduces an unbound eight-byte negative6 literal
`__real@c018000000000000`; the strict replay rejects it as
`relocation.dir32.unknown_symbol`. No placeholder or new literal binding was
added to bypass that failure. Neither control is selected. Earlier
[steering experiments](IKU_STEERING_CLAMPS_2026_10_17.md) retain their older
source scopes. Do not repeat these local rewrites without new evidence.

## Current-source native check

```sh
python3 scripts/compare-unit-object.py gpt-web-iku-action-state build/match-units/GptWeb_IkuActionState.obj --json
python3 scripts/probe-iku-upper-actions.py --sequence-exits --output build/IkuSequenceExitFinalNative.obj
python3 scripts/probe-iku-upper-actions.py --sequence-exits --control sequence-exit-gate
python3 scripts/audit-iku-full-root.py --object build/match-units/GptWeb_IkuActionState.obj --native-object build/IkuSequenceExitFinalNative.obj
```

Comparison and the deliberately wrong control exit1. The1728-case whole-entry
profile passes with zero differences:1224 RETs,384 action-backend entries,
64 object entries and56 actual sequence-backend entries. The latter cover
562/563/730 with12/12/32 cases, respectively;300 target-root instructions.
562/563 vary frame7/8/9, timer, sequence, enable byte, input/resource gate,
facing and PC53/PC64. 730 varies sequence4/5/6, time58/59/60/61, timer,
frame, facing and both control words. All helpers and the root prelude execute
genuine target instructions, without forced returns or replacement callbacks.
Both roots stop at the first actual backend or normal RET. The shared sequence
method's execution/return is outside the native scope; its following normal
root return is static control-flow evidence.

The `sequence-exit-gate` control changes730's `time >= 60` to `time > 60`
and detects16/1728 differences, all730 at input time60. Input SHA256:
`0cf8c92b28e9885824852ab5fe0f8f0e2fbc39a2e1db264234f0604014644da4`;
target output SHA256:
`a6b8aaee31fc0dc0b3d0fe3495e377f86347593943cc5085efb0fa61e1d73b19`.

Selected source CRLF SHA256 remains
`69c43bf58dcfbeee08866a93b007fa266718a37c7850b79609056b3920fa864b`;
full59502-byte canonical section remains
`dac7642939ffc375a5fc6095057722c35a47ebc7112faf978e9bdfcfd3b3f751`.
Fresh native/configured sections normalize identically. Strict whole59038
still differs at+0x64/620984. The preceding selected-source instruction,
call, home and owner diagnostics remain unchanged; no aggregate replay was
run. Reports are `build/iku-sequence-exit-final-{compare,native,control,facts}.json`.
Small private control patches remain under `.analysis/iku-730-face-20261017/`;
superseded full copies/objects are removed. Original C++/TU/inheritance and
compiler-phase provenance, payload-value equivalence, post-backend behavior
and exceptional timing remain unknown. Further work must recover joint
argument/control lifetimes or justified compilation context rather than
assuming a source label guarantees a unique machine tail.
