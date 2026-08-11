#include "BattleController.hpp"
#include "GameMode.hpp"

#include <deque>

namespace th105 {

extern "C" void __cdecl _invalid_parameter_noinfo();

typedef std::deque<short> SidePayloadView;

struct FixedBattleSetupSlotView {
    unsigned char side_value_lo_00[2];
    unsigned char side_byte_05_02[2];
    unsigned char side_byte_06_04[2];
    unsigned char side_byte_04_06[2];
    SidePayloadView payload_08[2];
    unsigned char token_tag_30[2];
    unsigned char tail_32;
    unsigned char tail_33;
    unsigned char tail_34;
    unsigned char padding_35[3];
    unsigned tail_dword_38;
};

struct FixedSlotEnvelopeView {
    FixedBattleSetupSlotView setup_00;
    SidePayloadView private_payload_3c;
};

struct SetupTokenInput {
    unsigned value_00;
    unsigned char tag_04;
    unsigned char padding_05[3];
};

struct MatchSetupSideView {
    int value_00;
    unsigned char byte_04;
    unsigned char byte_05;
    unsigned char byte_06;
    unsigned char padding_07;
    SidePayloadView payload_08;
    SetupTokenInput *token_1c;
};

struct MatchSetupView {
    int terminal_00;
    unsigned char terminal_04;
    unsigned char terminal_05;
    unsigned char padding_06[2];
    MatchSetupSideView sides_08[2];
    unsigned terminal_dword_48;
};

struct FixedSlotStoreView {
    unsigned allocator_00;
    FixedSlotEnvelopeView *begin_04;
    FixedSlotEnvelopeView *end_08;
    unsigned capacity_0c;

    FixedBattleSetupSlotView *select_slot_4275e0(int slot);
};

struct SavedTokenMetadata {
    unsigned value_00;
    unsigned char tag_04;
    unsigned char padding_05[3];
};

struct BattleInputGateSetupView {
    unsigned retained_token_values_00[2];
    unsigned char padding_08[0xd0];
    SavedTokenMetadata saved_tokens_d8[2];
    unsigned char padding_e8[8];
    signed char saved_token_mask_f0;
    unsigned char padding_f1[3];
    FixedSlotStoreView slots_f4;
    FixedBattleSetupSlotView *selected_slot_104;
    unsigned char padding_108[0x38];
    signed char maximum_saved_slot_140;
    signed char loaded_slot_141;
};

typedef char MatchSetupSideView_size_must_be_0x20[
    sizeof(MatchSetupSideView) == 0x20 ? 1 : -1];
typedef char MatchSetupView_size_must_be_0x4c[
    sizeof(MatchSetupView) == 0x4c ? 1 : -1];
typedef char BattleInputGateSetupView_loaded_slot_offset_must_be_0x141[
    offsetof(BattleInputGateSetupView, loaded_slot_141) == 0x141 ? 1 : -1];

FixedBattleSetupSlotView *FixedSlotStoreView::select_slot_4275e0(int slot)
{
    if (begin_04 == 0 ||
        static_cast<unsigned>(slot) >=
            static_cast<unsigned>(end_08 - begin_04)) {
        _invalid_parameter_noinfo();
    }
    return &begin_04[slot].setup_00;
}

void BattleInputGate::save_battle_setup_slot(
    signed char slot,
    MatchSetup *setup)
{
    if (slot < 0) {
        return;
    }

    BattleInputGateSetupView *owner =
        reinterpret_cast<BattleInputGateSetupView *>(this);
    int count = 0;
    if (owner->slots_f4.begin_04 != 0) {
        count = owner->slots_f4.end_08 - owner->slots_f4.begin_04;
    }
    if (slot > count) {
        return;
    }

    FixedBattleSetupSlotView *saved =
        owner->slots_f4.select_slot_4275e0(slot);
    owner->selected_slot_104 = saved;
    const MatchSetupSideView *source =
        reinterpret_cast<const MatchSetupView *>(setup)->sides_08;
    for (int side = 0, payload_offset = 0;
         payload_offset < 0x28;
         payload_offset += 0x14, ++side, ++source) {
        saved->side_value_lo_00[side] = source->value_00;
        saved->side_byte_05_02[side] = source->byte_05;
        saved->payload_08[side] = source->payload_08;
        saved->side_byte_04_06[side] = source->byte_04;
        saved->side_byte_06_04[side] = source->byte_06;
        if (source->token_1c != 0) {
            saved->token_tag_30[side] = source->token_1c->tag_04;
            owner->retained_token_values_00[side] = source->token_1c->value_00;
        } else {
            owner->retained_token_values_00[side] = 0;
        }
    }

    const MatchSetupView *source_setup =
        reinterpret_cast<const MatchSetupView *>(setup);
    saved->tail_32 = source_setup->terminal_00;
    saved->tail_33 = source_setup->terminal_04;
    saved->tail_34 = source_setup->terminal_05;
    saved->tail_dword_38 = source_setup->terminal_dword_48;
    if (slot > owner->maximum_saved_slot_140) {
        owner->maximum_saved_slot_140 = slot;
    }
}

void BattleInputGate::load_battle_setup_slot(
    signed char slot,
    MatchSetup *setup)
{
    if (slot < 0) {
        return;
    }

    BattleInputGateSetupView *owner =
        reinterpret_cast<BattleInputGateSetupView *>(this);
    int count = 0;
    if (owner->slots_f4.begin_04 != 0) {
        count = owner->slots_f4.end_08 - owner->slots_f4.begin_04;
    }
    if (slot > count) {
        return;
    }

    FixedBattleSetupSlotView *saved =
        owner->slots_f4.select_slot_4275e0(slot);
    owner->loaded_slot_141 = slot;
    owner->selected_slot_104 = saved;
    MatchSetupSideView *destination =
        reinterpret_cast<MatchSetupView *>(setup)->sides_08;
    SavedTokenMetadata *metadata = owner->saved_tokens_d8;
    for (int side = 0, payload_offset = 0;
         payload_offset < 0x28;
         payload_offset += 0x14, ++side, ++destination, ++metadata) {
        destination->value_00 =
            static_cast<signed char>(saved->side_value_lo_00[side]);
        destination->byte_05 = saved->side_byte_05_02[side];
        destination->payload_08 = saved->payload_08[side];
        destination->byte_04 = saved->side_byte_04_06[side];
        destination->byte_06 = saved->side_byte_06_04[side];
        if ((owner->saved_token_mask_f0 & (1 << side)) != 0) {
            metadata->tag_04 = saved->token_tag_30[side];
            destination->token_1c =
                reinterpret_cast<SetupTokenInput *>(metadata);
        } else {
            destination->token_1c = 0;
        }
    }

    MatchSetupView *destination_setup =
        reinterpret_cast<MatchSetupView *>(setup);
    destination_setup->terminal_00 =
        static_cast<signed char>(saved->tail_32);
    destination_setup->terminal_04 = saved->tail_33;
    destination_setup->terminal_05 = saved->tail_34;
    destination_setup->terminal_dword_48 = saved->tail_dword_38;
}

} // namespace th105
