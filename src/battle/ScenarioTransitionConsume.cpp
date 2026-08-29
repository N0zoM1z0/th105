#include <list>
#include <stddef.h>

namespace th105 {

struct ScenarioTransitionConsumeView {
    unsigned char reserved_000[0x5a4];
    std::list<int> transition_codes_5a4;

    int consume_transition_code_458d90();
};

int ScenarioTransitionConsumeView::consume_transition_code_458d90()
{
    int value = transition_codes_5a4.front();
    transition_codes_5a4.erase(transition_codes_5a4.begin());
    return value;
}

typedef char ScenarioTransitionConsumeView_list_offset[
    offsetof(ScenarioTransitionConsumeView, transition_codes_5a4) == 0x5a4 ? 1 : -1];

} // namespace th105
