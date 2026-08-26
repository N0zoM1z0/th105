#include "SpellData.hpp"

#include <map>

namespace th105 {

SpellTree g_common_spell_tree;

typedef std::map<int, SpellRecordView> NativeSpellMap;

SpellRecordView *SpellDataOwner::find_local_then_common_spell_record(int key)
{
    NativeSpellMap &local =
        *reinterpret_cast<NativeSpellMap *>(&local_tree_14);
    NativeSpellMap::iterator it = local.find(key);
    if (it != local.end())
        return &it->second;

    NativeSpellMap &common =
        *reinterpret_cast<NativeSpellMap *>(&g_common_spell_tree);
    it = common.find(key);
    if (it != common.end())
        return &it->second;
    return 0;
}

} // namespace th105
