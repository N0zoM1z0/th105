# Isolated original VC8 patched runtime provenance

## Evidence that the previous runtime is not sufficient

The existing SHA-pinned SP1 runtime remains the default build/link reference.
A fresh full-inventory search of 1,823 eligible original archive fingerprints
found no additional review matches. Native write_nolock at 69AFAF is 1,570
bytes, versus 1,478 in that archive. Native write at 69B5D1 is 220 bytes,
like the old archive, but three non-relocated instruction bytes differ:
native SHL ESI,6 indexes a 64-byte ioinfo; old IMUL ESI,ESI,56 indexes 56 bytes.
This is a concrete runtime-layout difference, not a reason to coerce game
register allocation or alter matching thresholds.

The original Microsoft KB971090 runtime resolves these two complete shapes
and twelve more reviewed bodies. It is a compatible runtime reference, not
proof that every object in the shipped executable used the same patch release.

## Official package and extraction

Official download page:
https://www.microsoft.com/en-us/download/details.aspx?id=25287

Official package:
https://download.microsoft.com/download/D/2/3/D23F9F62-3DEE-4EC0-B3B9-D64E9F573D1F/VS80sp1-KB971090-X86-INTL.exe

The package was downloaded directly over HTTPS and only read as archive data.
No installer, filehashfixup executable, MSI action, or vendor executable ran.
No active compiler, headers, library directory, system setting, or build profile
was replaced. Extracted vendor material remains ignored and is not committed.

Pinned identities:

- EXE: 261,194,672 bytes, SHA-256
  38494dccecaa3fec1fd7b1cd9b93df5f77bee7305971513364e8fcf9339d3618.
- MSP member: 296,257,024 bytes, SHA-256
  64826db38c375cca7c890a72bee993e01a69072e76146b947b5993f7cf6b3d65.
- Cabinet stream: 246,055,772 bytes, SHA-256
  f9b898274082a2f907cb6382370c82b2d0442cdc2b4517436eed9d1c6a935991.
- libcmt.lib: 7,705,590 bytes, SHA-256
  cbc9a9f5f706aa63deda800a01386dd0b46c121f60bb7ea28bd74e5d9399c581.
- libcpmt.lib: 4,983,946 bytes, SHA-256
  fe8597decade589a232c45aed8c52d939d9a26f64069cfccb3a77caf9abe4138.

The exact cabinet member names, original sizes and hashes are encoded in
scripts/upstream_vc8_runtime.py. Optional explicit acquisition uses libarchive-c,
olefile and system libarchive; offline verification uses only the standard
library. Dependencies must already be available; the script does not install
them. Extraction stops after both verified library members, avoiding unrelated
later cabinet data. A first exploratory all-member traversal encountered an
LZX error after the two selected libraries; fresh bounded extraction and the
public bootstrap replay independently reproduced both original hashes.

    scripts/repo-python scripts/upstream_vc8_runtime.py --fetch
    scripts/repo-python scripts/upstream_vc8_runtime.py

Fetch is explicit and missing-only, with size/hash verification before atomic
publication. Existing altered files are never silently replaced. All paths
resolve within the repository. Native origin verification never downloads.
A fresh public-script bootstrap replay from verified cached original package
files reproduced both archives without executing the package.

## Accepted library scope

Fourteen complete inventory bodies / 4,876 bytes are classified vc8_runtime:

- 68CF0A fprintf, 335.
- 68D05F initstdio, 177.
- 691F43 isindst_nolock, 470.
- 692A36 flsbuf, 352.
- 699DF6 filbuf, 288.
- 69A827 close_nolock, 151.
- 69ADFB free_osfhnd, 129.
- 69AE7C get_osfhandle, 113.
- 69AFAF write_nolock, 1,570.
- 69B5D1 write, 220.
- 69D071 lseeki64_nolock, 131.
- 69D251 isatty, 94.
- 69D2AF fputwc_nolock, 478.
- 69FD9C flswbuf, 368.

The patched inventory scan found 16 source patterns but only 14 physical
functions. The 220-byte locking/lseek/write wrappers share a relocation-masked
shape. Native 69B5D1 calls the independently matching write_nolock at 69AFAF,
so its selected original member is write.obj, not an arbitrary first hit.
All candidate sizes come from complete original COFF function extents; no
prefix or partial match is accepted.

config/vc8-kb971090-runtime-origin-anchors.toml explicitly selects the isolated
archive set. Each full native body hash, current name, complete inventory hit
set and every COFF relocation operand target is pinned. Minimum non-relocated
coverage is 0.70 and minimum invariant bytes 31. No threshold was weakened.
The validator separately checks full extent, SHA-pinned archives, relocation
kind/site validity, operand target readback and full-inventory uniqueness.
This is original-library provenance evidence, not new authored exact credit.

The existing extractor defaults to unchanged vc8-sp1. Only explicit
--archive-set vc8-kb971090 selects the new reference, and it rejects a
toolchain-root override for that isolated set. The default SP1 locale cleanup
and shift rule was also freshly validated (two bodies) after the selector change.
No blanket native census rebuild or all-unit replay was performed.

Totals: exact authored 1,553 functions / 441,679 bytes; source 1,750;
authored ownership 1,770; exclusions 1,628; review 629; match units 744.

Default target-independent CI passes 171 tests. New regression cases cover the
unchanged default and explicit selection, source bytes before publication,
same-length hash tampering, incomplete/excess downloads, and escaped paths.
Generated progress and git diff --check pass.

## Follow-up: relocation-resolved short and data-heavy bodies

A separate scope classifies 11 further complete library bodies / 655 bytes:

- type_info equality 689919 / 27, calling the existing strcmp at 68E650.
- std::exception constructor 689F0B / 17, destructor 689FDA / 22,
  and what 689FF0 / 13. The actual vtable 6CD24C, locator 6DBE88,
  its type descriptor and .?AVexception@std@@ name are pinned by DWORD readback.
  The fallback string at 6CD254 is verified as Unknown exception plus NUL;
  the destructor calls the existing free at 68C686.
- exit 68E3F5 / 17, with its doexit destination 68E313 pinned.
- fdivp_sti_st 697476 / 19, fdivrp_sti_st 697489 / 19,
  safe_fdiv 69769C / 21 and safe_fdivr 6976B1 / 21. These original complete
  archive functions have no relocations: every body byte is identical.
- unlock_fhandle 69AF8D / 34. Its pioinfo base 7038C0 agrees with the independently
  matched write paths; its LeaveCriticalSection IAT cell is 6C0104.
- crtMessageBoxA 69C244 / 445. Full original shape has 305 invariant bytes;
  every relocation is pinned, and destination contents include USER32.DLL,
  MessageBoxA and GetUserObjectInformationA, plus the three other named APIs.
  Thus the byte-similar W implementation is not selected by an arbitrary name.

The separate manifest uses coverage 0.60 / minimum 9 invariant bytes, with all
relocation operands and the additional actual RTTI/string contents above fixed.
This is the established short-runtime evidence mechanism (the existing security
cookie rule uses 0.45 / 7), not a relaxation of the 14-body 0.70 / 31 rule.
Each selected fingerprint remains unique across the complete inventory.
The broad diagnostic also found generic deleting destructors, copy constructors
and other ambiguous shapes; those are deliberately not selected.

The new rule passed the existing native validator. Only new-rule evidence is
materialized; unchanged proofs are retained. Final exclusions 1,639, review 618;
authored/source/exact counts and all match units remain unchanged.
