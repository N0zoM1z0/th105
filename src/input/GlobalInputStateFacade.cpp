namespace th105 {

// Narrow current-target view of the shared input-state service at 0x006FC618.
// The two member ABIs are independently canonical-exact at 0x0040A660 and
// 0x0040A6B0; this facade intentionally does not speculate about the rest of
// the concrete owner type.
struct GlobalInputStateFacade {
    bool is_initial_press(
        unsigned char key,
        bool require_modifier_0,
        bool require_modifier_1,
        bool require_modifier_2) const;
    void set_input_state_table_entry(unsigned char index, bool state);
};

extern GlobalInputStateFacade g_global_input_state;

bool __cdecl is_menu_initial_press(
    unsigned char key,
    bool require_modifier_0,
    bool require_modifier_1,
    bool require_modifier_2)
{
    return g_global_input_state.is_initial_press(
        key,
        require_modifier_0,
        require_modifier_1,
        require_modifier_2);
}

void __cdecl set_menu_input_state(unsigned char index, bool state)
{
    g_global_input_state.set_input_state_table_entry(index, state);
}

} // namespace th105
