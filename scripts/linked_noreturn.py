"""Target-pinned VC8 vector range-error exits; no auxiliary exact credit."""
from __future__ import annotations

import hashlib
import re
import struct

import capstone

HELPER = 0x40C350
HELPER_SIZE = 123
HELPER_SHA = "a02adc82307ea7507f3024cd6bb4d30229469d2464a73be1c15b8955745445e2"
THROW = 0x68A153
THROW_SIZE = 74
THROW_SHA = "005fb09ff53b504488b42efb5f28b6994f9a0a91a051345c53a22008afeafba6"
RECORD = 0x6CD268
RECORD_SHA = "47319cfc7d36ae39541424fbeb90ab2cff937bd3bd6e1576c7351210075e0420"
MESSAGE = b"invalid vector<T> subscript\0"
KIND = "vc8-vector-out-of-range"
BYTE_KIND = "vc8-byte-vector-out-of-range"
BYTE_SYMBOL = "?_Xran@?$vector@EV?$allocator@E@std@@@std@@KAXXZ"
BYTE_HELPER = 0x40A8A0
BYTE_HELPER_SIZE = 117
BYTE_HELPER_SHA = "0c8d4d002e27c42d0d079456e7e5dd8e2f42e1122df4581fa5609b9cd257adf7"


def helper_anchor(contract):
    if contract["kind"] == BYTE_KIND:
        if contract["symbol"] != BYTE_SYMBOL:
            raise ValueError("byte-vector error requires its exact VC8 specialization")
        return BYTE_HELPER, BYTE_HELPER_SIZE, BYTE_HELPER_SHA
    return HELPER, HELPER_SIZE, HELPER_SHA


def validate_contract(function):
    contracts = function.get("error_tails", [])
    if not isinstance(contracts, list) or len(contracts) > 1:
        raise ValueError("linked error tails require one bounded vector error contract")
    for contract in contracts:
        symbol = contract.get("symbol", "") if isinstance(contract, dict) else ""
        if (not isinstance(contract, dict) or set(contract) != {"kind", "symbol", "site"}
                or contract["kind"] not in {KIND, BYTE_KIND} or not isinstance(symbol, str)
                or not symbol.startswith("?_Xran@?$vector@") or not symbol.endswith("@@KAXXZ")
                or not re.fullmatch(r"0x[0-9A-Fa-f]{8}", str(contract["site"]))
                or any(key in function for key in ("private_from", "private_global", "vtable_entry", "eh_cleanup"))):
            raise ValueError("unsupported linked vector error-tail contract")
        mappings = [value for value in function.get("rel32_targets", [])
                    if value.partition("=")[0] == symbol]
        if len(mappings) != 1 or int(mappings[0].partition("=")[2], 0) != helper_anchor(contract)[0]:
            raise ValueError("vector error tail must map its exact static helper")


def instructions(code, start):
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    decoder.detail = True
    rows = list(decoder.disasm(code, start))
    if not rows or sum(row.size for row in rows) != len(code):
        raise ValueError("incomplete vector error-helper decode")
    return rows


def straight_throw(code, start, destination):
    rows = instructions(code, start)
    last = rows[-1]
    if (last.size != 5 or last.bytes[0] != 0xE8
            or last.operands[0].type != capstone.x86.X86_OP_IMM
            or last.operands[0].imm != destination):
        raise ValueError("vector error helper must end at the attested C++ throw call")
    for row in rows:
        if (row.group(capstone.CS_GRP_RET) or row.group(capstone.CS_GRP_JUMP)
                or row.mnemonic.startswith("loop") or row.mnemonic in {"jcxz", "jecxz", "int3", "int", "hlt", "ud2"}
                or (row.group(capstone.CS_GRP_CALL) and (row.size != 5 or row.bytes[0] != 0xE8))):
            raise ValueError("vector error helper has an unsupported return/control-flow path")
    return rows


