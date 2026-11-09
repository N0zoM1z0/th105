"""Origin-only all-CIL UDP initialization and its real worker graph.

Existing opaque views are connected to actual peer-removal/thread implementations.
No synthesized function body, private helper export or COFF barrier is used.
"""
import json
import os
from pathlib import Path
import re
import subprocess
import linked_pe as core
from workflow_manifest import source_dependencies
from linked_logic_error_origins import require,digest

ROOT=Path(__file__).resolve().parents[1]
OUTPUT=ROOT/'build/origin-anchors/network-initialize-link'
SOURCES={
 'peer':'src/network/NetworkWinsockPeerRemoval.cpp',
 'accept':'src/network/NetworkWinsockAccept.cpp',
 'thread':'src/platform/BattleThreadHandleRuntime.cpp',
 'main':'src/network/NetworkWinsockReceiveThread.cpp',
 'initialize':'src/network/NetworkWinsockRuntime.cpp',
 'send':'src/network/NetworkWinsockSendClient.cpp',
 'service':'src/network/NetworkWinsockProbeThread.cpp',
}
EXPORTS=['?initialize@NetworkUdpInitializeView@th105@@QAE_NPBUNetworkInitializeKey16@2@H@Z']
SDK='PlatformSDK/Lib/WS2_32.Lib'
SDK_SHA='fc1fbe94773a2bafd735b7123d31e5f9377d8381d704494a7757c8a2eccfec90'

def source_inputs():
    out=set()
    for name in SOURCES.values():out.update(source_dependencies(dict(source=name)))
    return sorted(out)

def materialize(texts):
    thread=texts['thread'];peer=texts['peer'];source=texts['main']
    tm='BattleThreadHandle::BattleThreadHandle()'
    pm='NetworkPeerMap::iterator NetworkWinsockPeerRemovalView::find_peer'
    require(thread.count(tm)==peer.count(pm)==1,'network context declaration boundary changed')
    td=thread[:thread.index(tm)]+'\n} // namespace th105\n'
    pd=peer[:peer.index(pm)]
    pd,count=re.subn(r'extern "C" __declspec\(dllimport\) int __stdcall sendto\(.*?\);','',pd,flags=re.S)
    require(count==1,'network peer sendto declaration differs')
    pd+='\n} // namespace th105\n'
    pairs=[('                    remove_peer(it->second->slot_10);',
            '                    reinterpret_cast<NetworkWinsockPeerRemovalView *>(this)->remove_peer(it->second->slot_10);'),
           ('connection_worker_13c.start(network_winsock_connection_thread, &handoff);',
            'reinterpret_cast<BattleThreadHandle *>(&connection_worker_13c)->start(network_winsock_connection_thread, &handoff);')]
    for old,new in pairs:
        require(source.count(old)==1,'network actual implementation call changed');source=source.replace(old,new)
    return td+'\n'+pd+'\n'+source

def extra_contexts(texts):
    initialize='#include "platform/BattleThreadHandle.hpp"\n'+texts['initialize']
    old='        wait_for_exit();';require(initialize.count(old)==1,'initializer actual wait call differs')
    initialize=initialize.replace(old,'        reinterpret_cast<BattleThreadHandle *>(this)->wait_for_exit();')
    peer=texts['peer'];require(peer.count('NetworkPeerMap::iterator NetworkWinsockPeerRemovalView::find_peer')==1,'service peer declaration differs')
    pd=peer[:peer.index('NetworkPeerMap::iterator NetworkWinsockPeerRemovalView::find_peer')]
    pd,count=re.subn(r'extern "C" __declspec\(dllimport\) int __stdcall sendto\(.*?\);','',pd,flags=re.S);require(count==1,'service peer sendto declaration differs')
    service=pd+'\n}\n'+texts['service'];old='owner->remove_peer(slot);';require(service.count(old)==1,'service actual remove call differs')
    service=service.replace(old,'reinterpret_cast<NetworkWinsockPeerRemovalView *>(owner)->remove_peer(slot);')
    return dict(initialize=initialize,service=service)

