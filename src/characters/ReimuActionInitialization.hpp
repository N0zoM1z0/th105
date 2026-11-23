#pragma once
#include <stddef.h>

namespace th105 {

// Pointer-only receiver. No complete Reimu layout is claimed or instantiated.
class ReimuFinalizationView {
public:
 virtual void slot00();
 virtual void slot04();
 virtual void slot08();
 virtual void slot0c();
 virtual void slot10();
 virtual void slot14();
 virtual void slot18();
 virtual void slot1c();
 virtual void slot20();
 virtual void slot24();
 virtual void slot28();
 virtual void slot2c();
 virtual void slot30();
 virtual void slot34();
 virtual void slot38();
 virtual void initialize_action_entry();
 void advance_secondary_event_effect_cycle();
 void emit_effect(int, float, float, unsigned char, int);
 int spawn_owned_object(int, float, float, int, int, int, int);
 void publish_layout_scalar(float);
 void dispatch_event(unsigned);
 void zero_motion();
 void dispatch_sequence_window(signed char, int, int);
 void finalize_sequence_entry(int);
 void publish_texture_state(signed char, short);
 void copy_action_word_176_to_174();
 void initialize_common_action_entry();

 unsigned char unknown_004[0xe8];
 float x_ec;
 float y_f0;
 float velocity_x_f4;
 float velocity_y_f8;
 unsigned char unknown_0fc[4];
 float acceleration_y_100;
 signed char facing_104;
 unsigned char unknown_105[0x37];
 short action_id_13c;
};

typedef char ReimuActionEntry_x_ec_offset[
    offsetof(ReimuFinalizationView, x_ec) == 0xec ? 1 : -1];
typedef char ReimuActionEntry_y_f0_offset[
    offsetof(ReimuFinalizationView, y_f0) == 0xf0 ? 1 : -1];
typedef char ReimuActionEntry_velocity_x_f4_offset[
    offsetof(ReimuFinalizationView, velocity_x_f4) == 0xf4 ? 1 : -1];
typedef char ReimuActionEntry_velocity_y_f8_offset[
    offsetof(ReimuFinalizationView, velocity_y_f8) == 0xf8 ? 1 : -1];
typedef char ReimuActionEntry_acceleration_y_100_offset[
    offsetof(ReimuFinalizationView, acceleration_y_100) == 0x100 ? 1 : -1];
typedef char ReimuActionEntry_facing_104_offset[
    offsetof(ReimuFinalizationView, facing_104) == 0x104 ? 1 : -1];
typedef char ReimuActionEntry_action_id_13c_offset[
    offsetof(ReimuFinalizationView, action_id_13c) == 0x13c ? 1 : -1];

} // namespace th105
