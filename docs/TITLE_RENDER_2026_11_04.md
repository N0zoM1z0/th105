# Title-screen rendering

The RTTI-owned `CTitle` virtual table points to `0x00425740`, the complete
417-byte title-screen renderer. The raw boundary audit reaches all 117 native
instructions. The source uses the established `CTitle` members and retains
all three cosine calls, including the first whose result is discarded, the
color conversions, selected sprite scaling and 12 menu tile renders.

A fresh pinned VC8 build emits 417 bytes, but strict comparison differs first
at +232 because the selected-index load is scheduled before the sprite scale
stores. Equal length is not exactness; no exact bytes are added. This source
has not been exercised in a live game or graphics session.
