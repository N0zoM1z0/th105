#include "SpellData.hpp"

namespace th105 {

extern "C" void __cdecl _invalid_parameter_noinfo(void);

short *ShortDeque8::front_checked()
{
    unsigned absolute = head_0c;
    if (absolute > live_count_10 + absolute) {
        _invalid_parameter_noinfo();
    }

    const unsigned block_index = absolute >> 3;
    const unsigned within_block = absolute & 7;
    if (absolute >= live_count_10 + head_0c) {
        _invalid_parameter_noinfo();
    }

    unsigned wrapped_block = block_index;
    if (block_capacity_08 <= wrapped_block) {
        wrapped_block -= block_capacity_08;
    }
    return blocks_04[wrapped_block] + within_block;
}

} // namespace th105
