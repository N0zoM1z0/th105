# Complete DirectSound stop wrapper, 004185E0

The existing ordinary C++ BgmBufferRuntime::stop_if_playing body now has a
formal complete match:45 bytes, SHA256
72c8a2e9e9f0c7d72d27ef4bbb49b216e041b1d7f0942cad5d98df50136d06d9.
No authored source was rewritten. VC8 LTCG naturally gives this private member
its observed ESI receiver; no private-register declaration or ABI directive is
introduced. Only this45-byte whole function adds authored exact credit.

## Native boundary and application ownership

Pinned original Japanese1.06a remains the target. All22 instructions in
[4185E0,41860D) are reachable; two RET0 exits close the body. Resource04 is
checked before use. The actual COM GetStatus slot24 writes a local DWORD;
status bit1 gates the actual Stop slot48 call. The function returns that
HRESULT when called, or0 otherwise. Source preserves the original uninitialized
status local before GetStatus rather than adding a defensive value or guard.
This application policy wrapper is not a generated STL/runtime function.

A raw whole-text call inventory, qualified by complete owning-function decode,
finds one direct caller: BgmStream update402C10 at402C85. Native LEA
ESI,[EDI+24] at402C82 supplies the stream's actual buffer member. The existing
BgmStreamRuntime.cpp source implements the same member and call; its fresh
compiler-produced caller has the identical adjacent subobject LEA and naturally
uses the same private ESI convention in the leaf.

Discovery inspected37 existing configured linked DLL/MAP pairs whose artifact
hashes agree with retained build records. A relocation-masked comparison found
other leads, but4185E0 has no masked bytes and already matched all45 raw bytes.
That cached finding was not acceptance. All other discovery hits remain leads
requiring fresh source/tool provenance, complete boundaries and canonical proof.

## Independent relocation-free member proof

The previous source_only_caller path supports only its existing constructor/
stdcall-plus-EH scope. A formal attempt using that flag for this member failed,
and the rejected flag is not used. Its validation remains unchanged.

The new separate linked_member_leaf proof accepts only an ordinary nonvirtual
no-argument HRESULT member through one distinct configured exported source
caller. It requires all of the following, in addition to the existing pinned
compiler/source/dependency/image/MAP provenance and actual direct-edge checks:

- The entire source member equals the entire tracked native extent as raw
  bytes, before canonicalization, without any relocation or byte masking.
- Both complete instruction graphs close through RET0. External tails and
  direct external calls are rejected. No alignment/remote-EH waiver is allowed.
- Canonicalization must be an identity with no call or data-reference records,
  including otherwise attested absolute immediates.
- The leaf has no PE HIGHLOW relocation, absolute/segmented data reference or
  rewritten instance register. Its observed instance register is actually read.
- Both actual callers immediately supply the same aligned subobject using the
  same nonvolatile receiver/owner registers and offset. Missing, indexed,
  unaligned, changed, aliased or exported leaf entries fail closed.
- Every source-caller address role is independently qualified under the
  existing data-role machinery. Caller bytes and execution are not declared equal.

This proof describes compiler output, not a source-level private ABI. The
ordinary update method is exported only as a comparison root. Native update
enters with EDI while this exported comparison starts with ECX and copies it
into EDI; that parent remains nonexact. The leaf remains unexported. No native
export, caller equivalence or original nominal class/TU uniqueness is asserted.
Fifteen tests cover the positive contract and negative byte/extent, relocation,
ABI, entry alias/export, subobject, branch-bypass, partial/full receiver-write,
return and caller cases.
They also verify that the old source_only_caller rejection still applies.
The new proof module is included in the conservative build-input digest.

## Fresh complete unit and related acceptance

The configured exact-first-bgm-stream-runtime unit is rebuilt normally with
real source, pinned CRT/Xiph providers and unchanged compiler options. Its
Ogg open418A10/291 and SFL loader418D10/484 remain canonical exact. All eight
configured functions now return comparisons rather than an unbound-call error:
start349/358, handoff761/806, PCM251/252, gain87/103 and exported update969/943
remain nonexact. A mixed-unit comparison_failed status is therefore expected;
it is not reported as an aggregate exact pass.

The whole-call bindings for already observed clear418610, stack-probe, PCM,
volume and memory-copy edges are explicit. Native403100 independently reads
readonly double32768 at6D6EC8; its full8-byte literal is added for the existing
numeric-literal gate. Existing float/double2^32 literals are qualified in the
same way. No game code address is represented as data and no neighboring
callee gains credit from those bindings.

Reproduction:

    taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py --unit exact-first-bgm-stream-runtime --compare --json
    scripts/repo-python scripts/compare-linked-unit.py exact-first-bgm-stream-runtime --address 0x004185E0 --address 0x00418A10 --address 0x00418D10 --json
    scripts/repo-python -m unittest discover -s tests -p test_linked_member_leaf.py

No generated DLL was executed.
Only focused affected comparisons are required; no whole-corpus cold rebuild.
Totals: exact1583/449354 authored bytes, source1783, authored1803, mapped1810,
excluded1792, review432 and units765. No push.
