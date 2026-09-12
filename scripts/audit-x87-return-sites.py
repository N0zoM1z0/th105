#!/usr/bin/env python3
"""Capture bounded return-consumer windows at current IDA direct-call sites.

This is an instruction census, not source-type inference or a CFG/dataflow
proof. It never changes IDA, source contracts, or reconstruction ledgers.
"""
from __future__ import annotations

import argparse
import asyncio
from collections import Counter
import importlib.util
import json
from pathlib import Path
import struct
import sys

from capstone import Cs, CS_ARCH_X86, CS_MODE_32, CS_GRP_CALL, CS_GRP_JUMP, CS_GRP_RET
from ida_mcp_client import call_json, open_session, require_target

ROOT = Path(__file__).resolve().parents[1]


def load_typed():
    spec = importlib.util.spec_from_file_location("th105_x87_typed", ROOT / "scripts" / "typed-re.py")
    if spec is None or spec.loader is None:
        raise RuntimeError("cannot load target verification helpers")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def direct_call_target(code: bytes, site: int) -> int:
    if len(code) != 5 or code[0] != 0xE8:
        raise ValueError(f"IDA caller {site:#x} is not a five-byte direct CALL")
    return (site + 5 + struct.unpack_from("<i", code, 1)[0]) & 0xFFFFFFFF


def consumer_window(code: bytes, address: int) -> dict:
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    decoder.detail = True
    instructions = []
    first_x87 = None
    stop = "byte_limit"
    for insn in decoder.disasm(code, address):
        instructions.append({"address": f"0x{insn.address:08X}", "bytes": insn.bytes.hex(),
                             "instruction": f"{insn.mnemonic} {insn.op_str}".rstrip()})
        if first_x87 is None and insn.mnemonic.startswith("f"):
            first_x87 = insn.mnemonic
        if insn.group(CS_GRP_CALL) or insn.group(CS_GRP_JUMP) or insn.group(CS_GRP_RET):
            stop = "control_transfer"
            break
        if len(instructions) == 20:
            stop = "instruction_limit"
            break
    return {"first_x87": first_x87, "stop": stop, "instructions": instructions}


async def collect(callee: int) -> dict:
    typed = load_typed()
    data, manifest = typed.verify_local_target()
    async with open_session() as (session, _):
        metadata = await require_target(session)
        callers = await call_json(session, "get_callers", {"function_address": f"0x{callee:08X}"})
    if not isinstance(callers, list):
        raise ValueError("IDA caller result is not a list")
    seen = set()
    rows = []
    for caller in callers:
        site = int(caller["address"], 0)
        if site in seen:
            raise ValueError(f"duplicate IDA call site {site:#x}")
        seen.add(site)
        raw = typed.target_bytes(data, site, 5)
        if direct_call_target(raw, site) != callee:
            raise ValueError(f"IDA call site {site:#x} does not target {callee:#x}")
        rows.append({"site": f"0x{site:08X}", "ida_owner_name": caller.get("name"),
                     **consumer_window(typed.target_bytes(data, site + 5, 96), site + 5)})
    return {"schema": "th105-x87-return-sites-v1", "target_sha256": manifest["target"]["sha256"],
            "ida_target_sha256": metadata["sha256"], "callee": f"0x{callee:08X}",
            "site_count": len(rows), "first_x87_counts": dict(Counter(row["first_x87"] or "none" for row in rows)),
            "sites": rows,
            "limitation": "IDA direct-call inventory only; bounded linear windows stop at control transfers. "
                          "No exhaustive indirect-call coverage, returned-value dataflow, or unique source return type is claimed."}


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("callee", type=lambda value: int(value, 0))
    args = parser.parse_args()
    if not 0x00401000 <= args.callee < 0x006BF33A:
        parser.error("callee must lie in the pinned target .text range")
    try:
        report = asyncio.run(collect(args.callee))
    except (OSError, RuntimeError, ValueError, TypeError, KeyError, struct.error) as exc:
        print(f"return-site audit failed: {exc}", file=sys.stderr)
        return 1
    print(json.dumps(report, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
