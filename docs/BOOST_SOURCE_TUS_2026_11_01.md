# Original non-instance Boost.Regex source units

## New source context

The previous verified package contained 184 original headers/license files and
only the original narrow instances.cpp. That did not provide the library's
separate non-template implementation translation units. The pinned official
[Boost.Regex source directory](https://github.com/boostorg/regex/tree/fa1ef1dfd4136803625e49853289ade7c2ddff0a/src)
supplies the new context, without changing version, headers or library bodies.

Six original CPPs were fetched and checked against their immutable Git blobs,
byte sizes and SHA-256: regex.cpp, regex_raw_buffer.cpp, static_mutex.cpp,
w32_regex_traits.cpp, regex_traits_defaults.cpp and cpp_regex_traits.cpp.
The only missing include was the original mem_block_cache.hpp (Git blob
222142dd69cc7bd1b24d95634caaf1de54565dbc), fetched unchanged. The original Boost
license accompanies the separate eight-file package.

config/boost-regex-extra-source-lock.json pins every file. The existing 184-file
lock and its exact reject-extra-files check are unchanged; no new header is
silently placed in that old package. upstream_boost_sources.py verifies the
separate package, rejects altered/missing/unpinned files and escaped paths,
and permits only the named release wrappers with NDEBUG plus their original
include. Builds never fetch. Explicit package fetch/check is available through
that verifier. Native compilation is serial CPU 0/nice10 with the pinned VC8
SP1 /O2 /GS and the established standard release assertion policy.

## Complete canonical results

Four actual original source units now reproduce 15 whole bodies /1,391 bytes:

-Regex core: memory-cache get 163/put86, regex-error injector destructor 87,
 regex_error constructors 39/39, enable_error_info87, clone constructor 177,
 and option validation 194. Total 872.
-Raw storage resize 98 and insert 72. Total 170.
-Static mutex lock 61 and lock constructor 31. Total 92.
-Windows catalog open 69/get154 and typed deleter lookup 34. Total 257.

Every complete formal function section tail equals the entire native candidate,
including all code and absolute relocations. All named call fields, including
repeated lock destruction calls, are resolved. Separate original-source origin
rules recompile and pass full-inventory uniqueness at unchanged 70-percent/
24-byte/zero-alignment-tail thresholds. No instruction masking substitutes for
these complete canonical comparisons. No library implementation, private ABI,
helper export or copied native code is manufactured.

The other CPPs are retained as verified original context, not automatically
credited. lookup_default_collate_name6B4820/455 is a discovery lead with two
real pointer arrays at 6F9840/6F9A48, including base+4 operands. The ordinary
single-value DIR32 mapping intentionally rejects this nonuniform array case.
It remains review pending a separate complete pointer-table contract; no
shortened data pin or address-validation waiver is used.

## Metadata and auxiliary identities

Actual emitted COFF RTTI and native RTTI agree on every new vtable's type name
and primary/secondary offset. Regex-error injector has secondary offset 48;
its clone adds clone_base at 68. The runtime_error base is identified by its
actual 6D5E48 table and native type name. Earlier relocation-masked
logic_error-shaped fingerprints identify common standard-library construction
code, not the unique nominal exception class; the new original regex TU gives
the stronger runtime_error identity for 6A5930/6A59A0.

Those already-excluded107/113-byte runtime_error constructors also compare in
full as auxiliary witnesses. Mutex destructor 6B5EB0/26 and module-deleter
6B55D0/12 fully compare but remain outside this attribution batch; their short
sizes do not bypass the existing generated-origin threshold.

All new IAT names are checked against original PE imports, including
InterlockedCompareExchange/Exchange, Sleep, LoadLibraryA, FreeLibrary and
LoadStringA. The 77-byte option-error literal is source/native identical.
The function-pointer type descriptor name .P6AXPAX@Z agrees in full.
The three root EH handler bindings and two auxiliary handlers pin 16-byte
address prefixes only; no full remote EH equality or extra-byte credit.

## Validation and accounting

New units: boost-regex-source-core, boost-regex-source-raw-buffer,
boost-regex-source-static-mutex and boost-regex-source-w32-traits.
The existing original-header connect main-state unit freshly preserves all
nine configured comparisons, including 827 callable/full856 owned payload.
Nine new source-package tests preserve the old header-only/instance contracts.

All 15 newly classified bodies are third_party/boost_regex/exclude, not authored
game bytes. Excluded 1985/review387/units776; authored exact 1431/443916,
source 1635/authored1655/mapped1820 stay unchanged.

The canonical metadata
witnesses retain actual COFF/native types, import names and original literals.
No full-corpus cold rebuild or push.
