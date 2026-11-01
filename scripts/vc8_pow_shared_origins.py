"""Original pow shared body with both entire dispatch owners and x87 exits."""
import csv
import importlib.util
import json
from pathlib import Path
import struct
import tomllib
import capstone
import pefile
import build
import vc8_sin_shared_origins as sin
from linked_logic_error_origins import require,digest
ROOT=sin.ROOT
UNIT='vc8-original-pow-shared-body'
ANCHORS=ROOT/'config/vc8-pow-shared-origin-anchors.toml'
OUTPUT=ROOT/'build/origin-anchors/vc8-pow-shared'
HASHES={'pow.obj':'d1f7040f292405e4ee8a96b41c61e8a7d4bf534037bf70df49f288fb772461ef',
 'pow_pentium4.obj':'95319da2ff9158e4a9b5a8e4f62805ec342325d03cd2db911b74ddbd9d09d8c1',
 '87tran.obj':'d65ab10b5044fa429c963e3d95cf4461fd6f85d69d1b8e5cc123dd759622b35c'}
CALLS=sin.sqrt.CALLS|{'__pow_pentium4':0x698109,'__CIpow_pentium4':0x6980f0,'__twoToTOS':0x690dd0,'__check_range_exit':0x690eb9,'__startTwoArgErrorHandling':0x690d70,'__powhlp':0x698cb4,'___libm_error_support':0x694a92}
SHARED_CALLS=['__load_CW','__fload_withFB','__twoToTOS','__fast_exit','__check_range_exit','__startTwoArgErrorHandling','__powhlp']
BINDINGS=['___fastflag=vc8_sqrt_fastflag','POW_name=vc8_pow_operation_name','__infinity=vc8_pow_infinity','__indefinite=vc8_sqrt_indefinite']
ALL_BINDINGS=BINDINGS+['___use_sse2_mathfcns=vc8_sin_use_sse2','__half=vc8_pow_half']
RANGES=[(0,63,'_pow'),(64,123,'__CIpow'),(123,148,'__CIpow_default'),(148,157,'__pow_default'),(157,610,'start'),(610,650,'_test_whether_TOS_is_int')]
HELPERS=[('__twoToTOS',0x690dd0,21,0),('__load_CW',0x690de5,23,21),('__fload_withFB',0x690e15,67,69),('__fast_exit',0x690e6e,13,158),('__check_range_exit',0x690eb9,163,233)]
TAIL=bytes.fromhex('8da424000000008da4240000000090')

def validate_spec(spec,selected,units,target_sha):
    require(set(spec)=={'schema_version','target_sha256','unit','anchors'}and type(spec['schema_version'])is int and spec['schema_version']==1 and spec['target_sha256']==target_sha and spec['unit']==UNIT,'pow schema/target/unit differs')
    require(len(spec['anchors'])==len(selected)==1,'pow counts one new shared body');a=spec['anchors'][0]
    require(set(a)=={'address','size','symbol','sha256'}and a['address']=='0x0068C28D'and type(a['size'])is int and a['size']==453 and a['symbol']=='start'and selected[0]['address']==a['address']and int(selected[0]['size'],0)==453 and isinstance(a['sha256'],str)and len(a['sha256'])==64 and all(c in '0123456789abcdef'for c in a['sha256']),'pow complete shared extent differs')
    u=units[UNIT]
    require(u.get('kind')=='msvc_prebuilt'and u.get('source')=='scripts/extract-msvc-library-object.py'and u.get('profile')=='vc8-sp1-libcmt'and u.get('enable_gs')is False and u.get('toolchain_library')=='libcmt'and u.get('toolchain_object')=='pow.obj'and u.get('toolchain_archive_sha256')==sin.sqrt.ARCHIVE_SHA,'pow original member differs')
    require(u['functions']==[dict(address=a['address'],symbol_base='start',rel32_targets=[n+'='+f'0x{CALLS[n]:08X}'for n in SHARED_CALLS],dir32_targets=BINDINGS)],'pow formal data/call roles differ')
    old=tomllib.loads(sin.ANCHORS.read_text());sin.validate_spec(old,[dict(address=x['address'],size=str(x['size']))for x in old['anchors']],units,target_sha)
    return a,u

