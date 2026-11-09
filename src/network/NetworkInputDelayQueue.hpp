#pragma once

#include "battle/SpellData.hpp"
#include <stddef.h>

namespace th105 {

// The 0x7c input endpoint view used by the native queue-advance method.
// Its +0x60 word is the embedded CInputManagerEx injected input mask.
struct NetworkInputDelayQueueView {
    void advance_delay_queue();

    unsigned char reserved_000[0x60];
    unsigned short injected_mask_060;
    unsigned char reserved_062[0x06];
    ShortDeque8 queue_068;
};

typedef char NetworkInputDelayMaskOffset[
    offsetof(NetworkInputDelayQueueView, injected_mask_060) == 0x60 ? 1 : -1];
typedef char NetworkInputDelayQueueOffset[
    offsetof(NetworkInputDelayQueueView, queue_068) == 0x68 ? 1 : -1];
typedef char NetworkInputDelayQueueExtent[
    sizeof(NetworkInputDelayQueueView) == 0x7c ? 1 : -1];

} // namespace th105
