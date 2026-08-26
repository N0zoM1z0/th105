#pragma once

#include <deque>
#include <stddef.h>

namespace th105 {

struct Fighter;

struct InfoComboEntry {
    float value_00;
    int timer_04;
    unsigned char item_index_08;
    unsigned char reserved_09[3];
};

struct InfoComboUiObject {
    void *vtable_00;
    float x_04;
    float y_08;
    unsigned char reserved_0c[8];
    unsigned char enabled_14;
};

class InfoComboResourceRuntimeView {
public:
    virtual void slot_00();
    virtual void set_color_04(unsigned int color);
    virtual void slot_08();
    virtual void slot_0c();
    virtual void slot_10();
    virtual void slot_14();
    virtual void slot_18();
    virtual void move_1c(float x, float y);

    unsigned char reserved_04[0x40];
    InfoComboUiObject *items_44[6];
    int value_5c;
    int value_60;
    float value_64;
    int value_68;

    void render_combo_46a660(
        float x,
        float y,
        Fighter *fighter,
        std::deque<InfoComboEntry> *entries);
};

struct InfoShortRecord34Runtime {
    InfoComboResourceRuntimeView *combo_00;
    Fighter *fighter_04;
    float x_08;
    float y_0c;
    int previous_value_10;
    int timer_14;
    int progress_18;
    unsigned char active_mask_1c;
    unsigned char reserved_1d[3];
    std::deque<InfoComboEntry> entries_20;

    void update_46ac30();
    void render_46a800();
};

typedef char InfoComboEntry_size_must_be_0x0c[
    sizeof(InfoComboEntry) == 0x0c ? 1 : -1];
typedef char InfoComboResourceRuntimeView_size_must_be_0x6c[
    sizeof(InfoComboResourceRuntimeView) == 0x6c ? 1 : -1];
typedef char InfoShortRecord34Runtime_size_must_be_0x34[
    sizeof(InfoShortRecord34Runtime) == 0x34 ? 1 : -1];
typedef char InfoShortRecord34Runtime_entries_offset_must_be_0x20[
    offsetof(InfoShortRecord34Runtime, entries_20) == 0x20 ? 1 : -1];

} // namespace th105
