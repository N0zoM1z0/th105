#pragma once

#include <stddef.h>

namespace th105 {

// Neutral source-facing layouts recovered from 0x00460B50.  Names describe
// ownership and storage only; the original .pat field terminology is unknown.
struct PaletteHandleVectorView {
    unsigned char allocator_00[4];
    unsigned *begin_04;
    unsigned *end_08;
    unsigned *capacity_end_0c;
};

struct PatGroupDequeView {
    unsigned char storage_00[0x14];
};

struct PatGroup {
    unsigned char unknown_00[4];
    unsigned char record_vector_04[0x0c];
    short field_10;
    short field_12;
    unsigned char field_14;
    unsigned char padding_15[3];
    PatGroup *link_18;
    PatGroup *link_1c;
};

struct PatOptionalModePayload20 {
    unsigned mode_00;
    unsigned char bytes_04[4];
    float shared_scale_08;
    float shared_scale_0c;
    float shared_scale_10;
    float scale_14;
    float scale_18;
    float scale_1c;
};

struct PatRaw16 {
    unsigned char bytes_00[0x10];
};

struct PatRecord88 {
    void *vtable_00;
    short fields_04_to_12[8];
    unsigned char tag_14;
    unsigned char padding_15[3];
    PatOptionalModePayload20 *optional_mode_payload_18;
    unsigned char fields_1c_to_3b[0x20];
    float scaled_3c;
    float scaled_40;
    unsigned char fields_44_to_4b[8];
    unsigned flags_4c;
    unsigned field_50;
    PatRaw16 *optional_raw16_54;
    unsigned char raw16_vector_58[0x10];
    unsigned char raw16_vector_68[0x10];
    unsigned char raw16_pointer_vector_78[0x10];
};

struct PatTransientPairNode {
    PatTransientPairNode *next_00;
    PatTransientPairNode *previous_04;
    void *payload_08;
};

PatRecord88 *__thiscall PatRecord88_construct(PatRecord88 *self);
void __thiscall PatRecord88_destroy(PatRecord88 *self);
PatGroup *__thiscall PatGroup_construct(PatGroup *self);
void __thiscall PatGroup_destroy(PatGroup *self);
void __thiscall PatGroupDeque_grow_for_append(PatGroupDequeView *self);
int __thiscall PatRecord88_finalize_owned_fields(PatRecord88 *self, int selector);
int __thiscall PatRecord88_resize_raw16_values(void *self, int count, void *source);
int __cdecl PatGroup_copy_construct(void *destination, void const *source);
int __thiscall PatGroup_resize_records(PatGroup *self, int count, void *source);

typedef char PaletteHandleVectorView_size_must_be_0x10[
    sizeof(PaletteHandleVectorView) == 0x10 ? 1 : -1];
typedef char PatGroupDequeView_size_must_be_0x14[
    sizeof(PatGroupDequeView) == 0x14 ? 1 : -1];
typedef char PatGroup_size_must_be_0x20[
    sizeof(PatGroup) == 0x20 ? 1 : -1];
typedef char PatGroup_links_must_begin_at_0x18[
    offsetof(PatGroup, link_18) == 0x18 ? 1 : -1];
typedef char PatOptionalModePayload20_size_must_be_0x20[
    sizeof(PatOptionalModePayload20) == 0x20 ? 1 : -1];
typedef char PatRecord88_size_must_be_0x88[
    sizeof(PatRecord88) == 0x88 ? 1 : -1];
typedef char PatRecord88_tag_must_be_at_0x14[
    offsetof(PatRecord88, tag_14) == 0x14 ? 1 : -1];
typedef char PatRecord88_nested_vectors_must_begin_at_0x58[
    offsetof(PatRecord88, raw16_vector_58) == 0x58 ? 1 : -1];
typedef char PatTransientPairNode_size_must_be_0x0c[
    sizeof(PatTransientPairNode) == 0x0c ? 1 : -1];

} // namespace th105
