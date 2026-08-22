#include "BattleScenes.hpp"

namespace th105 {

unsigned char __cdecl start_async_engine_scene_load(int scene);

CBattle::CBattle()
{
}

CBattle::~CBattle()
{
    start_async_engine_scene_load(5);
}

} // namespace th105
