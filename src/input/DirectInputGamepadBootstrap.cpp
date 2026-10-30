// Current JP1.06a gamepad bootstrap and enumeration source; still nonexact.
// The included input runtime supplies the actual axis callback and vector types.
#include "input/InputManager.cpp"
namespace th105 {
struct EnumDeviceInstance { unsigned size; unsigned char instance_guid[16]; };
struct EnumDirectInput;
struct EnumDirectInputVtable {
 void *unused[3];
 long (__stdcall *create_device)(EnumDirectInput *,const void *,void **,void *);
};
struct EnumDirectInput { EnumDirectInputVtable *vtable; };
struct GamepadCaps { unsigned size,flags,type,axes,buttons,povs,sample_period,min_resolution,firmware,hardware,driver; };
struct EnumGamepadDevice;
struct EnumGamepadVtable {
 void *unused_00[3];
 long (__stdcall *get_caps)(EnumGamepadDevice *,GamepadCaps *);
 long (__stdcall *enum_objects)(EnumGamepadDevice *,int (__stdcall *)(const DirectInputObjectInstanceView *,void *),void *,unsigned);
 void *unused_14[6];
 long (__stdcall *set_format)(EnumGamepadDevice *,const void *);
 void *unused_30;
 long (__stdcall *set_cooperative)(EnumGamepadDevice *,void *,unsigned);
};
struct EnumGamepadDevice { EnumGamepadVtable *vtable; };
extern const unsigned char gamepad_data_format[];
int __stdcall enumerate_gamepad_device(const EnumDeviceInstance *instance,void *)
{
 if(!g_direct_input_backend.direct_input)return 0;
 void *empty=0;
 g_direct_input_backend.gamepad_devices.push_back(empty);
 if(static_cast<EnumDirectInput *>(g_direct_input_backend.direct_input)->vtable->create_device(static_cast<EnumDirectInput *>(g_direct_input_backend.direct_input),instance->instance_guid,&g_direct_input_backend.gamepad_devices.back(),0)<0){
  g_direct_input_backend.gamepad_devices.pop_back();return 0;
 }
 EnumGamepadDevice *device=static_cast<EnumGamepadDevice *>(g_direct_input_backend.gamepad_devices.back());
 device->vtable->set_format(device,gamepad_data_format);
 device=static_cast<EnumGamepadDevice *>(g_direct_input_backend.gamepad_devices.back());
 device->vtable->set_cooperative(device,g_direct_input_backend.window_handle,5);
 GamepadCaps caps;caps.size=sizeof(caps);
 device=static_cast<EnumGamepadDevice *>(g_direct_input_backend.gamepad_devices.back());
 device->vtable->get_caps(device,&caps);
 int buttons=caps.buttons;
 g_direct_input_backend.gamepad_button_counts.push_back(buttons);
 device=static_cast<EnumGamepadDevice *>(g_direct_input_backend.gamepad_devices.back());
 device->vtable->enum_objects(device,configure_gamepad_axis,0,3);
 return 1;
}
}

extern "C" __declspec(dllimport) int __stdcall MessageBoxA(void *,const char *,const char *,unsigned);
#include <string.h>
namespace th105 {
struct DirectInputEnum8;
struct DirectInputEnumVtable {
 void *slots_00[4];
 long (__stdcall *enum_devices)(DirectInputEnum8 *,unsigned,int (__stdcall *)(const EnumDeviceInstance *,void *),void *,unsigned);
};
struct DirectInputEnum8 { DirectInputEnumVtable *vtable; };
extern const char direct_input_enum_gamepads_error[];
extern const char direct_input_error_title[];
unsigned char initialize_gamepad_devices()
{
 DirectInputEnum8 *di=static_cast<DirectInputEnum8 *>(g_direct_input_backend.direct_input);
 if(di){
  if(di->vtable->enum_devices(di,4,enumerate_gamepad_device,0,1)<0){
   MessageBoxA(g_direct_input_backend.window_handle,direct_input_enum_gamepads_error,direct_input_error_title,0);return 0;
  }
  unsigned char count=static_cast<unsigned char>(g_direct_input_backend.gamepad_devices.size());
  g_direct_input_backend.gamepad_count=count;
  RawGamepadState state;
  memset(&state,0,sizeof(state));
  g_direct_input_backend.gamepad_states.assign(count,state);
 }
 return 1;
}
}

namespace th105 {
typedef char GamepadCapsSize[sizeof(GamepadCaps)==44?1:-1];
typedef char GamepadStateSize[sizeof(RawGamepadState)==80?1:-1];
}