def original_padding(body):
    require(body==TAIL,'pow original P4 tail differs')
    ins=list(capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32).disasm(body,0x1000))
    require([(i.mnemonic,i.op_str,i.size)for i in ins]==[('lea','esp, [esp]',7),('lea','esp, [esp]',7),('nop','',1)],'pow actual P4 alignment forms differ')

def qualify(units,anchor,rows,read,c,game):
    old=tomllib.loads(sin.ANCHORS.read_text());shared=sin.qualify(units,old['anchors'],rows,read,c,game)
    paths={n:(ROOT/units[UNIT]['object']if n=='pow.obj'else OUTPUT/n)for n in HASHES}
    for n,p in paths.items():require(digest(p.read_bytes())==HASHES[n],'pow original member hash differs: '+n)
    r=sin.sqrt.Reader(paths['pow.obj']);p=sin.sqrt.Reader(paths['pow_pentium4.obj']);tr=sin.sqrt.Reader(paths['87tran.obj']);common=sin.sqrt.Reader(sin.sqrt.OUTPUT/'common.obj');known=c.known_data_targets()
    require(r.section('__half').name=='.data'and r.section('__half').raw_size==12 and r.section('__half').reloc_count==0 and r.symbol('__half').value==0 and r.symbol('POW_name').value==8 and r.symbol('POW_name').section_number==r.symbol('__half').section_number,'pow complete small-data layout differs')
    data=r.raw('__half',12);require(data==bytes.fromhex('000000000000e03f706f7700')and data==read(0x6f7b40,12)and sin.sqrt.initialized(game,0x6f7b40,12,False)==data,'pow complete half/name data differs')
    require(known.get('vc8_pow_half')==(0x6f7b40,data[:8],frozenset({0}),'literal')and known.get('vc8_pow_operation_name')==(0x6f7b48,data[8:],frozenset({0}),'literal'),'pow half/name bindings differ')
    require(tr.symbol('__infinity').value==0 and tr.symbol('__minfinity').value==10 and tr.symbol('__infinity').section_number==tr.symbol('__minfinity').section_number and tr.section('__infinity').name=='.data'and not tr.refs('__infinity',10),'pow actual extended infinity literal boundary differs')
    inf=tr.raw('__infinity',10);require(inf==bytes.fromhex('0000000000000080ff7f')and inf==read(0x6f8b40,10)and sin.sqrt.initialized(game,0x6f8b40,10,False)==inf,'pow extended infinity literal differs')
    require(known.get('vc8_pow_infinity')==(0x6f8b40,inf,frozenset({0}),'address'),'pow independently owned external infinity binding differs')
    require(r.symbol('_pow').value==0 and r.section('_pow').name=='.text'and r.section('_pow').raw_size==650 and r.section('_pow').reloc_count==26,'pow complete original x87 owner differs')
    a=c.coff_symbol_bytes(paths['pow.obj'],'_pow',0x68c1f0,0xffffffff,CALLS,known,dict(x.split('=',1)for x in ALL_BINDINGS));require(len(a)==650 and a==read(0x68c1f0,650),'pow entire canonical x87 owner differs')
    require(r.raw('_pow',650)[63:64]==a[63:64]==b'\x90','pow actual entry separator differs')
    regions=[]
    for lo,hi,n in RANGES:
        require(r.symbol(n).value==lo and r.symbol(n).section_number==r.symbol('_pow').section_number,'pow actual source entry differs');regions.append((0x68c1f0+lo,a[lo:hi],n))
    require(p.symbol('__CIpow_pentium4').value==0 and p.symbol('__pow_pentium4').value==25 and p.section('__CIpow_pentium4').name=='.text'and p.section('__CIpow_pentium4').raw_size==2912 and p.section('__CIpow_pentium4').reloc_count==60,'pow entire original P4 owner differs')
    ds=p.section('rcp_t1');require(p.symbol('rcp_t1').value==0 and ds.name=='.rdata'and ds.raw_size==14656 and ds.reloc_count==0 and ds.characteristics&0x40000000 and not ds.characteristics&0xa0000000,'pow full coefficient storage differs')
    pd=p.raw('rcp_t1',14656);require(pd==read(0x6cf790,14656)and sin.sqrt.core.readonly_data(game,0x6cf790,14656)==pd,'pow full P4 coefficient section differs')
    labels={s.name:s.value for s in p.cf.symbols.values()if s.section_number==p.symbol('rcp_t1').section_number and not s.name.startswith('.')};ends=sorted(labels.values())+[14656];raw=p.raw('__CIpow_pentium4',2912);pdata={};overrides={};roles=[]
    for off,k,n in p.refs('__CIpow_pentium4',2912):
        if k==20:require(n=='___libm_error_support'and off==2116 and struct.unpack_from('<I',raw,off)[0]==0,'pow P4 actual call role differs');continue
        require(k==6 and n in labels,'pow P4 unexpected relocation role');add=struct.unpack_from('<I',raw,off)[0];pos=labels[n];end=next(x for x in ends if x>pos);require(0<=add<end-pos,'pow P4 addend leaves its source literal')
        key=n+'_'+str(add);pdata[key]=(0x6cf790+pos,pd[pos+add:end],frozenset({add}),'literal');overrides[n+'+0x'+format(add,'x')]=key;roles.append(dict(offset=off,symbol=n,addend=add,address=hex(0x6cf790+pos+add),size=end-pos-add))
    b=c.coff_symbol_bytes(paths['pow_pentium4.obj'],'__CIpow_pentium4',0x6980f0,0xffffffff,CALLS,pdata,overrides);require(len(b)==2912 and b==read(0x6980f0,2912),'pow entire canonical P4 owner differs')
    original_padding(raw[2897:]);original_padding(b[2897:]);require(all(s.value<2897 for s in p.cf.symbols.values()if s.section_number==p.symbol('__CIpow_pentium4').section_number),'pow source symbol enters P4 alignment')
    regions += [(0x6980f0,b[:25],'__CIpow_p4'),(0x698109,b[25:2897],'__pow_p4')]
    support=[]
    for n,at,size,offset in HELPERS:
        require(common.symbol(n).value==offset and common.section(n).name=='.text'and common.section(n).raw_size==396,'pow common helper source position differs');raw=bytearray(common.raw(n,size));refs=common.refs(n,size)
        expected=[(63,20,'__startOneArgErrorHandling'),(70,20,'__startTwoArgErrorHandling'),(83,6,'IeeeAdjU'),(99,6,'DblMin'),(116,6,'_zero'),(124,6,'IeeeAdjO'),(140,6,'DblMax'),(157,6,'_infinity')]if n=='__check_range_exit'else[]
        require(refs==expected,'pow helper relocation inventory differs')
        for off,k,symbol in refs:
            require(struct.unpack_from('<I',raw,off)[0]==0,'pow common helper unexpected addend')
            if k==6:struct.pack_into('<I',raw,off,0x6cda20+common.symbol(symbol).value)
            else:struct.pack_into('<i',raw,off,CALLS[symbol]-at-off-4)
        require(bytes(raw)==read(at,size),'pow complete common helper differs');sin.sqrt.core.decode_closed_body(bytes(raw),at);regions.append((at,bytes(raw),n));support.append(dict(symbol=n,address=hex(at),size=size,sha256=digest(raw)))
    by={x['address']:x for x in rows};origins={x['address']:x for x in csv.DictReader((ROOT/'config/function-origins.csv').open())}
    for at,n,size in [(0x68c1f0,'_pow',63),(0x68c230,'__CIpow',84),(0x68c452,'_test_whether_TOS_is_int',40),(0x6980f0,'__CIpow_pentium4',25),(0x698109,'__pow_pentium4',2872),(0x690d70,'__startTwoArgErrorHandling',23),(0x690d87,'__startOneArgErrorHandling',60),(0x698cb4,'__powhlp',318),(0x694a92,'___libm_error_support',634),(0x690dd0,'__twoToTOS',21),(0x690eb9,'__check_range_exit',163)]:
        key=f'0x{at:08X}';require(by[key]['current_name']==n and int(by[key]['size'],0)==size and origins[key]['disposition']=='exclude','pow existing owner/provider identity differs')
    graph=sin.sqrt.closed_graph(regions,[0x68c1f0,0x68c230],{0x690d70,0x690d87,0x698cb4,0x694a92})
    body=c.coff_symbol_bytes(paths['pow.obj'],'start',0x68c28d,0xffffffff,CALLS,known,dict(x.split('=',1)for x in ALL_BINDINGS));require(len(body)==493 and body==a[157:]and body[:453]==read(0x68c28d,453)and digest(body[:453])==anchor['sha256'],'pow complete shared body differs')
    hits=[x['address']for x in rows if int(x['size'],0)==453 and c.coff_symbol_bytes(paths['pow.obj'],'start',int(x['address'],0),0xffffffff,CALLS,known,dict(y.split('=',1)for y in ALL_BINDINGS))[:453]==read(int(x['address'],0),453)];require(hits==['0x0068C28D'],'pow shared body is not inventory-unique')
    return dict(anchor=dict(address=anchor['address'],size=453,sha256=digest(body[:453]),inventory_hits=hits,masked_bytes=0,unequal_bytes=0),owners=[dict(address='0x0068C1F0',size=650,sha256=digest(a)),dict(address='0x006980F0',size=2912,sha256=digest(b))],coefficient_section=dict(address='0x006CF790',size=14656,sha256=digest(pd),roles=roles),small_data=dict(address='0x006F7B40',size=12,sha256=digest(data)),external_infinity=dict(address='0x006F8B40',size=10,sha256=digest(inf)),support=support,graph=graph,common_support=shared,scope='453 new shared runtime bytes; no P4/prefix/integer-helper/common/data/alignment/authored credit')

