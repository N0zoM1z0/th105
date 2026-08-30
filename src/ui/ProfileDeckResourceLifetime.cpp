#include "../battle/SpellData.hpp"

#include <deque>
#include <map>

namespace th105 {

struct ProfileDeckResourceGroupNative20 {
    std::deque<unsigned> handles_00;
    std::map<int, SpellRecordView> tree_14;

    ProfileDeckResourceGroupNative20();
    ~ProfileDeckResourceGroupNative20();
};

ProfileDeckResourceGroupNative20::ProfileDeckResourceGroupNative20()
{
}

ProfileDeckResourceGroupNative20::~ProfileDeckResourceGroupNative20()
{
}

typedef char ProfileDeckResourceGroupNative20_size[
    sizeof(ProfileDeckResourceGroupNative20) == 0x20 ? 1 : -1];

} // namespace th105
