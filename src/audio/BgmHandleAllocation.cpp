#include "BgmHandleResult.hpp"

namespace th105 {
struct BgmHandleManagerAllocateView {
    // Native4040D0 returns the stream pointer and writes the explicit token.
    // Its private EDI receiver is not fabricated as a source calling convention.
    void *acquire(BgmHandleResult &token);
};
struct BgmPlaybackServiceView {
    unsigned char prefix[0x38];
    BgmHandleManagerAllocateView manager;
    BgmHandleResult allocate_handle();
};
BgmHandleResult BgmPlaybackServiceView::allocate_handle()
{
    BgmHandleResult result;
    manager.acquire(result);
    return result;
}
}
