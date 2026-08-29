#include <list>

namespace th105 {

struct UiSelectionMenu {
    void **vtable;
};

struct UiSelectionMenuDeleteView {
    virtual ~UiSelectionMenuDeleteView();
};

extern std::list<UiSelectionMenu *> g_ui_selection_menu_stack;

void __cdecl pop_profile_ui_menu_43ff40()
{
    UiSelectionMenu *menu = g_ui_selection_menu_stack.back();
    if (menu != 0)
        delete reinterpret_cast<UiSelectionMenuDeleteView *>(menu);
    g_ui_selection_menu_stack.pop_back();
}

} // namespace th105
