#include <list>

namespace th105 {

typedef std::list<void *> ListVoidPtrTidyGeneratedProbe;

__declspec(noinline) void emit_list_voidptr_destructor(
    ListVoidPtrTidyGeneratedProbe *values)
{
    values->~list();
}

} // namespace th105
