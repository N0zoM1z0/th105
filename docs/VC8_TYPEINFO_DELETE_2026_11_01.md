# Original type_info deleting destructor

6898FD/28 now compares completely and uniquely against the actual original
libcmt:typinfo.obj scalar deleting destructor. The original archive body and
freshly linked original-library body both canonically equal the native body.
Only28 runtime bytes are newly classified, never authored destructor credit.

The root calls actual normal type_info destructor6898EF and operator-delete
tail6898EA. The existing full14-byte normal destructor, complete RTTI and
112-byte cleanup/SEH/BSS-root proof freshly pass. The operator-delete tail's
whole five bytes also match and lead to the independently owned _free68C686.
No provider gets additional function-byte credit.

## Resolve the actual weak symbol, do not assume aliasing

The source vtable slot refers to the vector-deleting symbol. In typinfo.obj
that name is an actual weak external with search-library characteristic2 and
a scalar-deleting fallback. This is not an unconditional alias declaration.
The unchanged genuine original seven-TU graph is freshly rebuilt, and its
final MAP resolves both decorated names to the same28-byte body. The source
vtable slot points there; the corresponding native type_info slot points to
6898FD. Both source names, owners, full root bodies and named calls are checked.
One physical native body counts once.

The original formal unit now contains the normal14 and deleting28 roots. The
normal gate retains its own complete contract while permitting the separately
proved deleting function in the same original member. No original source,
header, compiler flag, graph export or generic threshold is changed.

Seven focused tests reject altered archive/member/class, missing normal support,
wrong delete target, prefix/masked bodies and duplicate alias credit. All45 real
corruption controls fail across every new root byte, the delete stub, native vslot
and selected complete-support boundaries. The narrow origin rule passes before the
single review row changes.
