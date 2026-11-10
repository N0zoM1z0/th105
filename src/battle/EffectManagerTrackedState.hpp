#pragma once
#include "EffectManager.hpp"
#include <list>
#include <stddef.h>

// Shared nonconstructing view of the native pool and checked object list.
// The public manager retains CollisionList until its full use is reconciled.
template <typename ObjectType, typename BaseObjectType>
struct EffectManagerTrackedState {
    virtual ~EffectManagerTrackedState();
    CHandleManagerEx<ObjectType> handle_pool_04;
    std::list<BaseObjectType *> linked_objects_54;
};

typedef EffectManagerTrackedState<CSelectObject, EffectObjectBase>
    SelectEffectManagerTrackedState;
typedef char EffectTrackedState_pool_offset[
    offsetof(SelectEffectManagerTrackedState, handle_pool_04) == 4 ? 1 : -1];
typedef char EffectTrackedState_list_offset[
    offsetof(SelectEffectManagerTrackedState, linked_objects_54) == 0x54 ? 1 : -1];
typedef char EffectTrackedState_size[
    sizeof(SelectEffectManagerTrackedState) == 0x60 ? 1 : -1];
