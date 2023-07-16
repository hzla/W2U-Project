# Project specific
project 		:= expansion
rom_code 		:= IRDO

# Directory configuration.
build_dir 		:= build
game_base       := $(build_dir)/$(rom_code)
incl_dir 		:= include
ci_res 			:= pmc

src_dir         =  src
arc_dir		    := $(src_dir)/arc
code_dir		:= $(src_dir)/code

exefs 	        := $(game_base)/exefs
romfs 	        := $(game_base)/romfs
tools			:= tools

# Targets
asm_src  		:= $(wildcard $(code_dir)/*.s)
asm_obj 		:= $(patsubst $(code_dir)/%.s, $(build_dir)/code/%.o, $(asm_src))

c_src  			:= $(wildcard $(code_dir)/*.c)
c_obj  			:= $(patsubst $(code_dir)/%.c, $(build_dir)/code/%.o, $(c_src))

cpp_src  		:= $(wildcard $(code_dir)/*.cpp)
cpp_obj  		:= $(patsubst $(code_dir)/%.cpp, $(build_dir)/code/%.o, $(cpp_src))

objs			:= $(asm_obj) $(c_obj) $(cpp_obj)

# Tools
as 	  			:= arm-none-eabi-as
blz				:= tools/blz/blz 
CTRMap			:= tools/CTRMap/CTRMap.jar
gcc 	  		:= arm-none-eabi-gcc
g++		  		:= arm-none-eabi-g++
knarc			:= tools/knarc/knarc
ld				:= arm-none-eabi-ld
lzcmp			:= tools/lzss/compress.py
ndstool   		:= ndstool
nitrogfx		:= tools/nitrogfx/nitrogfx
o2narc			:= tools/o2narc/o2narc

# Flags
as_flags := -mthumb -march=armv5t -r
c_flags  := -mthumb -mno-thumb-interwork -march=armv5t -mno-long-calls -Wall -Wextra -Os -fira-loop-pressure -fipa-pta 

.PHONY: all clean

all: $(project).nds
	@ echo "[!] Done!"

include $(arc_dir)/ARC.mk

$(project).nds: make_tools $(game_base) arcs
	@ echo "[+] Making $@..."
	$(ndstool) -c $@ -9 $(exefs)/ARM9.bin -7 $(exefs)/ARM7.bin -9i $(exefs)/ARM9i.bin -7i $(exefs)/ARM7i.bin -y9 $(exefs)/ARM9OVT.bin -y7 $(exefs)/ARM7OVT.bin -d $(romfs) -y $(exefs)/overlay -t $(exefs)/banner.bin -h $(exefs)/header.bin

$(romfs)/patches/$(project).dll: $(build_dir)/$(project).elf 
	@ mkdir -p $(romfs)/patches
	@ # java -cp $(CTRMap) rpm.cli.MAP2ESDB --map $(ci_res)/Symbols.map --thmfile $(ci_res)/SegmentRegisters.txt --output $(ci_res)/ESDB.yml
	@ echo "[+] Creating DLL $@..."
	@ java -cp $(CTRMap) rpm.cli.RPMTool -i $< --fourcc DLXF -o $@ --esdb $(ci_res)/ESDB.yml --generate-relocations

$(build_dir)/$(project).elf : $(objs)
	@ echo "[+] Linking all objects into $@..."
	@ $(ld) -o $@ -r $(objs)

# Code compilation/assembly.
$(build_dir)/code/%.o : $(code_dir)/%.s
	@ echo "[+] Assembling $<..."
	@ mkdir -p $(@D)
	@ $(as) $(as_flags) -c $< -o $@

$(build_dir)/code/%.o : $(code_dir)/%.c
	@ echo "[+] Compiling $<..."
	@ mkdir -p $(@D)
	@ $(gcc) $(c_flags) -I$(incl_dir) -I$(incl_dir)/swan -I$(incl_dir)/NitroKernel -c $< -o $@

$(build_dir)/code/%.o : $(code_dir)/%.cpp
	@ echo "[+] Compiling $<..."
	@ mkdir -p $(@D)
	@ $(gcc) $(c_flags) -I$(incl_dir) -I$(incl_dir)/swan -I$(incl_dir)/NitroKernel -c $< -o $@
	
$(game_base): 
	@ mkdir -p $(exefs)
	@ mkdir -p $(romfs)
	@ echo "[+] Extracting game to $@..."
	@ $(ndstool) -x $(rom_code).nds -9 $(exefs)/ARM9.bin -7 $(exefs)/ARM7.bin -9i $(exefs)/ARM9i.bin -7i $(exefs)/ARM7i.bin -y9 $(exefs)/ARM9OVT.bin -y7 $(exefs)/ARM7OVT.bin -d $(romfs) -y $(exefs)/overlay -t $(exefs)/banner.bin -h $(exefs)/header.bin
	
	@ echo "[+] Decompressing all overlays..."
	@ $(blz) -d $(exefs)/overlay/*

	@ echo "[+] Installing PMC..."
	@ cp pmc/ARM9PMC.bin $(exefs)/ARM9.bin # Replace ARM9 with PMC ARM9
	@ cp pmc/OVL344.bin $(exefs)/overlay/overlay_0344.bin # Replace with PMC Overlay 344
	@ python3 tools/OVTMK.py src/OVT.yml $(exefs)/ARM9OVT.bin
	@ mkdir -p $(romfs)/data/codeinjection
	@ cp -r pmc/RPMSYM-PMC.rpm $(romfs)/data/codeinjection # Copy PMC SYM-0


make_tools : $(blz) $(nitrogfx) $(knarc) $(o2narc)

$(blz) : tools/blz/blz.c
	@ echo [+] Building blz...
	@ gcc -o tools/blz/blz tools/blz/blz.c

$(nitrogfx) : $(wildcard tools/nitrogfx)
	@ echo [+] Building nitrogfx...
	@ make --silent -C tools/nitrogfx

$(knarc) : $(wildcard tools/knarc)
	@ echo [+] Building knarc...
	@ make --silent -C tools/knarc

$(o2narc) : $(wildcard tools/o2narc)
	@ echo [+] Building o2narc...
	@ make --silent -C tools/o2narc

clean: 
	rm -rf $(project).nds
	rm -rf $(build_dir)
	rm -rf $(nitrogfx)
	rm -rf $(blz)
	rm -rf $(knarc)
	rm -rf $(o2narc)