#pragma once

namespace th105 {

struct InfoLongSprite94 {
    virtual void slot_00();
    virtual void set_color(unsigned color);
    virtual void slot_08();
    virtual void slot_0c();
    virtual void slot_10();
    virtual void slot_14();
    virtual void slot_18();
    virtual void move_1c(float x, float y);

    unsigned char reserved_004[0x84];
    float scale_x_088;
    float scale_y_08c;
    unsigned char reserved_090[4];
};

typedef char InfoLongSprite94_size_must_be_0x94[
    sizeof(InfoLongSprite94) == 0x94 ? 1 : -1];

struct InfoLongRecord154Runtime {
    void *resource_000;
    InfoLongSprite94 primary_004;
    InfoLongSprite94 secondary_098;
    int timer_12c;
    unsigned char alpha_primary_130;
    unsigned char alpha_secondary_131;
    unsigned char mirrored_132;
    unsigned char reserved_133;
    float x_134;
    float y_138;
    float velocity_x_13c;
    float velocity_y_140;
    float scale_144;
    unsigned char reserved_148[4];
    unsigned char active_14c;
    unsigned char reserved_14d[3];
    int lifetime_150;

    void render_4325c0();
    void update_4327c0();
};

typedef char InfoLongRecord154Runtime_size_must_be_0x154[
    sizeof(InfoLongRecord154Runtime) == 0x154 ? 1 : -1];

} // namespace th105
