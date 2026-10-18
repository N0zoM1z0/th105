#include "reimu_native_host.hpp"

using namespace th105_native;

int main(int argc, char **argv) {
    SetErrorMode(SEM_FAILCRITICALERRORS|SEM_NOGPFAULTERRORBOX);
    require(argc==8,"arguments: target effect-data actor-data candidate cases mode output");
    require((unsigned)GetModuleHandleA(0)==0x10000000,"host image base");
    require(!strcmp(argv[6],"target") || !strcmp(argv[6],"source"),"execution mode");
    AddVectoredExceptionHandler(1,reject_exception);
    map_target(argv[1]);
    unsigned char *effect_data=allocate(0x3200000,0x10000);
    unsigned char *actor_data=allocate(0x3000000,0x10000);
    require(load_file(argv[2],effect_data,0x10000)==0x10000,"effect data length");
    require(load_file(argv[3],actor_data,0x10000)==0x10000,"actor data length");
    protect(effect_data,0x10000,PAGE_READONLY);protect(actor_data,0x10000,PAGE_READONLY);
    unsigned char *candidate=allocate(0x4000000,0x20000);
    candidate_size=load_file(argv[4],candidate,0x20000);
    require(candidate_size<=82924,"candidate envelope");
    candidate_bytes=(unsigned char*)malloc(candidate_size);
    require(candidate_bytes!=0,"candidate witness allocation");
    memcpy(candidate_bytes,candidate,candidate_size);protect(candidate,0x20000,PAGE_EXECUTE_READ);
    unsigned char *actor=allocate(0x2000000,0x10000);
    initialize_runtime();
    FILE *inputs=open_file(argv[5],"rb"), *output=open_file(argv[7],"wb");
    char magic[8];unsigned count;
    read_exact(inputs,magic,8);read_exact(inputs,&count,4);
    require(!memcmp(magic,"TH105FX1",8) && count>0 && count<=2048,"input schema/count");
    write_exact(output,&count,4);
    for (unsigned n=0;n<count;++n) {
        unsigned seed,control_word;
        read_exact(inputs,&seed,4);read_exact(inputs,&control_word,4);
        require(control_word==0x27f || control_word==0x37f,"x87 precision fixture");
        memset(actor,0,0x10000);read_exact(inputs,actor,0x3000);
        unsigned char *manager=(unsigned char*)VirtualAlloc(0,0x1000,
            MEM_RESERVE|MEM_COMMIT,PAGE_READWRITE);
        require(manager!=0,"manager storage");
        require(((void* (__thiscall*)(void*))0x4378F0)(manager)==manager,"real manager constructor");
        require(*(unsigned*)manager==0x6C1490 && (*(unsigned**)manager)[3]==0x437C00,
            "manager constructor vtable/emit slot");
        unsigned char saved_vector[16],saved_tree[12];
        memcpy(saved_vector,manager+0x64,16);memcpy(saved_tree,manager+0x88,12);
        memcpy(manager+0x64,effect_data+0x300,16);memcpy(manager+0x88,effect_data,12);
        *(void**)0x6FBCB0=manager;
        ((void (__cdecl*)(unsigned))0x406670)(seed);
        unsigned expected_control=(control_word==0x27f?_PC_53:_PC_64)|_RC_NEAR|_MCW_EM;
        unsigned control_mask=_MCW_PC|_MCW_RC|_MCW_EM;
        _control87(expected_control,control_mask);
        unsigned address=!strcmp(argv[6],"target")?0x478FA0:0x4000000;
        ((void (__thiscall*)(void*))address)(actor);
        unsigned objects=*(unsigned*)(manager+0x60);
        require(objects==1,"root must return after exactly one real effect");
        unsigned head=*(unsigned*)(manager+0x5C), node=*(unsigned*)head;
        require(node!=head && *(unsigned*)node==head && *(unsigned*)(head+4)==node &&
            *(unsigned*)(node+4)==head,"single linked effect node");
        unsigned char *effect=*(unsigned char**)(node+8);
        require(*(unsigned*)effect==0x6C14BC && *(unsigned short*)(effect+0x13C)==123 &&
            *(unsigned*)(effect+0x15C)==0x10000 && *(void**)(effect+0x164)==actor &&
            *(unsigned*)(effect+0x158)==1,"real effect identity/handle/context");
        unsigned char **slots=*(unsigned char***)(manager+0x10);
        require(slots!=0 && *(unsigned char***)(manager+0x14)==slots+1 && slots[0]==effect &&
            **(unsigned**)(manager+0x20)==1,"effect pool slot/generation");
        unsigned actual_control=_control87(0,0)&control_mask;
        require(actual_control==expected_control,"root x87 control word");
        write_exact(output,actor,0x1000);write_exact(output,effect,0x178);
        write_exact(output,(void*)0x6FA1FC,4);write_exact(output,(void*)0x6FDEF0,2496);
        write_exact(output,&objects,4);write_exact(output,&actual_control,4);
        // Restore borrowed resource headers before the actual owning destructor.
        memcpy(manager+0x64,saved_vector,16);memcpy(manager+0x88,saved_tree,12);
        ((void (__thiscall*)(void*))0x437DF0)(manager);
        require(VirtualFree(manager,0,MEM_RELEASE)!=0,"manager storage release");
        *(void**)0x6FBCB0=0;
        require(text_unchanged() && !memcmp(candidate,candidate_bytes,candidate_size),"code changed");
    }
    require(fgetc(inputs)==EOF,"trailing input records");
    require(fclose(inputs)==0 && fclose(output)==0,"file close");
    printf("{\"cases\":%u,\"kernel32_imports\":%u,\"blocked_imports\":%u,"
        "\"target_text_unchanged\":true,\"candidate_unchanged\":true}\n",
        count,kernel_imports,blocked_imports);
    return 0;
}
