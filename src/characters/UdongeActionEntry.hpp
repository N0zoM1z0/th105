#ifndef TH105_UDONGE_ACTION_ENTRY_HPP
#define TH105_UDONGE_ACTION_ENTRY_HPP
namespace th105 {
// Pointer-only call view. Never construct or embed this receiver.
// Byte-facing effect call view is local; shared helper declarations stay unchanged.
class UdongeActionEntryView {
public:
    void initialize_action_entry();
    int reset_action_visual_state();
    void advance_secondary_event_effect_cycle();
    void emit_effect(int effect, float x, float y, unsigned char direction, int trailing);
    void publish_battle_layout_scalar(float value);
    void dispatch_indexed_event_member(unsigned index);
    void zero_velocity_acceleration();
    int spawn_owned_object_via_manager(int action, float x, float y,
        int direction, int layer, const unsigned *words, int count);
    void dispatch_character_wave_handle(unsigned index);
    void initialize_common_action_state();
};
}
#endif
