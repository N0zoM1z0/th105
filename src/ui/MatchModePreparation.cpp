// JP1.06a title/result match setup; complete286-byte source remains nonexact.
#include "input/InputSelectionInitialization.cpp"
#include "ui/ScenarioMatchPreparation.cpp"
#include "battle/GameMode.hpp"
namespace th105 {
// Method-facing network prefix. No allocation/full-owner-size claim.
struct NetworkMatchPreparationView {
 unsigned char prefix[0x1f0];
 PlayerInput *primary_1f0;
 unsigned unknown_1f4;
 PlayerInput *alternate_1f8;
 unsigned char middle_1fc[0x4b8];
 void *local_input_6b4;
 void bind_result_input(void *,void *);
};
extern CNetworkBase *g_network_session;
extern unsigned char g_player2_input_storage[];
// Ordinary views here preserve the observed common input-selection suffix.
// Other accessor TUs retain their own visibility/qualification hypotheses.
extern unsigned g_session_setup_option;
extern GameMode g_game_mode;
unsigned char __cdecl start_async_engine_scene_load(int);
void __cdecl prepare_title_match_mode(int mode,int option)
{
 g_scenario_match_runtime.field_70=1;
 g_scenario_match_runtime.flag_96=1;
 g_session_setup_option=option;
 g_scenario_match_runtime.deck_index_50=0;
 g_scenario_match_runtime.flag_4c=0;
 g_scenario_match_runtime.flag_94=0;
 g_scenario_match_runtime.flag_95=0;
 g_game_mode=static_cast<GameMode>(mode);
 g_selected_inputs[0]=0;
 g_selected_input_sources[0]=-2;
 g_selected_inputs[1]=0;
 g_selected_input_sources[1]=-2;
 rebind_selected_input_43b640(0,0);
 switch(g_game_mode) {
 case 4: case 5:
  reinterpret_cast<NetworkMatchPreparationView *>(g_network_session)->bind_result_input(g_selected_inputs[0],g_player_slot_records);
  reinterpret_cast<NetworkMatchPreparationView *>(g_network_session)->local_input_6b4=g_player2_input_storage;
  g_selected_inputs[0]=reinterpret_cast<NetworkMatchPreparationView *>(g_network_session)->primary_1f0;
  g_selected_inputs[1]=reinterpret_cast<NetworkMatchPreparationView *>(g_network_session)->alternate_1f8;
  break;
 case 6:
  reinterpret_cast<NetworkMatchPreparationView *>(g_network_session)->bind_result_input(g_selected_inputs[0],g_player_slot_records);
  reinterpret_cast<NetworkMatchPreparationView *>(g_network_session)->local_input_6b4=g_player2_input_storage;
  break;
 }
 start_async_engine_scene_load(2);
}
}
