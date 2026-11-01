"""Pinned original non-instance Boost.Regex translation units and extra header.

Separate from the unchanged184-file header package. Builds never download.
"""
import argparse
import hashlib
import json
from pathlib import Path
from upstream_boost import ROOT, FOLDER as BASE, SUPERPROJECT, verify_bytes, fetch_entry

FOLDER = '.tools/upstream/boost-regex-1.40.0-extra'
INCLUDE = FOLDER + '/include'
LOCK = 'config/boost-regex-extra-source-lock.json'
LOCK_SHA256 = '1d38b89479d5d28e74c5c5c39c569994947a70b5c2cd81da9ef28df0667ed0eb'
COMMIT = 'fa1ef1dfd4136803625e49853289ade7c2ddff0a'
PROBES = {
    'w32_regex_traits.cpp': 'scripts/probes/BoostRegexSourceW32Traits.cpp',
    'regex_raw_buffer.cpp': 'scripts/probes/BoostRegexSourceRawBuffer.cpp',
    'regex.cpp': 'scripts/probes/BoostRegexSourceRegex.cpp',
    'regex_traits_defaults.cpp': 'scripts/probes/BoostRegexSourceDefaults.cpp',
    'static_mutex.cpp': 'scripts/probes/BoostRegexSourceMutex.cpp',
    'cpp_regex_traits.cpp': 'scripts/probes/BoostRegexSourceCppTraits.cpp',
}
HEADER = 'include/boost/regex/v4/mem_block_cache.hpp'

def validate_selection(unit):
    name=unit.get('boost_regex_source_tu')
    if (not isinstance(name,str) or name not in PROBES
            or unit.get('boost_regex_headers')is not True
            or unit.get('boost_regex_instances',False)is not False
            or unit.get('source')!=PROBES[name]
            or unit.get('kind')!='probe'
            or unit.get('include_dirs')!=[BASE,INCLUDE]):
        raise ValueError('Boost source TU requires its original wrapper and two pinned packages')


def load_records(root):
    raw=(root/LOCK).read_bytes()
    if hashlib.sha256(raw).hexdigest()!=LOCK_SHA256:
        raise ValueError('Boost extra source lock differs')
    manifest=json.loads(raw)
    if (set(manifest)!={'schema_version','release','regex_commit','files'}
            or type(manifest['schema_version'])is not int or manifest['schema_version']!=1
            or manifest['release']!='boost-1.40.0' or manifest['regex_commit']!=COMMIT):
        raise ValueError('Boost extra source identity differs')
    entries=manifest['files'];wanted={'src/'+n for n in PROBES}|{HEADER,'LICENSE_1_0.txt'}
    if (not isinstance(entries,list)or len(entries)!=len(wanted)
            or {e['path']for e in entries}!=wanted):
        raise ValueError('Boost extra source inventory differs')
    for e in entries:
        license=e['path']=='LICENSE_1_0.txt'
        if (e['source_path']!=e['path']
                or e['repository']!=('https://github.com/boostorg/boost'if license else'https://github.com/boostorg/regex')
                or e['commit']!=(SUPERPROJECT if license else COMMIT)):
            raise ValueError('Boost extra source origin differs')
    return entries


def path_for(root,name):
    folder=(root/FOLDER).resolve();folder.relative_to(root.resolve())
    path=(folder/name).resolve();path.relative_to(folder)
    return path


def verified_sources(root):
    entries=load_records(root);out=[]
    for e in entries:
        p=path_for(root,e['path']);verify_bytes(p.read_bytes(),e);out.append(p)
    folder=root/FOLDER
    actual={p.relative_to(folder).as_posix()for p in folder.rglob('*')if p.is_file()}
    if actual!={e['path']for e in entries}:
        raise ValueError('Boost extra package contains unpinned files')
    return out


def verify_wrapper(unit,root):
    name=unit['boost_regex_source_tu']
    lines=[line.split('//',1)[0].strip() for line in (root/PROBES[name]).read_text().splitlines()]
    lines=[line for line in lines if line]
    if lines!=['#define NDEBUG','#include "../../'+FOLDER+'/src/'+name+'"']:
        raise ValueError('Boost source wrapper must contain only its release define and original include')


def inputs(unit,root=ROOT):
    validate_selection(unit)
    verify_wrapper(unit,root)
    return [root/LOCK,root/'scripts/upstream_boost_sources.py',*verified_sources(root)]


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--fetch',action='store_true',help='explicitly fetch missing immutable official files')
    args=parser.parse_args()
    if args.fetch:
        for e in load_records(ROOT):fetch_entry(path_for(ROOT,e['path']),e)
    files=verified_sources(ROOT)
    print('Original Boost extra source package verified:',len(files),'files')
    return 0

if __name__=='__main__':raise SystemExit(main())
