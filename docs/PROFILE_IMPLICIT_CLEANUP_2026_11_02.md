# Profile member cleanup: compiler ownership correction, 2026-11-02

## Outcome

The 205-byte profile-data destructor at 0x42D320 remains completely canonical,
but is removed from authored game-source acceptance. A real existing caller
naturally emits it as an implicit C++ member destructor. Exactness is preserved;
its accounting category is corrected, with no new helper or caller byte credit.

Pinned Japanese v1.06a SHA-256:
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.

## Natural source witness

ScoreDefaults.cpp already constructs a real ProfileMenuBaseDataLifetime defaults
local and uses it for score initialization. The control removes only the empty
explicit destructor definition and declaration. It adds no destructor body,
probe object, forced emission, barrier, noinline attribute, assembly or bytes.

Before removal, that actual caller TU does not emit the destructor. Afterward,
VC8 emits one complete 205-byte destructor COMDAT. The original ScoreDefaults
parent stays exactly 2428 bytes, SHA-256
edf6201796372e2afccac1e7d42589bf8c3a5c6014a4f35490b9c3f2b004ccc5.
Its source EH code (112 bytes) and metadata (84 bytes) also retain raw bytes and
symbolic relocations; this is a before/after preservation check, not a new claim
of full native parent-EH qualification.

The observed native calls are:
- 0x42EDBD calls the existing profile constructor at 0x42D260.
- 0x42F6C3 calls the cleanup at 0x42D320.
Both match the real source-local lifetime. The exact parent and source-reviewed
member layout supply ownership, not an artificial object created for a test.

Cleanup SHA-256:
8880bb1d3c7e6a2d2a2765acb29fcfef74f36bec02636d1362acc7557b3c19a4.
Its whole emitted extent and native RET boundary agree, followed by three INT3
bytes. Full relocation-aware comparison against same-sized inventory candidates
selects only 0x42D320. Its own complete EH code 80 and metadata 68 bytes also
match the native records. String and input cleanup dependencies remain qualified.
No unique original source spelling or declaration syntax is inferred: the
counted instructions are ordinary compiler member cleanup, not bespoke game logic.

## Durable accounting and verification

The selector moves from gpt-web-profile-menu-base-data-lifetime to the existing
exact-first-score-defaults unit. The empty source destructor is removed. New
profile-base-cleanup-origin-anchors.toml pins the actual owner/declarations and
whole body, and rule implicit-profile-base-cleanup-106a records one compiler
exclusion with the native incoming edge. Existing comparison thresholds remain
unchanged. The Replay source-review hash is renewed for the changed header.

Only the 0x42D320 origin/function rows, its authored implementation entry and
its authored match entry change; unrelated classifications are retained.
Four accepted roots in the three-unit actual include closure remain exact.
The new 1 / 205 origin proof and existing Replay 2 / 32 proof pass. Wrong native
body hash, wrong incoming instruction, partial extent and changed reviewed source
are all rejected. The nine implicit-lifetime and twelve Replay validator tests
pass. Generated progress is refreshed. Final CI passed 962 tests (105.437
seconds), tracking, generated progress and whitespace. After the client timeout,
the zero exit marker and full terminal log confirmed success without a repeat
run. Both working-tree and staged diff checks passed.

New totals:
- Exact authored: 1426 functions / 443399 bytes, down exactly 1 / 205.
- Source-present: 1636; authored: 1655; excluded: 2075.
- Mapped: 1826; review: 297; units: 813; candidates: 4027, unchanged.

No target, compiler artifact or private report is committed.
