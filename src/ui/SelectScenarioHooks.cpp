#include "SelectScenario.hpp"

extern "C" void __cdecl clear_menu_objects();

namespace th105 {

void CSelectScenario::unknown_scene_method()
{
}

void CSelectScenario::on_scene_exit(int)
{
    clear_menu_objects();
}

} // namespace th105
