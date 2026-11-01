# Original type_info destructor and complete cleanup support

6898EF/14 is now whole canonical and inventory-unique from actual pinned
libcmt:typinfo.obj. The original root stores the type_info vtable6CD238 and
calls the actual _Type_info_dtor at68E5D6. Complete source RTTI checks7 records
covering6 unique regions, including the self-referential class identity.
Only14 runtime code bytes are newly classified.

Archive SHA256:
3bc6c5b90f8507964839fd0264d8565c3b766d01f9efcad336532a11e8f06ac3.
Root typinfo.obj SHA256:
40061415f0967ee72c14ec7f7cb895551033c98ade9973dee139f8e4258622ae.
Provider typname.obj SHA256:
86a3632d27658fd13f9f40c2db6014c0a29d85c275bb8bb729b385e89fdad656.

## Complete provider ownership, not an unreachable-byte exception

The provider's entire112 bytes canonically match. Its normal CFG owns103 bytes;
the source SEH scope and the normal-path call both identify the final9-byte
cleanup at68E63D. Both CFGs are independently closed. The complete28-byte EH4
scope table at6E2290 matches all fields, not just the action pointer.

The local COFF name $LN10 is not globally unique in typname.obj. The scope
relocation is checked by actual symbol-table index, owning section and103-byte
function offset, preventing accidental selection of another identically named
local label. All source relocations and named CRT calls are explicit.

The real type-info list root at6FD41C is two zero-initialized DWORDs. Its source
is an eight-byte uninitialized COFF .bss section; both target fields occupy the
writable, non-executable PE zero-fill tail. There are no raw file bytes there
to compare. The proof uses loader zero-initialization and actual pointer
addends0/4, not an invented raw-byte read or a mutable address placeholder.

The root's whole14-byte extent, two relocations, remaining bytes, CFG and
full-inventory uniqueness pass. Existing native cleanup/provider code and
metadata get no additional authored or function-byte credit.

Nine focused tests protect source/archive/member/type/bindings and zero-fill
storage rules. All166 actual initialized-byte mutations fail: every root,
provider and scope-table byte plus the boundaries of all unique RTTI regions.
The prior invalid_argument copy and its independently exact logic_error113/EH
gate freshly pass after registering the actual type_info vtable.

Evidence: build/origin-anchors/vc8-typeinfo-dtor/proof.json and
build/frontier-typeinfo-dtor-20261101/. Private scripts are under
.analysis/frontier-typeinfo-dtor-20261101/.
