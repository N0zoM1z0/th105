#include "Collision.hpp"

namespace th105 {

extern "C" void __cdecl _invalid_parameter_noinfo(void);

namespace {

unsigned frame_flags_50(const CollisionObject *object)
{
    const unsigned char *frame =
        reinterpret_cast<const unsigned char *>(object->frame_1a4);
    return *reinterpret_cast<const unsigned *>(frame + 0x50);
}

} // namespace

void CollisionContext::dispatch_family2_against_family1()
{
    Fighter *volatile *fighter = fighters;
    int fighter_count = 2;

    do {
        const int source_slot =
            static_cast<int>((*fighter)->player_index_334);
        CollisionList *source_list = &family_2[source_slot];
        CollisionListNode *source_it = source_list->sentinel->next;

        while (source_it != source_list->sentinel) {
            if (source_it == source_list->sentinel) {
                _invalid_parameter_noinfo();
            }
            CollisionObject *source =
                static_cast<CollisionObject *>(source_it->payload);

            if (source->result_180 == 0) {
                if (source_it == source_list->sentinel) {
                    _invalid_parameter_noinfo();
                }
                if (source->result_slot_184 != 0) {
                    Fighter *other_fighter = (*fighter)->other_fighter_170;
                    const int other_slot =
                        static_cast<int>(other_fighter->player_index_334);
                    CollisionList *other_list = &family_1[other_slot];
                    CollisionListNode *other_it = other_list->sentinel->next;

                    while (other_it != other_list->sentinel) {
                        if (other_it == other_list->sentinel) {
                            _invalid_parameter_noinfo();
                        }
                        if (source_it == source_list->sentinel) {
                            _invalid_parameter_noinfo();
                        }
                        CollisionObject *other =
                            static_cast<CollisionObject *>(other_it->payload);
                        if (!try_group_b_pair_response(source, other)) {
                            if (other_it == other_list->sentinel) {
                                _invalid_parameter_noinfo();
                            }
                            if (source_it == source_list->sentinel) {
                                _invalid_parameter_noinfo();
                            }
                            try_group_a_vs_group_b_interaction(source, other);
                        }
                        if (other_it == other_list->sentinel) {
                            _invalid_parameter_noinfo();
                        }
                        other_it = other_it->next;
                    }

                    if (source_it == source_list->sentinel) {
                        _invalid_parameter_noinfo();
                    }
                    if ((frame_flags_50(source) & 0x100000) != 0) {
                        CollisionList *same_list = &family_1[source_slot];
                        CollisionListNode *same_it = same_list->sentinel->next;

                        while (same_it != same_list->sentinel) {
                            if (source_it == source_list->sentinel) {
                                _invalid_parameter_noinfo();
                            }
                            if (same_it == same_list->sentinel) {
                                _invalid_parameter_noinfo();
                            }
                            CollisionObject *same =
                                static_cast<CollisionObject *>(same_it->payload);
                            if (source != same) {
                                if (same_it == same_list->sentinel) {
                                    _invalid_parameter_noinfo();
                                }
                                if (source_it == source_list->sentinel) {
                                    _invalid_parameter_noinfo();
                                }
                                if (!try_group_b_pair_response(source, same)) {
                                    if (same_it == same_list->sentinel) {
                                        _invalid_parameter_noinfo();
                                    }
                                    if (source_it == source_list->sentinel) {
                                        _invalid_parameter_noinfo();
                                    }
                                    try_group_a_vs_group_b_interaction(
                                        source, same);
                                }
                            }
                            if (same_it == same_list->sentinel) {
                                _invalid_parameter_noinfo();
                            }
                            same_it = same_it->next;
                        }
                    }
                }
            }

            if (source_it == source_list->sentinel) {
                _invalid_parameter_noinfo();
            }
            source_it = source_it->next;
        }
        ++fighter;
    } while (--fighter_count != 0);
}

} // namespace th105
