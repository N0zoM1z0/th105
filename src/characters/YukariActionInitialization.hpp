#pragma once
namespace th105 {
// Pointer-only views: neither the scratch prefix nor full Fighter is instantiated.
// Numeric states and original nominal class/TU details remain provisional.
struct YukariEntryScratchView { void reset(); };
class YukariActionEntryView {
public:
 virtual void slot00();virtual void slot04();virtual int set_action(short);
 virtual void slot0c();virtual void slot10();virtual void slot14();virtual void slot18();virtual void slot1c();
 virtual void slot20();virtual void slot24();virtual void slot28();virtual void slot2c();
 virtual void slot30();virtual void slot34();virtual void slot38();
 virtual void initialize_action_entry();
 void advance_secondary_event_effect_cycle();
 void emit_effect(short,float,float,unsigned char,int);
 int spawn_owned_object(int,float,float,unsigned char,int,float *,int);
 void publish_layout_scalar(float);
 void dispatch_event(unsigned);
 void zero_motion();
 unsigned char advance_frame_and_dispatch();
 void dispatch_character_wave_handle(unsigned);
 void initialize_common_action_entry();
};
}
