#ifndef TH105_ALICE_INPUT_POLICY_HPP
#define TH105_ALICE_INPUT_POLICY_HPP
namespace th105 {
// Pointer-only call view. Do not construct or embed this receiver.
class AliceInputPolicyView {
public:
    virtual void slot00();
    virtual void slot04();
    virtual int set_action(int action);
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
    virtual void slot3c();
    virtual void slot40();
    virtual void slot44();
    virtual void slot48();
    virtual void slot4c();
    virtual void dispatch_input();
    void pop_sequence();
    int pack_input();
    int reset_input();
    unsigned char gate493ac0();
    unsigned char gate493b40();
    unsigned char gate493c50();
    unsigned char gate493d90(int window, int bypass);
    unsigned char gate493f90(int window, int override_value);
    unsigned char gate4940e0(int window, int bypass, int count, int minimum);
    unsigned char gate4941d0(int window, int bypass, int count, int minimum);
    unsigned char gate4942c0(int window, int bypass, int count);
    unsigned char gate494450(int window);
    unsigned char front_ready(signed char index);
    int finalize_command(int action, int window);
    short command_window(short key);
};
class AliceInputSequenceView {
public:
    short *at(unsigned index);
};
int __fastcall is_y_at_or_below_stage_surface(void *fighter);
}
#endif
