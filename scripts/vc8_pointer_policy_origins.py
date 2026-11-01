"""Original encoded-pointer initializers and SIGABRT handler getter."""
import csv
import importlib.util
import json
from pathlib import Path
import struct
import tomllib
import pefile
import build
import linked_pe as core
from coff_exception_rtti import Reader
from linked_logic_error_origins import require,digest
from linked_bad_alloc_origins import import_at
from workflow_manifest import load_manifest
from vc8_sqrt_shared_origins import initialized
from xiph_owned_switch_origins import zero_initialized_counter
ROOT=Path(__file__).resolve().parents[1]
ANCHORS=ROOT/'config/vc8-pointer-policy-origin-anchors.toml'
OUTPUT=ROOT/'build/origin-anchors/vc8-pointer-policy'
ARCHIVE='3bc6c5b90f8507964839fd0264d8565c3b766d01f9efcad336532a11e8f06ac3'
HASHES={'crt0dat.obj':'72a9f77fb45c08985c23679d0ee1fb4ab4793cfa81d4149902e7c58eacfade14','abort.obj':'b2090d8bfacd08f6e1e5a9e0fef78f81313e2ba5b76686247998131dd89126d4','winsig.obj':'d6242d29f8b8ee8855c33653477bcaa4d3216ee0d1ea62e01b598ce074591b2b','rand_s.obj':'eb9a53401a1d4d2d77e3094b2bea655aedf99bd947b8b00cec2dc3b54cc0e465','winxfltr.obj':'3b8f2c7f2111c458e2887c7127c46eb140b357f3b270a72b9f959231e78f8035'}
REGIONS = [{'member': 'crt0dat.obj',
  'symbol': '__init_pointers',
  'address': 6874165,
  'size': 76,
  'refs': [[2, 20, '__encoded_null', 6875804],
           [10, 20, '__initp_heap_handler', 6883675],
           [16, 20, '__initp_misc_initcrit', 6929423],
           [22, 20, '__initp_misc_invarg', 6856729],
           [28, 20, '__initp_misc_purevirt', 6877054],
           [34, 20, '__initp_misc_rand_s', 6929413],
           [40, 20, '__initp_misc_winsig', 6928891],
           [46, 20, '__initp_misc_winxfltr', 6901811],
           [52, 20, '__initp_eh_hooks', 6880405],
           [57, 6, '__exit', 6874118],
           [62, 20, '__encode_pointer', 6875694],
           [70, 6, '__aexit_rtn', 7307072]]},
 {'member': 'abort.obj',
  'symbol': '_abort',
  'address': 6874840,
  'size': 243,
  'refs': [[15, 6, '___security_cookie', 7305864],
           [29, 6, '___abort_behavior', 7307104],
           [40, 20, '__NMSG_WRITE', 6875113],
           [46, 20, '___get_sigabrt', 6928968],
           [57, 20, '_raise', 6928981],
           [64, 6, '___abort_behavior', 7307104],
           [188, 20, '_memset', 6857792],
           [221, 6, '__imp__SetUnhandledExceptionFilter@4', 7078228],
           [231, 6, '__imp__UnhandledExceptionFilter@4', 7078224],
           [238, 20, '__exit', 6874118]]},
 {'member': 'winsig.obj',
  'symbol': '__initp_misc_winsig',
  'address': 6928891,
  'size': 25,
  'refs': [[5, 6, '_ctrlc_action', 7331324],
           [10, 6, '_ctrlbreak_action', 7331328],
           [15, 6, '_abort_action', 7331332],
           [20, 6, '_term_action', 7331336]]},
 {'member': 'winsig.obj',
  'symbol': '___get_sigabrt',
  'address': 6928968,
  'size': 13,
  'refs': [[2, 6, '_abort_action', 7331332], [7, 20, '__decode_pointer', 6875813]]},
 {'member': 'rand_s.obj',
  'symbol': '__initp_misc_rand_s',
  'address': 6929413,
  'size': 10,
  'refs': [[5, 6, '_g_pfnRtlGenRandom', 7331344]]},
 {'member': 'winxfltr.obj', 'symbol': '__initp_misc_winxfltr', 'address': 6901811, 'size': 1, 'refs': []}]
