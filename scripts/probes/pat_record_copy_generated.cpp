#include "../../src/battle/PatResourceContracts.hpp"

#include <new>

namespace th105 {

void probe_pat_record_copy(void *destination, PatRecord88 const &source)
{
    new (destination) PatRecord88(source);
}

} // namespace th105
