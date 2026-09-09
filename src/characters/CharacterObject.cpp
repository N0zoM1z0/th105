#include "CharacterObject.hpp"
#include "battle/SecondaryAnimationRender.hpp"

#include <stdlib.h>


CharacterObject::CharacterObject()
{
    copied_words_340 = 0;
    field_338 = 0;
    field_344 = 0;
    field_346 = 0;
    state_158.value_01c = 0;
    state_158.maximum_01e = 0;
}

CharacterObject::~CharacterObject()
{
    if (copied_words_340 != 0) {
        free(copied_words_340);
        copied_words_340 = 0;
    }
    if (field_338 != 0) {
        delete reinterpret_cast<th105::SecondaryAnimationRenderRuntimeView *>(field_338);
        field_338 = 0;
    }
}
