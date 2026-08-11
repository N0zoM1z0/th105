#pragma once

#include <deque>

namespace th105 {

struct Fighter;
struct FileReader;
struct String28;

typedef std::deque<short> SidePayload;

struct FixedBattleSetupSlot {
    unsigned char side_value_lo_00[2];
    unsigned char side_byte_05_02[2];
    unsigned char side_byte_06_04[2];
    unsigned char side_byte_04_06[2];
    SidePayload payload_08[2];
    unsigned char token_tag_30[2];
    unsigned char tail_32;
    unsigned char tail_33;
    unsigned char tail_34;
    unsigned char padding_35[3];
    unsigned tail_dword_38;
};

struct FixedSlotEnvelope {
    FixedBattleSetupSlot setup_00;
    SidePayload private_payload_3c;

    bool deserialize_fixed_slot_envelope(FileReader *reader);
};

struct FixedSlotEnvelopeVector {
    unsigned allocator_00;
    FixedSlotEnvelope *begin_04;
    FixedSlotEnvelope *end_08;
    FixedSlotEnvelope *capacity_end_0c;
};

typedef char SidePayload_size_must_be_0x14[
    sizeof(SidePayload) == 0x14 ? 1 : -1];
typedef char FixedBattleSetupSlot_size_must_be_0x3c[
    sizeof(FixedBattleSetupSlot) == 0x3c ? 1 : -1];
typedef char FixedSlotEnvelope_size_must_be_0x50[
    sizeof(FixedSlotEnvelope) == 0x50 ? 1 : -1];
typedef char FixedSlotEnvelopeVector_size_must_be_0x10[
    sizeof(FixedSlotEnvelopeVector) == 0x10 ? 1 : -1];

// One-hop contracts reached directly from the BattleController island. These
// names are neutral reconstruction views; no original class ownership is
// claimed beyond the observed __thiscall receiver.
struct BattleControlBridgeView {
    int update_local_practice_battle_controls();
    int publish_synchronized_control_bits();
    int collect_battle_control_bits();
};

struct BattleSetupOwner {
    void save_battle_setup_slot(signed char slot, const void *setup);
    void load_battle_setup_slot(signed char slot, void *setup);
    void configure_session_input_slots(
        signed char slot_count,
        signed char game_mode);
    bool load_battle_input_recording(const char *path);
};

struct ScenarioBattleView {
    int advance_scenario_script_page();
    void initialize_character_story_script(
        signed char character_key,
        int argument0,
        int argument1);
    void parse_scenario_event_row(void *destination);
};

struct BattleMenuView {
    void *construct_battle_menu(unsigned selection);
};

struct BattleRenderStateView {
    int reset_battle_render_state_and_signal();
};

struct BattlePairContextView {
    int initialize_battle_fighter_pair();
};

unsigned int __thiscall update_fighter_scripted_input_state(Fighter *fighter);

} // namespace th105
