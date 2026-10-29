// JP1.06a 0x00456760. Rebuild the current window text texture.
// See docs/SCENARIO_TEXT_REBUILD_2026_10_29.md.
#include "ui/DesignBaseLifetime.hpp"
#include "ui/Title.hpp"
#include "assets/TextFontOwner.hpp"
#include <list>
#include <string>
#include <stddef.h>
namespace th105 {
class RebuildColorView {
public:
    RebuildColorView() {}
    virtual ~RebuildColorView() {}
    virtual void set_color(unsigned)=0;
    virtual void set_vertex_colors(const unsigned *)=0;
    virtual void multiply_color(unsigned)=0;
    DesignTextureHandle handle_004;
};
class RebuildSpriteView : public RebuildColorView {
public:
    RebuildSpriteView() {}
    // Native455160 is the nonthrowing physical sprite copy provider.
    RebuildSpriteView(const RebuildSpriteView &) throw();
    virtual ~RebuildSpriteView() {}
    virtual void set_color(unsigned);
    virtual void set_vertex_colors(const unsigned *);
    virtual void multiply_color(unsigned);
    virtual void set_texture_options(unsigned,int,int,unsigned,unsigned,int,int);
    virtual void slot_14();
    virtual void slot_18();
    virtual void render(float,float);
    unsigned char fields_008[0x8c];
};
struct RebuildEntryView {
    unsigned resource_handle_000;
    RebuildSpriteView sprite_004;
    // Only two semantic bytes follow the sprite; the final two are padding.
    unsigned char alpha_098;
    signed char delta_099;
    RebuildEntryView()
    {
        alpha_098 = 0;
        delta_099 = 5;
        resource_handle_000 = 0;
    }
    ~RebuildEntryView();
};
RebuildEntryView::~RebuildEntryView()
{
    g_title_resource_manager.release_title_resource_handle(resource_handle_000);
}
struct CInputManager;
class ScenarioTextRebuildView {
public:
    virtual void configure(CInputManager *);
    virtual void clear_runtime();
    virtual signed char update();
    virtual void render();
    unsigned char prefix_004[0x64];
    TextFontOwner194 font_068;
    unsigned char gap_1fc[0x154];
    std::list<RebuildEntryView> entries_350;
    unsigned char gap_35c[0x1c4];
    int fade_step_520;
    void rebuild_text(std::string *text);
};
typedef char EntrySize[sizeof(RebuildEntryView)==0x9c?1:-1];
typedef char OwnerSize[sizeof(ScenarioTextRebuildView)==0x524?1:-1];
typedef char EntriesOffset[offsetof(ScenarioTextRebuildView,entries_350)==0x350?1:-1];
void ScenarioTextRebuildView::rebuild_text(std::string *text)
{
    while(entries_350.size()>1) entries_350.pop_front();
    entries_350.push_back(RebuildEntryView());
    entries_350.back().resource_handle_000=g_title_resource_manager.create_text_texture(
        text->c_str(),&font_068,1024,128,0,0).value;
    entries_350.back().sprite_004.set_texture_options(
        entries_350.back().resource_handle_000,0,0,640,80,-32,0);
    entries_350.back().sprite_004.set_color(0x00ffffffu);
    entries_350.back().delta_099=static_cast<signed char>(fade_step_520);
}
}
