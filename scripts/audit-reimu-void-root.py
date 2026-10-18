#!/usr/bin/env python3
"""Compare the generated void Reimu root, including actual upper defaults."""
from __future__ import annotations

import argparse
from collections import Counter
from functools import lru_cache
import hashlib
import importlib.util
import itertools
import json
from pathlib import Path
import struct
import sys
import tomllib
from types import SimpleNamespace
import pefile
import unicorn

import unicorn

from reimu_740_mode_facts import load, packet

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location('reimu_void_previous', ROOT / 'scripts/audit-reimu-740-mode-shape.py')
previous = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = previous
spec.loader.exec_module(previous)
low = previous.low
SYMBOL = '?run_action_dispatch_root@ReimuActionStatePreludeView@th105@@QAEXXZ'
HELPERS, CALL_TARGETS = previous.HELPERS, previous.CALL_TARGETS
LITERAL_BINDINGS = previous.LITERAL_BINDINGS
SUPPORT_PATHS = (Path(previous.__file__), ROOT / 'scripts/probe-reimu-action-source-shape.py',
                 ROOT / 'scripts/audit-reimu-low-actions.py',
                 ROOT / 'scripts/audit-reimu-late-low-actions.py',
                 ROOT / 'scripts/audit-reimu-mid-shot-actions.py',
                 ROOT / 'scripts/audit-reimu-high-middle-actions.py',
                 ROOT / 'scripts/audit-reimu-movement-attack-actions.py', *previous.SUPPORT_PATHS)
SCHEMA = 'th105-reimu-void-root-native-v1'
SCOPE = ('void noargs thiscall candidate; actual helpers/RET and common-root defaults over the signed action domain; '
         'optional writable surface data, actual query-X and first root Y/height-query ordering observations; '
         '740 stops before indeterminate reads and world calls stop at real entry; no returning-world, '
         'arbitrary-stack, full-relocation or canonical-exact claim')
RANDOM_COHORTS = ('random_lifetimes', 'random124_lifetimes', 'movement_random_lifetimes')
LIFETIME_COHORTS = (*RANDOM_COHORTS, 'flight_effect_lifetimes')
FLIGHT_COHORTS = ('steering', 'flight_exit')
COHORTS = ('integration', 'defaults', 'common_return', 'unresolved740',
           'aim_argument_lifetimes', 'projectile_receivers', 'falling_returns',
           'landing_action_returns', 'surface_inputs', 'shot_boundaries', 'hover_snapshots',
           *LIFETIME_COHORTS, *FLIGHT_COHORTS)
SMOKE_COUNT = 26
ALLOW_SWITCH_METADATA = True
SURFACE_ADDRESS, SURFACE_ELEMENTS = 0x6FA898, 0x500
SURFACE_ACTIONS = (6, 7, 8, 9, 197, 198, 201, 202, 203, 208, 209, 210, 211,
                   212, 220, 221, 222, 224, 225, 226, 306, 307, 308, 309, 404,
                   406, 414, 416, 522, 523, 560, 561, 608, 614, 658, 795, 797, 798)
SURFACE_LANDING_ACTIONS = (6, 7, 8, 9, 208, 209, 210, 211, 212, 220, 221,
                          222, 306, 307, 308, 309, 795, 797, 798)


def surface_terrain():
    return struct.pack('<1280f', *(5.0 + ((index % 17) - 8) * 0.125
                                  for index in range(SURFACE_ELEMENTS)))


def surface_cases():
    templates = itertools.chain(previous.cases(True),
                                (case for case in previous.cases() if case['cohort'] == 'integration'))
    for case in templates:
        if case['action'] in SURFACE_ACTIONS:
            yield {**case, 'cohort': 'surface_inputs', 'terrain_pattern': 'ripple17'}
    base = next(previous.cases(True))
    for action in SURFACE_LANDING_ACTIONS:
        for cw in (0x27F, 0x37F):
            yield {**base, 'cohort': 'surface_inputs', 'terrain_pattern': 'ripple17',
                   'height_boost': True, 'action': action, 'sequence': 0 if action >= 795 else 1,
                   'y': 0.0, 'vy': 0xBF800000, 'ay': 0, 'control_word': cw}
    for action in sorted(set(SURFACE_ACTIONS) - set(SURFACE_LANDING_ACTIONS)):
        for cw in (0x27F, 0x37F):
            yield {**base, 'cohort': 'surface_inputs', 'terrain_pattern': 'ripple17',
                   'height_boost': True, 'action': action,
                   'sequence': 0 if action in (414, 416) else 1,
                   'frame': 8 if action == 414 else 4 if action == 416 else 1,
                   'timer': 1, 'counter': 1, 'y': 0.0, 'vy': 0xBF800000, 'ay': 0,
                   'control_word': cw}


