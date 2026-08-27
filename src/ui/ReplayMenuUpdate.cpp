#include "ReplayMenu.hpp"

namespace th105 {

extern "C" bool __cdecl is_menu_initial_press(int, int, int, int);

// These call-site views preserve the target dispatcher ABI without changing
// the independently exact helper TUs, whose source return types are byte-sized.
struct ReplayModeMemberView {
    bool update_mode_state();
};
struct ReplayBrowseMemberView {
    bool update_browse_state();
};
struct ReplayDeleteMemberView {
    bool update_delete_state();
};

bool CMenuReplay::update()
{
    guides_124[0].update();
    guides_124[1].update();
    if (!state_04) {
        guides_124[0].visible = true;
        guides_124[1].visible = false;
    } else {
        guides_124[0].visible = false;
        guides_124[1].visible = true;
    }

    if (is_menu_initial_press(1, 0, 0, 0))
        return false;

    switch (state_04) {
    case 0:
        return reinterpret_cast<ReplayModeMemberView *>(this)
            ->update_mode_state();
    case 1:
        return reinterpret_cast<ReplayBrowseMemberView *>(this)
            ->update_browse_state();
    case 2:
        return reinterpret_cast<ReplayDeleteMemberView *>(this)
            ->update_delete_state();
    default:
        return true;
    }
}

} // namespace th105
