#include "InputCluster.hpp"
#include "InputSelection.hpp"

namespace th105 {

struct ResultInputRecord68 {
    unsigned char bytes_00[0x68];
};

struct ResultInputRecordTableView {
    unsigned unknown_00;
    ResultInputRecord68 *begin_04;
    ResultInputRecord68 *end_08;

    ResultInputRecord68 *at(unsigned index);
};

extern PlayerInput *g_selected_inputs[2];
extern signed char g_selected_input_sources[2];
extern CInputManagerCluster g_combined_menu_input;
extern ResultInputRecordTableView g_result_input_records;
extern PlayerInput g_default_input;

void __cdecl rebind_selected_input_43b640(
    int slot,
    signed char require_distinct)
{
    if (g_selected_inputs[slot] != 0)
        return;

    g_selected_input_sources[slot] =
        g_combined_menu_input.get_active_source();

    if (g_selected_input_sources[0] == g_selected_input_sources[1]) {
        if (require_distinct) {
            g_selected_input_sources[slot] = -2;
            return;
        }

        switch (slot) {
        case 0:
            g_selected_inputs[1] = 0;
            g_selected_input_sources[1] = -2;
            break;
        case 1:
            g_selected_inputs[0] = 0;
            g_selected_input_sources[0] = -2;
            break;
        }
    }

    signed char source = g_selected_input_sources[slot];
    if (source >= 0) {
        g_selected_inputs[slot] = reinterpret_cast<PlayerInput *>(
            g_result_input_records.at(source));
    } else {
        g_selected_inputs[slot] = &g_default_input;
    }
}

} // namespace th105
