# Two original public Boost exception-template copy bodies

Two complete clone copies are now canonical and inventory-unique:
-6B5060/46: clone_impl<error_info_injector<std::logic_error>>.
-6A95D0/46: clone_impl<error_info_injector<std::invalid_argument>>.

Only these92 third-party bytes are newly classified. This does not reinterpret
them as runtime_error, and the previously unresolved regex_error clone remains
outside this scope.

## Genuine original public instantiations

BoostExceptionCopiesOrigin.cpp contains only the standard release NDEBUG,
original public headers and two explicit public boost::throw_exception
instantiations. There is no replacement implementation, new caller algorithm,
private helper export, forced register convention or COFF barrier. The ordinary
VC8/O2/GS unit naturally emits both public specializations and their real
nested class copy machinery.

The original public declaration includes BOOST_ATTRIBUTE_NORETURN. VC8 rejects
an explicit instantiation that omits this original attribute with C2893.
Preserving the exact original declaration fixes that language-level mismatch;
it is not a newly invented noreturn contract. The selected declarations use
deduced template arguments. Original vendor files and all184 header pins are
unchanged. A dedicated exact-hash guard checks this public probe, accepting
Git LF/CRLF normalization but rejecting missing original attributes or added
wrapper code. Both public source bodies are97 bytes and receive no native
body acceptance or credit here.

The reproducible unit boost-public-exception-copies has the two46-byte roots.
Six new named vtable data rows cover the actual clone subobjects; the common
clone_base binding already existed. No old binding or gameplay source changes.

## Whole roots and actual type identity

Each46-byte body has one actual injector call at REL32+9 and four typed vptr
fields+16/+22/+29/+36. Its complete closed CFG and all nonrelocation bytes
are retained. Source names, operand inventories, whole native equality and
full-inventory uniqueness are required; no masked discovery result is counted.

The complete symbolic COFF RTTI graph is matched to the target before these
vptr addresses are admitted. Fourteen primary/secondary vtable roles establish
clone_base, boost::exception, the two standard classes, their injectors and
clones. Primary offsets are0; injector secondary offsets40; clone secondary
and clone_base offsets40/60. All complete-object locators, TypeDescriptors
including every name byte, hierarchy headers, all declared base-array entries
and base descriptors are canonical. Nonvirtual PMD adjustments, contained-base
counts and own-class hierarchy cycles are checked. Shared source symbols must
retain consistent native identity. These are typed metadata extents, not
padding or unrelated virtual-method byte claims.

## Complete injector and exception cleanup proof

Actual original copy injectors6B4E60/147 and6A7310/153 are wholly canonical.
They were already excluded and receive no new byte credit. Their complete
source .text$x35 sections contain action8 plus handler27; .xdata$x44 contains
unwind8 plus FuncInfo36. Both complete sections match:
- logic_error: action6BD3F0, handler6BD3F8, unwind6E37CC, info6E37D4.
- invalid_argument: action6BC9D0, handler6BC9D8, unwind6E2C68, info6E2C70.

The source logic_error destructor50 fully matches401740. The current ordinary
logic_error copy113 is still nonexact because of EH-state scheduling; its
named normal interface has an independent observed source proof in another
accepted context. It is not presented as an additional current exact body.

The invalid_argument destructor is another explicit provider limit. Source
inlining yields50 bytes equal to the base destructor401740, whereas the actual
native cleanup provider665AC7 is11 bytes: it stores the real invalid_argument
vptr6C7548 and tail-jumps to401740. Its full native body, ordinary ECX/no-stack
interface, class RTTI and independent existing ownership are checked. The EH
call binds that actual named destructor. Source50 is NOT claimed byte-equal
to native11, and no provider bytes are added. No noinline/ABI workaround is
introduced to erase this distinction.

## Verification and regression

The final ordinary unit reports both46-byte roots exact. Thirteen focused
tests cover schema, original public source/configuration, Git newline forms,
original noreturn declaration, type/subobject identities, immutable RTTI
storage, full names, hierarchy cycles and consistent pointer identities.
Twenty-nine actual mutations of roots, injectors, EH, RTTI and typed provider
witnesses are rejected.

The previous original runtime_error clone46 gate freshly passes after the upstream
probe guard addition. Its source remains unchanged; no cold all-unit rebuild is
justified. The initial private COFF leads alone were not accepted; full type/EH
validation precedes the final narrow origin replay.

Excluded2017/review355; authored exact1431/443916 bytes, authored1655,
source1635 and mapped1820 remain unchanged. The new library unit brings the
configured unit count to778. No push.

## Later regex-family source context

A separate original public regex_error instantiation now closes6B5350/46 with
whole154/113 support, both complete EH sections and actual original regex.cpp
destructor50. Its earlier seven-TU CIL negative remains unchanged. See
BOOST_PUBLIC_REGEX_EXCEPTION_2026_11_01.md; no prior gate or provider limit was
weakened to accept this distinct ordinary context.
