# Pixel and SFL array-storage lifetimes

This follows the script/file-buffer ownership correction without changing the
original game behavior or claiming additional exact functions.

## Typed local arrays

SFL metadata data (unsigned char[]), BMP file_data (unsigned char[]),
palette16 (unsigned short[]) and palette32 (unsigned int[]) now use delete[]
with their actual source element type. Their original allocations already use
new[]. Existing conditions, palette mutual exclusion, release order and
exception behavior are retained. No RAII recovery path or leak repair is
invented where the target has none.

## Type-erased pixel storage

CBitmapData::buffer_1c is a byte-pointer view of storage that may be produced
as byte, word or dword arrays. Blindly changing its old free call to a typed
delete[] expression would assume an element type not shared by all producers.

The current pinned VC8/native evidence instead supports the actual untyped
array-storage deallocation function. The normal destructor and all three
load_from_file replacement paths now call ::operator delete[] on the saved
allocation base. Only trivially destructible primitive pixel types are involved;
no element-destructor sequence or cookie offset is invented.

Raw allocation evidence includes BMP sites41A4AB,41A624,41A794, descriptor-copy
sites41ABFA,41AC29,41AC62 and PNG sites41AA91,41AAE8,41AAFD. They call the array
allocation entry665B8A and retain the returned base for their output buffers.
For example,41A4BA/41A633/41A7A1 and41AC02 publish the unchanged returned base.
The existing size/format branches determine storage bytes, not a hidden
nontrivial array element lifetime. This is the pinned VC8 storage model, not
an assertion about array-cookie layout on arbitrary compilers.

The scalar deleting destructor independently separates the two allocation
families: 419FB1 calls array delete68AA26 for buffer_1c; 419FC1 calls scalar
delete6898EA for the owning object. Normal destructor419FD0 follows the same
array-storage path. Source retains that distinction rather than mapping every
deallocation to one runtime name.

## Focused checks and boundaries

Five function-scoped callee bindings now name the actual array-delete symbol:
BMP parsing, normal/scalar bitmap destruction, raw bitmap-file loading and SFL
metadata. No runtime/compiler files or global symbol mapping were replaced.

Dependency discovery identifies exactly three affected units. Fresh canonical
replay preserves all19 previously accepted functions:
- gpt-web-cbitmap-data-runtime: five accepted constructor/destructor/copy/callback bodies.
- exact-first-csv-file-loading: twelve accepted reader/script/texture bodies.
- exact-first-bgm-stream-runtime: two accepted Ogg/SFL bodies.

The selected cleanup-EH packets in the linked comparisons remain exact.
BMP419FF0 remains nonexact: source section2181, first difference+16 from
frame438h versus native430h. The correction is not permission to alter frame
size, add padding, force registers or promote the BMP source.

Evidence is retained under build/frontier-local-array-lifetimes-20261031,
including bitmap-storage-formal.json, csv-storage-accepted.json and
bgm-accepted.json. No full-corpus rebuild or game execution is claimed.
Authored exact, source/ownership census and unit counts are unchanged.
