#include "InfoManagerResources.hpp"
#include "../ui/Title.hpp"
#include "../ui/CNumberRuntime.hpp"
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

namespace th105 {
// Bounded typed runtime view of the already established embedded-resource extents.

struct NormalEffect94 { InfoEffectManagerSubobject api; unsigned char rest[0x90]; };
struct NormalDesign34 { InfoDesignResourceSubobject api; unsigned char rest[0x30]; };
struct NormalInfoRuntimeView {
    void *vtable;
    NormalEffect94 effect;
    NormalDesign34 upper,lower;
    InfoComboResourceSubobject combo;
    unsigned char rest_104[0x384];
    float counter_488;
    UiDesignObject *numbers_48c[2];
    int state_494;
    BattleInfoRecordF8 records_498[2];
};
typedef char normal_records_offset[offsetof(NormalInfoRuntimeView,records_498)==0x498?1:-1];
void CInfoManagerNormalLifecycle::initialize_normal_runtime_46eb90()
{
    NormalInfoRuntimeView *view=reinterpret_cast<NormalInfoRuntimeView *>(this);
    view->effect.api.load_resource("data/infoEffect/effect.pat",0);
    view->combo.load_combo_resources_46a8c0();
    view->upper.api.load_design("data/battle/battleUpper.dat");
    view->lower.api.load_design("data/battle/battleUnder.dat");
    view->records_498[0].initialize_46fd20(0,&view->upper.api,&view->lower.api,&view->effect.api);
    view->records_498[1].initialize_46fd20(1,&view->upper.api,&view->lower.api,&view->effect.api);
    for(int i=0;i<2;++i){
        reinterpret_cast<TitleDesignResource *>(&view->upper.api)->bind_object_alt(&view->numbers_48c[i],100+i);
        reinterpret_cast<CNumber *>(reinterpret_cast<unsigned char *>(view->numbers_48c[i])+0x18)->bind_value(&view->counter_488);
    }
    view->state_494=0;
}
}
