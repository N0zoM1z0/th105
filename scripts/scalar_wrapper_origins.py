"""Canonical compiler-only provenance for emitted VC8 scalar deleting bodies.

Compile only explicitly selected owner units. Checks revalidate current-input
receipts, actual emitted ??_G symbols, full comparisons and native RTTI owners.
No authored count, instruction mask or partial-body evidence is accepted.
"""
import argparse
import hashlib
import json
from pathlib import Path
import struct
import tomllib
import pefile
from build import build_unit, compare_unit
from workflow_manifest import ROOT, load_manifest, repository_path, unit_input_digest, compiler_sha256
import linked_pe as core
import rank_retained_exact as rank

ANCHORS = ROOT / "config/vc8-scalar-wrapper-origin-anchors.toml"
OUTPUT = ROOT / "build/origin-anchors/scalar-wrappers"


def digest(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def validate_spec(spec, selected, rows, units, target_sha):
    if (set(spec) != {"schema_version","target_sha256","compiler_sha256","anchors"}
            or type(spec["schema_version"]) is not int or spec["schema_version"] != 1
            or spec["target_sha256"] != target_sha
            or spec["compiler_sha256"] != "71c93ca5bddc9b2816d0e053cac2b952f926f6b9321fab6b1ab6e8603621324c"):
        raise ValueError("scalar-wrapper target/compiler/schema differs")
    anchors=spec["anchors"];by={r["address"]:r for r in rows}
    if (not isinstance(anchors,list) or not anchors
            or len({a["address"]for a in anchors})!=len(anchors)
            or {a["address"]for a in anchors}!={r["address"]for r in selected}):
        raise ValueError("scalar-wrapper selection differs")
    groups={}
    for a in anchors:
        if (set(a)!={"address","size","unit","symbol_base","sha256","owners"}
                or type(a["size"]) is not int or a["size"]<4
                or a["address"]not in by or int(by[a["address"]]["size"],0)!=a["size"]
                or not isinstance(a["owners"],list) or not a["owners"]):
            raise ValueError("scalar-wrapper extent or RTTI owners missing")
        u=units.get(a["unit"],{})
        if u.get("kind")!="probe" or u.get("profile")!="vc8-sp1-probe-o2":
            raise ValueError("scalar-wrapper needs its original ordinary pinned owner unit")
        f=[f for f in u["functions"]if int(f["address"],0)==int(a["address"],0)]
        if len(f)!=1 or f[0]["symbol_base"]!=a["symbol_base"]:
            raise ValueError("scalar-wrapper configured source symbol differs")
        if not (a["symbol_base"].startswith("??_G")
                or a["symbol_base"].endswith("_scalar_deleting_destructor")):
            raise ValueError("scalar-wrapper source selector is not a compiler deleting member")
        groups.setdefault(a["unit"],[]).append(a)
    return groups


def native_owner(pe, read, address, owner):
    if set(owner)!={"vtable","slot","col","type_descriptor","type_name"}:
        raise ValueError("invalid scalar-wrapper RTTI schema")
    table,slot,col,td=(int(owner[k],0)for k in ("vtable","slot","col","type_descriptor"))
    base=pe.OPTIONAL_HEADER.ImageBase
    def section(addr):
        return pe.get_section_by_rva(addr-base)
    def readonly(addr,size):
        s=section(addr)
        if (s is None or s.Name.rstrip(b"\0")!=b".rdata"
                or addr+size>base+s.VirtualAddress+s.SizeOfRawData
                or s.Characteristics&0xA0000000):
            raise ValueError("scalar-wrapper RTTI is not complete read-only data")
    readonly(table-4,slot-table+8);readonly(col,20)
    if slot-table not in (0,4):
        raise ValueError("scalar-wrapper has unreviewed virtual slot order")
    if struct.unpack("<I",read(table-4,4))[0]!=col or struct.unpack("<I",read(slot,4))[0]!=address:
        raise ValueError("scalar-wrapper vtable/COL pointer differs")
    for at in range(table,slot,4):
        value=struct.unpack("<I",read(at,4))[0];s=section(value)
        if s is None or not s.Characteristics&0x20000000:
            raise ValueError("scalar-wrapper preceding initializer is not code")
    sig,off,cd,type_descriptor,hierarchy=struct.unpack("<5I",read(col,20))
    if sig or off or cd or type_descriptor!=td:
        raise ValueError("scalar-wrapper needs its primary native RTTI owner")
    name=owner["type_name"].encode("ascii")
    if not name.startswith((b".?AV",b".?AU")) or read(td+8,len(name)+1)!=name+b"\0":
        raise ValueError("scalar-wrapper native type name differs")
    readonly(hierarchy,16)
    hs,attributes,count,array=struct.unpack("<4I",read(hierarchy,16))
    if hs or not 1<=count<=128:
        raise ValueError("invalid scalar-wrapper class hierarchy")
    readonly(array,4*count)
    first=struct.unpack("<I",read(array,4))[0];readonly(first,24)
    if struct.unpack("<I",read(first,4))[0]!=td:
        raise ValueError("scalar-wrapper hierarchy does not start with its owner")


def verify_comparisons(anchors, reports):
    by={r.get("address"):r for r in reports}
    if len(by)!=len(reports) or set(by)!={a["address"]for a in anchors}:
        raise ValueError("scalar-wrapper comparisons do not cover selected bodies")
    for a in anchors:
        r=by[a["address"]]
        if (r.get("result")!="exact" or r.get("target_size")!=a["size"]
                or r.get("object_section_tail_size")!=a["size"]
                or r.get("target_sha256")!=a["sha256"]
                or r.get("object_compared_sha256")!=a["sha256"]):
            raise ValueError("scalar-wrapper whole canonical comparison failed: "+a["address"])


def replay(unit_name, anchors, units, spec, read, pe, rebuild):
    unit=units[unit_name];obj=repository_path(unit["object"],output=True)
    receipt=OUTPUT/(unit_name+".json")
    if compiler_sha256()!=spec["compiler_sha256"]:
        raise ValueError("scalar-wrapper compiler pin changed")
    if rebuild:
        provenance=build_unit(unit_name,unit,True,spec["target_sha256"])
    else:
        proof=json.loads(receipt.read_text())
        if (proof["validator_sha256"]!=digest(__file__)
                or proof["anchor_sha256"]!=digest(ANCHORS)
                or proof["target_sha256"]!=spec["target_sha256"]):
            raise ValueError("scalar-wrapper proof is stale; rebuild selected unit")
        provenance=json.loads(obj.with_suffix(obj.suffix+".provenance.json").read_text())
        if proof["object_sha256"]!=digest(obj):
            raise ValueError("scalar-wrapper object differs from verified receipt")
    current,_=unit_input_digest(unit_name,unit)
    if (provenance["input_digest"]!=current or provenance["object_sha256"]!=digest(obj)
            or provenance["compiler_sha256"]!=spec["compiler_sha256"]):
        raise ValueError("scalar-wrapper current source provenance differs")
    facts=[]
    for a in anchors:
        actual,raw,wild,relocs=rank.read_coff_function(obj,a["symbol_base"],None)
        if not actual.startswith("??_G") or len(raw)!=a["size"]:
            raise ValueError("source did not emit one complete compiler scalar-deleting body: "+a["address"])
        native=read(int(a["address"],0),a["size"])
        if native[-3:]!=b"\xc2\x04\x00" or hashlib.sha256(native).hexdigest()!=a["sha256"]:
            raise ValueError("scalar-wrapper native extent/hash/RET4 differs")
        for owner in a["owners"]:native_owner(pe,read,int(a["address"],0),owner)
        facts.append(dict(address=a["address"],symbol=actual,size=a["size"],sha256=a["sha256"],owners=a["owners"]))
    view=dict(unit);wanted={int(a["address"],0)for a in anchors}
    view["functions"]=[f for f in unit["functions"]if int(f["address"],0)in wanted]
    rc,reports=compare_unit(view,True)
    verify_comparisons(anchors,reports)
    if rc:raise ValueError("scalar-wrapper comparator returned failure")
    result=dict(schema_version=1,unit=unit_name,target_sha256=spec["target_sha256"],
        validator_sha256=digest(__file__),anchor_sha256=digest(ANCHORS),
        object_sha256=digest(obj),input_digest=current,anchors=facts,reports=reports)
    if rebuild:
        OUTPUT.mkdir(parents=True,exist_ok=True)
        receipt.write_text(json.dumps(result,indent=2)+"\n")
    return result


def validate(rule, selected, rows, read, target_sha):
    try:
        if ROOT/str(rule["scalar_wrapper_anchor_file"])!=ANCHORS:
            raise ValueError("scalar-wrapper anchor path differs")
        spec=tomllib.loads(ANCHORS.read_text());units=load_manifest()["units"]
        groups=validate_spec(spec,selected,rows,units,target_sha)
        c=core.comparator();c.verify_target();pe=pefile.PE(str(c.TARGET))
        for name,anchors in groups.items():replay(name,anchors,units,spec,read,pe,False)
        return []
    except (OSError,ValueError,KeyError,TypeError,RuntimeError,struct.error)as exc:
        return [str(rule["id"])+": "+str(exc)]


def main():
    import csv
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--unit",action="append",help="fresh-build this selected owner unit; may repeat")
    parser.add_argument("--check",action="store_true",help="check all current receipts without a native rebuild")
    args=parser.parse_args()
    if bool(args.unit)==args.check:parser.error("choose --unit or --check")
    c=core.comparator();sha=c.verify_target();pe=pefile.PE(str(c.TARGET))
    rows=list(csv.DictReader((ROOT/"config/functions.csv").open()))
    spec=tomllib.loads(ANCHORS.read_text());units=load_manifest()["units"]
    selected=[r for r in rows if r["address"]in {a["address"]for a in spec["anchors"]}]
    groups=validate_spec(spec,selected,rows,units,sha)
    chosen=list(groups)if args.check else args.unit
    if len(chosen)!=len(set(chosen))or any(n not in groups for n in chosen):raise ValueError("unknown/repeated owner unit")
    for name in chosen:
        result=replay(name,groups[name],units,spec,c.target_bytes,pe,not args.check)
        print(json.dumps(dict(unit=name,result="verified",count=len(result["anchors"]),
                              bytes=sum(a["size"]for a in result["anchors"]))),flush=True)
    return 0


if __name__=="__main__":raise SystemExit(main())
