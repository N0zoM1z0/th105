#include "TObjectManagerBase.hpp"


template TObjectManagerBase<ReimuObject, CharacterObject>::TObjectManagerBase();
template TObjectManagerBase<MarisaObject, CharacterObject>::TObjectManagerBase();
template TObjectManagerBase<SakuyaObject, CharacterObject>::TObjectManagerBase();
template TObjectManagerBase<AliceObject, CharacterObject>::TObjectManagerBase();
template TObjectManagerBase<PatchouliObject, CharacterObject>::TObjectManagerBase();
template TObjectManagerBase<YoumuObject, CharacterObject>::TObjectManagerBase();
template TObjectManagerBase<RemiliaObject, CharacterObject>::TObjectManagerBase();
template TObjectManagerBase<YuyukoObject, CharacterObject>::TObjectManagerBase();
template TObjectManagerBase<YukariObject, CharacterObject>::TObjectManagerBase();
template TObjectManagerBase<SuikaObject, CharacterObject>::TObjectManagerBase();
template TObjectManagerBase<UdongeObject, CharacterObject>::TObjectManagerBase();
template TObjectManagerBase<KomachiObject, CharacterObject>::TObjectManagerBase();
template TObjectManagerBase<AyaObject, CharacterObject>::TObjectManagerBase();
template TObjectManagerBase<IkuObject, CharacterObject>::TObjectManagerBase();
template TObjectManagerBase<TenshiObject, CharacterObject>::TObjectManagerBase();

#define TH105_INSTANTIATE_TOBJECT_MANAGER_BASE_DTOR(ObjectName) \
    template TObjectManagerBase<ObjectName, CharacterObject>:: \
        ~TObjectManagerBase()

TH105_INSTANTIATE_TOBJECT_MANAGER_BASE_DTOR(ReimuObject);
TH105_INSTANTIATE_TOBJECT_MANAGER_BASE_DTOR(MarisaObject);
TH105_INSTANTIATE_TOBJECT_MANAGER_BASE_DTOR(SakuyaObject);
TH105_INSTANTIATE_TOBJECT_MANAGER_BASE_DTOR(AliceObject);
TH105_INSTANTIATE_TOBJECT_MANAGER_BASE_DTOR(PatchouliObject);
TH105_INSTANTIATE_TOBJECT_MANAGER_BASE_DTOR(YoumuObject);
TH105_INSTANTIATE_TOBJECT_MANAGER_BASE_DTOR(RemiliaObject);
TH105_INSTANTIATE_TOBJECT_MANAGER_BASE_DTOR(YuyukoObject);
TH105_INSTANTIATE_TOBJECT_MANAGER_BASE_DTOR(YukariObject);
TH105_INSTANTIATE_TOBJECT_MANAGER_BASE_DTOR(SuikaObject);
TH105_INSTANTIATE_TOBJECT_MANAGER_BASE_DTOR(UdongeObject);
TH105_INSTANTIATE_TOBJECT_MANAGER_BASE_DTOR(KomachiObject);
TH105_INSTANTIATE_TOBJECT_MANAGER_BASE_DTOR(AyaObject);
TH105_INSTANTIATE_TOBJECT_MANAGER_BASE_DTOR(IkuObject);
TH105_INSTANTIATE_TOBJECT_MANAGER_BASE_DTOR(TenshiObject);

#undef TH105_INSTANTIATE_TOBJECT_MANAGER_BASE_DTOR
