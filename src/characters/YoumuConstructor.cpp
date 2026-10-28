#include <deque>
#include "YoumuObjectRecords.hpp"

namespace th105 {
class YoumuCharacterBaseView {
public:
    YoumuCharacterBaseView(int init_arg);
    virtual ~YoumuCharacterBaseView();
protected:
    unsigned char unknown_004[0x654];
    void *owned_manager_658;
};
class YoumuConstructorView;
class YoumuCtorObjectManager {
public:
    YoumuCtorObjectManager(YoumuConstructorView *owner);
private:
    unsigned char storage_00[0x68];
};
class YoumuConstructorView : public YoumuCharacterBaseView {
public:
    YoumuConstructorView(int init_arg);
    unsigned char unknown_65c[0x148];
    YoumuObjectRecord record_7a4;
    std::deque<YoumuObjectRecord> records_7d0;
};
typedef char YoumuCtorRecordOffset[offsetof(YoumuConstructorView, record_7a4)==0x7a4 ? 1 : -1];
typedef char YoumuCtorDequeOffset[offsetof(YoumuConstructorView, records_7d0)==0x7d0 ? 1 : -1];
YoumuConstructorView::YoumuConstructorView(int init_arg) : YoumuCharacterBaseView(init_arg)
{
    owned_manager_658 = new YoumuCtorObjectManager(this);
}
}
