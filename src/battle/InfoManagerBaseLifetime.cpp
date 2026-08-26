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
    unsigned char storage_000[0x154];
    InfoRecord154Lifecycle();
    ~InfoRecord154Lifecycle();
};

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
