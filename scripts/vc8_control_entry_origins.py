"""Original debugger hook and two CRT C-initialization entries with real roles."""
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
from linked_bad_alloc_origins import import_at
from xiph_owned_switch_origins import zero_initialized_counter
from workflow_manifest import load_manifest
from linked_logic_error_origins import require,digest
ROOT=Path(__file__).resolve().parents[1]
ANCHORS=ROOT/'config/vc8-control-entry-origin-anchors.toml'
OUTPUT=ROOT/'build/origin-anchors/vc8-control-entries'
ARCHIVE='3bc6c5b90f8507964839fd0264d8565c3b766d01f9efcad336532a11e8f06ac3'
FILTER='?__CxxUnhandledExceptionFilter@@YGJPAU_EXCEPTION_POINTERS@@@Z'
IAT='__imp__SetUnhandledExceptionFilter@4'
HASHES={'dbghook.obj':'0234cb8bfd298afb73d795b2500bfee09a5c6802bdf9fed4bc3cff094596f3ef','cpu_disp.obj':'188965ae890a819307b7431044ed68da143c12c772b1352d32bc174c8d705533','unhandld.obj':'bd5dff3a483c0df4073855f94993a1cdbdb1c15a62e8da16748e87e4783176c8','crt0dat.obj':'72a9f77fb45c08985c23679d0ee1fb4ab4793cfa81d4149902e7c58eacfade14','wincrt0.obj':'bc2c6d12db413b4a29031851855b3a1235e7037276008da6b84edf6671ed7c0a'}
CONTRACT={
 '0x00690987':dict(size=8,symbol='__crt_debugger_hook',unit='vc8-original-debugger-hook',member='dbghook.obj',refs=[(2,6,'__debugger_hook_dummy')],calls={},bindings=['__debugger_hook_dummy=vc8_debugger_hook_dummy']),
 '0x00695025':dict(size=14,symbol='___CxxSetUnhandledExceptionFilter',unit='vc8-original-cxx-filter-registration',member='unhandld.obj',refs=[(1,6,FILTER),(7,6,IAT)],calls={},bindings=[FILTER+'=vc8_cxx_unhandled_filter',IAT+'='+IAT]),
 '0x0069C9D8':dict(size=13,symbol='___sse2_available_init',unit='vc8-original-sse2-initializer',member='cpu_disp.obj',refs=[(1,20,'__get_sse2_info'),(6,6,'___sse2_available')],calls={'__get_sse2_info':0x69c978},bindings=['___sse2_available=vc8_sse2_available'])}
ENTRIES=[0,0x68aeb3,0x68d05f,0x69098f,0x6916e1,0x69c9d8,0x695025,0]
SUPPORT=[('cpu_disp.obj','__get_sse2_info',0x69c978,96,[(78,20,'_has_osfxsr_set')],{'_has_osfxsr_set':0x69c928}),('unhandld.obj',FILTER,0x694fe8,61,[(52,20,'?terminate@@YAXXZ')],{'?terminate@@YAXXZ':0x68fc12}),('crt0dat.obj','__initterm_e',0x68e1ee,32,[],{})]

def formal(at,k):
    f=dict(address=at,symbol_base=k['symbol'],dir32_targets=k['bindings'])
    if k['calls']:f['rel32_targets']=[n+'='+f'0x{to:08X}'for n,to in k['calls'].items()]
    return f

def validate_spec(spec,selected,units,target_sha):
    require(set(spec)=={'schema_version','target_sha256','anchors'}and type(spec['schema_version'])is int and spec['schema_version']==1 and spec['target_sha256']==target_sha,'CRT control schema/target differs')
    aa=spec['anchors'];by={r['address']:r for r in selected};require(len(aa)==len(selected)==len(CONTRACT)and set(by)==set(CONTRACT)and {a['address']for a in aa}==set(CONTRACT),'CRT control complete selection differs')
    for a in aa:
        k=CONTRACT[a['address']];require(set(a)=={'address','size','symbol','unit','sha256'}and type(a['size'])is int and a['size']==k['size']and int(by[a['address']]['size'],0)==k['size']and a['symbol']==k['symbol']and a['unit']==k['unit']and isinstance(a['sha256'],str)and len(a['sha256'])==64 and all(x in '0123456789abcdef'for x in a['sha256']),'CRT control whole member identity/extent differs')
        u=units[k['unit']];require(u.get('kind')=='msvc_prebuilt'and u.get('source')=='scripts/extract-msvc-library-object.py'and u.get('profile')=='vc8-sp1-libcmt'and u.get('enable_gs')is False and u.get('toolchain_library')=='libcmt'and u.get('toolchain_object')==k['member']and u.get('toolchain_archive_sha256')==ARCHIVE and u['functions']==[formal(a['address'],k)],'CRT control original member/provider/data contract differs')
    return aa

