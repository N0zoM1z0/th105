#include <string.h>

namespace th105 {

struct InputBindingsCtorView {
    signed char source_id;
    unsigned char reserved_01[3];
    int up;
    int down;
    int left;
    int right;
    int buttons[8];
};

struct HoldCountersCtorView {
    int horizontal;
    int vertical;
    int buttons[8];
};

class CInputManager {
public:
    CInputManager();
    virtual ~CInputManager();
    virtual void update_player_input_counters_from_raw();

    InputBindingsCtorView bindings;
    HoldCountersCtorView hold;
};

CInputManager::CInputManager()
    : hold()
{
    memset(&bindings, 0, sizeof(bindings));
}

typedef char CInputManager_ctor_size_must_be_0x60[
    sizeof(CInputManager) == 0x60 ? 1 : -1];

} // namespace th105
