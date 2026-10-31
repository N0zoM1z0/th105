# BGM service: complete global lifetime

Original Japanese TH105 v1.06a SHA-256:
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.

Two whole authored bodies are canonical exact:

- Constructor4032F0:199/199, SHA-256
  b240ba80b25ac537af4146ce78e86e16cc10e18cb49202583612204ac75b6fac.
- Destructor4033C0:148/148, SHA-256
  5aad3363707f068c9792486d3545690831f31c05f029ed336adbd4c4a69523dd.

The constructor additionally passes all180 cleanup/EH bytes: handler27,
funclets8/11/11/11/14/14, FuncInfo36 and unwind map48. The destructor passes
all117: handler27, funclets8/11/11, FuncInfo36 and unwind map24. Its actual
handlers are6BE505 and6BDA6E, with FuncInfo6E4D1C and6E4090 respectively.
No EH/helper bytes receive authored credit.

## Actual ownership and startup

Source BgmServiceLifetime.cpp owns two separate eight-byte thread members at
00/08, event pointers10/14, running flag18, critical wrapper1C, actual
BgmAllocationManager50 at38, three lists88/94/A0, and gainsAC/B0. The constructor
clears the events and running flag after member construction. The destructor
performs ordinary reverse member teardown, with no extra shutdown or event
closing absent from the target. Separate initialize403460 sets the gains.

The source-owned global at7026E0 has natural member extentB4. This does not
claim the four-byte gap before the next global as an original explicit member.
Its17-byte initializer6BE710, real CRT slot6C0360, atexit68AF1E and five-byte
exit callback6BEDD0 are independently replayed in every accepted receipt.

Ordinary C++ lifetimes select the native private entry conventions. Real
unsigned-vector COFF remains linked; unsigned-list CIL naturally gives the
outer list's ESI cleanup and receiver-free node allocator. The initial full
unsigned-list COFF control produced214/146 instead of199/148 and was rejected.
Native EH calls list destructor404080, while the ordinary destructor body
calls its cleanup408A00. Their actual separate source symbols are bound, not
collapsed into an invented alias.

Manager default construction now initializes the observed generation30 to
zero. Its body in this context is126/native133, so it is not accepted or given
independent exact credit. Outer queue element spelling remains a reproducing
four-byte handle representation, not proof of the original nominal C++ type.

## Exact extent versus section alignment

The genuine VC8 native layout COFF places the sole180-byte zero object in an
eight-aligned BSS section. Section alignment constrains the beginning address,
not the length. The verifier previously incorrectly required length to be a
multiple of section alignment. It now preserves the exact observed section
length, still requires four-byte member extent, a unique strong offset-zero
symbol, zero uninitialized storage, no peers or relocations, and only the
previously permitted4/8 alignments. Both source and target start alignment
remain mandatory. No rounding, synthetic padding or extra owned bytes occurs.
Tests retain rejection of unsupported flags and add180-byte/eight-aligned
coverage, rejecting176/184 substituted extents and179-byte unaligned extent.

## Focused validation

Public exact-first-bgm-service-lifetime passes both roots. Existing affected
BGM stream220, spatial139, reader15, manager279, scalar30 and stream ctor89
remain exact. Existing wave-service143/128 and member constructors193/145,
and package global constructor/destructor also freshly pass. Lifecycle tests
pass, followed by the default CI gate. No cold whole-repository replay.

Only two functions add347 authored bytes:1571 exact /447379 bytes;
source1767, authored1787, mapped1794, excluded1658, review582, units755.
Receipts and rejected control logs are under
build/frontier-bgm-service-lifetime-20261031/.
