# PNG provider version evidence, 2026-11-03

The original Japanese 1.06a executable is SHA-256 `56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`. The game PNG loader passes `1.5.2` at `0x6D6E04` to `0x66FD60`. The native create-read implementation at `0x66CE20` calls `0x66BF00`, whose six-byte body returns the same `1.5.2` address; its version checks compare against that returned string. This establishes the target PNG header-version value, not the full upstream release provenance.

The earlier libpng 1.2.5 origin claim conflated a separate marker: `0x66D037` pushes the string `1.2.5` at `0x6CB0F0`, and `0x66D03D` calls `0x6679C0`, the zlib inflate-initialization wrapper. This identifies the zlib header version passed at that call, not the native PNG release or necessarily the linked zlib binary version. The native PNG island remains excluded as third-party code, but its exact upstream release is not asserted.

The earlier linked comparison build used pinned upstream libpng 1.2.5 and zlib
1.2.3. The linked image contains both version strings, and its libpng provider's
`png_create_read_struct` checks the application minor version. A bounded Wine probe
linked against the exact generated provider archives accepted `1.2.5` and rejected
`1.5.2` as incompatible. The original native version check instead receives and
compares `1.5.2` with `1.5.2`. This proved that the old PNG provider was unsuitable
as-is for a runnable PNG path; it does not invalidate the strict 703-byte
game-function comparison, which rebinds verified call addresses and does not claim
provider or runtime equivalence. No original executable was executed.

A correct runnable provider still requires independent recovery or verification against the original implementation, including ABI and dependency versions. Do not alter the original game literal or patch the provider to conceal the mismatch.

## Replacement provider and bounded smoke test

The linked comparison context now builds official libpng 1.5.2 at commit `dcc3505c7bd0660876fc80110f8e3581900a186a`, with the byte-pinned upstream prebuilt configuration, pinned zlib 1.2.5 headers and the existing zlib 1.2.3 implementation. All fetched source and header files are checked against their official Git blob identifiers and local SHA-256 locks. The generated PNG configuration must match the locked prebuilt bytes. The game's native `1.5.2` argument remains unchanged.

`scripts/audit-png-provider-runtime.sh` rebuilds the actual linked provider archives
and runs a synthetic 1x1 RGB PNG through them under Wine. The provider accepts
`1.5.2`, the width/height/rowbytes/bit-depth/interlace/channels/pixel-depth offsets
match the reconstructed prefix, and BGR output is `56,34,12`. This is a bounded
provider test, not execution of the original game or proof of full target-library
equivalence. All 14 previously accepted roots in the affected CSV/bitmap link and
both replay-codec roots replay exactly; the affected linked CSV deque-copy origin
proof also passes.

## Native source fingerprint

With pinned VC8 `/O2 /GS`, the official 1.5.2 `png_sig_cmp` compiles to the complete 298-byte body at `0x66B870`, including all three security-cookie calls; canonical SHA-256 is `865c431a80fbe894a8370d4df8c124e21296e9bfbeab9c5059b3db850a696dfb` and the source compares 298/298. The same build of the previously used official 1.2.5 source emits 297 bytes and fails at offset 140. This independently corroborates the 1.5.2 choice but does not prove every native PNG routine or the full library. The reproducible provider audit now runs this comparison after its synthetic decode. No authored-byte credit is added for third-party code.

The same official source and compiler configuration also reproduce the complete native IO-pointer getter `0x66BEF0` (13 bytes), create-read wrapper `0x66FD60` (35 bytes, including its verified call target), and BGR setter `0x66FE60` (13 bytes). These small helpers corroborate individual interfaces but do not independently identify a unique upstream release. `scripts/audit-png-provider-runtime.sh` replays all four native source comparisons and the synthetic PNG smoke.

## Recovered zlib header context and native create body

The PNG provider now compiles against official zlib 1.2.5 headers at commit `9712272c78b9d9c93746d9c8e156a3728c65ca72`, matching the native `inflateInit_` version argument, while retaining the zlib 1.2.3 implementation. The two header files and their Git blob/SHA-256 hashes are pinned in `config/png-zlib-header-lock.json` and independently verified for every linked build/comparison. The synthetic 1x1 decode succeeds with this exact mixed configuration.

With libpng 1.5.2 and these headers, the pinned VC8 `/O2 /GS` build reproduces the complete native `png_create_read_struct_2` body at `0x66CE20` (756/756 bytes) and its seven-entry switch table (28/28 bytes) after replaying explicitly enumerated target-role relocations and checking every source/native literal. The native body SHA-256 is `5d1b0245401ddd1f1fdf335139484df87a8cc7dec838549405044e15fa4b106e`; switch table SHA-256 is `5dbb9933a0a2ec5bab767ba8b4766897cad7c4fd2383f54286cbd419611e3f31`. The audit does not claim separately proved equivalence for all mapped callees or the whole library. All 14 accepted CSV/bitmap roots, both replay-codec roots and the affected CSV deque-copy origin rule still replay; no authored bytes are added.

## Native zlib initialization witness

Pinned zlib 1.2.3 `inflate.c`, built with VC8 `/O2 /GS`, reproduces the complete native `inflateInit2_` body at `0x6678F0` (203/203) under explicitly checked allocator/reset target-role bindings. The native `inflateInit_` wrapper at `0x6679C0` also compares 26/26 with its call bound to that body. The canonical body SHA-256 is `3ec7df001cc27cd27f2221da9508f3052ad4b3b90783ed3ae7ec090d43c54333`. This supports the mixed 1.2.5-header/1.2.3-implementation context but does not establish every zlib function or allocator implementation as equivalent. The provider audit replays both bodies and the synthetic decode; no authored-byte credit is added.
