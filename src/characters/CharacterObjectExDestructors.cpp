#include "characters/CharacterObject.hpp"

#include <deque>
#include <stddef.h>

// Destructor-TU view of the real intermediate roster-object base.  The pool
// constructor TU intentionally keeps its existing narrow layout view: exposing
// this polymorphic layer there changes VC8 constructor lowering, while current
// RTTI/vtable writes prove that destruction occurs through
// CharacterObjectEx<Fighter,Object>.  Keep this hierarchy local to the lifetime
// TU unless constructor-side evidence independently closes that visibility gap.

class Reimu;
class ReimuObject;
class Marisa;
class MarisaObject;
class Sakuya;
class SakuyaObject;
class Alice;
class AliceObject;
class Patchouli;
class PatchouliObject;
class Youmu;
class YoumuObject;
class Remilia;
class RemiliaObject;
class Yuyuko;
class YuyukoObject;
class Yukari;
class YukariObject;
class Suika;
class SuikaObject;
class Udonge;
class UdongeObject;
class Komachi;
class KomachiObject;
class Aya;
class AyaObject;
class Iku;
class IkuObject;
class Tenshi;
class TenshiObject;

template <typename FighterType, typename ObjectType>
class CharacterObjectEx : public CharacterObject {
public:
    virtual ~CharacterObjectEx();

    void *owner_348;
    ObjectType *parent_34c;
    std::deque<ObjectType *> child_refs_350;
    unsigned char unknown_364[0x24];
};

class ReimuObject : public CharacterObjectEx<Reimu, ReimuObject> {
public:
    __forceinline ReimuObject() {}
};

class MarisaObject : public CharacterObjectEx<Marisa, MarisaObject> {
public:
    __forceinline MarisaObject() {}
};

class SakuyaObject : public CharacterObjectEx<Sakuya, SakuyaObject> {
public:
    __forceinline SakuyaObject() {}
};

class AliceObject : public CharacterObjectEx<Alice, AliceObject> {
public:
    __forceinline AliceObject() {}
    unsigned int unknown_388;
};

class PatchouliObject : public CharacterObjectEx<Patchouli, PatchouliObject> {
public:
    __forceinline PatchouliObject() {}
};

class YoumuObject : public CharacterObjectEx<Youmu, YoumuObject> {
public:
    __forceinline YoumuObject() {}
};

class RemiliaObject : public CharacterObjectEx<Remilia, RemiliaObject> {
public:
    __forceinline RemiliaObject() {}
};

class YuyukoObject : public CharacterObjectEx<Yuyuko, YuyukoObject> {
public:
    __forceinline YuyukoObject() {}
};

class YukariObject : public CharacterObjectEx<Yukari, YukariObject> {
public:
    __forceinline YukariObject() {}
};

class SuikaObject : public CharacterObjectEx<Suika, SuikaObject> {
public:
    __forceinline SuikaObject() {}
};

class UdongeObject : public CharacterObjectEx<Udonge, UdongeObject> {
public:
    __forceinline UdongeObject() {}
};

class KomachiObject : public CharacterObjectEx<Komachi, KomachiObject> {
public:
    __forceinline KomachiObject() {}
};

class AyaObject : public CharacterObjectEx<Aya, AyaObject> {
public:
    __forceinline AyaObject() {}
};

class IkuObject : public CharacterObjectEx<Iku, IkuObject> {
public:
    __forceinline IkuObject() {}
};

class TenshiObject : public CharacterObjectEx<Tenshi, TenshiObject> {
public:
    __forceinline TenshiObject() {}
};

template <typename FighterType, typename ObjectType>
CharacterObjectEx<FighterType, ObjectType>::~CharacterObjectEx()
{
    if (parent_34c != 0) {
        typename std::deque<ObjectType *>::iterator it =
            parent_34c->child_refs_350.begin();
        for (; it != parent_34c->child_refs_350.end(); ++it) {
            if (*it == static_cast<ObjectType *>(this)) {
                parent_34c->child_refs_350.erase(it);
                break;
            }
        }
    }

    if (!child_refs_350.empty()) {
        for (typename std::deque<ObjectType *>::iterator it = child_refs_350.begin();
             it != child_refs_350.end(); ++it) {
            (*it)->parent_34c = 0;
        }
    }
}

typedef char CharacterObjectEx_Reimu_size_must_be_0x388[
    sizeof(CharacterObjectEx<Reimu, ReimuObject>) == 0x388 ? 1 : -1];
typedef char ReimuObject_size_must_be_0x388[
    sizeof(ReimuObject) == 0x388 ? 1 : -1];
typedef char AliceObject_size_must_be_0x38c[
    sizeof(AliceObject) == 0x38c ? 1 : -1];

template CharacterObjectEx<Reimu, ReimuObject>::~CharacterObjectEx();
template CharacterObjectEx<Marisa, MarisaObject>::~CharacterObjectEx();
template CharacterObjectEx<Sakuya, SakuyaObject>::~CharacterObjectEx();
template CharacterObjectEx<Alice, AliceObject>::~CharacterObjectEx();
template CharacterObjectEx<Patchouli, PatchouliObject>::~CharacterObjectEx();
template CharacterObjectEx<Youmu, YoumuObject>::~CharacterObjectEx();
template CharacterObjectEx<Remilia, RemiliaObject>::~CharacterObjectEx();
template CharacterObjectEx<Yuyuko, YuyukoObject>::~CharacterObjectEx();
template CharacterObjectEx<Yukari, YukariObject>::~CharacterObjectEx();
template CharacterObjectEx<Suika, SuikaObject>::~CharacterObjectEx();
template CharacterObjectEx<Udonge, UdongeObject>::~CharacterObjectEx();
template CharacterObjectEx<Komachi, KomachiObject>::~CharacterObjectEx();
template CharacterObjectEx<Aya, AyaObject>::~CharacterObjectEx();
template CharacterObjectEx<Iku, IkuObject>::~CharacterObjectEx();
template CharacterObjectEx<Tenshi, TenshiObject>::~CharacterObjectEx();
