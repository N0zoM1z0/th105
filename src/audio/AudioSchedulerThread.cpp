#include "AudioSchedulerRuntime.hpp"
// Native arithmetic rounds drift and fractional accumulation to single precision.
// Retain strict rounding without exception-sensitive instruction scheduling.
#pragma float_control(except, off, push)
namespace th105 {
extern "C" __declspec(dllimport) void *__stdcall CreateEventA(void *,int,int,const char *);
extern "C" __declspec(dllimport) int __stdcall CloseHandle(void *);
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();
extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(void *,unsigned long);
extern "C" __declspec(dllimport) int __stdcall SetEvent(void *);
#define GREATER(a,b) (((a)>(b))?(a):(b))
#define LESSER(a,b) (((a)>(b))?(b):(a))
unsigned long __stdcall AudioScheduler_thread_main(void *)
{
 void *event=CreateEventA(0,0,0,0);
 float correction=0.0f;
 float previous=0.0f;
 float fraction=0.0f;
 int limit=1000-g_audio_scheduler_state.tick_interval_24*60;
 int count=0;
 bool adjusted=false;
 unsigned long start=timeGetTime();
 while(g_audio_scheduler_state.running_38) {
  int elapsed=(int)(timeGetTime()-start-1000);
  if(elapsed>=0) {
   if(adjusted) adjusted=false;
   else {
    previous=LESSER(GREATER(previous,(float)(count-g_audio_scheduler_state.tick_interval_24*60.0f-elapsed)),limit);
    correction=previous/60.0f;
   }
   count=0;
   start+=1000;
  }
  fraction+=correction;
  count+=g_audio_scheduler_state.tick_interval_24;
  int extra=0;
  if(fraction>=1.0f) {fraction-=1.0f;extra=1;count+=extra;}
  if(g_audio_scheduler_state.wait_adjustment_28) {
   WaitForSingleObject(event,g_audio_scheduler_state.wait_adjustment_28+g_audio_scheduler_state.tick_interval_24+extra);
   g_audio_scheduler_state.wait_adjustment_28=0;
   adjusted=true;
  } else WaitForSingleObject(event,g_audio_scheduler_state.tick_interval_24+extra);
  EnterCriticalSection(&g_audio_scheduler_state.critical_section_00.critical_section_04);
  std::list<void *>::iterator it=g_audio_scheduler_state.listeners_2c.begin();
  std::list<void *>::iterator end=g_audio_scheduler_state.listeners_2c.end();
  for(;it!=end;++it) SetEvent(*it);
  LeaveCriticalSection(&g_audio_scheduler_state.critical_section_00.critical_section_04);
 }
 CloseHandle(event);
 return 0;
}
}

#pragma float_control(pop)
