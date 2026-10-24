#!/usr/bin/env python3
"""Check twelve native SuikaObject RET paths for ordered signs and x87 lifetime.

Original selector/frame, motion, MT and RNG instructions execute against data
fixtures. No helper result or return is injected. These scoped controls earn
no canonical exact credit.
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
UNIT = "exact-first-suika-object-entry"
ADDRESS, PAYLOAD_SIZE = 0x5BD380, 9284
PAYLOAD_SHA256 = "9c143cb673cd84d287096bb3cc4e653bfb0796ff1bdc7402219d19d5bc079de1"
OWNER, STACK, RETURN, VTABLE = 0x1000000, 0x2000000, 0x710000, 0x6C5B04
RESOURCE = 0x3000000
TREE, HEAD, NODE, VECTOR, SLOT, BLOCK, FRAME, PARAMETERS = [
    RESOURCE+x for x in (0,0x100,0x200,0x300,0x400,0x1000,0x10000,0x30000)]
MT_INDEX, MT_STATE = 0x6FA1FC, 0x6FDEF0
NATIVE_ENTRIES = (0x45C390,0x45C180,0x45C110,0x45C320,0x436760,
                  0x40C100,0x4073C0,0x435160,0x4067D0,0x4066B0)


def cases():
    for bits in (0x3F800000,0xBF800000,0,0x7FC00000):
        yield dict(action=812,sequence=0,cw=0x27F,vertical_bits=bits)
    for action in (815,940):
        for sequence in (4,5):
            for control in (0x27F,0x37F):
                yield dict(action=action,sequence=sequence,cw=control,vertical_bits=0x40000000)


def seed_for_roll(bound,roll):
    # Find a data fixture for the actual MT temper/division instructions.
    # The native return is independently checked by the instruction hook.
    for index in range(10000):
        seed = (index*1664525+1013904223)&0xFFFFFFFF
        value = seed ^ (seed>>11)
        value ^= (value<<7)&0x9D2C5680
        value ^= (value<<15)&0xEFC60000
        value = (value ^ (value>>18))&0xFFFFFFFF
        if value//(0xFFFFFFFF//bound) == roll:
            return seed
    raise ValueError("no bounded MT fixture for requested roll")


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
    put(PARAMETERS,"4f",1.,0.,float(case["sequence"]),-0.3)
    put(PARAMETERS+4,"I",case["vertical_bits"])
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
            (0x11C,"f",7.),(0x120,"f",8.),(0x113,"B",52),
            (0x348,"I",OWNER+0x1000)):
        put(OWNER+offset,fmt,value)
    put(OWNER+0x1000+0xEC,"f",100.)
    put(OWNER+0x1000+0xF0,"f",20.)
    put(MT_INDEX,"I",0)
    seeds = [seed_for_roll(100,9),seed_for_roll(360,1),seed_for_roll(10,3)]
    engine.mem_write(MT_STATE,struct.pack("<624I",*seeds,*range(3,624)))
    put(STACK+0xFF00,"I",RETURN)
    engine.reg_write(registers.UC_X86_REG_ECX,OWNER)
    engine.reg_write(registers.UC_X86_REG_ESP,STACK+0xFF00)
    engine.reg_write(registers.UC_X86_REG_FPCW,case["cw"])
    engine.reg_write(registers.UC_X86_REG_FPSW,0)
    engine.reg_write(registers.UC_X86_REG_FPTAG,65535)
    result, calls, rolls = {}, [], []

    def step(uc,address,size,unused):
        if address in NATIVE_ENTRIES:
            calls.append(hex(address))
        if address == 0x4067EA:
            esp = uc.reg_read(registers.UC_X86_REG_ESP)
            rolls.append(dict(bound=struct.unpack("<I",uc.mem_read(esp+4,4))[0],
                              value=uc.reg_read(registers.UC_X86_REG_EAX)))
        if address != RETURN:
            return
        result.update(boundary="ret",actor=bytes(uc.mem_read(OWNER,0x388)).hex(),
                      calls=calls,rolls=rolls,
                      rng_index=struct.unpack("<I",uc.mem_read(MT_INDEX,4))[0],
                      stack_delta=uc.reg_read(registers.UC_X86_REG_ESP)-(STACK+0xFF00),
                      top=(uc.reg_read(registers.UC_X86_REG_FPSW)>>11)&7,
                      tags=uc.reg_read(registers.UC_X86_REG_FPTAG),
                      control=uc.reg_read(registers.UC_X86_REG_FPCW))
        uc.emu_stop()

    engine.hook_add(unicorn.UC_HOOK_CODE,step)
    engine.emu_start(ADDRESS,RETURN+1,count=30000)
    if not result or "0x4073c0" not in calls or calls.count("0x45c390") != 1:
        raise ValueError("real RET or native selector/frame commit missing")
    return result


def confirm_target(case,result):
    actor = bytes.fromhex(result["actor"])
    if case["action"] == 812:
        expected = 0xBDCCCCCD if case["vertical_bits"] == 0x3F800000 else 0x3DCCCCCD
        if struct.unpack_from("<I",actor,0x370)[0] != expected:
            raise ValueError("target ordered vertical-sign predicate changed")
        if struct.unpack_from("<I",actor,0xF8)[0] != case["vertical_bits"]:
            raise ValueError("target direct vertical input changed")
        if result["rolls"] or "0x435160" in result["calls"]:
            raise ValueError("target812 native path changed")
    else:
        # 3*double(float0.1) + float(-0.3) = -2**-27. A float
        # product capture instead rounds to float0.3 and cancels to zero.
        if struct.unpack_from("<2I",actor,0x11C) != (0xB2000000,0xB2000000):
            raise ValueError("target unrounded product then input addition changed")
        if result["rolls"] != [dict(bound=100,value=9),dict(bound=360,value=1),dict(bound=10,value=3)]:
            raise ValueError("fixture did not execute the requested native RNG rolls")
        if result["rng_index"] != 3 or result["calls"].count("0x435160") != 1:
            raise ValueError("target RNG/motion path changed")
    if result["stack_delta"] != 4 or result["control"] != case["cw"] or result["top"] != 0:
        raise ValueError("target RET/x87 contract changed")


def audit(object_path):
    spec = importlib.util.spec_from_file_location(
        "suika_object_entry_canonical",ROOT/"scripts/compare-function.py")
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
                scope="twelve native RETs: ordered vertical-sign predicate and unrounded random product/input sum; other actions outside scope")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--object",type=Path)
    args = parser.parse_args()
    unit = load_manifest()["units"][UNIT]
    report = audit(args.object or ROOT/unit["object"])
    print(json.dumps(report,indent=2))
    return int(report["mismatch_count"] != 0)


if __name__ == "__main__":
    raise SystemExit(main())
