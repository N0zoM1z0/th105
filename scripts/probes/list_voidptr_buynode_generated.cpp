#include <list>

namespace th105 {

typedef std::list<void *> ListVoidPtrGeneratedProbe;

__declspec(noinline) void emit_list_voidptr_push_back(
    ListVoidPtrGeneratedProbe &values,
    void *const &value)
{
    values.push_back(value);
}

} // namespace th105
