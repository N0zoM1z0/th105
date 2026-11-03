"""Whole VC8 packet-deque back helper in the real UDP sender graph."""
import csv
import hashlib
import json
from pathlib import Path
import struct
import tomllib
import capstone
import pefile
import linked_pe as core
from linked_logic_error_origins import require, named
from workflow_manifest import load_manifest, source_dependencies

ROOT=Path(__file__).resolve().parents[1]
ANCHORS=ROOT/'config/linked-packet-deque-back-origin-anchors.toml'
UNIT='cross-v106a-network-winsock-send-client'
SYMBOL='?back@?$deque@UNetworkUdpPacketBuffer41C@th105@@V?$allocator@UNetworkUdpPacketBuffer41C@th105@@@std@@@std@@QAEAAUNetworkUdpPacketBuffer41C@th105@@XZ'
PARENT='?acquire@NetworkUdpPacketHandleManager64@th105@@QAEPAUNetworkUdpPacketBuffer41C@2@AAUResourceHandleToken@2@@Z'
SHA='45252decccc5e54cbebe34eb2a4c5e49b3d25576f71d0df148891db407bc4fe2'
PARENT_SHA='ffc37d12373208d75b91a5ce48359fc4247ae7a6775a05e824718ea56cbdd621'
INVALID_SHA='cd349dae43dbf63016fe6ea9339dab15c59041e3224e48cf8a53004224b45e77'
HEADERS={'include/deque':'2970afda6fd33a55bb0f3860124a28e5c9e532dda18a240ac5749fb0a8cc0fc7',
         'include/xmemory':'83a2121ebc455b25493a689a4fb299db0ca848ffc29668159bc9fb5faa95e50b',
         'include/xutility':'104560e2ad5e433eb62c06d70882534306ba345f5f74e6907a6b270df3bd7cea'}

def inputs(unit):
    paths=set(source_dependencies(unit))
    for s in unit.get('linked_coff_sources',[]):paths.update(source_dependencies(dict(source=s)))
    return paths

def validate_spec(spec,selected,unit,target_sha):
    require(set(spec)=={'schema_version','target_sha256','unit','source_pins','anchors'}
        and type(spec['schema_version']) is int and spec['schema_version']==1
        and spec['target_sha256']==target_sha and spec['unit']==UNIT,'packet deque schema/target/unit differs')
    require(len(selected)==len(spec['anchors'])==1,'packet deque requires one whole candidate')
    a=spec['anchors'][0]
    require(a==dict(address='0x004179D0',size=82,symbol=SYMBOL,sha256=SHA)
        and selected[0]['address']==a['address'] and int(selected[0]['size'],0)==82,'packet deque target/type differs')
    require(unit.get('kind')=='linked_candidate' and unit.get('profile')==core.PROFILE
        and unit.get('source')=='src/network/NetworkWinsockSendClient.cpp'
        and unit.get('enable_gs') is False and unit.get('link_runtime','import')=='import'
        and unit.get('linked_coff_sources')==['src/library/UnsignedIntList.cpp']
        and {f['address'] for f in unit['functions']}=={'0x00416990','0x00405200','0x00416B60','0x00416D90','0x00416DB0'},
        'packet deque actual sender source graph differs')
    expected={str(p.relative_to(ROOT)) for p in inputs(unit)};pins=spec['source_pins']
    require(isinstance(pins,dict) and set(pins)==expected and all(isinstance(v,str) and len(v)==64
        and all(c in '0123456789abcdef' for c in v) for v in pins.values()),'packet deque source closure differs')
    return a

