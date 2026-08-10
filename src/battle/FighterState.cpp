#include "Collision.hpp"

namespace th105 {

void Fighter::adjust_counter_482(short amount, int floor_value)
{
    counter_482 -= amount;
    if (counter_482 < 0) {
        counter_482 = 0;
    }
    if (state_4b8 == 5 && floor_value != 1) {
        floor_value = 0;
    }
    if (floor_486 < floor_value) {
        floor_486 = static_cast<short>(floor_value);
    }
}

} // namespace th105
