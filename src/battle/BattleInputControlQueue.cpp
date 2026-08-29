#include "BattleController.hpp"

namespace th105 {

namespace {
class CriticalSectionScopeProbe {
public:
    explicit CriticalSectionScopeProbe(CriticalSectionWrapper *lock) : lock_(lock) { lock_->enter(); }
    ~CriticalSectionScopeProbe() { lock_->leave(); }
private:
    CriticalSectionWrapper *lock_;
};
}

struct BattleInputGateQueueView {
    FighterControlInput *first_control_input_000;
    FighterControlInput *second_control_input_004;
    unsigned char unknown_008[0x60];
    unsigned short first_control_low_bits_068;
    unsigned char unknown_06a[0x66];
    unsigned short second_control_low_bits_0d0;
    unsigned char unknown_0d2[0x1e];
    unsigned char publish_flags_0f0;
    unsigned char unknown_0f1[0x13];
    SynchronizedInputState *input_104;
    unsigned char unknown_108[0x1c];
    CriticalSectionWrapper lock_124;
    unsigned char published_140;
    unsigned char consumed_141;

    void queue_control_word(unsigned int packed_control_bits);
};

void BattleInputGateQueueView::queue_control_word(unsigned int packed_control_bits)
{
    CriticalSectionScopeProbe scope(&lock_124);
    packed_control_bits = static_cast<unsigned short>(packed_control_bits);
    SynchronizedInputState *input = input_104;
    input->controls_3c.push_back(
        reinterpret_cast<const short *>(&packed_control_bits));
}

}
