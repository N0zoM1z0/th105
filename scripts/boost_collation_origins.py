"""Whole original Boost collation code plus its complete string-pointer tables.

This narrow contract does not alter ordinary DIR32 mapping or mask any bytes.
"""
import csv
import hashlib
import importlib.util
import json
from pathlib import Path
import re
import struct
import sys
import tomllib
import capstone
import pefile
from build import build_unit
from workflow_manifest import ROOT, compiler_sha256
from rank_retained_exact import read_coff_function
import upstream_boost_sources as extra
import linked_pe as core

ANCHOR = ROOT/'config/boost-collation-origin-anchors.toml'
OUTPUT = ROOT/'build/origin-anchors/boost-collation'
COMPILER = '71c93ca5bddc9b2816d0e053cac2b952f926f6b9321fab6b1ab6e8603621324c'
SYMBOL = '?lookup_default_collate_name@re_detail@boost@@YI?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ABV34@@Z'
TABLE_NAMES = {'?def_coll_names@re_detail@boost@@3PAPBDA':'def_coll_names',
               '?def_multi_coll@re_detail@boost@@3PAPBDA':'def_multi_coll'}


def source_literals(text,name):
    match=re.search(r'const char\*\s+'+re.escape(name)+r'\[\]\s*=\s*\{(.*?)\};',text,re.S)
    if not match:raise ValueError('original collation table declaration missing')
    body=match.group(1);pattern=r'"(?:\\.|[^"\\])*"'
    if re.sub(pattern,'',body).strip(' \t\r\n,'):
        raise ValueError('collation table is not a complete literal-only initializer')
    values=[json.loads(v).encode('ascii')+b'\0'for v in re.findall(pattern,body)]
    if not values or values[-1]!=b'\0' or any(b'\0'in v[:-1]for v in values)or any(v==b'\0'for v in values[:-1]):
        raise ValueError('collation table needs exactly its final empty sentinel')
    return values


def canonicalize(body,relocs,address,tables,calls,expected):
    actual=[dict(offset=o,kind=k,symbol=s,addend=struct.unpack_from('<i',body,o)[0])for o,k,s in relocs]
    if actual!=expected:raise ValueError('collation relocation fields changed')
    result=bytearray(body);occupied=set()
    for r in actual:
        off,kind,sym,add=r['offset'],r['kind'],r['symbol'],r['addend']
        if not 0<=off<=len(body)-4 or occupied.intersection(range(off,off+4)):
            raise ValueError('collation relocation overlaps or escapes')
        occupied.update(range(off,off+4))
        if kind==6:
            if sym not in tables or add not in (0,4):raise ValueError('unowned collation array reference')
            struct.pack_into('<I',result,off,tables[sym]+add)
        elif kind==20:
            if sym not in calls or add or core.comparator().rel32_operand_kind(body,off)!='call':
                raise ValueError('unowned collation code call')
            struct.pack_into('<i',result,off,calls[sym]-(address+off+4))
        else:raise ValueError('unsupported collation relocation')
    return bytes(result)


def inspect_cfg(code,address,call_offsets):
    md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);md.detail=True
    rows=list(md.disasm(code,address));by={r.address:r for r in rows}
    if sum(r.size for r in rows)!=len(code):raise ValueError('incomplete collation decode')
    seen=set();todo=[address];calls=set();returns=[]
    while todo:
        at=todo.pop()
        if at in seen:continue
        if at not in by:raise ValueError('collation CFG leaves complete body')
        seen.add(at);r=by[at]
        if r.group(capstone.CS_GRP_RET):
            if r.mnemonic!='ret' or r.op_str:raise ValueError('unexpected collation return ABI')
            returns.append(at);continue
        if r.group(capstone.CS_GRP_CALL):
            if r.size!=5 or r.bytes[0]!=0xe8:raise ValueError('indirect collation call')
            calls.add(at-address+1)
        if r.group(capstone.CS_GRP_JUMP):
            if not r.operands or r.operands[0].type!=capstone.x86.X86_OP_IMM:
                raise ValueError('indirect collation jump')
            dest=r.operands[0].imm
            if dest not in by:raise ValueError('external collation branch')
            todo.append(dest)
            if r.mnemonic=='jmp':continue
        todo.append(at+r.size)
    if len(seen)!=len(rows)or calls!=set(call_offsets)or not returns:
        raise ValueError('collation complete reachability/call set differs')
    return dict(instructions=len(rows),returns=[hex(a)for a in sorted(returns)])


