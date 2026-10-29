// JP1.06a replay consumer. Zero-extended input words enter an unsigned16-bit
// destination deque; the existing signed packet-word view is preserved.
#include "engine/CriticalSectionWrapper.hpp"
#include <deque>
#include <stddef.h>
namespace th105 {
struct ReplayInputPacketView {
 unsigned char prefix_00[8];
 unsigned sequence_08,metadata_0c;
 unsigned char tag_10;
 unsigned char padding_11[3];
 std::deque<short> values_14;
};
struct ReplayInputSinkView { void append(unsigned short); };
struct ReplayDequeAccessView { short &at(unsigned); };
class ReplayConsumerView {
public:
 virtual void slot00();virtual void slot04();virtual void slot08();
 virtual void slot0c();virtual void slot10();virtual void slot14();
 virtual void slot18();virtual void slot1c();virtual void slot20();
 virtual void slot24();virtual void slot28();virtual void reject(int);
 unsigned char gap_004[0xd8];
 CriticalSectionWrapper lock_0dc;
 unsigned char gap_0f8[0x5bc];
 ReplayInputSinkView *sink_6b4;
 unsigned char tag_6b8;
 unsigned char gap_6b9[3];
 unsigned sequence_6bc,metadata_6c0,unused_6c4;
 std::deque<unsigned short> values_6c8;
 void consume(ReplayInputPacketView *packet);
};
typedef char ConsumerSize[sizeof(ReplayConsumerView)==0x6dc?1:-1];
typedef char ConsumerLock[offsetof(ReplayConsumerView,lock_0dc)==0xdc?1:-1];
typedef char ConsumerSink[offsetof(ReplayConsumerView,sink_6b4)==0x6b4?1:-1];
void ReplayConsumerView::consume(ReplayInputPacketView *packet)
{
 if(packet->tag_10!=tag_6b8) {
  reject(3);
  return;
 }
 unsigned count=packet->sequence_08-sequence_6bc;
 metadata_6c0=packet->metadata_0c;
 if(count<=packet->values_14.size()) {
  sequence_6bc=packet->sequence_08;
  while(count) {
   --count;
   lock_0dc.enter();
   unsigned short value=static_cast<unsigned short>(
    reinterpret_cast<ReplayDequeAccessView *>(&packet->values_14)->at(count));
   values_6c8.push_back(value);
   lock_0dc.leave();
   sink_6b4->append(value);
  }
 }
}
}