UNITS={'___get_sigabrt':'vc8-original-sigabrt-getter','__initp_misc_rand_s':'vc8-original-rand-pointer-initializer','__initp_misc_winxfltr':'vc8-original-winxfltr-initializer'}
CONTRACT={f"0x{r['address']:08X}":r for r in REGIONS[3:]}
BINDINGS={'_abort_action':'vc8_signal_abort_action','_g_pfnRtlGenRandom':'vc8_rand_s_callback'}
def formal(r):
    f=dict(address=f"0x{r['address']:08X}",symbol_base=r['symbol']);calls=[n+'='+f'0x{a:08X}'for off,k,n,a in r['refs']if k==20];data=[n+'='+BINDINGS[n]for off,k,n,a in r['refs']if k==6]
    if calls:f['rel32_targets']=calls
    if data:f['dir32_targets']=data
    return f

def validate_spec(spec,selected,units,target_sha):
    require(set(spec)=={'schema_version','target_sha256','anchors'}and type(spec['schema_version'])is int and spec['schema_version']==1 and spec['target_sha256']==target_sha,'pointer policy schema/target differs');aa=spec['anchors'];by={r['address']:r for r in selected};require(len(aa)==len(selected)==3 and set(by)==set(CONTRACT)and {a['address']for a in aa}==set(CONTRACT),'pointer policy complete selection differs')
    for a in aa:
        r=CONTRACT[a['address']];require(set(a)=={'address','size','symbol','unit','sha256'}and type(a['size'])is int and a['size']==r['size']and int(by[a['address']]['size'],0)==r['size']and a['symbol']==r['symbol']and a['unit']==UNITS[r['symbol']]and isinstance(a['sha256'],str)and len(a['sha256'])==64 and all(x in '0123456789abcdef'for x in a['sha256']),'pointer policy whole extent/identity differs');u=units[a['unit']]
        require(u.get('kind')=='msvc_prebuilt'and u.get('source')=='scripts/extract-msvc-library-object.py'and u.get('profile')=='vc8-sp1-libcmt'and u.get('enable_gs')is False and u.get('toolchain_library')=='libcmt'and u.get('toolchain_object')==r['member']and u.get('toolchain_archive_sha256')==ARCHIVE and u['functions']==[formal(r)],'pointer policy original member/call/data contract differs')
    return aa

def whole(reader,r,read):
    n=r['symbol'];size=r['size'];base=r['address'];sec=reader.section(n);require(reader.symbol(n).value==0 and sec.name=='.text'and sec.raw_size==size and reader.refs(n,size)==[(o,k,s)for o,k,s,a in r['refs']],'pointer policy complete original extent/relocations differ');raw=bytearray(reader.raw(n,size))
    for off,k,name,to in r['refs']:
        require(k in [6,20]and struct.unpack_from('<I',raw,off)[0]==0,'pointer policy needs actual zero-addend original relocation');struct.pack_into('<I',raw,off,(to-(base+off+4)if k==20 else to)&0xffffffff)
    require(bytes(raw)==read(base,size),'pointer policy whole canonical body differs');return bytes(raw)

def bss(reader,name,size,address,labels,game):
    s=reader.symbol(name);sec=reader.section(name);require(s.value==0 and sec.name=='.bss'and sec.raw_size==size and sec.raw_offset==0 and sec.reloc_count==0 and sec.characteristics&0x80,'pointer policy original BSS ownership differs')
    require(all(reader.symbol(n).section_number==s.section_number and reader.symbol(n).value==o for n,o in labels),'pointer policy BSS subobject offsets differ')
    require(size%4==0 and all(zero_initialized_counter(game,address+i,4)==bytes(4)for i in range(0,size,4)),'pointer policy full native BSS range differs');return dict(address=hex(address),size=size,labels=labels,raw_bss_read=False)

