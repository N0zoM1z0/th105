#include "DirectSound.hpp"
#include <string.h>

namespace th105 {

struct DirectSound3DBuffer : UnknownInterface {
    virtual HResult __stdcall get_all_parameters(void *) = 0;
    virtual HResult __stdcall get_cone_angles(ULong *, ULong *) = 0;
    virtual HResult __stdcall get_cone_orientation(void *) = 0;
    virtual HResult __stdcall get_cone_outside_volume(long *) = 0;
    virtual HResult __stdcall get_max_distance(float *) = 0;
    virtual HResult __stdcall get_min_distance(float *) = 0;
    virtual HResult __stdcall get_mode(ULong *) = 0;
    virtual HResult __stdcall get_position(void *) = 0;
    virtual HResult __stdcall get_velocity(void *) = 0;
    virtual HResult __stdcall set_all_parameters(const void *, ULong) = 0;
    virtual HResult __stdcall set_cone_angles(ULong, ULong, ULong) = 0;
    virtual HResult __stdcall set_cone_orientation(float, float, float, ULong) = 0;
    virtual HResult __stdcall set_cone_outside_volume(long, ULong) = 0;
    virtual HResult __stdcall set_max_distance(float, ULong) = 0;
    virtual HResult __stdcall set_min_distance(float distance, ULong apply) = 0;
};

struct DirectSoundBufferDescription36 {
    ULong size;
    ULong flags;
    ULong buffer_bytes;
    ULong reserved;
    const void *format;
    Guid algorithm;
};

typedef char DirectSoundBufferDescription36_size[
    sizeof(DirectSoundBufferDescription36) == 36 ? 1 : -1];

extern "C" __declspec(dllimport) int __stdcall MessageBoxA(
    void *, const char *, const char *, unsigned);
extern "C" const char direct_sound_buffer8_acquire_error[];
extern "C" const char direct_sound_3d_buffer8_acquire_error[];
extern const Guid iid_direct_sound_3d_buffer;

class DirectSoundResourceBaseLifetime {
public:
    DirectSoundResourceBaseLifetime();
    virtual bool initialize(const void *source, unsigned size);
    virtual ~DirectSoundResourceBaseLifetime();

protected:
    DirectSoundBuffer8 *resource_04;
    unsigned state_08;
};

class DirectSoundResourceLifetime : public DirectSoundResourceBaseLifetime {
public:
    DirectSoundResourceLifetime();
    virtual bool initialize(const void *source, unsigned size);
    virtual ~DirectSoundResourceLifetime();

private:
    DirectSound3DBuffer *resource_0c;
};

bool DirectSoundResourceBaseLifetime::initialize(
    const void *format, unsigned buffer_bytes)
{
    DirectSoundBufferDescription36 description;
    memset(&description, 0, sizeof(description));
    description.size = sizeof(description);
    description.flags = 0x18088;
    description.buffer_bytes = buffer_bytes;
    description.format = format;
    if (create_secondary_buffer8(
            reinterpret_cast<const DirectSoundBufferDescription *>(&description),
            &resource_04) < 0) {
        MessageBoxA(0, direct_sound_buffer8_acquire_error,
                    "DSound-Error", 0);
        return false;
    }
    return true;
}

bool DirectSoundResourceLifetime::initialize(
    const void *format, unsigned buffer_bytes)
{
    DirectSoundBufferDescription36 description;
    memset(&description, 0, sizeof(description));
    description.size = sizeof(description);
    description.flags = 0x58090;
    description.buffer_bytes = buffer_bytes;
    description.format = format;
    if (create_secondary_buffer8(
            reinterpret_cast<const DirectSoundBufferDescription *>(&description),
            &resource_04) < 0) {
        MessageBoxA(0, direct_sound_buffer8_acquire_error,
                    "DSound-Error", 0);
        return false;
    }
    if (resource_04->query_interface(
            &iid_direct_sound_3d_buffer,
            reinterpret_cast<void **>(&resource_0c)) < 0) {
        MessageBoxA(0, direct_sound_3d_buffer8_acquire_error,
                    "DSound-Error", 0);
        return false;
    }
    resource_0c->set_min_distance(3.0f, 1);
    return true;
}

DirectSoundResourceBaseLifetime::DirectSoundResourceBaseLifetime()
{
    resource_04 = 0;
    state_08 = 0;
}

DirectSoundResourceBaseLifetime::~DirectSoundResourceBaseLifetime()
{
    if (resource_04 != 0) {
        resource_04->release();
        resource_04 = 0;
    }
}

DirectSoundResourceLifetime::DirectSoundResourceLifetime()
{
    resource_0c = 0;
}

DirectSoundResourceLifetime::~DirectSoundResourceLifetime()
{
    if (resource_0c != 0) {
        resource_0c->release();
        resource_0c = 0;
    }
    if (resource_04 != 0) {
        resource_04->release();
        resource_04 = 0;
    }
}

typedef char DirectSoundResourceBaseLifetime_size[
    sizeof(DirectSoundResourceBaseLifetime) == 0x0c ? 1 : -1];
typedef char DirectSoundResourceLifetime_size[
    sizeof(DirectSoundResourceLifetime) == 0x10 ? 1 : -1];

} // namespace th105
