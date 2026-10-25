#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <cstring>
#include <deque>
#include <map>
#include <string>
#include <vector>
#include "input/InputManager.hpp"

namespace th105 {

// Root-local 0x34 binding record: every observed button is a DWORD field.
// Scalar field spelling is a hypothesis; see the target evidence note.
struct SceneBootstrapBindings {
    signed char source_id;
    int up;
    int down;
    int left;
    int right;
    int button0;
    int button1;
    int button2;
    int button3;
    int button4;
    int button5;
    int button6;
    int button7;
};
typedef char binding_size[sizeof(SceneBootstrapBindings) == 0x34 ? 1 : -1];

struct SceneBootstrapInputBase {
    SceneBootstrapInputBase();
    virtual ~SceneBootstrapInputBase();
    virtual void update();
    SceneBootstrapBindings bindings;
    HoldCounters hold;
    void assign_profile(const SceneBootstrapBindings *source);
};

struct SceneBootstrapInputEx : SceneBootstrapInputBase {
    unsigned short injected_mask;
    unsigned short resolved_mask;
    bool use_injected_input;
    SceneBootstrapInputEx() {
        use_injected_input = false;
        injected_mask = 0;
        // The target does not initialize resolved_mask at +0x62.
    }
    virtual void update();
};

typedef char input_base_size[sizeof(SceneBootstrapInputBase) == 0x60 ? 1 : -1];
typedef char input_ex_size[sizeof(SceneBootstrapInputEx) == 0x68 ? 1 : -1];

// The target uses the independent deque provider at both call sites.
struct SceneBootstrapInputSourcesView {
    void push_back(SceneBootstrapInputBase *const &value);
};

struct SceneBootstrapInputCluster : SceneBootstrapInputBase {
    std::deque<SceneBootstrapInputBase *> sources;
    signed char active_source;
};

struct SceneBootstrapKeyTable {
    void reset();
    void add_tracked_key(unsigned char key);
};
struct SceneBootstrapDeckRefresh {
    unsigned char reload_common_resources(unsigned char red, unsigned char green,
                                           unsigned char blue);
};
struct SceneBootstrapScore {
    void load();
};
struct BgmVolumeService {
    int set_volume(float value);
};

extern std::map<int, std::string> g_bootstrap_character_names;
extern std::map<int, unsigned char> g_bootstrap_stages;
extern std::map<int, unsigned char> g_bootstrap_bgms;
// DWORD key/value ABI projection; original nominal specialization is unknown.
extern std::map<int, int> g_bootstrap_effect_frames;
extern SceneBootstrapKeyTable g_bootstrap_keys;
extern SceneBootstrapInputBase g_bootstrap_keyboard;
extern SceneBootstrapInputCluster g_bootstrap_combined_input;
extern std::vector<SceneBootstrapInputEx> g_bootstrap_gamepads;
extern int g_input_source_limit;
extern signed char g_selected_input_sources[2];
extern void *g_bootstrap_selected_inputs[2];
extern SceneBootstrapDeckRefresh g_bootstrap_deck_refresh;
extern SceneBootstrapScore g_bootstrap_score;
extern bool g_bootstrap_send_enter;
extern HWND g_main_window;
extern int g_bootstrap_bgm_percent;
extern int g_bootstrap_se_percent;
extern BgmVolumeService g_bgm_volume_service;

bool __cdecl initialize_profile_ui(void *input);
void __cdecl initialize_scene_auxiliary_6654a0();
void __cdecl initialize_player_profiles_from_game_config();
int __cdecl apply_se_percent(int value);

void __cdecl initialize_scene_resources_43e2e0()
{
    char names[15][16] = {
        "sfjnv", "nbsjtb", "tblvzb", "bmjdf", "qbudipvmj",
        "zpvnv", "sfnjmjb", "zvzvlp", "zvlbsj", "tvjlb",
        "vepohf", "bzb", "lpnbdij", "jlv", "ufotij"
    };
    for (int character = 0; character < 15; ++character) {
        for (unsigned offset = 0; offset < std::strlen(names[character]); ++offset)
            --names[character][offset];
        g_bootstrap_character_names.insert(
            std::pair<int, std::string>(character, std::string(names[character])));
    }

    g_bootstrap_stages.insert(std::pair<int, unsigned char>(0, 0));
    g_bootstrap_stages.insert(std::pair<int, unsigned char>(1, 11));
    g_bootstrap_stages.insert(std::pair<int, unsigned char>(2, 12));
    g_bootstrap_stages.insert(std::pair<int, unsigned char>(3, 13));
    g_bootstrap_stages.insert(std::pair<int, unsigned char>(4, 14));
    g_bootstrap_stages.insert(std::pair<int, unsigned char>(5, 15));
    g_bootstrap_stages.insert(std::pair<int, unsigned char>(6, 16));
    g_bootstrap_stages.insert(std::pair<int, unsigned char>(7, 17));
    g_bootstrap_stages.insert(std::pair<int, unsigned char>(8, 0));
    g_bootstrap_stages.insert(std::pair<int, unsigned char>(9, 5));
    g_bootstrap_stages.insert(std::pair<int, unsigned char>(10, 18));
    g_bootstrap_stages.insert(std::pair<int, unsigned char>(11, 3));
    g_bootstrap_stages.insert(std::pair<int, unsigned char>(12, 2));
    g_bootstrap_stages.insert(std::pair<int, unsigned char>(13, 4));
    g_bootstrap_stages.insert(std::pair<int, unsigned char>(14, 5));

    g_bootstrap_bgms.insert(std::pair<int, unsigned char>(0, 10));
    g_bootstrap_bgms.insert(std::pair<int, unsigned char>(1, 11));
    g_bootstrap_bgms.insert(std::pair<int, unsigned char>(2, 12));
    g_bootstrap_bgms.insert(std::pair<int, unsigned char>(3, 13));
    g_bootstrap_bgms.insert(std::pair<int, unsigned char>(4, 15));
    g_bootstrap_bgms.insert(std::pair<int, unsigned char>(5, 14));
    g_bootstrap_bgms.insert(std::pair<int, unsigned char>(6, 17));
    g_bootstrap_bgms.insert(std::pair<int, unsigned char>(7, 16));
    g_bootstrap_bgms.insert(std::pair<int, unsigned char>(8, 18));
    g_bootstrap_bgms.insert(std::pair<int, unsigned char>(9, 19));
    g_bootstrap_bgms.insert(std::pair<int, unsigned char>(10, 20));
    g_bootstrap_bgms.insert(std::pair<int, unsigned char>(11, 21));
    g_bootstrap_bgms.insert(std::pair<int, unsigned char>(12, 22));
    g_bootstrap_bgms.insert(std::pair<int, unsigned char>(13, 4));
    g_bootstrap_bgms.insert(std::pair<int, unsigned char>(14, 5));

    g_bootstrap_effect_frames.insert(std::pair<int, int>(0, 100));
    g_bootstrap_effect_frames.insert(std::pair<int, int>(1, 110));
    g_bootstrap_effect_frames.insert(std::pair<int, int>(2, 120));
    g_bootstrap_effect_frames.insert(std::pair<int, int>(3, 130));
    g_bootstrap_effect_frames.insert(std::pair<int, int>(4, 140));
    g_bootstrap_effect_frames.insert(std::pair<int, int>(5, 150));
    g_bootstrap_effect_frames.insert(std::pair<int, int>(6, 160));
    g_bootstrap_effect_frames.insert(std::pair<int, int>(7, 170));
    g_bootstrap_effect_frames.insert(std::pair<int, int>(8, 180));
    g_bootstrap_effect_frames.insert(std::pair<int, int>(9, 190));
    g_bootstrap_effect_frames.insert(std::pair<int, int>(17, 200));
    g_bootstrap_effect_frames.insert(std::pair<int, int>(10, 210));
    g_bootstrap_effect_frames.insert(std::pair<int, int>(11, 220));
    g_bootstrap_effect_frames.insert(std::pair<int, int>(12, 230));
    g_bootstrap_effect_frames.insert(std::pair<int, int>(13, 240));
    g_bootstrap_effect_frames.insert(std::pair<int, int>(14, 250));
    g_bootstrap_effect_frames.insert(std::pair<int, int>(15, 260));
    g_bootstrap_effect_frames.insert(std::pair<int, int>(16, 270));

    g_bootstrap_keys.reset();
    g_bootstrap_keys.add_tracked_key(1);
    g_bootstrap_keys.add_tracked_key(59);
    g_bootstrap_keys.add_tracked_key(60);
    g_bootstrap_keys.add_tracked_key(61);
    g_bootstrap_keys.add_tracked_key(62);
    g_bootstrap_keys.add_tracked_key(63);
    g_bootstrap_keys.add_tracked_key(64);
    g_bootstrap_keys.add_tracked_key(65);
    g_bootstrap_keys.add_tracked_key(66);
    g_bootstrap_keys.add_tracked_key(67);
    g_bootstrap_keys.add_tracked_key(68);
    g_bootstrap_keys.add_tracked_key(87);
    g_bootstrap_keys.add_tracked_key(88);

    SceneBootstrapBindings bindings;
    std::memset(&bindings, 0, sizeof(bindings));
    bindings.source_id = -1;
    bindings.up = 200;
    bindings.down = 208;
    bindings.left = 203;
    bindings.right = 205;
    bindings.button0 = 44;
    bindings.button1 = 45;
    bindings.button2 = 46;
    bindings.button3 = 30;
    bindings.button4 = 31;
    bindings.button5 = 32;
    bindings.button6 = 1;
    g_bootstrap_keyboard.assign_profile(&bindings);
    reinterpret_cast<SceneBootstrapInputSourcesView *>(
        &g_bootstrap_combined_input.sources)->push_back(&g_bootstrap_keyboard);

    std::memset(&bindings, 0, sizeof(bindings));
    bindings.button0 = 0;
    bindings.button1 = 1;
    bindings.button2 = 2;
    bindings.button3 = 3;
    bindings.button4 = 4;
    bindings.button5 = 5;
    bindings.button6 = 6;
    g_bootstrap_gamepads.assign(g_input_source_limit, SceneBootstrapInputEx());
    for (unsigned index = 0; index < g_bootstrap_gamepads.size(); ++index) {
        bindings.source_id = static_cast<signed char>(index);
        g_bootstrap_gamepads[index].assign_profile(&bindings);
        reinterpret_cast<SceneBootstrapInputSourcesView *>(
            &g_bootstrap_combined_input.sources)->push_back(&g_bootstrap_gamepads[index]);
    }

    g_bootstrap_selected_inputs[0] = 0;
    g_selected_input_sources[0] = -2;
    g_bootstrap_selected_inputs[1] = 0;
    g_selected_input_sources[1] = -2;
    initialize_profile_ui(&g_bootstrap_combined_input);
    initialize_scene_auxiliary_6654a0();
    initialize_player_profiles_from_game_config();
    g_bootstrap_deck_refresh.reload_common_resources(255, 96, 96);
    g_bootstrap_score.load();
    if (g_bootstrap_send_enter)
        SendMessageA(g_main_window, 0x104, 13, 0);
    const float volume = static_cast<float>(
        static_cast<double>(g_bootstrap_bgm_percent) * 0.01f * 0.75);
    g_bgm_volume_service.set_volume(volume);
    apply_se_percent(g_bootstrap_se_percent);
}

} // namespace th105
