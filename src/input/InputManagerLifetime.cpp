// RTTI identifies the global CInputManager base type; its empty destructor
// contains only compiler-managed virtual-table restoration.
struct InputBindingsLifetime {
    signed char source_id;
    unsigned char reserved_01[3];
    int keys[12];
};

struct HoldCountersLifetime {
    int values[10];
};

class CInputManager {
public:
    virtual ~CInputManager();
    virtual void update_player_input_counters_from_raw();

    InputBindingsLifetime bindings;
    HoldCountersLifetime hold;
};

CInputManager::~CInputManager()
{
}

typedef char CInputManager_size_must_be_0x60[
    sizeof(CInputManager) == 0x60 ? 1 : -1];
