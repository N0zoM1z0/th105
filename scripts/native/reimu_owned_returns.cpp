#include "reimu_native_host.hpp"
#include <deque>

using namespace th105_native;

int main(int argc, char **argv) {
    SetErrorMode(SEM_FAILCRITICALERRORS|SEM_NOGPFAULTERRORBOX);
    require(argc==7,"arguments: target resources candidate cases mode output");
    require((unsigned)GetModuleHandleA(0)==0x10000000,"host image base");
    require(!strcmp(argv[5],"target") || !strcmp(argv[5],"source"),"execution mode");
    AddVectoredExceptionHandler(1,reject_exception);
    map_target(argv[1]);initialize_runtime();
    unsigned char *data=allocate(0x3000000,0x100000);
    load_file(argv[2],data,0x100000);protect(data,0x100000,PAGE_READONLY);
    unsigned char *candidate=allocate(0x4000000,0x20000);
    candidate_size=load_file(argv[3],candidate,0x20000);
    require(candidate_size<=82924,"candidate envelope");
    candidate_bytes=(unsigned char*)malloc(candidate_size);
    require(candidate_bytes!=0,"candidate witness allocation");
    memcpy(candidate_bytes,candidate,candidate_size);protect(candidate,0x20000,PAGE_EXECUTE_READ);
    unsigned char *actor=allocate(0x2000000,0x10000);
    FILE *inputs=open_file(argv[4],"rb"),*output=open_file(argv[6],"wb");
    char magic[8];unsigned count,total_objects=0;
    read_exact(inputs,magic,8);read_exact(inputs,&count,4);
    require(!memcmp(magic,"TH105OB1",8) && count>0 && count<=2048,"input schema/count");
    write_exact(output,&count,4);
    for (unsigned n=0;n<count;++n) {
        unsigned seed,cw,expected_count,expected_action,parameter_words;
        read_exact(inputs,&seed,4);read_exact(inputs,&cw,4);read_exact(inputs,&expected_count,4);
        read_exact(inputs,&expected_action,4);read_exact(inputs,&parameter_words,4);
        require((cw==0x27f || cw==0x37f) && expected_count>0 && expected_count<=10 &&
            (parameter_words==3 || parameter_words==4),"case scope");
        memset(actor,0,0x10000);read_exact(inputs,actor,0x3000);
        unsigned expected_control=(cw==0x27f?_PC_53:_PC_64)|_RC_NEAR|_MCW_EM;
        unsigned control_mask=_MCW_PC|_MCW_RC|_MCW_EM;
        _control87(expected_control,control_mask);
        ((void (__cdecl*)())0x4065B0)();
        ((void (__cdecl*)(unsigned))0x406670)(seed);
        unsigned char *manager=allocate(0x3400000,0x10000);
        require(((void* (__thiscall*)(void*,void*))0x493750)(manager,actor)==manager,"owned manager constructor");
        require(*(unsigned*)manager==0x6C40FC && (*(unsigned**)manager)[1]==0x4938D0 &&
            *(void**)(manager+0x64)==actor,"owned manager vtable/owner");
        unsigned char **slots=*(unsigned char***)(manager+0x10);
        unsigned *generations=*(unsigned**)(manager+0x20);
        require(slots!=0 && *(unsigned char***)(manager+0x14)==slots+256 &&
            generations!=0 && *(unsigned**)(manager+0x24)==generations+256 &&
            *(unsigned*)(manager+0x34)==256 && *(unsigned*)(manager+0x38)==256 &&
            *(unsigned*)(manager+0x60)==0,"actual 256-object preallocation/release");
        *(void**)(actor+0x658)=manager;
        ((void (__thiscall*)(void*))(!strcmp(argv[5],"target")?0x478FA0:0x4000000))(actor);
        unsigned objects=*(unsigned*)(manager+0x60),generation=*(unsigned*)(manager+0x38);
        unsigned free_slots=*(unsigned*)(manager+0x34),actual_control=_control87(0,0)&control_mask;
        if (objects!=expected_count) {
            unsigned h=*(unsigned*)(manager+0x5C),p=*(unsigned*)h;
            for (unsigned j=0;j<objects && j<32 && p!=h;++j,p=*(unsigned*)p) {
                unsigned char *o=*(unsigned char**)(p+8);void *params=*(void**)(o+0x340);
                fprintf(stderr,"node%u object%p id%u seq%u parent%p related%p params%p bytes%u\n",j,o,
                    *(unsigned short*)(o+0x13C),*(unsigned short*)(o+0x13E),*(void**)(o+0x34C),
                    *(void**)(o+0x16C),params,params?(unsigned)HeapSize(*(HANDLE*)0x6FDC94,0,params):0);
            }
        }
        if (objects!=expected_count || generation!=256+objects || free_slots!=256-objects)
            fprintf(stderr,"case%u action%u: objects%u expected%u generation%u free%u\n",n,
                *(unsigned short*)(actor+0x13C),objects,expected_count,generation,free_slots);
        require(objects==expected_count && generation==256+objects && free_slots==256-objects,
            "complete returning volley/pool counters");
        require(actual_control==expected_control,"root FP control word");
        write_exact(output,&objects,4);write_exact(output,&actual_control,4);
        write_exact(output,&generation,4);write_exact(output,&free_slots,4);
        write_exact(output,actor,0x1000);
        write_exact(output,(void*)0x6FA1FC,4);write_exact(output,(void*)0x6FDEF0,2496);
        unsigned head=*(unsigned*)(manager+0x5C),node=*(unsigned*)head,previous=head;
        for (unsigned j=0;j<objects;++j) {
            require(node!=head && *(unsigned*)(node+4)==previous,"owned list predecessor");
            unsigned char *object=*(unsigned char**)(node+8);
            unsigned token=*(unsigned*)(object+0x334),slot=token&0xffff,object_generation=token>>16;
            require(*(unsigned*)object==0x6C40A4 && *(unsigned short*)(object+0x13C)==expected_action &&
                slot==255-j && object_generation==257+j && slots[slot]==object &&
                generations[slot]==object_generation && *(unsigned*)(object+0x330)==1,
                "actual active object slot/generation/identity");
            require(*(void**)(object+0x348)==actor && *(void**)(object+0x168)==actor &&
                *(void**)(object+0x16C)==actor && *(unsigned*)(object+0x170)==0x2002000,
                "object owner/related/peer links");
            void *parameters=*(void**)(object+0x340);
            require(parameters!=0,"copied parameter allocation");
            SIZE_T allocation=HeapSize(*(HANDLE*)0x6FDC94,0,parameters);
            require(allocation!=(SIZE_T)-1 && allocation>=parameter_words*4,"parameter heap extent");
            write_exact(output,&object,4);write_exact(output,&allocation,4);
            write_exact(output,&parameter_words,4);write_exact(output,object,0x388);
            write_exact(output,parameters,parameter_words*4);
            const std::deque<void *> &children=*reinterpret_cast<const std::deque<void *> *>(object+0x350);
            unsigned child_count=(unsigned)children.size();
            bool companion=expected_action==811 && (j&1)!=0;
            require(child_count==((expected_action==811 && !companion)?1u:0u),"object child deque count");
            void *parent=companion?*(void**)(previous+8):0;
            require(*(void**)(object+0x34C)==parent,"object parent link");
            write_exact(output,&child_count,4);
            if (child_count) {
                unsigned next=*(unsigned*)node;require(next!=head,"companion list node");
                void *child=children[0];require(child==*(void**)(next+8),"parent child deque/list correspondence");
                write_exact(output,&child,4);
            }
            previous=node;node=*(unsigned*)node;
        }
        require(node==head && *(unsigned*)(head+4)==previous,"complete owned list");
        ((void (__thiscall*)(void*))0x4939C0)(manager);
        require(VirtualFree(manager,0,MEM_RELEASE)!=0,"owned manager storage release");
        require(text_unchanged() && !memcmp(candidate,candidate_bytes,candidate_size),"code changed");
        total_objects+=objects;
    }
    require(fgetc(inputs)==EOF,"trailing input records");
    require(fclose(inputs)==0 && fclose(output)==0,"file close");
    printf("{\"cases\":%u,\"kernel32_imports\":%u,\"blocked_imports\":%u,"
        "\"target_text_unchanged\":true,\"candidate_unchanged\":true,\"objects\":%u}\n",
        count,kernel_imports,blocked_imports,total_objects);
    return 0;
}