def qualify(units,anchors,rows,read,c,game):
    paths={n:OUTPUT/n for n in HASHES}
    for a in anchors:paths[CONTRACT[a['address']]['member']]=ROOT/units[a['unit']]['object']
    rr={}
    for n,p in paths.items():require(digest(p.read_bytes())==HASHES[n],'pointer policy pinned member differs: '+n);rr[n]=Reader(p)
    storage=[bss(rr['winsig.obj'],'_ctrlc_action',20,0x6fddfc,[('_ctrlc_action',0),('_ctrlbreak_action',4),('_abort_action',8),('_term_action',12),('_ConsoleCtrlHandler_Installed',16)],game),bss(rr['rand_s.obj'],'_g_pfnRtlGenRandom',4,0x6fde10,[('_g_pfnRtlGenRandom',0)],game)]
    known=c.known_data_targets()
    for key,address in [('vc8_signal_abort_action',0x6fde04),('vc8_rand_s_callback',0x6fde10)]:require(known.get(key)==(address,bytes(4),frozenset({0}),'address'),'pointer policy exact BSS binding differs')
    require(read(0x6f7a88,4)==bytes.fromhex('4ee640bb')and initialized(game,0x6f7a88,4,False)==read(0x6f7a88,4),'pointer policy existing native security-cookie initializer differs')
    ar=rr['abort.obj'];require(ar.symbol('___abort_behavior').value==0 and ar.section('___abort_behavior').name=='.data'and ar.section('___abort_behavior').raw_size==4 and not ar.refs('___abort_behavior',4),'pointer policy whole abort behavior storage differs');behavior=ar.raw('___abort_behavior',4);require(behavior==bytes.fromhex('03000000')and behavior==read(0x6f7f60,4)and initialized(game,0x6f7f60,4,False)==behavior,'pointer policy initial abort behavior differs')
    cr=rr['crt0dat.obj'];require(cr.symbol('__aexit_rtn').value==0 and cr.section('__aexit_rtn').name=='.data'and cr.section('__aexit_rtn').raw_size==4 and cr.raw('__aexit_rtn',4)==bytes(4)and cr.refs('__aexit_rtn',4)==[(0,6,'__exit')],'pointer policy actual exit callback storage differs');exitptr=struct.pack('<I',0x68e406);require(exitptr==read(0x6f7f40,4)and initialized(game,0x6f7f40,4,False)==exitptr,'pointer policy full initial exit callback differs')
    for at,name in [(0x6c0154,'SetUnhandledExceptionFilter'),(0x6c0150,'UnhandledExceptionFilter')]:require(import_at(game,at)==[('kernel32.dll',name)],'pointer policy actual Windows import differs')
    by={r['address']:r for r in rows};origins={r['address']:r for r in csv.DictReader((ROOT/'config/function-origins.csv').open())}
    for at,name,size in [(0x68e435,'__init_pointers',76),(0x68e6d8,'_abort',242),(0x69b9fb,'__initp_misc_winsig',25),(0x68eaa5,'__decode_pointer',110),(0x69ba55,'_raise',432)]:
        k=f'0x{at:08X}';require(by[k]['current_name']==name and int(by[k]['size'],0)==size and origins[k]['origin']=='vc8_runtime'and origins[k]['disposition']=='exclude','pointer policy existing owner/provider differs')
    bodies={};support=[]
    for r in REGIONS:
        b=whole(rr[r['member']],r,read);bodies[r['symbol']]=b
        if r['symbol']=='_abort':require(b[-6]==0xe8 and b[-1:]==b'\xcc','pointer policy original noreturn abort call/trap tail differs')
        else:core.decode_closed_body(b,r['address'])
        support.append(dict(symbol=r['symbol'],address=hex(r['address']),size=r['size'],sha256=digest(b)))
    # Actual source call indices bind the tiny initializer despite unrelated RET aliases.
    init=REGIONS[0];require(init['refs'][5]==[34,20,'__initp_misc_rand_s',0x69bc05]and init['refs'][7]==[46,20,'__initp_misc_winxfltr',0x695033]and REGIONS[1]['refs'][3]==[46,20,'___get_sigabrt',0x69ba48],'pointer policy actual named caller roles differ')
    facts=[]
    for a in anchors:
        r=CONTRACT[a['address']];b=bodies[r['symbol']];require(digest(b)==a['sha256'],'pointer policy root hash differs');hits=[]
        if r['size']>1:
            calls={n:to for o,k,n,to in r['refs']if k==20};over={n:BINDINGS[n]for o,k,n,to in r['refs']if k==6}
            for row in rows:
                if int(row['size'],0)==r['size']and c.coff_symbol_bytes(paths[r['member']],r['symbol'],int(row['address'],0),r['size'],calls,known,over)==read(int(row['address'],0),r['size']):hits.append(row['address'])
            require(hits==[a['address']],'pointer policy nontrivial root not inventory-unique')
        facts.append(dict(address=a['address'],size=r['size'],symbol=r['symbol'],sha256=digest(b),inventory_hits=hits,identity='actual named source caller; no uniqueness/ICF claim'if r['size']==1 else'whole original root and actual caller/storage'))
    return dict(anchors=facts,whole_bodies=support,bss=storage,scope='24 new runtime bytes only; original abort243 includes final INT3, not a closed RET body or new callable extent; no support/data/authored credit or exclusive RET/ICF claim')

