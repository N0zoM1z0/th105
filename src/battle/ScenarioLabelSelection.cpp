#include "battle/ScenarioData.hpp"

namespace th105 {

unsigned char CScenarioData::select_label(std::string label)
{
    script_35c.current_28 = script_35c.pending_14.begin();
    CCommandBase *command;
    while ((command = script_35c.next_command()) != 0) {
        if (static_cast<CCommand0 *>(command)->command_id_04 == 0 &&
            static_cast<TCommand1<std::string> *>(command)->arg0_08.compare(label) == 0)
            return 1;
    }
    return 0;
}

} // namespace th105
