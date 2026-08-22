#include "ResultMenu.hpp"

extern "C" void __fastcall destroy_result_index_deque(void *deque);
extern "C" void __fastcall release_owned_pointer_buffer(void *buffer);

namespace th105 {

ResultStringDeque20::~ResultStringDeque20()
{
    destroy_result_index_deque(this);
}

void ResultStringDeque20::clear()
{
    destroy_result_index_deque(this);
}

ResultIndexDeque20::~ResultIndexDeque20()
{
    destroy_result_index_deque(this);
}

ResultPointerDeque20::~ResultPointerDeque20()
{
    release_owned_pointer_buffer(this);
}

ResultReplayDeque20::~ResultReplayDeque20()
{
    release_owned_pointer_buffer(this);
}

ResultList::ResultList()
{
    field_ac = 0;
    field_a8 = 0;
}


} // namespace th105
