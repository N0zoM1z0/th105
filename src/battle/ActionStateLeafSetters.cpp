#include <stddef.h>
#include "battle/ScenarioData.hpp"
#include "battle/Collision.hpp"
namespace th105 {
typedef char AccumulatedOffset[offsetof(Fighter, accumulated_counter_488) == 0x488 ? 1 : -1];
typedef char PendingOffset[offsetof(Fighter, pending_gate_48a) == 0x48a ? 1 : -1];
void Fighter::set_pending_gate_48a(short value) {pending_gate_48a=value;}
void ScenarioResultResource::start() {state_000=1;}
}
