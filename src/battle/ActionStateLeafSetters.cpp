#include <stddef.h>
#include "battle/ScenarioData.hpp"
namespace th105 {
// Fighter view is pointer-only; scenario uses the shared result owner.
struct FighterActionCounterLeafView {
 unsigned char unknown_000[0x48a];
 short counter_48a;
 void set_counter(short value);
};
typedef char CounterOffset[offsetof(FighterActionCounterLeafView,counter_48a)==0x48a?1:-1];
void FighterActionCounterLeafView::set_counter(short value) {counter_48a=value;}
void ScenarioResultResource::start() {state_000=1;}
}
