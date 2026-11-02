import copy
import importlib.util
from pathlib import Path
import sys
import unittest
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
spec = importlib.util.spec_from_file_location('profile_preview_tests',Path(__file__).resolve().parents[1]/'scripts/audit-profile-character-preview.py')
g = importlib.util.module_from_spec(spec)
spec.loader.exec_module(g)


class ProfilePreviewTests(unittest.TestCase):
    def test_complete_call_and_store_contract(self):
        g.check_contract(dict(g.EXPECTED_CALLS),3,[(4,4),(4,4)],[0])

    def test_wrong_call_width_or_return_rejected(self):
        good = [dict(g.EXPECTED_CALLS),3,[(4,4),(4,4)],[0]]
        for index,value in [(0,{}),(1,2),(2,[(4,2),(4,4)]),(3,[4])]:
            args = copy.deepcopy(good)
            args[index] = value
            with self.assertRaises(ValueError):
                g.check_contract(*args)

    def test_absent_selection_only_releases_and_clears(self):
        case = dict(old_handle=99,character=-1,loaded=7)
        result = dict(calls=[('release',99)],writes=[(4,4,0)],texture=0,cookie_checks=1)
        g.check_result(case,result)
        result['calls'].append(('name',-1))
        with self.assertRaises(ValueError):
            g.check_result(case,result)

    def test_success_requires_texture_then_gray_color(self):
        case = dict(old_handle=3,character=15,loaded=0xf0000000)
        path = g.PATH_BYTES[:-1].decode()
        result = dict(calls=[('release',3),('name',15),('format',path),('load',path,0,0),('texture',0xf0000000,0,0,512,480),('color',0xff808080)],writes=[(4,4,0),(4,4,0xf0000000)],texture=0xf0000000,cookie_checks=1)
        g.check_result(case,result)
        result['calls'][-1] = ('color',0xffffffff)
        with self.assertRaises(ValueError):
            g.check_result(case,result)


if __name__ == '__main__':
    unittest.main()
