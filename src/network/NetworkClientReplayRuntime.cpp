#include "../engine/CriticalSectionWrapper.hpp"

#include <deque>
#include <stddef.h>

namespace th105 {

struct NetworkReplayRecord24 {
    unsigned char reserved_000[0x08];
    unsigned int sequence_008;
    unsigned char tag_00c;
    unsigned char reserved_00d[3];
    std::deque<short> values_010;
};

struct CNetworkClientReplayView {
    void consume_sequence(const NetworkReplayRecord24 *record);

    unsigned char reserved_000[0x48];
    CriticalSectionWrapper critical_048;
    unsigned char reserved_064[0x14];
    unsigned char tag_078;
    unsigned char reserved_079[0x1f];
    unsigned int sequence_098;
    unsigned char reserved_09c[0x04];
    std::deque<short> queue_0a0;
    unsigned char reserved_0b4[0x28];
    CriticalSectionWrapper critical_0dc;
    unsigned char reserved_0f8[0x68];
    std::deque<short> queue_160;
    unsigned char reserved_174[0x68];
    std::deque<short> queue_1dc;
};

void CNetworkClientReplayView::consume_sequence(
    const NetworkReplayRecord24 *record)
{
    critical_048.enter();
    const unsigned int incoming = record->sequence_008;
    const unsigned int previous = sequence_098;
    if (incoming > previous && record->tag_00c == tag_078) {
        unsigned int remaining = 2 * (incoming - previous);
        if (remaining <= record->values_010.size()) {
            sequence_098 = incoming;
            if (remaining != 0) {
                do {
                    critical_0dc.enter();
                    --remaining;
                    int value = static_cast<unsigned short>(
                        record->values_010.at(remaining));
                    queue_1dc.push_back(static_cast<short>(value));
                    --remaining;
                    value = static_cast<unsigned short>(
                        record->values_010.at(remaining));
                    queue_160.push_back(static_cast<short>(value));
                    critical_0dc.leave();
                } while (remaining != 0);
            }
        }
    }
    critical_048.leave();
}

typedef char NetworkReplayRecord24_size_must_be_0x24[
    sizeof(NetworkReplayRecord24) == 0x24 ? 1 : -1];
typedef char CNetworkClientReplayView_queue_160_offset_must_be_0x160[
    offsetof(CNetworkClientReplayView, queue_160) == 0x160 ? 1 : -1];
typedef char CNetworkClientReplayView_queue_1dc_offset_must_be_0x1dc[
    offsetof(CNetworkClientReplayView, queue_1dc) == 0x1dc ? 1 : -1];

} // namespace th105
