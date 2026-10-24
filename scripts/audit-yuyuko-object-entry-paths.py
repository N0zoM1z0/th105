#!/usr/bin/env python3
"""Check four native RETs and four first-spawn fragments for YuyukoObject.

Native selector/frame/FTOL/MT/RNG instructions execute against read-only fixtures.
Fragments start after motion setup and stop at a genuine spawn entry; earlier
setup, later loop iterations and spawn bodies are outside their scope. No helper
result, return or control-flow transfer is injected.
"""
from __future__ import annotations

import argparse
import hashlib
import importlib.util
import json
from pathlib import Path
import struct

import capstone
import pefile
import unicorn
from unicorn import x86_const as registers
from workflow_manifest import load_manifest

ROOT = Path(__file__).resolve().parents[1]
UNIT = "exact-first-yuyuko-object-entry"
ADDRESS, PAYLOAD_SIZE = 0x578000, 11143
METADATA_SIZE = 29*4+199
PAYLOAD_SHA256 = "5cf0ed1dfe099e8bffaa78ffd2620fd6cae98d370750c04766adcbd90631702d"
OWNER, STACK, RETURN, VTABLE = 0x1000000, 0x2000000, 0x710000, 0x6C55C4
RESOURCE = 0x3000000
TREE, HEAD, NODE, VECTOR, SLOT, BLOCK, FRAME, PARAMETERS = [
    RESOURCE+x for x in (0,0x100,0x200,0x300,0x400,0x1000,0x10000,0x30000)]
MT_INDEX, MT_STATE = 0x6FA1FC, 0x6FDEF0
NATIVE_ENTRIES = (0x68A1A0,0x45C390,0x45C180,0x45C110,0x45C320,0x436760,
                  0x40C100,0x4073C0,0x4067D0,0x4066B0)


def cases():
    for control_word in (0x27F,0x37F):
        yield dict(kind="round",action=852,sequence=3,input1_bits=0,
                   state_word=32904,cw=control_word)
    for sequence in (0,1):
        yield dict(kind="retained",action=922,sequence=sequence,input1_bits=0,
                   state_word=1,cw=0x27F)
    for control_word in (0x27F,0x37F):
        yield dict(kind="angle",action=857,sequence=12,input1_bits=0,
                   state_word=32904,cw=control_word)
    for bits in (0x3F345678,0xBE800000):
        yield dict(kind="packet",action=816,sequence=12,input1_bits=bits,
                   state_word=1,cw=0x27F)


def fragment_entry(image,code,kind):
    """Map the same independently attested physical motion call in both bodies."""
    decoder = capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
    decoder.detail = True

    def motions(blob):
        instructions = list(decoder.disasm(blob[:-METADATA_SIZE],ADDRESS))
        tables = [i.operands[0].mem.disp for i in instructions
                  if i.mnemonic == "jmp" and i.operands[0].type == capstone.x86.X86_OP_MEM]
        if tables != [ADDRESS+len(blob)-METADATA_SIZE]:
            raise ValueError("reviewed switch-metadata boundary changed")
        return [i for i in instructions
                if i.mnemonic == "call" and i.operands[0].type == capstone.x86.X86_OP_IMM
                and i.operands[0].imm == 0x435160]

    target = image[ADDRESS-0x400000:ADDRESS-0x400000+PAYLOAD_SIZE]
    target_motion,source_motion = motions(target),motions(code)
    if len(target_motion) != 23 or len(source_motion) != 23:
        raise ValueError("reviewed motion-call inventory changed")
    site = 0x578B5D if kind == "packet" else 0x57A2E6
    index = next(n for n,i in enumerate(target_motion) if i.address == site)
    start = source_motion[index].address+5
    if kind == "packet":
        if code[start-ADDRESS:start-ADDRESS+2] != bytes.fromhex("d9ee"):
            raise ValueError("packet fragment must start at the real FLDZ")
        return start
    instructions = list(decoder.disasm(code[start-ADDRESS:start-ADDRESS+24],start))
    for i in instructions:
        if i.mnemonic == "push" and i.operands[0].type == capstone.x86.X86_OP_IMM and i.operands[0].imm == 20:
            offset = i.address-ADDRESS
            call = list(decoder.disasm(code[offset+2:offset+7],i.address+2))
            if (len(call) != 1 or call[0].mnemonic != "call"
                    or call[0].operands[0].type != capstone.x86.X86_OP_IMM
                    or call[0].operands[0].imm != 0x4067D0):
                raise ValueError("angle fragment must start at real PUSH20; CALL bounded RNG")
            return i.address
        if i.mnemonic not in ("fldz","fstp","nop","lea"):
            raise ValueError("unreviewed instruction before angle loop entry")
    raise ValueError("angle-loop entry missing")


