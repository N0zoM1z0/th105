#include <deque>

#include "characters/YoumuObjectRecords.hpp"

// Force the VC8 checked-deque specializations used by Youmu's owner-record
// adapter. YoumuObjectRecord is 44 bytes including its natural tail padding,
// so VC8 selects the one-element-per-block deque layout seen in the target.
template class std::deque<th105::YoumuObjectRecord>;
