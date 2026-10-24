#pragma once
namespace th105 {
// Pointer-only virtual receiver. Never instantiate or embed as a full Fighter.
// Original nominal layout/TU and numeric-state meanings remain provisional.
class SuikaActionEntryView {
public:
 virtual void slot00();virtual void slot04();virtual void slot08();virtual void slot0c();
 virtual void slot10();virtual void slot14();virtual void slot18();virtual void slot1c();
 virtual void slot20();virtual void slot24();virtual void slot28();virtual void slot2c();
 virtual void slot30();virtual void slot34();virtual void slot38();virtual void initialize_action_entry();
 void zero_motion();
 void dispatch_character_wave_handle(unsigned);
 int spawn_owned_object(int,float,float,unsigned char,int,float *,int);
 void initialize_common_action_entry();
};
int __cdecl selector_random_roll(int);
}
