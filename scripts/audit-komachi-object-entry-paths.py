#!/usr/bin/env python3
"""Check eight bounded KomachiObject initializer paths with native helpers.

Six inputs complete real RETs; two stop before the real unparented-spawn body.
The selector, checked tree, frame application, FTOL and RNG execute original
instructions against data fixtures. No helper result or return is injected.
These controls earn no canonical exact credit.
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
UNIT = "exact-first-komachi-object-entry"
ADDRESS, PAYLOAD_SIZE = 0x600390, 6540
PAYLOAD_SHA256 = "fe41b8cbdcd9e6c4a28c24ca2c5220f067fff3d0f144af1294188779d99526ca"
OWNER, STACK, RETURN, VTABLE = 0x1000000, 0x2000000, 0x710000, 0x6C5FDC
RESOURCE = 0x3000000
TREE, HEAD, NODE, VECTOR, SLOT, BLOCK, FRAME, PARAMETERS = [
    RESOURCE+x for x in (0,0x100,0x200,0x300,0x400,0x1000,0x10000,0x30000)]
MT_INDEX, MT_STATE, FIRST_STATE_WORD = 0x6FA1FC, 0x6FDEF0, 1013904223
NATIVE_ENTRIES = (0x68A1A0,0x45C390,0x45C180,0x45C110,0x45C320,0x436760,
                  0x40C100,0x4073C0,0x4067D0,0x4066B0)


def cases():
    for sequence in (0,1,2,3):
        yield dict(action=930,sequence=sequence,cw=0x27F)
    yield dict(action=902,sequence=0,cw=0x27F)
    for control_word in (0x27F,0x37F):
        yield dict(action=810,sequence=2,cw=control_word)
    yield dict(action=817,sequence=0,cw=0x27F)


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
    for sequence in range(4):
        block, frame = BLOCK+sequence*0x20, FRAME+sequence*0x100
        put(block+4,"II",frame,frame+0x88)
        put(block+0x14,"B",sequence != 0)
        put(block+0x18,"II",block-0x20 if sequence else 0,
            block+0x20 if sequence < 3 else 0)
        put(frame+8,"hhhhhhb",3,0,sequence+1,sequence+2,16,24,-1)
    put(PARAMETERS,"4f",37.25,-12.5,float(case["sequence"]),0.)
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
    for offset,fmt,value in (
            (0,"I",VTABLE),(0x13C,"h",case["action"]),(0x13E,"h",9),
            (0x104,"B",255),(0xEC,"f",640.),(0xF0,"f",100.),
            (0x130,"I",VECTOR),(0x160,"I",TREE),(0x340,"I",PARAMETERS),
            (0x11C,"f",7.),(0x120,"f",8.),(0x113,"B",52)):
        engine.mem_write(OWNER+offset,struct.pack("<"+fmt,value))
    # A deterministic MT state fixture: the first real roll(15) returns9.
    # Its intermediate float product makes the two-stage rounding observable.
    engine.mem_write(MT_INDEX,struct.pack("<I",0))
    engine.mem_write(MT_STATE,struct.pack("<624I",FIRST_STATE_WORD,*range(1,624)))
    engine.mem_write(STACK+0xFF00,struct.pack("<I",RETURN))
    engine.reg_write(registers.UC_X86_REG_ECX,OWNER)
    engine.reg_write(registers.UC_X86_REG_ESP,STACK+0xFF00)
    engine.reg_write(registers.UC_X86_REG_FPCW,case["cw"])
    engine.reg_write(registers.UC_X86_REG_FPSW,0)
    engine.reg_write(registers.UC_X86_REG_FPTAG,65535)
    result, calls = {}, []

    def step(uc,address,size,unused):
        if address in NATIVE_ENTRIES:
            calls.append(hex(address))
        if address not in (RETURN,0x64CCB0):
            return
        result.update(boundary="ret" if address == RETURN else "spawn-entry",
                      actor=bytes(uc.mem_read(OWNER,0x388)).hex(),calls=calls,
                      rng_index=struct.unpack("<I",uc.mem_read(MT_INDEX,4))[0],
                      top=(uc.reg_read(registers.UC_X86_REG_FPSW)>>11)&7,
                      tags=uc.reg_read(registers.UC_X86_REG_FPTAG),
                      control=uc.reg_read(registers.UC_X86_REG_FPCW))
        esp = uc.reg_read(registers.UC_X86_REG_ESP)
        if address == RETURN:
            result["stack_delta"] = esp-(STACK+0xFF00)
        else:
            args = struct.unpack("<7I",uc.mem_read(esp+4,28))
            result.update(spawn_args=list(args[:5])+[args[6]],
                          payload=bytes(uc.mem_read(args[5],args[6]*4)).hex(),
                          receiver=uc.reg_read(registers.UC_X86_REG_ECX)-OWNER)
        uc.emu_stop()

    engine.hook_add(unicorn.UC_HOOK_CODE,step)
    engine.emu_start(ADDRESS,RETURN+1,count=30000)
    if not result or "0x4073c0" not in calls or calls.count("0x45c390") != 1:
        raise ValueError("reviewed stop or native selector/frame commit missing")
    return result


def confirm_target(case,result):
    actor = bytes.fromhex(result["actor"])
    if case["action"] in (930,902):
        expects_spawn = case["action"] == 902 or case["sequence"] == 1
        if result["boundary"] != ("spawn-entry" if expects_spawn else "ret"):
            raise ValueError("target did not confirm the action/sequence spawn guard")
        if expects_spawn:
            if result["spawn_args"] != [case["action"],0x44200000,0x42C80000,255,1,3]:
                raise ValueError("target object-request arguments changed")
            if case["action"] == 902 and result["payload"] != struct.pack("<3f",0.,0.,2.).hex():
                raise ValueError("target902 first payload changed")
        if case["action"] == 930 and actor[0x17C] != 2:
            raise ValueError("target930 mode byte changed")
    if case["action"] == 810:
        if struct.unpack_from("<2I",actor,0x11C) != (0x3FF33334,0x3FF33334):
            raise ValueError("target did not confirm rounded-product then addition")
    if result["boundary"] == "ret" and result["stack_delta"] != 4:
        raise ValueError("target did not complete an ordinary RET0")
    if result["control"] != case["cw"] or result["top"] != 0:
        raise ValueError("target x87 environment changed")


def audit(object_path):
    spec = importlib.util.spec_from_file_location(
        "komachi_object_entry_canonical",ROOT/"scripts/compare-function.py")
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
                scope="six native RETs and two real pre-spawn prefixes; later spawn body and gameplay outside scope")


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
