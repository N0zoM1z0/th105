#pragma once

#include <vector>
#include <stddef.h>

namespace th105 {

// Shared callback and query prefix, not the complete transport class.
struct NetworkSendRecord20 {
    unsigned char reserved_00[0x10];
    int state_10;
    unsigned int age_14;
    unsigned char reserved_18[8];
};

struct RawCriticalSection18 {
    unsigned char storage_00[0x18];
};

struct NetworkSendStateView {
    unsigned char reserved_000[0x80];
    void *callback_080;
    unsigned char reserved_084[0x04];
    RawCriticalSection18 critical_088;
    unsigned char reserved_0a0[0x68];
    std::vector<NetworkSendRecord20> records_108;
    unsigned char reserved_118[0x0c];
    RawCriticalSection18 critical_124;
    unsigned char reserved_13c[8];
    int status_144;

    void publish_callback(void *callback);
    bool check(int index);
    int status();

    // Existing peer-removal call boundary; its implementation has a separate view.
    void process(int index);
};

typedef char NetworkSendRecord20_size_must_be_0x20[
    sizeof(NetworkSendRecord20) == 0x20 ? 1 : -1];
typedef char NetworkSendState_callback_offset[
    offsetof(NetworkSendStateView, callback_080) == 0x080 ? 1 : -1];
typedef char NetworkSendState_critical_088_offset[
    offsetof(NetworkSendStateView, critical_088) == 0x088 ? 1 : -1];
typedef char NetworkSendState_records_offset[
    offsetof(NetworkSendStateView, records_108) == 0x108 ? 1 : -1];
typedef char NetworkSendState_critical_offset[
    offsetof(NetworkSendStateView, critical_124) == 0x124 ? 1 : -1];

typedef char NetworkSendState_status_offset[
    offsetof(NetworkSendStateView, status_144) == 0x144 ? 1 : -1];
typedef char NetworkSendState_prefix_size[
    sizeof(NetworkSendStateView) == 0x148 ? 1 : -1];

} // namespace th105
