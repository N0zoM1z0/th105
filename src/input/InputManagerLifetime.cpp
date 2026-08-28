namespace th105 {

struct InputBindingsLifetime {
    signed char source_id;
    unsigned char reserved_01[3];
    int keys[12];
};

struct HoldCountersLifetime {
    int values[10];
};

class CInputManagerLifetimeView {
public:
    virtual ~CInputManagerLifetimeView();
    virtual void update_player_input_counters_from_raw();

    InputBindingsLifetime bindings;
    HoldCountersLifetime hold;
};

CInputManagerLifetimeView::~CInputManagerLifetimeView()
{
}

typedef char CInputManagerLifetimeView_size_must_be_0x60[
    sizeof(CInputManagerLifetimeView) == 0x60 ? 1 : -1];

} // namespace th105
