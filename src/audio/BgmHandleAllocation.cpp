namespace th105 {

struct BgmHandleResult {
    unsigned value;
};

struct BgmHandleManagerAllocateView {
    BgmHandleResult allocate_handle();
};

struct BgmPlaybackServiceView {
    unsigned char reserved_0000[0x38];
    BgmHandleManagerAllocateView manager_0038;

    BgmHandleResult allocate_handle();
};

BgmHandleResult BgmPlaybackServiceView::allocate_handle()
{
    return manager_0038.allocate_handle();
}

} // namespace th105
