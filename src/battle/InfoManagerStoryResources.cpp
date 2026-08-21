#include "InfoManagerResources.hpp"

namespace th105 {

void InfoManagerResourceView::initialize_story_info_resources_471e50()
{
    load_info_effect_resources_46e960();

    InfoDesignResourceSubobject *upper = &upper_design_98();
    upper->load_design("data/battle/battleUpperStory.dat");

    InfoDesignResourceSubobject *lower = &lower_design_cc();
    lower->load_design("data/battle/battleUnderStory.dat");

    InfoEffectManagerSubobject *effect = &effect_manager_04();
    battle_records_498()[0].initialize_46fd20(0, upper, lower, effect);
    battle_records_498()[1].initialize_story_471c10(upper, lower, effect);
}

} // namespace th105
