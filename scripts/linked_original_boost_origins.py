"""Whole original-library CIL proof for the four-byte vector back accessor.

This vendor-source contract is separate from the existing game-owner/pure and
checked-iterator gates. It does not claim an exact public constructor context.
"""
import csv
import hashlib
import json
from pathlib import Path
import struct
import tomllib
import capstone
import pefile
import linked_pe as core
import original_boost_link as original

ROOT=Path(__file__).resolve().parents[1]
ANCHORS=ROOT/'config/boost-linked-vector-back-origin-anchors.toml'
SYMBOL='?back@?$vector@JV?$allocator@J@std@@@std@@QAEAAJXZ'
INVALID=0x68a143
INVALID_SHA='cd349dae43dbf63016fe6ea9339dab15c59041e3224e48cf8a53004224b45e77'


def validate_spec(spec,selected,rows,target_sha):
    if (set(spec)!={'schema_version','target_sha256','anchors','receiver_witnesses'}
            or type(spec['schema_version'])is not int or spec['schema_version']!=1
            or spec['target_sha256']!=target_sha or len(spec['anchors'])!=1):
        raise ValueError('original-library vector anchor schema differs')
    a=spec['anchors'][0]
    if (set(a)!={'address','size','symbol','sha256'} or a['address']!='0x0040DBF0'
            or type(a['size'])is not int or a['size']!=67 or a['symbol']!=SYMBOL
            or len(selected)!=1 or selected[0]['address']!=a['address']or int(selected[0]['size'],0)!=67):
        raise ValueError('original-library vector selection differs')
    w=spec['receiver_witnesses']
    if not isinstance(w,list)or len(w)!=4 or len({r['site']for r in w})!=4:
        raise ValueError('original-library vector needs all four actual receiver sites')
    return a


def verify_receivers(spec,rows,read):
    by={r['address']:r for r in rows};out=[]
    for w in spec['receiver_witnesses']:
        if set(w)!={'caller','load','site','gap_hex'}or w['caller']!='0x0040D9F0':
            raise ValueError('unreviewed vector receiver witness')
        row=by.get(w['caller']);start=int(w['caller'],0);load=int(w['load'],0);site=int(w['site'],0);gap=bytes.fromhex(w['gap_hex'])
        if (row is None or not start<=load<site<=start+int(row['size'],0)-5
                or site!=load+5+len(gap) or gap not in (b'',bytes.fromhex('c74424142c000000'))
                or read(load,5)!=b'\xb8'+struct.pack('<I',0x702a38)or read(load+5,len(gap))!=gap):
            raise ValueError('actual input vector EAX receiver differs')
        call=read(site,5)
        if call[0]!=0xe8 or site+5+struct.unpack_from('<i',call,1)[0]!=0x40dbf0 or read(site+5,2)!=b'\x8b\x00':
            raise ValueError('actual vector call/returned-element dereference differs')
        out.append(dict(caller=w['caller'],load=w['load'],site=w['site'],receiver='0x00702A38'))
    return out


