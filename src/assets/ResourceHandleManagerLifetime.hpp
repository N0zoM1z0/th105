#pragma once

// Concrete pointer-resource CHandleManager lifetimes.
// Shared genuine critical-section member and original VC8 containers.
#include "network/NetworkUdpPacketPool.hpp"
namespace th105 {
struct WaveBufferResource;
struct SoundBufferResource;
struct TextureResource;
template<class T> struct ResourceHandleManagerLifetime64 {
    ResourceHandleManagerLifetime64();
    virtual ~ResourceHandleManagerLifetime64();
    std::deque<T> resources_04;
    std::vector<T *> slots_18;
    std::vector<unsigned> generations_28;
    std::list<unsigned> free_slots_38;
    unsigned generation_44;
    NetworkUdpPacketCriticalSectionView critical_48;
};
template<class T>
ResourceHandleManagerLifetime64<T>::ResourceHandleManagerLifetime64() { generation_44 = 0; }
template<class T>
ResourceHandleManagerLifetime64<T>::~ResourceHandleManagerLifetime64() {}
typedef ResourceHandleManagerLifetime64<TextureResource *> TextureManagerLayout;
typedef char ManagerSlotsOffset[offsetof(TextureManagerLayout, slots_18)==0x18?1:-1];
typedef char ManagerGenerationsOffset[offsetof(TextureManagerLayout, generations_28)==0x28?1:-1];
typedef char ManagerFreeSlotsOffset[offsetof(TextureManagerLayout, free_slots_38)==0x38?1:-1];
typedef char ManagerCriticalOffset[offsetof(TextureManagerLayout, critical_48)==0x48?1:-1];
typedef char ManagerSize[sizeof(ResourceHandleManagerLifetime64<TextureResource *>)==0x64?1:-1];
}