def validate(rule,selected,rows,read,target_sha):
    try:
        require(ROOT/str(rule['vc8_pow_shared_anchor_file'])==ANCHORS,'unreviewed pow anchor path');units=sin.sqrt.load_manifest()['units'];a,u=validate_spec(tomllib.loads(ANCHORS.read_text()),selected,units,target_sha)
        errors=sin.validate(dict(id='vc8-original-sin-shared-owners-106a',vc8_sin_shared_anchor_file=str(sin.ANCHORS.relative_to(ROOT))),[x for x in rows if x['address']in sin.CONTRACT],rows,read,target_sha);require(not errors,'pow shared protocol failed: '+'; '.join(errors))
        archive=(ROOT/'.tools/msvc80-sp1/lib/libcmt.lib').read_bytes();require(digest(archive)==sin.sqrt.ARCHIVE_SHA,'pow original archive differs');sp=importlib.util.spec_from_file_location('pow_extract',ROOT/'scripts/extract-msvc-library-object.py');m=importlib.util.module_from_spec(sp);sp.loader.exec_module(m);members=m.archive_members(archive);OUTPUT.mkdir(parents=True,exist_ok=True)
        for n,sha in HASHES.items():
            if n=='pow.obj':continue
            found=[b for name,b in members if Path(name).name==n];require(len(found)==1 and digest(found[0])==sha,'pow original support member differs');(OUTPUT/n).write_bytes(found[0])
        record=build.build_unit(UNIT,u,True,target_sha);c=sin.sqrt.core.comparator();c.verify_target();game=pefile.PE(str(c.TARGET));proof=qualify(units,a,rows,read,c,game);code,results=build.compare_unit(u,True);require(code==0 and len(results)==1 and results[0]['result']=='exact','pow formal shared body failed')
        proof.update(build=record,comparisons=results,member_sha256=HASHES,validator_sha256=sin.sqrt.core.sha(Path(__file__)),anchor_sha256=sin.sqrt.core.sha(ANCHORS));(OUTPUT/'proof.json').write_text(json.dumps(proof,indent=2)+'\n');return []
    except (OSError,ValueError,KeyError,TypeError,RuntimeError,struct.error,pefile.PEFormatError)as exc:return [str(rule['id'])+': '+str(exc)]

def main():
    c=sin.sqrt.core.comparator();sha=c.verify_target();rows=list(csv.DictReader((ROOT/'config/functions.csv').open()));result=validate(dict(id='vc8-original-pow-shared-owner-106a',vc8_pow_shared_anchor_file=str(ANCHORS.relative_to(ROOT))),[r for r in rows if r['address']=='0x0068C28D'],rows,c.target_bytes,sha);print(json.dumps(dict(errors=result)));return bool(result)
if __name__=='__main__':raise SystemExit(main())
