#include "engine/SceneBase.hpp"
#include "ui/Title.hpp"

#include <deque>

namespace th105 {

unsigned char __cdecl start_async_engine_scene_load(int scene);
int __cdecl get_async_scene_load_request();
char *__cdecl get_combined_menu_input_counters();

struct SceneTextureHandle {
    unsigned value;
    SceneTextureHandle() : value(0) {}
};

struct SceneSpriteColorBase {
    unsigned reserved_04;
    SceneSpriteColorBase() : reserved_04(0) {}
};

class SceneSprite94 : public SceneSpriteColorBase {
public:
    SceneSprite94() {}
    virtual ~SceneSprite94();
    virtual void set_color(unsigned int);
    virtual void slot_08();
    virtual void slot_0c();
    virtual void set_texture_options(
        unsigned int, int, int, unsigned int, unsigned int, int, int);
    virtual void set_texture(unsigned int, int, int, int, int);
    virtual void slot_18();
    virtual void render(float, float);
    unsigned char reserved_08[0x8C];
};

class LogoSpriteE8 : public SceneSpriteColorBase {
public:
    LogoSpriteE8() {}
    virtual ~LogoSpriteE8();
    virtual void set_color(unsigned int);
    virtual void slot_08();
    virtual void slot_0c();
    void set_texture_options(unsigned int, int, int, int, int, int, int);
    unsigned char reserved_08[0xE0];
};

class LogoTileA4 : public SceneSpriteColorBase {
public:
    LogoTileA4() {}
    virtual ~LogoTileA4();
    virtual void set_color(unsigned int);
    virtual void slot_08();
    virtual void slot_0c();
    unsigned char reserved_08[0x9C];
};

struct SceneRenderClusterOwner93 {
    unsigned char bytes_00[0x90];
    unsigned char state_90;
    unsigned char active_91;
    unsigned char flag_92;

    SceneRenderClusterOwner93();
    ~SceneRenderClusterOwner93();
    void initialize();
    void load_script(const char *path);
    unsigned char update_451400();
};

class EndingConstructorView : public IScene {
public:
    EndingConstructorView();
    virtual ~EndingConstructorView();

    SceneRenderClusterOwner93 cluster_04;
    unsigned char alpha_97;
};

class CLoadingConstructorView : public IScene {
public:
    CLoadingConstructorView();
    virtual ~CLoadingConstructorView();
    virtual int update();

    SceneTextureHandle texture_04;
    SceneSprite94 sprite_08;
    unsigned char reserved_9c[8];
    std::deque<unsigned char> queue_a4;
    unsigned short timer_b8;
};

class CLogoConstructorView : public IScene {
public:
    CLogoConstructorView();
    virtual ~CLogoConstructorView();
    virtual int update();

    SceneTextureHandle texture_04;
    LogoSpriteE8 sprite_08;
    LogoTileA4 tile_f0;
    int state_194;
};

class OpeningConstructorView : public CSceneBase {
public:
    OpeningConstructorView();
    virtual ~OpeningConstructorView();
    virtual int update();

    SceneRenderClusterOwner93 cluster_08;
    unsigned char reserved_9b;
    unsigned char active_9c;
};

class NetworkSessionSceneControl {
public:
    virtual void slot_00();
    virtual void slot_04();
    virtual void slot_08();
    virtual void slot_0c();
    virtual void slot_10();
    virtual void slot_14();
    virtual void slot_18();
    virtual void slot_1c();
    virtual void slot_20();
    virtual void slot_24();
    virtual void slot_28();
    virtual void request_scene(int scene);
};

NetworkSessionSceneControl *__cdecl get_network_session();

class CLoadingWatchConstructorView : public IScene {
public:
    CLoadingWatchConstructorView();
    virtual ~CLoadingWatchConstructorView();

    SceneTextureHandle texture_04;
    SceneSprite94 sprite_08;
    unsigned short timer_9c;
    unsigned char reserved_9e[2];
    int state_a0;
};

EndingConstructorView::EndingConstructorView()
{
    cluster_04.active_91 = 1;
    cluster_04.state_90 = 0;
    cluster_04.flag_92 = 0;
    alpha_97 = 0;
}

CLoadingConstructorView::CLoadingConstructorView()
{
    unsigned loaded;
    texture_04.value = *g_title_resource_manager.load_texture(
        &loaded, "data/scene/logo/0002.bmp", 0, 0);
    sprite_08.set_texture(texture_04.value, 0, 0, 128, 32);
    start_async_engine_scene_load(3);
}

int CLoadingConstructorView::update()
{
    ++timer_b8;
    return (get_async_scene_load_request() != 0) + 5;
}

CLogoConstructorView::CLogoConstructorView()
{
    unsigned loaded;
    texture_04.value = *g_title_resource_manager.load_texture(
        &loaded, "data/scene/logo/0000.bmp", 0, 0);
    sprite_08.set_texture_options(texture_04.value, 0, 0, 640, 480, 0, 0);
    state_194 = 0;
}

int CLogoConstructorView::update()
{
    ++state_194;
    if (get_async_scene_load_request())
        return 0;
    get_combined_menu_input_counters();
    return state_194 >= 180;
}

OpeningConstructorView::OpeningConstructorView()
{
    cluster_08.initialize();
    cluster_08.load_script("data/scene/opening/opening.txt");
    active_9c = 1;
}

int OpeningConstructorView::update()
{
    if (cluster_08.update_451400()) {
        return (*reinterpret_cast<int *>(
            get_combined_menu_input_counters() + 8) - 1) ? 1 : 2;
    }
    *reinterpret_cast<unsigned *>(
        reinterpret_cast<unsigned char *>(scene_id) + 4) = 0xFFFFFF;
    return 2;
}

CLoadingWatchConstructorView::CLoadingWatchConstructorView()
{
    unsigned loaded;
    texture_04.value = *g_title_resource_manager.load_texture(
        &loaded, "data/scene/logo/0002.bmp", 0, 0);
    sprite_08.set_texture(texture_04.value, 0, 0, 128, 32);
    state_a0 = 0;
    get_network_session()->request_scene(3);
}

typedef char SceneTextureHandle_size[sizeof(SceneTextureHandle) == 4 ? 1 : -1];
typedef char SceneSprite94_size[sizeof(SceneSprite94) == 0x94 ? 1 : -1];
typedef char LogoSpriteE8_size[sizeof(LogoSpriteE8) == 0xE8 ? 1 : -1];
typedef char LogoTileA4_size[sizeof(LogoTileA4) == 0xA4 ? 1 : -1];
typedef char SceneRenderClusterOwner93_size[
    sizeof(SceneRenderClusterOwner93) == 0x93 ? 1 : -1];
typedef char Ending_alpha_offset[
    offsetof(EndingConstructorView, alpha_97) == 0x97 ? 1 : -1];
typedef char Loading_queue_offset[
    offsetof(CLoadingConstructorView, queue_a4) == 0xA4 ? 1 : -1];
typedef char Loading_timer_offset[
    offsetof(CLoadingConstructorView, timer_b8) == 0xB8 ? 1 : -1];
typedef char Logo_state_offset[
    offsetof(CLogoConstructorView, state_194) == 0x194 ? 1 : -1];
typedef char Opening_active_offset[
    offsetof(OpeningConstructorView, active_9c) == 0x9C ? 1 : -1];
typedef char Watch_state_offset[
    offsetof(CLoadingWatchConstructorView, state_a0) == 0xA0 ? 1 : -1];

} // namespace th105
