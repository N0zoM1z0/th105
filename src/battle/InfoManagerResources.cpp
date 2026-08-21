#include "InfoManagerResources.hpp"

namespace th105 {

int InfoManagerResourceView::load_info_effect_resources_46e960()
{
    effect_manager_04().load_resource("data/infoEffect/effect.pat", 0);
    return combo_design_100().load_combo_resources_46a8c0();
}

int InfoManagerResourceView::release_info_effect_resources_46e990()
{
    upper_design_98().release_design();
    lower_design_cc().release_design();
    combo_design_100().release_combo_resources_46a610();
    return effect_manager_04().release_resource();
}

} // namespace th105