def validate(rule,selected,rows,read,target_sha):
    try:
        require(ROOT/str(rule['vc8_pointer_policy_anchor_file'])==ANCHORS,'unreviewed pointer policy anchor path');units=load_manifest()['units'];aa=validate_spec(tomllib.loads(ANCHORS.read_text()),selected,units,target_sha);archive=(ROOT/'.tools/msvc80-sp1/lib/libcmt.lib').read_bytes();require(digest(archive)==ARCHIVE,'pointer policy original archive differs');sp=importlib.util.spec_from_file_location('pointer_extract',ROOT/'scripts/extract-msvc-library-object.py');m=importlib.util.module_from_spec(sp);sp.loader.exec_module(m);members=m.archive_members(archive);OUTPUT.mkdir(parents=True,exist_ok=True)
        for n in HASHES:
            found=[b for name,b in members if Path(name).name==n];require(len(found)==1 and digest(found[0])==HASHES[n],'pointer policy original support member differs');(OUTPUT/n).write_bytes(found[0])
        records=[build.build_unit(a['unit'],units[a['unit']],True,target_sha)for a in aa];c=core.comparator();c.verify_target();proof=qualify(units,aa,rows,read,c,pefile.PE(str(c.TARGET)));reports=[]
        for a in aa:
            code,results=build.compare_unit(units[a['unit']],True);require(code==0 and len(results)==1 and results[0]['result']=='exact','pointer policy formal root failed');reports+=results
        proof.update(builds=records,comparisons=reports,validator_sha256=core.sha(Path(__file__)),anchor_sha256=core.sha(ANCHORS));(OUTPUT/'proof.json').write_text(json.dumps(proof,indent=2)+'\n');return []
    except (OSError,ValueError,KeyError,TypeError,RuntimeError,struct.error,pefile.PEFormatError)as exc:return [str(rule['id'])+': '+str(exc)]
def main():
    c=core.comparator();sha=c.verify_target();rows=list(csv.DictReader((ROOT/'config/functions.csv').open()));errors=validate(dict(id='vc8-original-pointer-policy-106a',vc8_pointer_policy_anchor_file=str(ANCHORS.relative_to(ROOT))),[r for r in rows if r['address']in CONTRACT],rows,c.target_bytes,sha);print(json.dumps(dict(errors=errors)));return bool(errors)
if __name__=='__main__':raise SystemExit(main())