@lru_cache(maxsize=1)
def late_low_family():
    return load('reimu_void_random_effect_family', 'audit-reimu-late-low-actions.py')


def lifetime_families():
    family = late_low_family()
    return family, family.movement


@lru_cache(maxsize=1)
def shot_family():
    return load('reimu_void_shot_family', 'audit-reimu-mid-shot-actions.py')


def shot_boundary_cases(base):
    family = shot_family()
    for case in family.cases():
        if case['action'] in (410, 414, 416) and case['cohort'] != 'integration':
            yield {**base, **case, 'cohort': 'shot_boundaries',
                   'shot_family_cohort': case['cohort']}
    template = {**base, **next(family.cases(True))}
    # On the flat surface the landing helper preserves sequence3; an airborne
    # input selects action9 before reaching the frame-start guard under test.
    for (action, site), cw in itertools.product(((414, 0x47EDB4), (416, 0x487495)),
                                               (0x27F, 0x37F)):
        yield {**template, 'cohort': 'shot_boundaries', 'shot_family_cohort': 'branches',
               'action': action, 'sequence': 3, 'frame': 0, 'counter': -1, 'timer': -1,
               'y': 0.0, 'control_word': cw, 'required_site': site,
               'require_sequence3_return': True}


@lru_cache(maxsize=1)
def hover_family():
    return load('reimu_void_hover_family', 'audit-reimu-high-middle-actions.py')


def hover_snapshot_cases(base):
    family = hover_family()
    for case in family.cases():
        if (case['action'] == 616 and case['sequence'] in (4, 5)
                and case['cohort'] in ('hover', 'branches')):
            yield {**base, **case, 'cohort': 'hover_snapshots',
                   'hover_family_cohort': case['cohort']}
    template = {**base, **next(family.cases(True))}
    for sequence, y, cw in itertools.product((4, 5), (float('nan'), float('inf'), -float('inf')),
                                            (0x27F, 0x37F)):
        yield {**template, 'action': 616, 'sequence': sequence, 'y': y, 'counter': 0,
               'control_word': cw, 'cohort': 'hover_snapshots', 'hover_family_cohort': 'hover'}


@lru_cache(maxsize=1)
def default_actions():
    mapper = load('reimu_void_target_map', 'map-giant-action-switches.py')
    manifest = tomllib.loads((ROOT / 'config/giant-action-switches.toml').read_text())
    root = mapper.select_root(manifest, 'reimu-vslot28')
    target = mapper.map_root(mapper.PeImage(ROOT / 'resources/th105.exe'),
                             mapper.load_function_rows(ROOT / 'config/functions.csv'), root)
    known = {key for region in target['regions'] for group in region['groups']
             if group['destination'] != 0x48CE1F for key in group['cases']} | {300, 560}
    if len(known) != 128:
        raise ValueError('canonical nondefault action domain changed')
    choices = {-32768, -1, 799, 800, 1000, 32766, 32767}
    choices.update(value for key in known for value in (key-1, key+1)
                   if -32768 <= value <= 32767 and value not in known)
    return tuple(sorted(choices-known))


