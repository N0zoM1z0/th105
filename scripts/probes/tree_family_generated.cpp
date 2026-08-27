#include <map>
#include <set>

namespace th105 {

// Representative current-target std::_Tree instantiations used only for
// origin census.  The generated COMDATs, not these wrappers, are the anchors.
//
// The three layouts are independently target-backed:
//   * unsigned set nodes expose the nil byte at node +0x11;
//   * signed-int/small-mapped nodes expose it at +0x15;
//   * unsigned-key/eight-byte-mapped nodes expose it at +0x19.
// Current 0x006B3DA0 also reads/writes the last family's two mapped dwords at
// node +0x10/+0x14.  Anchor manifests require complete inventory-unique
// relocation-masked fingerprints from the SHA-pinned VC8 SP1 compiler.
struct TreeValue8 {
    unsigned first;
    unsigned second;

    TreeValue8() : first(0), second(0) {}
    TreeValue8(unsigned a, unsigned b) : first(a), second(b) {}
};

typedef std::set<unsigned int> UIntSetGeneratedProbe;
typedef std::map<int, unsigned char> IntByteMapGeneratedProbe;
typedef std::map<unsigned int, TreeValue8> UIntValue8MapGeneratedProbe;

__declspec(noinline) UIntSetGeneratedProbe::iterator
emit_uint_set_find(UIntSetGeneratedProbe &tree, const unsigned int &key)
{
    return tree.find(key);
}

__declspec(noinline) void
emit_uint_set_insert(UIntSetGeneratedProbe &tree, unsigned int key)
{
    tree.insert(key);
}

__declspec(noinline) IntByteMapGeneratedProbe::iterator
emit_int_byte_find(IntByteMapGeneratedProbe &tree, const int &key)
{
    return tree.find(key);
}

__declspec(noinline) void
emit_int_byte_insert(IntByteMapGeneratedProbe &tree, int key, unsigned char value)
{
    tree.insert(std::make_pair(key, value));
}

__declspec(noinline) unsigned
emit_int_byte_erase(IntByteMapGeneratedProbe &tree, int key)
{
    return static_cast<unsigned>(tree.erase(key));
}

__declspec(noinline) void
emit_int_byte_clear(IntByteMapGeneratedProbe &tree)
{
    tree.clear();
}

__declspec(noinline) UIntValue8MapGeneratedProbe::iterator
emit_uint_value8_find(UIntValue8MapGeneratedProbe &tree, const unsigned int &key)
{
    return tree.find(key);
}

__declspec(noinline) void
emit_uint_value8_insert(
    UIntValue8MapGeneratedProbe &tree,
    unsigned key,
    unsigned first,
    unsigned second)
{
    tree.insert(std::make_pair(key, TreeValue8(first, second)));
}

__declspec(noinline) unsigned
emit_uint_value8_erase(UIntValue8MapGeneratedProbe &tree, unsigned key)
{
    return static_cast<unsigned>(tree.erase(key));
}

__declspec(noinline) void
emit_uint_value8_clear(UIntValue8MapGeneratedProbe &tree)
{
    tree.clear();
}

// Iterator erasure forces the checked iterator increment/decrement and tree
// node lifetime helpers that survive as out-of-line COMDATs in the current
// binary.
__declspec(noinline) void
emit_int_byte_erase_iterator(
    IntByteMapGeneratedProbe &tree,
    IntByteMapGeneratedProbe::iterator it)
{
    tree.erase(it);
}

__declspec(noinline) void
emit_uint_value8_erase_iterator(
    UIntValue8MapGeneratedProbe &tree,
    UIntValue8MapGeneratedProbe::iterator it)
{
    tree.erase(it);
}

} // namespace th105