def common_word(path,reader,name,address,game):
    raw=path.read_bytes();ptr,count=struct.unpack_from('<II',raw,8);found=[(i,s)for i,s in reader.cf.symbols.items()if s.name==name];require(len(found)==1,'CRT control common definition is ambiguous');i,s=found[0];rec=raw[ptr+18*i:ptr+18*(i+1)]
    require(s.section_number==0 and s.value==4 and rec[14:18]==bytes([0,0,2,0]),'CRT control needs actual four-byte external common storage')
    require(zero_initialized_counter(game,address,4)==bytes(4),'CRT control common word is not native zero-fill');return dict(symbol=name,address=hex(address),size=4,storage='COFF common/native zero-fill; no raw BSS read')

def registration(reader,section,symbol,target,slot,read):
    s=reader.section('_pinit');require(reader.symbol('_pinit').value==0 and s.name==section and s.raw_size==4 and s.characteristics&0x40000000 and not s.characteristics&0xa0000000 and reader.raw('_pinit',4)==bytes(4)and reader.refs('_pinit',4)==[(0,6,symbol)],'CRT control original registration record differs')
    require(struct.unpack('<I',read(slot,4))[0]==target,'CRT control actual registration slot differs');return dict(source_section=section,symbol=symbol,native_slot=hex(slot),native_target=hex(target))

def qualify(units,anchors,rows,read,c,game):
    paths={k['member']:ROOT/units[k['unit']]['object']for k in CONTRACT.values()};paths.update({n:OUTPUT/n for n in ['crt0dat.obj','wincrt0.obj']});rr={}
    for name,p in paths.items():require(digest(p.read_bytes())==HASHES[name],'CRT control original object hash differs: '+name);rr[name]=Reader(p)
    known=c.known_data_targets();common=[common_word(paths['dbghook.obj'],rr['dbghook.obj'],'__debugger_hook_dummy',0x7039cc,game),common_word(paths['cpu_disp.obj'],rr['cpu_disp.obj'],'___sse2_available',0x7039c8,game)]
    for key,at in [('vc8_debugger_hook_dummy',0x7039cc),('vc8_sse2_available',0x7039c8)]:require(known.get(key)==(at,bytes(4),frozenset({0}),'address'),'CRT control exact common binding differs')
    require(import_at(game,0x6c0154)==[('kernel32.dll','SetUnhandledExceptionFilter')],'CRT control actual Windows import differs')
    require(known.get(IAT)==(0x6c0154,read(0x6c0154,4),frozenset({0}),'literal')and core.readonly_data(game,0x6c0154,4)==read(0x6c0154,4),'CRT control whole IAT binding differs')
    require(known.get('vc8_cxx_unhandled_filter')==(0x694fe8,read(0x694fe8,61),frozenset({0}),'address'),'CRT control typed callback binding differs')
    by={r['address']:r for r in rows};origins={r['address']:r for r in csv.DictReader((ROOT/'config/function-origins.csv').open())}
    for at,name,size in [(0x69c978,'__get_sse2_info',96),(0x69c928,'_has_osfxsr_set',80),(0x694fe8,FILTER,61),(0x68fc12,'?terminate@@YAXXZ',57),(0x68e1ee,'__initterm_e',32),(0x68e281,'__cinit',146)]:
        key=f'0x{at:08X}';require(by[key]['current_name']==name and int(by[key]['size'],0)==size and origins[key]['disposition']=='exclude'and origins[key]['origin']=='vc8_runtime','CRT control named provider ownership differs')
    support=[]
    for member,sym,at,size,refs,calls in SUPPORT:
        r=rr[member];require(r.symbol(sym).value==0 and r.section(sym).name=='.text'and r.section(sym).raw_size==size and r.refs(sym,size)==refs,'CRT control complete support extent/relocations differ')
        raw=r.raw(sym,size)
        for off,k,n in refs:require(struct.unpack_from('<I',raw,off)[0]==0,'CRT control support call addend differs')
        b=c.coff_symbol_bytes(paths[member],sym,at,size,calls,{});require(b==read(at,size),'CRT control whole support body differs');ins=core.decode_closed_body(b,at);support.append(dict(symbol=sym,address=hex(at),size=size,sha256=digest(b),instructions=len(ins)))
    caller=rr['crt0dat.obj'];require(caller.section('__cinit').raw_size==146 and caller.refs('__cinit',15,40)==[(1,6,'___xi_z'),(6,6,'___xi_a'),(11,20,'__initterm_e')],'CRT control actual C-table caller roles differ');site=bytearray(caller.raw('__cinit',15,40))
    for off in [1,6,11]:require(struct.unpack_from('<I',site,off)[0]==0,'CRT control C-table caller addend differs')
    struct.pack_into('<I',site,1,0x6c03b8);struct.pack_into('<I',site,6,0x6c039c);struct.pack_into('<i',site,11,0x68e1ee-(0x68e2a9+15));require(bytes(site)==read(0x68e2a9,15),'CRT control complete C-table caller site differs')
    table=read(0x6c039c,32);require(table==struct.pack('<8I',*ENTRIES)and core.readonly_data(game,0x6c039c,32)==table,'CRT control full native C initialization range/sentinels differ')
    for at in ENTRIES[1:5]:require(origins[f'0x{at:08X}']['disposition']=='exclude'and origins[f'0x{at:08X}']['origin']=='vc8_runtime','CRT control other C-table entry lacks existing runtime ownership')
    regs=[registration(rr['cpu_disp.obj'],'.CRT$XIC','___sse2_available_init',0x69c9d8,0x6c03b0,read),registration(rr['wincrt0.obj'],'.CRT$XIY','___CxxSetUnhandledExceptionFilter',0x695025,0x6c03b4,read)]
    facts=[]
    for a in anchors:
        k=CONTRACT[a['address']];r=rr[k['member']];at=int(a['address'],0);size=k['size'];sym=k['symbol'];require(r.symbol(sym).value==0 and r.section(sym).name=='.text'and r.section(sym).raw_size==size and r.refs(sym,size)==k['refs'],'CRT control whole root extent/relocations differ');raw=r.raw(sym,size)
        for off,kind,n in k['refs']:require(struct.unpack_from('<I',raw,off)[0]==0,'CRT control root relocation addend differs')
        bindings=dict(x.split('=',1)for x in k['bindings']);b=c.coff_symbol_bytes(paths[k['member']],sym,at,size,k['calls'],known,bindings);require(len(b)==size and b==read(at,size)and digest(b)==a['sha256'],'CRT control whole canonical root differs');ins=core.decode_closed_body(b,at)
        hits=[x['address']for x in rows if int(x['size'],0)==size and c.coff_symbol_bytes(paths[k['member']],sym,int(x['address'],0),size,k['calls'],known,bindings)==read(int(x['address'],0),size)];require(hits==[a['address']],'CRT control complete root is not inventory-unique');facts.append(dict(address=a['address'],size=size,symbol=sym,sha256=digest(b),instructions=len(ins),inventory_hits=hits,masked_bytes=0,unequal_bytes=0))
    return dict(anchors=facts,support=support,common_storage=common,registrations=regs,c_table=dict(start='0x006C039C',end='0x006C03B8',size_with_end_sentinel=32,entries=[hex(x)for x in ENTRIES],sha256=digest(table)),caller_site=dict(address='0x0068E2A9',size=15,sha256=digest(site)),scope='35 new CRT bytes only; no support/caller/table/IAT/BSS/remote-SEH/authored credit; registration witness does not uniquely identify original startup object or whole-runtime patch version')

