#include "Collision.hpp"

namespace th105 {

int AttackCandidate::calculate_descriptor_scaled_quantity_1c()
{
    return static_cast<int>(
        calculate_base_hit_quantity() *
        static_cast<float>(frame_1a4->quantity_1c));
}

int AttackCandidate::calculate_descriptor_scaled_quantity_20()
{
    return static_cast<int>(
        calculate_base_hit_quantity() *
        static_cast<float>(frame_1a4->quantity_20));
}

int ByteStrideRange::count_0x88_byte_stride_entries()
{
    if (begin_04 == 0) {
        return 0;
    }
    return (end_08 - begin_04) / 0x88;
}

} // namespace th105
