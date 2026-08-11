#include "Collision.hpp"
#include "SpellData.hpp"
#include "SpellRuntime.hpp"

#include "input/InputManager.hpp"

#include <cstring>
#include <deque>

namespace th105 {

void __fastcall initialize_fighter_phase_62380(Fighter *fighter);
void __fastcall initialize_fighter_phase_631e0(Fighter *fighter);
void __stdcall set_spell_sequence_mode_430fa0(int value);
void __fastcall reset_fighter_sequence_controller_45e5f0(
    FighterSequenceController *controller);
extern "C" void __cdecl _invalid_parameter_noinfo(void);

namespace {

struct OwnedManagerInitializationView {
    virtual void slot_00();
    virtual void slot_04();
    virtual void reset_08();
};

struct FighterPhaseSubobject710 {
    std::deque<short> history_00;
};

typedef void (__thiscall *SetFighterAction)(Fighter *fighter, int action);

__forceinline void set_fighter_action(Fighter *fighter, int action)
{
    void **vtable = *reinterpret_cast<void ***>(fighter);
    reinterpret_cast<SetFighterAction>(vtable[2])(fighter, action);
}

__forceinline FighterSequenceSlot *checked_front_sequence_slot(
    FighterSequenceController *controller)
{
    unsigned index = controller->head_0c;
    if (controller->live_count_10 + index < index) {
        _invalid_parameter_noinfo();
    }
    if (controller->live_count_10 + controller->head_0c < index ||
        index < controller->head_0c) {
        _invalid_parameter_noinfo();
    }
    if (controller->live_count_10 + controller->head_0c <= index) {
        _invalid_parameter_noinfo();
    }
    if (controller->slot_capacity_08 <= index) {
        index -= controller->slot_capacity_08;
    }
    return controller->slots_04[index];
}

__forceinline void store_word(Fighter *fighter, unsigned offset, short value)
{
    *reinterpret_cast<short *>(
        reinterpret_cast<unsigned char *>(fighter) + offset) = value;
}

__forceinline void store_byte(
    Fighter *fighter,
    unsigned offset,
    unsigned char value)
{
    *(reinterpret_cast<unsigned char *>(fighter) + offset) = value;
}

__forceinline void store_int(Fighter *fighter, unsigned offset, int value)
{
    *reinterpret_cast<int *>(
        reinterpret_cast<unsigned char *>(fighter) + offset) = value;
}

} // namespace

// The native deque assign is semantically void.  Linked callers in the target
// may observe its incidental EAX, so the ledger retains that ABI uncertainty;
// return types do not participate in the x86 decorated symbol.
void __fastcall initialize_fighter_phase_631e0(Fighter *fighter)
{
    unsigned char packed =
        static_cast<unsigned>(fighter->field_6c8) > 0;
    packed += packed;
    packed |= static_cast<unsigned>(fighter->field_6c4) > 0;
    packed += packed;
    packed |= static_cast<unsigned>(fighter->field_6c0) > 0;
    packed += packed;
    packed |= static_cast<unsigned>(fighter->field_6bc) > 0;
    packed += packed;
    packed |= fighter->field_6b8 > 0;
    packed += packed;
    packed |= fighter->field_6b8 < 0;
    packed += packed;
    packed |= fighter->field_6b4 > 0;
    packed += packed;
    packed |= fighter->field_6b4 < 0;

    unsigned short packed_input = packed;
    reinterpret_cast<FighterPhaseSubobject710 *>(
        reinterpret_cast<unsigned char *>(fighter) + 0x710)
        ->history_00.assign(
            0x5a,
            reinterpret_cast<short const &>(packed_input));
}

void Fighter::initialize_fighter_battle_state()
{
    if (field_6b0 != 0) {
        reinterpret_cast<CInputManager *>(
            *reinterpret_cast<void **>(field_6b0))->reset_counters();
    }
    reinterpret_cast<OwnedManagerInitializationView *>(owned_manager_658)
        ->reset_08();

    field_6b4 = 0;
    field_6b8 = 0;
    field_6bc = 0;
    field_6c0 = 0;
    field_6c4 = 0;
    field_6c8 = 0;
    field_6cc = 0;
    field_6d0 = 0;
    field_6f4 = 0;
    field_6f8 = 0;
    field_6fc = 0;
    field_700 = 0;
    field_704 = 0;
    field_708 = 0;
    initialize_fighter_phase_62380(this);
    initialize_fighter_phase_631e0(this);

    x_ec = static_cast<float>(
        (player_index_334 == 1) * 320.0 + 480.0);
    facing_104 = static_cast<unsigned char>(
        1 - (player_index_334 == 1) * 2);
    y_f0 = 0.0f;
    x_component_f4 = 0.0f;
    y_component_f8 = 0.0f;
    body_overlap_x_6a4 = 0.0f;
    body_overlap_y_6a8 = 0.0f;
    peer_component_6ac = 0.0f;
    response_18c = 0.0f;
    response_190 = 0.0f;
    x_component_fc = 0.0f;
    y_component_100 = 0.0f;
    reinterpret_cast<FighterActionScratch *>(
        reinterpret_cast<unsigned char *>(this) + 4)
        ->reset_fighter_action_scratch();

    result_186 = 0;
    store_word(this, 0x48a, 0);
    gate_48c = 0;
    gate_4a8 = 0;
    gate_4aa = 0;
    gate_4ac = 0;
    field_4ae = 0;
    store_word(this, 0x4b0, 0);
    store_word(this, 0x4b2, 0);
    state_4b8 = *reinterpret_cast<int *>(0x006e4e20);
    maximum_176 = 10000;
    value_174 = 10000;
    value_47c = 10000;
    blocker_48e = 0;
    field_49e = 0;
    value_4a0 = 0;
    value_4a2 = 0;
    field_4a6 = 0;
    field_4a4 = 0;
    unknown_490 = 0;
    store_byte(this, 0x47e, 0);
    store_byte(this, 0x47f, 0);
    store_byte(this, 0x480, 0);
    store_word(this, 0x4b4, 0);
    counter_558 = 0;
    unknown_484 = 1000;
    counter_482 = 1000;
    floor_486 = 0;
    scalar_494 = 1.0f;
    store_word(this, 0x488, 0);
    store_word(this, 0x6a0, 0);
    source_factor_4bc = 1.0f;
    value_498 = 0;
    target_factor_4c0 = 1.0f;
    value_49a = 0;
    threshold_scale_4c4 = 1.0f;
    flag_491 = 0;
    source_modifier_4c8 = 1.0f;
    gate_4e4 = 0;
    source_modifier_4cc = 1.0f;
    unknown_4e5 = 0;
    factor_4d0 = 1.0f;
    gate_4e6 = 0;
    unknown_4e7 = 0;
    factor_4d4 = 0.0f;
    value_49c = 0;
    scale_4d8 = 0.0f;
    x_scale_4dc = 1.0f;
    y_scale_4e0 = 1.0f;

    std::memset(unknown_624, -1, 0x20);
    std::memset(scalar_modifier_table_604, 0, sizeof(scalar_modifier_table_604));

    SetFighterAction reset_action = reinterpret_cast<SetFighterAction>(
        (*reinterpret_cast<void ***>(this))[2]);
    unknown_184[0] = 0;
    result_180 = 0;
    reset_action(this, 0);
    state_4ea = 0;
    store_byte(this, 0x4e9, 0);
    terminal_finalize_4eb = 0;
    store_byte(this, 0x4ec, 0);
    store_byte(this, 0x4e8, 0);
    gate_4ed = 0;
    field_724 = 0;
    field_728 = 0;
    store_byte(this, 0x135, 1);
    store_byte(this, 0x688, 0);
    store_int(this, 0x670, 0);
    store_int(this, 0x648, 0);
    store_int(this, 0x644, 0);
    store_byte(this, 0x654, 0);
    statistic_enable_655 = 0;
    statistic_candidate_64c = -1;

    if (state_72c == 2) {
        SpellDataOwner *lookup =
            reinterpret_cast<SpellDataOwner *>(spell_lookup_4f0);
        set_spell_sequence_mode_430fa0(0);
        state_55b = static_cast<signed char>(
            *reinterpret_cast<unsigned char *>(&spell_nonzero_gate_534));
        state_55a = 0;
        reset_fighter_sequence_controller_45e5f0(&sequence_controller_55c);
        for (int i = 0; i < state_55b; ++i) {
            prepare_next_spell_sequence_entry();
        }

        FighterSequenceSlot *front =
            checked_front_sequence_slot(&sequence_controller_55c);
        SpellRecordView *record =
            lookup->find_local_then_common_spell_record(front->record_id_00);
        value_174 = record->value_1e;
        maximum_176 = record->value_1e;
        store_byte(this, 0x6a2, 0);

        front = checked_front_sequence_slot(&sequence_controller_55c);
        if (front->record_id_00 >= 200) {
            post_advance_value_650 = -1;
            set_fighter_action(this, 700);
            return;
        }
        FighterSequenceSlot *selected =
            sequence_controller_55c.entry_at_checked(0);
        record = lookup->find_local_then_common_spell_record(
            selected->record_id_00);
        post_advance_value_650 = record->value_3c;
        set_fighter_action(this, 700);
        return;
    }

    set_spell_sequence_mode_430fa0(1);
    state_55b = 5;
    state_55a = 0;
    reset_fighter_sequence_controller_45e5f0(&sequence_controller_55c);
    store_byte(this, 0x6a2, 0);
    statistic_candidate_64c = -1;
    post_advance_value_650 = -1;
}

} // namespace th105
