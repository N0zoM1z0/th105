namespace th105 {
struct BattleEffectBootstrapView {
    bool initialize(const void *, unsigned);
    void shutdown();
};
extern BattleEffectBootstrapView g_battle_effect;
extern const unsigned char battle_effect_program[];
void __cdecl initialize_scene_auxiliary_6654a0()
{
    g_battle_effect.initialize(battle_effect_program,0xac8);
}
void __cdecl shutdown_scene_auxiliary_6654c0()
{
    g_battle_effect.shutdown();
}
}
