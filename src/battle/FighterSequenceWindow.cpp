#include "SpellRuntime.hpp"
#include "Collision.hpp"

namespace th105 {

extern "C" void __cdecl _invalid_parameter_noinfo(void);

struct FighterSequenceIterator {
    unsigned unknown_00;
    FighterSequenceController *owner_04;
    unsigned absolute_position_08;

    FighterSequenceSlot *dereference_checked();
};

typedef char FighterSequenceIterator_size_must_be_0x0c[
    sizeof(FighterSequenceIterator) == 0x0c ? 1 : -1];

// The target helper returns its first argument after advancing the checked
// iterator by one sequence entry.  It is intentionally a declaration: its
// validation and erase behavior belong to 0x45C620, not to this caller.
FighterSequenceIterator *__stdcall erase_one_checked(
    FighterSequenceIterator *result,
    int unused,
    FighterSequenceController *owner,
    unsigned absolute_position);

struct FighterSequenceEffectWindowView {
    int reset_and_set_color();
};

extern unsigned char *g_battle_scene_renderer;

namespace {

__forceinline FighterSequenceSlot *slot_at_checked(
    FighterSequenceController *controller,
    unsigned absolute_position)
{
    const unsigned end = controller->head_0c + controller->live_count_10;
    if (absolute_position >= end) {
        _invalid_parameter_noinfo();
    }

    unsigned slot_index = absolute_position;
    if (controller->slot_capacity_08 <= absolute_position) {
        slot_index -= controller->slot_capacity_08;
    }
    return controller->slots_04[slot_index];
}

} // namespace

void Fighter::dispatch_indexed_sequence_window_45c8b0(
    signed char relative_index,
    int outcome,
    int source_token)
{
    (void)outcome;

    if (state_55a != 0) {
        FighterSequenceController *controller = &sequence_controller_55c;
        unsigned position = controller->head_0c;
        if (position > position + controller->live_count_10) {
            _invalid_parameter_noinfo();
        }

        position += relative_index;
        const unsigned begin = controller->head_0c;
        const unsigned end = begin + controller->live_count_10;
        if (position > end || position < begin) {
            _invalid_parameter_noinfo();
        }

        FighterSequenceIterator iterator;
        iterator.unknown_00 = 0;
        iterator.owner_04 = controller;
        iterator.absolute_position_08 = position;

        FighterSequenceSlot *slot = slot_at_checked(controller, position);
        const int category_is_two = state_4b8 == 2;
        signed char erase_count;
        if (static_cast<unsigned short>(slot->field_02) - category_is_two < 1) {
            erase_count = 1;
        } else {
            erase_count = static_cast<signed char>(
                iterator.dereference_checked()->field_02 - category_is_two);
        }

        if (slot_at_checked(controller, position)->record_id_00 >= 200) {
            reinterpret_cast<FighterSequenceEffectWindowView *>(
                reinterpret_cast<unsigned char *>(this) + 0x3d0)
                ->reset_and_set_color();
        }

        reinterpret_cast<PlayerIndexedCallbackView *>(
            g_battle_scene_renderer +
            static_cast<int>(player_index_334) * 0x154 + 0x1d4)
            ->invoke_indexed_record(
                slot_at_checked(controller, position)->record_id_00,
                source_token);

        for (signed char erased = 0; erased < erase_count; ++erased) {
            const unsigned erase_begin = controller->head_0c;
            const unsigned erase_end = erase_begin + controller->live_count_10;
            if (erase_begin > erase_end) {
                _invalid_parameter_noinfo();
            }
            if (iterator.owner_04 == 0 || iterator.owner_04 != controller) {
                _invalid_parameter_noinfo();
            }
            if (iterator.absolute_position_08 == erase_end) {
                break;
            }
            erase_one_checked(
                &iterator,
                0,
                iterator.owner_04,
                iterator.absolute_position_08);
        }

        state_55a = static_cast<signed char>(controller->live_count_10);
    }
}

} // namespace th105
