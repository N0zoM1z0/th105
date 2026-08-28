namespace th105 {

float __cdecl lookup_orientation_sine(int angle);

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

void FighterEmbeddedState3d0Runtime::step_4652f0()
{
    int previous = state_09c;
    if (previous < 0)
        return;

    switch (previous) {
    case 0: {
        float position =
            (lookup_orientation_sine(3 * counter_0a0) - 1.0f) * 480.0f - 64.0f;
        position_0a4 = position;
        if (side_098 == 1)
            position_0a4 = 640.0f - position;
        if (counter_0a0 == 30)
            state_09c = 1;
        break;
    }
    case 1:
        if (counter_0a0 == 0)
            state_09c = 2;
        break;
    case 2:
        if (alpha_0a8 != 0)
            alpha_0a8 -= 2;
        else
            state_09c = -1;
        color_004.set_color(
            (static_cast<unsigned>(alpha_0a8) << 24) | 0x00ffffffu);
        break;
    }

    if (previous == state_09c)
        ++counter_0a0;
    else
        counter_0a0 = 0;
}

void FighterEmbeddedState3d0Runtime::phase_4653f0()
{
    if (state_09c >= 0)
        color_004.apply(position_0a4, 32.0f);
}

} // namespace th105