def cases(smoke=False):
    base = {**next(previous.cases(True)), 'effect': 1}
    for case in previous.cases(True):
        yield {**case, 'cohort': 'integration'}
    if not smoke:
        yield from surface_cases()
        air = load('reimu_void_air_inputs', 'audit-reimu-low-actions.py')
        for case in air.cases():
            if (case['cohort'] == 'air' and case['action'] == 9
                    and case['sequence'] == 0 and case['flag'] == 1):
                yield {**base, **case, 'cohort': 'falling_returns'}
            elif case['cohort'] == 'animation' and case['action'] == 10:
                yield {**base, **case, 'cohort': 'landing_action_returns',
                       'single_sequence': case['transition'] == 'terminal'}
        for case in previous.cases():
            if case['cohort'] == 'integration':
                yield case
        for family in lifetime_families():
            for case in family.cases():
                if case['cohort'] in (*LIFETIME_COHORTS, *FLIGHT_COHORTS):
                    yield {**base, **case}
        yield from shot_boundary_cases(base)
        yield from hover_snapshot_cases(base)
        for action, facing, cw, seed, shot, latch in itertools.product(
                (400, 401, 404, 406), (-128, -1, 0, 1, 127), (0x27F, 0x37F),
                (0, 5489, 0xFFFFFFFF), (0, 4), (0, 1)):
            yield {**base, 'cohort': 'projectile_receivers', 'action': action,
                   'sequence': 0, 'counter': 0, 'timer': 0,
                   'y': 0.0 if action in (400, 401) else 100.0, 'vy': 0, 'ay': 0,
                   'counter730': 3, 'counter732': shot, 'counter734': 10,
                   'latch750': latch, 'held6c0': 1, 'facing': facing,
                   'control_word': cw, 'seed': seed}
        aim_profiles = ((400, 2, 0, 0x47DF03), (400, 6, 0, 0x47E039),
                        (401, 2, 0, 0x47E44A), (401, 6, 0, 0x47E577),
                        (404, 2, 0, 0x47EBCC), (404, 6, 0, 0x47ED11),
                        (406, 2, 0, 0x47F1CE), (406, 6, 0, 0x47F307),
                        (410, 0, 8, 0x47F60B), (410, 2, 2, 0x47F788),
                        (414, 0, 5, 0x47FBA3), (414, 2, 1, 0x47FD29))
        geometry = ((640.0, 0x44480000, 150.0), (640.0, 0x44200000, -100.0),
                    (33554432.0, 0x4C000001, 250.0), (640.0, 0x43A00000, 1.0),
                    (0.0, 0x3F000001, 251.0))
        for profile, facing, cw, (position, peer, peer_y) in itertools.product(
                aim_profiles, (-128, -1, 0, 1, 127), (0x27F, 0x37F), geometry):
            action, sequence, frame, site = profile
            yield {**base, 'cohort': 'aim_argument_lifetimes', 'action': action,
                   'sequence': sequence, 'frame': frame, 'aim_site': site,
                   'counter': -1, 'timer': -1, 'counter730': 0,
                   'x': position, 'y': 0.0 if action in (400, 401, 410) else 100.0,
                   'peer': peer, 'peer_y': peer_y, 'facing': facing, 'control_word': cw}
    choices = (-32768, 799, 32767) if smoke else default_actions()
    gates = ((0, 0),) if smoke else ((0, 0), (1, 0), (0, 1))
    for action, (entry, peer), cw in itertools.product(choices, gates, (0x27F, 0x37F)):
        yield {**base, 'cohort': 'defaults', 'action': action, 'entry_gate': entry,
               'peer_gate': peer, 'control_word': cw}
    for action, count, cw in itertools.product((799, 32767) if smoke else (799, 800, 1000, 32767),
                                                (0,) if smoke else (-1, 0), (0x27F, 0x37F)):
        yield {**base, 'cohort': 'common_return', 'action': action,
               'counter': count, 'execute_common': True, 'control_word': cw}
    for sequence, mode, cw in itertools.product((1, 6), (4,) if smoke else (4, 0xFFFFFFFF), (0x27F, 0x37F)):
        yield {**base, 'cohort': 'unresolved740', 'action': 740, 'sequence': sequence,
               'match_selector': mode, 'control_word': cw}


