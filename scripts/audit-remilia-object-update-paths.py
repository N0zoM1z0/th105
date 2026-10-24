#!/usr/bin/env python3
"""Check angle/ordered857 H3 prefixes and852/855/856 shared fade exits.

Execute actual atan2, FTOL and lookup instructions to the first spawn/advance.
The mapped PE supplies zero-initialized lookup-table fixtures. No helper return,
instruction or control-flow transfer is injected. This is a bounded diagnostic.
Fade fixtures reach actual RET0 or the first animation call.
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
UNIT = "exact-first-remilia-object-update"
ADDRESS, PAYLOAD_SIZE = 0x557690, 18388
PAYLOAD_SHA256 = "793c1954983d385b07ead1e850f95b4c521448100500074eaa0b371e2f3b0cd6"
OWNER, STACK, PARENT, PARAMETERS, TARGET, RETURN = (
    0x1000000,0x2000000,0x3000000,0x3001000,0x3002000,0x710000)
NATIVE_ENTRIES = (0x406540,0x406360,0x4063D0,0x68A1A0)


def float_bits(value):
    return struct.unpack("<I",struct.pack("<f",value))[0]


def cases():
    for action,parent_action in ((816,525),(857,607),(900,710)):
        for angle in (179.,-540.):
            yield dict(action=action,parent_action=parent_action,sequence=1,
                       angle=angle,h3_bits=float_bits(45.),parent_hp=100,timer=1,
                       kind="angle")
    for h3_bits in (*[float_bits(x) for x in (44.999,45.,45.001)],0x7FC00000):
        yield dict(action=857,parent_action=607,sequence=1,angle=37.25,
                   h3_bits=h3_bits,parent_hp=100,timer=1,kind="ordered_h3")
    for action in (852,855,856):
        for sequence in (0,1):
            for alpha in (9,10):
                yield dict(action=action,parent_action=0,sequence=sequence,
                           angle=37.25,h3_bits=0,parent_hp=100,timer=1,
                           kind="fade",alpha=alpha)


def execute(image,code,case):
    engine = unicorn.Uc(unicorn.UC_ARCH_X86,unicorn.UC_MODE_32)
    engine.mem_map(0x400000,(len(image)+4095)//4096*4096)
    engine.mem_write(0x400000,image)
    engine.mem_write(ADDRESS,code)
    for base in (OWNER,STACK,PARENT):
        engine.mem_map(base,65536)
    engine.mem_map(RETURN,4096)

    def put(address,fmt,*values):
        engine.mem_write(address,struct.pack("<"+fmt,*values))

    for offset,fmt,value in (
            (0,"I",0x6C533C),(0x13C,"h",case["action"]),
            (0x13E,"h",case["sequence"]),(0x144,"i",case["timer"]),
            (0x180,"i",0),(0x330,"i",3),(0x104,"B",255),
            (0xEC,"f",640.),(0xF0,"f",100.),(0x340,"I",PARAMETERS),
            (0x348,"I",PARENT),(0x170,"I",TARGET),(0x113,"B",case.get("alpha",180)),
            (0x11C,"f",1.),(0x120,"f",1.),(0x370,"f",3.25),(0x374,"f",5.5)):
        put(OWNER+offset,fmt,value)
    put(PARENT+0x13C,"h",case["parent_action"])
    put(PARENT+0x13E,"h",1)
    put(PARENT+0x174,"h",case["parent_hp"])
    put(PARAMETERS,"fffI",case["angle"],10.,1.,case["h3_bits"])
    put(TARGET+0xEC,"f",760.)
    put(TARGET+0xF0,"f",100.)
    put(STACK+0xFF00,"I",RETURN)
    engine.reg_write(registers.UC_X86_REG_ESP,STACK+0xFF00)
    engine.reg_write(registers.UC_X86_REG_ECX,OWNER)
    engine.reg_write(registers.UC_X86_REG_FPCW,0x27F)
    engine.reg_write(registers.UC_X86_REG_FPSW,0)
    engine.reg_write(registers.UC_X86_REG_FPTAG,0xFFFF)
    calls, result = [], {}

    def step(uc,address,size,unused):
        if address in NATIVE_ENTRIES:
            calls.append(hex(address))
        if address not in (0x64CCB0,0x4351C0,RETURN):
            return
        result.update(boundary=hex(address),
                      owner=bytes(uc.mem_read(OWNER,0x388)).hex(),calls=calls,
                      top=(uc.reg_read(registers.UC_X86_REG_FPSW)>>11)&7,
                      control=uc.reg_read(registers.UC_X86_REG_FPCW))
        if address == 0x64CCB0:
            esp = uc.reg_read(registers.UC_X86_REG_ESP)
            args = struct.unpack("<7I",uc.mem_read(esp+4,28))
            result["arguments"] = [*args[:5],args[6]]
            result["receiver"] = uc.reg_read(registers.UC_X86_REG_ECX)
            result["payload"] = bytes(uc.mem_read(args[5],args[6]*4)).hex()
        if address == RETURN:
            result["stack_delta"] = uc.reg_read(registers.UC_X86_REG_ESP)-(STACK+0xFF00)
        uc.emu_stop()

    engine.hook_add(unicorn.UC_HOOK_CODE,step)
    engine.emu_start(ADDRESS,RETURN+1,count=20000)
    if not result:
        raise ValueError("native prefix did not reach a reviewed first call/RET boundary")
    return result


def audit(object_path):
    spec = importlib.util.spec_from_file_location(
        "remilia_update_canonical",ROOT/"scripts/compare-function.py")
    if spec is None or spec.loader is None:
        raise ValueError("canonical comparator unavailable")
    canonical = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(canonical)
    identity = canonical.verify_target()
    target = canonical.target_bytes(ADDRESS,PAYLOAD_SIZE)
    if hashlib.sha256(target).hexdigest() != PAYLOAD_SHA256:
        raise ValueError("complete target payload changed")
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
    results = []
    for case in cases():
        expected,actual = (execute(image,code,case) for code in (target,candidate))
        h3 = struct.unpack("<f",struct.pack("<I",case["h3_bits"]))[0]
        if case["kind"] == "fade":
            want = RETURN if case["alpha"] < 10 else 0x4351C0
        else:
            want = 0x4351C0 if case["action"] == 857 and not h3 <= 45 else 0x64CCB0
        if int(expected["boundary"],0) != want:
            raise ValueError("target ordered H3/fade boundary contract changed")
        if case["kind"] == "fade":
            actor = bytes.fromhex(expected["owner"])
            if expected["calls"] or actor[0x113] != (9 if want == RETURN else 0):
                raise ValueError("target fade prefix/helper contract changed")
            if want == RETURN and (
                    expected["stack_delta"] != 4
                    or struct.unpack_from("<i",actor,0x330)[0] != 2):
                raise ValueError("target fade retirement/RET0 contract changed")
        if want == 0x64CCB0 and (
                expected["calls"] != ["0x406540","0x68a1a0","0x406360",
                                      "0x68a1a0","0x4063d0","0x68a1a0"]
                or expected["arguments"][0] != case["action"]
                or expected["arguments"][-1] != 4):
            raise ValueError("native angle/lookup/spawn call contract changed")
        results.append(dict(case=case,boundary=expected["boundary"],
                            expected_payload=expected.get("payload"),
                            actual_payload=actual.get("payload"),
                            differences=[key for key in sorted(expected.keys()|actual.keys())
                                         if expected.get(key) != actual.get(key)]))
    return dict(diagnostic_only=True,target_sha256=identity,
                candidate_sha256=hashlib.sha256(candidate).hexdigest(),
                count=len(results),mismatch_count=sum(bool(r["differences"]) for r in results),
                results=results,scope=__doc__)


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
