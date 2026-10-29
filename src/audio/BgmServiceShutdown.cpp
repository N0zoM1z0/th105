#include "AudioSchedulerRuntime.hpp"
#include <stddef.h>
namespace th105 {
extern "C" __declspec(dllimport) int __stdcall SetEvent(void *);
extern "C" __declspec(dllimport) int __stdcall CloseHandle(void *);
struct BgmShutdownHandleManager50 {
 unsigned char unknown_00[0x50];
 void release(unsigned handle);
};
struct BgmShutdownView {
 BattleThreadHandle workers_00[2];
 void *events_10[2];
 bool running_18;
 unsigned char unknown_19[0x1f];
 BgmShutdownHandleManager50 handles_38;
 std::list<unsigned> handles_88;
 std::list<unsigned> handles_94;
 std::list<unsigned> handles_a0;
 void shutdown();
};
typedef char BgmShutdownListOffset[offsetof(BgmShutdownView,handles_88)==0x88?1:-1];
void BgmShutdownView::shutdown()
{
 running_18=false;
 if(events_10[1]) SetEvent(events_10[1]);
 workers_00[0].wait_for_exit();
 workers_00[1].wait_for_exit();
 if(events_10[0]) {CloseHandle(events_10[0]);events_10[0]=0;}
 if(events_10[1]) {CloseHandle(events_10[1]);events_10[1]=0;}
 for(std::list<unsigned>::iterator it=handles_88.begin();it!=handles_88.end();++it) handles_38.release(*it);
 for(std::list<unsigned>::iterator it=handles_94.begin();it!=handles_94.end();++it) handles_38.release(*it);
 for(std::list<unsigned>::iterator it=handles_a0.begin();it!=handles_a0.end();++it) handles_38.release(*it);
 handles_88.clear();
 handles_94.clear();
 handles_a0.clear();
}
}
