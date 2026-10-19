// Target-backed runtime prefixes; these do not recover complete original classes.
#include <list>
#include <vector>
#include <stddef.h>

namespace th105 {
void __fastcall prepare_collision_geometry_from_frame(void *object);
namespace {
struct Box16 { int x0, y0, x1, y1; };
struct PhaseFrame {
    unsigned char unknown_00[0x4c];
    unsigned flags_4c;
    unsigned flags_50;
    void *primary_54;
    std::vector<Box16> family1_58;
    std::vector<Box16> family2_68;
};
struct PhaseCandidateFrame {
    unsigned char unknown_00[0x50];
    unsigned flags_50;
};
struct PhaseFighter;
struct PhaseObject {
    unsigned char unknown_000[0x158];
    PhaseFrame *frame_158;
    unsigned char unknown_15c[0x10];
    PhaseFighter *owner_16c;
    unsigned char unknown_170[0x10];
    int result_180;
    signed char result_184;
    unsigned char unknown_185[0x0f];
    void *extension_194;
    unsigned char unknown_198[0x0c];
    PhaseCandidateFrame *prepared_frame_1a4;
};
struct PhaseManager {
    virtual void slot_00(); virtual void slot_04();
    virtual void slot_08(); virtual void slot_0c();
    virtual void slot_10(); virtual void slot_14();
    virtual void slot_18(); virtual void slot_1c();
    virtual void slot_20();
    virtual std::list<PhaseObject *> *collision_objects_24();
};
struct PhaseFighter {
    unsigned char unknown_000[0x170];
    PhaseFighter *other_170;
    short value_174, maximum_176;
    unsigned char unknown_178[8];
    int result_180;
    signed char result_184;
    unsigned char unknown_185[0x2a];
    unsigned char active_1af;
    unsigned char unknown_1b0[0x184];
    signed char player_334;
    unsigned char unknown_335[0x1b4];
    unsigned char state_4e9, state_4ea;
    unsigned char unknown_4eb[0x16d];
    PhaseManager *manager_658;
    void apply_deferred_counter_558(short amount);
};
struct CollisionPhase {
    unsigned char unknown_00[0x0c];
    PhaseFighter *fighters[2];
    unsigned char unknown_14[0x18];
    std::list<void *> family_0[2], family_1[2], family_2[2];
    int deferred_74[2], deferred_7c[2];
    void run_attack_projectile_collision_phase();
    void dispatch_family1_object_clashes();
    void dispatch_family2_against_family1();
    void resolve_attack_candidate_against_fighter(void *candidate, PhaseFighter *fighter);
};
typedef char CheckCollisionPhaseSize[sizeof(CollisionPhase) == 0x84 ? 1 : -1];
typedef char CheckCollisionFamily0Offset[offsetof(CollisionPhase, family_0) == 0x2c ? 1 : -1];
typedef char CheckCollisionFamily1Offset[offsetof(CollisionPhase, family_1) == 0x44 ? 1 : -1];
typedef char CheckCollisionFamily2Offset[offsetof(CollisionPhase, family_2) == 0x5c ? 1 : -1];
typedef char CheckDeferredOffset[offsetof(CollisionPhase, deferred_74) == 0x74 ? 1 : -1];
typedef char CheckManagerOffset[offsetof(PhaseFighter, manager_658) == 0x658 ? 1 : -1];
typedef char CheckFighterPlayerOffset[offsetof(PhaseFighter, player_334) == 0x334 ? 1 : -1];
typedef char CheckFighterStateOffset[offsetof(PhaseFighter, state_4e9) == 0x4e9 ? 1 : -1];
typedef char CheckActorOwnerOffset[offsetof(PhaseObject, owner_16c) == 0x16c ? 1 : -1];
typedef char CheckActorExtensionOffset[offsetof(PhaseObject, extension_194) == 0x194 ? 1 : -1];
typedef char CheckPreparedFrameOffset[offsetof(PhaseObject, prepared_frame_1a4) == 0x1a4 ? 1 : -1];

void CollisionPhase::run_attack_projectile_collision_phase()
{
    int slot;
    for (slot=0;slot<2;++slot) {
        family_0[slot].clear();
        family_1[slot].clear();
        family_2[slot].clear();
        deferred_74[slot]=0;
        deferred_7c[slot]=0;
    }
    for (slot=0;slot<2;++slot) {
        prepare_collision_geometry_from_frame(fighters[slot]);
        fighters[slot]->state_4ea=fighters[slot]->state_4e9;
        std::list<PhaseObject *>::iterator it= fighters[slot]->manager_658->collision_objects_24()->begin();
        std::list<PhaseObject *>::iterator end=fighters[slot]->manager_658->collision_objects_24()->end();
        for (;it!=end;++it) {
            int player=(*it)->owner_16c->player_334;
            int family2_count=(*it)->frame_158->family2_68.size();
            int family1_count=(*it)->frame_158->family1_58.size();
            if ((*it)->extension_194!=0) {
                ++family2_count;
                if (((*it)->frame_158->flags_4c & 0x1000000)!=0)
                    ++family1_count;
            }
            if (family2_count!=0 && (*it)->result_180==0 && (*it)->result_184>0) {
                prepare_collision_geometry_from_frame(*it);
                family_0[player].push_back(*it);
                if (family1_count!=0)family_1[player].push_back(*it);
                family_2[player].push_back(*it);
            } else if (family1_count!=0) {
                prepare_collision_geometry_from_frame(*it);
                family_1[player].push_back(*it);
                family_2[player].push_back(*it);
            }
        }
    }
    for (slot=0;slot<2;++slot) {
        if (fighters[slot]->active_1af!=0 && fighters[slot]->result_180==0 && fighters[slot]->result_184>0) {
            family_0[slot].push_back(fighters[slot]);
            family_2[slot].push_back(fighters[slot]);
        }
    }
    dispatch_family1_object_clashes();
    dispatch_family2_against_family1();
    for (slot=0;slot<2;++slot) {
        PhaseFighter *other=fighters[slot]->other_170;
        std::list<void *>::iterator it=family_0[slot].begin();
        std::list<void *>::iterator end=family_0[slot].end();
        for (;it!=end;++it) {
            resolve_attack_candidate_against_fighter(*it,other);
            if ((static_cast<PhaseObject *>(*it)->prepared_frame_1a4->flags_50 & 0x100000)!=0)
                resolve_attack_candidate_against_fighter(*it,fighters[slot]);
        }
    }
    for (slot=0;slot<2;++slot) {
        if (deferred_74[slot]!=0 && fighters[slot]->value_174>0) {
            PhaseFighter *fighter = fighters[slot];
            int value=static_cast<short>(deferred_74[slot])+static_cast<int>(fighter->value_174);
            if (value>=fighter->maximum_176)value=fighter->maximum_176;
            fighter->value_174=static_cast<short>(value);
        }
        if (deferred_7c[slot]!=0)
            fighters[slot]->apply_deferred_counter_558(static_cast<short>(deferred_7c[slot]));
    }

}
} // namespace
} // namespace th105
