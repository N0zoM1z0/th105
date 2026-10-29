#include <stddef.h>
namespace th105 {
// Pointer-only views: no complete Fighter or scenario allocation is asserted.
struct FighterActionCounterLeafView {
 unsigned char unknown_000[0x48a];
 short counter_48a;
 void set_counter(short value);
};
struct ScenarioResultEnableLeafView {
 unsigned char state_000;
 void start();
};
typedef char CounterOffset[offsetof(FighterActionCounterLeafView,counter_48a)==0x48a?1:-1];
void FighterActionCounterLeafView::set_counter(short value) {counter_48a=value;}
void ScenarioResultEnableLeafView::start() {state_000=1;}
}
