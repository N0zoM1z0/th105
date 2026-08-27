#include "ui/Title.hpp"
#include <list>
#include <string>
#include <string.h>

extern "C" const char profile_ui_effect_label[];

namespace th105 {

struct ResultSprite94 {
    virtual void slot_00();
    virtual void slot_04();
    virtual void slot_08();
    virtual void slot_0c();
    virtual void slot_10();
    virtual void set_texture(unsigned int handle, int x, int y, int width, int height);
    unsigned char reserved_004[0x90];
};

struct ResultEffectConfig128 {
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

struct ResultEffectOwner194 {
    void *field_000;
    void *field_004;
    void *field_008;
    ResultEffectConfig128 config_00c;
    unsigned char reserved_134[0x10];
    void *pixel_buffer_144;
    unsigned char reserved_148[0x0c];
    unsigned int *colors_154;
    unsigned int *allocated_colors_158;
    std::list<void *> payloads_15c;
    unsigned int packed_color_168;
    unsigned int field_16c;
    std::string text_170;
    unsigned int field_18c;
    unsigned int field_190;

    ResultEffectOwner194();
    ~ResultEffectOwner194();
    void configure(const ResultEffectConfig128 *config);
};

struct NetworkResultFinalizeLayout {
    void *vtable_000;
    char primary_text_004[0x20];
    char secondary_text_024[0x254];
    unsigned int texture_278;
    ResultSprite94 sprite_27c;
    ResultSprite94 sprite_310;
};

class NetworkSessionResultView {
public:
    void finalize_result_binding_44dcb0();
};

void NetworkSessionResultView::finalize_result_binding_44dcb0()
{
    NetworkResultFinalizeLayout *layout = reinterpret_cast<NetworkResultFinalizeLayout *>(this);
    ResultEffectOwner194 text_owner;
    ResultEffectConfig128 config;
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
    config.color_100[1] = 0xa0;
    config.color_100[2] = 0xff;
    config.color_100[3] = 0xa0;
    config.color_100[4] = 0xff;
    config.color_100[5] = 0xff;
    config.option_120 = 0;
    config.option_124 = 2;
    config.flag_111 = 1;
    text_owner.configure(&config);

    std::string text(layout->primary_text_004);
    text.append("<br><color FF8080>", 18);
    text.append(layout->secondary_text_024);
    text.append("</color>", 8);
    layout->texture_278 = g_title_resource_manager.create_text_texture(
        text.c_str(), &text_owner, 256, 64, 0, 0).value;
    layout->sprite_27c.set_texture(layout->texture_278, 0, 0, 256, 16);
    layout->sprite_310.set_texture(layout->texture_278, 0, 16, 256, 32);
}

}
