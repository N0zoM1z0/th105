#pragma once

#include <stddef.h>
#include <vector>

namespace th105 {

struct FighterPhaseObjectView;

// Current 1.06a checked-vector owner.  VC8's debug/checked std::vector object
// begins at +0x38; its begin/end pointers therefore appear at +0x3c/+0x40 in
// target code.  Keep this layout shared by the phase caller and phase methods.
struct FighterPhaseContext {
    unsigned char reserved_000[0x38];
    std::vector<FighterPhaseObjectView *> fighters_038;

    void phase_463820();
    void phase_463970();
    void phase_463a00(int value);
    void phase_463a60();
    void phase_463ab0();
};

typedef char FighterPhaseContext_vector_offset_must_be_0x38[
    offsetof(FighterPhaseContext, fighters_038) == 0x38 ? 1 : -1];

extern FighterPhaseContext *g_fighter_phase_context;

} // namespace th105
