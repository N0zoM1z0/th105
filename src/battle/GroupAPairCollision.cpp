// Complete group-A/group-B traversal; native per-call descriptor reloads.
// Whole398/398 remains nonexact; see GROUP_A_PAIR_COLLISION_2026_11_01.md.
#include "battle/Collision.hpp"
#include <stddef.h>
namespace th105 {
namespace {
// Pointer-only view; exact geometry preparation establishes both five-box
// groups and the actual descriptor-storage/primary-box interval.
struct PreparedPairView {
 unsigned char prefix[0x1af];
 signed char count_a, count_b;
 unsigned char alignment_1b1[3];
 CollisionAabb boxes_b[5];
 CollisionAabb boxes_a[5];
 ShapeWords shapes_a[5];
 ShapeWords shapes_b[5];
 CollisionAabb primary_box;
 ShapeWords *descriptors_a[5];
 ShapeWords *descriptors_b[5];
};
typedef char PairCountA[offsetof(PreparedPairView,count_a)==0x1af?1:-1];
typedef char PairCountB[offsetof(PreparedPairView,count_b)==0x1b0?1:-1];
typedef char PairBoxesA[offsetof(PreparedPairView,boxes_a)==0x204?1:-1];
typedef char PairBoxesB[offsetof(PreparedPairView,boxes_b)==0x1b4?1:-1];
typedef char PairDescriptorsA[offsetof(PreparedPairView,descriptors_a)==0x304?1:-1];
typedef char PairDescriptorsB[offsetof(PreparedPairView,descriptors_b)==0x318?1:-1];
PreparedPairView *prepared(CollisionObject *object)
{ return reinterpret_cast<PreparedPairView *>(object); }
}

int CollisionContext::test_group_a_against_group_b(
    CollisionObject *first,
    CollisionObject *second)
{
    int result = 0;
    signed char first_index = 0;
    if (prepared(first)->count_a > 0) {
        do {
            signed char second_index = 0;

            if (prepared(first)->descriptors_a[first_index] != 0) {
                if (prepared(second)->count_b > 0) {
                    CollisionAabb *first_box = (&prepared(first)->boxes_a[first_index]);
                    do {
                        ShapeWords *second_descriptor =
                            prepared(second)->descriptors_b[second_index];
                        if (second_descriptor != 0)
                            result |= test_descriptor_shapes_overlap(
                                first_box, prepared(first)->descriptors_a[first_index],
                                (&prepared(second)->boxes_b[second_index]), second_descriptor);
                        else
                            result |= test_aabb_against_descriptor_shape(
                                first_box, prepared(first)->descriptors_a[first_index], (&prepared(second)->boxes_b[second_index]));
                        ++second_index;
                    } while (second_index < prepared(second)->count_b);
                }
            } else if (prepared(second)->count_b > 0) {
                CollisionAabb *first_box = (&prepared(first)->boxes_a[first_index]);
                do {
                    ShapeWords *second_descriptor =
                        prepared(second)->descriptors_b[second_index];
                    int hit;
                    if (second_descriptor != 0) {
                        hit = test_aabb_against_descriptor_shape(
                            (&prepared(second)->boxes_b[second_index]), second_descriptor, first_box);
                    } else {
                        CollisionAabb *second_box = (&prepared(second)->boxes_b[second_index]);
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
                } while (second_index < prepared(second)->count_b);
            }
            ++first_index;
        } while (first_index < prepared(first)->count_a);
    }
    return result;
}

}