def resource_graph(case):
    image = bytearray(0x40000)

    def put(address, fmt, *values):
        struct.pack_into("<"+fmt,image,address-RESOURCE,*values)

    put(TREE+4,"II",HEAD,1)
    put(HEAD,"III",NODE,NODE,NODE)
    put(HEAD+0x14,"BB",1,1)
    put(NODE,"IIIiI",HEAD,HEAD,HEAD,case["action"],BLOCK)
    put(NODE+0x14,"BB",1,0)
    put(VECTOR+4,"III",SLOT,SLOT+4,SLOT+4)
    for sequence in range(17):
        block, frame = BLOCK+sequence*0x20, FRAME+sequence*0x100
        put(block+4,"II",frame,frame+0x88)
        put(block+0x14,"B",sequence != 0)
        put(block+0x18,"II",block-0x20 if sequence else 0,
            block+0x20 if sequence < 16 else 0)
        put(frame+8,"hhhhhhb",3,0,sequence+1,sequence+2,16,24,-1)
    put(PARAMETERS,"fIff",16777216. if case["kind"] == "angle" else 37.25,case["input1_bits"],float(case["sequence"]),0.)
    return bytes(image)


def execute(image, code, case):
    engine = unicorn.Uc(unicorn.UC_ARCH_X86,unicorn.UC_MODE_32)
    engine.mem_map(0x400000,(len(image)+4095)//4096*4096)
    engine.mem_write(0x400000,image)
    engine.mem_write(ADDRESS,code)
    engine.mem_map(OWNER,65536)
    engine.mem_map(STACK,65536)
    engine.mem_map(RESOURCE,0x40000,unicorn.UC_PROT_READ)
    engine.mem_write(RESOURCE,resource_graph(case))
    engine.mem_map(RETURN,4096)

    def put(address,fmt,value):
        engine.mem_write(address,struct.pack("<"+fmt,value))

    for offset,fmt,value in (
            (0,"I",VTABLE),(0x13C,"h",case["action"]),(0x13E,"h",9),
            (0x104,"B",255),(0xEC,"f",640.),(0xF0,"f",100.),
            (0x130,"I",VECTOR),(0x160,"I",TREE),(0x340,"I",PARAMETERS),
            (0x11C,"f",7.),(0x120,"f",8.),(0x113,"B",52)):
        put(OWNER+offset,fmt,value)
    put(MT_INDEX,"I",0)
    state = [case["state_word"],*range(1,624)]
    if case["kind"] == "round":
        state[3] = 2400000  # native temper=2108212345, real roll(20)=9
    engine.mem_write(MT_STATE,struct.pack("<624I",*state))
    put(STACK+0xFF00,"I",RETURN)
    engine.reg_write(registers.UC_X86_REG_ECX,OWNER)
    engine.reg_write(registers.UC_X86_REG_ESP,STACK+0xFF00)
    engine.reg_write(registers.UC_X86_REG_FPCW,case["cw"])
    engine.reg_write(registers.UC_X86_REG_FPSW,0)
    engine.reg_write(registers.UC_X86_REG_FPTAG,65535)
    start = ADDRESS
    fragment = case["kind"] in ("angle","packet")
    if fragment:
        start,stack = fragment_entry(image,code,case["kind"]),STACK+0xFF00-32
        engine.reg_write(registers.UC_X86_REG_ESP,stack)
        engine.reg_write(registers.UC_X86_REG_ESI,OWNER)
        engine.reg_write(registers.UC_X86_REG_EBX,0)
        engine.reg_write(registers.UC_X86_REG_EDI,VTABLE)
        put(OWNER+0x13E,"h",case["sequence"])
        put(stack+0xC,"f",0.)
        engine.mem_write(stack+0x14,struct.pack("<III",0,case["input1_bits"],0))
    result, calls, rolls, mt_values = {}, [], [], []

    def step(uc,address,size,unused):
        if address in NATIVE_ENTRIES:
            calls.append(hex(address))
        if address == 0x4067C6:
            mt_values.append(uc.reg_read(registers.UC_X86_REG_EAX))
        if address == 0x4067EA:
            esp = uc.reg_read(registers.UC_X86_REG_ESP)
            rolls.append(dict(bound=struct.unpack("<I",uc.mem_read(esp+4,4))[0],
                              value=uc.reg_read(registers.UC_X86_REG_EAX)))
        boundary = 0x64CCB0 if fragment else RETURN
        if address != boundary:
            return
        result.update(boundary="spawn-entry" if fragment else "ret",
                      actor=bytes(uc.mem_read(OWNER,0x388)).hex(),calls=calls,
                      rolls=rolls,mt_values=mt_values,
                      rng_index=struct.unpack("<I",uc.mem_read(MT_INDEX,4))[0],
                      top=(uc.reg_read(registers.UC_X86_REG_FPSW)>>11)&7,
                      tags=uc.reg_read(registers.UC_X86_REG_FPTAG),
                      control=uc.reg_read(registers.UC_X86_REG_FPCW))
        esp = uc.reg_read(registers.UC_X86_REG_ESP)
        if fragment:
            args = struct.unpack("<7I",uc.mem_read(esp+4,28))
            result.update(spawn_args=list(args[:5])+[args[6]],
                          payload=bytes(uc.mem_read(args[5],args[6]*4)).hex(),
                          receiver=uc.reg_read(registers.UC_X86_REG_ECX)-OWNER)
        else:
            result["stack_delta"] = esp-(STACK+0xFF00)
        uc.emu_stop()

    engine.hook_add(unicorn.UC_HOOK_CODE,step)
    engine.emu_start(start,RETURN+1,count=30000)
    if not result:
        raise ValueError("reviewed native boundary was not reached")
    if not fragment and (
            "0x4073c0" not in calls or calls.count("0x45c390") != 1):
        raise ValueError("native selector/frame commit missing")
    return result


def confirm_target(case,result):
    actor = bytes.fromhex(result["actor"])
    if case["kind"] == "round":
        if result["rolls"] != [dict(bound=n,value=v) for n,v in ((100,38),(180,0),(360,0),(20,9),(100,0))]:
            raise ValueError("native five-draw rounding fixture changed")
        if struct.unpack_from("<f",actor,0x374)[0] != -1.9000000953674316:
            raise ValueError("target consumed-product rounding changed")
        if struct.unpack_from("<h",actor,0x364)[0] != 60 or actor[0x113] != 0:
            raise ValueError("target timer/visibility continuation changed")
    elif case["kind"] == "retained":
        if struct.unpack_from("<f",actor,0x10C)[0] != 100. or result["rolls"]:
            raise ValueError("retained x87 value must write F10C100 in both sequences")
    else:
        if result["receiver"] != 0:
            raise ValueError("first request receiver changed")
        if case["kind"] == "angle":
            if result["spawn_args"] != [857,0x44200000,0x42C80000,255,0xFFFFFFFF,3]:
                raise ValueError("target857 first request contract changed")
            if result["payload"] != struct.pack("<3f",16777213.,10.,0.).hex():
                raise ValueError("target857 prematurely rounded RNG20+H0 before subtracting10")
            if result["rolls"] != [dict(bound=20,value=7),dict(bound=20,value=0)]:
                raise ValueError("native two-draw angle fixture changed")
        else:
            if result["spawn_args"] != [816,0x44200000,0x42C80000,255,1,3]:
                raise ValueError("target816 first request contract changed")
            if result["payload"] != struct.pack("<III",0,case["input1_bits"],0x41500000).hex() or result["rolls"]:
                raise ValueError("target816 must leave second packet word untouched")
        if "0x45c390" in result["calls"]:
            raise ValueError("fragment unexpectedly included selector/setup")
    if result["rng_index"] != len(result["rolls"]):
        raise ValueError("target consumed an unreviewed MT state word")
    if result["boundary"] == "ret" and result["stack_delta"] != 4:
        raise ValueError("target did not complete a real RET0")
    if result["control"] != case["cw"] or result["top"] != 0:
        raise ValueError("target x87 environment changed")


def audit(object_path, kind=None):
    spec = importlib.util.spec_from_file_location(
        "yuyuko_object_entry_canonical",ROOT/"scripts/compare-function.py")
    canonical = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(canonical)
    identity = canonical.verify_target()
    target = canonical.target_bytes(ADDRESS,PAYLOAD_SIZE)
    if hashlib.sha256(target).hexdigest() != PAYLOAD_SHA256:
        raise ValueError("complete target payload changed")
    for slot,destination in ((0x0C,0x45C390),(0x1C,0x45C180),(0x3C,ADDRESS)):
        if struct.unpack("<I",canonical.target_bytes(VTABLE+slot,4))[0] != destination:
            raise ValueError("reviewed primary vtable cell changed")
    unit = load_manifest()["units"][UNIT]
    function, = unit["functions"]
    if int(function["address"],0) != ADDRESS:
        raise ValueError("configured root changed")
    targets = canonical.known_targets()
    for binding in function["rel32_targets"]:
        name,value = binding.rsplit("=",1)
        targets[name] = int(value,0)
    candidate = canonical.coff_symbol_bytes(
        object_path,function["symbol_base"],ADDRESS,0xFFFFFFFF,
        targets,canonical.known_data_targets())
    image = pefile.PE(str(ROOT/"resources/th105.exe")).get_memory_mapped_image()
    count, failures, digest = 0, [], hashlib.sha256()
    for case in cases():
        if kind is not None and case["kind"] != kind:
            continue
        expected,actual = (execute(image,code,case) for code in (target,candidate))
        confirm_target(case,expected)
        count += 1
        digest.update(json.dumps(case,sort_keys=True).encode())
        if expected != actual:
            failures.append(dict(case=case,differing_fields=[
                key for key in sorted(expected.keys()|actual.keys())
                if expected.get(key) != actual.get(key)]))
    return dict(diagnostic_only=True,target_sha256=identity,
                candidate_sha256=hashlib.sha256(candidate).hexdigest(),count=count,
                vector_sha256=digest.hexdigest(),mismatch_count=len(failures),failures=failures,
                selected_kind=kind or "all",
                scope="four real RETs for852 product rounding/922 retained value; four816/857 first-spawn fragments for untouched packet word/unrounded addition; motion setup, later iterations and spawn bodies outside fragment scope")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--object",type=Path)
    parser.add_argument("--kind",choices=("round","retained","angle","packet"),
                        help="restrict to one concrete ambiguity, including negative controls")
    args = parser.parse_args()
    unit = load_manifest()["units"][UNIT]
    report = audit(args.object or ROOT/unit["object"],args.kind)
    print(json.dumps(report,indent=2))
    return int(report["mismatch_count"] != 0)


if __name__ == "__main__":
    raise SystemExit(main())
