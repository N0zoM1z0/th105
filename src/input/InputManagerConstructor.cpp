#include "InputManager.hpp"
#include <string.h>

namespace th105 {

CInputManager::CInputManager()
    : hold()
{
    memset(&bindings, 0, sizeof(bindings));
}

typedef char CInputManager_ctor_size_must_be_0x60[
    sizeof(CInputManager) == 0x60 ? 1 : -1];

} // namespace th105
