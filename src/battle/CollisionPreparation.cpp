#include <math.h>
#include <vector>
#include <stddef.h>

namespace th105 {

float __cdecl lookup_orientation_sine(int angle);
float __cdecl lookup_orientation_cosine(int angle);

namespace {

struct LocalAabb {
    int left;
    int top;
    int right;
    int bottom;
};

struct ShapeWords {
    int x0;
    int y0;
    int x1;
    int y1;
};

struct OrientedRecord {
    LocalAabb box;
    short angle_10;
    short pivot_x_12;
    short pivot_y_14;
};

struct FrameGeometry {
    unsigned char unknown_00[0x4c];
    unsigned flags_4c;
    unsigned char unknown_50[4];
    LocalAabb *primary_54;
    std::vector<LocalAabb> group_b_58;
    std::vector<LocalAabb> group_a_68;
    std::vector<ShapeWords *> group_a_descriptors_78;
};

struct CollisionGeometryObject {
    unsigned char unknown_000[0xec];
    float x_ec;
    float y_f0;
    unsigned char unknown_f4[0x10];
    signed char facing_104;
    unsigned char unknown_105[3];
    float pivot_x_108;
    float pivot_y_10c;
    unsigned char unknown_110[0x1c];
    float angle_12c;
    unsigned char unknown_130[0x0c];
    unsigned short copied_13c;
    unsigned char unknown_13e[0x1a];
    FrameGeometry *frame_158;
    void *copied_15c;
    unsigned char unknown_160[0x14];
    unsigned short copied_174;
    unsigned char unknown_176[0x0a];
    unsigned copied_180;
    unsigned char copied_184;
    unsigned char unknown_185[0x0f];
    OrientedRecord *extension_194;
    short prepared_198;
    unsigned prepared_19c;
    unsigned char prepared_1a0;
    unsigned short prepared_1a2;
    FrameGeometry *cached_frame_1a4;
    void *prepared_1a8;
    short prepared_1ac;
    signed char prepared_1ae;
    signed char prepared_group_a_count_1af;
    signed char prepared_group_b_count_1b0;
    LocalAabb prepared_group_b_1b4[5];
    LocalAabb prepared_group_a_204[5];
    ShapeWords prepared_group_a_shapes_254[5];
    ShapeWords prepared_group_b_shapes_2a4[5];
    LocalAabb prepared_primary_2f4;
    ShapeWords *prepared_group_a_shape_ptrs_304[5];
    ShapeWords *prepared_group_b_shape_ptrs_318[5];
    LocalAabb *prepared_primary_ptr_32c;

