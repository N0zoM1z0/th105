#include "MenuSelect.hpp"
#include "Title.hpp"

#include <list>
#include <string>
#include <string.h>

extern "C" const char profile_ui_effect_label[];

namespace th105 {

struct PlayerSlotSprite94 {
    virtual void slot_00();
    virtual void slot_04();
    virtual void slot_08();
    virtual void slot_0c();
    virtual void slot_10();
    virtual void set_texture(
        unsigned int handle, int x, int y, int width, int height);

    unsigned char reserved_004[0x90];
};

typedef char PlayerSlotSprite94_size_must_be_0x94[
    sizeof(PlayerSlotSprite94) == 0x94 ? 1 : -1];

struct PlayerSlotColorLayout {
    unsigned int texture_000;
    PlayerSlotSprite94 sprite_004;
    std::string string_098;
    std::string string_0b4;
};

typedef char PlayerSlotColorLayout_string_098_offset_must_be_0x98[
    offsetof(PlayerSlotColorLayout, string_098) == 0x98 ? 1 : -1];
typedef char PlayerSlotColorLayout_string_0b4_offset_must_be_0xb4[
    offsetof(PlayerSlotColorLayout, string_0b4) == 0xB4 ? 1 : -1];

struct ProfileSlotEffectConfig {
    char text_000[256];
    unsigned char color_100[6];
    unsigned char alignment_106[2];
    int count_108;
    int duration_10c;
    unsigned char flag_110;
    unsigned char flag_111;
    unsigned char flag_112;
    unsigned char alignment_113;
    int interval_114;
    int mode_118;
    int state_11c;
    int option_120;
    int option_124;
};

typedef char ProfileSlotEffectConfig_size_must_be_0x128[
    sizeof(ProfileSlotEffectConfig) == 0x128 ? 1 : -1];

struct ProfileSlotEffectOwner194 {
    void *field_000;
    void *field_004;
    void *field_008;
    ProfileSlotEffectConfig config_00c;
    unsigned char reserved_134[0x10];
    void *pixel_buffer_144;
    unsigned char reserved_148[0x0C];
    unsigned int *colors_154;
    unsigned int *allocated_colors_158;
    std::list<void *> payloads_15c;
    unsigned int packed_color_168;
    unsigned int field_16c;
    std::string text_170;
    unsigned int field_18c;
    unsigned int field_190;

    ProfileSlotEffectOwner194();
    ~ProfileSlotEffectOwner194();
    void configure(const ProfileSlotEffectConfig *config);
};

typedef char ProfileSlotEffectOwner194_size_must_be_0x194[
    sizeof(ProfileSlotEffectOwner194) == 0x194 ? 1 : -1];

void PlayerSlotRecord::set_profile_color(
    unsigned char red,
    unsigned char green,
    unsigned char blue)
{
    PlayerSlotColorLayout *slot =
        reinterpret_cast<PlayerSlotColorLayout *>(this);

    ProfileSlotEffectOwner194 text_owner;
    ProfileSlotEffectConfig config;
    config.duration_10c = 400;
    config.flag_110 = 0;
    config.flag_111 = 0;
    config.flag_112 = 0;
    config.option_120 = 0;
    config.option_124 = 0;
    config.mode_118 = 0;
    config.state_11c = 0;
    config.interval_114 = 100000;
    strcpy_s(config.text_000, 256, profile_ui_effect_label);
    config.count_108 = 14;
    config.duration_10c = 300;
    config.color_100[0] = 0xff;
    config.color_100[1] = red;
    config.color_100[2] = 0xff;
    config.color_100[3] = green;
    config.color_100[4] = 0xff;
    config.color_100[5] = blue;
    config.option_120 = 0;
    config.option_124 = 2;
    config.flag_111 = 1;
    text_owner.configure(&config);

    g_title_resource_manager.release_title_resource_handle(slot->texture_000);
    slot->texture_000 =
        g_title_resource_manager.create_text_texture(
            slot->string_0b4.c_str(), &text_owner, 256, 64, 0, 0).value;
    slot->sprite_004.set_texture(slot->texture_000, 0, 0, 256, 32);
}

} // namespace th105
