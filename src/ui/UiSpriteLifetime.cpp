// Real CSprite lifetime callbacks. Base initialization and virtual-table
// restoration are provided by ordinary C++, not hand-written vptr fields.
#include "battle/EffectSprite.hpp"

CSprite::CSprite() {}
CSprite::~CSprite() {}
