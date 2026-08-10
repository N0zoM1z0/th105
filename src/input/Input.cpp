#include "Input.hpp"

namespace th105 {

MenuInput *get_combined_menu_input()
{
    return reinterpret_cast<MenuInput *>(0x006e7520);
}

PlayerInput *get_player2_input()
{
    return reinterpret_cast<PlayerInput *>(0x006e6370);
}

} // namespace th105
