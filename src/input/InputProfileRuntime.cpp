#include <cstring>
#include <stddef.h>

namespace th105 {

extern int g_input_source_limit;

struct PlayerProfileBlockOwnerView {
    unsigned char reserved_00[4];
    unsigned char block_04[0x34];

    void assign_profile_block(const unsigned char *source);
};

void PlayerProfileBlockOwnerView::assign_profile_block(
    const unsigned char *source)
{
    std::memcpy(block_04, source, sizeof(block_04));
    if (static_cast<signed char>(block_04[0]) >= g_input_source_limit) {
        std::memset(block_04, 0, sizeof(block_04));
        block_04[0] = static_cast<unsigned char>(-2);
    }
}

typedef char PlayerProfileBlockOwnerView_block[
    offsetof(PlayerProfileBlockOwnerView, block_04) == 0x04 ? 1 : -1];

} // namespace th105
