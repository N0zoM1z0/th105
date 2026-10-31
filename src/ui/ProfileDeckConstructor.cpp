// JP1.06a CProfileDeckEdit constructor-facing model; full root remains nonexact.
// Native RTTI proves eight CSprite slots, four CTile slots and signed-char value adapters.
// Runtime views and their accepted consumers remain unchanged.
#include "ui/Menu.hpp"
#include "ui/Title.hpp"
#include "ui/GuideOverlay.hpp"
#include "ui/CNumberRuntime.hpp"
#include "ui/DesignBaseLifetime.hpp"
#include "ui/DesignObjectLookup.cpp"
#include "ui/ProfileDeckResourceLifetime.hpp"
#include "battle/EffectSprite.hpp"
#include "assets/TextFontOwner.hpp"
#include "input/InputManager.hpp"
#include <string>
#include <string.h>

extern "C" __declspec(dllimport) int __cdecl wsprintfA(char *, const char *, ...);
extern "C" th105::CInputManager *g_active_menu_input;
extern "C" const char deck_name_path_format[];
extern "C" const char deck_digit_text_format[];
extern "C" const char deck_design_path[];
extern "C" const char profile_ui_effect_label[];
extern "C" const char deck_disabled_text[39];

namespace th105 {
struct TitleResourceManagerValueView { TextureHandleResult load_texture_value(const char *,unsigned *,unsigned *); };
extern TitleResourceManagerValueView g_title_resource_manager_value;

const char *__cdecl character_key_to_name(int);
extern TextFontOwner194 g_profile_deck_font;

typedef std::map<int, SpellRecordView> DeckSpellMap;
typedef std::map<unsigned, UiDesignObject *> DeckDesignMap;

class DeckCtorSprite94 : public IColor {
public:
    DeckCtorSprite94() {}
    virtual ~DeckCtorSprite94() {}
    virtual void set_color(unsigned);
    virtual void set_vertex_colors(const unsigned *);
    virtual void multiply_color(unsigned);
    virtual void set_texture_options(unsigned, int, int, unsigned, unsigned, int, int);
    virtual void set_texture(unsigned, int, int, int, int);
    virtual void slot_18();
    virtual void render(float, float);
    SpriteVertex28 vertices_08[4];
    float width_78, height_7c, extension_80[5];
};
class DeckCtorTileA4 : public IColor {
public:
    DeckCtorTileA4() {}
    virtual ~DeckCtorTileA4() {}
    virtual void set_color(unsigned);
    virtual void set_vertex_colors(const unsigned *);
    virtual void multiply_color(unsigned);
    void set_texture(unsigned, int, int, unsigned, unsigned);
    SpriteVertex28 vertices_08[4];
    float width_78, height_7c, extension_80[9];
};
struct DeckPlayerView {
    std::deque<unsigned short> *copy_deck(std::deque<unsigned short> *output, int character);
};
struct ProfileDeckRefreshFacade {
    void clear_common_resources();
    unsigned char reload_common_resources(unsigned char red, unsigned char green, unsigned char blue);
};
struct DeckResourceLoadView {
    unsigned char load_spell_csv(int character, signed char story_mode, unsigned char use_owner);
};

class ProfileDeckConstructorView : public Menu {
public:
    ProfileDeckConstructorView(PlayerSlotRecord *player, int character, UiSprite94 *stand);
    virtual ~ProfileDeckConstructorView();
    virtual bool update();
    virtual void render();
    void select_filter(unsigned char category);
    void import_counts(const std::deque<short> &source);
    void show_record(SpellRecordView *record);

