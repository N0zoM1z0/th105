#include "InputCluster.hpp"

namespace th105 {

extern unsigned char g_combined_menu_input_storage[];

signed char get_active_input_source_43b050()
{
    return reinterpret_cast<CInputManagerCluster *>(
        g_combined_menu_input_storage)->get_active_source();
}

} // namespace th105
