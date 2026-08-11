#include <list>

// Force VC8 SP1 to emit the checked std::list<unsigned> specializations used
// by the free-slot reuse path in every roster-owned CharacterObject pool.
template class std::list<unsigned>;
