"""Execute the final stripped setup veneer at different module addresses."""
import struct
from pathlib import Path


def verify(path):
    from unicorn import Uc, UC_ARCH_ARM, UC_MODE_THUMB, UC_HOOK_CODE
    from unicorn.arm_const import (UC_CPU_ARM_946, UC_ARM_REG_R0, UC_ARM_REG_R1,
        UC_ARM_REG_R2, UC_ARM_REG_R3, UC_ARM_REG_R4, UC_ARM_REG_R5,
        UC_ARM_REG_SP, UC_ARM_REG_LR, UC_ARM_REG_PC)
    raw = Path(path).read_bytes()
    u32 = lambda offset: struct.unpack_from("<I",raw,offset)[0]
    assert raw[:4]==b"DLXF"
    header=u32(8)
    assert raw[header:header+4]==b"DLXH" and u32(header+12)==0
    info=header+u32(header+8)
    symbols_at=header+u32(info+4)
    symbols=[struct.unpack_from("<HHIBBH",raw,symbols_at+24+12*i)
             for i in range(u32(symbols_at+20))]
    assert all(name==0 and not flags&2 for name,size,at,kind,flags,section in symbols)
    image=raw[u32(info+16):u32(info+16)+u32(info+20)]
    rel=header+u32(info+8)
    modules=header+u32(rel+20)
    assert struct.unpack_from("<H",raw,modules)[0]==1
    strings=header+u32(info+12)+4
    name=strings+struct.unpack_from("<H",raw,modules+2)[0]
    assert raw[name:raw.index(0,name)]==b"ARM9"
    assert struct.unpack_from("<H",raw,symbols_at+10)[0]==1
    assert u32(info+24)==u32(info+28)==0xffffffff
    relocations=[]
    for field in (8,12,16):
        if u32(rel+field)==0xffffffff: continue
        start=header+u32(rel+field)
        relocations += [struct.unpack_from("<IBBH",raw,start+4+8*i) for i in range(u32(start))]
    external=[entry for entry in relocations if entry[1]!=255]
    assert len(external)==1 and external[0][:3]==(0x020182c0,0,5)
    checks=0
    for base in (0x02300000,0x02380004):
        loaded=bytearray(image)
        for at,module,kind,index in relocations:
            if module!=255: continue
            _,_,symbol,typ,flags,_=symbols[index]
            assert kind==0 and not flags&6
            struct.pack_into("<I",loaded,at,(base+symbol)|(typ==3))
        _,size,offset,_,flags,_=symbols[external[0][3]]
        assert size==16 and not flags&6
        for trainer in (1,4,65533):
            cpu=Uc(UC_ARCH_ARM,UC_MODE_THUMB)
            cpu.ctl_set_cpu_model(UC_CPU_ARM_946)
            cpu.mem_map(0x02000000,0x400000)
            cpu.mem_write(base,bytes(loaded))
            cpu.mem_write(0x020182c0,bytes(loaded[offset:offset+size]))
            cpu.mem_write(0x020183b0,b"\x70\x47") # Native setup replaced by an argument spy only.
            stack,stop=0x023f0000,0x02008000
            args=(0x02200000,0x02210000,0x02220000,trainer)
            for register,value in zip((UC_ARM_REG_R0,UC_ARM_REG_R1,UC_ARM_REG_R2,UC_ARM_REG_R3),args):
                cpu.reg_write(register,value)
            cpu.reg_write(UC_ARM_REG_R4,0x11223344)
            cpu.reg_write(UC_ARM_REG_R5,0x55667788)
            cpu.reg_write(UC_ARM_REG_SP,stack)
            cpu.reg_write(UC_ARM_REG_LR,stop|1)
            cpu.mem_write(stack,struct.pack("<I",4))
            observed=[]
            def spy(cpu,address,size,user):
                if address!=0x020183b0:return
                sp=cpu.reg_read(UC_ARM_REG_SP)
                assert sp%8==0
                observed.append(tuple(cpu.reg_read(r) for r in (UC_ARM_REG_R0,UC_ARM_REG_R1,UC_ARM_REG_R2,UC_ARM_REG_R3))+
                    struct.unpack("<III",cpu.mem_read(sp,12)))
            cpu.hook_add(UC_HOOK_CODE,spy)
            cpu.emu_start(0x020182c1,stop,count=100)
            assert observed==[args[:3]+(trainer+1,trainer,trainer+2,4)]
            assert cpu.reg_read(UC_ARM_REG_SP)==stack and cpu.reg_read(UC_ARM_REG_PC)==stop
            assert cpu.reg_read(UC_ARM_REG_R4)==0x11223344 and cpu.reg_read(UC_ARM_REG_R5)==0x55667788
            checks+=1
    return checks
