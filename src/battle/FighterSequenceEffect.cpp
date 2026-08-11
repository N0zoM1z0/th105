#include <stddef.h>

namespace th105 {

namespace {

class SequenceEffectColor {
public:
    virtual ~SequenceEffectColor() {}
    virtual int set_color(unsigned color);
};

struct FighterSequenceEffect {
    void *unknown_00;
    SequenceEffectColor color_04;
    unsigned char unknown_08[0x94];
    int reset_count_9c;
    int reset_count_a0;
    float reset_y_a4;
    unsigned char reset_alpha_a8;

    int reset_and_set_color();
};

typedef char FighterSequenceEffect_color_offset_must_be_4[
    offsetof(FighterSequenceEffect, color_04) == 0x04 ? 1 : -1];
typedef char FighterSequenceEffect_reset_count_offset_must_be_9c[
    offsetof(FighterSequenceEffect, reset_count_9c) == 0x9c ? 1 : -1];
typedef char FighterSequenceEffect_reset_y_offset_must_be_a4[
    offsetof(FighterSequenceEffect, reset_y_a4) == 0xa4 ? 1 : -1];
typedef char FighterSequenceEffect_reset_alpha_offset_must_be_a8[
    offsetof(FighterSequenceEffect, reset_alpha_a8) == 0xa8 ? 1 : -1];

int FighterSequenceEffect::reset_and_set_color()
{
    reset_count_9c = 0;
    reset_y_a4 = -640.0f;
    reset_count_a0 = 0;
    reset_alpha_a8 = 0x80;
    return color_04.set_color(0x80ffffff);
}

} // namespace

} // namespace th105
