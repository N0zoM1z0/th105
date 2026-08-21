#include "PatResourceContracts.hpp"

#include <cstring>

namespace th105 {

FrameData::FrameData()
{
    std::memset(&raw_04, 0, 0x14);
    tag_14 = 0;
    optional_mode_payload_18 = 0;
}

FrameData::~FrameData()
{
    if (optional_mode_payload_18 != 0)
        delete optional_mode_payload_18;
}

PatRecord88::PatRecord88()
{
    // This destructive zeroing looks unusual, but it is the current target's
    // observed constructor body after base/member construction.
    std::memset(this, 0, sizeof(*this));
    optional_raw16_54 = 0;
    raw16_vector_58.clear();
    raw16_vector_68.clear();
    raw16_pointer_vector_78.clear();
}

PatRecord88::~PatRecord88()
{
    for (unsigned int index = 0; index < raw16_pointer_vector_78.size(); ++index) {
        if (raw16_pointer_vector_78[index] != 0)
            delete raw16_pointer_vector_78[index];
    }
    if (optional_raw16_54 != 0)
        delete optional_raw16_54;
    raw16_vector_58.clear();
    raw16_vector_68.clear();
    raw16_pointer_vector_78.clear();
}

} // namespace th105