def load_coff(path):
    spec=importlib.util.spec_from_file_location('boost_collation_coff',ROOT/'scripts/compare-giant-action-switches.py')
    module=importlib.util.module_from_spec(spec);sys.modules[spec.name]=module;spec.loader.exec_module(module)
    return module.CoffObject(path)


def symbol(cf,name):
    found=[s for s in cf.symbols.values()if s.name==name and s.section_number>0]
    if len(found)!=1:raise ValueError('collation COFF symbol is not uniquely defined')
    return found[0]


def verify_table(cf,table,values,pe,read):
    name=table['symbol'];a=int(table['address'],0);count=table['entries'];size=4*count
    if len(values)!=count:raise ValueError('collation initializer extent changed')
    raw=read(a,size)
    if hashlib.sha256(raw).hexdigest()!=table['sha256']:raise ValueError('native collation pointer table changed')
    sec=pe.get_section_by_rva(a-pe.OPTIONAL_HEADER.ImageBase)
    if (sec is None or sec.Name.rstrip(b'\0')!=b'.data' or sec.Characteristics&0x20000000
            or a+size>pe.OPTIONAL_HEADER.ImageBase+sec.VirtualAddress+sec.SizeOfRawData):
        raise ValueError('collation pointer array is not complete initialized data')
    s=symbol(cf,name);section=cf.sections[s.section_number-1]
    if section.name!='.data' or s.value+size>section.raw_size:raise ValueError('source collation array extent differs')
    rels={}
    for i in range(section.reloc_count):
        off,idx,kind=struct.unpack('<IIH',cf._read_raw(section.reloc_offset+10*i,10))
        if s.value<=off<s.value+size:
            if off-s.value in rels:raise ValueError('duplicate collation cell relocation')
            rels[off-s.value]=(cf.symbols[idx],kind)
    if set(rels)!=set(range(0,size,4)):raise ValueError('collation must own every pointer cell')
    for index,value in enumerate(values):
        ref,kind=rels[4*index]
        if kind!=6 or ref.section_number<=0:raise ValueError('collation cell is not a literal pointer')
        literal_section=cf.sections[ref.section_number-1]
        add=struct.unpack('<I',cf._read_raw(section.raw_offset+s.value+index*4,4))[0]
        if (literal_section.name!='.rdata' or literal_section.characteristics&0xa0000000
                or ref.value+add+len(value)>literal_section.raw_size):raise ValueError('source collation literal escapes readonly storage')
        literal=cf._read_raw(literal_section.raw_offset+ref.value+add,len(value))
        dest=struct.unpack_from('<I',raw,4*index)[0];target_section=pe.get_section_by_rva(dest-pe.OPTIONAL_HEADER.ImageBase)
        if (target_section is None or target_section.Name.rstrip(b'\0')!=b'.rdata'
                or target_section.Characteristics&0xa0000000
                or dest+len(value)>pe.OPTIONAL_HEADER.ImageBase+target_section.VirtualAddress+target_section.SizeOfRawData):
            raise ValueError('native collation literal escapes readonly storage')
        if literal!=value or read(dest,len(value))!=value:raise ValueError('collation source/native string cell differs')
    return dict(symbol=name,address=hex(a),entries=count,bytes=size,sha256=table['sha256'],
                strings_sha256=hashlib.sha256(b''.join(struct.pack('<I',len(v))+v for v in values)).hexdigest())


def validate_contract(spec,selected,target_sha):
    if (set(spec)!={'schema_version','target_sha256','compiler_sha256','anchors','tables','calls','relocations'}
            or type(spec['schema_version'])is not int or spec['schema_version']!=1
            or spec['target_sha256']!=target_sha or spec['compiler_sha256']!=COMPILER):
        raise ValueError('collation target/compiler/schema differs')
    anchors=spec['anchors']
    if (not isinstance(anchors,list)or len(anchors)!=1 or len(selected)!=1
            or set(anchors[0])!={'address','size','symbol','sha256'}
            or anchors[0]['address']!='0x006B4820' or anchors[0]['address']!=selected[0]['address']
            or anchors[0]['symbol']!=SYMBOL or type(anchors[0]['size'])is not int
            or anchors[0]['size']!=455 or anchors[0]['size']!=int(selected[0]['size'],0)
            or not re.fullmatch('[0-9a-f]{64}',anchors[0]['sha256'])):
        raise ValueError('collation selection/source identity differs')
    expected_tables={list(TABLE_NAMES)[0]:('0x006F9840',129),list(TABLE_NAMES)[1]:('0x006F9A48',22)}
    if not isinstance(spec['tables'],list)or len(spec['tables'])!=2:
        raise ValueError('collation needs both complete original tables')
    seen=set()
    for t in spec['tables']:
        if (set(t)!={'symbol','address','entries','sha256'}or t['symbol']in seen
                or t['symbol']not in expected_tables or type(t['entries'])is not int
                or (t['address'],t['entries'])!=expected_tables[t['symbol']]
                or not re.fullmatch('[0-9a-f]{64}',t['sha256'])):
            raise ValueError('collation table identity/extent differs')
        seen.add(t['symbol'])
    if len(spec['calls'])!=3 or any(set(r)!={'symbol','address'}for r in spec['calls']):
        raise ValueError('collation requires original three named callees')
    if len(spec['relocations'])!=9 or any(set(r)!={'offset','kind','symbol','addend'}
            or any(type(r[k])is not int for k in ('offset','kind','addend'))for r in spec['relocations']):
        raise ValueError('collation requires all nine typed relocation fields')
    return anchors[0]


