#include "Collision.hpp"

namespace th105 {

bool CollisionContext::try_group_b_pair_response(
    CollisionObject *source,
    CollisionObject *other)
{
    if ((source->frame_1a4->flags_4c & 0x80000) == 0) {
        return false;
    }
    if ((other->frame_158->flags_50 & 0x20000) != 0) {
        return false;
    }
    if (other->gate_189 != 0) {
        return false;
    }
    if (!test_group_b_against_group_b(source, other)) {
        return false;
    }

    other->facing_104 = -other->facing_104;
    other->owner_16c = source->owner_16c;
    other->owner_170 = source->owner_170;
    ++source->counter_188;
    ++other->counter_188;
    reset_collision_extents();
    return true;
}

void CollisionContext::resolve_group_b_object_clash(
    CollisionObject *left,
    CollisionObject *right)
{
    if (!test_group_b_against_group_b(left, right)) {
        return;
    }

    short left_value_12 = left->frame_1a8->value_12;
    if (left_value_12 != 0) {
        short right_value_12 = right->frame_1a8->value_12;
        if (left_value_12 == right_value_12) {
            left->result_180 = 4;
            left->result_slot_184 = left->source_1a0 - 1;
            right->result_180 = 4;
            right->result_slot_184 = right->source_1a0 - 1;
            reset_collision_extents();
            return;
        }
        if (left_value_12 < right_value_12) {
            left->result_180 = 4;
            left->result_slot_184 = left->source_1a0 - 1;
            right->result_slot_184 = right->source_1a0 - 1;
            right->result_180 = 8;
            reset_collision_extents();
            return;
        }
        if (right_value_12 != 0) {
            left->result_180 = 8;
            left->result_slot_184 = left->source_1a0 - 1;
            right->result_180 = 4;
            right->result_slot_184 = right->source_1a0 - 1;
            reset_collision_extents();
            return;
        }
        if (left_value_12 < right->frame_1a8->value_10) {
            left->result_180 = 4;
            left->result_slot_184 = right->source_1a0 - 1;
            reset_collision_extents();
            return;
        }
        left->result_180 = 8;
        left->result_slot_184 = left->source_1a0 - 1;
        right->result_180 = 5;
        right->result_slot_184 = right->source_1a0 - 1;
        reset_collision_extents();
        return;
    }

    CollisionObjectClashFrame *right_frame = right->frame_1a8;
    if (right_frame->value_12 != 0) {
        if (right_frame->value_10 >= 0) {
            left->result_180 = 5;
            left->result_slot_184 = left->source_1a0 - 1;
            right->result_180 = 8;
            right->result_slot_184 = right->source_1a0 - 1;
            reset_collision_extents();
            return;
        }
        right->result_slot_184 = right->source_1a0 - 1;
        right->result_180 = 4;
        reset_collision_extents();
        return;
    }

    short left_value_10 = left->frame_1a8->value_10;
    if (right_frame->value_10 < left_value_10) {
        right->result_slot_184 = right->source_1a0 - 1;
        right->result_180 = 4;
        reset_collision_extents();
        return;
    }
    if (left_value_10 < right_frame->value_10) {
        left->result_180 = 4;
        left->result_slot_184 = left->source_1a0 - 1;
        reset_collision_extents();
        return;
    }

    left->result_180 = 8;
    left->result_slot_184 = left->source_1a0 - 1;
    right->result_180 = 8;
    right->result_slot_184 = right->source_1a0 - 1;
    reset_collision_extents();
}

} // namespace th105
