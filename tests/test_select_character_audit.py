import copy
import importlib.util
from pathlib import Path
import sys
import unittest
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
sp=importlib.util.spec_from_file_location('character_audit_tests',Path(__file__).resolve().parents[1]/'scripts/audit-select-character-update.py');g=importlib.util.module_from_spec(sp);sp.loader.exec_module(g)
class CharacterAuditTests(unittest.TestCase):
    def shape(self):return [619,192,{0x41fcba:bytes.fromhex('8d9b00000000')},{a:b'\xc3'for a in [0x41fe2a,0x41feb1,0x41fed7,0x41fefa]}]
    def test_complete_body_and_four_returns(self):g.check_shape(*self.shape())
    def test_no_partial_extent_or_instruction_census(self):
        for i,v in [(0,613),(1,191)]:
            args=self.shape();args[i]=v
            with self.assertRaises(ValueError):g.check_shape(*args)
    def test_compared_alignment_cannot_change(self):
        args=self.shape();args[2][0x41fcba]=bytes.fromhex('8d9b01000000')
        with self.assertRaises(ValueError):g.check_shape(*args)
    def test_missing_return_rejected(self):
        args=self.shape();args[3].pop(0x41feb1)
        with self.assertRaises(ValueError):g.check_shape(*args)
    def test_wrong_return_stack_cleanup(self):
        args=self.shape();args[3][0x41fefa]=b'\xc2\x04\x00'
        with self.assertRaises(ValueError):g.check_shape(*args)
    def case(self,name):return copy.deepcopy(next(c for c in g.CASES if c['name']==name))
    def random(self):
        return dict(result=6,state=0,characters=[12,3],confirmed=[1,0],options=[0,0],random=[1,170],events=[dict(kind='mode',args=[],result=1),dict(kind='mode',args=[],result=1),dict(kind='random',args=[13]),dict(kind='prepare',args=[0]),dict(kind='fade',args=[1000,0])])
    def test_locked_random_contract(self):g.check_observation(self.case('random_locked'),self.random())
    def test_wrong_random_bound_rejected(self):
        obs=self.random();obs['events'][2]['args']=[15]
        with self.assertRaises(ValueError):g.check_observation(self.case('random_locked'),obs)
    def test_random_flag_required(self):
        obs=self.random();obs['random'][0]=0
        with self.assertRaises(ValueError):g.check_observation(self.case('random_locked'),obs)
    def changes(self):
        return dict(result=6,state=0,characters=[5,3],confirmed=[1,0],options=[0,0],random=[0,170],events=[dict(kind='mode',args=[],result=2),dict(kind='mode',args=[],result=1),dict(kind='prepare',args=[0]),dict(kind='fade',args=[1000,0])])
    def test_independent_mode_queries(self):g.check_observation(self.case('mode_changes'),self.changes())
    def test_caching_first_mode_is_not_equivalent(self):
        obs=self.changes();obs['events'][1]['result']=2
        with self.assertRaises(ValueError):g.check_observation(self.case('mode_changes'),obs)
    def test_shared_cancel_does_not_leave_scene(self):
        obs=dict(result=3,state=0,characters=[2,3],confirmed=[0,0],options=[0,0],random=[170,170],events=[dict(kind='event',args=[41]),dict(kind='cursor',args=[]),dict(kind='cursor',args=[]),dict(kind='event',args=[41]),dict(kind='mode',args=[],result=2),dict(kind='mode',args=[],result=2)])
        g.check_observation(self.case('shared_second_cancel'),obs);obs['result']=2
        with self.assertRaises(ValueError):g.check_observation(self.case('shared_second_cancel'),obs)
    def test_no_unreviewed_event_added(self):
        obs=self.random();obs['events'].append(dict(kind='event',args=[40]))
        with self.assertRaises(ValueError):g.check_observation(self.case('random_locked'),obs)
if __name__=='__main__':unittest.main()
