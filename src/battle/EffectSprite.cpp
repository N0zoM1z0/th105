#include "EffectSprite.hpp"



CEffectSprite::CEffectSprite()
{
    reinterpret_cast<th105::FighterActionScratch *>(this)
        ->reset_fighter_action_scratch();
}
