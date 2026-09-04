#include <deque>
#include "battle/SpellRuntime.hpp"
#include "battle/Collision.hpp"

namespace th105 {

class FighterSequenceEffectWindowView {
public:
    int reset_and_set_color();
};


extern unsigned char *g_battle_scene_renderer;

static PlayerIndexedCallbackView *player_indexed_callback_at(int player_index)
{
    return reinterpret_cast<PlayerIndexedCallbackView *>(
        g_battle_scene_renderer + 0x1d4 + player_index * 0x154);
}

typedef std::deque<FighterSequenceSlot> FighterSequenceDeque;
typedef char fighter_sequence_deque_size[
    sizeof(FighterSequenceDeque) == 0x14 ? 1 : -1];
typedef char fighter_sequence_iterator_size[
    sizeof(FighterSequenceDeque::iterator) == 0x0c ? 1 : -1];

void Fighter::dispatch_indexed_sequence_window_45c8b0(
    signed char relative_index,
    int outcome,
    int source_token)
{
    (void)outcome;

    if (state_55a == 0)
        return;

    FighterSequenceDeque &sequence =
        *reinterpret_cast<FighterSequenceDeque *>(&sequence_controller_55c);
    FighterSequenceDeque::iterator iterator =
        sequence.begin() + relative_index;

    int category = static_cast<unsigned short>((*iterator).field_02);
    category -= state_4b8 == 2 ? 1 : 0;

    signed char erase_count;
    if (category < 1) {
        erase_count = 1;
    } else {
        erase_count = static_cast<signed char>(
            (*iterator).field_02 - (state_4b8 == 2 ? 1 : 0));
    }

    if ((*iterator).record_id_00 >= 200) {
        reinterpret_cast<FighterSequenceEffectWindowView *>(
            reinterpret_cast<unsigned char *>(this) + 0x3d0)
            ->reset_and_set_color();
    }

    player_indexed_callback_at(player_index_334)
        ->invoke_indexed_record((*iterator).record_id_00, source_token);

    for (signed char erased = 0;
         erased < erase_count && iterator != sequence.end();
         ++erased) {
        iterator = sequence.erase(iterator);
    }

    state_55a = static_cast<signed char>(sequence_controller_55c.live_count_10);
}

} // namespace th105