def qualify(pe,functions,anchor,rows,read):
    if pe.FILE_HEADER.Machine!=0x14c or pe.OPTIONAL_HEADER.ImageBase!=core.IMAGE_BASE:
        raise ValueError("original library image architecture/base differs")
    found=[(a,aliases)for a,aliases in functions.items()if any(n==SYMBOL for n,o in aliases)]
    if len(found)!=1 or found[0][1]!=[(SYMBOL,'i original-0.obj')]:
        raise ValueError('vector back needs its unique original instance CIL owner')
    start=found[0][0];exports=getattr(getattr(pe,'DIRECTORY_ENTRY_EXPORT',None),'symbols',[])
    if any(pe.OPTIONAL_HEADER.ImageBase+e.address==start for e in exports):raise ValueError('vector back may not be exported')
    if len(exports)!=1 or exports[0].name.decode()!=original.PUBLIC_ROOT:raise ValueError('original library has an unreviewed export')
    helpers=[(a,aliases)for a,aliases in functions.items()if any(n=='__invalid_parameter_noinfo'for n,o in aliases)]
    if len(helpers)!=1 or helpers[0][1]!=[('__invalid_parameter_noinfo','libcmt:invarg.obj')]:
        raise ValueError('vector back needs its original named CRT helper')
    helper=helpers[0][0];hb=core.linked_body(pe,functions,helper);native_helper=read(INVALID,16)
    if (len(hb)!=16 or hb!=native_helper or hashlib.sha256(hb).hexdigest()!=INVALID_SHA
            or functions.get(helper-36)!=[('__invalid_parameter','libcmt:invarg.obj')]):
        raise ValueError('complete original CRT invalid-parameter ownership differs')
    raw=core.linked_body(pe,functions,start);target=int(anchor['address'],0);native=read(target,67)
    if len(raw)!=67 or len(native)!=67:raise ValueError('vector back whole extent differs')
    source_rows=core.decode_closed_body(raw,start);target_rows=core.decode_closed_body(native,target)
    core.validate_body_relocations(pe,start,67,[])
    for i in source_rows:
        for op in i.operands:
            if op.type==capstone.x86.X86_OP_MEM and ((not op.mem.base and not op.mem.index)or op.mem.segment):
                raise ValueError('vector back has absolute or segmented data')
    def resolve(a):
        if a!=helper:raise ValueError('vector back has an unproved callee')
        return '__invalid_parameter_noinfo',INVALID
    def rebound(a):return core.canonicalize(raw,start,a,[],resolve,(core.IMAGE_BASE,core.IMAGE_BASE+pe.OPTIONAL_HEADER.SizeOfImage),(0x400000,0x706000))
    canonical,calls,refs=rebound(target)
    if (canonical!=native or refs or [r['offset']for r in calls]!=[17,41,54]
            or hashlib.sha256(native).hexdigest()!=anchor['sha256']):
        raise ValueError('whole vector back canonical body differs')
    changed={i for off in (17,41,54)for i in range(off,off+4)}
    if any(x!=y for i,(x,y)in enumerate(zip(raw,canonical))if i not in changed):
        raise ValueError('vector back changed a non-call byte')
    hits=[]
    for r in rows:
        if int(r['size'],0)==67 and rebound(int(r['address'],0))[0]==read(int(r['address'],0),67):hits.append(r['address'])
    if hits!=[anchor['address']]:raise ValueError('whole vector back is not inventory-unique')
    return dict(address=anchor['address'],size=67,sha256=anchor['sha256'],source_va=hex(start),
                source_instructions=len(source_rows),target_instructions=len(target_rows),
                calls=calls,inventory_hits=hits,crt_helper_sha256=INVALID_SHA)


def validate(rule,selected,rows,read,target_sha):
    try:
        if ROOT/str(rule['original_boost_link_anchor_file'])!=ANCHORS:raise ValueError('unreviewed original-library anchor path')
        spec=tomllib.loads(ANCHORS.read_text());anchor=validate_spec(spec,selected,rows,target_sha)
        receivers=verify_receivers(spec,rows,read);image,provenance=original.build();pe=pefile.PE(str(image));functions=core.parse_map(image.with_suffix('.map').read_text())
        proof=qualify(pe,functions,anchor,rows,read);proof.update(receiver_witnesses=receivers,build=provenance,
            validator_sha256=core.sha(Path(__file__)),anchor_sha256=core.sha(ANCHORS))
        root=[a for a,aliases in functions.items()if any(n==original.PUBLIC_ROOT for n,o in aliases)]
        if len(root)!=1:raise ValueError('original public library root is missing')
        proof['unaccepted_context_root']=dict(symbol=original.PUBLIC_ROOT,source_size=len(core.linked_body(pe,functions,root[0])),native_size=111)
        (original.OUTPUT/'vector-back-proof.json').write_text(json.dumps(proof,indent=2)+'\n');return []
    except (OSError,ValueError,KeyError,TypeError,RuntimeError,struct.error)as exc:return [str(rule['id'])+': '+str(exc)]


def main():
    c=core.comparator();sha=c.verify_target();rows=list(csv.DictReader((ROOT/'config/functions.csv').open()));selected=[r for r in rows if r['address']=='0x0040DBF0'];rule=dict(id='original-boost-linked-vector-back-106a',original_boost_link_anchor_file=str(ANCHORS.relative_to(ROOT)));errors=validate(rule,selected,rows,c.target_bytes,sha);print(json.dumps(dict(errors=errors)));return bool(errors)

if __name__=='__main__':raise SystemExit(main())
