#include "RosterObjectPools.hpp"

#include <cstring>


namespace th105 {

namespace {

__forceinline unsigned &owner_field(void *owner, unsigned offset)
{
    return *reinterpret_cast<unsigned *>(
        reinterpret_cast<unsigned char *>(owner) + offset);
}

} // namespace


#define TH105_DEFINE_ROSTER_OBJECT_SPAWN(FighterName)                         \
::FighterName##Object *FighterName##ObjectManager::spawn_object(              \
    ::FighterName##Object *parent,                                            \
    ::FighterName##Object *related,                                           \
    int action_id,                                                            \
    float x,                                                                  \
    float y,                                                                  \
    signed char facing,                                                       \
    unsigned char field_33c,                                                  \
    const unsigned *copied_words,                                             \
    int copied_word_count)                                                    \
{                                                                             \
    FighterName##Object *object = base_04.acquire_and_link_object();          \
                                                                              \
    void *owner = owner_64;                                                   \
    object->owner_348 = owner;                                                \
    object->state_158.owner_010 = owner;                                      \
    object->owner_field_000 = owner_field(owner, 0x130);                      \
    object->state_158.owner_field_008 = owner_field(owner, 0x160);            \
                                                                              \
    if (parent != 0) {                                                        \
        std::deque<FighterName##Object *> *child_refs =                       \
            &parent->child_refs_350;                                          \
        object->parent_34c = parent;                                          \
        parent = object;                                                      \
        child_refs->push_back(parent);                                        \
    }                                                                         \
                                                                              \
    if (copied_word_count > 0) {                                              \
        object->copied_words_340 = new unsigned[copied_word_count];           \
        if (copied_words != 0) {                                              \
            memcpy(                                                           \
                object->copied_words_340,                                     \
                copied_words,                                                 \
                copied_word_count * sizeof(unsigned));                       \
        }                                                                     \
    }                                                                         \
                                                                              \
    object->state_158.related_014 = related;                                  \
    object->state_158.related_018 = related->state_158.related_018;           \
    object->effect_000.object_x_0e8 = x;                                      \
    object->effect_000.object_facing_100 = facing;                            \
    object->effect_000.object_y_0ec = y;                                      \
                                                                              \
    object->field_33c = field_33c;                                            \
    object->set_action(action_id);                                            \
    return object;                                                            \
}

TH105_DEFINE_ROSTER_OBJECT_SPAWN(Reimu)
TH105_DEFINE_ROSTER_OBJECT_SPAWN(Marisa)
TH105_DEFINE_ROSTER_OBJECT_SPAWN(Alice)
TH105_DEFINE_ROSTER_OBJECT_SPAWN(Patchouli)
TH105_DEFINE_ROSTER_OBJECT_SPAWN(Youmu)
TH105_DEFINE_ROSTER_OBJECT_SPAWN(Remilia)
TH105_DEFINE_ROSTER_OBJECT_SPAWN(Yuyuko)
TH105_DEFINE_ROSTER_OBJECT_SPAWN(Yukari)
TH105_DEFINE_ROSTER_OBJECT_SPAWN(Suika)
TH105_DEFINE_ROSTER_OBJECT_SPAWN(Udonge)
TH105_DEFINE_ROSTER_OBJECT_SPAWN(Komachi)
TH105_DEFINE_ROSTER_OBJECT_SPAWN(Aya)
TH105_DEFINE_ROSTER_OBJECT_SPAWN(Iku)
TH105_DEFINE_ROSTER_OBJECT_SPAWN(Tenshi)

#undef TH105_DEFINE_ROSTER_OBJECT_SPAWN

} // namespace th105
