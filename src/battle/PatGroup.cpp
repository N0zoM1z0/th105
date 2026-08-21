#include "PatResourceContracts.hpp"

namespace th105 {

PatGroup::PatGroup()
{
    records_00.clear();
    field_10 = 0;
    field_12 = 0;
}

PatGroup::~PatGroup()
{
    records_00.clear();
}

} // namespace th105
