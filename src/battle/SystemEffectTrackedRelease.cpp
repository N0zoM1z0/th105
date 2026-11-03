#include "battle/SystemEffectManager.hpp"
#include <list>
namespace th105 {
struct SystemEffectReleaseView {
    virtual ~SystemEffectReleaseView();
    CHandleManagerEx<SystemEffectObject> pool_004;
    std::list<SystemEffectObjectBase *> objects_054;
    void release_all();
};
typedef char CheckSize[sizeof(SystemEffectReleaseView)==0x60?1:-1];
void SystemEffectReleaseView::release_all()
{
    for(std::list<SystemEffectObjectBase *>::iterator it=objects_054.begin();
        it!=objects_054.end();++it)
        pool_004.release_handle((*it)->handle_token_004);
    objects_054.clear();
}
}
