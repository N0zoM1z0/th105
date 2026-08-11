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
    if (slot > static_cast<signed char>(
                   owner->slots_f4.begin_04 != 0
                       ? owner->slots_f4.end_08 - owner->slots_f4.begin_04
                       : 0)) {
        return;
    }

    owner->selected_slot_104 = owner->slots_f4.select_slot_4275e0(slot);
    int side = 0;
    int payload_offset = 0;
    const unsigned char *source =
        reinterpret_cast<const unsigned char *>(setup) + 0x0d;
    for (; payload_offset < 0x28;
         payload_offset += 0x14, ++side, source += 0x20) {
        reinterpret_cast<unsigned char *>(owner->selected_slot_104)[side] =
            source[-5];
        reinterpret_cast<unsigned char *>(owner->selected_slot_104)[side + 2] =
            source[0];
        *reinterpret_cast<SidePayloadView *>(
            reinterpret_cast<unsigned char *>(owner->selected_slot_104) +
            payload_offset + 8) =
            *reinterpret_cast<const SidePayloadView *>(source + 3);
        reinterpret_cast<unsigned char *>(owner->selected_slot_104)[side + 6] =
            source[-1];
        reinterpret_cast<unsigned char *>(owner->selected_slot_104)[side + 4] =
            source[1];
        if (*reinterpret_cast<SetupTokenInput *const *>(source + 0x17) != 0) {
            reinterpret_cast<unsigned char *>(owner->selected_slot_104)
                [side + 0x30] =
                (*reinterpret_cast<SetupTokenInput *const *>(source + 0x17))
                    ->tag_04;
            owner->retained_token_values_00[side] =
                (*reinterpret_cast<SetupTokenInput *const *>(source + 0x17))
                    ->value_00;
        } else {
            owner->retained_token_values_00[side] = 0;
        }
    }

    owner->selected_slot_104->tail_32 =
        *reinterpret_cast<const unsigned char *>(setup);
    owner->selected_slot_104->tail_33 =
        *(reinterpret_cast<const unsigned char *>(setup) + 4);
    owner->selected_slot_104->tail_34 =
        *(reinterpret_cast<const unsigned char *>(setup) + 5);
    owner->selected_slot_104->tail_dword_38 =
        *reinterpret_cast<const unsigned *>(
            reinterpret_cast<const unsigned char *>(setup) + 0x48);
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
    FixedSlotStoreView *slots = &owner->slots_f4;
    if (slot > static_cast<signed char>(
                   slots->begin_04 != 0
                       ? slots->end_08 - slots->begin_04
                       : 0)) {
        return;
    }

    owner->selected_slot_104 = slots->select_slot_4275e0(slot);
    owner->loaded_slot_141 = slot;
    unsigned char *destination =
        reinterpret_cast<unsigned char *>(setup) + 0x0d;
    SavedTokenMetadata *metadata = owner->saved_tokens_d8;
    for (int side = 0, payload_offset = 0;
         payload_offset < 0x28;
         payload_offset += 0x14, ++side, destination += 0x20, ++metadata) {
        *reinterpret_cast<int *>(destination - 5) =
            static_cast<signed char>(
                reinterpret_cast<unsigned char *>(owner->selected_slot_104)
                    [side]);
        destination[0] =
            reinterpret_cast<unsigned char *>(owner->selected_slot_104)
                [side + 2];
        *reinterpret_cast<SidePayloadView *>(destination + 3) =
            *reinterpret_cast<SidePayloadView *>(
                reinterpret_cast<unsigned char *>(owner->selected_slot_104) +
                payload_offset + 8);
        destination[-1] =
            reinterpret_cast<unsigned char *>(owner->selected_slot_104)
                [side + 6];
        destination[1] =
            reinterpret_cast<unsigned char *>(owner->selected_slot_104)
                [side + 4];
        if ((owner->saved_token_mask_f0 & (1 << side)) != 0) {
            metadata->tag_04 =
                reinterpret_cast<unsigned char *>(owner->selected_slot_104)
                    [side + 0x30];
            *reinterpret_cast<SetupTokenInput **>(destination + 0x17) =
                ((owner->saved_token_mask_f0 & (1 << side)) != 0)
                    ? reinterpret_cast<SetupTokenInput *>(metadata)
                    : 0;
        } else {
            *reinterpret_cast<SetupTokenInput **>(destination + 0x17) = 0;
        }
    }

    *reinterpret_cast<int *>(setup) = static_cast<signed char>(
        owner->selected_slot_104->tail_32);
    *(reinterpret_cast<unsigned char *>(setup) + 4) =
        owner->selected_slot_104->tail_33;
    *(reinterpret_cast<unsigned char *>(setup) + 5) =
        owner->selected_slot_104->tail_34;
    *reinterpret_cast<unsigned *>(
        reinterpret_cast<unsigned char *>(setup) + 0x48) =
        owner->selected_slot_104->tail_dword_38;
}

} // namespace th105
