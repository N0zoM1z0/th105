#include <stddef.h>
#include "battle/BattleObjectManagerRuntime.hpp"

namespace th105 {

struct FighterTextureHandleDequeView {
    unsigned char storage_00[0x14];
    int *entry_at_checked(int index);
};

struct FighterTextureStateView {
    void publish_texture_state(signed char texture_index, short duration);

    unsigned char unknown_000[0x170];
    FighterTextureStateView *other_fighter_170;
    unsigned char unknown_174[0x1c0];
    signed char player_index_334;
    unsigned char unknown_335[0x357];
    FighterTextureHandleDequeView texture_handles_68c;
    short texture_state_duration_6a0;
    signed char texture_index_6a2;
};

typedef char fighter_texture_other_offset[
    offsetof(FighterTextureStateView, other_fighter_170) == 0x170 ? 1 : -1];
typedef char fighter_texture_player_offset[
    offsetof(FighterTextureStateView, player_index_334) == 0x334 ? 1 : -1];
typedef char fighter_texture_handles_offset[
    offsetof(FighterTextureStateView, texture_handles_68c) == 0x68c ? 1 : -1];
typedef char fighter_texture_duration_offset[
    offsetof(FighterTextureStateView, texture_state_duration_6a0) == 0x6a0 ? 1 : -1];

void FighterTextureStateView::publish_texture_state(
    signed char texture_index,
    short duration)
{
    texture_index_6a2 = texture_index;

    if (other_fighter_170->texture_state_duration_6a0 != 0 ||
        texture_state_duration_6a0 != 0) {
        const unsigned handle = static_cast<unsigned>(
            *texture_handles_68c.entry_at_checked(texture_index));
        reinterpret_cast<unsigned *>(&g_battle_object_manager->texture_a_d8)
            [player_index_334] = handle;
        texture_state_duration_6a0 = duration;
        return;
    }

    g_battle_object_manager->texture_a_d8 =
        *texture_handles_68c.entry_at_checked(texture_index);
    g_battle_object_manager->texture_b_dc =
        *texture_handles_68c.entry_at_checked(texture_index_6a2);
    texture_state_duration_6a0 = duration;
}

} // namespace th105
