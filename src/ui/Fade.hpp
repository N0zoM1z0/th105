#pragma once

#include <stddef.h>

namespace th105 {

struct IFade {
    virtual bool initialize();
    virtual void shutdown();
    virtual bool update_fade();
    virtual bool advance_to_midpoint();
    virtual bool render();
};

class CFade : public IFade {
public:
    virtual bool initialize();
    virtual void shutdown() {}
    virtual bool update_fade();
    virtual bool advance_to_midpoint();
    virtual bool render();

    unsigned color_04;
    int timer_08;
};

typedef char FadeInterfaceExtent[sizeof(IFade) == 4 ? 1 : -1];
typedef char FadeExtent[sizeof(CFade) == 12 ? 1 : -1];
typedef char FadeColorOffset[offsetof(CFade, color_04) == 4 ? 1 : -1];
typedef char FadeTimerOffset[offsetof(CFade, timer_08) == 8 ? 1 : -1];

} // namespace th105
