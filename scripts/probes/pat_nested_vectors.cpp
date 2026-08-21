#include "../../src/battle/PatResourceContracts.hpp"

namespace th105 {

void probe_pat_raw16_clear(std::vector<PatRaw16> &values)
{
    values.clear();
}

void probe_pat_raw16_pointer_clear(std::vector<PatRaw16 *> &values)
{
    values.clear();
}

void probe_pat_raw16_destroy(std::vector<PatRaw16> *values)
{
    values->~vector();
}

void probe_pat_raw16_pointer_destroy(std::vector<PatRaw16 *> *values)
{
    values->~vector();
}

void probe_pat_raw16_assign_operator(
    std::vector<PatRaw16> &destination,
    std::vector<PatRaw16> const &source)
{
    destination = source;
}

} // namespace th105
