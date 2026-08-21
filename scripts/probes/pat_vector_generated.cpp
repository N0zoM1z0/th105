#include "../../src/battle/PatResourceContracts.hpp"
#include <memory>

namespace th105 {

void probe_pat_vector_copy(
    void *destination,
    std::vector<PatRecord88> const &source)
{
    new (destination) std::vector<PatRecord88>(source);
}

void probe_pat_vector_insert(
    std::vector<PatRecord88> &records,
    unsigned count,
    PatRecord88 const &value)
{
    records.insert(records.begin(), count, value);
}

void probe_pat_vector_assign(
    std::vector<PatRecord88> &records,
    unsigned count,
    PatRecord88 const &value)
{
    records.assign(count, value);
}

void probe_pat_group_construct(void *destination, PatGroup const &source)
{
    std::_Construct(static_cast<PatGroup *>(destination), source);
}

} // namespace th105
