#!/usr/bin/env python3
"""Pin the complete deck renderer and the push-relative missing-count contract."""
import argparse
from collections import Counter
import hashlib
import importlib.util
import json
from pathlib import Path
import struct

import capstone
from capstone import x86
import pefile
from unicorn import Uc, UC_ARCH_X86, UC_MODE_32, UC_HOOK_CODE
from unicorn.x86_const import (UC_X86_REG_EAX, UC_X86_REG_EBX, UC_X86_REG_ECX,
    UC_X86_REG_EDX, UC_X86_REG_EBP, UC_X86_REG_ESI, UC_X86_REG_EDI,
    UC_X86_REG_ESP, UC_X86_REG_EIP, UC_X86_REG_FPCW, UC_X86_REG_FPTAG)
from workflow_manifest import load_manifest

ROOT = Path(__file__).resolve().parents[1]
ADDRESS, SIZE = 0x448F60, 2521
SHA = '6898ee39c83606abc8cbf1618d91834dfaa9e901fd2adb3f38163101f780fb0c'
UNIT = 'exact-first-profile-deck-render'


def require(condition, message):
    if not condition:
        raise ValueError(message)


def observe_missing_counts(image, code):
    """One in-range three-row case; external drawing/availability calls are observers."""
    a = ADDRESS
    m = Uc(UC_ARCH_X86, UC_MODE_32)
    m.mem_map(0x400000, (len(image) + 4095) & ~4095)
    m.mem_write(0x400000, image)
    m.mem_write(a, code)
    m.mem_map(0, 0x10000)
    m.mem_map(0x800000, 0x20000)
    m.mem_map(0x1000000, 0x20000)
    m.mem_map(0xf00000, 0x1000)
    w=lambda a,v:m.mem_write(a,struct.pack('<I',v&0xffffffff));r=lambda a:struct.unpack('<I',m.mem_read(a,4))[0];wf=lambda a,v:m.mem_write(a,struct.pack('<f',v))
    obj=0x801000;head=0x804000;mapbase=0x805000;owner=0x806000;end=0x806100;vt=0x807000;rend=0x800010;design=0x800020
    w(obj+4,0x809000);w(obj+8,1);w(obj+0xc,0x80a000);w(obj+0x10,vt);w(vt+0x24,design);w(vt+0x1c,rend)
    for i in range(20):
     q=0x80b000+i*0x100;w(obj+0x44+4*i,q);w(q,vt);wf(q+0xc,100.0+i);wf(q+0x10,200.0+i)
    w(0x80a000,vt);w(obj+0x3c4,head)
    for off in [0,4,8]:w(head+off,head)
    m.mem_write(head+0x10,b'\x01\x01');w(obj+0x3c8,0);w(obj+0x3bc,owner);w(owner+4,end)
    w(obj+0x3d0,mapbase);w(obj+0x3d4,2);w(obj+0x3d8,0);w(obj+0x3dc,3);w(obj+0x3f0,0);w(obj+0x3f4,0)
    for i in range(2):w(mapbase+i*4,0x80e000+i*0x100)
    for i in range(3):
     node=0x810000+i*0x100;pair=0x80e000+(i//2)*0x100+(i%2)*8;w(pair,owner);w(pair+4,node);w(node+0xc,100+i);w(node+0x24,4+i);w(node+0x50,0x1234+i);w(node+0x58,10+i);w(node+0x54,0)
    for off in [0x98,0x1c4,0x304]:w(obj+off,vt)
    w(0x6fa6c0,64);w(0x6fa6c4,32);stack=0x1010004;w(stack,0xf00000)
    for rg,v in [(UC_X86_REG_ESP,stack),(UC_X86_REG_EBP,0x12345678),(UC_X86_REG_EBX,0x22334455),(UC_X86_REG_ESI,0x33445566),(UC_X86_REG_EDI,0x44556677),(UC_X86_REG_ECX,obj),(UC_X86_REG_FPCW,0x37f),(UC_X86_REG_FPTAG,0xffff)]:m.reg_write(rg,v)
    events=[]
    stubs={0x43f9d0:('cursor',12),0x448df0:('available',4),0x406a60:('texture',20),0x406be0:('sprite',8),0x4099f0:('tile',16),0x43faf0:('player',12),0x43f970:('footer',0),0x43f4c0:('guide',0),rend:('virtual_render',8),design:('design',0)}
    def hook(u,addr,size,data):
     if addr==0xf00000:u.emu_stop();return
     if addr==0x68a143:raise ValueError('invalid parameter fixture at '+hex(r(u.reg_read(UC_X86_REG_ESP))))
     if addr not in stubs:return
     name,n=stubs[addr];ss=u.reg_read(UC_X86_REG_ESP);args=list(struct.unpack('<'+str(n//4)+'I',u.mem_read(ss+4,n)))if n else[];res=0
     if name=='available':
      assert args[0] < 3
      res=25
     receiver = u.reg_read(UC_X86_REG_ECX)
     events.append(dict(kind=name,receiver='temporary_sprite' if 0x1000000 <= receiver < 0x1020000 else hex(receiver),args=args))
     u.reg_write(UC_X86_REG_EAX,res);u.reg_write(UC_X86_REG_ECX,0xbad0c0de);u.reg_write(UC_X86_REG_EDX,0xbad0dada);u.reg_write(UC_X86_REG_ESP,ss+4+n);u.reg_write(UC_X86_REG_EIP,r(ss))
    m.hook_add(UC_HOOK_CODE,hook);m.emu_start(a,0,count=15000);assert m.reg_read(UC_X86_REG_EIP)==0xf00000;assert m.reg_read(UC_X86_REG_ESP)==stack+4
    for rg,v in [(UC_X86_REG_EBP,0x12345678),(UC_X86_REG_EBX,0x22334455),(UC_X86_REG_ESI,0x33445566),(UC_X86_REG_EDI,0x44556677)]:assert m.reg_read(rg)==v
    assert r(0)==0
    tiles = [event['args'][3] for event in events if event['kind'] == 'tile']
    require(tiles[2::3] == [0, 0, 0], 'missing-count default differs from native zero')
    require(len(events) == 32, 'three-row/selected-preview call census changed')
    return dict(filtered_count=3, selection=0, missing_counts=tiles[2::3], events=events,
                stack_and_callee_saves_preserved=True, fs0_restored=True)


def audit(obj=None):
    spec = importlib.util.spec_from_file_location("deck_render_compare", ROOT / "scripts/compare-function.py")
    compare = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(compare)
    identity = compare.verify_target()
    code = compare.target_bytes(ADDRESS, SIZE)
    require(hashlib.sha256(code).hexdigest() == SHA, "complete body changed")
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    decoder.detail = True
    instructions = list(decoder.disasm(code, ADDRESS))
    require(len(instructions) == 744 and sum(i.size for i in instructions) == SIZE,
            "complete instruction census changed")
    by_address = {i.address: i for i in instructions}
    pending, reached, returns, calls = [ADDRESS], set(), [], Counter()
    while pending:
        address = pending.pop()
        if address in reached:
            continue
        require(address in by_address, "escaping/noninstruction edge")
        reached.add(address)
        instruction = by_address[address]
        if instruction.mnemonic == "ret":
            require(bytes(instruction.bytes) == b"\xc3", "return cleanup changed")
            returns.append(address)
            continue
        if instruction.mnemonic == "call":
            operand = instruction.operands[0]
            calls[hex(operand.imm) if operand.type == x86.X86_OP_IMM else instruction.op_str] += 1
        if instruction.group(capstone.CS_GRP_JUMP):
            require(instruction.operands[0].type == x86.X86_OP_IMM, "unreviewed indirect jump")
            pending.append(instruction.operands[0].imm)
            if instruction.mnemonic == "jmp":
                continue
        pending.append(address + instruction.size)
    require(len(reached) == 744 and returns == [0x449938], "full CFG changed")
    require(calls["0x68a143"] == 40 and calls["eax"] == 5, "guard/virtual call census changed")
    require(calls["0x4300b0"] == 6 and calls["0x4099f0"] == 3 and calls["0x448df0"] == 2,
            "checked-index/digit/availability sites changed")
    require(compare.target_bytes(ADDRESS + SIZE, 7) == b"\xcc" * 7, "following separation changed")
    require(compare.target_bytes(0x6C2228, 20).hex() ==
            "10866d0020b3440090f8410010a44400608f4400", "primary RTTI/render slot changed")
    require(compare.target_bytes(0x6D8610, 20).hex() ==
            "000000000000000000000000dc6d6e0024866d00", "complete object locator changed")
    type_name = b".?AVCProfileDeckEdit@@\0"
    require(compare.target_bytes(0x6E6DE4, len(type_name)) == type_name,
            "RTTI class name changed")
    providers = []
    for address, size, digest in [
        (0x448DF0, 358, "632a2b65bbea6144410a9edccc1d4fe4005f5c89d98e0082fe13914211586e17"),
        (0x448D70, 109, "93a5309d0f340393274acff345c7ec5cf3329d4c9cb02c7f1fc8fd15e8d5edb7"),
        (0x4300B0, 99, "ae509a3b09331186abecad3ad6672e6e772a99b2f953159388cb7c6b9c3b6479"),
        (0x406A60, 39, "578ecfa5118001a1f6590962ccd76548e5d2e507e6edbf2895b357df106748aa"),
    ]:
        require(hashlib.sha256(compare.target_bytes(address, size)).hexdigest() == digest,
                "provider body changed")
        providers.append(dict(address=hex(address), size=size, sha256=digest, new_credit=False))
    # ESP has one pushed index here: encoded +0x20 denotes base +0x1C.
    require(compare.target_bytes(0x4493DB, 1) == b"\x51" and
            compare.target_bytes(0x4493E2, 8).hex() == "c744242000000000",
            "push-relative count clear changed")
    image = bytes(pefile.PE(str(ROOT / "resources/th105.exe")).get_memory_mapped_image())
    native_case = observe_missing_counts(image, code)
    report = dict(result="target_cfg_closed", target_sha256=identity, address=hex(ADDRESS),
                  size=SIZE, code_sha256=SHA, instructions=744, reached=744,
                  ret0_sites=[hex(a) for a in returns], following_int3_bytes=7,
                  calls=dict(calls), layout_providers=providers,
                  missing_count_case=native_case, new_helper_credit=False,
                  limitations="One call-observer fixture; populated-deck grid and general FP/service equivalence are unproved.")
    if obj is not None:
        function = load_manifest()["units"][UNIT]["functions"][0]
        targets = compare.known_targets()
        targets.update({name: int(address, 0) for name, address in
                        (value.split("=", 1) for value in function["rel32_targets"])})
        overrides = dict(value.split("=", 1) for value in function.get("dir32_targets", []))
        candidate = compare.coff_symbol_bytes(obj, function["symbol_base"], ADDRESS, 0xFFFFFFFF,
                                              targets, compare.known_data_targets(), overrides)
        candidate_case = observe_missing_counts(image, candidate)
        require(candidate_case == native_case, "candidate observer events differ from native")
        differences = [dict(offset=index, address=hex(ADDRESS + index), target=f"{a:02x}", candidate=f"{b:02x}")
                       for index, (a, b) in enumerate(zip(code, candidate)) if a != b]
        report["candidate"] = dict(object=str(obj), section_size=len(candidate),
                                   size_difference=len(candidate) - SIZE,
                                   full_section_canonical_sha256=hashlib.sha256(candidate).hexdigest(),
                                   full_relocation_replay=True, unequal_positions=len(differences),
                                   differences=differences, observer_events_equal=32)
        report["result"] = "candidate_exact" if candidate == code else "candidate_nonexact"
    return report


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--object", type=Path)
    args = parser.parse_args()
    try:
        report = audit(args.object)
    except (OSError, ValueError, KeyError, AssertionError) as error:
        print(json.dumps(dict(result="blocked", error=str(error)), indent=2))
        return 1
    print(json.dumps(report, indent=2))
    return int(report["result"] == "candidate_nonexact")


if __name__ == "__main__":
    raise SystemExit(main())
