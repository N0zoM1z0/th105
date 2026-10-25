#pragma once
namespace th105 {
// Pointer-only call view; never instantiate/embed a recovered full Fighter.
class SakuyaActionEntryView {
public:
 virtual void slot00();virtual void slot04();virtual void slot08();virtual void slot0c();
 virtual void slot10();virtual void slot14();virtual void slot18();virtual void slot1c();
 virtual void slot20();virtual void slot24();virtual void slot28();virtual void slot2c();
 virtual void slot30();virtual void slot34();virtual void slot38();virtual void initialize_action_entry();
 void zero_motion();
 void initialize_common_action_entry();
};
}
