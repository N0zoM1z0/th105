#include <stddef.h>
#include <string>

namespace th105 {

struct NetworkReplayNamesView {
    void *vtable_00;
    char player0_name_04[0x20];
    char player1_name_24[0x20];
};

struct ReplayInputStorageView {
    void build_replay_filename_42a560(
        char *output,
        const char *player0_name,
        const char *player1_name);
    void save_replay_428d90(const char *path);
};

struct PlayerSlotReplayNameView {
    unsigned char prefix_000[0xb4];
    std::string replay_name_b4;
};

typedef char ContinueReplay_string_size_must_be_0x1c[
    sizeof(std::string) == 0x1c ? 1 : -1];
typedef char ContinueReplay_name_offset_must_be_0xb4[
    offsetof(PlayerSlotReplayNameView, replay_name_b4) == 0xb4 ? 1 : -1];

// This caller uses the storage directly; unlike the accessor TU, the target
// emits a memory CMP and therefore does not see this object through volatile.
extern unsigned g_session_setup_option;
extern NetworkReplayNamesView *g_network_session;
extern unsigned char g_player2_input_storage[];
extern unsigned char g_player_slot_records[];

void refresh_continue_network_state()
{
    if (g_session_setup_option != 1)
        return;

    char path[260];
    ReplayInputStorageView *replay =
        reinterpret_cast<ReplayInputStorageView *>(g_player2_input_storage);
    if (g_network_session != 0) {
        replay->build_replay_filename_42a560(
            path,
            g_network_session->player0_name_04,
            g_network_session->player1_name_24);
    } else {
        PlayerSlotReplayNameView *player0 =
            reinterpret_cast<PlayerSlotReplayNameView *>(g_player_slot_records);
        PlayerSlotReplayNameView *player1 =
            reinterpret_cast<PlayerSlotReplayNameView *>(
                g_player_slot_records + 0x33c);
        replay->build_replay_filename_42a560(
            path,
            player0->replay_name_b4.c_str(),
            player1->replay_name_b4.c_str());
    }
    replay->save_replay_428d90(path);
}

} // namespace th105
