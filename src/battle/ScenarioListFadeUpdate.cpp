#include "battle/ScenarioData.hpp"
// JP1.06a 0x00455850. Complete fade/update policy; source remains nonexact.
// Uses the shared scenario and list-entry owners. See docs/SCENARIO_LIST_FADE_2026_10_29.md.
#include <list>
#include <stddef.h>
namespace th105 {
void CScenarioData::update_list(std::list<ScenarioRenderEntry9C> *entries)
{
    std::list<ScenarioRenderEntry9C>::iterator it=entries->begin();
    while(it!=entries->end()) {
        if(it->delta_099>0) {
            if(it->alpha_098<255) {
                if(it->delta_099>255-it->alpha_098) it->alpha_098=255;
                else it->alpha_098+=it->delta_099;
            }
        } else {
            if(it->alpha_098 < -it->delta_099) {
                it=entries->erase(it);
                continue;
            }
            it->alpha_098+=it->delta_099;
        }
        if(it->resource_handle_000!=0)
            it->sprite_004.set_color((static_cast<unsigned>(it->alpha_098)<<24)|0x00ffffffu);
        else
            it->sprite_004.set_color(static_cast<unsigned>(it->alpha_098)<<24);
        ++it;
    }
}
}
