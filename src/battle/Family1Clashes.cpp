// Partial runtime views; no original complete class/TU identity is asserted.
#include "PatResourceContracts.hpp"
#include <list>
#include <stddef.h>
namespace th105 {
namespace {
struct ClashObject {
    unsigned char unknown_000[0x1a0];
    unsigned char snapshot_result_slot_1a0;
    unsigned char unknown_1a1[3];
    PatRecord88 *prepared_frame_1a4;
};
struct ClashContext {
    unsigned char unknown_00[0x44];
    std::list<void *> family_1[2];
    void dispatch_family1_object_clashes();
    void resolve_group_b_object_clash(void *first,void *second);
};
typedef char CheckFamily1Offset[offsetof(ClashContext, family_1) == 0x44 ? 1 : -1];
typedef char CheckFamily1Stride[sizeof(std::list<void *>) == 12 ? 1 : -1];
typedef char CheckActiveOffset[offsetof(ClashObject, snapshot_result_slot_1a0) == 0x1a0 ? 1 : -1];
typedef char CheckFrameOffset[offsetof(ClashObject, prepared_frame_1a4) == 0x1a4 ? 1 : -1];

void ClashContext::dispatch_family1_object_clashes()
{
    // Same-side pass: only an object with flags_50 bit 0x100000 can
    // initiate a clash. Ordered pairs are visited, except self-pairs.
    for (int slot=0;slot<2;++slot) {
        std::list<void *>::iterator outer=family_1[slot].begin();
        std::list<void *>::iterator end=family_1[slot].end();
        for (;outer!=end;++outer) {
            if ((static_cast<ClashObject *>(*outer)->prepared_frame_1a4->flags_50&0x100000)!=0 &&
                (static_cast<ClashObject *>(*outer)->prepared_frame_1a4->flags_4c&0x40)==0 &&
                static_cast<ClashObject *>(*outer)->snapshot_result_slot_1a0!=0 &&
                (static_cast<ClashObject *>(*outer)->prepared_frame_1a4->flags_4c&0x80000)==0) {
                std::list<void *>::iterator inner=family_1[slot].begin();
                std::list<void *>::iterator inner_end=family_1[slot].end();
                for (;inner!=inner_end;++inner) {
                    if ((static_cast<ClashObject *>(*inner)->prepared_frame_1a4->flags_4c&0x40)==0 &&
                        static_cast<ClashObject *>(*inner)->snapshot_result_slot_1a0!=0 &&
                        (static_cast<ClashObject *>(*inner)->prepared_frame_1a4->flags_4c&0x80000)==0 &&
                        *inner!=*outer) {
                        resolve_group_b_object_clash(*outer,*inner);
                    }
                }
            }
        }
    }
    // Cross-side pass: visit family 1 slot 0 against slot 1 once.
    // Both sides use the same frame-flag and snapshot-slot gates as above;
    // this pass does not require the initiator bit used in the first pass.
    std::list<void *>::iterator outer=family_1[0].begin();
    std::list<void *>::iterator left_end=family_1[0].end();
    for (;outer!=left_end;++outer) {
        if ((static_cast<ClashObject *>(*outer)->prepared_frame_1a4->flags_4c&0x40)==0 &&
            static_cast<ClashObject *>(*outer)->snapshot_result_slot_1a0!=0 &&
            (static_cast<ClashObject *>(*outer)->prepared_frame_1a4->flags_4c&0x80000)==0) {
            std::list<void *>::iterator inner=family_1[1].begin();
            std::list<void *>::iterator right_end=family_1[1].end();
            for (;inner!=right_end;++inner) {
                if ((static_cast<ClashObject *>(*inner)->prepared_frame_1a4->flags_4c&0x40)==0 &&
                    static_cast<ClashObject *>(*inner)->snapshot_result_slot_1a0!=0 &&
                    (static_cast<ClashObject *>(*inner)->prepared_frame_1a4->flags_4c&0x80000)==0) {
                    resolve_group_b_object_clash(*outer,*inner);
                }
            }
        }
    }
}
} // namespace
} // namespace th105
