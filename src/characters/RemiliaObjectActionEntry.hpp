#ifndef TH105_REMILIA_OBJECT_ACTION_ENTRY_HPP
#define TH105_REMILIA_OBJECT_ACTION_ENTRY_HPP
namespace th105 {
// Pointer-only primary-vtable view. Never construct or embed this receiver.
// Slot names and complete owner layout remain provisional.
class RemiliaObjectEntryView {
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void select_sequence(short sequence);
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
    void continue_action_980();
    void *spawn_parented(int action, float x, float y, signed char facing,
                         int layer, const unsigned *words, int count);
    void replace_secondary(int key, float half_width, int subdivisions,
                           int bands, int blend);
    void replace_auxiliary(short resource);
};
class RemiliaEntryMotionView {
public:
    void set_components(float angle, float magnitude);
};
int __cdecl selector_random_roll(int limit);
}
#endif
