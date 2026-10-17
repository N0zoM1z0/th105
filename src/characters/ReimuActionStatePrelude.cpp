#include "ReimuActionStateStaging.hpp"

namespace th105 {

bool ReimuActionStatePreludeView::run_checked_prelude()
{
#include "ReimuActionStatePreludeBody.hpp"
    return false;
}

} // namespace th105
