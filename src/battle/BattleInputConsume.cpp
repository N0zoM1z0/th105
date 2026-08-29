#include "BattleController.hpp"
#include "SpellData.hpp"

namespace th105 {

struct SynchronizedControlQueueView {
    unsigned char reserved_00[0x3c];
    ShortDeque8 controls_3c;
};

unsigned short BattleInputGate::peek_front_control_word(
    unsigned short *output)
{
    lock_124.enter();

    SynchronizedControlQueueView *state =
        reinterpret_cast<SynchronizedControlQueueView *>(input_104);
    if (state->controls_3c.live_count_10)
        *output = static_cast<unsigned short>(
            *state->controls_3c.front_checked());
    else
        *output = 0;

    const unsigned short value = *output;
    lock_124.leave();
    return value;
}

typedef char SynchronizedControlQueueView_queue_offset[
    offsetof(SynchronizedControlQueueView, controls_3c) == 0x3c ? 1 : -1];

} // namespace th105
