#include "DesignBaseLifetime.hpp"
#include "Menu.hpp"
#include "../input/InputSelection.hpp"

#include <new>

extern "C" int __cdecl update_profile_message();
extern "C" int __cdecl update_profile_confirmation();
extern "C" void __cdecl dispatch_indexed_event(unsigned index);
extern "C" bool __cdecl is_menu_initial_press(
    int primary, int modifier_a, int modifier_b, int modifier_c);
extern "C" __declspec(dllimport) int __cdecl wsprintfA(
    char *buffer, const char *format, ...);
extern "C" const char continue_save_prompt[];
extern "C" const char continue_save_success[];
extern "C" const char continue_count_prompt_format[];

namespace th105 {

struct ContinueOwnerRuntimeView {
    unsigned char unknown_000[0x84];
    int end_pending_84;
    unsigned char unknown_088[0x18];
    int remaining_continues_a0;
    unsigned char active_a4;

    void reset_battle_round_471180();
};

struct ContinueGameConfigView {
    unsigned char unknown_000[0x71];
    unsigned char continue_flag_71;
};

struct ProfileFooterMemberView {
    void render_profile_menu_footer();
};

ContinueGameConfigView *get_game_config_for_continue();
void refresh_continue_network_state();
void start_scene_fade_in(unsigned int color, int duration);
void start_scene_fade_out(unsigned int color, int duration);
// This caller consumes only AL. The canonical callee at 0x0043B2C0 keeps its
// independently exact int return contract in SceneTransitionState.cpp.
bool is_scene_fade_in_progress();
void __cdecl install_menu_object(void *object);

// Current call sites allocate 0x44 physical bytes before invoking the exact
// CMenuEnd constructor at 0x00445100. This is an allocation-extent view only;
// the named CMenuEnd prefix below remains the independently proved 0x40 bytes.
struct CMenuEndDispatchView {
    unsigned char observed_extent_00[0x44];
    explicit CMenuEndDispatchView(void *owner);
};

class CMenuContinue : public Menu {
public:
    explicit CMenuContinue(void *owner);
    virtual ~CMenuContinue();
    virtual void unknown_menu_method();
    virtual bool update();
    virtual void render();

private:
    unsigned char state_04;
    CDesignBase design_08;
    void *owner_3c;
};

class CMenuEnd : public Menu {
public:
    explicit CMenuEnd(void *owner);
    virtual ~CMenuEnd();
    virtual void unknown_menu_method();
    virtual bool update();
    virtual void render();

private:
    void initialize_runtime_4404f0();
    void hide_profile_message_43f8d0();

    unsigned char state_04;
    CDesignBase design_08;
    void *owner_3c;
};

typedef char CMenuContinue_size_must_be_0x40[
    sizeof(CMenuContinue) == 0x40 ? 1 : -1];
typedef char CMenuEnd_size_must_be_0x40[
    sizeof(CMenuEnd) == 0x40 ? 1 : -1];
typedef char CMenuEndDispatchView_size_must_be_0x44[
    sizeof(CMenuEndDispatchView) == 0x44 ? 1 : -1];

bool CMenuContinue::update()
{
    ContinueOwnerRuntimeView *owner =
        static_cast<ContinueOwnerRuntimeView *>(owner_3c);

    switch (static_cast<signed char>(state_04)) {
    case 0:
        show_profile_message(continue_save_prompt, true);
        state_04 = 1;
        break;
    case 1:
        switch (update_profile_message()) {
        case 2:
        case 4:
            state_04 = 10;
            break;
        case 3:
            show_profile_result(continue_save_success);
            refresh_continue_network_state();
            state_04 = 2;
            break;
        }
        break;
    case 2:
        switch (update_profile_confirmation()) {
        case 1:
        case 2:
            state_04 = 10;
            break;
        }
        break;
    case 10: {
        char message[1024];
        wsprintfA(
            message,
            continue_count_prompt_format,
            owner->remaining_continues_a0);
        show_profile_message(message, true);
        state_04 = 11;
        break;
    }
    case 11:
        switch (update_profile_message()) {
        case 2:
        case 4:
            set_session_setup_option(0);
            install_menu_object(new CMenuEndDispatchView(owner));
            break;
        case 3:
            --owner->remaining_continues_a0;
            owner->active_a4 = 1;
            state_04 = 12;
            break;
        }
        break;
    case 12:
        start_scene_fade_in(0xFF000000u, 60);
        state_04 = 13;
        break;
    case 13:
        if (is_scene_fade_in_progress())
            break;
        owner->reset_battle_round_471180();
        start_scene_fade_out(0xFF000000u, 60);
        return false;
    }
    return true;
}

void CMenuContinue::render()
{
    design_08.render();
    reinterpret_cast<ProfileFooterMemberView *>(this)
        ->render_profile_menu_footer();
}

bool CMenuEnd::update()
{
    ContinueOwnerRuntimeView *owner =
        static_cast<ContinueOwnerRuntimeView *>(owner_3c);
    if (owner != 0 && owner->end_pending_84 != 0)
        return true;

    switch (static_cast<signed char>(state_04)) {
    case 0:
        if (reinterpret_cast<int *>(get_combined_menu_input_counters())[2] != 1 &&
            reinterpret_cast<int *>(get_combined_menu_input_counters())[3] != 1 &&
            !is_menu_initial_press(1, 0, 0, 0))
            return true;
        dispatch_indexed_event(0x28);
        if (get_session_setup_option() != 1)
            goto complete;
        if (get_game_config_for_continue()->continue_flag_71 != 0) {
            refresh_continue_network_state();
            goto complete;
        }
        state_04 = 1;
        return true;
    case 1:
        show_profile_message(continue_save_prompt, false);
        state_04 = 2;
        return true;
    case 2:
        switch (update_profile_message()) {
        case 2:
        case 4:
            goto complete;
        case 3:
            show_profile_result(continue_save_success);
            refresh_continue_network_state();
            state_04 = 3;
            return true;
        default:
            return true;
        }
    case 3:
        switch (update_profile_confirmation()) {
        case 1:
        case 2:
            goto complete;
        default:
            break;
        }
        break;
    default:
        break;
    }
    return true;

complete:
    if (owner != 0)
        owner->end_pending_84 = 1;
    else
        g_scene_mode = 2;
    return true;
}

void CMenuEnd::render()
{
    design_08.render();
    render_profile_tiles();
    reinterpret_cast<ProfileFooterMemberView *>(this)
        ->render_profile_menu_footer();
}

} // namespace th105
