#!/usr/bin/env python3
"""Check six native RETs and two first-spawn loop fragments for PatchouliObject.

Original selector/frame/FTOL/MT/RNG instructions execute against data fixtures.
The loop fragments start after auxiliary setup and stop at the first genuine
spawn entry. They do not validate that setup, later iterations or the spawn
body. No helper result, return or control-flow transfer is injected.
"""
from __future__ import annotations

import argparse
import hashlib
import importlib.util
import json
from pathlib import Path
import struct

import pefile
import unicorn
from unicorn import x86_const as registers
from workflow_manifest import load_manifest

ROOT = Path(__file__).resolve().parents[1]
UNIT = "exact-first-patchouli-object-entry"
ADDRESS, PAYLOAD_SIZE = 0x52D200, 11180
PAYLOAD_SHA256 = "67ced657b52e6f61667e3621fab7a715b8c8263db759167e8848602ffeb5bccc"
LOOP_ENTRY = 0x52DFD1
OWNER, STACK, RETURN, VTABLE = 0x1000000, 0x2000000, 0x710000, 0x6C4E24
RESOURCE = 0x3000000
TREE, HEAD, NODE, VECTOR, SLOT, BLOCK, FRAME, PARAMETERS = [
    RESOURCE+x for x in (0,0x100,0x200,0x300,0x400,0x1000,0x10000,0x30000)]
MT_INDEX, MT_STATE = 0x6FA1FC, 0x6FDEF0
NATIVE_ENTRIES = (0x68A1A0,0x45C390,0x45C180,0x45C110,0x45C320,0x436760,
                  0x40C100,0x4073C0,0x4067D0,0x4066B0)


def cases():
    for control_word in (0x27F,0x37F):
        # Native temper(32904)=1648679945; real bounded roll(50)=19.
        yield dict(kind="round",action=800,sequence=1,input1_bits=0,
                   state_word=32904,cw=control_word)
    for bits in (0,0x3F800000,0x3F000000,0x7FC00000):
        yield dict(kind="guard",action=853,sequence=4,input1_bits=bits,
                   state_word=1,cw=0x27F)
    for control_word in (0x27F,0x37F):
        yield dict(kind="loop",action=830,sequence=0,input1_bits=0,
                   state_word=1,cw=control_word)


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
    for sequence in range(14):
        block, frame = BLOCK+sequence*0x20, FRAME+sequence*0x100
        put(block+4,"II",frame,frame+0x88)
        put(block+0x14,"B",sequence != 0)
        put(block+0x18,"II",block-0x20 if sequence else 0,
            block+0x20 if sequence < 13 else 0)
        put(frame+8,"hhhhhhb",3,0,sequence+1,sequence+2,16,24,-1)
    put(PARAMETERS,"fIff",37.25,case["input1_bits"],float(case["sequence"]),0.)
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
    engine.mem_write(MT_STATE,struct.pack("<624I",case["state_word"],*range(1,624)))
    put(STACK+0xFF00,"I",RETURN)
    engine.reg_write(registers.UC_X86_REG_ECX,OWNER)
    engine.reg_write(registers.UC_X86_REG_ESP,STACK+0xFF00)
    engine.reg_write(registers.UC_X86_REG_FPCW,case["cw"])
    engine.reg_write(registers.UC_X86_REG_FPSW,0)
    engine.reg_write(registers.UC_X86_REG_FPTAG,65535)
    start = ADDRESS
    if case["kind"] == "loop":
        # Real first-iteration stack/receiver inputs after the auxiliary prefix.
        # The first seven bytes must remain PUSH40; CALL native bounded RNG.
        offset = LOOP_ENTRY-ADDRESS
        if code[offset:offset+7] != image[LOOP_ENTRY-0x400000:LOOP_ENTRY-0x400000+7]:
            raise ValueError("reviewed loop entry no longer identifies the first RNG call")
        start, stack = LOOP_ENTRY, STACK+0xFF00-36
        engine.reg_write(registers.UC_X86_REG_ESP,stack)
        engine.reg_write(registers.UC_X86_REG_ESI,OWNER)
        engine.reg_write(registers.UC_X86_REG_EBX,0)
        engine.reg_write(registers.UC_X86_REG_EDI,0)
        put(OWNER+0x13E,"h",0)
        put(OWNER+0x17C,"B",4)
        put(OWNER+0x184,"B",1)
        put(OWNER+0xF8,"f",60.)
        put(stack+0xC,"f",0.)
        engine.mem_write(stack+0x14,struct.pack("<4f",0.,15.,3.,0.))
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
        boundary = 0x64CCB0 if case["kind"] == "loop" else RETURN
        if address != boundary:
            return
        result.update(boundary="spawn-entry" if case["kind"] == "loop" else "ret",
                      actor=bytes(uc.mem_read(OWNER,0x388)).hex(),calls=calls,
                      rolls=rolls,mt_values=mt_values,
                      rng_index=struct.unpack("<I",uc.mem_read(MT_INDEX,4))[0],
                      top=(uc.reg_read(registers.UC_X86_REG_FPSW)>>11)&7,
                      tags=uc.reg_read(registers.UC_X86_REG_FPTAG),
                      control=uc.reg_read(registers.UC_X86_REG_FPCW))
        esp = uc.reg_read(registers.UC_X86_REG_ESP)
        if case["kind"] == "loop":
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
    if case["kind"] != "loop" and (
            "0x4073c0" not in calls or calls.count("0x45c390") != 1):
        raise ValueError("native selector/frame commit missing")
    return result


