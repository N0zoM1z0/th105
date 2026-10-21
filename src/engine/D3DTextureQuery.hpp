#pragma once

#include "D3DBackend.hpp"

namespace th105 {

// Direct3D9 surface description; all enum and DWORD fields are 32-bit.
struct D3DSurfaceDescription32 {
    unsigned format_00;
    unsigned resource_type_04;
    unsigned usage_08;
    unsigned pool_0c;
    unsigned multisample_type_10;
    unsigned multisample_quality_14;
    unsigned width_18;
    unsigned height_1c;
};

struct D3DResource9 : D3DUnknown {
    virtual D3DHResult __stdcall GetDevice(D3DDevice9 **) = 0; // 3
    virtual D3DHResult __stdcall SetPrivateData(const void *, const void *, unsigned, unsigned) = 0;
    virtual D3DHResult __stdcall GetPrivateData(const void *, void *, unsigned *) = 0;
    virtual D3DHResult __stdcall FreePrivateData(const void *) = 0;
    virtual unsigned __stdcall SetPriority(unsigned) = 0;
    virtual unsigned __stdcall GetPriority() = 0;
    virtual void __stdcall PreLoad() = 0;
    virtual unsigned __stdcall GetType() = 0; // 10
};

struct D3DBaseTexture9 : D3DResource9 {
    virtual unsigned __stdcall SetLOD(unsigned) = 0; // 11
    virtual unsigned __stdcall GetLOD() = 0;
    virtual unsigned __stdcall GetLevelCount() = 0;
    virtual D3DHResult __stdcall SetAutoGenFilterType(unsigned) = 0;
    virtual unsigned __stdcall GetAutoGenFilterType() = 0;
    virtual void __stdcall GenerateMipSubLevels() = 0; // 16
};

struct D3DSurface9 : D3DResource9 {
    virtual D3DHResult __stdcall GetContainer(const void *, void **) = 0; // 11
    virtual D3DHResult __stdcall GetDesc(D3DSurfaceDescription32 *) = 0; // 12
};

struct D3DTexture9 : D3DBaseTexture9 {
    virtual D3DHResult __stdcall GetLevelDesc(unsigned, D3DSurfaceDescription32 *) = 0; // 17
    virtual D3DHResult __stdcall GetSurfaceLevel(unsigned, D3DSurface9 **) = 0; // 18
};

typedef char D3DSurfaceDescription32_size[sizeof(D3DSurfaceDescription32) == 32 ? 1 : -1];
typedef char D3DSurfaceDescription32_width_offset[
    offsetof(D3DSurfaceDescription32, width_18) == 0x18 ? 1 : -1];
typedef char D3DSurfaceDescription32_height_offset[
    offsetof(D3DSurfaceDescription32, height_1c) == 0x1c ? 1 : -1];

} // namespace th105
