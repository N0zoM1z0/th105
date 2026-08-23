namespace th105 {

struct ConfigResetView {
    void reset(void *source, int zero, int index);
    void finalize();
};
struct OpaqueConfigSource {
    unsigned char value;
};

extern ConfigResetView g_game_config_reset;
extern ConfigResetView g_game_config_secondary;
extern OpaqueConfigSource g_config_source_first;
extern OpaqueConfigSource g_config_source_second;

void close_config_menu()
{
    g_game_config_reset.reset(&g_config_source_first, 0, -1);
    g_game_config_secondary.reset(&g_config_source_second, 0, -1);
    g_game_config_reset.finalize();
}

} // namespace th105
