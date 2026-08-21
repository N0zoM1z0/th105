#include "EffectSprite.hpp"


IColor::IColor() : value_04(0)
{
}




CEffectSprite::CEffectSprite()
{
    reinterpret_cast<th105::FighterActionScratch *>(this)
        ->reset_fighter_action_scratch();
}
