import copy
from pathlib import Path
import struct
import sys
import tomllib
from types import SimpleNamespace
import unittest
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
import csprite_lifetime_origins as g
class SpriteLifetimeTests(unittest.TestCase):
    def fixture(self):
        s=tomllib.loads(g.ANCHORS.read_text());return s,[dict(address=a,size=str(v[0]))for a,v in g.CONTRACT.items()],g.load_manifest()['units']
    def test_two_whole_actual_lifetimes(self):
        s,r,u=self.fixture();aa,_,_=g.validate_spec(s,r,u,s['target_sha256']);self.assertEqual(sum(a['size']for a in aa),23)
    def test_no_mask_or_partial_body(self):
        for k,v in [('size',15),('mask',[11])]:
            s,r,u=self.fixture();s['anchors'][0][k]=v
            with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_source_hierarchy_review_pinned(self):
        s,r,u=self.fixture();s['source_sha256']['src/battle/EffectSprite.hpp']='0'*64
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_old_raw_vptr_probe_not_accepted(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.UNIT]['functions'][0]['symbol_base']='??0UiSpriteCtorProbe@th105@@QAE@XZ'
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_actual_parent_required(self):
        s,r,u=self.fixture();u=copy.deepcopy(u);u[g.PARENT]['enable_gs']=False
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def test_no_alias_double_count(self):
        s,r,u=self.fixture();s['anchors'].append(copy.deepcopy(s['anchors'][1]))
        with self.assertRaises(ValueError):g.validate_spec(s,r,u,s['target_sha256'])
    def weak(self):
        symbols={0:SimpleNamespace(name=g.SCALAR,section_number=0,value=0),1:SimpleNamespace(name=g.WEAK,section_number=0,value=0),3:SimpleNamespace(name=g.SCALAR,section_number=11,value=0)};reader=SimpleNamespace(cf=SimpleNamespace(symbols=symbols),symbol=lambda n:symbols[3]);raw=bytearray(100);struct.pack_into('<II',raw,8,20,4);raw[52:56]=bytes([32,0,105,1]);struct.pack_into('<II',raw,56,0,2);return reader,raw
    def test_actual_weak_scalar_fallback(self):
        r,b=self.weak();self.assertEqual(g.weak_fallback(r,bytes(b))['fallback'],g.SCALAR)
    def test_other_equivalent_scalar_name_rejected(self):
        r,b=self.weak();r.cf.symbols[0].name='??_GIColor@@UAEPAXI@Z'
        with self.assertRaises(ValueError):g.weak_fallback(r,bytes(b))
    def test_wrong_weak_search_or_aux_rejected(self):
        for off in [54,60,64]:
            r,b=self.weak();b[off]^=1
            with self.assertRaises(ValueError):g.weak_fallback(r,bytes(b))
    def array(self):
        b=bytearray.fromhex('680000000068000000006a0268940000008d867c02000050c644242c06899e78020000e800000000');n=bytearray(b);struct.pack_into('<I',n,1,0x40ad50);struct.pack_into('<I',n,6,0x40ada0);struct.pack_into('<i',n,36,0x68a30c-(0x44dc03+40));r=SimpleNamespace(symbol=lambda n:SimpleNamespace(value=0),section=lambda n:SimpleNamespace(raw_size=411),raw=lambda n,s,o:bytes(b),refs=lambda n,s,o:[(1,6,g.DTOR),(6,6,g.CTOR),(36,20,g.ARRAY)]);return r,b,bytes(n)
    def test_actual_sprite_array_pair(self):
        r,b,n=self.array();self.assertEqual(g.array_site(r,lambda a,s:n)['member_offset'],636)
    def test_actual_callback_not_other_sprite_constructor(self):
        r,b,n=self.array();n=bytearray(n);struct.pack_into('<I',n,6,0x41f6e0)
        with self.assertRaises(ValueError):g.array_site(r,lambda a,s:bytes(n))
    def test_count_stride_member_and_addend_required(self):
        for off in [1,11,13,19]:
            r,b,n=self.array();b[off]^=1
            with self.assertRaises(ValueError):g.array_site(r,lambda a,s:n)
    def table(self):
        refs=[(i*4,6,n)for i,(n,a)in enumerate(g.TABLE_SLOTS)];raw=bytearray(36);native=bytearray(struct.pack('<9I',*(a for n,a in g.TABLE_SLOTS)))
        r=SimpleNamespace(section=lambda n:SimpleNamespace(name='.rdata',raw_size=40),symbol=lambda n:SimpleNamespace(value=4),refs=lambda n,size:refs,raw=lambda n,size:bytes(raw))
        return r,refs,raw,native
    def test_complete_nine_virtual_slots(self):
        r,refs,raw,n=self.table();self.assertEqual(len(g.virtual_table(r,lambda a,s:bytes(n))['slots']),9)
    def test_old_four_slot_table_rejected(self):
        r,refs,raw,n=self.table();r.section=lambda name:SimpleNamespace(name='.rdata',raw_size=20)
        with self.assertRaises(ValueError):g.virtual_table(r,lambda a,s:bytes(n))
    def test_signed_rectangle_contract(self):
        r,refs,raw,n=self.table();refs[4]=(16,6,'?set_texture_options@CSprite@@UAEXIHHIIHH@Z')
        with self.assertRaises(ValueError):g.virtual_table(r,lambda a,s:bytes(n))
    def test_render_slots_cannot_swap(self):
        r,refs,raw,n=self.table();n[28:32],n[32:36]=n[32:36],n[28:32]
        with self.assertRaises(ValueError):g.virtual_table(r,lambda a,s:bytes(n))
    def test_each_native_slot_byte_checked(self):
        for i in range(36):
            r,refs,raw,n=self.table();n[i]^=1
            with self.assertRaises(ValueError):g.virtual_table(r,lambda a,s:bytes(n))
    def test_table_source_addend_rejected(self):
        r,refs,raw,n=self.table();raw[16]=4
        with self.assertRaises(ValueError):g.virtual_table(r,lambda a,s:bytes(n))
    def test_missing_or_extra_role_rejected(self):
        for extra in [False,True]:
            r,refs,raw,n=self.table()
            if extra:refs.append((36,6,'extra'))
            else:refs.pop()
            with self.assertRaises(ValueError):g.virtual_table(r,lambda a,s:bytes(n))
    def test_real_array_owner_emits_lifetimes(self):
        spec,rows,units=self.fixture();_,unit,parent=g.validate_spec(spec,rows,units,spec['target_sha256'])
        self.assertEqual(unit['source'],parent['source']);self.assertTrue(unit['enable_gs'])
    def test_detached_lifetime_stub_rejected(self):
        spec,rows,units=self.fixture();units=copy.deepcopy(units);units[g.UNIT]['source']='src/ui/UiSpriteLifetime.cpp'
        with self.assertRaises(ValueError):g.validate_spec(spec,rows,units,spec['target_sha256'])
    def test_common_interface_source_must_be_reviewed(self):
        spec,rows,units=self.fixture();spec['source_sha256'].pop('src/engine/ColorInterface.hpp')
        with self.assertRaises(ValueError):g.validate_spec(spec,rows,units,spec['target_sha256'])
if __name__=='__main__':unittest.main()
