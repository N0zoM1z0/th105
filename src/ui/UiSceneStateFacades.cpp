namespace th105 {

void trim_profile_ui_menu_stack();
void set_ui_selection_state_tracking(char enabled);

void trim_profile_ui_menu_stack_facade()
{
    trim_profile_ui_menu_stack();
}

void set_ui_selection_state_tracking_facade(char enabled)
{
    set_ui_selection_state_tracking(enabled);
}

} // namespace th105
