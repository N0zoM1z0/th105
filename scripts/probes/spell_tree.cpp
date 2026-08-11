#include "../../src/battle/SpellData.hpp"

#include <map>

namespace th105 {

typedef std::map<int, SpellRecordView> SpellTreeProbe;

__declspec(noinline) void emit_spell_tree_decrement(
    SpellTreeProbe::iterator &iterator)
{
    --iterator;
}

__declspec(noinline) std::pair<SpellTreeProbe::iterator, bool>
emit_spell_tree_insert(
    SpellTreeProbe &tree,
    const SpellTreeProbe::value_type &value)
{
    return tree.insert(value);
}

} // namespace th105
