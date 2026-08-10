#include "BattleSetup.hpp"

namespace th105 {

int get_battle_setup_task()
{
    return *reinterpret_cast<volatile int *>(0x006e62e8);
}

} // namespace th105
