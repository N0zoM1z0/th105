#include "battle/EffectSprite.hpp"

#include <stddef.h>

namespace th105 {

struct CharacterObjectBoundsDescriptor {
    int min_x_00;
    int min_y_04;
    int max_x_08;
    int max_y_0c;
    short metadata_10;
    short metadata_12;
    short metadata_14;
    short reserved_16;
};

class CharacterObjectBoundsView {
public:
    void publish_bounds_descriptor(
        int x1, int y1, int x2, int y2,
        short metadata_10, short metadata_12, short metadata_14);

    unsigned char reserved_000[0x194];
    CharacterObjectBoundsDescriptor *bounds_194;
};

struct CharacterObjectAuxiliaryRendererOwner {
    CEffectSprite sprite_000;
};

class CharacterObjectAuxiliaryRendererSlotView {
public:
    void release_auxiliary_renderer();

    unsigned char reserved_000[0x154];
    CharacterObjectAuxiliaryRendererOwner *auxiliary_renderer_154;
};

typedef char CharacterObjectBoundsDescriptor_size[
    sizeof(CharacterObjectBoundsDescriptor) == 0x18 ? 1 : -1];
typedef char CharacterObjectBoundsView_bounds_offset[
    offsetof(CharacterObjectBoundsView, bounds_194) == 0x194 ? 1 : -1];
typedef char CharacterObjectAuxiliaryRendererSlotView_renderer_offset[
    offsetof(CharacterObjectAuxiliaryRendererSlotView, auxiliary_renderer_154) == 0x154 ? 1 : -1];

void CharacterObjectBoundsView::publish_bounds_descriptor(
    int x1, int y1, int x2, int y2,
    short metadata_10, short metadata_12, short metadata_14)
{
    if (!bounds_194)
        bounds_194 = new CharacterObjectBoundsDescriptor;

    if (x1 > x2) {
        bounds_194->min_x_00 = x2;
        bounds_194->max_x_08 = x1;
    } else {
        bounds_194->min_x_00 = x1;
        bounds_194->max_x_08 = x2;
    }

    if (y1 > y2) {
        bounds_194->min_y_04 = y2;
        bounds_194->max_y_0c = y1;
    } else {
        bounds_194->min_y_04 = y1;
        bounds_194->max_y_0c = y2;
    }

    bounds_194->metadata_10 = metadata_10;
    bounds_194->metadata_12 = metadata_12;
    bounds_194->metadata_14 = metadata_14;
}

void CharacterObjectAuxiliaryRendererSlotView::release_auxiliary_renderer()
{
    if (auxiliary_renderer_154) {
        delete auxiliary_renderer_154;
        auxiliary_renderer_154 = 0;
    }
}

} // namespace th105
