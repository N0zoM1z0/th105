#include <map>
#include <string.h>
#include <utility>

namespace th105 {

extern "C" __declspec(dllimport) int __cdecl wsprintfA(
    char *destination,
    const char *format,
    ...);

struct FighterPhaseContextBootstrap {
    unsigned char storage_000[0x54];
    FighterPhaseContextBootstrap();
};

struct BattleObjectManagerBootstrap {
    unsigned char storage_000[0x118];
    BattleObjectManagerBootstrap();
};

struct EventEffectStateBootstrap {
    unsigned char storage_000[0xe8];
    EventEffectStateBootstrap();
    void initialize_effect_runtime();
};

struct EffectSinkBootstrap {
    virtual ~EffectSinkBootstrap();
    virtual void load_effect_resource(const char *path, unsigned mode);
    unsigned char storage_004[0x90];
    EffectSinkBootstrap();
};

struct BattleInputGateAllocationView {
    unsigned char storage_000[0x30];
};

typedef std::map<unsigned int, unsigned short> InfoEffectLookupMap;

extern FighterPhaseContextBootstrap *g_fighter_phase_context_bootstrap;
extern BattleObjectManagerBootstrap *g_battle_object_manager_bootstrap;
extern EventEffectStateBootstrap *g_event_effect_state_bootstrap;
extern EffectSinkBootstrap *g_effect_sink_bootstrap;
extern BattleInputGateAllocationView *g_battle_input_gate_bootstrap;
extern InfoEffectLookupMap g_info_effect_lookup_map;

unsigned __cdecl case_insensitive_crc32(
    const unsigned char *bytes,
    int length);

void __cdecl initialize_shared_battle_runtime()
{
    g_fighter_phase_context_bootstrap = new FighterPhaseContextBootstrap;
    g_battle_object_manager_bootstrap = new BattleObjectManagerBootstrap;
    g_event_effect_state_bootstrap = new EventEffectStateBootstrap;
    g_effect_sink_bootstrap = new EffectSinkBootstrap;
    g_battle_input_gate_bootstrap = new BattleInputGateAllocationView;

    g_effect_sink_bootstrap->load_effect_resource(
        "data/effect/effect.pat", 256);
    g_event_effect_state_bootstrap->initialize_effect_runtime();

    char path[260];
    for (int index = 0; index < 23; ++index) {
        wsprintfA(path, "data/bgm/st%02d.ogg", index);
        const unsigned hash = case_insensitive_crc32(
            reinterpret_cast<const unsigned char *>(path),
            static_cast<int>(strlen(path)));
        g_info_effect_lookup_map.insert(
            std::make_pair(hash, static_cast<unsigned short>(index + 900)));
    }
}

} // namespace th105
