#pragma once
namespace th105 {
// Pointer-only receiver/returned-record views; no complete owner is instantiated.
// Original nominal class layout and source partition remain provisional.
struct PatchouliEntryScratchView { void reset(); };
struct PatchouliEntryCardSlot { short code; };
struct PatchouliEntryCardDeque { PatchouliEntryCardSlot &at(unsigned); };
class PatchouliActionEntryView {
public:
 virtual void slot00();virtual void slot04();virtual void slot08();virtual void slot0c();
 virtual void slot10();virtual void slot14();virtual void slot18();virtual void slot1c();
 virtual void slot20();virtual void slot24();virtual void slot28();virtual void slot2c();
 virtual void slot30();virtual void slot34();virtual void slot38();virtual void initialize_action_entry();
 void zero_motion();
 void emit_effect(short,float,float,unsigned char,int);
 void dispatch_sequence_window(signed char,int,int);
 void finalize_sequence_entry(int);
 void publish_texture_state(signed char,short);
 void copy_action_word_176_to_174();
 void dispatch_event(unsigned);
 void initialize_common_action_entry();
};
float __fastcall stage_surface_height_at_x(PatchouliActionEntryView *);
}
