#pragma once

namespace th105 {

struct FighterInputStateView {
    virtual void slot_00();
    virtual void update_04();
    unsigned char unknown_04[0x34];
    unsigned counter_38;
    unsigned counter_3c;
    unsigned counter_40;
    unsigned counter_44;
    unsigned counter_48;
    unsigned counter_4c;
    unsigned counter_50;
    unsigned counter_54;
};
struct FighterInputBindingView {
    FighterInputStateView *source_00;
    unsigned char direct_04;
};
struct FighterInputRuntimeView {
    unsigned char unknown_000[0x6b0];
    FighterInputBindingView *binding_6b0;
    unsigned field_6b4;
    unsigned field_6b8;
    unsigned field_6bc;
    unsigned field_6c0;
    unsigned field_6c4;
    unsigned field_6c8;
    unsigned field_6cc;
    unsigned field_6d0;
    unsigned char unknown_6d4[0x20];
    unsigned edge_6f4;
    unsigned edge_6f8;
    unsigned edge_6fc;
    unsigned edge_700;
    unsigned edge_704;
    unsigned edge_708;
    void update_input_4631c0();
};
} // namespace th105
