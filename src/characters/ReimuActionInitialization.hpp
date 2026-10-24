#pragma once
namespace th105 {
// Pointer-only receiver. No complete Reimu layout is claimed or instantiated.
class ReimuFinalizationView {
public:
 virtual void slot00();virtual void slot04();virtual void slot08();virtual void slot0c();
 virtual void slot10();virtual void slot14();virtual void slot18();virtual void slot1c();
 virtual void slot20();virtual void slot24();virtual void slot28();virtual void slot2c();
 virtual void slot30();virtual void slot34();virtual void slot38();
 virtual void initialize_action_entry();
 void advance_secondary_event_effect_cycle();
 void emit_effect(int,float,float,unsigned char,int);
 int spawn_owned_object(int,float,float,int,int,int,int);
 void publish_layout_scalar(float);
 void dispatch_event(unsigned);
 void zero_motion();
 void dispatch_sequence_window(signed char,int,int);
 void finalize_sequence_entry(int);
 void publish_texture_state(signed char,short);
 void copy_action_word_176_to_174();
 void initialize_common_action_entry();
};
}
