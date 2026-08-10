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
    Fighter **fighter = fighters;
    // The checked iterators retain three independent end-sentinel lifetimes.
    struct EndSentinelLocals {
        CollisionListNode *source;
        CollisionListNode *other;
        CollisionListNode *same;
    } end_sentinels;
    int fighter_count = 2;

    do {
        const int source_slot =
            static_cast<int>((*fighter)->player_index_334);
        CollisionList *source_begin_list = &family_2[source_slot];
        CollisionList *source_end_list = &family_2[source_slot];
        CollisionListNode *source_it = source_begin_list->sentinel->next;
        end_sentinels.source = source_end_list->sentinel;

        if (source_begin_list != source_end_list) {
            _invalid_parameter_noinfo();
        }

source_loop:
        if (source_it == end_sentinels.source) {
            goto source_done;
        }
            if (source_it == source_begin_list->sentinel) {
                _invalid_parameter_noinfo();
            }

            if (static_cast<CollisionObject *>(
                    source_it->payload)->result_180 == 0) {
                if (source_it == source_begin_list->sentinel) {
                    _invalid_parameter_noinfo();
                }
                if (static_cast<CollisionObject *>(
                        source_it->payload)->result_slot_184 != 0) {
                    Fighter *other_fighter = (*fighter)->other_fighter_170;
                    const int other_slot =
                        static_cast<int>(other_fighter->player_index_334);
                    CollisionList *other_begin_list = &family_1[other_slot];
                    CollisionList *other_end_list = &family_1[other_slot];
                    CollisionListNode *other_it =
                        other_begin_list->sentinel->next;
                    end_sentinels.other = other_end_list->sentinel;

                    if (other_begin_list != other_end_list) {
                        _invalid_parameter_noinfo();
                    }

other_loop:
                    if (other_it == end_sentinels.other) {
                        goto other_done;
                    }
                        if (other_it == other_begin_list->sentinel) {
                            _invalid_parameter_noinfo();
                        }
                        if (source_it == source_begin_list->sentinel) {
                            _invalid_parameter_noinfo();
                        }
                        if (!try_group_b_pair_response(
                                static_cast<CollisionObject *>(
                                    source_it->payload),
                                static_cast<CollisionObject *>(
                                    other_it->payload))) {
                            if (other_it == other_begin_list->sentinel) {
                                _invalid_parameter_noinfo();
                            }
                            if (source_it == source_begin_list->sentinel) {
                                _invalid_parameter_noinfo();
                            }
                            try_group_a_vs_group_b_interaction(
                                static_cast<CollisionObject *>(
                                    source_it->payload),
                                static_cast<CollisionObject *>(
                                    other_it->payload));
                        }
                        if (other_it == other_begin_list->sentinel) {
                            _invalid_parameter_noinfo();
                        }
                        other_it = other_it->next;
                    goto other_loop;
other_done:

                    if (source_it == source_begin_list->sentinel) {
                        _invalid_parameter_noinfo();
                    }
                    if ((frame_flags_50(static_cast<CollisionObject *>(
                            source_it->payload)) & 0x100000) != 0) {
                        CollisionList *same_begin_list = &family_1[source_slot];
                        CollisionList *same_end_list = &family_1[source_slot];
                        CollisionListNode *same_it =
                            same_begin_list->sentinel->next;
                        end_sentinels.same = same_end_list->sentinel;

                        if (same_begin_list != same_end_list) {
                            _invalid_parameter_noinfo();
                        }

same_loop:
                        if (same_it == end_sentinels.same) {
                            goto same_done;
                        }
                            if (source_it == source_begin_list->sentinel) {
                                _invalid_parameter_noinfo();
                            }
                            if (same_it == same_begin_list->sentinel) {
                                _invalid_parameter_noinfo();
                            }
                            if (source_it->payload != same_it->payload) {
                                if (same_it == same_begin_list->sentinel) {
                                    _invalid_parameter_noinfo();
                                }
                                if (source_it == source_begin_list->sentinel) {
                                    _invalid_parameter_noinfo();
                                }
                                if (!try_group_b_pair_response(
                                        static_cast<CollisionObject *>(
                                            source_it->payload),
                                        static_cast<CollisionObject *>(
                                            same_it->payload))) {
                                    if (same_it == same_begin_list->sentinel) {
                                        _invalid_parameter_noinfo();
                                    }
                                    if (source_it ==
                                        source_begin_list->sentinel) {
                                        _invalid_parameter_noinfo();
                                    }
                                    try_group_a_vs_group_b_interaction(
                                        static_cast<CollisionObject *>(
                                            source_it->payload),
                                        static_cast<CollisionObject *>(
                                            same_it->payload));
                                }
                            }
                            if (same_it == same_begin_list->sentinel) {
                                _invalid_parameter_noinfo();
                            }
                            same_it = same_it->next;
                        goto same_loop;
same_done:
                        ;
                    }
                }
            }

            if (source_it == source_begin_list->sentinel) {
                _invalid_parameter_noinfo();
            }
            source_it = source_it->next;
        goto source_loop;
source_done:
        ++fighter;
    } while (--fighter_count != 0);
}

} // namespace th105