def check_target_case(case, result, sites):
    if case['cohort'] == 'hover_snapshots':
        hover_family().check_target_case({**case, 'cohort': case['hover_family_cohort']}, result, sites)
        if 0x489E06 not in sites or result['endpoint'] != 'ret':
            raise ValueError('hover snapshot input bypassed the real height comparison/return')
        observations = [call[0] for call in result['calls']
                        if call[0] in ('hover_y_read', 'hover_height_query')]
        if observations != ['hover_y_read', 'hover_height_query']:
            raise ValueError('target hover did not read its Y snapshot before querying height')
    elif case['cohort'] == 'shot_boundaries':
        shot_family().check_target_case({**case, 'cohort': case['shot_family_cohort']}, result, sites)
        if case.get('require_sequence3_return') and (
                result['endpoint'] != 'ret' or result['actor'][0x13C:0x13E] != struct.pack('<h', 9)):
            raise ValueError('sequence3 shot input bypassed its real action9 return')
    elif case['cohort'] == 'surface_inputs':
        roots = [call for call in result['calls'] if call[:2] == ('height_input_x', True)]
        if case.get('height_boost') and (not roots or result['endpoint'] != 'ret'):
            raise ValueError('target surface input bypassed its real root height query/return')
        if case.get('height_boost') and case['action'] in (795, 797, 798):
            expected = {795: 5.375, 797: 4.5, 798: 4.125}[case['action']]
            if case['x'] != 640.0 or result['actor'][0xF0:0xF4] != struct.pack('<f', expected):
                raise ValueError('target high landing did not consume its nonflat surface value')
    elif case['cohort'] == 'falling_returns':
        if (result['endpoint'] != 'ret' or 0x47970A not in sites
                or ((0x479713 in sites) == (0x47973C in sites))):
            raise ValueError('target falling input bypassed its real landing/advance return')
        if 0x479713 in sites and result['actor'][0xF0:0xF4] != bytes(4):
            raise ValueError('target falling input did not restore the flat terrain fixture')
    elif case['cohort'] == 'landing_action_returns':
        if (result['endpoint'] != 'ret' or 0x47975B not in sites
                or (0x47977A in sites and case['field'] != 0)
                or (0x479786 in sites and case['field'] == 0)):
            raise ValueError('target landing input bypassed its full-width action-selection return')
    elif case['cohort'] == 'projectile_receivers':
        ranges = [call for call in result['calls'] if call[0] == 0x4351A0]
        arguments = [call[2] for call in result['calls']
                     if call[:2] == ('native_args', 0x4351A0)]
        expected = 2 if case['latch750'] else 0
        if ((result['spawn_request'] or ())[:2] != (0x465190, 800)
                or len(ranges) != expected
                or any(call[1:] != (low.OWNER+4, 0) for call in ranges)
                or arguments != ([struct.pack('<II', 0, 30).hex(),
                                  struct.pack('<II', 0, 5).hex()] if expected else [])):
            raise ValueError('target projectile bypassed its actual range receiver/argument path')
    elif case['cohort'] == 'defaults':
        if case['entry_gate'] or case['peer_gate']:
            if result['endpoint'] != 'ret' or any(call[0] == 0x4740C0 for call in result['calls']):
                raise ValueError('default entry gate did not return before dispatch')
        elif result['spawn_request'] != (0x4740C0,) or 0x48CE1F not in sites:
            raise ValueError('default action did not reach the original common call')
    elif case['cohort'] in RANDOM_COHORTS:
        family = late_low_family().movement if case['cohort'] == 'movement_random_lifetimes' else late_low_family()
        family.check_target_case(case, result, sites)
        observations = [call for call in result['calls'] if call[0] == 'pending_effect_arguments']
        direction = -case['facing'] if case['action'] in (201, 203, 224, 225) else case['facing']
        tail = struct.pack('<II', direction & 0xFF, 1).hex()
        if (len(observations) != 2 or observations[0][1:] != (1, tail)
                or observations[1][1] != 2 or len(observations[1][2]) != 24
                or observations[1][2][-16:] != tail):
            raise ValueError('target random effect lacks its pending direction/trailing arguments')
    elif case['cohort'] in FLIGHT_COHORTS:
        late_low_family().check_target_case(case, result, sites)
        if case['cohort'] == 'flight_exit' and (
                0x47BBDB not in sites or result['endpoint'] != 'ret'):
            raise ValueError('target flight exit bypassed its real resource cost/return')
    elif case['cohort'] == 'flight_effect_lifetimes':
        late_low_family().check_target_case(case, result, sites)
        observations = [call for call in result['calls'] if call[0] == 'pending_flight_effect_arguments']
        tail = struct.pack('<II', case['facing'] & 0xFF, 1).hex()
        if (len(observations) != 2 or observations[0][1:] != ('sine', tail)
                or observations[1][1] != 'cosine' or len(observations[1][2]) != 24
                or observations[1][2][-16:] != tail):
            raise ValueError('target flight effect lacks its pending direction/trailing arguments')
    elif case['cohort'] == 'aim_argument_lifetimes':
        pending = [call[1] for call in result['calls'] if call[0] == 'pending_aim_x']
        arguments = [call[1] for call in result['calls'] if call[0] == 'aim_arguments']
        if (case['aim_site'] not in sites or len(pending) != 1 or len(arguments) != 1
                or len(arguments[0]) != 16 or pending[0] != arguments[0][8:]):
            raise ValueError('target aim lacks its actual X argument before the peer Y read')
        if case['action'] in (410, 414):
            if result['spawn_request'][:2] != (0x465190, 801):
                raise ValueError('shot aim fixture bypassed its actual object801 request')
        elif result['endpoint'] != 'ret':
            raise ValueError('projectile aim fixture bypassed its real return')
    else:
        previous.check_target_case(case, result, sites)
    if case['cohort'] == 'common_return' and 0x48CE1F not in sites:
        raise ValueError('upper default common-return case bypassed the actual root default')


