#include "UiSelectionState.hpp"

#include <list>

namespace th105 {

struct UiSelectionMenu {
    void **vtable;
};

typedef void (__thiscall *UiSelectionTrackingCallback)(UiSelectionMenu *);

extern unsigned g_ui_selection_state;
extern unsigned char g_ui_selection_snapshot;
extern unsigned char g_ui_selection_fade;
extern std::list<UiSelectionMenu *> g_ui_selection_menu_stack;

extern "C" bool __cdecl has_ui_selection_state_changed()
{
    return g_ui_selection_state - g_ui_selection_snapshot > 0;
}

extern "C" void __cdecl set_ui_selection_state_tracking(char enabled)
{
    if (enabled) {
        g_ui_selection_snapshot =
            static_cast<unsigned char>(g_ui_selection_state);
        g_ui_selection_fade = 0;
        return;
    }

    g_ui_selection_snapshot = 0;
    g_ui_selection_fade = 0xff;
    if (g_ui_selection_state == 0)
        return;

    UiSelectionMenu *menu = g_ui_selection_menu_stack.back();
    reinterpret_cast<UiSelectionTrackingCallback>(menu->vtable[1])(menu);
}

} // namespace th105
