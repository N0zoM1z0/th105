#include "Collision.hpp"

namespace th105 {

namespace {

signed char prepared_count(const CollisionObject *object, int offset)
{
    return *reinterpret_cast<const signed char *>(
        reinterpret_cast<const unsigned char *>(object) + offset);
}

CollisionAabb *prepared_box(CollisionObject *object, int base, signed char index)
{
    return reinterpret_cast<CollisionAabb *>(
        reinterpret_cast<unsigned char *>(object) + base + index * 0x10);
}

ShapeWords *prepared_descriptor(
    CollisionObject *object,
    int base,
    signed char index)
{
    return reinterpret_cast<ShapeWords **>(
        reinterpret_cast<unsigned char *>(object) + base)[index];
}

CollisionAabb *primary_box(CollisionObject *object)
{
    return *reinterpret_cast<CollisionAabb **>(
        reinterpret_cast<unsigned char *>(object) + 0x32c);
}

} // namespace

int CollisionContext::test_group_a_against_primary_box(
    CollisionObject *first,
    CollisionObject *second)
{
    CollisionAabb *primary = primary_box(second);
    if (primary == 0) {
        return 0;
    }

    int result = 0;
    for (signed char index = 0;
         index < prepared_count(first, 0x1af);
         ++index) {
        CollisionAabb *aabb = prepared_box(first, 0x204, index);
        ShapeWords *descriptor = prepared_descriptor(first, 0x304, index);
        int hit;

        if (descriptor != 0) {
            hit = test_aabb_against_descriptor_shape(
                aabb, descriptor, primary);
        } else {
            int overlap = primary->top - aabb->bottom;
            overlap &= aabb->top - primary->bottom;
            overlap &= aabb->left - primary->right;
            overlap &= primary->left - aabb->right;
            if (overlap < 0) {
                accumulate_collision_extents(&aabb->left, &primary->left);
                hit = 1;
            } else {
                hit = 0;
            }
        }
        result |= hit;
    }
    return result;
}

int CollisionContext::test_group_a_against_group_b(
    CollisionObject *first,
    CollisionObject *second)
{
    int result = 0;
    signed char first_index = 0;
    if (prepared_count(first, 0x1af) > 0) {
        do {
            CollisionAabb *first_box =
                prepared_box(first, 0x204, first_index);
            ShapeWords *first_descriptor =
                prepared_descriptor(first, 0x304, first_index);
            signed char second_index = 0;

            if (first_descriptor != 0) {
                if (prepared_count(second, 0x1b0) > 0) {
                    do {
                        CollisionAabb *second_box =
                            prepared_box(second, 0x1b4, second_index);
                        ShapeWords *second_descriptor =
                            prepared_descriptor(second, 0x318, second_index);
                        result |= second_descriptor == 0
                            ? test_aabb_against_descriptor_shape(
                                  first_box, first_descriptor, second_box)
                            : test_descriptor_shapes_overlap(
                                  first_box,
                                  first_descriptor,
                                  second_box,
                                  second_descriptor);
                        ++second_index;
                    } while (second_index < prepared_count(second, 0x1b0));
                }
            } else if (prepared_count(second, 0x1b0) > 0) {
                do {
                    CollisionAabb *second_box =
                        prepared_box(second, 0x1b4, second_index);
                    ShapeWords *second_descriptor =
                        prepared_descriptor(second, 0x318, second_index);
                    int hit;
                    if (second_descriptor == 0) {
                        int overlap = second_box->top - first_box->bottom;
                        overlap &= first_box->top - second_box->bottom;
                        overlap &= first_box->left - second_box->right;
                        overlap &= second_box->left - first_box->right;
                        if (overlap < 0) {
                            accumulate_collision_extents(
                                &first_box->left, &second_box->left);
                            hit = 1;
                        } else {
                            hit = 0;
                        }
                    } else {
                        hit = test_aabb_against_descriptor_shape(
                            second_box, second_descriptor, first_box);
                    }
                    result |= hit;
                    ++second_index;
                } while (second_index < prepared_count(second, 0x1b0));
            }
            ++first_index;
        } while (first_index < prepared_count(first, 0x1af));
    }
    return result;
}

int CollisionContext::test_group_b_against_group_b(
    CollisionObject *first,
    CollisionObject *second)
{
    int result = 0;
    signed char first_index = 0;
    if (prepared_count(first, 0x1b0) > 0) {
        do {
            CollisionAabb *first_box =
                prepared_box(first, 0x1b4, first_index);
            ShapeWords *first_descriptor =
                prepared_descriptor(first, 0x318, first_index);
            signed char second_index = 0;

            if (first_descriptor != 0) {
                if (prepared_count(second, 0x1b0) > 0) {
                    do {
                        CollisionAabb *second_box =
                            prepared_box(second, 0x1b4, second_index);
                        ShapeWords *second_descriptor =
                            prepared_descriptor(second, 0x318, second_index);
                        result |= second_descriptor == 0
                            ? test_aabb_against_descriptor_shape(
                                  first_box, first_descriptor, second_box)
                            : test_descriptor_shapes_overlap(
                                  first_box,
                                  first_descriptor,
                                  second_box,
                                  second_descriptor);
                        ++second_index;
                    } while (second_index < prepared_count(second, 0x1b0));
                }
            } else if (prepared_count(second, 0x1b0) > 0) {
                do {
                    CollisionAabb *second_box =
                        prepared_box(second, 0x1b4, second_index);
                    ShapeWords *second_descriptor =
                        prepared_descriptor(second, 0x318, second_index);
                    int hit;
                    if (second_descriptor == 0) {
                        int overlap = second_box->top - first_box->bottom;
                        overlap &= first_box->top - second_box->bottom;
                        overlap &= first_box->left - second_box->right;
                        overlap &= second_box->left - first_box->right;
                        if (overlap < 0) {
                            accumulate_collision_extents(
                                &first_box->left, &second_box->left);
                            hit = 1;
                        } else {
                            hit = 0;
                        }
                    } else {
                        hit = test_aabb_against_descriptor_shape(
                            second_box, second_descriptor, first_box);
                    }
                    result |= hit;
                    ++second_index;
                } while (second_index < prepared_count(second, 0x1b0));
            }
            ++first_index;
        } while (first_index < prepared_count(first, 0x1b0));
    }
    return result;
}

} // namespace th105
