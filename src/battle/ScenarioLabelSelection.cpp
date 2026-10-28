#include "battle/ScriptCommandRuntime.hpp"
#include <deque>
#include <string>
#include <stddef.h>

namespace th105 {
struct ScenarioLabelScriptView {
    unsigned char registry_00[0x14];
    std::deque<CCommandBase *> commands_14;
    std::deque<CCommandBase *>::iterator cursor_28;
    CCommandBase *next_command();
};
struct ScenarioLabelOwnerView {
    unsigned char prefix_000[0x35c];
    ScenarioLabelScriptView script_35c;
    unsigned char select_label(std::string label);
};
typedef char label_script_size[sizeof(ScenarioLabelScriptView)==0x34?1:-1];
typedef char label_cursor_offset[offsetof(ScenarioLabelScriptView,cursor_28)==0x28?1:-1];

unsigned char ScenarioLabelOwnerView::select_label(std::string label)
{
    script_35c.cursor_28=script_35c.commands_14.begin();
    CCommandBase *command;
    while((command=script_35c.next_command())!=0) {
        if(static_cast<CCommand0 *>(command)->command_id_04==0 &&
           static_cast<TCommand1<std::string> *>(command)->arg0_08.compare(label)==0)
            return 1;
    }
    return 0;
}
}
