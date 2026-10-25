#pragma once
namespace th105 {
// Pointer-only views; never instantiate/embed complete Fighter owners.
struct AyaEntryScratchView { void reset(); };
class AyaActionEntryView {
public:
 virtual void slot00();virtual void slot04();virtual int set_action_and_finalize(short);
 virtual void slot0c();virtual void slot10();virtual void slot14();virtual void slot18();virtual void slot1c();
 virtual void slot20();virtual void slot24();virtual void slot28();virtual void slot2c();
 virtual void slot30();virtual void slot34();virtual void slot38();virtual void initialize_action_entry();
 void zero_motion();
 unsigned char advance_frame_and_dispatch();
 void dispatch_character_wave_handle(unsigned int);
 void initialize_common_action_entry();
};
}
