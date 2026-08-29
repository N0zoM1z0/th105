#include <stddef.h>
#include <stdlib.h>
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
typedef char fis_bind[offsetof(FighterInputRuntimeView,binding_6b0)==0x6b0?1:-1];
typedef char fis_fields[offsetof(FighterInputRuntimeView,field_6bc)==0x6bc?1:-1];
typedef char fis_edges[offsetof(FighterInputRuntimeView,edge_6f4)==0x6f4?1:-1];
typedef char source_count[offsetof(FighterInputStateView,counter_38)==0x38?1:-1];
void FighterInputRuntimeView::update_input_4631c0()
{
    FighterInputBindingView *binding = binding_6b0;
    if (!binding)
        return;

    FighterInputStateView *source = binding->source_00;
    source->update_04();

    unsigned old_6bc = field_6bc;
    unsigned old_6c0 = field_6c0;
    unsigned old_6c4 = field_6c4;
    unsigned old_6c8 = field_6c8;
    unsigned old_6cc = field_6cc;
    unsigned old_6d0 = field_6d0;

    field_6b4 = source->counter_38;
    field_6b8 = source->counter_3c;
    field_6bc = source->counter_40;
    field_6c0 = source->counter_44;
    field_6c4 = source->counter_48;
    field_6c8 = source->counter_4c;

    if (!binding_6b0->direct_04) {
        unsigned first = field_6bc;
        unsigned second = field_6c0;
        if (abs(static_cast<int>(first - second)) < 2) {
            if (first >= second)
                first = second;
            field_6cc = first;
        }

        unsigned third = field_6c4;
        if (abs(static_cast<int>(second - third)) < 2) {
            if (second >= third)
                second = third;
            field_6d0 = second;
        }

        unsigned next = field_6cc;
        if (next <= source->counter_50)
            next = source->counter_50;
        field_6cc = next;

        next = field_6d0;
        if (next <= source->counter_54)
            next = source->counter_54;
        field_6d0 = next;
    } else {
        field_6cc = source->counter_50;
        field_6d0 = source->counter_54;
    }

    if (field_6bc != 0 || old_6bc == 0)
        edge_6f4 = 0;
    else
        edge_6f4 = old_6bc;
    if (field_6c0 != 0 || old_6c0 == 0)
        edge_6f8 = 0;
    else
        edge_6f8 = old_6c0;
    if (field_6c4 != 0 || old_6c4 == 0)
        edge_6fc = 0;
    else
        edge_6fc = old_6c4;
    if (field_6c8 != 0 || old_6c8 == 0)
        edge_700 = 0;
    else
        edge_700 = old_6c8;
    if (field_6cc != 0 || old_6cc == 0)
        edge_704 = 0;
    else
        edge_704 = old_6cc;
    if (field_6d0 != 0 || old_6d0 == 0)
        edge_708 = 0;
    else
        edge_708 = old_6d0;
}
}