def build():
    c=core.comparator();target=c.verify_target();tools,pins=core.pinned_tools(False)
    paths=source_inputs();texts={k:(ROOT/v).read_text()for k,v in SOURCES.items()}
    OUTPUT.mkdir(parents=True,exist_ok=True);cpp=OUTPUT/'Receive.cpp';cpp.write_text(materialize(texts))
    generated={'main':cpp}
    for tag,content in extra_contexts(texts).items():
        path=OUTPUT/(tag+'.cpp');path.write_text(content);generated[tag]=path
    sdk=tools/SDK;require(core.sha(sdk)==SDK_SHA,'network original Winsock import library changed')
    libraries=[tools/'lib/msvcrt.lib',tools/'lib/msvcprt.lib',sdk]
    keys=['__imp__EnterCriticalSection@4','__imp__LeaveCriticalSection@4',
          '__imp__TerminateProcess@8','__imp__GetCurrentProcess@0','__imp__UnhandledExceptionFilter@4',
          '__imp__SetUnhandledExceptionFilter@4','__imp__IsDebuggerPresent@0','__imp__GetExitCodeThread@8',
          '__imp__WaitForSingleObject@8','__imp__CloseHandle@4','__imp__SetThreadPriority@8',
          '__imp__CreateThread@24','__imp__timeGetTime@0']
    keys += ['_g_winsock_ref_lock','_g_winsock_refcount','_g_winsock_data','_network_udp_socket_error','_network_udp_bind_error','__imp__CreateEventA@16','__imp__SetEvent@4','__imp__InitializeCriticalSection@4','__imp__DeleteCriticalSection@4','__imp__wsprintfA','__imp__MessageBoxA@16']
    bindings=core.target_bindings(dict(link_data_targets=[n+'='+n for n in keys]))
    data=OUTPUT/'bindings.obj';data.write_bytes(core.absolute_data_object(bindings))
    env=os.environ.copy();env.update(WINEPREFIX=env.get('TH105_WINEPREFIX',str(ROOT/'.tools/wine-msvc8')),WINEARCH='win32',WINEDEBUG='-all')
    for key in ('CL','_CL_','LINK','_LINK_','INCLUDE','LIB','LIBPATH'):env[key]=''
    def win(p):return 'Z:'+str(p).replace('/','\\')
    commands=[];objects=[]
    def run(label,command):
        log=OUTPUT/(label+'.log');commands.append(command)
        with log.open('w')as stream:r=subprocess.run(command,cwd=ROOT,env=env,stdout=stream,stderr=subprocess.STDOUT)
        core.check_build_phase(label,r.returncode,log)
    for tag,source in SOURCES.items():
        obj=OUTPUT/(tag+'.obj');objects.append(obj);path=generated.get(tag,ROOT/source)
        cmd=['wine',str(tools/'bin/cl.exe'),'/nologo','/c','/O2','/GL','/GS','/GR','/EHsc','/MT']
        cmd+=['/I'+win(p)for p in [ROOT/'src',tools/'include',tools/'PlatformSDK/Include']]
        cmd+=['/Fo'+win(obj),win(path)];run(tag+'-compile',cmd)
    image=OUTPUT/'Receive.dll';maps=image.with_suffix('.map')
    cmd=['wine',str(tools/'bin/link.exe'),'/nologo','/DLL','/NOENTRY','/LTCG','/NODEFAULTLIB','/OPT:NOICF',
         '/BASE:0x10000000','/MAP:'+win(maps),'/OUT:'+win(image)]
    cmd+=['/EXPORT:'+n for n in EXPORTS];cmd+=[win(p)for p in objects+[data]+libraries];run('link',cmd)
    record=dict(schema_version=1,target_sha256=target,compiler_pins=pins,
        source_inputs={str(p.relative_to(ROOT)):digest(p.read_bytes().replace(b'\r\n',b'\n'))for p in paths},
        generated_sources={p.name:core.sha(p)for p in generated.values()},builder_sha256=core.sha(Path(__file__)),
        libraries={str(p.relative_to(tools)):core.sha(p)for p in libraries},bindings=bindings,
        commands=commands,objects={p.name:core.sha(p)for p in objects},exports=EXPORTS,
        image_sha256=core.sha(image),map_sha256=core.sha(maps))
    (OUTPUT/'build.json').write_text(json.dumps(record,indent=2)+'\n')
    return image,record

if __name__=="__main__":
    image,record=build();print(image,record["image_sha256"])
