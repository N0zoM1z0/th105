#include "BattleController.hpp"

namespace th105 {

void __cdecl set_menu_input_state(unsigned char index, bool state);

unsigned short SynchronizedInputState::pop_control_word(
    unsigned short *output)
{
    if (controls_3c.live_count_10 != 0) {
        ShortDeque8 *queue = &controls_3c;
        *output = static_cast<unsigned short>(*queue->front_checked());

        if (queue->live_count_10 != 0) {
            ++queue->head_0c;
            if (queue->block_capacity_08 * 8 <= queue->head_0c)
                queue->head_0c = 0;
            --queue->live_count_10;
            if (queue->live_count_10 == 0)
                queue->head_0c = 0;
        }
    } else {
        *output = 0;
    }
    return *output;
}

void BattleInputGate::publish_synchronized_control_bits_427ac0()
{
    unsigned short control_word;
    if ((publish_flags_0f0 & 1) != 0) {
        lock_124.enter();
        input_104->pop_control_word(&control_word);
        lock_124.leave();

        first_control_low_bits_068 =
            static_cast<unsigned short>(control_word & 0x3ff);
        set_menu_input_state(59, (control_word & 0x8000) > 0);
        set_menu_input_state(60, (control_word & 0x4000) > 0);
        set_menu_input_state(61, (control_word & 0x2000) > 0);
        set_menu_input_state(63, (control_word & 0x1000) > 0);
        set_menu_input_state(64, (control_word & 0x0800) > 0);
        set_menu_input_state(65, (control_word & 0x0400) > 0);
    }

    if ((publish_flags_0f0 & 2) != 0) {
        lock_124.enter();
        input_104->pop_control_word(&control_word);
        lock_124.leave();
        second_control_low_bits_0d0 =
            static_cast<unsigned short>(control_word & 0x3ff);
    }
}

} // namespace th105
