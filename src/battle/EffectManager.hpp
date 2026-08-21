#pragma once

#include "characters/TObjectManagerBase.hpp"

#include <map>
#include <vector>


class CSelectObject;
class WeatherEffectObject;
class EffectObject;
class InfoEffectObject;
class EffectObjectBase;


class IEffectManager {
public:
    // Current CEffectManager<T> destructors inline this trivial primary-base
    // lifetime as a direct IEffectManager-vptr restore.
    virtual ~IEffectManager() {}
};


// Current CEffectManager<T> ctor/dtor code fixes this 0x14-byte owning deque
// layout.  Construction zeroes +4/+8/+0x0c/+0x10; destruction is the linked
// 0x00420AF0 owner cleanup that virtual-destroys live entries then frees blocks.
struct EffectOwnedDeque20 {
    unsigned proxy_or_base_00;
    void **map_04;
    unsigned map_size_08;
    unsigned offset_0c;
    unsigned count_10;

    __forceinline EffectOwnedDeque20()
        : map_04(0), map_size_08(0), offset_0c(0), count_10(0)
    {
    }

    ~EffectOwnedDeque20();
};


template <typename ObjectType>
class CEffectManager : public IEffectManager,
                       public TObjectManagerBase<ObjectType, EffectObjectBase> {
public:
    CEffectManager();
    virtual ~CEffectManager();

    ObjectType *spawn_effect(
        int effect_id,
        float x,
        float y,
        unsigned char facing,
        unsigned char spawn_flag,
        int spawn_context);

    // VC8 checked containers observed at +0x64, +0x74, and +0x88.
    std::vector<unsigned> resources_64;
    EffectOwnedDeque20 owned_74;
    std::map<unsigned, unsigned> lookup_88;
};


typedef char IEffectManager_size_must_be_0x04[
    sizeof(IEffectManager) == 0x04 ? 1 : -1];
typedef char EffectOwnedDeque20_size_must_be_0x14[
    sizeof(EffectOwnedDeque20) == 0x14 ? 1 : -1];
typedef char CSelectEffectManager_size_must_be_0x94[
    sizeof(CEffectManager<CSelectObject>) == 0x94 ? 1 : -1];
