#include "PatResourceContracts.hpp"

#include <cstring>

namespace th105 {

FrameData::FrameData()
{
    // The real temporary clears the complete object. In the derived PAT
    // construction context VC8 removes overwritten base/vptr stores.
    std::memset(this, 0, sizeof(*this));
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
    primary_collision_box_54 = 0;
    group_b_collision_boxes_58.clear();
    group_a_collision_boxes_68.clear();
    group_a_descriptors_78.clear();
}

PatRecord88::~PatRecord88()
{
    for (unsigned int index = 0; index < group_a_descriptors_78.size(); ++index) {
        if (group_a_descriptors_78[index] != 0)
            delete group_a_descriptors_78[index];
    }
    if (primary_collision_box_54 != 0)
        delete primary_collision_box_54;
    group_b_collision_boxes_58.clear();
    group_a_collision_boxes_68.clear();
    group_a_descriptors_78.clear();
}

} // namespace th105
