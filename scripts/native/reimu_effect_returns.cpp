// Diagnostic host for a hash-attested canonical image and source-derived root.
// No game entry point, instruction patch, callback stub or supplied result.
#define _WIN32_WINNT 0x0501
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static unsigned char *raw_image;
static unsigned char *target_image;
static IMAGE_NT_HEADERS *headers;
static IMAGE_SECTION_HEADER *sections;
static unsigned candidate_size;
static unsigned char *candidate_bytes;
static unsigned kernel_imports, blocked_imports;

static void require(bool condition, const char *message) {
    if (!condition) {
        fprintf(stderr,"native effect-return probe failed: %s\n",message);
        fflush(stderr);
        ExitProcess(2);
    }
}
static LONG CALLBACK reject_exception(EXCEPTION_POINTERS *fault) {
    fprintf(stderr,"native exception %08lx at %p\n",
        fault->ExceptionRecord->ExceptionCode,fault->ExceptionRecord->ExceptionAddress);
    fflush(stderr);
    TerminateProcess(GetCurrentProcess(),3);
    return EXCEPTION_CONTINUE_SEARCH;
}
static unsigned char *allocate(unsigned address, unsigned size) {
    unsigned char *result=(unsigned char*)VirtualAlloc((void*)address,size,
        MEM_RESERVE|MEM_COMMIT,PAGE_READWRITE);
    require(result==(unsigned char*)address,"fixed-address allocation");
    return result;
}
static void protect(void *address, unsigned size, DWORD permissions) {
    DWORD old;
    require(VirtualProtect(address,size,permissions,&old)!=0,"memory protection");
}
static void read_exact(FILE *file, void *output, unsigned size) {
    require(fread(output,1,size,file)==size,"truncated input");
}
static void write_exact(FILE *file, const void *input, unsigned size) {
    require(fwrite(input,1,size,file)==size,"output write");
}
static FILE *open_file(const char *path, const char *mode) {
    FILE *result=fopen(path,mode);
    require(result!=0,"file open");
    return result;
}
static unsigned load_file(const char *path, void *output, unsigned capacity) {
    FILE *file=open_file(path,"rb");
    require(fseek(file,0,SEEK_END)==0,"input seek");
    long size=ftell(file);
    require(size>0 && (unsigned long)size<=capacity,"input length");
    rewind(file);read_exact(file,output,(unsigned)size);
    require(fclose(file)==0,"input close");
    return (unsigned)size;
}
static bool text_unchanged() {
    for (unsigned n=0;n<headers->FileHeader.NumberOfSections;++n)
        if (!memcmp(sections[n].Name,".text",5))
            return !memcmp(target_image+sections[n].VirtualAddress,
                raw_image+sections[n].PointerToRawData,sections[n].SizeOfRawData);
    return false;
}
static void map_target(const char *path) {
    // Reserve before the large file allocation; Wine also needs PRELOADRESERVE.
    target_image=allocate(0x400000,0x306000);
    raw_image=(unsigned char*)malloc(3129344);
    require(raw_image!=0,"raw image allocation");
    require(load_file(path,raw_image,3129344)==3129344,"canonical file length");
    require(((IMAGE_DOS_HEADER*)raw_image)->e_magic==IMAGE_DOS_SIGNATURE,"DOS header");
    headers=(IMAGE_NT_HEADERS*)(raw_image+((IMAGE_DOS_HEADER*)raw_image)->e_lfanew);
    require(headers->Signature==IMAGE_NT_SIGNATURE &&
        headers->FileHeader.Machine==IMAGE_FILE_MACHINE_I386 &&
        headers->OptionalHeader.ImageBase==0x400000 &&
        headers->OptionalHeader.AddressOfEntryPoint==0x28B9D2 &&
        headers->OptionalHeader.SizeOfImage==0x306000,"canonical PE identity");
    memcpy(target_image,raw_image,headers->OptionalHeader.SizeOfHeaders);
    sections=IMAGE_FIRST_SECTION(headers);
    for (unsigned n=0;n<headers->FileHeader.NumberOfSections;++n) {
        require(sections[n].VirtualAddress+sections[n].Misc.VirtualSize<=0x306000 &&
            sections[n].PointerToRawData+sections[n].SizeOfRawData<=3129344,"section bounds");
        memcpy(target_image+sections[n].VirtualAddress,
            raw_image+sections[n].PointerToRawData,sections[n].SizeOfRawData);
    }
    IMAGE_IMPORT_DESCRIPTOR *imports=(IMAGE_IMPORT_DESCRIPTOR*)(target_image+
        headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);
    for (;imports->Name;++imports) {
        const char *name=(char*)(target_image+imports->Name);
        bool kernel=_stricmp(name,"KERNEL32.dll")==0;
        HMODULE dll=kernel?LoadLibraryA(name):0;
        require(!kernel || dll!=0,"kernel32 load");
        IMAGE_THUNK_DATA *lookup=(IMAGE_THUNK_DATA*)(target_image+imports->OriginalFirstThunk);
        IMAGE_THUNK_DATA *iat=(IMAGE_THUNK_DATA*)(target_image+imports->FirstThunk);
        for (;lookup->u1.AddressOfData;++lookup,++iat) {
            if (!kernel) {
                iat->u1.Function=0;++blocked_imports;
                continue;
            }
            const char *symbol=IMAGE_SNAP_BY_ORDINAL(lookup->u1.Ordinal)?
                (const char*)IMAGE_ORDINAL(lookup->u1.Ordinal):
                (char*)((IMAGE_IMPORT_BY_NAME*)(target_image+lookup->u1.AddressOfData))->Name;
            FARPROC address=GetProcAddress(dll,symbol);
            require(address!=0,"kernel32 export resolution");
            iat->u1.Function=(unsigned long)address;++kernel_imports;
        }
    }
    for (unsigned n=0;n<headers->FileHeader.NumberOfSections;++n) {
        DWORD flags=sections[n].Characteristics;
        DWORD permissions=(flags&IMAGE_SCN_MEM_EXECUTE)?PAGE_EXECUTE_READ:
            (flags&IMAGE_SCN_MEM_WRITE)?PAGE_READWRITE:PAGE_READONLY;
        protect(target_image+sections[n].VirtualAddress,sections[n].Misc.VirtualSize,permissions);
    }
    protect(target_image,headers->OptionalHeader.SizeOfHeaders,PAGE_READONLY);
    require(text_unchanged(),"initial mapped text differs");
}
static void initialize_runtime() {
    ((void (__cdecl*)())0x6959A1)(); // Actual security-cookie initializer.
    // Reproduce only the observed OS-data stores at 68B85B..68B8B1.
    OSVERSIONINFOA version;ZeroMemory(&version,sizeof(version));
    version.dwOSVersionInfoSize=sizeof(version);
    require(GetVersionExA(&version)!=0,"OS version query");
    *(unsigned*)0x6FD3D8=version.dwPlatformId;
    *(unsigned*)0x6FD3E0=(version.dwMajorVersion<<8)+version.dwMinorVersion;
    *(unsigned*)0x6FD3E4=version.dwMajorVersion;
    *(unsigned*)0x6FD3E8=version.dwMinorVersion;
    *(unsigned*)0x6FD3DC=(version.dwBuildNumber&0x7fff)|(version.dwPlatformId==2?0:0x8000);
    require(((int (__cdecl*)(int))0x695947)(1)==1,"target CRT heap initialization");
    require(((int (__cdecl*)())0x68EDFA)()==1,"target CRT thread/lock initialization");
}
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
