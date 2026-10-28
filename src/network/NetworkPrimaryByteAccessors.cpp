#include <stddef.h>

namespace th105 {

// Pointer-only field prefixes. RTTI fixes the owning primary vtables, not
// unique source class names or a complete allocation declaration.
struct NetworkServerByteView {
    unsigned char reserved_000[0x78];
    signed char state_078;
    unsigned char reserved_079[7];
    signed char byte_080;

    void set_state(signed char value);
    int state() const;
    signed char read_byte_80() const;
};

struct NetworkClientByteView {
    unsigned char reserved_000[0x6c];
    signed char state_06c;
    unsigned char reserved_06d[0x14];
    signed char byte_081;

    void set_state(signed char value);
    int state() const;
    signed char read_byte_81() const;
};

void NetworkServerByteView::set_state(signed char value)
{
    state_078 = value;
}

int NetworkServerByteView::state() const
{
    return state_078;
}

signed char NetworkServerByteView::read_byte_80() const
{
    return byte_080;
}

void NetworkClientByteView::set_state(signed char value)
{
    state_06c = value;
}

int NetworkClientByteView::state() const
{
    return state_06c;
}

signed char NetworkClientByteView::read_byte_81() const
{
    return byte_081;
}

typedef char ServerStateOffset[offsetof(NetworkServerByteView, state_078) == 0x78 ? 1 : -1];
typedef char ServerByteOffset[offsetof(NetworkServerByteView, byte_080) == 0x80 ? 1 : -1];
typedef char ClientStateOffset[offsetof(NetworkClientByteView, state_06c) == 0x6c ? 1 : -1];
typedef char ClientByteOffset[offsetof(NetworkClientByteView, byte_081) == 0x81 ? 1 : -1];

} // namespace th105
