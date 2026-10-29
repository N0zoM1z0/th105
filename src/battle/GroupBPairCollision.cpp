// Complete JP1.06a group-B pair predicate. Source398/native398 remains nonexact.
#include "Collision.hpp"
#include <stddef.h>
namespace th105 {
namespace {
// Pointer-only prepared-geometry view; the group-B block has five physical
// boxes before group A starts at204 and five descriptor pointers at318.
struct PreparedGroupBView {
 unsigned char prefix[0x1b0];
 signed char count;
 unsigned char alignment_1b1[3];
 CollisionAabb boxes[5];
 unsigned char gap_204[0x114];
 ShapeWords *descriptors[5];
};
typedef char GroupBCountOffset[offsetof(PreparedGroupBView, count) == 0x1b0 ? 1 : -1];
typedef char GroupBBoxesOffset[offsetof(PreparedGroupBView, boxes) == 0x1b4 ? 1 : -1];
typedef char GroupBDescriptorsOffset[offsetof(PreparedGroupBView, descriptors) == 0x318 ? 1 : -1];
PreparedGroupBView *group_b(CollisionObject *object)
{ return reinterpret_cast<PreparedGroupBView *>(object); }
}

int CollisionContext::test_group_b_against_group_b(
    CollisionObject *first,
    CollisionObject *second)
{
    int result = 0;
    signed char first_index = 0;
    if (group_b(first)->count > 0) {
        do {
            signed char second_index = 0;

            if (group_b(first)->descriptors[first_index] != 0) {
                if (group_b(second)->count > 0) {
                    CollisionAabb *first_box = (&group_b(first)->boxes[first_index]);
                    do {
                        ShapeWords *second_descriptor =
                            group_b(second)->descriptors[second_index];
                        if (second_descriptor != 0)
                            result |= test_descriptor_shapes_overlap(
                                first_box, group_b(first)->descriptors[first_index],
                                (&group_b(second)->boxes[second_index]), second_descriptor);
                        else
                            result |= test_aabb_against_descriptor_shape(
                                first_box, group_b(first)->descriptors[first_index], (&group_b(second)->boxes[second_index]));
                        ++second_index;
                    } while (second_index < group_b(second)->count);
                }
            } else if (group_b(second)->count > 0) {
                CollisionAabb *first_box = (&group_b(first)->boxes[first_index]);
                do {
                    ShapeWords *second_descriptor =
                        group_b(second)->descriptors[second_index];
                    int hit;
                    if (second_descriptor != 0) {
                        hit = test_aabb_against_descriptor_shape(
                            (&group_b(second)->boxes[second_index]), second_descriptor, first_box);
                    } else {
                        CollisionAabb *second_box = (&group_b(second)->boxes[second_index]);
                        int overlap = second_box->top - first_box->bottom;
                        overlap &= first_box->top - second_box->bottom;
                        overlap &= first_box->left - second_box->right;
                        overlap &= second_box->left - first_box->right;
                        if ((static_cast<unsigned>(overlap) & 0x80000000u) != 0) {
                            accumulate_collision_extents(
                                &first_box->left, &second_box->left);
                            hit = 1;
                        } else {
                            hit = 0;
                        }
                    }
                    result |= hit;
                    ++second_index;
                } while (second_index < group_b(second)->count);
            }
            ++first_index;
        } while (first_index < group_b(first)->count);
    }
    return result;
}

}
