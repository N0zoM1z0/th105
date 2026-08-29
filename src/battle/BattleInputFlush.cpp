#include "BattleController.hpp"

#include <deque>
#include <stddef.h>

namespace th105 {

namespace {
class CriticalSectionScopeFlush {
public:
    explicit CriticalSectionScopeFlush(CriticalSectionWrapper *lock) : lock_(lock) { lock_->enter(); }
    ~CriticalSectionScopeFlush() { lock_->leave(); }
private:
    CriticalSectionWrapper *lock_;
};
}

struct NetworkInputSinkView {
    unsigned char reserved_000[0x104];
    SynchronizedInputState *input_104;
    unsigned char reserved_108[0x1c];
    CriticalSectionWrapper lock_124;

    void flush_to(std::deque<short> *destination);
};

void NetworkInputSinkView::flush_to(std::deque<short> *destination)
{
    CriticalSectionScopeFlush scope(&lock_124);

    unsigned int index = destination->size();
    while (index < reinterpret_cast<std::deque<short> *>(
                       &input_104->controls_3c)->size()) {
        destination->push_back(
            (*reinterpret_cast<std::deque<short> *>(
                &input_104->controls_3c))[index]);
        ++index;
    }
}

typedef char NetworkInputSinkView_input_offset[
    offsetof(NetworkInputSinkView, input_104) == 0x104 ? 1 : -1];
typedef char NetworkInputSinkView_lock_offset[
    offsetof(NetworkInputSinkView, lock_124) == 0x124 ? 1 : -1];

} // namespace th105
