// JP1.06a 0x004540F0. Complete timeline command loader; full code and switch payload replay.
// See docs/SCENE_TIMELINE_LOADER_2026_10_29.md.
#include "battle/ScriptCommandRegistry.hpp"
#include "ui/RenderTimeline.hpp"
#include "ui/SceneTimelineEntries.hpp"
#include "ui/Title.hpp"
#include <map>
#include <list>
#include <string>
#include <stddef.h>
namespace th105 {
struct TimelineScriptReaderView {
    bool load(const char *, int);
    CCommandBase *next_command();
};
struct TimelineCommandHeader { void *vtable_00; int id_04; };
struct TimelineSpriteOptionsView {
    void set_texture_options(unsigned,int,int,int,int,int,int);
};
struct SceneTimelineLoaderView {
    int bpm_00;
    unsigned start_tick_04, elapsed_08, end_time_0c;
    unsigned previous_tick_10, accumulated_time_14;
    CScript script_18;
    std::map<int,RenderTimelineEntry *> objects_4c;
    std::list<RenderTimelineEntry> records_58;
    SceneTimelineEntries events_64;
    std::string music_path_70;
    unsigned event_flag_8c;
    unsigned char flags_90[4];
    bool load_script(const char *path);
};
typedef char LoaderSize[sizeof(SceneTimelineLoaderView)==0x94?1:-1];
typedef char ScriptOffset[offsetof(SceneTimelineLoaderView,script_18)==0x18?1:-1];
typedef char EventOffset[offsetof(SceneTimelineLoaderView,events_64)==0x64?1:-1];
bool SceneTimelineLoaderView::load_script(const char *path)
{
    TimelineScriptReaderView *script=reinterpret_cast<TimelineScriptReaderView *>(&script_18);
    if(!script->load(path,0)) return false;
    bpm_00=120;
    previous_tick_10=0;
    accumulated_time_14=0;
    // A notify event initializes only time/type. Native ignores its other
    // fields, so do not invent zero initialization for the reusable record.
    SceneInterpolationEntry24 event;
    CCommandBase *command=script->next_command();
    while(command!=0) {
        switch(reinterpret_cast<TimelineCommandHeader *>(command)->id_04) {
        case 0: {
            TCommand2<int,int> *c=static_cast<TCommand2<int,int> *>(command);
            accumulated_time_14+=(static_cast<unsigned>(c->arg0_08)-previous_tick_10)*60000u/static_cast<unsigned>(bpm_00);
            previous_tick_10=c->arg0_08;
            bpm_00=c->arg1;
            break;
        }
        case 2:
            music_path_70=static_cast<TCommand1<std::string> *>(command)->arg0_08;
            break;
        case 1: {
            typedef TCommand5<int,std::string,int,int,int> Picture;
            Picture *c=static_cast<Picture *>(command);
            if(c->arg1.empty()) break;
            std::map<int,RenderTimelineEntry *>::iterator found=objects_4c.find(c->arg0_08);
            RenderTimelineEntry *record;
            if(found==objects_4c.end()) {
                records_58.push_back(RenderTimelineEntry());
                record=&records_58.back();
                objects_4c.insert(std::pair<int,RenderTimelineEntry *>(c->arg0_08,record));
            } else record=found->second;
            switch(c->arg2) {
            case 0: record->sampler_one_6c=1;record->sampler_two_70=1;break;
            case 1: record->sampler_two_70=1;record->sampler_one_6c=3;break;
            case 2: record->sampler_one_6c=1;record->sampler_two_70=3;break;
            case 3: record->sampler_two_70=3;record->sampler_one_6c=3;break;
            }
            unsigned width,height,handle;
            record->texture_handles_00.push_back(*g_title_resource_manager.load_texture(&handle,c->arg1.c_str(),&width,&height));
            record->sprites_14.push_back(CSpriteEx());
            switch(c->arg3) {
            case 0:
                record->sprites_14.back().set_texture(record->texture_handles_00.back(),0,0,width,height);break;
            case 1:
                reinterpret_cast<TimelineSpriteOptionsView *>(&record->sprites_14.back())->set_texture_options(record->texture_handles_00.back(),0,0,width,height,width/2,height/2);break;
            case 2:
                reinterpret_cast<TimelineSpriteOptionsView *>(&record->sprites_14.back())->set_texture_options(record->texture_handles_00.back(),0,0,width,height,0,height);break;
            case 3:
                reinterpret_cast<TimelineSpriteOptionsView *>(&record->sprites_14.back())->set_texture_options(record->texture_handles_00.back(),0,0,width,height,width,0);break;
            case 4:
                reinterpret_cast<TimelineSpriteOptionsView *>(&record->sprites_14.back())->set_texture_options(record->texture_handles_00.back(),0,0,width,height,width,height);break;
            }
            record->blend_mode_68=c->arg4;
            break;
        }
        case 3:case 4:case 5:case 6:case 11:case 12:case 13: {
            typedef TCommand5<int,float,float,float,int> Float;
            Float *c=static_cast<Float *>(command);
            if(objects_4c.find(c->arg0_08)==objects_4c.end()) break;
            event.type_14=reinterpret_cast<TimelineCommandHeader *>(command)->id_04;
            event.object_id_00=c->arg0_08;
            event.start_04=static_cast<unsigned>(
                (c->arg1-static_cast<float>(previous_tick_10))*60000.0/
                static_cast<float>(bpm_00)+static_cast<float>(accumulated_time_14));
            event.end_08=static_cast<unsigned>(
                (c->arg1+c->arg2-static_cast<float>(previous_tick_10))*60000.0/
                static_cast<float>(bpm_00)+static_cast<float>(accumulated_time_14));
            event.target.float_0c=c->arg3;
            event.easing_10=c->arg4;
            events_64.insert(event);
            break;
        }
        case 7:case 8:case 9:case 10: {
            typedef TCommand5<int,float,float,int,int> Color;
            Color *c=static_cast<Color *>(command);
            if(objects_4c.find(c->arg0_08)==objects_4c.end()) break;
            event.type_14=reinterpret_cast<TimelineCommandHeader *>(command)->id_04;
            event.object_id_00=c->arg0_08;
            event.start_04=static_cast<unsigned>(
                (c->arg1-static_cast<float>(previous_tick_10))*60000.0/
                static_cast<float>(bpm_00)+static_cast<float>(accumulated_time_14));
            event.end_08=static_cast<unsigned>(
                (c->arg1+c->arg2-static_cast<float>(previous_tick_10))*60000.0/
                static_cast<float>(bpm_00)+static_cast<float>(accumulated_time_14));
            event.target.uint_0c=c->arg3;
            event.easing_10=c->arg4;
            events_64.insert(event);
            break;
        }
        case 14: {
            TCommand2<int,int> *c=static_cast<TCommand2<int,int> *>(command);
            std::map<int,RenderTimelineEntry *>::iterator found=objects_4c.find(c->arg0_08);
            if(found!=objects_4c.end()) found->second->duration_78=c->arg1;
            break;
        }
        case 16: {
            unsigned time=(static_cast<unsigned>(static_cast<TCommand1<int> *>(command)->arg0_08)-previous_tick_10)*60000u/static_cast<unsigned>(bpm_00)+accumulated_time_14;
            event.type_14=16;
            event.start_04=time;
            event.end_08=time;
            events_64.insert(event);
            break;
        }
        case 17:
            end_time_0c=(static_cast<unsigned>(static_cast<TCommand1<int> *>(command)->arg0_08)-previous_tick_10)*60000u/static_cast<unsigned>(bpm_00)+accumulated_time_14;
            break;
        }
        command=script->next_command();
    }
    start_tick_04=0;
    event_flag_8c=0;
    return true;
}
}
