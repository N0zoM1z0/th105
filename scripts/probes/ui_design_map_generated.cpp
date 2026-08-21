#include <map>

namespace th105 {

// Force the VC8 checked std::_Tree specialization used by the current
// unsigned-key resource/design map.  The emitted find() COMDAT, not this
// wrapper, is the origin anchor.
typedef std::map<unsigned int, void *> UiDesignMapGeneratedProbe;

__declspec(noinline) UiDesignMapGeneratedProbe::iterator
emit_ui_design_map_find(
    UiDesignMapGeneratedProbe &tree,
    const unsigned int &key)
{
    typedef UiDesignMapGeneratedProbe::iterator
        (UiDesignMapGeneratedProbe::*FindMember)(const unsigned int &);
    FindMember member = &UiDesignMapGeneratedProbe::find;
    return (tree.*member)(key);
}

} // namespace th105
