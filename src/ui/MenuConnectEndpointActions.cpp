// JP1.06a endpoint action wrappers. The genuine VC8 swprintf header supplies its private count argument.
#include "ui/MenuConnectStateRuntime.hpp"
#include <wchar.h>
#include <string.h>
extern "C" __declspec(dllimport) int __cdecl wsprintfA(char *,const char *,...);
namespace th105 {
struct EndpointAssignView {void assign_bytes(const char *,unsigned);};
struct EndpointConfigView { unsigned char prefix[0x3c];unsigned short address[4];unsigned port; };
class ConnectEndpointActionView : public CMenuConnectStateRuntimeView {
public:
 void update_clipboard_action();
 void update_history_action();
 void update_digits_action();
 int edit_combined_digits();
 int select_history();
};
void ConnectEndpointActionView::update_clipboard_action()
{
 switch(update_profile_message()) {
 case 2:case 4:field<signed char>(8)=0;break;
 case 3:
  swprintf(field<wchar_t[260]>(0x448),260,L"%S",field<MenuString28>(0x42c).c_str());
  field<signed char>(9)=1;
  break;
 default:break;
 }
}
void ConnectEndpointActionView::update_history_action()
{
 field<GuideOverlay>(0x103c).visible=true;
 switch(select_history()) {
 case 2:field<signed char>(8)=0;break;
 case 1:
  swprintf(field<wchar_t[260]>(0x448),260,L"%S",field<MenuString28>(0x42c).c_str());
  field<signed char>(9)=1;
  break;
 default:break;
 }
}
void ConnectEndpointActionView::update_digits_action()
{
 field<GuideOverlay>(0xd9c).visible=true;
 switch(edit_combined_digits()) {
 case 2:field<signed char>(8)=0;break;
 case 1: {
  char text[260];
  swprintf(field<wchar_t[260]>(0x448),260,L"%d.%d.%d.%d",
   field<unsigned short>(0x420),field<unsigned short>(0x422),
   field<unsigned short>(0x424),field<unsigned short>(0x426));
  wsprintfA(text,"%d.%d.%d.%d",
   field<unsigned short>(0x420),field<unsigned short>(0x422),
   field<unsigned short>(0x424),field<unsigned short>(0x426));
  reinterpret_cast<EndpointAssignView *>(&field<MenuString28>(0x42c))->assign_bytes(text,strlen(text));
  for(int i=0;i<4;++i)
   field<EndpointConfigView *>(0xc48)->address[i]=field<unsigned short[4]>(0x420)[i];
  field<EndpointConfigView *>(0xc48)->port=field<unsigned>(0x428);
  field<signed char>(9)=1;
  break;
 }
 default:break;
 }
}
}
