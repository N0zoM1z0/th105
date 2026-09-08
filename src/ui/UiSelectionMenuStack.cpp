#include <list>

namespace th105 {

struct UiSelectionMenu;
extern std::list<UiSelectionMenu *> g_ui_selection_menu_stack;

void push_ui_selection_menu(UiSelectionMenu *menu)
{
    g_ui_selection_menu_stack.push_back(menu);
}

} // namespace th105
