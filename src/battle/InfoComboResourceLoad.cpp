#include "InfoComboRuntime.hpp"

namespace th105 {
void InfoComboResourceRuntimeView::load_combo_46a8c0()
{
    design_00.load("data/battle/combo.dat");
    UiDesignObject *found;
    design_00.bind_object_alt(&found,1000);
    {
        CDesignNumber *object=reinterpret_cast<CDesignNumber *>(found);
        object->number_18.bind_value(&value_5c);
        object->enabled_14=true;
    }
    design_00.bind_object_alt(&found,1001);
    {
        CDesignNumber *object=reinterpret_cast<CDesignNumber *>(found);
        object->number_18.bind_value(&value_64);
        object->enabled_14=true;
    }
    design_00.bind_object_alt(&found,1002);
    {
        CDesignNumber *object=reinterpret_cast<CDesignNumber *>(found);
        object->number_18.bind_value(&value_68);
        object->enabled_14=true;
    }
    design_00.bind_object_alt(&found,1003);
    {
        CDesignNumber *object=reinterpret_cast<CDesignNumber *>(found);
        object->number_18.bind_value(&value_60);
        object->enabled_14=true;
    }
    design_00.bind_object_alt(reinterpret_cast<UiDesignObject **>(&items_44[0]),2103);
    design_00.bind_object_alt(reinterpret_cast<UiDesignObject **>(&items_44[1]),2104);
    design_00.bind_object_alt(reinterpret_cast<UiDesignObject **>(&items_44[2]),2105);
    design_00.bind_object_alt(reinterpret_cast<UiDesignObject **>(&items_44[3]),2100);
    design_00.bind_object_alt(reinterpret_cast<UiDesignObject **>(&items_44[4]),2101);
    design_00.bind_object_alt(reinterpret_cast<UiDesignObject **>(&items_44[5]),2102);
}
}
