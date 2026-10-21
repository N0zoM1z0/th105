#include <map>

namespace th105 {
struct UiDesignObject;
}

// Compiler-library context, excluded from authored progress. The ordinary
// native tree instantiation preserves the shared find ABI before CIL linking.
// This provides no claim about the original source translation-unit boundary.
typedef std::_Tree<std::_Tmap_traits<unsigned int,
    th105::UiDesignObject *, std::less<unsigned int>,
    std::allocator<std::pair<const unsigned int, th105::UiDesignObject *> >,
    false> > UiDesignObjectTreeForAbi;

template UiDesignObjectTreeForAbi::iterator
    UiDesignObjectTreeForAbi::find(const unsigned int &);
