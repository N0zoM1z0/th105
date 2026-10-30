# Exact Ogg opening in the real BGM stream graph

Ogg opening at418A10 is canonical exact291/291, SHA-256
10ce585b835d209c07032de85af1b66516241a5c0af766469c212f7f3cb8c5e2.
The incremental checkpoint is1526 exact functions and433145 authored bytes.
No library bytes, callback bodies, caller bytes or partial matches are added.

## Source ownership and private entry

The real358-byte stream-start body402A00 derives the decoder at stream+30
and calls418A10 at402A1E. Its new ordinary C++ candidate supplies the actual
name, reader, DirectSound buffer, ring, scheduling and linked-stream context.
CIL naturally selects ESI for the Ogg receiver. The previous exported ordinary
member remained293 bytes; the private body now matches every byte without a
register declaration, shim, extra local or padding.

The complete source and target caller CFGs qualify the one actual E8 edge.
The source caller has no unaccounted image relocation. Its own349/native358
body remains nonexact and receives no byte or EH credit.

src/audio/BgmStreamRuntime.cpp contains this coherent provider/caller graph.
OggStreamSource uses the observed reader prefix as a C++ base adapter; this
does not assert the original class spelling or inheritance declaration.
Its1310-byte extent, stream+30 placement and the1378-byte stream are checked.
Unrecovered view constructors/destructors are declarations, not invented
implementations. Other source views and existing matched constructors remain
unchanged.

## Real original codec providers

The link uses the existing archived official Ogg/Vorbis1.0.1 SDK, not stubs
or new imports. Archive SHA-256:
fead50bbdf6a17e695b8b628f4ebe2c64a8f589ca6b983909484f4f361afbfcc.

The exact static-library hashes are:
- vorbisfile: deeda1a326333abf91e9912dd0b65e1e7d7a85070dbd167de720f4f39041575f
- vorbis: f09d5d66d2f943e70964ae1e5449f1f0a4b420a4303db2e04f7b3c092b9d293a
- ogg: f144c78498e6e263edd37e331a09cf1178b2ae945932a44280826f84f072214e

linked_xiph_sdk.py verifies the archive and all three members, extracts only
those providers into ignored build paths and binds their hashes to the link
receipt. Replays reject changed artifacts. This option requires the pinned
static CRT and never uses /FORCE or generated replacement code.

The genuine SDK vorbisfile object also pulls the pinned VC8 stdio initializer
___initstdio from libcmt:_file.obj. Runtime-only static validation admits that
one additional C initializer only for this pinned SDK option. Source/C++
initializers and wrong owners remain rejected. The legacy default is unchanged.

## Complete callback table

The real source OggCallbacks object contains four function pointers and is
emitted by CIL. linked_ogg_callbacks.py verifies its unique ownership, all four
actual callback function symbols, complete16-byte native table at6FA194 and
each existing target anchor, plus exact source HIGHLOW coverage. Source roles
must be distinct and executable. No new target addends or split fake globals
are introduced.

Only four-byte MOV-to-register reads from those specific source slots can be
canonicalized. Writes, address escape and other operand roles are rejected.
The accepted Ogg body performs all four reads before passing the real callback
value to the original ov_open_callbacks provider.

## Remaining source candidates

The three newly implemented game paths are402A00 start358,402C10 update943
and402FC0 handoff806. They own the100000h ring,8000h decode blocks, EOF cursor,
delayed playback, fade state and linked-stream synchronization. Their compiled
candidates are349,925 and761 bytes and are not exact. The source preserves the
observed unchecked API paths and unsigned wrap behavior, rather than adding
new defensive policies.

PCM fill remains251/native252 with the genuine qword time lifetime. SFL metadata
now derives its private path-in-ECX/source-on-stack/RET4 interface naturally
from an ordinary owner method. Its positive ownership guard and scoped floating
environment recover the observed conversions and484-byte body, but the frame
remains110h versus118h. No speculative path-buffer capacity or scratch storage
is added. The original source method-versus-free-function spelling is unknown.
The natural gain provider remains87/native103 in this CIL context.

An ordinary Ob1 control outlined the volume helper but changed other stream
bodies and did not close the target. It is not selected. Split-CIL palette and
read-only package-map/positive-found controls likewise remain private and
receive no credit.

## Verification

Fresh Factory-native IDA preflight at02:30-02:32 UTC checked canonical metadata,
entry, all five mapped byte samples against the raw PE, inventory, disassembly,
decompiler and caller/callee probes. Database bytes and metadata were not edited.
Raw target instructions remain authoritative over decompiler hypotheses.

The selected unit is exact-first-bgm-stream-runtime. Its supporting functions
are intentionally nonexact; select418A10 for acceptance. The former standalone
Ogg/PCM/SFL descriptors and gain descriptor move into this real graph without
duplicating candidate or exact ownership. Existing direct-sound anchors and
the11 accepted file-graph roots are replayed as focused regressions. Default
CI, the focused SDK/callback checks and whitespace checks pass. No cold full
corpus or broad gameplay matrix is run.

```bash
scripts/repo-python scripts/build.py --unit exact-first-bgm-stream-runtime --json
scripts/repo-python scripts/compare-linked-unit.py exact-first-bgm-stream-runtime --address 0x00418A10 --json
```

Private receipts are under build/frontier-bgm-stream-runtime-20261030:
ida-preflight.json, ida-stream-functions.json, formal-build.json,
formal-open.json, the focused regression receipts and ci.log.
SDK archives, generated libraries and analysis artifacts are not committed.