def validate(rule,selected,rows,read,target_sha):
    try:
        require(ROOT/str(rule['vc8_control_entry_anchor_file'])==ANCHORS,'unreviewed CRT control anchor path');units=load_manifest()['units'];aa=validate_spec(tomllib.loads(ANCHORS.read_text()),selected,units,target_sha)
        archive=(ROOT/'.tools/msvc80-sp1/lib/libcmt.lib').read_bytes();require(digest(archive)==ARCHIVE,'CRT control original archive differs');sp=importlib.util.spec_from_file_location('control_extract',ROOT/'scripts/extract-msvc-library-object.py');m=importlib.util.module_from_spec(sp);sp.loader.exec_module(m);members=m.archive_members(archive);OUTPUT.mkdir(parents=True,exist_ok=True)
        for name in ['crt0dat.obj','wincrt0.obj']:
            found=[b for n,b in members if Path(n).name==name];require(len(found)==1 and digest(found[0])==HASHES[name],'CRT control original support member differs');(OUTPUT/name).write_bytes(found[0])
        builds=[build.build_unit(a['unit'],units[a['unit']],True,target_sha)for a in aa];c=core.comparator();c.verify_target();game=pefile.PE(str(c.TARGET));proof=qualify(units,aa,rows,read,c,game);reports=[]
        for a in aa:
            code,results=build.compare_unit(units[a['unit']],True);require(code==0 and len(results)==1 and results[0]['result']=='exact','CRT control formal comparison failed');reports+=results
        proof.update(builds=builds,comparisons=reports,member_sha256=HASHES,validator_sha256=core.sha(Path(__file__)),anchor_sha256=core.sha(ANCHORS));(OUTPUT/'proof.json').write_text(json.dumps(proof,indent=2)+'\n');return []
    except (OSError,ValueError,KeyError,TypeError,RuntimeError,struct.error,pefile.PEFormatError)as exc:return [str(rule['id'])+': '+str(exc)]

def main():
    c=core.comparator();sha=c.verify_target();rows=list(csv.DictReader((ROOT/'config/functions.csv').open()));result=validate(dict(id='vc8-original-control-entries-106a',vc8_control_entry_anchor_file=str(ANCHORS.relative_to(ROOT))),[r for r in rows if r['address']in CONTRACT],rows,c.target_bytes,sha);print(json.dumps(dict(errors=result)));return bool(result)
if __name__=='__main__':raise SystemExit(main())
