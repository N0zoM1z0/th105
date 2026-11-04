#include "battle/ScenarioData.hpp"
#include <utility>

namespace th105 {
void CScenarioData::install_character(
    std::string name, std::string text, signed char slot, int x, int y,
    unsigned char red, unsigned char green, unsigned char blue)
{
    CScenarioData &s = *this;
    ScenarioTextEntryDC entry;
    entry.text_098 = text;
    entry.flags_0d4[0] = slot;
    if (slot > 0) {
        entry.sprite_004.scale_x_88 = -1.0f;
        entry.sprite_004.scale_y_8c = 1.0f;
        entry.flags_0d4[1] = -1;
        entry.values_0b8[0] = 640 - x;
    } else {
        entry.values_0b8[0] = x;
        entry.flags_0d4[1] = 1;
    }
    entry.flags_0b4[1] = red;
    entry.flags_0b4[2] = green;
    entry.values_0b8[1] = 480 + y;
    entry.flags_0b4[3] = blue;
    s.text_entries_32c.insert(std::pair<std::string, ScenarioTextEntryDC>(name, entry));
    ScenarioEffectConfig128 *config = &s.effect_config_1fc;
    config->color_100[0] = 0xff;
    config->color_100[2] = 0xff;
    config->color_100[4] = 0xff;
    config->color_100[1] = entry.flags_0b4[1];
    config->color_100[3] = entry.flags_0b4[2];
    config->color_100[5] = entry.flags_0b4[3];
    s.effect_owner_068.configure(config);
}
} // namespace th105
