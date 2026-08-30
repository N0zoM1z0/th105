#include "battle/GameMode.hpp"
#include "ui/Title.hpp"
#include "ui/UiPrimitives.hpp"

#include <string>

namespace th105 {

class CMenuEnd {
public:
    void initialize_runtime_4404f0();
};

struct ScoreDataEndView {
    bool select_story_display_name(int character_key, std::string *output);
    void persist_story_progress_42d3f0();
};

ScoreDataEndView *__cdecl get_score_data_end_view();
int __cdecl selector_random_roll(int limit);

extern unsigned char g_round_counter;
extern unsigned int g_profile_back_texture;
extern unsigned char g_profile_text_config[];
extern UiTileA4 g_profile_tile_end_view;

void CMenuEnd::initialize_runtime_4404f0()
{
    g_title_resource_manager.release_title_resource_handle(
        g_profile_back_texture);

    int character_keys[2];
    switch (get_game_mode()) {
    case 0:
    case 1:
    case 2:
    case 4:
        character_keys[0] = character_keys[1] =
            get_match_setup()->sides_08[0].character_key_00;
        break;
    case 3:
        character_keys[0] = get_match_setup()->sides_08[0].character_key_00;
        character_keys[1] = get_match_setup()->sides_08[1].character_key_00;
        break;
    case 5:
        character_keys[0] = character_keys[1] =
            get_match_setup()->sides_08[1].character_key_00;
        break;
    default:
        break;
    }

    std::string name;
    std::string text;
    int index = 0;
    if (static_cast<signed char>(g_round_counter) > 0) {
        do {
            if (index >= 32)
                break;
            if (get_score_data_end_view()->select_story_display_name(
                    character_keys[selector_random_roll(2)], &name)) {
                text.append(name + "<br>", 0, static_cast<unsigned int>(-1));
            }
            ++index;
        } while (index < static_cast<signed char>(g_round_counter));
    }

    unsigned int handle = g_title_resource_manager.create_text_texture(
        text.c_str(), g_profile_text_config, 512, 512, 0, 0).value;
    g_profile_back_texture = handle;
    g_profile_tile_end_view.set_texture(handle, 0, 0, 512, 16);
    get_score_data_end_view()->persist_story_progress_42d3f0();
}

} // namespace th105