def confirm_target(case,result):
    actor = bytes.fromhex(result["actor"])
    if case["kind"] == "round":
        if result["rolls"] != [dict(bound=50,value=19)] or result["mt_values"] != [1648679945]:
            raise ValueError("fixture did not produce the reviewed native roll19")
        if struct.unpack_from("<2f",actor,0x11C) != (1.190000057220459,)*2:
            raise ValueError("target product-rounding boundary changed")
    elif case["kind"] == "guard":
        bits = case["input1_bits"]
        expected = {0:(0.5,1.,2.),0x3F800000:(struct.unpack('<f',struct.pack('<f',0.2))[0],1.,-4.)}.get(bits,(0.,0.,0.))
        if struct.unpack_from("<3f",actor,0x370) != expected:
            raise ValueError("target ordered H[1] equality guard changed")
        bound = {0:5,0x3F800000:2}.get(bits)
        if result["rolls"] != ([] if bound is None else [dict(bound=bound,value=0)]):
            raise ValueError("target guard RNG side effects changed")
        if struct.unpack_from("<2f",actor,0x11C) != (7.,0.):
            raise ValueError("target horizontal/vertical scale distinction changed")
    else:
        if result["rolls"] != [dict(bound=40,value=0)] or result["mt_values"] != [4194449]:
            raise ValueError("fixture did not produce the reviewed native roll0")
        if result["spawn_args"] != [830,0x44200000,0x42C80000,255,1,4] or result["receiver"] != 0:
            raise ValueError("target first four-word request contract changed")
        if result["payload"] != struct.pack("<4f",4294967296.,15.,3.,0.).hex():
            raise ValueError("target unsigned integer subtraction/conversion changed")
        if "0x45c390" in result["calls"]:
            raise ValueError("loop fragment scope unexpectedly included the prefix")
    if result["rng_index"] != len(result["rolls"]):
        raise ValueError("target consumed an unreviewed MT state word")
    if result["boundary"] == "ret" and result["stack_delta"] != 4:
        raise ValueError("target did not complete a real RET0")
    if result["control"] != case["cw"] or result["top"] != 0:
        raise ValueError("target x87 environment changed")


def audit(object_path, kind=None):
    spec = importlib.util.spec_from_file_location(
        "patchouli_object_entry_canonical",ROOT/"scripts/compare-function.py")
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
                scope="default: six real RETs for product rounding/ordered equality and two first-spawn loop fragments for unsigned subtraction; auxiliary prefix, later iterations and spawn body outside scope")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--object",type=Path)
    parser.add_argument("--kind",choices=("round","guard","loop"),
                        help="restrict to one concrete ambiguity, including negative controls")
    args = parser.parse_args()
    unit = load_manifest()["units"][UNIT]
    report = audit(args.object or ROOT/unit["object"],args.kind)
    print(json.dumps(report,indent=2))
    return int(report["mismatch_count"] != 0)


if __name__ == "__main__":
    raise SystemExit(main())
