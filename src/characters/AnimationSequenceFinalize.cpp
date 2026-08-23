#include "AnimationSequenceVirtuals.hpp"

namespace th105 {

int AnimationSequenceObjectView::set_action_and_finalize(short action)
{
    set_action(action);
    return finalize_action();
}

int AnimationSequenceObjectView::set_action_sequence_and_finalize(
    short action, int sequence)
{
    set_action_sequence(action, sequence);
    return finalize_action();
}

} // namespace th105
