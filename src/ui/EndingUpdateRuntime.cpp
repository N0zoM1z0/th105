#include <stddef.h>
namespace th105 {

extern "C" bool __cdecl has_ui_selection_state_changed();
extern "C" char *__cdecl get_combined_menu_input_counters();
extern "C" bool __cdecl is_menu_initial_press(
    unsigned char, bool, bool, bool);
void __cdecl fade_bgm(int duration, int target);
void __cdecl install_menu_object(void *object);
extern int g_scene_mode;

struct BattlePhaseEndingView {
    unsigned char reserved_000[0x574];
    unsigned char flag_574;
    unsigned char reserved_575[7];
    int state_57c;

    signed char status_45a290();
};
extern BattlePhaseEndingView *g_battle_phase_block_ending;

struct EndingUpdateClusterMethodView {
    unsigned char update_451400();
};

struct CMenuEndDispatchView {
    unsigned char storage_00[0x44];
    explicit CMenuEndDispatchView(void *owner);
};

struct EndingUpdateView {
    void **vtable;
    unsigned char cluster_storage_04[0x93];
    unsigned char alpha_97;

    int update();

    unsigned char &cluster_active_94() { return cluster_storage_04[0x90]; }
    unsigned char &phase_active_95() { return cluster_storage_04[0x91]; }
    unsigned char &fade_started_96() { return cluster_storage_04[0x92]; }
    int &cluster_state_90() { return *reinterpret_cast<int *>(cluster_storage_04 + 0x8c); }
    EndingUpdateClusterMethodView &cluster_method()
    { return *reinterpret_cast<EndingUpdateClusterMethodView *>(cluster_storage_04); }
};

int EndingUpdateView::update()
{
    if (fade_started_96() && alpha_97 < 0xff)
        alpha_97 += 15;

    if (has_ui_selection_state_changed())
        return g_scene_mode == 22 ? 20 : 2;

    if (phase_active_95()) {
        if (!g_battle_phase_block_ending->status_45a290())
            phase_active_95() = 0;
        if (g_battle_phase_block_ending->state_57c)
            cluster_active_94() = 1;
    }

    if (cluster_active_94()) {
        if (!cluster_method().update_451400())
            cluster_active_94() = 0;
        if (cluster_state_90() && phase_active_95())
            g_battle_phase_block_ending->flag_574 = 0;
    }

    if (!phase_active_95()) {
        if (*reinterpret_cast<int *>(get_combined_menu_input_counters() + 0x10) == 1 ||
            is_menu_initial_press(1, false, false, false)) {
            fade_started_96() = 1;
            if (cluster_active_94())
                fade_bgm(1000, 0);
            install_menu_object(new CMenuEndDispatchView(0));
        }
    }
    return 20;
}

typedef char EndingUpdateView_cluster_off[
    offsetof(EndingUpdateView, cluster_storage_04) == 0x04 ? 1 : -1];
typedef char EndingUpdateView_alpha_off[
    offsetof(EndingUpdateView, alpha_97) == 0x97 ? 1 : -1];
typedef char CMenuEndDispatchView_size[
    sizeof(CMenuEndDispatchView) == 0x44 ? 1 : -1];

} // namespace th105
