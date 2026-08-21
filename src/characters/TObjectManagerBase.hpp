#pragma once

#include "battle/CollisionList.hpp"
#include "engine/CriticalSectionWrapper.hpp"

#include <list>
#include <stddef.h>
#include <vector>


class SakuyaObject;
class CharacterObject;
class ReimuObject;
class MarisaObject;
class AliceObject;
class PatchouliObject;
class YoumuObject;
class RemiliaObject;
class YuyukoObject;
class YukariObject;
class SuikaObject;
class UdongeObject;
class KomachiObject;
class AyaObject;
class IkuObject;
class TenshiObject;


template <typename ObjectType>
class CHandleManagerEx {
public:
    CHandleManagerEx();
    virtual ~CHandleManagerEx();

    std::vector<ObjectType *> slots_04;
    std::vector<unsigned> generations_14;
    std::list<unsigned> free_slots_24;
    unsigned generation_counter_30;
    th105::CriticalSectionWrapper lock_34;
};


template <typename ObjectType, typename BaseObjectType>
class TObjectManagerBase {
public:
    TObjectManagerBase();
    virtual ~TObjectManagerBase();
    void preallocate_object_pool(unsigned target_count);

    CHandleManagerEx<ObjectType> handle_pool_04;
    th105::CollisionList linked_objects_54;
};


#ifndef TH105_TOBJECT_MANAGER_BASE_DECLARATIONS_ONLY
template <typename ObjectType, typename BaseObjectType>
TObjectManagerBase<ObjectType, BaseObjectType>::TObjectManagerBase()
    : handle_pool_04(), linked_objects_54()
{
}
#endif


typedef char SakuyaCHandleManagerEx_size_must_be_0x50[
    sizeof(CHandleManagerEx<SakuyaObject>) == 0x50 ? 1 : -1];
typedef TObjectManagerBase<SakuyaObject, CharacterObject>
    SakuyaTObjectManagerBase;
typedef char SakuyaTObjectManagerBase_size_must_be_0x60[
    sizeof(SakuyaTObjectManagerBase) == 0x60 ? 1 : -1];
typedef char SakuyaTObjectManagerBase_pool_offset_must_be_0x04[
    offsetof(SakuyaTObjectManagerBase, handle_pool_04) == 0x04 ? 1 : -1];
typedef char SakuyaTObjectManagerBase_list_offset_must_be_0x54[
    offsetof(SakuyaTObjectManagerBase, linked_objects_54) == 0x54 ? 1 : -1];
