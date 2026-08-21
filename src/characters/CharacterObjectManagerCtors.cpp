#define TH105_TOBJECT_MANAGER_BASE_DECLARATIONS_ONLY
#include "TObjectManagerBase.hpp"
#undef TH105_TOBJECT_MANAGER_BASE_DECLARATIONS_ONLY

class Reimu;
class Marisa;
class Sakuya;
class Alice;
class Patchouli;
class Youmu;
class Remilia;
class Yuyuko;
class Yukari;
class Suika;
class Udonge;
class Komachi;
class Aya;
class Iku;
class Tenshi;

class ICharacterObjectManager {
public:
    virtual ~ICharacterObjectManager();
};

template <typename FighterType, typename ObjectType>
class CharacterObjectManager
    : public ICharacterObjectManager,
      public TObjectManagerBase<ObjectType, CharacterObject> {
public:
    CharacterObjectManager(FighterType *owner);

private:
    FighterType *owner_64;
};

template <typename FighterType, typename ObjectType>
CharacterObjectManager<FighterType, ObjectType>::CharacterObjectManager(
    FighterType *owner)
    : TObjectManagerBase<ObjectType, CharacterObject>(), owner_64(owner)
{
    this->preallocate_object_pool(256);
}

typedef char CharacterObjectManagerAlice_size_must_be_0x68[
    sizeof(CharacterObjectManager<Alice, AliceObject>) == 0x68 ? 1 : -1];

#define TH105_INSTANTIATE_CHARACTER_OBJECT_MANAGER_CTOR(FighterName) \
    template CharacterObjectManager<FighterName, FighterName##Object>:: \
        CharacterObjectManager(FighterName *owner)

TH105_INSTANTIATE_CHARACTER_OBJECT_MANAGER_CTOR(Reimu);
TH105_INSTANTIATE_CHARACTER_OBJECT_MANAGER_CTOR(Marisa);
TH105_INSTANTIATE_CHARACTER_OBJECT_MANAGER_CTOR(Sakuya);
TH105_INSTANTIATE_CHARACTER_OBJECT_MANAGER_CTOR(Alice);
TH105_INSTANTIATE_CHARACTER_OBJECT_MANAGER_CTOR(Patchouli);
TH105_INSTANTIATE_CHARACTER_OBJECT_MANAGER_CTOR(Youmu);
TH105_INSTANTIATE_CHARACTER_OBJECT_MANAGER_CTOR(Remilia);
TH105_INSTANTIATE_CHARACTER_OBJECT_MANAGER_CTOR(Yuyuko);
TH105_INSTANTIATE_CHARACTER_OBJECT_MANAGER_CTOR(Yukari);
TH105_INSTANTIATE_CHARACTER_OBJECT_MANAGER_CTOR(Suika);
TH105_INSTANTIATE_CHARACTER_OBJECT_MANAGER_CTOR(Udonge);
TH105_INSTANTIATE_CHARACTER_OBJECT_MANAGER_CTOR(Komachi);
TH105_INSTANTIATE_CHARACTER_OBJECT_MANAGER_CTOR(Aya);
TH105_INSTANTIATE_CHARACTER_OBJECT_MANAGER_CTOR(Iku);
TH105_INSTANTIATE_CHARACTER_OBJECT_MANAGER_CTOR(Tenshi);

#undef TH105_INSTANTIATE_CHARACTER_OBJECT_MANAGER_CTOR
