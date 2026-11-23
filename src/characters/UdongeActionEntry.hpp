#ifndef TH105_UDONGE_ACTION_ENTRY_HPP
#define TH105_UDONGE_ACTION_ENTRY_HPP

#include <stddef.h>

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

    unsigned char unknown_000[0xec];
    float x_ec;
    float y_f0;
    float velocity_x_f4;
    float velocity_y_f8;
    unsigned char unknown_0fc[0x4];
    float acceleration_y_100;
    signed char facing_104;
    unsigned char unknown_105[0x37];
    short action_id_13c;
    unsigned char unknown_13e[0x42];
    int phase_state_180;
};

typedef char UdongeActionEntry_x_ec_offset[
    offsetof(UdongeActionEntryView, x_ec) == 0xec ? 1 : -1];
typedef char UdongeActionEntry_y_f0_offset[
    offsetof(UdongeActionEntryView, y_f0) == 0xf0 ? 1 : -1];
typedef char UdongeActionEntry_velocity_x_f4_offset[
    offsetof(UdongeActionEntryView, velocity_x_f4) == 0xf4 ? 1 : -1];
typedef char UdongeActionEntry_velocity_y_f8_offset[
    offsetof(UdongeActionEntryView, velocity_y_f8) == 0xf8 ? 1 : -1];
typedef char UdongeActionEntry_acceleration_y_100_offset[
    offsetof(UdongeActionEntryView, acceleration_y_100) == 0x100 ? 1 : -1];
typedef char UdongeActionEntry_facing_104_offset[
    offsetof(UdongeActionEntryView, facing_104) == 0x104 ? 1 : -1];
typedef char UdongeActionEntry_action_id_13c_offset[
    offsetof(UdongeActionEntryView, action_id_13c) == 0x13c ? 1 : -1];
typedef char UdongeActionEntry_phase_state_180_offset[
    offsetof(UdongeActionEntryView, phase_state_180) == 0x180 ? 1 : -1];
}
#endif
