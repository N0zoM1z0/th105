# Restore the standalone core contract validator

CoreContracts.cpp failed to compile before the actual-sprite changes because
CoreContracts.hpp still asserted sizeof(SequenceRecord4). That type was removed
in dbca9393 when the enqueue argument was corrected to the complete98-byte
FighterSequenceSlot; the unrelated old assertion survived. A fresh pre-change
compile reproduced the undefined-type/negative-subscript diagnostics.

The validator now checks the real record's id0,flags2,sprite4 offsets alongside
its existing98-byte size check. It also binds enqueue_record to an explicit
void (FighterSequenceController::*)(const FighterSequenceSlot *) member pointer.
No removed prefix type is recreated and no runtime implementation changes.
The obsolete reference to the removed core-types.csv is removed from a comment.

The full compile-only TU now passes with the repository VC8 toolchain:

taskset -c 0 nice -n 10 env TH105_ENABLE_GS=1 scripts/compile-unit.sh
src/battle/CoreContracts.cpp build/core-contracts/CoreContracts.obj

Two private negative controls prove the checks operate: sprite offset8 rejects
with a negative-array diagnostic, and a mutable enqueue argument rejects the
member-pointer conversion. Restoring the real header passes again. Fresh
cross-v106a-sequence-enqueue remains canonical114 bytes at45DBA0. No manifest
unit includes this validator, and it earns no native/source/exact credit.

Default CI remains target-independent and does not silently require native
compilation; the explicit command above validates recovered C++ declarations when
needed.
