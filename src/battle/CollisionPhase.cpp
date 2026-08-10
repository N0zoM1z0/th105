#include "Collision.hpp"

namespace th105 {

void __cdecl free_transient_list_node(void *node);
void __cdecl _invalid_parameter_noinfo(void);

namespace {

struct OwnedObjectManagerCollisionView {
    virtual void slot_00();
    virtual void slot_04();
    virtual void slot_08();
    virtual void slot_0c();
    virtual void slot_10();
    virtual void slot_14();
    virtual void slot_18();
    virtual void slot_1c();
    virtual void slot_20();
    virtual CollisionList *collision_objects_24();
};

struct FighterCollisionPhaseView {
    unsigned char unknown_000[0x1af];
    unsigned char collision_active_1af;
    unsigned char unknown_1b0[0x339];
    unsigned char state_4e9;
    unsigned char state_4ea;
    unsigned char unknown_4eb[0x16d];
    OwnedObjectManagerCollisionView *owned_manager_658;
};

struct ObjectClassificationFrameView {
    unsigned char unknown_00[0x4c];
    unsigned flags_4c;
    unsigned char unknown_50[0x0c];
    unsigned char *family1_begin_5c;
    unsigned char *family1_end_60;
    unsigned unknown_64;
    unsigned char *family2_begin_6c;
    unsigned char *family2_end_70;
};

struct CollisionObjectClassificationView {
    unsigned char unknown_000[0x158];
    ObjectClassificationFrameView *frame_158;
    unsigned char unknown_15c[0x38];
    void *extension_194;
};

struct DeferredFighterView {
    unsigned char unknown_000[0x174];
    short value_174;
    short maximum_176;
};

struct CollisionListIncsizeView {
    void std_list_incsize_pointer(unsigned amount);
};

__forceinline void reset_transient_list(CollisionList *list)
{
    CollisionListNode *sentinel = list->sentinel;
    CollisionListNode *node = sentinel->next;
    sentinel->next = sentinel;
    sentinel->previous = sentinel;
    list->count = 0;
    while (node != sentinel) {
        CollisionListNode *next = node->next;
        free_transient_list_node(node);
        node = next;
    }
}

__forceinline void append_payload(CollisionList *list, void *payload)
{
    CollisionListNode *sentinel = list->sentinel;
    CollisionListNode *node = create_collision_list_node(
        sentinel, sentinel->previous, &payload);
    reinterpret_cast<CollisionListIncsizeView *>(list)
        ->std_list_incsize_pointer(1);
    sentinel->previous = node;
    node->previous->next = node;
}

__forceinline int entry_count(unsigned char *begin, unsigned char *end)
{
    return begin == 0 ? 0 : (end - begin) >> 4;
}

__forceinline void require_not_sentinel(
    CollisionListNode *node,
    CollisionListNode *sentinel)
{
    if (node == sentinel) {
        _invalid_parameter_noinfo();
    }
}

__forceinline void classify_owned_object(
    CollisionContext *context,
    CollisionObject *object)
{
    CollisionObjectClassificationView *view =
        reinterpret_cast<CollisionObjectClassificationView *>(object);
    ObjectClassificationFrameView *frame = view->frame_158;
    const int slot = reinterpret_cast<Fighter *>(
        object->owner_16c)->player_index_334;
    int family2_count = entry_count(
        frame->family2_begin_6c, frame->family2_end_70);
    int family1_count = entry_count(
        frame->family1_begin_5c, frame->family1_end_60);

    if (view->extension_194 != 0) {
        ++family2_count;
        if ((frame->flags_4c & 0x01000000) != 0) {
            ++family1_count;
        }
    }

    if (family2_count != 0 && object->result_180 == 0 &&
        static_cast<signed char>(object->result_slot_184) > 0) {
        prepare_collision_geometry_from_frame(object);
        append_payload(&context->family_0[slot], object);
        if (family1_count != 0) {
            append_payload(&context->family_1[slot], object);
        }
        append_payload(&context->family_2[slot], object);
    } else if (family1_count != 0) {
        prepare_collision_geometry_from_frame(object);
        append_payload(&context->family_1[slot], object);
        append_payload(&context->family_2[slot], object);
    }
}

__forceinline void append_eligible_fighter(
    CollisionContext *context,
    Fighter *fighter,
    int slot)
{
    FighterCollisionPhaseView *view =
        reinterpret_cast<FighterCollisionPhaseView *>(fighter);
    if (view->collision_active_1af != 0 && fighter->result_180 == 0 &&
        static_cast<signed char>(fighter->unknown_184[0]) > 0) {
        append_payload(&context->family_0[slot], fighter);
        append_payload(&context->family_2[slot], fighter);
    }
}

} // namespace

void CollisionContext::run_attack_projectile_collision_phase()
{
    int slot;
    for (slot = 0; slot != 2; ++slot) {
        reset_transient_list(&family_0[slot]);
        reset_transient_list(&family_1[slot]);
        reset_transient_list(&family_2[slot]);
        deferred_74[slot] = 0;
        deferred_7c[slot] = 0;
    }

    for (slot = 0; slot != 2; ++slot) {
        Fighter *fighter = fighters[slot];
        FighterCollisionPhaseView *fighter_view =
            reinterpret_cast<FighterCollisionPhaseView *>(fighter);
        prepare_collision_geometry_from_frame(fighter);
        fighter_view->state_4ea = fighter_view->state_4e9;

        CollisionList *begin_list =
            fighter_view->owned_manager_658->collision_objects_24();
        CollisionListNode *node = begin_list->sentinel->next;
        CollisionList *end_list =
            fighter_view->owned_manager_658->collision_objects_24();
        if (begin_list != end_list) {
            _invalid_parameter_noinfo();
        }
        for (; node != end_list->sentinel; node = node->next) {
            require_not_sentinel(node, begin_list->sentinel);
            classify_owned_object(
                this, static_cast<CollisionObject *>(node->payload));
            require_not_sentinel(node, begin_list->sentinel);
        }
    }

    for (slot = 0; slot != 2; ++slot) {
        append_eligible_fighter(this, fighters[slot], slot);
    }

    dispatch_family1_object_clashes();
    dispatch_family2_against_family1();

    for (slot = 0; slot != 2; ++slot) {
        Fighter *fighter = fighters[slot];
        Fighter *other = fighter->other_fighter_170;
        CollisionList *attacks = &family_0[slot];
        for (CollisionListNode *node = attacks->sentinel->next;
             node != attacks->sentinel;
             node = node->next) {
            require_not_sentinel(node, attacks->sentinel);
            AttackCandidate *candidate =
                static_cast<AttackCandidate *>(node->payload);
            resolve_attack_candidate_against_fighter(candidate, other);
            require_not_sentinel(node, attacks->sentinel);
            if ((candidate->frame_1a4->flags_50 & 0x00100000) != 0) {
                require_not_sentinel(node, attacks->sentinel);
                resolve_attack_candidate_against_fighter(candidate, fighter);
            }
            require_not_sentinel(node, attacks->sentinel);
        }
    }

    for (slot = 0; slot != 2; ++slot) {
        Fighter *fighter = fighters[slot];
        DeferredFighterView *fighter_view =
            reinterpret_cast<DeferredFighterView *>(fighter);
        if (deferred_74[slot] != 0 && fighter_view->value_174 > 0) {
            int value = static_cast<short>(deferred_74[slot]) +
                static_cast<int>(fighter_view->value_174);
            if (fighter_view->maximum_176 <= value) {
                value = fighter_view->maximum_176;
            }
            fighter_view->value_174 = static_cast<short>(value);
        }
        if (deferred_7c[slot] != 0) {
            fighter->apply_deferred_counter_558(
                static_cast<short>(deferred_7c[slot]));
        }
    }
}

} // namespace th105