def qualify(pe,functions,symbols,owner,anchor,rows,origins,read):
    start=named(symbols,SYMBOL,'i '+owner);parent=named(symbols,PARENT,owner)
    require(functions.get(start)==[(SYMBOL,'i '+owner)] and functions.get(parent)==[(PARENT,owner)],'packet deque source owner/alias differs')
    require(all(core.IMAGE_BASE+e.address!=start for e in pe.DIRECTORY_ENTRY_EXPORT.symbols),'packet deque helper must not be forced export')
    invalid=named(symbols,'__invalid_parameter_noinfo','msvcrt:MSVCR80.dll')
    section=pe.get_section_by_rva(invalid-core.IMAGE_BASE)
    require(section is not None and section.Characteristics & 0x20000000 and section.contains_rva(invalid-core.IMAGE_BASE+5),'packet deque import thunk is outside executable code')
    thunk=pe.get_data(invalid-core.IMAGE_BASE,6);require(len(thunk)==6 and thunk[:2]==bytes.fromhex('ff25'),'packet deque invalid-parameter thunk differs')
    iat=struct.unpack_from('<I',thunk,2)[0]
    imports={(x.address,d.dll.decode('ascii').lower(),x.name.decode('ascii') if x.name else None)
        for d in pe.DIRECTORY_ENTRY_IMPORT for x in d.imports}
    require((iat,'msvcr80.dll','_invalid_parameter_noinfo') in imports,'packet deque actual runtime import differs')
    origin=origins.get('0x0068A143',{})
    require(origin.get('evidence_id')=='vc8-pinned-archive-symbols-106a' and origin.get('disposition')=='exclude'
        and hashlib.sha256(read(0x68a143,16)).hexdigest()==INVALID_SHA,'packet deque native runtime identity differs')
    require(hashlib.sha256(read(0x417660,410)).hexdigest()==PARENT_SHA,'packet deque native acquire body differs')
    def direct(code,at,to):
        return [i.address for i in core.decode_closed_body(code,at) if i.group(capstone.CS_GRP_CALL)
            and i.operands[0].type==capstone.x86.X86_OP_IMM and i.operands[0].imm==to]
    source_parent=core.linked_body(pe,functions,parent)
    require(direct(source_parent,parent,start)==[parent+0x9d] and direct(read(0x417660,410),0x417660,0x4179d0)==[0x417706],
        'packet deque source/native acquire call edge differs')
    raw=core.linked_body(pe,functions,start);require(len(raw)==82,'packet deque whole emitted extent differs')
    core.decode_closed_body(raw,start);core.decode_closed_body(read(0x4179d0,82),0x4179d0)
    def resolve(a):
        require(a==invalid,'packet deque unproved callee')
        return '__invalid_parameter_noinfo',0x68a143
    def rebound(a):return core.canonicalize(raw,start,a,[],resolve,(core.IMAGE_BASE,core.IMAGE_BASE+pe.OPTIONAL_HEADER.SizeOfImage),(0x400000,0x706000))
    body,calls,refs=rebound(0x4179d0)
    require(body==read(0x4179d0,82) and hashlib.sha256(body).hexdigest()==anchor['sha256']
        and not refs and [x['offset'] for x in calls]==[14,38,53],'packet deque full canonical body differs')
    core.validate_body_relocations(pe,start,82,[])
    fields={i for off in (14,38,53) for i in range(off,off+4)}
    require(all(a==b for i,(a,b) in enumerate(zip(raw,body)) if i not in fields),'packet deque changed non-call byte')
    hits=[r['address'] for r in rows if int(r['size'],0)==82 and rebound(int(r['address'],0))[0]==read(int(r['address'],0),82)]
    require(hits==['0x004179D0'],'packet deque full inventory identity differs')
    return dict(address=anchor['address'],size=82,sha256=anchor['sha256'],symbol=SYMBOL,source_va=hex(start),
        native_parent='0x00417660',native_parent_exact=False,native_call='0x00417706',source_parent=hex(parent),source_parent_exact=False,
        source_call=hex(parent+0x9d),calls=calls,inventory_hits=hits,masked_bytes=0,unequal_bytes=0)

def validate(rule,selected,rows,read,target_sha):
    try:
        require(ROOT/str(rule['linked_packet_deque_back_anchor_file'])==ANCHORS,'packet deque anchor path differs')
        unit=load_manifest()['units'][UNIT];spec=tomllib.loads(ANCHORS.read_text());anchor=validate_spec(spec,selected,unit,target_sha)
        require(all(core.sha(ROOT/path)==sha for path,sha in spec['source_pins'].items()),'packet deque source pin differs')
        require(next(r for r in rows if r['address']=='0x00405200')['status']=='matching'
            and next(r for r in rows if r['address']=='0x00417660')['status']=='implemented','packet deque owner statuses differ')
        tools,_=core.pinned_tools(False);require(all(core.sha(tools/n)==s for n,s in HEADERS.items()),'packet deque standard header pin differs')
        core.build_linked(UNIT,unit);roots=core.compare_linked(UNIT,unit,{'0x00405200'})
        require(len(roots)==1 and roots[0]['result']=='exact','packet deque existing accepted release differs')
        image=ROOT/unit['object'];pe=pefile.PE(str(image));maps=image.with_suffix('.map').read_text()
        origins={r['address']:r for r in csv.DictReader((ROOT/'config/function-origins.csv').open())}
        proof=qualify(pe,core.parse_map(maps),core.parse_map_symbols(maps),image.with_suffix('.ltcg.obj').name,anchor,rows,origins,read)
        output=ROOT/'build/origin-anchors/linked-packet-deque-back';output.mkdir(parents=True,exist_ok=True)
        (output/'proof.json').write_text(json.dumps(dict(target_sha256=target_sha,proof=proof,roots=roots),indent=2)+'\n')
        return []
    except (OSError,ValueError,KeyError,TypeError,RuntimeError,struct.error,pefile.PEFormatError) as exc:
        return [str(rule['id'])+': '+str(exc)]
