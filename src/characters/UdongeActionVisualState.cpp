#include <stddef.h>

namespace th105 {

// Udonge action-entry callers use this tail helper after publishing their
// action-specific motion state.  Keep the three observed fields typed rather
// than treating the tail as an opaque blob: VC8 then preserves the assignment
// expression's EAX/AX/AL value across all three stores.
struct UdongeActionVisualStateView {
    unsigned char unknown_000[0x113];
    unsigned char visual_state_113;
    unsigned char unknown_114[0x692];
    unsigned short opacity_7a6;
    float scale_7a8;

    int reset_action_visual_state();
};

typedef char UdongeActionVisualState_state_offset[
    offsetof(UdongeActionVisualStateView, visual_state_113) == 0x113 ? 1 : -1];
typedef char UdongeActionVisualState_opacity_offset[
    offsetof(UdongeActionVisualStateView, opacity_7a6) == 0x7a6 ? 1 : -1];
typedef char UdongeActionVisualState_scale_offset[
    offsetof(UdongeActionVisualStateView, scale_7a8) == 0x7a8 ? 1 : -1];

int UdongeActionVisualStateView::reset_action_visual_state()
{
    scale_7a8 = 1.0f;
    return visual_state_113 = static_cast<unsigned char>(opacity_7a6 = 255);
}

} // namespace th105
