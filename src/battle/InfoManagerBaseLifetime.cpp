#include "battle/EffectSprite.hpp"
#include "ui/DesignBaseLifetime.hpp"
namespace th105 {
struct InfoEffectManagerLifecycle94 {
    unsigned char storage_000[0x94];
    InfoEffectManagerLifecycle94();
    ~InfoEffectManagerLifecycle94();
};

struct DesignResource34Lifecycle {
    unsigned char storage_000[0x34];
    DesignResource34Lifecycle();
    ~DesignResource34Lifecycle();
};

struct ComboResource34Lifecycle : DesignResource34Lifecycle {
};

struct InfoRecord34Lifecycle {
    unsigned char storage_000[0x34];
    InfoRecord34Lifecycle();
    ~InfoRecord34Lifecycle();
};

struct InfoRecord154Lifecycle {
    void *resource_000;
    CSprite primary_004;
    CSprite secondary_098;
    int timer_12c;
    unsigned char alpha_primary_130;
    unsigned char alpha_secondary_131;
    unsigned char mirrored_132;
    unsigned char reserved_133;
    float x_134;
    float y_138;
    float velocity_x_13c;
    float velocity_y_140;
    float scale_144;
    unsigned char reserved_148[4];
    unsigned char active_14c;
    unsigned char reserved_14d[3];
    int lifetime_150;
};
// Natural implicit record construction/destruction are passed by the
// owner to the actual VC8 array lifetime helpers.
typedef char RecordSize[sizeof(InfoRecord154Lifecycle)==0x154?1:-1];
typedef char RecordPrimary[offsetof(InfoRecord154Lifecycle,primary_004)==4?1:-1];
typedef char RecordSecondary[offsetof(InfoRecord154Lifecycle,secondary_098)==0x98?1:-1];

struct CInfoManagerBaseLifecycle {
    virtual void slot_00();
    InfoEffectManagerLifecycle94 effect_manager_004;
    DesignResource34Lifecycle upper_098;
    DesignResource34Lifecycle lower_0cc;
    ComboResource34Lifecycle combo_100;
    unsigned char reserved_134[0x38];
    InfoRecord34Lifecycle records_16c[2];
    InfoRecord154Lifecycle records_1d4[2];
    unsigned char tail_47c[0x1c];

    CInfoManagerBaseLifecycle();
    virtual ~CInfoManagerBaseLifecycle();
};

extern CInfoManagerBaseLifecycle *g_info_manager_base_lifecycle;

CInfoManagerBaseLifecycle::CInfoManagerBaseLifecycle()
{
    g_info_manager_base_lifecycle = this;
}

CInfoManagerBaseLifecycle::~CInfoManagerBaseLifecycle()
{
}

} // namespace th105
