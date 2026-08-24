#include "RosterObjectPools.hpp"
#include "TObjectManagerBase.hpp"


class InfoEffectObject {
public:
    virtual ~InfoEffectObject();
};

class CSelectObject {
public:
    virtual ~CSelectObject();
};

class WeatherEffectObject {
public:
    virtual ~WeatherEffectObject();
};

class EffectObject {
public:
    virtual ~EffectObject();
};

class SystemEffectObject {
public:
    virtual ~SystemEffectObject();
};


template <typename ObjectType>
CHandleManagerEx<ObjectType>::CHandleManagerEx()
    : slots_04(), generations_14(), free_slots_24(), lock_34()
{
    generation_counter_30 = 0;
}


template <typename ObjectType>
CHandleManagerEx<ObjectType>::~CHandleManagerEx()
{
    for (unsigned index = 0; index < slots_04.size(); ++index) {
        ObjectType *object = slots_04[index];
        if (object != 0)
            delete object;
    }
}


namespace {

struct CHandleManagerObjectHandle32 {
    unsigned short slot;
    unsigned short generation;
};

} // namespace


template <typename ObjectType>
void CHandleManagerEx<ObjectType>::release_handle(unsigned handle_token)
{
    lock_34.enter();
    const unsigned index =
        reinterpret_cast<CHandleManagerObjectHandle32 *>(&handle_token)->slot;
    if (generations_14[index] ==
        reinterpret_cast<CHandleManagerObjectHandle32 *>(
            &handle_token)->generation) {
        generations_14[index] = 0;
        slots_04.at(index)->~ObjectType();
        handle_token = index;
        free_slots_24.push_back(handle_token);
    }
    lock_34.leave();
}


#define TH105_INSTANTIATE_HANDLE_MANAGER(ObjectType) \
    template CHandleManagerEx<ObjectType>::CHandleManagerEx(); \
    template CHandleManagerEx<ObjectType>::~CHandleManagerEx()

TH105_INSTANTIATE_HANDLE_MANAGER(ReimuObject);
TH105_INSTANTIATE_HANDLE_MANAGER(MarisaObject);
TH105_INSTANTIATE_HANDLE_MANAGER(SakuyaObject);
TH105_INSTANTIATE_HANDLE_MANAGER(AliceObject);
TH105_INSTANTIATE_HANDLE_MANAGER(PatchouliObject);
TH105_INSTANTIATE_HANDLE_MANAGER(YoumuObject);
TH105_INSTANTIATE_HANDLE_MANAGER(RemiliaObject);
TH105_INSTANTIATE_HANDLE_MANAGER(YuyukoObject);
TH105_INSTANTIATE_HANDLE_MANAGER(YukariObject);
TH105_INSTANTIATE_HANDLE_MANAGER(SuikaObject);
TH105_INSTANTIATE_HANDLE_MANAGER(UdongeObject);
TH105_INSTANTIATE_HANDLE_MANAGER(KomachiObject);
TH105_INSTANTIATE_HANDLE_MANAGER(AyaObject);
TH105_INSTANTIATE_HANDLE_MANAGER(IkuObject);
TH105_INSTANTIATE_HANDLE_MANAGER(TenshiObject);
TH105_INSTANTIATE_HANDLE_MANAGER(InfoEffectObject);
TH105_INSTANTIATE_HANDLE_MANAGER(CSelectObject);
TH105_INSTANTIATE_HANDLE_MANAGER(WeatherEffectObject);
TH105_INSTANTIATE_HANDLE_MANAGER(EffectObject);
TH105_INSTANTIATE_HANDLE_MANAGER(SystemEffectObject);

template void CHandleManagerEx<SystemEffectObject>::release_handle(unsigned);

#undef TH105_INSTANTIATE_HANDLE_MANAGER
