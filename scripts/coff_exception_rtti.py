"""Whole symbolic COFF RTTI graph replay for the original exception probes."""
import importlib.util
from pathlib import Path
import struct
import sys
import linked_pe as core
from linked_logic_error_origins import require,digest

ROOT=Path(__file__).resolve().parents[1]

class Reader:
    def __init__(self,path):
        spec=importlib.util.spec_from_file_location('exception_rtti_coff',ROOT/'scripts/compare-giant-action-switches.py')
        module=importlib.util.module_from_spec(spec);sys.modules[spec.name]=module;spec.loader.exec_module(module)
        self.cf=module.CoffObject(path)
    def symbol(self,name):
        found=[s for s in self.cf.symbols.values()if s.name==name and s.section_number>0]
        require(len(found)==1,'COFF exception symbol must have one definition: '+name);return found[0]
    def section(self,name):return self.cf.sections[self.symbol(name).section_number-1]
    def raw(self,name,size,offset=0):
        s=self.symbol(name);sec=self.cf.sections[s.section_number-1];start=s.value+offset
        require(type(size)is int and size>0 and type(offset)is int,'COFF region size/offset must be explicit integers')
        require(0<=start and start+size<=sec.raw_size,'COFF exception region exceeds its owned section')
        return self.cf._read_raw(sec.raw_offset+start,size)
    def refs(self,name,size,offset=0):
        s=self.symbol(name);sec=self.cf.sections[s.section_number-1];start=s.value+offset;out=[]
        for i in range(sec.reloc_count):
            at,idx,kind=struct.unpack('<IIH',self.cf._read_raw(sec.reloc_offset+10*i,10))
            if start<=at<start+size:
                require(at+4<=start+size,'COFF relocation crosses region boundary')
                out.append((at-start,kind,self.cf.symbols[idx].name))
        return out
    def pointer(self,name,offset):
        rr=self.refs(name,4,offset)
        require(len(rr)==1 and rr[0][:2]==(0,6)and self.raw(name,4,offset)==b'\0'*4,'COFF typed pointer must be one zero-addend DIR32')
        return rr[0][2]
    def typename(self,name):
        s=self.symbol(name);sec=self.cf.sections[s.section_number-1];tail=self.cf._read_raw(sec.raw_offset+s.value+8,sec.raw_size-s.value-8)
        require(b'\0'in tail and tail.index(b'\0')<512,'COFF whole type name is missing or oversized')
        return tail[:tail.index(b'\0')+1]

class RttiGraph:
    def __init__(self,reader,game,read,allowed_types):
        self.r=reader;self.game=game;self.read=read;self.allowed=set(allowed_types)
        self.bindings={};self.hierarchies={};self.records=[];self.tables=[]
    def bind(self,name,address):
        require(name not in self.bindings or self.bindings[name]==address,'COFF RTTI pointer identity is inconsistent')
        self.bindings[name]=address
    def words(self,address,count):return list(struct.unpack('<'+'I'*count,self.read(address,4*count)))
    def record(self,name,size,address,fields,offset=0,readonly=True):
        raw=bytearray(self.r.raw(name,size,offset));refs=self.r.refs(name,size,offset)
        require({r[0]for r in refs}==set(fields)and len(refs)==len(fields),'COFF whole RTTI relocation inventory differs')
        if readonly:require(self.r.section(name).name in {'.rdata','.rdata$r'}and self.r.section(name).characteristics&0x40000000 and not self.r.section(name).characteristics&0xa0000000 and core.readonly_data(self.game,address,size)==self.read(address,size),'RTTI readonly ownership differs')
        for off,kind,symbol in refs:
            require(kind==6 and struct.unpack_from('<I',raw,off)[0]==0,'COFF RTTI needs typed zero-addend DIR32 fields')
            self.bind(symbol,fields[off]);struct.pack_into('<I',raw,off,fields[off])
        require(raw==self.read(address,size),'COFF complete RTTI record differs')
        self.records.append(dict(symbol=name,offset=offset,address=hex(address),size=size,sha256=digest(raw)))
    def descriptor(self,name,address,expected=None):
        self.bind(name,address);require(self.r.section(name).name in {'.data','.rdata'},'COFF TypeDescriptor storage differs')
        text=self.r.typename(name);typename=text[:-1].decode('ascii')
        require(typename in self.allowed and (expected is None or typename==expected),'COFF exception class identity differs')
        require(self.r.pointer(name,0)=='??_7type_info@@6B@'and self.r.raw(name,4,4)==b'\0'*4,'COFF TypeDescriptor header differs')
        header=self.words(address,2)
        require(header[1]==0 and core.primary_type_name(self.game,header[0])=='.?AVtype_info@@','native TypeDescriptor type_info identity differs')
        self.record(name,8+len(text),address,{0:header[0]},readonly=False)
        return typename
    def hierarchy(self,name,address,expected):
        self.bind(name,address)
        if name in self.hierarchies:
            require(self.hierarchies[name]==expected,'COFF RTTI hierarchy cycle changes type');return
        self.hierarchies[name]=expected
        sw=list(struct.unpack('<4I',self.r.raw(name,16)));tw=self.words(address,4)
        require(sw[:3]==tw[:3]and sw[0]==0 and sw[1]in (0,1)and 1<=sw[2]<=8,'COFF nonvirtual exception hierarchy differs')
        array=self.r.pointer(name,12);count=sw[2];targets=self.words(tw[3],count);self.bind(array,tw[3])
        for i,to in enumerate(targets):
            desc=self.r.pointer(array,4*i);self.bind(desc,to);sd=list(struct.unpack('<7I',self.r.raw(desc,28)));td=self.words(to,7)
            require(sd[1:6]==td[1:6]and sd[1]<8 and sd[2]<128 and sd[3:6]==[0xffffffff,0,0x40],'COFF exception base adjustments differ')
            typename=self.descriptor(self.r.pointer(desc,0),td[0],expected if i==0 else None)
            child=self.r.pointer(desc,24)
            if i==0:require(child==name and td[6]==address and sd[1]==count-1 and sd[2]==0,'COFF own-class RTTI hierarchy must close locally')
            self.hierarchy(child,td[6],typename)
            self.record(desc,28,to,{0:td[0],24:td[6]})
        self.record(array,count*4,tw[3],{4*i:to for i,to in enumerate(targets)})
        self.record(name,16,address,{12:tw[3]})
    def table(self,name,address,offset,typename):
        self.bind(name,address);col=self.r.pointer(name,-4);native_col=self.words(address-4,1)[0];self.bind(col,native_col)
        sw=list(struct.unpack('<5I',self.r.raw(col,20)));tw=self.words(native_col,5)
        require(sw[:3]==tw[:3]==[0,offset,0],'COFF exception primary/secondary subobject offset differs')
        self.descriptor(self.r.pointer(col,12),tw[3],typename)
        self.hierarchy(self.r.pointer(col,16),tw[4],typename)
        self.record(col,20,native_col,{12:tw[3],16:tw[4]});self.record(name,4,address-4,{0:native_col},offset=-4)
        self.tables.append(dict(symbol=name,address=hex(address),offset=offset,type_name=typename))
