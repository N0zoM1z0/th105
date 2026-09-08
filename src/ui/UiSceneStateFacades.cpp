namespace th105 {

struct UiSelectionMenu;
void push_ui_selection_menu(UiSelectionMenu *menu);
void trim_profile_ui_menu_stack();
void set_ui_selection_state_tracking(char enabled);

void push_ui_selection_menu_facade(void *menu)
{
    push_ui_selection_menu(static_cast<UiSelectionMenu *>(menu));
}

void trim_profile_ui_menu_stack_facade()
{
    trim_profile_ui_menu_stack();
}

void set_ui_selection_state_tracking_facade(char enabled)
{
    set_ui_selection_state_tracking(enabled);
}

} // namespace th105
