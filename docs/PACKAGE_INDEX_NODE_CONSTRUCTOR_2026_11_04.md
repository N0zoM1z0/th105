# Package index node constructor

The authored node constructor at `0x0041B7F0` is called twice from the
package-index registration root, once for a temporary and once for a new
collision-chain node. It allocates and copies a path, stores archive index,
size and offset, and clears the next pointer. The existing ordinary C++
constructor in `src/assets/PackageFileIndexNode.cpp` is now tracked.

The pinned native body is 84 bytes and uses a private ESI receiver. The
ordinary C++ method uses ECX and emits 85 bytes. Its first difference is at
+5, so this is not byte-exact; no private ABI is imitated in source and no
exact or EH credit is claimed. The first 84 relocated candidate bytes have
SHA-256 `74bd12c20741b5dbee259129c25f968d1d0fd99eaf633b68ed0c55b1fb8a5e6e`.

The bounded observer tests five valid NUL-terminated paths and varied scalar
values against the native instructions, the candidate and an independent
model, with allocation and `strcpy_s` mocked. It tests a changed next-pointer
initialization as a negative control. Allocation failures, invalid paths,
real CRT behavior and full-game execution are outside this check. See also
`PACKAGE_INDEX_UPDATE_2026_10_19.md` for the larger registration-root scope.
