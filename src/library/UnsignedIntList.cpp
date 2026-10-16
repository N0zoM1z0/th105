#include <list>

// Compiler-library context, excluded from authored progress. Compile without
// /GL to expose the ordinary shared list ABI; the original TU is unknown.
template class std::list<unsigned int>;