def audit(path, smoke=False, cohorts=None):
    facts = packet(path, symbol=SYMBOL)
    canonical = low.linked_pe.comparator()
    if canonical.known_data_targets()['?g_stage_surface_heights@th105@@3PAMA'][0] != SURFACE_ADDRESS:
        raise ValueError('attested surface global binding changed')
    pe = pefile.PE(str(ROOT / 'resources/th105.exe'))
    rva = SURFACE_ADDRESS - pe.OPTIONAL_HEADER.ImageBase
    section = pe.get_section_by_rva(rva)
    if (section is None or not section.Characteristics & 0x80000000
            or rva + 4 * SURFACE_ELEMENTS > section.VirtualAddress + section.Misc_VirtualSize):
        raise ValueError('surface fixture is not inside the attested writable data section')
    instances = []

    class VoidProbe(previous.Probe):
        candidate_return_kind = 'void'
        handled_action_max = 32767

        def __init__(self, *args, **kwargs):
            super().__init__(*args, **kwargs)
            self.return_bytes = Counter()
            self.original_surface = bytes(self.engine.mem_read(SURFACE_ADDRESS, 4 * SURFACE_ELEMENTS))
            if self.original_surface != bytes(4 * SURFACE_ELEMENTS):
                raise ValueError('initial supplied surface data is not the reviewed flat fixture')
            self.surface_root_sites = Counter()
            self.surface_query_words = Counter()
            instances.append(self)

        def evaluate(self, case):
            self.track_surface_inputs = case['cohort'] == 'surface_inputs'
            self.surface_action = case['action']
            self.track_hover_reads = case['cohort'] == 'hover_snapshots'
            self.hover_y_observed = self.hover_height_observed = False
            self.track_random_tails = case['cohort'] in RANDOM_COHORTS
            self.random_draw_count = 0
            self.track_flight_tails = case['cohort'] == 'flight_effect_lifetimes'
            self.flight_lookup_counts = Counter()
            self.track_aim_arguments = case['cohort'] == 'aim_argument_lifetimes'
            observer = (self.engine.hook_add(unicorn.UC_HOOK_MEM_READ, self.observe_aim_read)
                        if self.track_aim_arguments else None)
            hover_observer = (self.engine.hook_add(unicorn.UC_HOOK_MEM_READ, self.observe_hover_read,
                                                 begin=low.OWNER + 0xF0, end=low.OWNER + 0xF3)
                              if self.track_hover_reads else None)
            try:
                result = super().evaluate(case)
            finally:
                if observer is not None:
                    self.engine.hook_del(observer)
                if hover_observer is not None:
                    self.engine.hook_del(hover_observer)
            if result['endpoint'] == 'ret':
                self.return_bytes[self.engine.reg_read(low.r.UC_X86_REG_EAX) & 0xFF] += 1
            if bytes(self.engine.mem_read(SURFACE_ADDRESS, 4 * SURFACE_ELEMENTS)) != self.expected_surface:
                raise ValueError('surface data changed during the root update')
            return result

        def prepare_extra_case(self, case):
            super().prepare_extra_case(case)
            pattern = case.get('terrain_pattern')
            if ((self.track_surface_inputs and pattern != 'ripple17')
                    or (not self.track_surface_inputs and pattern is not None)):
                raise ValueError('unreviewed surface fixture pattern')
            self.expected_surface = surface_terrain() if self.track_surface_inputs else self.original_surface
            self.engine.mem_write(SURFACE_ADDRESS, self.expected_surface)

        def observe_aim_read(self, uc, access, address, size, value, unused):
            pc = uc.reg_read(low.r.UC_X86_REG_EIP)
            if (address == low.OWNER + 0x20F0 and size == 4
                    and low.ADDRESS <= pc < low.ADDRESS + low.SIZE):
                sp = uc.reg_read(low.r.UC_X86_REG_ESP)
                self.calls.append(('pending_aim_x', bytes(uc.mem_read(sp + 4, 4)).hex()))

        def observe_hover_read(self, uc, access, address, size, value, unused):
            pc = uc.reg_read(low.r.UC_X86_REG_EIP)
            if (not self.hover_y_observed and address == low.OWNER + 0xF0 and size == 4
                    and low.ADDRESS <= pc < low.ADDRESS + low.SIZE):
                # Observe the real first root load; never change actor memory or execution.
                self.calls.append(('hover_y_read', bytes(uc.mem_read(address, size)).hex()))
                self.hover_y_observed = True

        def step(self, uc, address, size):
            super().step(uc, address, size)
            if (address == 0x435D60 and getattr(self, 'track_hover_reads', False)
                    and not self.hover_height_observed):
                caller, = struct.unpack('<I', uc.mem_read(uc.reg_read(low.r.UC_X86_REG_ESP), 4))
                if low.ADDRESS <= caller < low.ADDRESS + low.SIZE:
                    self.calls.append(('hover_height_query',))
                    self.hover_height_observed = True
            if address == 0x435D60 and getattr(self, 'track_surface_inputs', False):
                receiver = uc.reg_read(low.r.UC_X86_REG_ECX)
                if receiver != low.OWNER:
                    raise ValueError('unreviewed actual surface-query receiver')
                caller, = struct.unpack('<I', uc.mem_read(uc.reg_read(low.r.UC_X86_REG_ESP), 4))
                root = low.ADDRESS <= caller < low.ADDRESS + low.SIZE
                bits = bytes(uc.mem_read(receiver + 0xEC, 4)).hex()
                self.calls.append(('height_input_x', root, bits))
                self.surface_query_words[(root, bits)] += 1
                if root:
                    if uc.mem_read(caller - 5, 1) != b'\xe8':
                        raise ValueError('surface query lacks its reviewed direct root call')
                    self.surface_root_sites[(self.surface_action, caller - 5)] += 1
            if address == 0x406540 and getattr(self, 'track_aim_arguments', False):
                sp = uc.reg_read(low.r.UC_X86_REG_ESP)
                caller, = struct.unpack('<I', uc.mem_read(sp, 4))
                if low.ADDRESS <= caller < low.ADDRESS + low.SIZE:
                    self.calls.append(('aim_arguments', bytes(uc.mem_read(sp + 4, 8)).hex()))
            if address == 0x4066B0 and getattr(self, 'track_random_tails', False):
                sp = uc.reg_read(low.r.UC_X86_REG_ESP)
                caller, = struct.unpack('<I', uc.mem_read(sp, 4))
                if low.ADDRESS <= caller < low.ADDRESS + low.SIZE:
                    self.random_draw_count += 1
                    if self.random_draw_count not in (1, 2):
                        raise ValueError('random effect executes more than two root MT calls')
                    # Read only: both original MT calls continue to their RET.
                    count = self.random_draw_count + 1
                    self.calls.append(('pending_effect_arguments', self.random_draw_count,
                                       bytes(uc.mem_read(sp + 4, count * 4)).hex()))
            if address in (0x406360, 0x4063D0) and getattr(self, 'track_flight_tails', False):
                sp = uc.reg_read(low.r.UC_X86_REG_ESP)
                caller, = struct.unpack('<I', uc.mem_read(sp, 4))
                if low.ADDRESS <= caller < low.ADDRESS + low.SIZE:
                    self.flight_lookup_counts[address] += 1
                    if self.flight_lookup_counts[address] > 2:
                        raise ValueError('flight effect executes more than two lookups of one kind')
                    if self.flight_lookup_counts[address] == 2:
                        kind, count = ('sine', 2) if address == 0x406360 else ('cosine', 3)
                        # Read only, above this real cdecl lookup's phase argument.
                        self.calls.append(('pending_flight_effect_arguments', kind,
                                           bytes(uc.mem_read(sp + 8, count * 4)).hex()))

    contract = SimpleNamespace(**vars(sys.modules[__name__]))
    contract.Probe = previous.boundary_probe(facts, base=VoidProbe)
    contract.COHORT_COUNTS = {'integration': 1010, 'defaults': len(default_actions())*6,
                              'common_return': 16, 'unresolved740': 8,
                              'aim_argument_lifetimes': 600,
                              'projectile_receivers': 480,
                              'falling_returns': 192,
                              'landing_action_returns': 256,
                              'surface_inputs': 285,
                              'shot_boundaries': 1380,
                              'hover_snapshots': 354,
                              **{name: count for family in lifetime_families()
                                 for name, count in family.COHORT_COUNTS.items()
                                 if name in (*LIFETIME_COHORTS, *FLIGHT_COHORTS)}}
    result = low.audit(path, smoke, cohorts, contract=contract)
    target_sites = instances[0].visited
    required = {'falling_returns': (0x479713, 0x47973C),
                'landing_action_returns': (0x47977A, 0x479786)}
    for cohort, sites in required.items():
        if cohort in result['cohorts'] and not all(site in target_sites for site in sites):
            raise ValueError(cohort+' did not cover both original return paths')
    result['target_return_sites'] = {
        cohort: [hex(site) for site in sites if site in target_sites]
        for cohort, sites in required.items() if cohort in result['cohorts']}
    if 'flight_exit' in result['cohorts']:
        sites = (0x47BD95, 0x47BDDD, 0x47BE39, 0x47BE8D)
        if not all(site in target_sites for site in sites):
            raise ValueError('flight exits did not cover both facing branches in both sequence groups')
        result['target_flight_exit_sites'] = [hex(site) for site in sites]
    if 'surface_inputs' in result['cohorts']:
        if any({action for action, _ in p.surface_root_sites} != set(SURFACE_ACTIONS) for p in instances):
            raise ValueError('surface cohort did not query actual root height for all38 actions')
        result['surface_fixture'] = {
            'address': hex(SURFACE_ADDRESS), 'bytes': 4 * SURFACE_ELEMENTS,
            'pattern_sha256': hashlib.sha256(surface_terrain()).hexdigest(),
            'flat_sha256': hashlib.sha256(instances[0].original_surface).hexdigest(),
            'root_sites': {('source' if p.candidate else 'target'): [
                {'action': action, 'site': hex(site), 'count': count}
                for (action, site), count in sorted(p.surface_root_sites.items())] for p in instances},
            'query_x_words': {('source' if p.candidate else 'target'): [
                {'root': root, 'bits': bits, 'count': count}
                for (root, bits), count in sorted(p.surface_query_words.items())] for p in instances}}
    result['mode_structure'] = facts
    result['observed_return_low_bytes'] = {('source' if p.candidate else 'target'): dict(p.return_bytes)
                                          for p in instances}
    result['default_action_samples'] = list(default_actions())
    return result


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('object', type=Path)
    selection = parser.add_mutually_exclusive_group()
    selection.add_argument('--smoke', action='store_true')
    selection.add_argument('--cohort', action='append', choices=COHORTS)
    args = parser.parse_args()
    try:
        result = audit(args.object, args.smoke, args.cohort)
    except (KeyError, OSError, ValueError, unicorn.UcError) as error:
        parser.exit(2, f'Reimu void-root audit failed: {error}\n')
    print(json.dumps(result, indent=2))
    raise SystemExit(1 if result['mismatch_count'] else 0)
