#include "battle/InfoManagerResources.hpp"
#include "ui/UiPrimitives.hpp"
// Complete unselected candidate; docs/STORY_INFO_UPDATE_2026_10_28.md.
namespace th105 {
struct StoryInfoFighterView {
    unsigned char reserved_000[0x174];
    short health_174,maximum_176;
    unsigned char reserved_178[0x304];
    short secondary_47c;
    unsigned char reserved_47e[0x1ce];
    int remaining_64c,total_650;
};
typedef char story_timer_offset[offsetof(StoryInfoFighterView,remaining_64c)==0x64c?1:-1];
typedef char story_duration_offset[offsetof(StoryInfoFighterView,total_650)==0x650?1:-1];
void BattleInfoRecordF8::update_story_471930()
{
    StoryInfoFighterView *fighter=reinterpret_cast<StoryInfoFighterView *>(story_fighter_1c);
    int target=fighter->health_174;
    // Story mode overlays this normal-mode ratio cell with signed health.
    int displayed=*reinterpret_cast<int *>(&height_ratio_08);
    if(displayed<target){
        int next=displayed+fighter->maximum_176/120;
        if(next>=target)next=target;
        *reinterpret_cast<int *>(&height_ratio_08)=next;
    }else *reinterpret_cast<int *>(&height_ratio_08)=target;
    target=fighter->secondary_47c;
    displayed=gauge_0c;
    if(displayed>target){
        int next=displayed-fighter->maximum_176/120;
        if(next<=target)next=target;
        gauge_0c=next;
    }else gauge_0c=target;
    if(fighter->remaining_64c>=0){
        story_progress_10=static_cast<float>(fighter->remaining_64c/60.0);
        if(fighter->total_650-fighter->remaining_64c>60 && fade_alpha_14<255)fade_alpha_14+=15;
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
