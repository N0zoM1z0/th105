#include "battle/GameMode.hpp"

namespace th105 {

struct NormalSceneManagerBootstrap {
    unsigned char storage_000[0x5b4];
    NormalSceneManagerBootstrap();
};

struct ArcadeSceneManagerBootstrap {
    unsigned char storage_000[0x5c8];
    ArcadeSceneManagerBootstrap();
};

struct InfoManagerNormalBootstrap {
    unsigned char storage_000[0x688];
    InfoManagerNormalBootstrap();
};

struct BattleManagerBaseStoryDependency {
    virtual ~BattleManagerBaseStoryDependency();
    unsigned char storage_004[0x70];
    BattleManagerBaseStoryDependency();
};

struct StorySceneManagerBootstrap : BattleManagerBaseStoryDependency {
    unsigned char storage_074[0x34];
    StorySceneManagerBootstrap();
};

StorySceneManagerBootstrap::StorySceneManagerBootstrap()
{
}

struct InfoManagerStoryBootstrap {
    unsigned char storage_000[0x610];
    InfoManagerStoryBootstrap();
};

struct BattlePhaseBlockBootstrap {
    unsigned char storage_000[0x5b0];
    BattlePhaseBlockBootstrap();
    ~BattlePhaseBlockBootstrap();
};

struct SceneRendererDeleteView {
    virtual ~SceneRendererDeleteView();
};

struct InfoManagerDeleteView {
    virtual ~InfoManagerDeleteView();
};

extern NormalSceneManagerBootstrap *g_scene_renderer_normal;
extern InfoManagerNormalBootstrap *g_info_manager_normal;
extern StorySceneManagerBootstrap *g_story_scene_renderer;
extern InfoManagerStoryBootstrap *g_story_info_manager;
extern BattlePhaseBlockBootstrap *g_battle_phase_block_bootstrap;
extern SceneRendererDeleteView *g_scene_renderer_delete;
extern InfoManagerDeleteView *g_info_manager_delete;
extern GameMode g_game_mode;

void __cdecl initialize_story_managers();

void __cdecl initialize_normal_scene_managers()
{
    g_scene_renderer_normal = new NormalSceneManagerBootstrap;
    g_info_manager_normal = new InfoManagerNormalBootstrap;
}

void __cdecl initialize_arcade_scene_managers()
{
    g_scene_renderer_normal =
        reinterpret_cast<NormalSceneManagerBootstrap *>(
            new ArcadeSceneManagerBootstrap);
    g_info_manager_normal = new InfoManagerNormalBootstrap;
}

void __cdecl initialize_story_scene_managers()
{
    g_story_scene_renderer = new StorySceneManagerBootstrap;
    g_story_info_manager = new InfoManagerStoryBootstrap;
    g_battle_phase_block_bootstrap = new BattlePhaseBlockBootstrap;
}

void __cdecl destroy_scene_managers()
{
    if (g_scene_renderer_delete) {
        delete g_scene_renderer_delete;
        g_scene_renderer_delete = 0;
    }
    if (g_info_manager_delete) {
        delete g_info_manager_delete;
        g_info_manager_delete = 0;
    }
    if (g_battle_phase_block_bootstrap) {
        delete g_battle_phase_block_bootstrap;
        g_battle_phase_block_bootstrap = 0;
    }
}

void __cdecl prepare_scene_resources_by_mode()
{
    destroy_scene_managers();
    switch (g_game_mode) {
    case static_cast<GameMode>(0):
        initialize_story_scene_managers();
        break;
    case GAME_MODE_VS_COM:
        initialize_arcade_scene_managers();
        break;
    case static_cast<GameMode>(7):
        initialize_story_managers();
        break;
    default:
        initialize_normal_scene_managers();
        break;
    }
}

} // namespace th105
