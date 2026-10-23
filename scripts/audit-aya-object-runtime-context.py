#!/usr/bin/env python3
"""Read Aya's RTTI/base offsets and compare isolated owner-context COFF payloads."""

import argparse
import csv
import hashlib
import importlib.util
import json
from pathlib import Path
import struct
import sys
import tomllib

import capstone
from capstone import x86_const as x

import linked_pe as lp
from workflow_manifest import load_manifest

ROOT = Path(__file__).resolve().parents[1]


def observations(c):
    def words(address, n):
        return struct.unpack("<" + "I" * n, c.target_bytes(address, 4 * n))

    def name(address):
        return c.target_bytes(address + 8, 192).split(b"\0", 1)[0].decode("ascii")

    vtable = 0x6C624C
    locator = words(vtable - 4, 1)[0]
    signature, offset, cd_offset, type_descriptor, hierarchy = words(locator, 5)
    assert (signature, offset, cd_offset) == (0, 0, 0) and name(
        type_descriptor
    ) == ".?AVAyaObject@@"
    hsig, attrs, count, base_array = words(hierarchy, 4)
    assert hsig == 0 and attrs == 1 and count == 8
    expected = (
        (".?AVAyaObject@@", 7, 0),
        (".?AV?$CharacterObjectEx@VAya@@VAyaObject@@@@", 6, 0),
        (".?AVCharacterObject@@", 5, 0),
        (".?AVCObjectBase@@", 0, 0x330),
        (".?AVAttackObject@@", 3, 0),
        (".?AVAnimationObject@@", 2, 0),
        (".?AVAnimationObjectBase@@", 0, 4),
        (".?AVEnvironment@@", 0, 0x130),
    )
    bases = []
    for descriptor, witness in zip(words(base_array, count), expected):
        td, contained = words(descriptor, 2)
        pmd = struct.unpack("<iii", c.target_bytes(descriptor + 8, 12))
        battrs = words(descriptor + 20, 1)[0]
        assert (name(td), contained, pmd[0]) == witness and pmd[1:] == (-1, 0)
        bases.append(
            dict(
                descriptor=hex(descriptor),
                type_descriptor=hex(td),
                type_name=name(td),
                contained=contained,
                pmd=pmd,
                attributes=hex(battrs),
                core24_sha256=hashlib.sha256(
                    c.target_bytes(descriptor, 24)
                ).hexdigest(),
            )
        )
    with (ROOT / "config/functions.csv").open() as f:
        ledger = {int(r["address"], 0): r for r in csv.DictReader(f)}
    slots = []
    for i, address in enumerate(words(vtable, 17)):
        row = ledger.get(address, {})
        slots.append(
            dict(
                offset=hex(4 * i),
                address=hex(address),
                ledger_name=row.get("proposed_name") or row.get("current_name"),
                ledger_status=row.get("status"),
            )
        )
    assert slots[10]["address"] == "0x61a290" and slots[15]["address"] == "0x61f0b0"
    cs = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    cs.detail = True
    pool_address, pool_size = 0x617DF0, 519
    rows = list(cs.disasm(c.target_bytes(pool_address, pool_size), pool_address))
    assert sum(r.size for r in rows) == pool_size
    pushes = [
        r
        for r in rows
        if r.mnemonic == "push"
        and r.operands[0].type == x.X86_OP_IMM
        and r.operands[0].imm == 0x388
    ]
    stores = [
        r
        for r in rows
        if r.mnemonic == "mov"
        and r.operands[0].type == x.X86_OP_MEM
        and r.operands[1].type == x.X86_OP_IMM
        and r.operands[1].imm == vtable
    ]
    assert len(pushes) == 1 and len(stores) == 2
    return dict(
        primary_vtable=hex(vtable),
        locator=hex(locator),
        type_descriptor=hex(type_descriptor),
        hierarchy=hex(hierarchy),
        hierarchy_attributes=hex(attrs),
        base_array=hex(base_array),
        bases=bases,
        slots=slots,
        pool_size_witness=dict(
            address=hex(pool_address),
            bytes=pool_size,
            sha256=hashlib.sha256(c.target_bytes(pool_address, pool_size)).hexdigest(),
            size_argument=0x388,
            size_push=hex(pushes[0].address),
            vtable_stores=[hex(r.address) for r in stores],
        ),
        scope="raw20-byte locator,16-byte hierarchy and24-byte base-descriptor cores plus names, configured17-slot surface and pool instructions; no complete RTTI-record boundaries, member types, lifecycle or exact-root claim",
    )


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--object",
        type=Path,
        action="append",
        help="Optional nonvirtual-Q symbol control; repeatable",
    )
    parser.add_argument(
        "--virtual-object",
        type=Path,
        action="append",
        help="Optional virtual-U symbol control; repeatable",
    )
    parser.add_argument(
        "--output", type=Path, default=ROOT / "build/aya-object-runtime-context.json"
    )
    args = parser.parse_args()
    c = lp.comparator()
    target_sha = c.verify_target()
    target = observations(c)
    spec = importlib.util.spec_from_file_location(
        "aya_owner_context_coff", ROOT / "scripts/compare-giant-action-switches.py"
    )
    mapper = importlib.util.module_from_spec(spec)
    sys.modules[spec.name] = mapper
    spec.loader.exec_module(mapper)
    unit = load_manifest()["units"]["gpt-web-aya-object-vslot28-full-root"]
    f = unit["functions"][0]
    root = mapper.load_target_mapper().select_root(
        tomllib.loads((ROOT / "config/giant-action-switches.toml").read_text()),
        "aya-object-vslot28",
    )
    symbol = f["symbol_base"]
    nonvirtual = symbol.replace("@@UAEXXZ", "@@QAEXXZ")
    virtual = symbol.replace("@@QAEXXZ", "@@UAEXXZ")
    assert virtual != nonvirtual
    inputs = (
        [(ROOT / unit["object"], symbol)]
        + [(p, nonvirtual) for p in args.object or []]
        + [(p, virtual) for p in args.virtual_object or []]
    )
    payloads = []
    selected = None
    for obj, sym in inputs:
        co = mapper.CoffObject(obj, symbol_base=sym)
        meta = mapper.build_candidate_map(co, root)["metadata_start"]
        code = c.coff_symbol_bytes(
            obj,
            sym,
            0x61A290,
            len(co.text),
            {a: int(b, 0) for a, b in (s.split("=", 1) for s in f["rel32_targets"])},
            c.known_data_targets(),
            dict(s.split("=", 1) for s in f.get("dir32_targets", [])),
        )
        if selected is None:
            selected = code
        payloads.append(
            dict(
                path=str(obj),
                symbol=sym,
                object_sha256=lp.sha(obj),
                full_size=len(code),
                metadata_start=meta,
                canonical_sha256=hashlib.sha256(code).hexdigest(),
                identical_to_selected_payload=code == selected,
            )
        )
    report = dict(
        evidence="target_abi_observations_and_compiler_controls_not_exact_acceptance",
        target_sha256=target_sha,
        target=target,
        objects=payloads,
        scope="source hierarchy/virtual-member controls compare complete canonical root payload only; equality to selected nonexact code does not qualify nominal C++ identity, constructors, original TU or target matching",
    )
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps(report, indent=2))


if __name__ == "__main__":
    main()
