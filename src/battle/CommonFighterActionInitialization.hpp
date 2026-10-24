#pragma once
namespace th105 {
// Only a returned record prefix is accessed; no record/owner is instantiated.
struct CommonEntryCardSlot { short code; };
struct CommonEntryCardDeque { CommonEntryCardSlot &at(unsigned); };
class CommonActionEntryView {
public:
 virtual void slot00();virtual void slot04();virtual int set_action(short);
 void initialize_common_action_entry();
 void zero_motion();
 void advance_secondary_event_effect_cycle();
 void emit_effect(short,float,float,unsigned char,int);
 void publish_layout_scalar(float);
 void dispatch_event(unsigned);
 void dispatch_sequence_window(signed char,int,int);
};
}
