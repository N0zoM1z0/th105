// JP1.06a 0x00455850. Complete fade/update policy; source remains nonexact.
// Pointer-only list value view. See docs/SCENARIO_LIST_FADE_2026_10_29.md.
#include <list>
#include <stddef.h>
namespace th105 {
struct ScenarioFadeSpriteView {
    virtual ~ScenarioFadeSpriteView();
    virtual void set_color(unsigned);
    virtual void set_vertex_colors(const unsigned *);
    virtual void multiply_color(unsigned);
    virtual void slot_10();
    virtual void slot_14();
    virtual void slot_18();
    virtual void render(float,float);
    unsigned char fields_004[0x90];
};
struct ScenarioFadeEntryView {
    unsigned resource_handle_000;
    ScenarioFadeSpriteView sprite_004;
    unsigned char alpha_098;
    signed char delta_099;
    unsigned char reserved_09a[2];
    ~ScenarioFadeEntryView();
};
typedef char CheckFadeSize[sizeof(ScenarioFadeEntryView)==0x9c?1:-1];
struct ScenarioListUpdateView {
    void update_list(std::list<ScenarioFadeEntryView> *entries);
};
void ScenarioListUpdateView::update_list(std::list<ScenarioFadeEntryView> *entries)
{
    std::list<ScenarioFadeEntryView>::iterator it=entries->begin();
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
