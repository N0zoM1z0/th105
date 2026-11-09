#include "Collision.hpp"

namespace th105 {

int AttackCandidate::calculate_descriptor_scaled_quantity_1c()
{
    return static_cast<int>(
        calculate_base_hit_quantity() *
        static_cast<float>(prepared_frame_1a4->quantity_1c));
}

int AttackCandidate::calculate_descriptor_scaled_quantity_20()
{
    return static_cast<int>(
        calculate_base_hit_quantity() *
        static_cast<float>(prepared_frame_1a4->quantity_20));
}

} // namespace th105

// Native 0x45C090 is the PAT record vector provider, not a game method.
template std::vector<th105::PatRecord88>::size_type std::vector<th105::PatRecord88>::size() const;