def throw_types(read, address):
    def words(at, count):
        data = read(at, count * 4)
        if len(data) != count * 4:
            raise ValueError("truncated throw metadata")
        return struct.unpack("<" + "I" * count, data)
    array = words(address, 4)[3]
    count = words(array, 1)[0]
    if count != 3:
        raise ValueError("vector exception needs its three catchable base types")
    result = []
    for entry in words(array + 4, count):
        flags, descriptor, mdisp, pdisp, vdisp, size, copy = words(entry, 7)
        name = read(descriptor + 8, 128).split(b"\0", 1)[0]
        if not name or len(name) >= 128 or not copy:
            raise ValueError("invalid vector exception type descriptor")
        result.append((name.decode("ascii"), flags, mdisp, pdisp, vdisp, size))
    expected = [(".?AVout_of_range@std@@", 0, 0, 0xFFFFFFFF, 0, 40),
                (".?AVlogic_error@std@@", 0, 0, 0xFFFFFFFF, 0, 40),
                (".?AVexception@std@@", 0, 0, 0xFFFFFFFF, 0, 12)]
    if result != expected:
        raise ValueError("vector error has different exception types/layouts")
    return result


def witness(core, function, pe, game, functions, exports, cil_owner, start, raw, target, read_target):
    validate_contract(function)
    contracts = function.get("error_tails", [])
    if not contracts:
        return {}, {}, []
    helper_target, helper_size, helper_sha = helper_anchor(contracts[0])
    target_helper = read_target(helper_target, helper_size)
    if (hashlib.sha256(target_helper).hexdigest() != helper_sha
            or hashlib.sha256(read_target(THROW, THROW_SIZE)).hexdigest() != THROW_SHA
            or hashlib.sha256(read_target(RECORD, 32)).hexdigest() != RECORD_SHA
            or struct.unpack("<I", read_target(RECORD + 4, 4))[0] != 1):
        raise ValueError("target vector error/throw/noncontinuable-record anchor changed")
    if not hasattr(game, "DIRECTORY_ENTRY_IMPORT"):
        game.parse_data_directories(directories=[core.pefile.DIRECTORY_ENTRY["IMAGE_DIRECTORY_ENTRY_IMPORT"]])
    raise_imports = [(dll.dll.decode().lower(), entry.name)
                     for dll in game.DIRECTORY_ENTRY_IMPORT for entry in dll.imports
                     if entry.address == 0x6C015C]
    if raise_imports != [("kernel32.dll", b"RaiseException")]:
        raise ValueError("target C++ throw RaiseException identity changed")
    straight_throw(target_helper, helper_target, THROW)
    types = throw_types(read_target, 0x6E3BA4)
    if read_target(0x6D694C, len(MESSAGE)) != MESSAGE:
        raise ValueError("target vector range-error message changed")
    source_rows = instructions(raw, start)
    source_exits, target_exits, reports = {}, {}, []
    for contract in contracts:
        symbol = contract["symbol"]
        found = [(address, owner) for address, aliases in functions.items()
                 for name, owner in aliases if name == symbol]
        if (len(found) != 1 or found[0][1].split()[-1:] != [cil_owner]
                or functions[found[0][0]] != [(symbol, found[0][1])]
                or found[0][0] in exports.values()):
            raise ValueError("vector error helper needs a unique unexported source CIL owner")
        helper = found[0][0]
        body = core.linked_body(pe, functions, helper)
        if not 5 <= len(body) <= 512:
            raise ValueError("vector error helper exceeds its bounded source extent")
        decoded = instructions(body, helper)
        last = decoded[-1]
        destination = last.operands[0].imm if last.operands and last.operands[0].type == capstone.x86.X86_OP_IMM else 0
        thunk = pe.get_data(destination - core.IMAGE_BASE, 6) if destination >= core.IMAGE_BASE else b""
        if len(thunk) != 6 or thunk[:2] != b"\xff\x25" or functions.get(destination) != [("__CxxThrowException@8", "msvcrt:MSVCR80.dll")]:
            raise ValueError("vector error must call the genuine pinned CRT throw import")
        cell = struct.unpack_from("<I", thunk, 2)[0]
        imports = [(dll.dll.decode().lower(), entry.name) for dll in pe.DIRECTORY_ENTRY_IMPORT
                   for entry in dll.imports if entry.address == cell]
        if imports != [("msvcr80.dll", b"_CxxThrowException")]:
            raise ValueError("vector error CRT throw IAT identity disagrees")
        straight_throw(body, helper, destination)
        def read(address, count):
            if not core.IMAGE_BASE <= address <= address + count <= core.IMAGE_BASE + pe.OPTIONAL_HEADER.SizeOfImage:
                raise ValueError("vector exception metadata leaves its source image")
            data = pe.get_data(address - core.IMAGE_BASE, count)
            if len(data) != count:
                raise ValueError("truncated native vector exception metadata")
            return data
        messages, infos = [], []
        for row in decoded:
            if row.mnemonic != "push" or row.operands[0].type != capstone.x86.X86_OP_IMM:
                continue
            address = row.operands[0].imm
            section = pe.get_section_by_rva(address - core.IMAGE_BASE)
            if section is None or section.Characteristics & 0xA0000000:
                continue
            if read(address, len(MESSAGE)) == MESSAGE:
                messages.append(address)
            try:
                if throw_types(read, address) == types:
                    infos.append(address)
            except (ValueError, struct.error, UnicodeError):
                pass
        if len(messages) != 1 or len(infos) != 1:
            raise ValueError("vector error needs its unique native message and exception metadata")
        info_index = next(index for index, row in enumerate(decoded)
                          if row.mnemonic == "push" and row.operands[0].type == capstone.x86.X86_OP_IMM
                          and row.operands[0].imm == infos[0])
        arguments = decoded[info_index + 1:-1]
        pushes = [row for row in arguments if row.mnemonic == "push"]
        if (len(pushes) != 1 or pushes[0].operands[0].type != capstone.x86.X86_OP_REG
                or any(row.group(capstone.CS_GRP_CALL)
                       or (capstone.x86.X86_REG_ESP in row.regs_access()[1] and row is not pushes[0])
                       for row in arguments)):
            raise ValueError("vector exception metadata is not the actual second throw argument")
        jumps = [row for row in source_rows if row.size == 5 and row.bytes[0] == 0xE9
                 and row.operands[0].imm == helper]
        site = int(contract["site"], 0)
        address = int(function["address"], 0)
        offset = site - address
        expected = b"\xe9" + struct.pack("<i", helper_target - site - 5)
        if len(jumps) != 1 or not 0 <= offset <= len(target) - 5 or target[offset:offset + 5] != expected:
            raise ValueError("vector error needs its sole source jump and exact target E9 site")
        source_exits[jumps[0].address] = helper
        target_exits[site] = helper_target
        reports.append(dict(kind=contract["kind"], source_site=hex(jumps[0].address), target_site=contract["site"],
            symbol=symbol, source_helper=hex(helper), target_helper=hex(helper_target),
            source_helper_sha256=hashlib.sha256(body).hexdigest(), target_helper_sha256=helper_sha,
            source_throw_import=hex(destination), target_throw=hex(THROW),
            target_throw_sha256=THROW_SHA, target_record_sha256=RECORD_SHA,
            catchable_types=types, source_message=hex(messages[0]), source_throw_info=hex(infos[0]),
            scope="noreturn/error-role witness only; no helper/EH exact or origin credit"))
    core.decode_closed_body(target, int(function["address"], 0), external_exits=target_exits,
        alignment_sites={int(site, 0) for site in function.get("alignment_sites", [])})
    core.decode_closed_body(raw, start, external_exits=source_exits,
        alignment_sites={start + int(site, 0) - int(function["address"], 0)
                         for site in function.get("alignment_sites", [])})
    return source_exits, target_exits, reports
