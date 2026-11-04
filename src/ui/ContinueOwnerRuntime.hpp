#pragma once
#include <stddef.h>

namespace th105 {
struct Fighter;
struct RoundPostVirtual;

// Shared current-target owner prefix used by the continue menu and round reset.
struct ContinueOwnerRuntimeView {
    virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
    virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
    virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2c();
    virtual void slot30(); virtual void dispatch34(int);
    unsigned frame_04;
    int field_08;
    Fighter *fighter_0c;
    Fighter *fighter_10;
    unsigned char reserved_14[0x70];
    int end_pending_84;
    int phase_88;
    RoundPostVirtual *post_8c;
    unsigned char reserved_90[0x10];
    int remaining_continues_a0;
    unsigned char active_a4;
    void reset_battle_round_471180();
};
typedef char ContinueOwner_pending_offset[offsetof(ContinueOwnerRuntimeView,end_pending_84)==0x84?1:-1];
typedef char ContinueOwner_remaining_offset[offsetof(ContinueOwnerRuntimeView,remaining_continues_a0)==0xa0?1:-1];
typedef char ContinueOwner_active_offset[offsetof(ContinueOwnerRuntimeView,active_a4)==0xa4?1:-1];
} // namespace th105
