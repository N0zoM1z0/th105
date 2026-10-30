# Exact SFL loop metadata loading

Native418D10 is canonical exact484/484, SHA-256
3cdccc342d52b6da45d522a9c4cb3e4f9e9e74229910987c36e12fab4e3d6d8a.
The incremental ledger is1527 exact functions /433629 authored bytes.
No partial caller, library, numeric data or extra EH bytes are credited.

## Target-backed source closure

The real Ogg open418A10 calls the ordinary OggStreamSource method at418B25.
CIL naturally derives path in ECX, receiver on the stack and RET4. The parent
is freshly replayed exact291/291 in the same linked image before accepting
this private edge. The outer stream-start body remains nonexact349/358.

Existing positive ownership/count guards and precise FP environment already
matched the complete484-byte instruction sequence except frame-relative
operands. Enabling floating-point exceptions inside this method's existing
scoped precise/fenv region recovers the native118h frame and both cookies.
This preserves exception-sensitive evaluation of the unsigned cue conversions.
The path buffer remains char[260], with a260-byte strcpy_s bound. No padding,
inert local, forced register declaration or guessed stack allocation is added.
This does not identify the original source spelling or compiler command line.

The actual public normal FileReaderOwner destructor is retained as a source
export. Its cleanup call uses the native ECX receiver rather than a private
EAX variant. No generated destructor wrapper or alias is substituted.

## Complete strict replay

The ordinary full-byte comparison also validates:
- cleanup handler6BDD5B,46 bytes, including both cookie checks;
- cleanup funclet6BDD50,11 bytes, targeting normal destructor40CF20;
- FuncInfo6E43BC,36 bytes;
- unwind map6E43B4,8 bytes.

Four full-width x87 reads use the compiler-emitted readonly2^32 qword at
native6D6ED0. Its complete IEEE bytes000000000000f041 agree with the unique
CIL-owned __real@41f0000000000000 symbol. The literal is not externally
rebound or rewritten. Stores, narrow/interior reads and address escapes fail.

Reproduction:

    scripts/repo-python scripts/build.py --unit exact-first-bgm-stream-runtime --json
    scripts/repo-python scripts/compare-linked-unit.py exact-first-bgm-stream-runtime --address 0x00418A10 --address 0x00418D10 --json

Initial formal receipt: build/frontier-sfl-fp-except-20261030/public-compare.json.
Focused final receipts use the same directory. The mixed unit's other roots
remain unaccepted; do not interpret their source coverage as exactness.

Final focused replay freshly builds only the two affected/context units:
Ogg + SFL2/2 and the existing reader/script/bitmap/palette file graph11/11
are exact. Receipts: exact-first-bgm-stream-runtime-final.json and
exact-first-csv-file-loading-final.json in the evidence directory above.
The default-empty numeric contract and prior public-member consumers retain
their exact output. Target-independent CI passes142 tests; whitespace is clean.
No full-corpus cold rebuild was run.
