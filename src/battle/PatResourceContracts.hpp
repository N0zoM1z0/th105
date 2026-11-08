#pragma once

#include <stddef.h>
#include <vector>

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

class FrameData {
public:
    FrameData();
    virtual ~FrameData();

    // Raw 16-bit frame fields; render/animation views interpret these bits.
    unsigned short pivot_x_bits_04, pivot_y_bits_06;
    unsigned short duration_bits_08, texture_index_bits_0a;
    unsigned short texture_x_bits_0c, texture_y_bits_0e;
    unsigned short texture_width_bits_10, texture_height_bits_12;
    unsigned char tag_14;
    // +15..+17 are natural alignment padding, not assignment members.
    PatOptionalModePayload20 *optional_mode_payload_18;
};

typedef char FrameData_base_size[sizeof(FrameData) == 0x1c ? 1 : -1];
typedef char FrameData_first_word_offset[offsetof(FrameData, pivot_x_bits_04) == 4 ? 1 : -1];
typedef char FrameData_last_word_offset[offsetof(FrameData, texture_height_bits_12) == 0x12 ? 1 : -1];
typedef char FrameData_tag_offset[offsetof(FrameData, tag_14) == 0x14 ? 1 : -1];
typedef char FrameData_payload_offset[offsetof(FrameData, optional_mode_payload_18) == 0x18 ? 1 : -1];

class PatRecord88 : public FrameData {
public:
    PatRecord88();
    virtual ~PatRecord88();

    // Hit resolution reads these fields through the prepared frame snapshot.
    // The loader retains the observed raw 16-bit representation.
    short quantity_1c;
    short owner_multiplier_per_1000_1e;
    short quantity_20;
    short amount_22;
    short boosted_response_quantity_24;
    short threshold_increment_26;
    short result_accumulator_increment_28;
    unsigned short candidate_output_2a;
    unsigned short fighter_output_2c;
    unsigned short result_2e;
    unsigned short result_30;
    short owner_capped_counter_quantity_32;
    unsigned short amount_34;
    unsigned short action_code_36;
    unsigned short alternate_action_code_38;
    // +0x3A..+0x3B are natural alignment padding and are not copy members.
    float response_3c;
    float response_40;
    short indexed_event_44;
    unsigned short effect_46;
    signed char action_offset_48;
    unsigned char owner_flag_bits_49;
    // +0x4A..+0x4B are natural alignment padding and are not copy members.
    unsigned flags_4c;
    unsigned flags_50;
    // Collision preparation interprets these raw records as boxes/descriptors.
    PatRaw16 *primary_collision_box_54;
    std::vector<PatRaw16> group_b_collision_boxes_58;
    std::vector<PatRaw16> group_a_collision_boxes_68;
    std::vector<PatRaw16 *> group_a_descriptors_78;
};

struct PatGroup {
    std::vector<PatRecord88> records_00;
    short field_10;
    short field_12;
    // Nonzero suppresses the frame-wrap signal used for automatic block advance.
    // Frames still wrap, and explicit block selection remains possible.
    unsigned char suppress_wrap_signal_14;
    // 0x15..0x17 are natural alignment padding; current copy construction does not copy them.
    PatGroup *previous_18;
    PatGroup *next_1c; // The last block can link back to the chain root.

    PatGroup();
    ~PatGroup();
};

struct PatTransientPairNode {
    PatTransientPairNode *next_00;
    PatTransientPairNode *previous_04;
    void *payload_08;
};

void PatGroupDeque_grow_for_append(PatGroupDequeView *self);
int PatRecord88_finalize_owned_fields(PatRecord88 *self, int selector);
int PatRecord88_resize_raw16_values(void *self, int count, void *source);
int __cdecl PatGroup_copy_construct(void *destination, void const *source);
int PatGroup_resize_records(PatGroup *self, int count, void *source);

typedef char PaletteHandleVectorView_size_must_be_0x10[
    sizeof(PaletteHandleVectorView) == 0x10 ? 1 : -1];
typedef char PatGroupDequeView_size_must_be_0x14[
    sizeof(PatGroupDequeView) == 0x14 ? 1 : -1];
typedef char PatGroup_size_must_be_0x20[
    sizeof(PatGroup) == 0x20 ? 1 : -1];
typedef char PatGroup_links_must_begin_at_0x18[
    offsetof(PatGroup, previous_18) == 0x18 ? 1 : -1];
typedef char PatOptionalModePayload20_size_must_be_0x20[
    sizeof(PatOptionalModePayload20) == 0x20 ? 1 : -1];
typedef char FrameData_size_must_be_0x1c[
    sizeof(FrameData) == 0x1C ? 1 : -1];
typedef char PatRecord88_size_must_be_0x88[
    sizeof(PatRecord88) == 0x88 ? 1 : -1];
typedef char PatRecord88_tag_must_be_at_0x14[
    offsetof(PatRecord88, tag_14) == 0x14 ? 1 : -1];
typedef char PatRecord88_nested_vectors_must_begin_at_0x58[
    offsetof(PatRecord88, group_b_collision_boxes_58) == 0x58 ? 1 : -1];
typedef char PatTransientPairNode_size_must_be_0x0c[
    sizeof(PatTransientPairNode) == 0x0c ? 1 : -1];

} // namespace th105
