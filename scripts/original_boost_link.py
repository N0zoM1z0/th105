"""Link only the verified original Boost TUs and original pinned CRT/SDK.

One genuine public basic_regex constructor roots the library graph. No game
implementation, synthetic caller, private export, COFF barrier or stub is used.
"""
import hashlib
import json
import os
from pathlib import Path
import subprocess
import linked_pe as core
import upstream_boost as base
import upstream_boost_sources as extra

ROOT = Path(__file__).resolve().parents[1]
OUTPUT = ROOT/'build/origin-anchors/original-boost-link'
PUBLIC_ROOT = '??0?$basic_regex@DU?$regex_traits@DV?$w32_regex_traits@D@boost@@@boost@@@boost@@QAE@PBDI@Z'
USER32_PATH = 'PlatformSDK/Lib/User32.Lib'
USER32_SHA256 = 'ad95124a0182d955a0065f5817ee92746f602d0535a1c359a2789c422b830c2a'


def source_units():
    units=[dict(kind='probe',source=base.RELEASE_INSTANCE_PROBE,boost_regex_headers=True,
                boost_regex_instances=True,include_dirs=[base.FOLDER])]
    units += [dict(kind='probe',source=probe,boost_regex_headers=True,
                   boost_regex_source_tu=name,include_dirs=[base.FOLDER,extra.INCLUDE])
              for name,probe in extra.PROBES.items()]
    return units


def verified_inputs(root=ROOT):
    lines=[line.split('//',1)[0].strip()for line in (root/base.RELEASE_INSTANCE_PROBE).read_text().splitlines()]
    if [s for s in lines if s]!=['#define NDEBUG','#include "../../'+base.INSTANCE_PATH+'"']:
        raise ValueError('original library instance wrapper has extra source or flags')
    inputs={root/'scripts/original_boost_link.py',root/'scripts/linked_pe.py',root/'config/tools.lock.toml'}
    for unit in source_units():
        inputs.update(base.inputs(unit,root));inputs.add(root/unit['source'])
    return sorted(inputs)


def library_paths(tools):
    user=tools/USER32_PATH
    if core.sha(user)!=USER32_SHA256:raise ValueError('original User32 import library changed')
    return [tools/p for p in core.STATIC_LIBS]+[user]


def link_flags():
    return ['/nologo','/DLL','/LTCG','/NODEFAULTLIB','/OPT:NOICF','/OPT:REF',
            '/BASE:0x10000000','/EXPORT:'+PUBLIC_ROOT]


def build(output=OUTPUT):
    output=Path(output).resolve();output.relative_to(ROOT)
    source_inputs=verified_inputs();tools,pins=core.pinned_tools(True);libraries=library_paths(tools)
    env=os.environ.copy();env.update(WINEPREFIX=env.get('TH105_WINEPREFIX',str(ROOT/'.tools/wine-msvc8')),
                                   WINEARCH='win32',WINEDEBUG='-all')
    for v in ('CL','_CL_','LINK','_LINK_','INCLUDE','LIB','LIBPATH'):env[v]=''
    def win(path):
        return subprocess.run(['winepath','-w',str(path)],cwd=ROOT,env=env,check=True,
                              capture_output=True,text=True).stdout.strip()
    output.mkdir(parents=True,exist_ok=True);commands=[];objects=[]
    def run(label,command):
        commands.append(command);log=output/(label+'.log')
        with log.open('w')as stream:r=subprocess.run(command,cwd=ROOT,env=env,stdout=stream,stderr=subprocess.STDOUT)
        core.check_build_phase(label,r.returncode,log)
    for i,unit in enumerate(source_units()):
        obj=output/f'original-{i}.obj';objects.append(obj)
        cmd=['wine',str(tools/'bin/cl.exe'),'/nologo','/c','/O2','/GL','/GS','/GR','/EHsc','/MT']
        cmd+=['/I'+win(p)for p in [ROOT/'src',tools/'include',tools/'PlatformSDK/Include',*[ROOT/d for d in unit['include_dirs']]]]
        cmd+=['/Fo'+win(obj),win(ROOT/unit['source'])];run(f'compile-{i}',cmd)
    image=output/'OriginalBoost.dll';maps=output/'OriginalBoost.map'
    command=['wine',str(tools/'bin/link.exe'),*link_flags(),'/MAP:'+win(maps),'/OUT:'+win(image)]
    command += [win(p)for p in objects+libraries];run('link',command)
    record=dict(schema_version=1,target_sha256=core.comparator().verify_target(),compiler_pins=pins,
        source_inputs={str(p.relative_to(ROOT)):core.sha(p)for p in source_inputs},
        libraries={str(p.relative_to(tools)):core.sha(p)for p in libraries},commands=commands,
        objects={p.name:core.sha(p)for p in objects},exported_root=PUBLIC_ROOT,
        image_sha256=core.sha(image),map_sha256=core.sha(maps))
    (output/'build.json').write_text(json.dumps(record,indent=2)+'\n')
    return image,record


if __name__=='__main__':
    image,record=build();print(json.dumps(dict(image=str(image),image_sha256=record['image_sha256'])))
