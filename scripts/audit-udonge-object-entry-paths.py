#!/usr/bin/env python3
"""Check native820/821 RETs for the observed input-load-before-alpha-clear order.

The native selector, checked tree and frame instructions execute against read-only
fixtures. Two ordinary inputs and two inputs aliasing the alpha byte distinguish
load epochs. No helper result, return or control-flow transfer is injected.
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
UNIT = "exact-first-udonge-object-entry"
ADDRESS, PAYLOAD_SIZE = 0x5DF0E0, 11112
PAYLOAD_SHA256 = "bf3801d220492a28d82be486b7c1a8706c83e8e4edfd2b6ef403618148218654"
OWNER, STACK, RETURN, VTABLE = 0x1000000, 0x2000000, 0x710000, 0x6C5DA4
RESOURCE = 0x3000000
TREE, HEAD, NODE, VECTOR, SLOT, BLOCK, FRAME, PARAMETERS = [
    RESOURCE+x for x in (0,0x100,0x200,0x300,0x400,0x1000,0x10000,0x30000)]
MT_INDEX, MT_STATE = 0x6FA1FC, 0x6FDEF0
NATIVE_ENTRIES = (0x68A1A0,0x45C390,0x45C180,0x45C110,0x45C320,0x436760,
                  0x40C100,0x4073C0,0x4067D0,0x4066B0)


def cases():
    for action in (820,821):
        for alias in (False,True):
            yield dict(kind="alias",action=action,sequence=3,input1_bits=0,
                       state_word=1,cw=0x27F,alias=alias)


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
    if case["alias"]:
        # H[0] overlaps alpha113; H[2] overlaps the later scale destination.
        put(OWNER+0x340,"I",OWNER+0x113)
        put(OWNER+0x113,"I",0x3F800034)
        put(OWNER+0x11B,"f",3.)
    put(MT_INDEX,"I",0)
    state = [case["state_word"],*range(1,624)]
    engine.mem_write(MT_STATE,struct.pack("<624I",*state))
    put(STACK+0xFF00,"I",RETURN)
    engine.reg_write(registers.UC_X86_REG_ECX,OWNER)
    engine.reg_write(registers.UC_X86_REG_ESP,STACK+0xFF00)
    engine.reg_write(registers.UC_X86_REG_FPCW,case["cw"])
    engine.reg_write(registers.UC_X86_REG_FPSW,0)
    engine.reg_write(registers.UC_X86_REG_FPTAG,65535)
    start = ADDRESS
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
        if address != RETURN:
            return
        result.update(boundary="ret",
                      actor=bytes(uc.mem_read(OWNER,0x388)).hex(),calls=calls,
                      rolls=rolls,mt_values=mt_values,
                      rng_index=struct.unpack("<I",uc.mem_read(MT_INDEX,4))[0],
                      top=(uc.reg_read(registers.UC_X86_REG_FPSW)>>11)&7,
                      tags=uc.reg_read(registers.UC_X86_REG_FPTAG),
                      control=uc.reg_read(registers.UC_X86_REG_FPCW))
        esp = uc.reg_read(registers.UC_X86_REG_ESP)
        result["stack_delta"] = esp-(STACK+0xFF00)
        uc.emu_stop()

    engine.hook_add(unicorn.UC_HOOK_CODE,step)
    engine.emu_start(start,RETURN+1,count=30000)
    if not result:
        raise ValueError("reviewed native boundary was not reached")
    if (
            "0x4073c0" not in calls or calls.count("0x45c390") != 1):
        raise ValueError("native selector/frame commit missing")
    return result


def confirm_target(case,result):
    actor = bytes.fromhex(result["actor"])
    input_value = struct.unpack("<f",struct.pack("<I",0x3F800034))[0] if case["alias"] else 37.25
    scale = struct.unpack("<f",struct.pack("<f",input_value-struct.unpack("<f",struct.pack("<f",0.3))[0]))[0]
    if struct.unpack_from("<2f",actor,0x11C) != (scale,scale) or actor[0x113] != 0:
        raise ValueError("target must load H0 before clearing alpha, then publish consumed scale")
    if result["rolls"] or result["rng_index"] != 0 or result["stack_delta"] != 4:
        raise ValueError("target RNG/RET0 contract changed")
    if result["control"] != case["cw"] or result["top"] != 0:
        raise ValueError("target x87 environment changed")


def audit(object_path):
    spec = importlib.util.spec_from_file_location(
        "udonge_object_entry_canonical",ROOT/"scripts/compare-function.py")
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
                scope="four complete real RETs for820/821 normal and alpha-alias inputs; native selector/tree/frame instructions; no injected helper execution")


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
