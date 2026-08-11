#include "Sakuya.hpp"

#include <string.h>

namespace th105 {

namespace {

typedef void (__thiscall *SetObjectAction)(SakuyaObject *, int);

__forceinline unsigned &owner_field(Sakuya *owner, unsigned offset)
{
    return *reinterpret_cast<unsigned *>(
        reinterpret_cast<unsigned char *>(owner) + offset);
}

} // namespace

SakuyaObject *SakuyaObjectManager::spawn_object(
    SakuyaObject *parent,
    SakuyaObject *related,
    int action_id,
    float x,
    float y,
    signed char facing,
    unsigned char field_33c,
    const unsigned *copied_words,
    int copied_word_count)
{
    SakuyaObject *object = base_04.acquire_and_link_object();

    Sakuya *owner = owner_64;
    object->owner_348 = owner;
    object->owner_168 = owner;
    object->field_130 = owner_field(owner, 0x130);
    unsigned const owner_field_160 = owner_field(owner, 0x160);

    if (parent != 0) {
        std::deque<SakuyaObject *> *child_refs = &parent->child_refs_350;
        object->field_160 = owner_field_160;
        object->parent_34c = parent;
        parent = object;
        child_refs->push_back(parent);
    } else {
        object->field_160 = owner_field_160;
    }

    if (copied_word_count > 0) {
        object->copied_words_340 = new unsigned[copied_word_count];
        if (copied_words != 0) {
            memcpy(
                object->copied_words_340,
                copied_words,
                copied_word_count * sizeof(unsigned));
        }
    }

    object->related_16c = related;
    object->x_ec = x;
    object->facing_104 = facing;
    object->y_f0 = y;
    object->copied_related_field_170 = related->copied_related_field_170;

    SetObjectAction const set_action =
        reinterpret_cast<SetObjectAction>(
            (*reinterpret_cast<void ***>(object))[2]);
    object->field_33c = field_33c;
    set_action(object, action_id);
    return object;
}

} // namespace th105
