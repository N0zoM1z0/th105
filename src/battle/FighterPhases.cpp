#include <vector>

namespace th105 {

void __fastcall integrate_and_clamp_fighter_position(void *fighter);
void __fastcall run_common_character_update(void *fighter);
void __fastcall process_fighter_transient_status(void *fighter);
void __fastcall decrement_fighter_timers_and_cleanup(void *fighter);

namespace {

struct OwnedObjectManagerView {
    virtual void slot_00();
    virtual void slot_04();
    virtual void slot_08();
    virtual void slot_0c();
    virtual void slot_10();
};

struct ActiveFighterView {
    virtual void slot_00();
    virtual void slot_04();
    virtual void slot_08();
    virtual void slot_0c();
    virtual void slot_10();
    virtual void slot_14();
    virtual void slot_18();
    virtual void slot_1c();
    virtual void slot_20();
    virtual void slot_24();
    virtual void slot_28();
    virtual void slot_2c();
    virtual void slot_30();
    virtual void slot_34();
    virtual void slot_38();
    virtual void slot_3c();
    virtual void slot_40();

    unsigned char unknown_004[0x654];
    OwnedObjectManagerView *owned_manager_658;
};

struct FighterPhaseContextView {
    // VC8's vector object includes a four-byte allocator/pair base before
    // _Myfirst, so the object begins at +0x38 while its pointer triplet is
    // observed at +0x3c/+0x40/+0x44.
    unsigned char unknown_00[0x38];
    std::vector<ActiveFighterView *> fighters_3c;
};

} // namespace

void __fastcall run_active_character_and_owned_object_callbacks(
    void *raw_context)
{
    FighterPhaseContextView *context =
        static_cast<FighterPhaseContextView *>(raw_context);

    unsigned index;
    for (index = 0; index < context->fighters_3c.size(); ++index) {
        context->fighters_3c[index]->slot_40();
    }
    for (index = 0; index < context->fighters_3c.size(); ++index) {
        context->fighters_3c[index]->owned_manager_658->slot_0c();
    }
    for (index = 0; index < context->fighters_3c.size(); ++index) {
        context->fighters_3c[index]->slot_28();
    }
    for (index = 0; index < context->fighters_3c.size(); ++index) {
        run_common_character_update(context->fighters_3c[index]);
    }
    for (index = 0; index < context->fighters_3c.size(); ++index) {
        context->fighters_3c[index]->owned_manager_658->slot_10();
    }
}

void __fastcall commit_fighter_physics_status_timers(void *raw_context)
{
    FighterPhaseContextView *context =
        static_cast<FighterPhaseContextView *>(raw_context);

    unsigned index;
    for (index = 0; index < context->fighters_3c.size(); ++index) {
        integrate_and_clamp_fighter_position(context->fighters_3c[index]);
    }
    for (index = 0; index < context->fighters_3c.size(); ++index) {
        process_fighter_transient_status(context->fighters_3c[index]);
    }
    for (index = 0; index < context->fighters_3c.size(); ++index) {
        decrement_fighter_timers_and_cleanup(context->fighters_3c[index]);
    }
}

} // namespace th105
