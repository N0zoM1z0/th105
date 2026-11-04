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

The focused score origin rule and the emitted replay-string helper origin proof
were both revalidated. Receipts: `build/frontier-shared-plain-reader-20261104/`.
All 1,030 target-independent CI tests and generated-progress checks passed.
