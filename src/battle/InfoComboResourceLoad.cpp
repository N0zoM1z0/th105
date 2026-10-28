#include "ui/DesignBaseLifetime.hpp"
#include "ui/CNumberRuntime.hpp"

namespace th105 {
struct ComboNumberObject {
    UiDesignObject ui;
    CNumber number_18;
};
struct InfoComboLoadView : CDesignBase {
    unsigned char unknown_34[0x10];
    UiDesignObject *items_44[6];
    int value_5c,value_60;
    float value_64;
    int value_68;
    void load_combo_46a8c0();
};
typedef char combo_number_offset[offsetof(ComboNumberObject,number_18)==0x18?1:-1];
typedef char combo_load_value_offset[offsetof(InfoComboLoadView,value_5c)==0x5c?1:-1];

void InfoComboLoadView::load_combo_46a8c0()
{
    load("data/battle/combo.dat");
    UiDesignObject *found;
    find_object(&found,1000);
    {
        ComboNumberObject *object=reinterpret_cast<ComboNumberObject *>(found);
        object->number_18.bind_value(&value_5c);
        object->ui.enabled=true;
    }
    find_object(&found,1001);
    {
        ComboNumberObject *object=reinterpret_cast<ComboNumberObject *>(found);
        object->number_18.bind_value(&value_64);
        object->ui.enabled=true;
    }
    find_object(&found,1002);
    {
        ComboNumberObject *object=reinterpret_cast<ComboNumberObject *>(found);
        object->number_18.bind_value(&value_68);
        object->ui.enabled=true;
    }
    find_object(&found,1003);
    {
        ComboNumberObject *object=reinterpret_cast<ComboNumberObject *>(found);
        object->number_18.bind_value(&value_60);
        object->ui.enabled=true;
    }
    find_object(&items_44[0],2103);
    find_object(&items_44[1],2104);
    find_object(&items_44[2],2105);
    find_object(&items_44[3],2100);
    find_object(&items_44[4],2101);
    find_object(&items_44[5],2102);
}
}
