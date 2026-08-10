#include "Collision.hpp"

namespace th105 {

int AttackCandidate::calculate_descriptor_scaled_quantity_1c()
{
    return static_cast<int>(
        calculate_base_hit_quantity() *
        static_cast<float>(frame_1a4->quantity_1c));
}

} // namespace th105
