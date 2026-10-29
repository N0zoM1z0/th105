#include "AnimationSpriteState.hpp"



AnimationSpriteState::AnimationSpriteState()
{
    reinterpret_cast<th105::FighterActionScratch *>(this)
        ->reset_fighter_action_scratch();
}
