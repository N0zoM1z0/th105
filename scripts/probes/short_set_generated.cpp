#include <set>

namespace th105 {

typedef std::set<short> ShortSetProbe;

__declspec(noinline) std::pair<ShortSetProbe::iterator, bool>
emit_short_set_insert(ShortSetProbe &set, const short &value)
{
    return set.insert(value);
}

__declspec(noinline) ShortSetProbe::iterator
emit_short_set_erase_one(ShortSetProbe &set, ShortSetProbe::iterator where)
{
    ShortSetProbe::iterator next = where;
    ++next;
    set.erase(where);
    return next;
}

__declspec(noinline) void emit_short_set_erase_range(
    ShortSetProbe &set,
    ShortSetProbe::iterator first,
    ShortSetProbe::iterator last)
{
    set.erase(first, last);
}

__declspec(noinline) void emit_short_set_clear(ShortSetProbe &set)
{
    set.clear();
}

} // namespace th105
