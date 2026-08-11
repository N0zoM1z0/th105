#include "BattleController.hpp"

namespace th105 {

class CriticalSectionScope {
public:
    explicit CriticalSectionScope(CriticalSectionWrapper *lock)
        : lock_(lock)
    {
        lock_->enter();
    }

    ~CriticalSectionScope()
    {
        lock_->leave();
    }

private:
    CriticalSectionWrapper *lock_;
};

unsigned char BattleInputGate::poll_synchronized_input_4708b0()
{
    CriticalSectionScope scope(&lock_124);
    unsigned char available = input_104->is_input_available_427680();
    return available & (published_140 == consumed_141);
}

} // namespace th105
