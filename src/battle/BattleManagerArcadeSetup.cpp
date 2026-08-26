#include "battle/BattleManagerArcade.hpp"
#include "battle/GameMode.hpp"
#include "config/ScoreData.hpp"
#include "input/InputSelection.hpp"

#include <deque>
#include <list>

namespace th105 {

int __cdecl selector_random_roll(int limit);
unsigned char __cdecl get_stage_for_character(int character_key);
unsigned char __cdecl get_bgm_for_character(int character_key);
extern unsigned char g_round_counter;
unsigned char __cdecl start_async_engine_scene_load(int scene);

struct PlayerSlotRecordArcadeSetupView {
    void configure_character_payload_431e80(
        unsigned char *payload,
        int character_key);
};

struct ScoreDataArcadeSetupView {
    unsigned char *bytes()
    {
        return reinterpret_cast<unsigned char *>(this);
    }

    unsigned &flags_04()
    {
        return *reinterpret_cast<unsigned *>(bytes() + 0x04);
    }

    unsigned char extra_character_13_3d() const
    {
        return *(reinterpret_cast<const unsigned char *>(this) + 0x3d);
    }

    unsigned char extra_character_14_3e() const
    {
        return *(reinterpret_cast<const unsigned char *>(this) + 0x3e);
    }
};



void CBattleManagerArcade::finalize_arcade_round_473110()
{
    std::list<int> &opponents = *reinterpret_cast<std::list<int> *>(
        reinterpret_cast<unsigned char *>(this) + 0x5b4);
    if (opponents.empty())
        return;

    const int character = opponents.front();
    MatchSetup *setup = get_match_setup();
    setup->sides_08[1].character_key_00 = character;
    if (setup->sides_08[0].character_key_00 == character)
        setup->sides_08[1].fighter_option_05 =
            setup->sides_08[0].fighter_option_05 == 0;
    else
        setup->sides_08[1].fighter_option_05 = 0;

    if ((reinterpret_cast<ScoreDataArcadeSetupView *>(get_score_data())
            ->flags_04() & 0x100) != 0) {
        if (setup->sides_08[0].character_key_00 == 6) {
            setup->stage_04 = static_cast<signed char>(
                selector_random_roll(2) ? 14 : 16);
            setup->bgm_id_05 = static_cast<signed char>(
                get_bgm_for_character(character));
        } else {
            setup->stage_04 = static_cast<signed char>(
                get_stage_for_character(character));
            setup->bgm_id_05 = static_cast<signed char>(
                get_bgm_for_character(character));
        }
    } else {
        switch (*reinterpret_cast<unsigned *>(
            reinterpret_cast<unsigned char *>(this) + 0x5c0)) {
        case 0:
        case 1:
            setup->stage_04 = 0;
            setup->bgm_id_05 = 0;
            break;
        case 2:
        case 3:
            setup->stage_04 = 1;
            setup->bgm_id_05 = 1;
            break;
        case 4:
        case 5:
            setup->stage_04 = 2;
            setup->bgm_id_05 = 2;
            break;
        case 6:
            setup->stage_04 = 3;
            setup->bgm_id_05 = 3;
            break;
        case 7:
            setup->stage_04 = 4;
            setup->bgm_id_05 = 4;
            break;
        case 8:
            setup->stage_04 = 5;
            setup->bgm_id_05 = 5;
            break;
        default:
            break;
        }

        if (setup->sides_08[0].character_key_00 == 6 ||
            setup->sides_08[1].character_key_00 == 6)
            setup->stage_04 = 16;
    }

    reinterpret_cast<PlayerSlotRecordArcadeSetupView *>(
        get_player_slot_record(1))
        ->configure_character_payload_431e80(
            setup->sides_08[1].input_payload_08, character);
    start_async_engine_scene_load(4);
}

void CBattleManagerArcade::prepare_battle_setup_472110(MatchSetup *setup)
{
    setup->sides_08[1].fighter_option_05 = 0;

    std::deque<int> available;
    for (int character = 0; character < 13; ++character) {
        if (character != setup->sides_08[0].character_key_00) {
            int value = character;
            available.push_back(value);
        }
    }

    std::list<int> &opponents = *reinterpret_cast<std::list<int> *>(
        reinterpret_cast<unsigned char *>(this) + 0x5b4);
    opponents.clear();

    for (int count = 0; count < 7; ++count) {
        unsigned index = selector_random_roll(available.size());
        opponents.push_back(available[index]);
        available.erase(available.begin() + index);
    }

    if (reinterpret_cast<ScoreDataArcadeSetupView *>(get_score_data())
            ->extra_character_13_3d())
        opponents.push_back(13);
    if (reinterpret_cast<ScoreDataArcadeSetupView *>(get_score_data())
            ->extra_character_14_3e())
        opponents.push_back(14);

    setup->sides_08[1].character_key_00 = opponents.front();
    opponents.erase(opponents.begin());

    reinterpret_cast<PlayerSlotRecordArcadeSetupView *>(
        get_player_slot_record(1))
        ->configure_character_payload_431e80(
            setup->sides_08[1].input_payload_08,
            setup->sides_08[1].character_key_00);

    if ((reinterpret_cast<ScoreDataArcadeSetupView *>(get_score_data())
            ->flags_04() & 0x100) != 0) {
        if (setup->sides_08[0].character_key_00 == 6) {
            setup->stage_04 = static_cast<signed char>(
                selector_random_roll(2) ? 14 : 16);
        } else {
            setup->stage_04 = static_cast<signed char>(
                get_stage_for_character(setup->sides_08[1].character_key_00));
        }
        setup->bgm_id_05 = static_cast<signed char>(
            get_bgm_for_character(setup->sides_08[1].character_key_00));
    } else {
        setup->stage_04 = 0;
        setup->bgm_id_05 = 0;
        if (setup->sides_08[0].character_key_00 == 6 ||
            setup->sides_08[1].character_key_00 == 6) {
            setup->stage_04 = 16;
        }
    }

    *reinterpret_cast<unsigned *>(
        reinterpret_cast<unsigned char *>(this) + 0x5c0) = 1;
    fade_transition_pending_5c4() = 0;
    g_round_counter = 0;
    CBattleManager::prepare_battle_setup_472110(setup);
}

} // namespace th105
