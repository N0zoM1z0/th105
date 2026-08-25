#include <map>
#include <memory>

namespace th105 {

struct TreeValue244 {
    unsigned char bytes[244];
};

typedef std::map<int, TreeValue244> TreeMapIntValue244;

void probe_tree244_insert(TreeMapIntValue244 &items, int key, TreeValue244 const &value)
{
    items.insert(std::make_pair(key, value));
}

void probe_tree244_erase(TreeMapIntValue244 &items, TreeMapIntValue244::iterator where)
{
    items.erase(where);
}

void probe_tree244_clear(TreeMapIntValue244 &items)
{
    items.clear();
}

void probe_tree244_inc(TreeMapIntValue244::iterator &where)
{
    ++where;
}

void probe_tree244_dec(TreeMapIntValue244::iterator &where)
{
    --where;
}

void probe_tree244_construct(void *destination)
{
    new (destination) TreeMapIntValue244();
}

void probe_tree244_destroy(TreeMapIntValue244 *items)
{
    items->~TreeMapIntValue244();
}

} // namespace th105
