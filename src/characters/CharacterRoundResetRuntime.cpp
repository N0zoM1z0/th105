namespace th105 {

// The common Fighter prefix ends at +0x7A4.  Character vtable slot 17 resets
// the derived tail around the already-exact shared reset at 0x004776D0.
struct FighterResetBaseView {
    unsigned char unknown_000[0x138];
    float gravity_138;
    unsigned char unknown_13c[0x4ec];
    unsigned char flag_628;
    unsigned char unknown_629[0x17b];

    int reset_extended_state();
};

typedef char FighterResetBaseView_size[
    sizeof(FighterResetBaseView) == 0x7a4 ? 1 : -1];

struct ReimuRoundResetView : FighterResetBaseView {
    unsigned short counter_7a4;
    unsigned char unknown_7a6[2];
    float value_7a8;
    float value_7ac;
    float value_7b0;
    float value_7b4;
    float value_7b8;
    float value_7bc;
    float value_7c0;
    float value_7c4;
    unsigned short counter_7c8;
    unsigned short counter_7ca;
    unsigned short counter_7cc;

    int reset_character_state();
};

int ReimuRoundResetView::reset_character_state()
{
    gravity_138 = -6.0f;
    counter_7a4 = 0;
    counter_7c8 = 0;
    value_7a8 = 0.0f;
    counter_7ca = 0;
    value_7ac = 0.0f;
    counter_7cc = 0;
    value_7b0 = 0.0f;
    value_7b4 = 0.0f;
    value_7b8 = 0.0f;
    value_7bc = 0.0f;
    value_7c0 = 0.0f;
    value_7c4 = 0.0f;
    return reset_extended_state();
}

struct MarisaRoundResetView : FighterResetBaseView {
    unsigned short counter_7a4;
    unsigned short counter_7a6;
    unsigned short counter_7a8;
    unsigned char unknown_7aa[2];
    float value_7ac;
    float value_7b0;

    int reset_character_state();
};

int MarisaRoundResetView::reset_character_state()
{
    value_7ac = 0.0f;
    counter_7a4 = 0;
    value_7b0 = 0.0f;
    counter_7a6 = 0;
    counter_7a8 = 0;
    gravity_138 = -6.0f;
    return reset_extended_state();
}

struct SakuyaRoundResetView : FighterResetBaseView {
    unsigned short counter_7a4;
    unsigned short counter_7a6;

    int reset_character_state();
};

int SakuyaRoundResetView::reset_character_state()
{
    reset_extended_state();
    gravity_138 = -6.0f;
    counter_7a6 = 0;
    counter_7a4 = 0;
    return 0;
}

struct AliceRoundResetView : FighterResetBaseView {
    unsigned short counters_7a4[4];
    unsigned short counter_7ac;
    unsigned char unknown_7ae[2];
    float first_values_7b0[4];
    float second_values_7c0[4];
    unsigned char flag_7d0;
    unsigned char flags_7d1[4];

    int reset_character_state();
};

int AliceRoundResetView::reset_character_state()
{
    for (int index = 0; index < 4; ++index) {
        counters_7a4[index] = 0;
        first_values_7b0[index] = 0.0f;
        second_values_7c0[index] = 0.0f;
        flags_7d1[index] = 0;
    }
    counter_7ac = 0;
    flag_7d0 = 0;
    return reset_extended_state();
}

struct PatchouliRoundResetView : FighterResetBaseView {
    unsigned short counters_7a4[7];
    unsigned char unknown_7b2[2];
    float value_7b4;

    int reset_character_state();
};

int PatchouliRoundResetView::reset_character_state()
{
    gravity_138 = -6.0f;
    counters_7a4[0] = 0;
    value_7b4 = 0.0f;
    counters_7a4[1] = 0;
    counters_7a4[2] = 0;
    counters_7a4[3] = 0;
    counters_7a4[4] = 0;
    counters_7a4[5] = 0;
    counters_7a4[6] = 0;
    int result = reset_extended_state();
    flag_628 = 0;
    return result;
}

struct YoumuRoundResetView : FighterResetBaseView {
    unsigned value_7a4;
    unsigned char unknown_7a8[0x25];
    unsigned char flag_7cd;
    unsigned char unknown_7ce[0x16];
    unsigned char flag_7e4;
    unsigned char flag_7e5;
    unsigned short counters_7e6[4];
    unsigned char unknown_7ee[2];
    float values_7f0[3];
    unsigned char flag_7fc;

    int reset_character_state();
};

int YoumuRoundResetView::reset_character_state()
{
    gravity_138 = -6.0f;
    value_7a4 = 0;
    flag_7cd = 0;
    values_7f0[0] = 0.0f;
    flag_7e4 = 0;
    values_7f0[1] = 0.0f;
    flag_7e5 = 0;
    values_7f0[2] = 0.0f;
    counters_7e6[0] = 0;
    counters_7e6[1] = 0;
    counters_7e6[2] = 0;
    counters_7e6[3] = 0;
    flag_7fc = 0;
    return reset_extended_state();
}

struct YuyukoRoundResetView : FighterResetBaseView {
    unsigned values_7a4[4];

    int reset_character_state();
};

int YuyukoRoundResetView::reset_character_state()
{
    gravity_138 = -6.0f;
    values_7a4[0] = 0;
    values_7a4[1] = 0;
    values_7a4[2] = 0;
    values_7a4[3] = 0;
    return reset_extended_state();
}

struct SuikaRoundResetView : FighterResetBaseView {
    unsigned short counter_7a4;
    unsigned short counter_7a6;

    int reset_character_state();
};

int SuikaRoundResetView::reset_character_state()
{
    gravity_138 = -6.0f;
    reset_extended_state();
    counter_7a4 = 0;
    counter_7a6 = 0;
    return 0;
}

struct UdongeRoundResetView : FighterResetBaseView {
    unsigned short counter_7a4;
    unsigned short opacity_7a6;
    float scale_7a8;
    unsigned short counter_7ac;
    unsigned short counter_7ae;
    float value_7b0;
    float value_7b4;
    unsigned value_7b8;

    int reset_character_state();
};

int UdongeRoundResetView::reset_character_state()
{
    gravity_138 = -6.0f;
    counter_7a4 = 0;
    opacity_7a6 = 255;
    scale_7a8 = 1.0f;
    value_7b8 = 0;
    counter_7ac = 0;
    value_7b0 = 0.0f;
    counter_7ae = 0;
    value_7b4 = 0.0f;
    return reset_extended_state();
}

struct KomachiRoundResetView : FighterResetBaseView {
    unsigned short counter_7a4;
    unsigned char unknown_7a6[2];
    unsigned value_7a8;

    int reset_character_state();
};

int KomachiRoundResetView::reset_character_state()
{
    reset_extended_state();
    gravity_138 = -6.0f;
    counter_7a4 = 0;
    value_7a8 = 0;
    return 0;
}

// Remilia and Aya both point slot 17 at the same linker-folded body.
struct RemiliaAyaRoundResetView : FighterResetBaseView {
    int reset_character_state();
};

int RemiliaAyaRoundResetView::reset_character_state()
{
    gravity_138 = -6.0f;
    return reset_extended_state();
}

struct IkuRoundResetView : FighterResetBaseView {
    unsigned values_7a4[3];
    unsigned short counter_7b0;
    unsigned short counter_7b2;
    float value_7b4;

    int reset_character_state();
};

int IkuRoundResetView::reset_character_state()
{
    value_7b4 = 0.0f;
    counter_7b0 = 0;
    counter_7b2 = 0;
    values_7a4[0] = 0;
    values_7a4[1] = 0;
    values_7a4[2] = 0;
    return reset_extended_state();
}

struct TenshiRoundResetView : FighterResetBaseView {
    float prefix_values_7a4[8];
    float first_values_7c4[12];
    float second_values_7f4[12];
    float value_824;
    float value_828;
    unsigned char flag_82c;
    unsigned char unknown_82d;
    unsigned short counter_82e;
    unsigned short counter_830;
    unsigned char unknown_832[2];
    unsigned values_834[3];
    unsigned short counter_840;

    int reset_character_state();
};

int TenshiRoundResetView::reset_character_state()
{
    reset_extended_state();
    gravity_138 = -6.0f;
    prefix_values_7a4[0] = 0.0f;
    prefix_values_7a4[1] = 0.0f;
    prefix_values_7a4[2] = 0.0f;
    prefix_values_7a4[3] = 0.0f;
    prefix_values_7a4[4] = 0.0f;
    prefix_values_7a4[5] = 0.0f;
    prefix_values_7a4[6] = 0.0f;
    prefix_values_7a4[7] = 0.0f;
    for (int index = 0; index < 12; ++index) {
        first_values_7c4[index] = 0.0f;
        second_values_7f4[index] = 0.0f;
    }
    value_824 = 0.0f;
    value_828 = 0.0f;
    flag_82c = 0;
    counter_840 = 0;
    counter_82e = 0;
    counter_830 = 0;
    values_834[0] = 0;
    values_834[1] = 0;
    values_834[2] = 0;
    return 0;
}

} // namespace th105
