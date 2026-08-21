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
    FrameData(FrameData const &other);
    virtual ~FrameData();

    unsigned raw_04;
    unsigned raw_08;
    unsigned raw_0c;
    unsigned raw_10;
    union {
        unsigned raw_14;
        struct {
            unsigned char tag_14;
            unsigned char padding_15[3];
        };
    };
    PatOptionalModePayload20 *optional_mode_payload_18;
};

class PatRecord88 : public FrameData {
public:
    PatRecord88();
    virtual ~PatRecord88();

    short field_1c;
    short field_1e;
    short field_20;
    short field_22;
    short field_24;
    short field_26;
    short field_28;
    short field_2a;
    short field_2c;
    short field_2e;
    short field_30;
    short field_32;
    short field_34;
    short field_36;
    short field_38;
    // +0x3A..+0x3B are natural alignment padding and are not copy members.
    float scaled_3c;
    float scaled_40;
    short field_44;
    short field_46;
    unsigned char field_48;
    unsigned char field_49;
    // +0x4A..+0x4B are natural alignment padding and are not copy members.
    unsigned flags_4c;
    unsigned field_50;
    PatRaw16 *optional_raw16_54;
    std::vector<PatRaw16> raw16_vector_58;
    std::vector<PatRaw16> raw16_vector_68;
    std::vector<PatRaw16 *> raw16_pointer_vector_78;
};

struct PatGroup {
    std::vector<PatRecord88> records_00;
    short field_10;
    short field_12;
    unsigned char field_14;
    // 0x15..0x17 are natural alignment padding; current copy construction does not copy them.
    PatGroup *link_18;
    PatGroup *link_1c;

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
    offsetof(PatGroup, link_18) == 0x18 ? 1 : -1];
typedef char PatOptionalModePayload20_size_must_be_0x20[
    sizeof(PatOptionalModePayload20) == 0x20 ? 1 : -1];
typedef char FrameData_size_must_be_0x1c[
    sizeof(FrameData) == 0x1C ? 1 : -1];
typedef char PatRecord88_size_must_be_0x88[
    sizeof(PatRecord88) == 0x88 ? 1 : -1];
typedef char PatRecord88_tag_must_be_at_0x14[
    offsetof(PatRecord88, tag_14) == 0x14 ? 1 : -1];
typedef char PatRecord88_nested_vectors_must_begin_at_0x58[
    offsetof(PatRecord88, raw16_vector_58) == 0x58 ? 1 : -1];
typedef char PatTransientPairNode_size_must_be_0x0c[
    sizeof(PatTransientPairNode) == 0x0c ? 1 : -1];

} // namespace th105
