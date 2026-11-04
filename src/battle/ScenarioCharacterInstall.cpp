#include "battle/ScenarioData.hpp"
#include <utility>

namespace th105 {
void CScenarioData::install_character(
    std::string name, std::string text, int slot, int x, int y,
    unsigned char red, unsigned char green, unsigned char blue)
{
    CScenarioData &s = *this;
    const signed char side = static_cast<signed char>(slot);
    ScenarioTextEntryDC entry;
    entry.text_098 = text;
    entry.flag_0d4 = side;
    if (side > 0) {
        entry.sprite_004.scale_x_88 = -1.0f;
        entry.sprite_004.scale_y_8c = 1.0f;
        entry.flag_0d5 = -1;
        entry.value_0b8 = 640 - x;
    } else {
        entry.value_0b8 = x;
        entry.flag_0d5 = 1;
    }
    entry.flag_0b5 = red;
    entry.flag_0b6 = green;
    entry.value_0bc = 480 + y;
    entry.flag_0b7 = blue;
    s.text_entries_32c.insert(std::pair<std::string, ScenarioTextEntryDC>(name, entry));
    ScenarioEffectConfig128 *config = &s.effect_config_1fc;
    config->color_100[0] = 0xff;
    config->color_100[2] = 0xff;
    config->color_100[4] = 0xff;
    config->color_100[1] = entry.flag_0b5;
    config->color_100[3] = entry.flag_0b6;
    config->color_100[5] = entry.flag_0b7;
    s.effect_owner_068.configure(config);
}
} // namespace th105
