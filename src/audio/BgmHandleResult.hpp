#pragma once

namespace th105 {

// The service initializes the returned token before the manager writes its
// slot/generation words. This is a value result, not the manager's pointer return.
struct BgmHandleResult {
    BgmHandleResult() : value(0) {}
    unsigned value;
};

} // namespace th105
