// Complete wave-service load policy in the actual reader/DirectSound CIL graph.
// Normal member declarations only; native private register allocation remains unresolved.
#include "audio/BgmStreamRuntime.cpp"
#include "audio/WaveDataRuntime.cpp"
#include <cstring>
#include "audio/BgmHandleResult.hpp"
#include "audio/WaveData.hpp"
#include "network/NetworkUdpPacketPool.hpp"
#include "assets/ResourceHandleManager.hpp"
namespace th105 {
extern "C" bool __fastcall dispatch_wave_resource(WaveData *output, const char *path)
{
    if (g_bootstrap_mode) {
        unsigned length = std::strlen(path);
        char filename[260];
        strcpy_s(filename, sizeof(filename), path);
        std::memcpy(filename + length - 4, ".cv3", 4);
        return load_cv3_wave_data(output, filename);
    }
    return load_wave_data(output, path);
}

bool BgmBufferRuntime::load_wave_file(const char *path)
{
    if (resource_04 != 0) {
        resource_04->release();
        resource_04 = 0;
    }
    WaveData wave;
    if (!dispatch_wave_resource(&wave, path))
        return false;
    state_08 = wave.data_size_18;
    if (!initialize(&wave.format_00, wave.data_size_18))
        return false;
    void *audio1, *audio2;
    ULong bytes1, bytes2;
    if (resource_04->lock(0, state_08, &audio1, &bytes1, &audio2, &bytes2, 2) < 0) {
        MessageBoxA(0, wave_lock_error, wave_error_title, 0);
        return false;
    }
    memcpy(audio1, wave.data_14, state_08);
    resource_04->unlock(audio1, bytes1, audio2, bytes2);
    return true;
}
struct WaveLoadLock {
 NetworkUdpPacketCriticalSectionView *lock;
 WaveLoadLock(NetworkUdpPacketCriticalSectionView *p):lock(p){EnterCriticalSection(&lock->critical_section_04);}
 ~WaveLoadLock(){LeaveCriticalSection(&lock->critical_section_04);}
};
struct WaveLoadManager64 {
 virtual ~WaveLoadManager64();
 std::deque<BgmBufferRuntime *> resources_04;
 std::vector<BgmBufferRuntime **> slots_18;
 std::vector<unsigned> generations_28;
 std::list<unsigned> free_slots_38;
 unsigned generation_44;
 NetworkUdpPacketCriticalSectionView critical_48;
 BgmBufferRuntime **acquire(ResourceHandleToken &token);
 void release(unsigned handle);
};
BgmBufferRuntime **WaveLoadManager64::acquire(ResourceHandleToken &token) {
 WaveLoadLock lock(&critical_48);
 unsigned slot;
 if(free_slots_38.empty()) {
  slot=resources_04.size();
  if(++generation_44>0xffff)generation_44=1;
  token.slot_00=static_cast<unsigned short>(slot);
  token.generation_02=static_cast<unsigned short>(generation_44);
  resources_04.push_back(0);
  slots_18.push_back(&resources_04.back());
  generations_28.push_back(token.generation_02);
 } else {
  slot=free_slots_38.back();
  if(++generation_44>0xffff)generation_44=1;
  token.slot_00=static_cast<unsigned short>(slot);
  token.generation_02=static_cast<unsigned short>(generation_44);
  free_slots_38.pop_back();
  generations_28[slot]=token.generation_02;
 }
 return slots_18.at(slot);
}
void WaveLoadManager64::release(unsigned handle) {
 EnterCriticalSection(&critical_48.critical_section_04);
 const ResourceHandleToken &token=*reinterpret_cast<const ResourceHandleToken *>(&handle);
 unsigned short slot=token.slot_00;
 if(generations_28[slot]==token.generation_02) {
  generations_28[slot]=0;
  free_slots_38.push_back(slot);
 }
 LeaveCriticalSection(&critical_48.critical_section_04);
}
struct WaveLoadService {
 unsigned char first_manager_000[0x64];
 WaveLoadManager64 handles_064;
 unsigned char buffer_arrays_counters_0c8[0x388];
 float gain_450,gain_454;
 BgmHandleResult load_wave(const char *path);
};
typedef char PoolSize[sizeof(WaveLoadManager64)==0x64?1:-1];
typedef char GainOffset[offsetof(WaveLoadService,gain_450)==0x450?1:-1];
BgmHandleResult WaveLoadService::load_wave(const char *path) {
 BgmHandleResult result;
 BgmBufferRuntime **slot=handles_064.acquire(*reinterpret_cast<ResourceHandleToken *>(&result.value));
 *slot=new BgmBufferRuntime;
 if(!(*slot)->load_wave_file(path)) {
  delete *slot;
  handles_064.release(result.value);
  return BgmHandleResult();
 }
 float effective=gain_454*gain_450;
 long volume=effective<=bgm_minimum_gain?-10000:linear_gain_to_ds_volume(effective);
 (*slot)->set_volume(volume);
 return result;
}
}
