#include "DirectSoundResourceLifetime.cpp"
#include "BgmHandleResult.hpp"
#include "../assets/ResourceHandleManager.hpp"
#include "../engine/CriticalSectionWrapper.hpp"
#include <string>
#include <vector>
#include <list>
#include <new>
#include "OggDataSource.hpp"
namespace th105 {
static const Guid bgm_buffer_iid={0x6825a449,0x7524,0x4d82,{0x92,0x0f,0x50,0xe3,0x6a,0xb3,0xab,0x1e}};
extern "C" const char create_sound_buffer_error[];
extern "C" const char direct_sound_error_title[];
HResult __stdcall create_secondary_buffer8(const DirectSoundBufferDescription *description,DirectSoundBuffer8 **buffer)
{
 DirectSoundBuffer *temporary=0;
 HResult result=g_direct_sound_globals.direct_sound->create_sound_buffer(description,&temporary,0);
 if(result<0) {MessageBoxA(0,create_sound_buffer_error,direct_sound_error_title,0);return result;}
 result=temporary->query_interface(&bgm_buffer_iid,reinterpret_cast<void **>(buffer));
 temporary->release();
 return result;
}
// Initializer-facing adapter over the already recovered decoder layout.
// This does not claim that the original source used a derived C++ type.
struct BgmOggDataSource : OggDataSource {
 BgmOggDataSource() { reader=0;stream_size=0; }
};
typedef char OggSize[sizeof(BgmOggDataSource)==0x1310?1:-1];
struct BgmStreamAllocationView {
 std::string name_00;
 int state_1c;
 bool active_20;
 DirectSoundResourceBaseLifetime buffer_24;
 BgmOggDataSource source_30;
 unsigned char unknown_1340[0x0c];
 unsigned scheduled_134c,transition_1350;
 int duration_1354;
 float gain_1358,start_135c,target_1360,master_1364;
 bool flag_1368;
 BgmStreamAllocationView *next_136c,*previous_1370;
 unsigned unknown_1374;
 BgmStreamAllocationView();
};
BgmStreamAllocationView::BgmStreamAllocationView()

{
 gain_1358=1.0f;
 scheduled_134c=0;duration_1354=0;transition_1350=0;
 active_20=false;flag_1368=false;state_1c=3;
 next_136c=0;previous_1370=0;
}
typedef char StreamSize[sizeof(BgmStreamAllocationView)==0x1378?1:-1];
typedef char StreamOggOffset[offsetof(BgmStreamAllocationView,source_30)==0x30?1:-1];
typedef char StreamScheduleOffset[offsetof(BgmStreamAllocationView,scheduled_134c)==0x134c?1:-1];

struct BgmAllocationLock {
 CriticalSectionWrapper *lock;
 BgmAllocationLock(CriticalSectionWrapper *p):lock(p){EnterCriticalSection(&lock->critical_section_04);}
 ~BgmAllocationLock(){LeaveCriticalSection(&lock->critical_section_04);}
};
struct BgmAllocationManager50 {
 virtual ~BgmAllocationManager50();
 std::vector<BgmStreamAllocationView *> streams_04;
 std::vector<unsigned> generations_14;
 std::list<unsigned> free_24;
 unsigned generation_30;
 CriticalSectionWrapper lock_34;
 BgmStreamAllocationView *acquire(BgmHandleResult &result);
};
typedef char ManagerSize[sizeof(BgmAllocationManager50)==0x50?1:-1];
BgmStreamAllocationView *BgmAllocationManager50::acquire(BgmHandleResult &result)
{
 BgmAllocationLock lock(&lock_34);
 ResourceHandleToken &token=*reinterpret_cast<ResourceHandleToken *>(&result.value);
 unsigned slot;
 if(free_24.empty()) {
  slot=streams_04.size();
  if(++generation_30>0xffff)generation_30=1;
  token.slot_00=static_cast<unsigned short>(slot);
  token.generation_02=static_cast<unsigned short>(generation_30);
  streams_04.push_back(new BgmStreamAllocationView);
  generations_14.push_back(token.generation_02);
 } else {
  slot=free_24.back();
  if(++generation_30>0xffff)generation_30=1;
  token.slot_00=static_cast<unsigned short>(slot);
  token.generation_02=static_cast<unsigned short>(generation_30);
  free_24.pop_back();
  generations_14[slot]=token.generation_02;
  BgmStreamAllocationView *stream=streams_04.at(slot);
  if(stream)new (stream) BgmStreamAllocationView;
 }
 return streams_04.at(slot);
}
}
