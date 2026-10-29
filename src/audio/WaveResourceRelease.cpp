// JP1.06a wave-resource release with genuine shared handle recycling context.
#include "assets/ResourceHandleLookupRuntime.cpp"
#include <deque>
#include <list>
#include <vector>
namespace th105 {
struct WaveSoundResource {
 virtual bool initialize(const void *, unsigned);
 virtual ~WaveSoundResource();
};
class WaveSoundPool64 {
public:
 virtual ~WaveSoundPool64();
 std::deque<WaveSoundResource *> resources_04;
 std::vector<WaveSoundResource **> slots_18;
 std::vector<unsigned> generations_28;
 std::list<unsigned> free_slots_38;
 unsigned generation_44;
 CriticalSectionWrapper critical_48;
 void release(unsigned packed_token);
};
typedef char WavePoolSize[sizeof(WaveSoundPool64)==0x64 ? 1 : -1];
// Pointer-only owner view; its preceding state is not accessed or constructed.
struct WaveResourceReleaseView {
 unsigned char prefix_00[0x64];
 WaveSoundPool64 pool_64;
 unsigned char release_handle(unsigned token);
};
void WaveSoundPool64::release(unsigned packed_token)
{
 const ResourceHandleToken &token=*reinterpret_cast<const ResourceHandleToken *>(&packed_token);
 EnterCriticalSection(&critical_48.critical_section_04);
 if(generations_28[token.slot_00]==token.generation_02) {
  generations_28[token.slot_00]=0;
  free_slots_38.push_back(token.slot_00);
 }
 LeaveCriticalSection(&critical_48.critical_section_04);
}
unsigned char WaveResourceReleaseView::release_handle(unsigned token)
{
 if(!token) return false;
 CHandleManagerLookupView *lookup=reinterpret_cast<CHandleManagerLookupView *>(&pool_64);
 if(lookup->lookup_token_417800(token)) {
  delete static_cast<WaveSoundResource *>(*lookup->lookup_token_417800(token));
  pool_64.release(token);
  return true;
 }
 return false;
}
}
