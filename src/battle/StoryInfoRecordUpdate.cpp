#include "battle/InfoManagerResources.hpp"
#include "ui/UiPrimitives.hpp"
#include "battle/Collision.hpp"
// Complete source, still nonexact; see docs/STORY_INFO_SOURCE_2026_11_03.md.
namespace th105 {
// These cells belong to the same Fighter installed by Story binding.
typedef char story_health_offset[offsetof(Fighter, health_174) == 0x174 ? 1 : -1];
typedef char story_maximum_offset[offsetof(Fighter, max_health_176) == 0x176 ? 1 : -1];
typedef char story_secondary_offset[offsetof(Fighter, value_47c) == 0x47c ? 1 : -1];
typedef char story_timer_offset[offsetof(Fighter, statistic_candidate_64c) == 0x64c ? 1 : -1];
typedef char story_duration_offset[offsetof(Fighter, post_advance_value_650) == 0x650 ? 1 : -1];
void BattleInfoRecordF8::update_story_471930()
{
    Fighter *fighter=story_fighter_1c;
    int target=fighter->health_174;
    int displayed=story_health_08;
    if(displayed<target){
        int next=displayed+fighter->max_health_176/120;
        if(next>=target)next=target;
        story_health_08=next;
    }else story_health_08=target;
    target=fighter->value_47c;
    displayed=gauge_0c;
    if(displayed>target){
        int next=displayed-fighter->max_health_176/120;
        if(next<=target)next=target;
        gauge_0c=next;
    }else gauge_0c=target;
    if(fighter->statistic_candidate_64c>=0){
        story_progress_10=static_cast<float>(fighter->statistic_candidate_64c/60.0);
        if(fighter->post_advance_value_650-fighter->statistic_candidate_64c>60 && fade_alpha_14<255)fade_alpha_14+=15;
        group_60[4]->set_color((static_cast<unsigned>(fade_alpha_14)<<24)|0x00ffffff);
        group_74[1]->set_color((static_cast<unsigned>(fade_alpha_14)<<24)|0x00ffffff);
        group_60[4]->enabled=true;
        group_74[1]->enabled=true;
        return;
    }
    if(fade_alpha_14){
        fade_alpha_14-=15;
        group_60[4]->set_color((static_cast<unsigned>(fade_alpha_14)<<24)|0x00ffffff);
        group_74[1]->set_color((static_cast<unsigned>(fade_alpha_14)<<24)|0x00ffffff);
        if(!fade_alpha_14){
            group_60[4]->enabled=false;
            group_74[1]->enabled=false;
        }
    }
}
}
