#include "engine/SceneBase.hpp"

namespace th105 {

// Constructor-facing physical view of the RTTI-owned 0x28C CTitle object.
// The shared Title.hpp intentionally keeps destructor-facing sprite facades;
// this TU needs the original polymorphic member visibility so VC8 emits the
// target member construction and EH cleanup naturally.
struct UiDesignObject;

struct SceneTextureHandle {
    unsigned int value;
    SceneTextureHandle() : value(0) {}
};

struct SceneSpriteColorBase {
    unsigned int reserved_04;
    SceneSpriteColorBase() : reserved_04(0) {}
};

class CSprite : public SceneSpriteColorBase {
public:
    CSprite() {}
    virtual ~CSprite();
    virtual void set_color(unsigned int color);
    virtual void slot_08();
    virtual void slot_0c();
    virtual void set_texture_options(
        unsigned int handle, int x, int y, unsigned int width,
        unsigned int height, int option, int flags);
    virtual void set_texture(
        unsigned int handle, int x, int y, int width, int height);
    virtual void slot_18();
    virtual void render(float x, float y);
private:
    unsigned char reserved_08[0x8C];
};

class CTile : public SceneSpriteColorBase {
public:
    CTile() {}
    virtual ~CTile();
    virtual void set_color(unsigned int color);
    virtual void slot_08();
    virtual void slot_0c();
    virtual void slot_10();
    virtual void slot_14();
    virtual void slot_18();
    virtual void render(float x, float y);
    void set_texture_options(
        unsigned int handle, int x, int y, unsigned int width,
        unsigned int height, int option, int flags);
private:
    unsigned char reserved_08[0x9C];
};

class TitleDesignResource {
public:
    TitleDesignResource();
    virtual ~TitleDesignResource();
    virtual void slot_04();
    virtual void slot_08();
    virtual void slot_0c();
    virtual void load(const char *path);
    void bind_object(UiDesignObject **result, int object_id);
private:
    unsigned char reserved_04[0x30];
};

struct TitleResourceManager {
    unsigned int *load_texture(
        unsigned int *result, const char *path,
        unsigned int *width, unsigned int *height);
};
extern TitleResourceManager g_title_resource_manager;
extern "C" void *__cdecl get_combined_menu_input();
unsigned int get_session_setup_option();
int get_game_mode();
extern "C" const char title_base_path[];
extern "C" const char title_menu_item_path[];
extern "C" const char title_design_path[];

class CTitleConstructorView : public CSceneBase {
public:
    CTitleConstructorView();
    virtual ~CTitleConstructorView();
    virtual int update();
    virtual bool render();
    virtual void unknown_scene_method();
    virtual void on_scene_enter(int previous_scene);
    virtual void on_scene_exit(int next_scene);
private:
    SceneTextureHandle texture_08;
    CSprite sprite_0c;
    SceneTextureHandle texture_a0;
    CSprite sprite_a4;
    CTile tile_138;
    TitleDesignResource design_1dc;
    int item_count_210;
    int state_214;
    void *menu_input_218;
    int mode_21c;
    int state_220;
    UiDesignObject *design_items_224[12];
    float menu_item_wave_offsets_254[12];
    int state_284;
    int wave_counter_288;
};

typedef char CTitleProbe_size_must_be_0x28c[sizeof(CTitleConstructorView) == 0x28c ? 1 : -1];

CTitleConstructorView::CTitleConstructorView()
{
    unsigned int width;
    unsigned int height;

    {
        unsigned int handle1;
        texture_08.value = *g_title_resource_manager.load_texture(
            &handle1, title_base_path, &width, &height);
        sprite_0c.set_texture(texture_08.value, 0, 0, 640, 480);
    }

    {
        unsigned int handle2;
        texture_a0.value = *g_title_resource_manager.load_texture(
            &handle2, title_menu_item_path, &width, &height);
        sprite_a4.set_texture_options(
            texture_a0.value, 0, 0, width, 16, width >> 1, 0);
        tile_138.set_texture_options(
            texture_a0.value, 0, 16, width, 24, width >> 1, 0);
    }

    design_1dc.load(title_design_path);

    void *input = get_combined_menu_input();
    if (input)
        menu_input_218 = reinterpret_cast<unsigned char *>(input) + 0x3C;
    else
        menu_input_218 = 0;
    mode_21c = 0;
    state_220 = 0;
    state_214 = 0;
    item_count_210 = 12;

    for (int i = 0; i < 12; ++i) {
        design_1dc.bind_object(&design_items_224[i], i + 100);
        menu_item_wave_offsets_254[i] = 0.0f;
    }

    state_284 = 0;
    wave_counter_288 = 0;

    if (get_session_setup_option() == 2 && get_game_mode() != 6) {
        mode_21c = 6;
    } else {
        switch (get_game_mode()) {
        case 0: mode_21c = 0; break;
        case 1: mode_21c = 1; break;
        case 2: mode_21c = 2; break;
        case 3: mode_21c = 3; break;
        case 4:
        case 5:
        case 6: mode_21c = 4; break;
        case 8: mode_21c = 5; break;
        case 7: mode_21c = 8; break;
        default: break;
        }
    }
}

}
