#include "Input.hpp"

namespace th105 {

extern unsigned char g_combined_menu_input_storage[];
extern unsigned char g_player2_input_storage[];

MenuInput *get_combined_menu_input()
{
    return reinterpret_cast<MenuInput *>(g_combined_menu_input_storage);
}

PlayerInput *get_player2_input()
{
    return reinterpret_cast<PlayerInput *>(g_player2_input_storage);
}

} // namespace th105
