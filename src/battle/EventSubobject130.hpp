#pragma once

namespace th105 {

// Narrow event-helper subobject contract.  Current roster callers establish
// this subobject at Fighter +0x130; the helper bodies may legitimately leave
// the receiver unused while preserving the member-function ABI.
struct EventSubobject130 {
    unsigned char storage_00[0x0c];

    int trigger_global_effect(int value);
    void trigger_secondary_event_effect(int event_id);
    void *set_global_pair(float first, float second);
};

} // namespace th105
