#include "assets/CsvFileLoading.cpp"
#include "battle/ScriptLifecycle.cpp"
#include <cstring>
#include <cstdlib>
#include <new>
namespace th105 {
void __stdcall parse_script_line(CScript *script,char *line)
{
    char *colon=strchr(line,':');
    if(colon!=0) {
        char *space=strchr(line,' ');
        int length=(space!=0 && space<colon)?space-line:colon-line;
        char *prefix=new char[length+1];
        strncpy_s(prefix,length+1,line,length);
        CScript::CommandMap::iterator found=script->commands_00.find(std::string(prefix));
        free(prefix);
        if(found!=script->commands_00.end()) {
            CCommandBase *command=found->second->create();
            command->parse(colon+1);
            script->pending_14.push_back(command);
            return;
        }
    }
    if(script->default_factory_0c!=0) {
        CCommandBase *command=script->default_factory_0c->create();
        command->parse(line);
        script->pending_14.push_back(command);
    }
}
}

bool CScript::load(const char *path, int option)
{
 th105::FileBufferContext file;
 if(!file.load_text(path))return false;
 clear_pending_commands();
 char delimiters[3]="\r\n";
 char *context;
 char *line=strtok_s(reinterpret_cast<char *>(file.data_00),delimiters,&context);
 while(line){
  if(*line!='#')th105::parse_script_line(this,line);
  line=strtok_s(0,delimiters,&context);
 }
 current_28=pending_14.begin();
 return true;
}
