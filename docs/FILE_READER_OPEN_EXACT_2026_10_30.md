# Exact reader opening through real constructor context

FileReaderOwner::open at 0040CF40 now matches all 213 bytes of the canonical
Japanese v1.06a target, SHA-256
af6ace376e9c519262ef6ca5c5d464f7474e63eb78cac11d5495cbd84f8e1eab.
This adds 213 authored exact bytes; the incremental total is 1522 functions
and 432000 bytes. No partial helper/provider bytes are included.

## Target-backed change

The allocation guards, delayed derived-vptr publication and shared failure
join observed in FILEREADER_OWNER_OPEN_2026_10_19.md are recovered by ordinary
path constructors, not post-construction field assignments. CFileReader's
default constructor initializes the base handle to zero; its path constructor
uses the observed CreateFileA access value 1. CPackageFileReader's path
constructor calls the real archive opener, stores the absolute position and
initializes the XOR key when a handle exists.

The complete package/hash/CRC implementation is now visible in the existing
file/CSV/script CIL graph. This is new evidence relative to the earlier
unresolved-provider constructor controls. No forced inlining, invented
nonthrowing declaration, disabled EH, fake vptr, assembly or inert local is
used. The actual compiler eliminates unnecessary constructor EH naturally.

The provider open_package_file_entry remains an ordinary stdcall function,
as independently observed at the native call. It is a configured public
source root, not a fabricated preserved-thiscall export. Without that real
public boundary, CIL changes its path argument to EAX and the reader caller
is 212 bytes. With it, all 213 caller bytes match. The provider itself remains
nonexact and is not awarded credit. Original TU organization and source
spelling remain unknown.

A full-source ordinary COFF control still retains a package-constructor call;
the original incomplete-provider COFF result is not evidence against the
successful genuine CIL reconstruction.

## Five-slot reader vtable verification

scripts/linked_reader_vtables.py is deliberately limited to CFileReader and
CPackageFileReader. Each explicit contract requires the exact existing
target data key, five native candidate addresses, complete read-only table
bytes and the primary RTTI type. Source tables must be uniquely owned by the
real CIL object, with their actual destructor/read/last-read/seek/size symbols
in the declared order. The inherited last-read method is explicitly the base
method. A sixth executable slot is rejected.

The complete relocatable source table must have exactly five HIGHLOW fields.
The canonical fixed-base executable has stripped relocations, so its entire
20-byte table and candidate addresses are checked directly. Existing generic
one-/two-slot contracts and vptr-store restrictions are unchanged. The new
contract grants no arbitrary address binding and no exactness to method bodies.

## Validation and selection

Only the 12 units actually dependent on FileReader.hpp were rebuilt.
All 31 prior accepted functions remained exact; adding open gives 32 focused
exact results. Two focused verifier tests cover the five-slot contract,
RTTI, slot order, extra slots and missing relocation rejection. Local CI and
whitespace checks pass. There was no cold full-corpus rebuild.

The source is in src/assets/FileReader.hpp and FileReader.cpp. The selected
root is compiled through src/battle/ScriptFileLoading.cpp. The old standalone
reader unit retains its two accessor anchors. The former standalone package
opener descriptor is moved into this real CIL unit without accepting it.
Private evidence lives under build/frontier-reader-constructor-cil-20261030,
including public-compare.json and the two regressions JSON batches.

```bash
scripts/repo-python scripts/build.py --unit exact-first-csv-file-loading --json
scripts/repo-python scripts/compare-linked-unit.py exact-first-csv-file-loading --address 0x0040CF40 --json
```
