#include <math.h>
#include <vector>

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

void __stdcall build_oriented_box_and_descriptor(
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
    self->prepared_198 = static_cast<short>(self->copied_174);
    self->prepared_1ac = static_cast<short>(self->copied_13c);
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

    LocalAabb local_box;
    ShapeWords local_shape;
    int index = 0;
    LocalAabb *out = &self->prepared_group_a_204[0];
    ShapeWords **out_shape = &self->prepared_group_a_shape_ptrs_304[0];
    for (;;) {
        if (index >= static_cast<int>(self->frame_158->group_a_6c.size())) {
            break;
        }
        ShapeWords *source_shape =
            self->frame_158->group_a_descriptors_7c[index];
        if (source_shape != 0) {
            self->transform_box_from_local_frame_flipped_y(
                reinterpret_cast<int *>(
                    &self->frame_158->group_a_6c.at(index)),
                reinterpret_cast<int *>(out));
            if (self->facing_104 > 0) {
                source_shape =
                    self->frame_158->group_a_descriptors_7c[index];
                **out_shape = *source_shape;
            } else {
                (*out_shape)->x0 =
                    self->frame_158->group_a_descriptors_7c[index]->x1;
                (*out_shape)->y0 =
                    -self->frame_158->group_a_descriptors_7c[index]->y1;
                (*out_shape)->x1 =
                    self->frame_158->group_a_descriptors_7c[index]->x0;
                (*out_shape)->y1 =
                    -self->frame_158->group_a_descriptors_7c[index]->y0;
            }
        } else if ((self->frame_158->flags_4c & 0x400000) != 0) {
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
            if (self->facing_104 > 0) {
                (*out_shape)->x0 = local_shape.x0;
                (*out_shape)->y0 = local_shape.y0;
                (*out_shape)->x1 = local_shape.x1;
                (*out_shape)->y1 = local_shape.y1;
            } else {
                (*out_shape)->x0 = local_shape.x1;
                (*out_shape)->y0 = -local_shape.y1;
                (*out_shape)->x1 = local_shape.x0;
                (*out_shape)->y1 = -local_shape.y0;
            }
        } else {
            self->transform_box_from_local_frame(
                reinterpret_cast<int *>(
                    &self->frame_158->group_a_6c.at(index)),
                reinterpret_cast<int *>(out));
        }
        ++index;
        ++out;
        ++out_shape;
    }

    if ((self->frame_158->flags_4c & 0x800000) != 0) {
        for (index = 0;
             index < static_cast<int>(self->frame_158->group_b_5c.size());
             ++index) {
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
            if (self->facing_104 > 0) {
                self->prepared_group_b_shape_ptrs_318[index]->x0 =
                    local_shape.x0;
                self->prepared_group_b_shape_ptrs_318[index]->y0 =
                    local_shape.y0;
                self->prepared_group_b_shape_ptrs_318[index]->x1 =
                    local_shape.x1;
                self->prepared_group_b_shape_ptrs_318[index]->y1 =
                    local_shape.y1;
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
        if (self->extension_194->angle_10 != 0) {
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
            if (self->facing_104 > 0) {
                (*extension_shape)->x0 = local_shape.x0;
                (*extension_shape)->y0 = local_shape.y0;
                (*extension_shape)->x1 = local_shape.x1;
                (*extension_shape)->y1 = local_shape.y1;
            } else {
                (*extension_shape)->x0 = local_shape.x1;
                (*extension_shape)->y0 = -local_shape.y1;
                (*extension_shape)->x1 = local_shape.x0;
                (*extension_shape)->y1 = -local_shape.y0;
            }
        } else {
            *extension_shape = 0;
            self->transform_box_from_local_frame(
                reinterpret_cast<int *>(self->extension_194),
                reinterpret_cast<int *>(extension_box));
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
