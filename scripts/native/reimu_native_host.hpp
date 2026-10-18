#pragma once

// Partial canonical-image loader for bounded native Reimu probes.
#define _WIN32_WINNT 0x0501
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

namespace th105_native {

static unsigned char *raw_image;
static unsigned char *target_image;
static IMAGE_NT_HEADERS *headers;
static IMAGE_SECTION_HEADER *sections;
static unsigned candidate_size;
static unsigned char *candidate_bytes;
static unsigned kernel_imports, blocked_imports;

static void require(bool condition, const char *message) {
    if (!condition) {
        fprintf(stderr,"native Reimu probe failed: %s\n",message);
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
    if (permissions==PAGE_EXECUTE_READ)
        require(FlushInstructionCache(GetCurrentProcess(),address,size)!=0,"instruction cache flush");
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
} // namespace th105_native
