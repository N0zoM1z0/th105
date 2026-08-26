#include "Collision.hpp"

namespace th105 {

float AttackCandidate::calculate_forwarded_quantity()
{
    float result = source_168->source_factor_4bc *
        related_fighter_170->target_factor_4c0;
    result = result * owner_16c->scalar_494;

    if (related_fighter_170->value_174 < 0) {
        result = result * 0.7f;
    } else if (related_fighter_170->maximum_176 > related_fighter_170->value_174) {
        result =
            ((static_cast<float>(related_fighter_170->value_174) /
              static_cast<float>(related_fighter_170->maximum_176)) * 0.3f + 0.7f) *
            result;
    }

    if (scalar_table_index_17c >= 0 && scalar_table_index_17c < 0x20) {
        result =
            ((static_cast<float>(source_168->scalar_modifier_table_604[
                  scalar_table_index_17c]) / 10.0f) + 1.0f) * result;
    }

    CollisionObjectFrame50 *frame =
        *reinterpret_cast<CollisionObjectFrame50 **>(
            reinterpret_cast<unsigned char *>(this) + 0x158);
    const unsigned flags = frame->flags_50;
    if ((flags & 0x1000) != 0) {
        result = source_168->source_modifier_4c8 * result;
    }
    if ((flags & 0x800) != 0) {
        result = source_168->source_modifier_4cc * result;
    }

    const unsigned char modifiers = owner_16c->flag_491;
    if ((modifiers & 1) != 0) {
        result = result * 0.8f;
    }
    if ((modifiers & 2) != 0) {
        result = result * 0.8f;
    }
    if ((modifiers & 4) != 0) {
        result = result * 0.8f;
    }
    if ((modifiers & 8) != 0) {
        result = result * 0.85f;
    }
    if ((modifiers & 0x10) != 0) {
        result = result * 0.85f;
    }
    return result;
}

float AttackCandidate::calculate_base_hit_quantity()
{
    float result = source_168->source_factor_4bc *
        related_fighter_170->target_factor_4c0;
    result = result * owner_16c->scalar_494;

    if (related_fighter_170->scalar_quantity_198 < 0) {
        result = result * 0.7f;
    } else if (related_fighter_170->maximum_176 > related_fighter_170->scalar_quantity_198) {
        result =
            ((static_cast<float>(related_fighter_170->scalar_quantity_198) /
              static_cast<float>(related_fighter_170->maximum_176)) * 0.3f + 0.7f) *
            result;
    }

    if (scalar_table_index_17c >= 0 && scalar_table_index_17c < 0x20) {
        result =
            ((static_cast<float>(source_168->scalar_modifier_table_604[
                  scalar_table_index_17c]) / 10.0f) + 1.0f) * result;
    }

    const unsigned flags = frame_1a4->flags_50;
    if ((flags & 0x1000) != 0) {
        result = source_168->source_modifier_4c8 * result;
    }
    if ((flags & 0x800) != 0) {
        result = source_168->source_modifier_4cc * result;
    }

    const unsigned char modifiers = owner_16c->flag_491;
    if ((modifiers & 1) != 0) {
        result = result * 0.8f;
    }
    if ((modifiers & 2) != 0) {
        result = result * 0.8f;
    }
    if ((modifiers & 4) != 0) {
        result = result * 0.8f;
    }
    if ((modifiers & 8) != 0) {
        result = result * 0.85f;
    }
    if ((modifiers & 0x10) != 0) {
        result = result * 0.85f;
    }
    return result;
}

} // namespace th105
