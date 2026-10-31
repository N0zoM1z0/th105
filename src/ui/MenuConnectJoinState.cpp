// JP1.06a connect-menu middle states; complete source, still nonexact.
// Partial receiver views are never instantiated. Message names identify raw addresses.
#include "ui/MenuConnectStateRuntime.hpp"
namespace th105 {
extern "C" const char connect_join_text_6c1d34[],connect_join_text_6c1d2c[],connect_join_text_6c1d0c[],
 connect_join_text_6c1ce4[],connect_join_text_6c1cf8[],connect_join_text_6c1ccc[],connect_join_text_6c1cb0[];
struct JoinStatusView { int status(); };
class ConnectJoinStateView : public CMenuConnectStateRuntimeView {
public:
 bool update_join_state();
 void update_endpoint_digits();
 void update_endpoint_history();
 void update_endpoint_clipboard();
 void finish_transition();
 void hide_profile_message_43f8d0();
};
bool ConnectJoinStateView::update_join_state()
{
 switch(field<signed char>(9)) {
 case 0:
  switch(field<signed char>(8)) {
  case 2:update_endpoint_digits();break;
  case 3:case 4:update_endpoint_history();break;
  case 5:update_endpoint_clipboard();break;
  default:break;
  }
  return true;
 case 1:
  show_profile_message(connect_join_text_6c1d34,true);
  field<signed char>(9)=2;
  return true;
 case 2:
  field<GuideOverlay>(0xe44).visible=true;
  switch(update_profile_message()) {
  case 2:field<signed char>(8)=0;break;
  case 3:
   field<signed char>(9)=3;field<unsigned char>(0x3b8)=1;
   show_profile_result(connect_join_text_6c1d2c);finalize_message_4425d0();break;
  case 4:
   field<signed char>(9)=6;field<unsigned char>(0x3b8)=0;
   show_profile_result(connect_join_text_6c1d2c);finalize_message_4425d0();break;
  default:break;
  }
  return true;
 case 3: {
  field<GuideOverlay>(0xeec).visible=true;
  unsigned char *network=field<unsigned char *>(4);
  int state=reinterpret_cast<JoinStatusView *>(network+0x3b4)->status();
  switch(state) {
  case 9:
   switch(*reinterpret_cast<int *>(field<unsigned char *>(4)+0x3ac)) {
   case 0:field<signed char>(9)=10;show_profile_result(connect_join_text_6c1cf8);break;
   case 1:field<signed char>(9)=5;show_profile_message(connect_join_text_6c1d0c,true);break;
   default:field<signed char>(9)=10;show_profile_result(connect_join_text_6c1ce4);break;
   }
   break;
  case 6:field<signed char>(9)=10;show_profile_result(connect_join_text_6c1ce4);break;
  case 0:
   dispatch_indexed_event(0x28);g_scene_mode=9;g_next_scene_mode=5;
   finish_transition();field<signed char>(9)=-1;return true;
  default:break;
  }
  if(g_active_menu_input->hold.buttons[1]==1 || is_menu_initial_press(1,0,0,0)) {
   dispatch_indexed_event(0x29);field<signed char>(8)=0;hide_profile_message_43f8d0();
   clear_network_session();field<void *>(4)=0;
  }
  return true;
 }
 case 5:
  field<GuideOverlay>(0xe44).visible=true;
  switch(update_profile_message()) {
  case 2:case 4:
   field<signed char>(8)=0;clear_network_session();field<void *>(4)=0;break;
  case 3:
   field<signed char>(9)=6;field<unsigned char>(0x3b8)=0;
   show_profile_result(connect_join_text_6c1d2c);finalize_message_4425d0();break;
  default:break;
  }
  return true;
 case 6: {
  field<GuideOverlay>(0xeec).visible=true;
  unsigned char *network=field<unsigned char *>(4);
  int state=reinterpret_cast<JoinStatusView *>(network+0x3b4)->status();
  switch(state) {
  case 9:
   switch(*reinterpret_cast<int *>(field<unsigned char *>(4)+0x3ac)) {
   default:show_profile_result(connect_join_text_6c1ce4);field<signed char>(9)=10;break;
   case 1:show_profile_result(connect_join_text_6c1ccc);field<signed char>(9)=10;break;
   case 0:show_profile_result(connect_join_text_6c1cb0);field<signed char>(9)=10;break;
   }
   break;
  case 6:field<signed char>(9)=10;show_profile_result(connect_join_text_6c1ce4);break;
  case 0:
   dispatch_indexed_event(0x28);g_scene_mode=12;g_next_scene_mode=6;
   finish_transition();field<signed char>(9)=-1;return true;
  default:break;
  }
  if(g_active_menu_input->hold.buttons[1]==1 || is_menu_initial_press(1,0,0,0)) {
   dispatch_indexed_event(0x29);field<signed char>(8)=0;hide_profile_message_43f8d0();
   clear_network_session();field<void *>(4)=0;
  }
  return true;
 }
 case 10:
  field<GuideOverlay>(0x10e4).visible=true;
  if(update_profile_confirmation()) {
   field<signed char>(8)=0;clear_network_session();field<void *>(4)=0;
  }
  return true;
 default:return true;
 }
}
}