    void transform_box_from_local_frame(int *record, int *out_box);
    void transform_box_from_local_frame_flipped_y(int *record, int *out_box);
    void build_oriented_box_and_descriptor(
        int *record, short angle, short pivot_x, short pivot_y,
        int *out_box, int *out_descriptor);
};

typedef char FrameGeometry_size[sizeof(FrameGeometry) == 0x88 ? 1 : -1];
typedef char FrameGeometry_group_b_offset[
    offsetof(FrameGeometry, group_b_58) == 0x58 ? 1 : -1];
typedef char FrameGeometry_group_a_offset[
    offsetof(FrameGeometry, group_a_68) == 0x68 ? 1 : -1];
typedef char FrameGeometry_descriptors_offset[
    offsetof(FrameGeometry, group_a_descriptors_78) == 0x78 ? 1 : -1];
typedef char CollisionGeometryObject_size[
    sizeof(CollisionGeometryObject) == 0x330 ? 1 : -1];
typedef char CollisionGeometryObject_frame_offset[
    offsetof(CollisionGeometryObject, frame_158) == 0x158 ? 1 : -1];
typedef char CollisionGeometryObject_cached_frame_offset[
    offsetof(CollisionGeometryObject, cached_frame_1a4) == 0x1a4 ? 1 : -1];
typedef char CollisionGeometryObject_group_a_shapes_offset[
    offsetof(CollisionGeometryObject, prepared_group_a_shapes_254) == 0x254 ? 1 : -1];
typedef char CollisionGeometryObject_shape_pointers_offset[
    offsetof(CollisionGeometryObject, prepared_group_a_shape_ptrs_304) == 0x304 ? 1 : -1];

} // namespace

namespace {

void CollisionGeometryObject::transform_box_from_local_frame(
    int *record,
    int *out_box)
{
    if (facing_104 == 1) {
        out_box[0] =
            static_cast<int>(static_cast<float>(ceil(x_ec))) + record[0];
        out_box[2] =
            static_cast<int>(static_cast<float>(ceil(x_ec))) + record[2];
    } else {
        out_box[0] =
            static_cast<int>(static_cast<float>(ceil(x_ec))) - record[2];
        out_box[2] =
            static_cast<int>(static_cast<float>(ceil(x_ec))) - record[0];
    }
    out_box[1] =
        record[1] - static_cast<int>(static_cast<float>(ceil(y_f0)));
    out_box[3] =
        record[3] - static_cast<int>(static_cast<float>(ceil(y_f0)));
}

void CollisionGeometryObject::transform_box_from_local_frame_flipped_y(
    int *record,
    int *out_box)
{
    if (facing_104 == 1) {
        out_box[0] =
            static_cast<int>(static_cast<float>(ceil(x_ec))) + record[0];
        out_box[2] =
            static_cast<int>(static_cast<float>(ceil(x_ec))) + record[2];
        out_box[1] =
            record[1] - static_cast<int>(static_cast<float>(ceil(y_f0)));
        out_box[3] =
            record[3] - static_cast<int>(static_cast<float>(ceil(y_f0)));
        return;
    }

    out_box[0] =
        static_cast<int>(static_cast<float>(ceil(x_ec))) - record[2];
    out_box[2] =
        static_cast<int>(static_cast<float>(ceil(x_ec))) - record[0];
    out_box[1] =
        record[3] - static_cast<int>(static_cast<float>(ceil(y_f0)));
    out_box[3] =
        record[1] - static_cast<int>(static_cast<float>(ceil(y_f0)));
}

void CollisionGeometryObject::build_oriented_box_and_descriptor(
    int *record,
    short angle,
    short pivot_x,
    short pivot_y,
    int *out_box,
    int *out_descriptor)
{
    float cosine = lookup_orientation_cosine(angle);
    float sine = lookup_orientation_sine(angle);

    if (sine >= 0.0f) {
        if (cosine >= 0.0f) {
            out_box[0] =
                static_cast<int>((record[0] - pivot_x) * cosine) -
                static_cast<int>((record[3] - pivot_y) * sine) + pivot_x;
            out_box[1] =
                static_cast<int>((record[0] - pivot_x) * sine) +
                static_cast<int>((record[3] - pivot_y) * cosine) + pivot_y;
            out_box[2] =
                static_cast<int>((record[2] - pivot_x) * cosine) -
                static_cast<int>((record[1] - pivot_y) * sine) + pivot_x;
            out_box[3] =
                static_cast<int>((record[2] - pivot_x) * sine) +
                static_cast<int>((record[1] - pivot_y) * cosine) + pivot_y;
            out_descriptor[0] =
                static_cast<int>((record[3] - record[1]) * sine);
            out_descriptor[1] =
                -static_cast<int>((record[3] - record[1]) * cosine);
            out_descriptor[2] =
                static_cast<int>((record[2] - record[0]) * cosine);
            out_descriptor[3] =
                static_cast<int>((record[2] - record[0]) * sine);
        } else {
            out_box[0] =
                static_cast<int>((record[2] - pivot_x) * cosine) -
                static_cast<int>((record[3] - pivot_y) * sine) + pivot_x;
            out_box[1] =
                static_cast<int>((record[2] - pivot_x) * sine) +
                static_cast<int>((record[3] - pivot_y) * cosine) + pivot_y;
            out_box[2] =
                static_cast<int>((record[0] - pivot_x) * cosine) -
                static_cast<int>((record[1] - pivot_y) * sine) + pivot_x;
            out_box[3] =
                static_cast<int>((record[0] - pivot_x) * sine) +
                static_cast<int>((record[1] - pivot_y) * cosine) + pivot_y;
            out_descriptor[0] =
                -static_cast<int>((record[2] - record[0]) * cosine);
            out_descriptor[1] =
                -static_cast<int>((record[2] - record[0]) * sine);
            out_descriptor[2] =
                static_cast<int>((record[3] - record[1]) * sine);
            out_descriptor[3] =
                -static_cast<int>((record[3] - record[1]) * cosine);
        }
    } else {
        if (cosine >= 0.0f) {
            out_box[0] =
                static_cast<int>((record[0] - pivot_x) * cosine) -
                static_cast<int>((record[1] - pivot_y) * sine) + pivot_x;
            out_box[1] =
                static_cast<int>((record[0] - pivot_x) * sine) +
                static_cast<int>((record[1] - pivot_y) * cosine) + pivot_y;
            out_box[2] =
                static_cast<int>((record[2] - pivot_x) * cosine) -
                static_cast<int>((record[3] - pivot_y) * sine) + pivot_x;
            out_box[3] =
                static_cast<int>((record[2] - pivot_x) * sine) +
                static_cast<int>((record[3] - pivot_y) * cosine) + pivot_y;
            out_descriptor[0] =
                static_cast<int>((record[2] - record[0]) * cosine);
            out_descriptor[1] =
                static_cast<int>((record[2] - record[0]) * sine);
            out_descriptor[2] =
                -static_cast<int>((record[3] - record[1]) * sine);
            out_descriptor[3] =
                static_cast<int>((record[3] - record[1]) * cosine);
        } else {
            out_box[0] =
                static_cast<int>((record[2] - pivot_x) * cosine) -
                static_cast<int>((record[1] - pivot_y) * sine) + pivot_x;
            out_box[1] =
                static_cast<int>((record[2] - pivot_x) * sine) +
                static_cast<int>((record[1] - pivot_y) * cosine) + pivot_y;
            out_box[2] =
                static_cast<int>((record[0] - pivot_x) * cosine) -
                static_cast<int>((record[3] - pivot_y) * sine) + pivot_x;
            out_box[3] =
                static_cast<int>((record[0] - pivot_x) * sine) +
                static_cast<int>((record[3] - pivot_y) * cosine) + pivot_y;
            out_descriptor[0] =
                -static_cast<int>((record[3] - record[1]) * sine);
            out_descriptor[1] =
                static_cast<int>((record[3] - record[1]) * cosine);
            out_descriptor[2] =
                -static_cast<int>((record[2] - record[0]) * cosine);
            out_descriptor[3] =
                -static_cast<int>((record[2] - record[0]) * sine);
        }
    }
}

} // namespace

void __fastcall prepare_collision_geometry_from_frame(void *raw_object)
{
    CollisionGeometryObject *self =
        static_cast<CollisionGeometryObject *>(raw_object);
    // Copy the state tuple before the action/frame snapshot, matching the
    // target access schedule without inventing extra storage.
    self->prepared_198 = static_cast<short>(self->copied_174);
    self->prepared_19c = self->copied_180;
    self->prepared_1a0 = self->copied_184;
    self->prepared_1a2 = 0;
    self->prepared_1ac = static_cast<short>(self->copied_13c);
    self->prepared_1ae = self->facing_104;
    self->prepared_1a8 = self->copied_15c;

    if (self->cached_frame_1a4 != self->frame_158) {
        self->cached_frame_1a4 = self->frame_158;
        self->prepared_group_a_count_1af =
            static_cast<signed char>(self->frame_158->group_a_68.size());
        self->prepared_group_b_count_1b0 =
            static_cast<signed char>(self->frame_158->group_b_58.size());

        for (int i = 0; i < self->prepared_group_a_count_1af; ++i) {
            if (self->frame_158->group_a_descriptors_78[i] == 0 &&
                (self->frame_158->flags_4c & 0x400000) == 0) {
                self->prepared_group_a_shape_ptrs_304[i] = 0;
            } else {
                self->prepared_group_a_shape_ptrs_304[i] =
                    &self->prepared_group_a_shapes_254[i];
            }
        }
        for (int i = 0; i < self->prepared_group_b_count_1b0; ++i) {
            if ((self->frame_158->flags_4c & 0x800000) != 0) {
                self->prepared_group_b_shape_ptrs_318[i] =
                    &self->prepared_group_b_shapes_2a4[i];
            } else {
                self->prepared_group_b_shape_ptrs_318[i] = 0;
            }
        }
    }

    LocalAabb local_box;
    ShapeWords local_shape;
    int index;
    for (index = 0;
         index < static_cast<int>(self->frame_158->group_a_68.size());
         ++index) {
        if (self->frame_158->group_a_descriptors_78[index] != 0) {
            self->transform_box_from_local_frame_flipped_y(
                reinterpret_cast<int *>(
                    &self->frame_158->group_a_68.at(index)),
                reinterpret_cast<int *>(&self->prepared_group_a_204[index]));
            if (self->facing_104 > 0) {
                *self->prepared_group_a_shape_ptrs_304[index] =
                    *self->frame_158->group_a_descriptors_78[index];
            } else {
                self->prepared_group_a_shape_ptrs_304[index]->x0 =
                    self->frame_158->group_a_descriptors_78[index]->x1;
                self->prepared_group_a_shape_ptrs_304[index]->y0 =
                    -self->frame_158->group_a_descriptors_78[index]->y1;
                self->prepared_group_a_shape_ptrs_304[index]->x1 =
                    self->frame_158->group_a_descriptors_78[index]->x0;
                self->prepared_group_a_shape_ptrs_304[index]->y1 =
                    -self->frame_158->group_a_descriptors_78[index]->y0;
            }
        } else if ((self->frame_158->flags_4c & 0x400000) != 0) {
            self->build_oriented_box_and_descriptor(
                reinterpret_cast<int *>(
                    &self->frame_158->group_a_68.at(index)),
                static_cast<short>(self->angle_12c),
                static_cast<short>(self->pivot_x_108),
                -static_cast<short>(self->pivot_y_10c),
                reinterpret_cast<int *>(&local_box),
                reinterpret_cast<int *>(&local_shape));
            self->transform_box_from_local_frame_flipped_y(
                reinterpret_cast<int *>(&local_box),
                reinterpret_cast<int *>(&self->prepared_group_a_204[index]));
            if (self->facing_104 > 0) {
                *self->prepared_group_a_shape_ptrs_304[index] = local_shape;
            } else {
                self->prepared_group_a_shape_ptrs_304[index]->x0 = local_shape.x1;
                self->prepared_group_a_shape_ptrs_304[index]->y0 = -local_shape.y1;
                self->prepared_group_a_shape_ptrs_304[index]->x1 = local_shape.x0;
                self->prepared_group_a_shape_ptrs_304[index]->y1 = -local_shape.y0;
            }
        } else {
            self->transform_box_from_local_frame(
                reinterpret_cast<int *>(
                    &self->frame_158->group_a_68.at(index)),
                reinterpret_cast<int *>(&self->prepared_group_a_204[index]));
        }
    }

    if ((self->frame_158->flags_4c & 0x800000) != 0) {
        for (index = 0;
             index < static_cast<int>(self->frame_158->group_b_58.size());
             ++index) {
            self->build_oriented_box_and_descriptor(
                reinterpret_cast<int *>(
                    &self->frame_158->group_b_58.at(index)),
                static_cast<short>(self->angle_12c),
                static_cast<short>(self->pivot_x_108),
                -static_cast<short>(self->pivot_y_10c),
                reinterpret_cast<int *>(&local_box),
                reinterpret_cast<int *>(&local_shape));
            self->transform_box_from_local_frame_flipped_y(
                reinterpret_cast<int *>(&local_box),
                reinterpret_cast<int *>(&self->prepared_group_b_1b4[index]));
            if (self->facing_104 > 0) {
                *self->prepared_group_b_shape_ptrs_318[index] = local_shape;
            } else {
                self->prepared_group_b_shape_ptrs_318[index]->x0 =
                    local_shape.x1;
                self->prepared_group_b_shape_ptrs_318[index]->y0 =
                    -local_shape.y1;
                self->prepared_group_b_shape_ptrs_318[index]->x1 =
                    local_shape.x0;
                self->prepared_group_b_shape_ptrs_318[index]->y1 =
                    -local_shape.y0;
            }
        }
    } else {
        for (index = 0;
             index < static_cast<int>(self->frame_158->group_b_58.size());
             ++index) {
            self->transform_box_from_local_frame(
                reinterpret_cast<int *>(
                    &self->frame_158->group_b_58.at(index)),
                reinterpret_cast<int *>(&self->prepared_group_b_1b4[index]));
        }
    }

    if (self->extension_194 != 0) {
        signed char a_count = static_cast<signed char>(
            self->frame_158->group_a_68.size());
        self->prepared_group_a_count_1af = static_cast<signed char>(a_count + 1);
        if (self->extension_194->angle_10 != 0) {
            self->prepared_group_a_shape_ptrs_304[a_count] =
                &self->prepared_group_a_shapes_254[a_count];
            self->build_oriented_box_and_descriptor(
                reinterpret_cast<int *>(self->extension_194),
                self->extension_194->angle_10,
                self->extension_194->pivot_x_12,
                self->extension_194->pivot_y_14,
                reinterpret_cast<int *>(&local_box),
                reinterpret_cast<int *>(&local_shape));
            self->transform_box_from_local_frame_flipped_y(
                reinterpret_cast<int *>(&local_box),
                reinterpret_cast<int *>(&self->prepared_group_a_204[a_count]));
            if (self->facing_104 > 0) {
                *self->prepared_group_a_shape_ptrs_304[a_count] = local_shape;
            } else {
                self->prepared_group_a_shape_ptrs_304[a_count]->x0 = local_shape.x1;
                self->prepared_group_a_shape_ptrs_304[a_count]->y0 = -local_shape.y1;
                self->prepared_group_a_shape_ptrs_304[a_count]->x1 = local_shape.x0;
                self->prepared_group_a_shape_ptrs_304[a_count]->y1 = -local_shape.y0;
            }
        } else {
            self->prepared_group_a_shape_ptrs_304[a_count] = 0;
            self->transform_box_from_local_frame(
                reinterpret_cast<int *>(self->extension_194),
                reinterpret_cast<int *>(&self->prepared_group_a_204[a_count]));
        }
        if ((self->frame_158->flags_4c & 0x1000000) != 0) {
            int b_count = static_cast<int>(self->frame_158->group_b_58.size());
            self->prepared_group_b_count_1b0 = static_cast<signed char>(a_count + 1);
            self->prepared_group_b_1b4[b_count] = self->prepared_group_a_204[a_count];
            self->prepared_group_b_shape_ptrs_318[b_count] =
                self->prepared_group_a_shape_ptrs_304[a_count];
        }
    }

    if (self->frame_158->primary_54 != 0) {
        self->prepared_primary_ptr_32c = &self->prepared_primary_2f4;
        self->transform_box_from_local_frame(
            reinterpret_cast<int *>(self->frame_158->primary_54),
            reinterpret_cast<int *>(self->prepared_primary_ptr_32c));
    } else {
        self->prepared_primary_ptr_32c = 0;
    }
}

} // namespace th105
