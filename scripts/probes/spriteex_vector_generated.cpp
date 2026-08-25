#include "../../src/battle/EffectSprite.hpp"
#include <vector>

namespace th105 {

void probe_spriteex_vector_reserve(std::vector<CSpriteEx> &items, unsigned count)
{
    items.reserve(count);
}

void probe_spriteex_vector_clear(std::vector<CSpriteEx> &items)
{
    items.clear();
}

void probe_spriteex_vector_resize(std::vector<CSpriteEx> &items, unsigned count)
{
    items.resize(count);
}

} // namespace th105
