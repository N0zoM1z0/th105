#include <list>

namespace th105 {

// Keep the list's source type identical to ProfileUiLifecycle.cpp. This TU
// additionally needs only the independently observed virtual deleting ABI.
struct UiSelectionMenu {
    void **vtable;
};
struct UiSelectionMenuDeleteView {
    virtual ~UiSelectionMenuDeleteView();
};

extern unsigned char g_ui_selection_snapshot;
extern unsigned char g_ui_selection_fade;
extern unsigned char g_ui_selection_active;
extern std::list<UiSelectionMenu *> g_ui_selection_menu_stack;

void __cdecl trim_profile_ui_menu_stack()
{
    unsigned char remove_count = static_cast<unsigned char>(
        static_cast<unsigned char>(g_ui_selection_menu_stack.size()) -
        g_ui_selection_snapshot);
    while (remove_count != 0) {
        UiSelectionMenu *menu = g_ui_selection_menu_stack.back();
        if (menu != 0)
            delete reinterpret_cast<UiSelectionMenuDeleteView *>(menu);
        g_ui_selection_menu_stack.pop_back();
        --remove_count;
    }
    if (g_ui_selection_menu_stack.empty()) {
        g_ui_selection_fade = 0;
        g_ui_selection_active = 0;
    }
}

} // namespace th105
