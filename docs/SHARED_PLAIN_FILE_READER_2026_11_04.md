# Shared plain file-reader lifetime

The score loader and two replay operations now use the same `PlainFileReader`
source type rather than duplicate 12-byte polymorphic file-reader definitions.
Its actual CreateFile/ReadFile/CloseHandle, seek and size behavior is unchanged;
the emitted vtable is bound to the already attested native CFileReader vtable.
The shared type name is a reconstruction label, not a claim of original spelling.

The replay header reader remains 313/313 exact, including the separate complete
48-byte cleanup/handler and 44-byte unwind/FuncInfo audit. The replay filename
builder and pattern function remain 1322/1322 and 1323/1323 exact. The score
loader's entire 1,672-byte candidate hash is unchanged and still differs from
target in seven SIB bytes; all four previously bounded call-observer cases still
agree. These cases do not execute real file I/O, decompression or OS exception
unwinding. No new exact functions or bytes are credited.

The focused score origin rule and the emitted replay-string helper origin proof were
both revalidated. All 1,030 target-independent CI tests and generated-progress
checks passed.

## Configuration reader's missing size implementation, 2026-11-09

`GameConfigFileReaderView::size()` incorrectly returned zero. The configuration
loader never invokes that slot, so its accepted 953-byte root did not expose
the incomplete local implementation. The source now calls `GetFileSize(file, 0)`.
The local declaration is otherwise unchanged; this is a provider correction,
not another class-identity merge.

The original five-entry table at `0x6C0F34` points to deleting destructor
`0x41B890`, read `0x40CED0`, last-read size `0x407C40`, seek `0x407C50`, and
size `0x40CF00`. The last body loads the handle at receiver +4 and calls the
PE-identified KERNEL32 `GetFileSize` import at `0x6C0070` with a null high-size
pointer. Its complete 13-byte SHA-256 is
`fd439230f3d19604cc39c3448d3adbdef22f5cb9d7d5bded13ed9c5d82c5bb7c`.

The revised local size body matches all 13 bytes, including its IAT relocation;
the old body was only `XOR EAX,EAX; RET`. All five locally emitted virtual
providers now match their complete native bodies (45/35/4/25/13 bytes), and the
20-byte table matches after binding those verified providers. The deleting
slot uses VC8's weak vector-deleting symbol alias to the emitted scalar-deleting
body. The local nominal RTTI is not claimed to reproduce CFileReader RTTI.

The only source-dependent unit is `gpt-web-game-config-load`. Its whole root remains
953/953; all 180 other non-debug COFF sections retain their bytes and relocation
roles, including EH and RTTI. No source pins or exact ledgers change: these native
providers already have established ownership and exact records. Tracking and the
current lightweight CI pass.