    PlayerSlotRecord *player_04;
    int character_08;
    UiSprite94 *stand_0c;
    CDesignBase design_10;
    UiDesignObject *objects_44[20];
    unsigned texture_94;
    DeckCtorSprite94 sprite_98;
    unsigned field_12c;
    DeckCtorSprite94 sprite_130, sprite_1c4;
    unsigned texture_258;
    DeckCtorTileA4 tile_25c;
    unsigned texture_300;
    DeckCtorSprite94 sprite_304;
    ProfileDeckResourceGroupNative20 resources_398;
    SpellTree *local_tree_3b8, *common_tree_3bc;
    std::map<short, signed char> counts_3c0;
    std::deque<DeckSpellMap::iterator> filtered_3cc;
    char color_3e0, total_3e1;
    MenuCursorState cursor_3e4, cursor_3f8;
    unsigned char flags_40c[4];
    GuideOverlay guides_410[4];
};

typedef char SpriteSize[sizeof(DeckCtorSprite94)==0x94?1:-1];
typedef char TileSize[sizeof(DeckCtorTileA4)==0xa4?1:-1];
typedef char OwnerSize[sizeof(ProfileDeckConstructorView)==0x6b0?1:-1];
typedef char ResourceOffset[offsetof(ProfileDeckConstructorView,resources_398)==0x398?1:-1];
typedef char GuideOffset[offsetof(ProfileDeckConstructorView,guides_410)==0x410?1:-1];

#define FIND_DECK_DESIGN(index,id) design_10.find_object(&objects_44[index],id)
#define NUMBER_VIEW(index) reinterpret_cast<CNumber *>(reinterpret_cast<unsigned char *>(objects_44[index])+0x18)

ProfileDeckConstructorView::ProfileDeckConstructorView(
    PlayerSlotRecord *player, int character, UiSprite94 *stand)
    : texture_94(0), field_12c(0), texture_258(0), texture_300(0)
{
    player_04 = player;
    character_08 = character;
    stand_0c = stand;

    char path[260];
    wsprintfA(path, deck_name_path_format, character_key_to_name(character));
    unsigned width, height;
    texture_300 = g_title_resource_manager_value.load_texture_value(path, &width, &height).value;
    sprite_304.set_texture(texture_300, 0, 0, width, height);

    TextFontConfig128 config;
    strcpy_s(config.face_000, 256, profile_ui_effect_label);
    config.height_108 = 14;
    config.weight_10c = 300;
    config.colors_100[0] = 255;
    config.colors_100[2] = 255;
    config.colors_100[4] = 255;
    config.colors_100[1] = 128;
    config.colors_100[3] = 128;
    config.colors_100[5] = 255;
    config.spacing_x_120 = 0;
    config.spacing_y_124 = 2;
    config.outline_111 = 1;
    config.wrap_112 = 1;
    g_profile_deck_font.configure(&config);

    std::string digits;
    char text[1024];
    for (int i = 0; i < 10; ++i) {
        wsprintfA(text, deck_digit_text_format, i, i, i, i);
        digits.append(text, strlen(text));
    }
    digits.append(deck_disabled_text, sizeof(deck_disabled_text)-1);
    texture_258 = g_title_resource_manager.create_text_texture(
        digits.c_str(), &g_profile_deck_font, 256, 256, 0, 0).value;
    tile_25c.set_texture(texture_258, 0, 0, 21, 16);

    design_10.load(deck_design_path);
    design_10.bind_object_alt(&objects_44[0], 100);
    design_10.bind_object_alt(&objects_44[1], 106);
    design_10.bind_object_alt(&objects_44[2], 121);
    design_10.bind_object_alt(&objects_44[3], 141);
    for (int i = 1; i < 4; ++i)
        objects_44[i]->enabled = true;
    FIND_DECK_DESIGN(5, 124);
    FIND_DECK_DESIGN(6, 123);
    for (int i = 0; i < 5; ++i)
        design_10.bind_object_alt(&objects_44[12+i], 200+i);
    for (int i = 0; i < 5; ++i)
        design_10.bind_object_alt(&objects_44[7+i], 101+i);
    FIND_DECK_DESIGN(17, 130);
    NUMBER_VIEW(17)->bind_value(&color_3e0);
    objects_44[17]->enabled = true;
    FIND_DECK_DESIGN(18, 1002);
    objects_44[18]->enabled = true;
    NUMBER_VIEW(18)->bind_value(&total_3e1);
    FIND_DECK_DESIGN(19, 1001);
    NUMBER_VIEW(19)->bind_value(&total_3e1);

    ProfileDeckRefreshFacade refresh;
    refresh.clear_common_resources();
    refresh.reload_common_resources(96, 96, 255);
    reinterpret_cast<DeckResourceLoadView *>(&resources_398)->load_spell_csv(character_08, 0, 1);
    local_tree_3b8 = reinterpret_cast<SpellTree *>(&resources_398.tree_14);
    common_tree_3bc = &g_common_spell_tree;
    flags_40c[1] = 0;
    flags_40c[2] = 0;
    flags_40c[3] = 0;
    flags_40c[0] = 0;
    select_filter(0);
    total_3e1 = 0;
    import_counts(*reinterpret_cast<std::deque<short> *>(
        reinterpret_cast<DeckPlayerView *>(player_04)->copy_deck(0, character_08)));
    show_record(&filtered_3cc[0]->second);
    CInputManager *input = g_active_menu_input;
    cursor_3f8.input_counter = input ? &input->hold.horizontal : 0;
    cursor_3f8.selection = 0;
    cursor_3f8.window_start = 0;
    cursor_3f8.item_count = 5;
    cursor_3f8.page_size = 0;
    guides_410[0].load(13);
    guides_410[1].load(14);
    guides_410[2].load(2);
    guides_410[3].load(10);
}
}
