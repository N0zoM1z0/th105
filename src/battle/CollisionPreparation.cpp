#include <vector>

namespace th105 {

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
    std::vector<LocalAabb> group_b_5c;
    std::vector<LocalAabb> group_a_6c;
    std::vector<ShapeWords *> group_a_descriptors_7c;
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
};

void __stdcall build_oriented_box_and_descriptor(
    int *record,
    short angle,
    short pivot_x,
    short pivot_y,
    int *out_box,
    int *out_descriptor);

__forceinline void copy_descriptor_for_facing(
    signed char facing,
    ShapeWords *out,
    const ShapeWords *in)
{
    if (facing > 0) {
        *out = *in;
    } else {
        out->x0 = in->x1;
        out->y0 = -in->y1;
        out->x1 = in->x0;
        out->y1 = -in->y0;
    }
}

} // namespace

void __fastcall prepare_collision_geometry_from_frame(void *raw_object)
{
    CollisionGeometryObject *self =
        static_cast<CollisionGeometryObject *>(raw_object);
    self->prepared_198 = self->copied_174;
    self->prepared_1ac = self->copied_13c;
    self->prepared_19c = self->copied_180;
    self->prepared_1a0 = self->copied_184;
    self->prepared_1a2 = 0;
    self->prepared_1ae = self->facing_104;
    self->prepared_1a8 = self->copied_15c;

    if (self->cached_frame_1a4 != self->frame_158) {
        self->cached_frame_1a4 = self->frame_158;
        self->prepared_group_a_count_1af =
            static_cast<signed char>(self->frame_158->group_a_6c.size());
        self->prepared_group_b_count_1b0 =
            static_cast<signed char>(self->frame_158->group_b_5c.size());

        for (int i = 0; i < self->prepared_group_a_count_1af; ++i) {
            if (self->frame_158->group_a_descriptors_7c[i] == 0 &&
                (self->frame_158->flags_4c & 0x400000) == 0) {
                self->prepared_group_a_shape_ptrs_304[i] = 0;
            } else {
                self->prepared_group_a_shape_ptrs_304[i] =
                    &self->prepared_group_a_shapes_254[i];
            }
        }
        for (int i = 0; i < self->prepared_group_b_count_1b0; ++i) {
            self->prepared_group_b_shape_ptrs_318[i] =
                (self->frame_158->flags_4c & 0x800000) != 0
                    ? &self->prepared_group_b_shapes_2a4[i] : 0;
        }
    }

    int index = 0;
    for (;;) {
        if (index >= static_cast<int>(self->frame_158->group_a_6c.size())) {
            break;
        }
        LocalAabb *out = &self->prepared_group_a_204[index];
        ShapeWords **out_shape = &self->prepared_group_a_shape_ptrs_304[index];
        ShapeWords *source_shape = self->frame_158->group_a_descriptors_7c[index];
        if (source_shape == 0) {
            if ((self->frame_158->flags_4c & 0x400000) == 0) {
                self->transform_box_from_local_frame(
                    reinterpret_cast<int *>(
                        &self->frame_158->group_a_6c.at(index)),
                    reinterpret_cast<int *>(out));
            } else {
                LocalAabb local_box;
                ShapeWords local_shape;
                build_oriented_box_and_descriptor(
                    reinterpret_cast<int *>(
                        &self->frame_158->group_a_6c.at(index)),
                    static_cast<short>(self->angle_12c),
                    static_cast<short>(self->pivot_x_108),
                    -static_cast<short>(self->pivot_y_10c),
                    reinterpret_cast<int *>(&local_box),
                    reinterpret_cast<int *>(&local_shape));
                self->transform_box_from_local_frame_flipped_y(
                    reinterpret_cast<int *>(&local_box),
                    reinterpret_cast<int *>(out));
                copy_descriptor_for_facing(
                    self->facing_104, *out_shape, &local_shape);
            }
        } else {
            self->transform_box_from_local_frame_flipped_y(
                reinterpret_cast<int *>(
                    &self->frame_158->group_a_6c.at(index)),
                reinterpret_cast<int *>(out));
            copy_descriptor_for_facing(
                self->facing_104, *out_shape, source_shape);
        }
        ++index;
    }

    if ((self->frame_158->flags_4c & 0x800000) != 0) {
        for (index = 0;
             index < static_cast<int>(self->frame_158->group_b_5c.size());
             ++index) {
            LocalAabb local_box;
            ShapeWords local_shape;
            build_oriented_box_and_descriptor(
                reinterpret_cast<int *>(
                    &self->frame_158->group_b_5c.at(index)),
                static_cast<short>(self->angle_12c),
                static_cast<short>(self->pivot_x_108),
                -static_cast<short>(self->pivot_y_10c),
                reinterpret_cast<int *>(&local_box),
                reinterpret_cast<int *>(&local_shape));
            self->transform_box_from_local_frame_flipped_y(
                reinterpret_cast<int *>(&local_box),
                reinterpret_cast<int *>(&self->prepared_group_b_1b4[index]));
            copy_descriptor_for_facing(
                self->facing_104,
                self->prepared_group_b_shape_ptrs_318[index],
                &local_shape);
        }
    } else {
        for (index = 0;
             index < static_cast<int>(self->frame_158->group_b_5c.size());
             ++index) {
            self->transform_box_from_local_frame(
                reinterpret_cast<int *>(
                    &self->frame_158->group_b_5c.at(index)),
                reinterpret_cast<int *>(&self->prepared_group_b_1b4[index]));
        }
    }

    if (self->extension_194 != 0) {
        int a_count = static_cast<signed char>(
            self->frame_158->group_a_6c.size());
        LocalAabb *extension_box = &self->prepared_group_a_204[a_count];
        ShapeWords **extension_shape =
            &self->prepared_group_a_shape_ptrs_304[a_count];
        self->prepared_group_a_count_1af =
            static_cast<signed char>(a_count + 1);
        if (self->extension_194->angle_10 == 0) {
            *extension_shape = 0;
            self->transform_box_from_local_frame(
                reinterpret_cast<int *>(self->extension_194),
                reinterpret_cast<int *>(extension_box));
        } else {
            LocalAabb local_box;
            ShapeWords local_shape;
            *extension_shape = &self->prepared_group_a_shapes_254[a_count];
            build_oriented_box_and_descriptor(
                reinterpret_cast<int *>(self->extension_194),
                self->extension_194->angle_10,
                self->extension_194->pivot_x_12,
                self->extension_194->pivot_y_14,
                reinterpret_cast<int *>(&local_box),
                reinterpret_cast<int *>(&local_shape));
            self->transform_box_from_local_frame_flipped_y(
                reinterpret_cast<int *>(&local_box),
                reinterpret_cast<int *>(extension_box));
            copy_descriptor_for_facing(
                self->facing_104, *extension_shape, &local_shape);
        }
        if ((self->frame_158->flags_4c & 0x1000000) != 0) {
            int b_count = static_cast<int>(
                self->frame_158->group_b_5c.size());
            self->prepared_group_b_count_1b0 =
                self->prepared_group_a_count_1af;
            self->prepared_group_b_1b4[b_count] = *extension_box;
            self->prepared_group_b_shape_ptrs_318[b_count] = *extension_shape;
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
