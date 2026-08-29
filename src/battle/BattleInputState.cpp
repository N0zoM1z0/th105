#include "BattleController.hpp"

namespace th105 {

unsigned char SynchronizedInputState::is_input_available_427680()
{
    return controls_3c.live_count_10 == 0;
}

} // namespace th105