def replay(spec,selected,rows,read,target_sha):
    a=validate_contract(spec,selected,target_sha)
    if compiler_sha256()!=COMPILER:raise ValueError('collation compiler changed')
    address=int(a['address'],0);size=a['size']
    tables={t['symbol']:int(t['address'],0)for t in spec['tables']}
    calls={r['symbol']:int(r['address'],0)for r in spec['calls']}
    if len(calls)!=len(spec['calls']):raise ValueError('duplicate collation callee')
    unit=dict(kind='probe',source=extra.PROBES['regex_traits_defaults.cpp'],
              object='build/origin-anchors/boost-collation/Defaults.obj',profile='vc8-sp1-probe-o2',
              enable_gs=True,boost_regex_headers=True,boost_regex_source_tu='regex_traits_defaults.cpp',
              include_dirs=[extra.BASE,extra.INCLUDE],functions=[])
    provenance=build_unit('original-boost-collation-origin',unit,True,target_sha)
    obj=ROOT/unit['object'];cf=load_coff(obj);c=core.comparator();c.verify_target();pe=pefile.PE(str(c.TARGET))
    source=(ROOT/extra.FOLDER/'src/regex_traits_defaults.cpp').read_text()
    table_proofs=[verify_table(cf,t,source_literals(source,TABLE_NAMES[t['symbol']]),pe,read)for t in spec['tables']]
    actual,body,wild,rels=read_coff_function(obj,SYMBOL,None)
    if actual!=SYMBOL or len(body)!=size:raise ValueError('collation needs whole original emitted function')
    canonical=canonicalize(body,rels,address,tables,calls,spec['relocations']);native=read(address,size)
    if canonical!=native or hashlib.sha256(native).hexdigest()!=a['sha256']:
        raise ValueError('complete canonical collation bytes differ')
    cfg=inspect_cfg(canonical,address,[off for off,kind,_ in rels if kind==20])
    unique=[]
    for row in rows:
        if int(row['size'],0)!=size:continue
        at=int(row['address'],0)
        if canonicalize(body,rels,at,tables,calls,spec['relocations'])==read(at,size):unique.append(row['address'])
    if unique!=[a['address']]:raise ValueError('whole canonical collation is not inventory-unique')
    result=dict(address=a['address'],size=size,sha256=a['sha256'],cfg=cfg,tables=table_proofs,
                canonical_inventory_hits=unique,provenance=provenance,
                validator_sha256=hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
                anchor_sha256=hashlib.sha256(ANCHOR.read_bytes()).hexdigest())
    OUTPUT.mkdir(parents=True,exist_ok=True);(OUTPUT/'proof.json').write_text(json.dumps(result,indent=2)+'\n')
    return result


def validate(rule,selected,rows,read,target_sha):
    try:
        if ROOT/str(rule['boost_collation_anchor_file'])!=ANCHOR:raise ValueError('unreviewed collation anchor path')
        replay(tomllib.loads(ANCHOR.read_text()),selected,rows,read,target_sha);return []
    except (OSError,ValueError,KeyError,TypeError,RuntimeError,struct.error)as exc:return [str(rule['id'])+': '+str(exc)]


def main():
    c=core.comparator();sha=c.verify_target();spec=tomllib.loads(ANCHOR.read_text());rows=list(csv.DictReader((ROOT/'config/functions.csv').open()));selected=[r for r in rows if r['address']==spec['anchors'][0]['address']]
    r=replay(spec,selected,rows,c.target_bytes,sha);print(json.dumps({k:r[k]for k in ['address','size','sha256','cfg','tables','canonical_inventory_hits']}));return 0

if __name__=='__main__':raise SystemExit(main())
