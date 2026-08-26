#include "InfoManagerResources.hpp"
namespace th105 {
struct InfoManagerBaseNormalDependency {
    virtual ~InfoManagerBaseNormalDependency();
    unsigned char storage_004[0x494];
    InfoManagerBaseNormalDependency();
};
struct BattleInfoRecordF8NormalDependency {
    unsigned char storage_000[0xf8];
    BattleInfoRecordF8NormalDependency();
    ~BattleInfoRecordF8NormalDependency();
};
struct CInfoManagerNormalLifecycle : InfoManagerBaseNormalDependency {
    BattleInfoRecordF8NormalDependency records_498[2];
    CInfoManagerNormalLifecycle();
    virtual ~CInfoManagerNormalLifecycle();
    void initialize_normal_runtime_46eb90();
};
CInfoManagerNormalLifecycle::CInfoManagerNormalLifecycle()
{
    initialize_normal_runtime_46eb90();
}
CInfoManagerNormalLifecycle::~CInfoManagerNormalLifecycle()
{
    reinterpret_cast<InfoDesignResourceSubobject *>(reinterpret_cast<unsigned char *>(this) + 0x98)->release_design();
    reinterpret_cast<InfoDesignResourceSubobject *>(reinterpret_cast<unsigned char *>(this) + 0xcc)->release_design();
    reinterpret_cast<InfoComboResourceSubobject *>(reinterpret_cast<unsigned char *>(this) + 0x100)->release_combo_resources_46a610();
    reinterpret_cast<InfoEffectManagerSubobject *>(reinterpret_cast<unsigned char *>(this) + 0x04)->release_resource();
}
}
