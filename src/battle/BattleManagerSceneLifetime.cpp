#include <list>
#include <stddef.h>

namespace th105 {

// Narrow current-target lifetime view of the exact CBattleManagerBase prefix.
struct BattleManagerBaseDependency {
    virtual ~BattleManagerBaseDependency();
    unsigned char storage_004[0x70];
    BattleManagerBaseDependency();
};
typedef char BattleManagerBaseDependency_size[(sizeof(BattleManagerBaseDependency)==0x74)?1:-1];

// Current CScenarioData/story-render subobject lifetime used by CBattleManager.
struct ScenarioDataLifetime {
    unsigned char storage_000[0x528];
    ScenarioDataLifetime();
    ~ScenarioDataLifetime();
};
typedef char ScenarioDataLifetime_size[(sizeof(ScenarioDataLifetime)==0x528)?1:-1];

struct NormalSceneManagerLifetime : BattleManagerBaseDependency {
    unsigned char gap_074[0x18];
    ScenarioDataLifetime scenario_08c;

    NormalSceneManagerLifetime();
    // Intentionally implicit virtual destructor. VC8's implicit destructor
    // omits a redundant derived-vptr publication that an explicit empty body
    // would introduce; current scalar-delete/vtable ownership proves this is
    // the shipped lifetime shape.
};
typedef char NormalSceneManager_scenario_off[(offsetof(NormalSceneManagerLifetime,scenario_08c)==0x8c)?1:-1];
typedef char NormalSceneManager_size[(sizeof(NormalSceneManagerLifetime)==0x5b4)?1:-1];
NormalSceneManagerLifetime::NormalSceneManagerLifetime() {}

struct ArcadeSceneManagerLifetime : NormalSceneManagerLifetime {
    std::list<int> opponents_5b4;
    unsigned phase_counter_5c0;
    unsigned fade_pending_5c4;

    ArcadeSceneManagerLifetime();
    // Implicit destructor is required for the target scalar wrapper to inline
    // list teardown before the NormalSceneManager destructor.
};
typedef char ArcadeSceneManager_opponents_off[(offsetof(ArcadeSceneManagerLifetime,opponents_5b4)==0x5b4)?1:-1];
typedef char ArcadeSceneManager_size[(sizeof(ArcadeSceneManagerLifetime)==0x5c8)?1:-1];
ArcadeSceneManagerLifetime::ArcadeSceneManagerLifetime() {}

} // namespace th105
