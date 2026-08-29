#include <stddef.h>
namespace th105 {
struct SharedEventStateSystemView {
    unsigned char set_target_20_enabled_2c(unsigned char enabled, float target);
    unsigned char reserved_01[0x0f];
    unsigned char set_target_28_enabled_2e(unsigned char enabled, float target);
};
extern SharedEventStateSystemView g_shared_event_state_system;
extern unsigned char g_stage_music_mode;
void __cdecl start_scene_fade_in(unsigned color, int duration);
void __cdecl start_scene_fade_out(unsigned color, int duration);
void __cdecl play_bgm(const char *path);

struct FighterEvent130SystemView {
    int trigger_global_effect(int value);
    void set_global_pair(float first, float second);
    void set_stage_music(int stage, int value);
};

class FighterSystemCommandView {
public:
    virtual void slot_00();
    virtual void slot_04();
    virtual void set_action(int action);
    virtual void slot_0c(int value);
    virtual void slot_10(); virtual void slot_14(); virtual void slot_18(); virtual void slot_1c();
    virtual void slot_20(); virtual void slot_24(); virtual void slot_28(); virtual void slot_2c();
    virtual void slot_30(); virtual void slot_34(); virtual void slot_38(); virtual void slot_3c();
    virtual void slot_40(); virtual void slot_44(); virtual void slot_48(); virtual void slot_4c();
    virtual void slot_50(); virtual void slot_54(); virtual void slot_58(); virtual void slot_5c();
    virtual unsigned char slot_60(int command);

    unsigned char reserved_004[0xe8];
    float field_ec;
    unsigned char reserved_f0[0x40];
    FighterEvent130SystemView event_130;
    unsigned char reserved_131[0x0b];
    unsigned short state_13c;
    unsigned short sequence_13e;
    unsigned char reserved_140[0x5f0];
    short value_730;
    unsigned char reserved_732[0x27];
    unsigned char flag_759;
    unsigned char reserved_75a[2];
    unsigned value_75c;
    unsigned value_760;
    unsigned char reserved_764[0x12];
    unsigned short flag_776;

    unsigned char set_shared_second_target_476ad0(unsigned char enabled, float target);
    unsigned char handle_system_command_4773a0(int command);
};

typedef char FighterSystemCommand_state[offsetof(FighterSystemCommandView,state_13c)==0x13c?1:-1];
typedef char FighterSystemCommand_v730[offsetof(FighterSystemCommandView,value_730)==0x730?1:-1];
typedef char FighterSystemCommand_f776[offsetof(FighterSystemCommandView,flag_776)==0x776?1:-1];

unsigned char FighterSystemCommandView::handle_system_command_4773a0(int command)
{
    switch (command) {
    case 100:
        field_ec = 1280.0f;
        set_action(700);
        return 0;
    case 150: {
        g_shared_event_state_system.set_target_20_enabled_2c(1, 640.0f);
        float value = static_cast<float>(value_730);
        set_shared_second_target_476ad0(1, value);
        g_shared_event_state_system.set_target_28_enabled_2e(1, 1.0f);
        set_action(799);
        return 0;
    }
    case 151:
        set_action(790);
        return 0;
    case 152:
        flag_776 = 1;
        return 0;
    case 153:
        event_130.trigger_global_effect(16);
        return 0;
    case 160:
        start_scene_fade_in(0xff000000u, 60);
        return 0;
    case 161:
        start_scene_fade_out(0xff000000u, 60);
        return 0;
    case 162:
        start_scene_fade_in(0xffffffffu, 60);
        return 0;
    case 163:
        start_scene_fade_out(0xffffffffu, 180);
        return 0;
    case 170:
        flag_759 = 1;
        value_75c = 0;
        value_760 = 120;
        return 0;
    case 171:
        flag_759 = 0;
        return 0;
    case 180:
        event_130.set_global_pair(0.0f, 0.0f);
        if (g_stage_music_mode == 6) {
            event_130.set_stage_music(5, 0);
            play_bgm("data/bgm/st05.ogg");
        }
        return 0;
    case 181:
        event_130.set_global_pair(0.0f, 0.0f);
        if (g_stage_music_mode == 6) {
            event_130.set_stage_music(10, 0);
            play_bgm("data/bgm/st05.ogg");
        }
        return 0;
    case 182:
        event_130.set_global_pair(0.0f, 0.0f);
        if (g_stage_music_mode == 6) {
            event_130.set_stage_music(0, 0);
            play_bgm("data/bgm/st05.ogg");
        }
        return 0;
    case 200:
        if (state_13c == 99 && sequence_13e == 2)
            return 0;
        return 1;
    case 201:
        set_action(99);
        slot_0c(3);
        return 0;
    case 202:
        return state_13c != 0;
    default:
        return slot_60(command);
    }
}
}
