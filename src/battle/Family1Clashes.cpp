// Partial runtime views; no original complete class/TU identity is asserted.
#include <list>
#include <stddef.h>
namespace th105 {
namespace {
struct ClashFrame {
    unsigned char unknown_00[0x4c];
    unsigned flags_4c;
    unsigned flags_50;
};
struct ClashObject {
    unsigned char unknown_000[0x1a0];
    unsigned char active_1a0;
    unsigned char unknown_1a1[3];
    ClashFrame *frame_1a4;
};
struct ClashContext {
    unsigned char unknown_00[0x44];
    std::list<void *> family_1[2];
    void dispatch_family1_object_clashes();
    void resolve_group_b_object_clash(void *first,void *second);
};
typedef char CheckFamily1Offset[offsetof(ClashContext, family_1) == 0x44 ? 1 : -1];
typedef char CheckFamily1Stride[sizeof(std::list<void *>) == 12 ? 1 : -1];
typedef char CheckActiveOffset[offsetof(ClashObject, active_1a0) == 0x1a0 ? 1 : -1];
typedef char CheckFrameOffset[offsetof(ClashObject, frame_1a4) == 0x1a4 ? 1 : -1];

void ClashContext::dispatch_family1_object_clashes()
{
    for (int slot=0;slot<2;++slot) {
        std::list<void *>::iterator outer=family_1[slot].begin();
        std::list<void *>::iterator end=family_1[slot].end();
        for (;outer!=end;++outer) {
            if ((static_cast<ClashObject *>(*outer)->frame_1a4->flags_50&0x100000)!=0 &&
                (static_cast<ClashObject *>(*outer)->frame_1a4->flags_4c&0x40)==0 &&
                static_cast<ClashObject *>(*outer)->active_1a0!=0 &&
                (static_cast<ClashObject *>(*outer)->frame_1a4->flags_4c&0x80000)==0) {
                std::list<void *>::iterator inner=family_1[slot].begin();
                std::list<void *>::iterator inner_end=family_1[slot].end();
                for (;inner!=inner_end;++inner) {
                    if ((static_cast<ClashObject *>(*inner)->frame_1a4->flags_4c&0x40)==0 &&
                        static_cast<ClashObject *>(*inner)->active_1a0!=0 &&
                        (static_cast<ClashObject *>(*inner)->frame_1a4->flags_4c&0x80000)==0 &&
                        *inner!=*outer) {
                        resolve_group_b_object_clash(*outer,*inner);
                    }
                }
            }
        }
    }
    std::list<void *>::iterator outer=family_1[0].begin();
    std::list<void *>::iterator left_end=family_1[0].end();
    for (;outer!=left_end;++outer) {
        if ((static_cast<ClashObject *>(*outer)->frame_1a4->flags_4c&0x40)==0 &&
            static_cast<ClashObject *>(*outer)->active_1a0!=0 &&
            (static_cast<ClashObject *>(*outer)->frame_1a4->flags_4c&0x80000)==0) {
            std::list<void *>::iterator inner=family_1[1].begin();
            std::list<void *>::iterator right_end=family_1[1].end();
            for (;inner!=right_end;++inner) {
                if ((static_cast<ClashObject *>(*inner)->frame_1a4->flags_4c&0x40)==0 &&
                    static_cast<ClashObject *>(*inner)->active_1a0!=0 &&
                    (static_cast<ClashObject *>(*inner)->frame_1a4->flags_4c&0x80000)==0) {
                    resolve_group_b_object_clash(*outer,*inner);
                }
            }
        }
    }
}
} // namespace
} // namespace th105
