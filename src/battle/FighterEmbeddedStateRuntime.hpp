#pragma once

namespace th105 {

struct FighterEmbeddedColorView {
    virtual void slot_00();
    virtual void set_color(unsigned color);
    virtual void slot_08();
    virtual void slot_0c();
    virtual void slot_10();
    virtual void slot_14();
    virtual void slot_18();
    virtual void apply(float value, float scale);
};

struct FighterEmbeddedState3d0Runtime {
    unsigned char reserved_000[4];
    FighterEmbeddedColorView color_004;
    unsigned char reserved_008[0x90];
    int side_098;
    int state_09c;
    int counter_0a0;
    float position_0a4;
    unsigned char alpha_0a8;

    void step_4652f0();
    void phase_4653f0();
};

} // namespace th105
