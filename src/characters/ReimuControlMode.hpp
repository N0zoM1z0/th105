#ifndef TH105_REIMU_CONTROL_MODE_HPP
#define TH105_REIMU_CONTROL_MODE_HPP
namespace th105 {
// Pointer-only call surfaces. Never instantiate or embed as complete owners.
class ReimuControlSequenceView { public: short *at(unsigned index); };
class ReimuControlModeView {
public:
    virtual void slot_00();
    virtual void slot_04();
    virtual int set_action(short action);
    virtual int set_sequence(int sequence);
    virtual void slot_10();
    virtual void slot_14();
    virtual void slot_18();
    virtual void slot_1c();
    virtual void slot_20();
    virtual void slot_24();
    virtual void slot_28();
    virtual void slot_2c();
    virtual void slot_30();
    virtual void slot_34();
    virtual void slot_38();
    virtual void slot_3c();
    virtual void slot_40();
    virtual void slot_44();
    virtual void slot_48();
    virtual void slot_4c();
    virtual void slot_50();
    virtual void slot_54();
    virtual void update_cpu_action_policy();
    void update_control_mode();
    void face_opponent_and_flip_horizontal_velocity();
};
int __cdecl selector_random_roll(int limit);
}
#endif
