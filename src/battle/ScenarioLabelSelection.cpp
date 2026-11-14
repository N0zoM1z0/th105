#include "battle/ScenarioData.hpp"

namespace th105 {

unsigned char CScenarioData::select_label(std::string label)
{
    script_35c.seek(0);
    for (;;) {
        CCommandBase *command = script_35c.next_command();
        if (command == 0)
            return 0;
        if (static_cast<CCommand0 *>(command)->command_id_04 == 0 &&
            static_cast<TCommand1<std::string> *>(command)->arg0_08.compare(label) == 0)
            return 1;
    }
}

} // namespace th105
