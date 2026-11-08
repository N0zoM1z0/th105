#include "NetworkBaseMembers.hpp"

namespace th105 {

NetworkInputEndpoint7C::NetworkInputEndpoint7C()
{
    input_000.use_injected_input = true;
    input_000.injected_mask = 0;
    queue_068.clear();
}

NetworkInputEndpoint7C::~NetworkInputEndpoint7C()
{
}

} // namespace th105
