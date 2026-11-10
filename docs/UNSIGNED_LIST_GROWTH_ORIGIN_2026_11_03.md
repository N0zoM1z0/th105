# Unsigned list growth: generated-code origin

The entire165-byte 0x402700 function is the VC8 `std::list<unsigned>::_Incsize`
implementation with its ordinary count argument, not a new authored function.
Native SHA256:
`0743f70aab2e36a82b3ee5df1e3a2cd5312c75b966f90846b4e1fd7ed7f7c79f`.
It is distinct from the constant-one specialization at 0x40C6D0.

## Independent source and owner evidence

The actual BGM allocation manager release method naturally calls the generated
unsigned-list helper in the existing static-CIL BGM lifetime graph. The source
release method itself is **not** asserted exact. Four already accepted roots in
that actual graph are freshly compared and remain exact. Independently, exact
native handle-manager release 0x405200 (167 bytes) calls 0x402700 at 0x405286;
the full parent hash and actual call are pinned. Another exact game owner also
reaches the helper. These facts support the helper's ownership without claiming
the two source/native parents are the same exact body or adding parent credit.

The complete165-byte helper matches after only named call and verified address
roles are replayed; no instruction bytes are masked. Its aligned EBP frame and
RET4 arise naturally from the genuine linked context. All same-size current
candidate bodies are checked and the full canonical body is unique at 0x402700.

## EH, exception and verification

The complete27-byte handler at 0x6BDFA8, 8-byte cleanup action, 36-byte
FuncInfo and 8-byte unwind map are compared with actual relocation roles. The
length_error ThrowInfo, all three catchable types and descriptors, original
literal and actual RTTI are checked. Full support bodies include both logic_error
constructors and their EH, length_error destructor50/copy25, string destructor38
and the noncontinuable CxxThrowException witness. These are supporting evidence,
not new authored matches. The existing target exception metadata is also used by
other routines; no duplicate credit is awarded.

The scoped origin validator pins the source/COFF closure, four VC8 headers, actual
owner/unit/flags and target; it rebuilds and replays the four existing BGM lifetime
roots before checking this helper. Five pure contract tests and six separate
corrupt-root, native-owner, handler, unwind, ThrowInfo and literal negative controls
reject. No global origin replay or runtime execution of exceptional paths is
claimed.

Only 0x402700 moves review → compiler-generated exclusion. Review292,
excluded2079; exact1426 /443399 bytes, source1637, authored1656, mapped1827,
units814 and candidates4027 are unchanged.
