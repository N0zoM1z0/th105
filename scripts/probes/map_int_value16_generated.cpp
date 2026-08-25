#include <map>
#include <memory>

namespace th105 {

struct TreeValue16 {
    unsigned values[4];
};

typedef std::map<int, TreeValue16> TreeMapIntValue16;

void probe_tree_insert(TreeMapIntValue16 &items, int key, TreeValue16 const &value)
{
    items.insert(std::make_pair(key, value));
}

void probe_tree_erase(TreeMapIntValue16 &items, TreeMapIntValue16::iterator where)
{
    items.erase(where);
}

void probe_tree_clear(TreeMapIntValue16 &items)
{
    items.clear();
}

void probe_tree_inc(TreeMapIntValue16::iterator &where)
{
    ++where;
}

void probe_tree_dec(TreeMapIntValue16::iterator &where)
{
    --where;
}

TreeMapIntValue16::iterator probe_tree_find(TreeMapIntValue16 &items, int key)
{
    return items.find(key);
}

void probe_tree_construct(void *destination)
{
    new (destination) TreeMapIntValue16();
}

void probe_tree_destroy(TreeMapIntValue16 *items)
{
    items->~TreeMapIntValue16();
}

} // namespace th105
