#include "battle/EffectSprite.hpp"
#include <stddef.h>
namespace th105 {
struct InfoVisualManagerView {
    unsigned char prefix_000[0x494];
    int transition_494;
};
extern InfoVisualManagerView *g_info_visual_manager;
float __cdecl lookup_orientation_cosine(int);
struct InfoEffectVisualView {
    unsigned primary_000;
    CEffectSprite sprite_004;
    unsigned owner_130;
    unsigned char absolute_134;
    unsigned char unknown_135[7];
    short action_13c;
    unsigned char unknown_13e[0x32];
    float transition_factor_170;
    float fade_latch_174;
    void prepare_render_transform();
    void dispatch_indexed_event_member(unsigned);
    void transform();
    void initialize_action();
    unsigned char &alpha() { return reinterpret_cast<unsigned char *>(&sprite_004.color_10c)[3]; }
};
typedef char InfoVisual_action_offset[offsetof(InfoEffectVisualView,action_13c)==0x13c?1:-1];
typedef char InfoVisual_factor_offset[offsetof(InfoEffectVisualView,transition_factor_170)==0x170?1:-1];
void InfoEffectVisualView::transform()
{
    prepare_render_transform();
    float shift = static_cast<float>((1.0-lookup_orientation_cosine(3*g_info_visual_manager->transition_494))*200.0*transition_factor_170);
    sprite_004.translate(0.0f, shift, 0.0f);
}
void InfoEffectVisualView::initialize_action()
{
    if (action_13c >= 900) transition_factor_170=0.0f;
    else if (action_13c >= 100) transition_factor_170=-1.0f;
    else if (action_13c < 30 && action_13c >= 10) transition_factor_170=0.0f;
    else transition_factor_170=1.0f;
    absolute_134=1;
    switch(action_13c) {
    case 10: case 11: case 12: case 13:
        sprite_004.reset_one_11c=sprite_004.reset_one_118=2.0f; break;
    case 15: case 16: case 17: case 18:
        sprite_004.reset_one_11c=sprite_004.reset_one_118=0.5f; break;
    case 20: alpha()=128; break;
    case 22: dispatch_indexed_event_member(44); break;
    case 32: sprite_004.reset_zero_104=20.0f; sprite_004.reset_zero_108=-33.0f; break;
    case 100: case 110: case 120: case 130: case 140: case 150: case 160: case 170: case 180: case 190: case 200: case 210: case 220: case 230: case 240: case 250: case 260:
        alpha()=0; fade_latch_174=0.0f; break;
    case 101: case 111: case 121: case 131: case 141: case 151: case 161: case 171: case 181: case 191: case 201: case 211: case 221: case 231: case 241: case 251: case 261:
        alpha()=0; fade_latch_174=0.0f; break;
    case 102: case 112: case 122: case 132: case 142: case 152: case 162: case 172: case 182: case 192: case 202: case 212: case 222: case 232: case 242: case 252: case 262:
        fade_latch_174=0.0f; break;
    case 103: case 113: case 123: case 133: case 143: case 153: case 163: case 173: case 183: case 193: case 203: case 213: case 223: case 233: case 243: case 253: case 263:
        sprite_004.reset_one_11c=sprite_004.reset_one_118=4.0f; alpha()=0; fade_latch_174=0.0f; break;
    case 104: case 114: case 124: case 134: case 144: case 154: case 164: case 174: case 184: case 194: case 204: case 214: case 224: case 234: case 244: case 254: case 264:
        sprite_004.reset_one_11c=sprite_004.reset_one_118=4.0f; alpha()=0; fade_latch_174=0.0f; break;
    case 105: case 115: case 125: case 135: case 145: case 155: case 165: case 175: case 185: case 195: case 205: case 215: case 225: case 235: case 245: case 255: case 265:
        fade_latch_174=0.0f; alpha()=0; sprite_004.reset_one_11c=sprite_004.reset_one_118=5.0f; break;
    case 30: case 31: case 270: case 273: alpha()=0; break;
    default: break;
    }
}
}
