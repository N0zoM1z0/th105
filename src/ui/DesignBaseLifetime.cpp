#include "DesignBaseLifetime.hpp"

namespace th105 {

CDesignBase::CDesignBase()
{
}

// Force the implicit virtual destructor/scalar wrapper COMDATs to materialize
// in the same reproducible VC8 probe object as the constructor.
void destroy_design_base_for_lifetime_probe(CDesignBase *value)
{
    delete value;
}

} // namespace th105
