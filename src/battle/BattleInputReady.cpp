#include "BattleController.hpp"

#include <stddef.h>

namespace th105 {

namespace {
class BattleInputReadyLock {
public:
    explicit BattleInputReadyLock(CriticalSectionWrapper *lock) : lock_(lock)
    {
        lock_->enter();
    }
    ~BattleInputReadyLock()
    {
        lock_->leave();
    }
private:
    CriticalSectionWrapper *lock_;
};
}

struct BattleInputReadyView {
    unsigned char reserved_000[0x104];
    SynchronizedInputState *input_104;
    unsigned char reserved_108[0x1c];
    CriticalSectionWrapper lock_124;
    unsigned char published_140;
    unsigned char consumed_141;

    unsigned char is_ready_4712b0();
};

unsigned char BattleInputReadyView::is_ready_4712b0()
{
    BattleInputReadyLock guard(&lock_124);
    return static_cast<unsigned char>(
        static_cast<unsigned char>(published_140 == consumed_141) &
        input_104->is_input_available_427680());
}

typedef char BattleInputReadyInputOffset[
    offsetof(BattleInputReadyView, input_104) == 0x104 ? 1 : -1];
typedef char BattleInputReadyLockOffset[
    offsetof(BattleInputReadyView, lock_124) == 0x124 ? 1 : -1];
typedef char BattleInputReadyPublishedOffset[
    offsetof(BattleInputReadyView, published_140) == 0x140 ? 1 : -1];

} // namespace th105
