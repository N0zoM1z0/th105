# VC8 default string constructor origin

The pinned Japanese TH105 1.06a executable contains an 18-byte callable body at
`0x00403EB0` with SHA-256
`8246af2f786a5ae528ac9b3284f8de002699bcbb0af05aa1ef24c8ac9cb776f8`.
The native Select constructor passes its address as a string-array construction
callback at `0x0042325B`.

A tracked `std::string[2]` witness built with the pinned VC8 compiler emits the
complete same 18-byte default-constructor COMDAT. Its fingerprint is unique
across the current candidate inventory, and both body and callback pointer are
pinned by the origin rule. It is classified as compiler-generated, not an
additional authored exact function. This default constructor is distinct from
the unresolved 37-byte local string-copy constructor in the Scenario update
candidate; that caller remains blocked.
