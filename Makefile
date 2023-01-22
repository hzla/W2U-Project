# Project specific
project 		:= expansion
rom_code 		:= IRDO

# Directory configuration
build_dir 		:= build
code_build_dir  =  $(build_dir)/code
asm_build 	    =  $(code_build_dir)/asm
c_build 	    =  $(code_build_dir)/c
src_dir         =  src
asm_src_dir		:= $(src_dir)/asm
c_src_dir		:= $(src_dir)/c
incl_dir 		:= include
ci_res			:= ci
game_base       := $(build_dir)/$(rom_code)
exefs 	        := $(game_base)/exefs
romfs 	        := $(game_base)/romfs
tools			:= tools

# Targets
ignore_objs		:= $(c_build)/Personal.o
asm_srcs  		:= $(wildcard $(asm_src_dir)/*.s)
asm_objs  		:= $(patsubst $(asm_src_dir)/%.s, $(asm_build)/%.d, $(asm_srcs)) 
cpp_srcs    	:= $(wildcard $(c_src_dir)/*.cpp)
c_srcs    		:= $(wildcard $(c_src_dir)/*.c)
cpp_objs    	:= $(filter-out $(ignore_objs), $(patsubst $(c_src_dir)/%.cpp, $(c_build)/%.o, $(cpp_srcs))) 
c_objs    		:= $(filter-out $(ignore_objs), $(patsubst $(c_src_dir)/%.c, $(c_build)/%.o, $(c_srcs))) 
objs      		:= $(asm_objs) $(c_objs) $(cpp_objs)

# Tools
CTRMap			:= tools/CTRMap/CTRMap.jar
as 	  			:= arm-none-eabi-as
armips 			:= armips
blz				:= tools/blz/blz 
gcc 	  		:= arm-none-eabi-gcc
g++		  		:= arm-none-eabi-g++
knarc			:= tools/knarc/knarc
ld				:= arm-none-eabi-ld
ndstool   		:= ndstool
o2narc			:= tools/o2narc/o2narc

# Flags
as_flags := -mthumb -march=armv5t -r
c_flags  := -mthumb -mno-thumb-interwork -march=armv5t -mno-long-calls -Wall -Wextra -Os -fira-loop-pressure -fipa-pta -r

.PHONY: clean all

all: $(project).nds 
	@ echo "[!] Done!"

$(project).nds: $(game_base) $(romfs)/patches/$(project).dll $(romfs)/a/0/1/6 make_narcs
	@ echo "[+] Making $@..."
	@ $(ndstool) -c $@ -9 $(exefs)/ARM9.bin -7 $(exefs)/ARM7.bin -y9 $(exefs)/ARM9OVT.bin -y7 $(exefs)/ARM7OVT.bin -d $(romfs) -y $(exefs)/overlay -t $(exefs)/banner.bin -h $(exefs)/header.bin

$(game_base): make_tools
	@ mkdir -p $(exefs)
	@ mkdir -p $(romfs)
	@ echo "[+] Extracting game to $@..."
	@ $(ndstool) -x $(rom_code).nds -9 $(exefs)/ARM9.bin -7 $(exefs)/ARM7.bin -y9 $(exefs)/ARM9OVT.bin -y7 $(exefs)/ARM7OVT.bin -d $(romfs) -y $(exefs)/overlay -t $(exefs)/banner.bin -h $(exefs)/header.bin
	
	@ echo "[+] Decompressing all overlays..."
	@ $(blz) -d $(exefs)/overlay/*

	@ echo "[+] Installing PMC..."
	@ cp vfs/ARM9PMC.bin $(exefs)/ARM9.bin # Replace ARM9 with PMC ARM9
	@ cp vfs/OVL344.bin $(exefs)/overlay/overlay_0344.bin # Replace with PMC Overlay 344
	@ armips src/ARM9OVT.s
	@ cp -r vfs/codeinjection $(romfs) # Copy PMC SYM-0

$(romfs)/patches/$(project).dll: $(code_build_dir)/$(project).elf 
	@ mkdir -p $(romfs)/patches
	@ # java -cp $(CTRMap) rpm.cli.MAP2ESDB --map $(ci_res)/Symbols.map --thmfile $(ci_res)/SegmentRegisters.txt --output $(ci_res)/ESDB.yml
	@ echo "[+] Creating DLL $@..."
	@ java -cp $(CTRMap) rpm.cli.RPMTool -i $< --fourcc DLXF -o $@ --esdb $(ci_res)/ESDB.yml --generate-relocations

$(code_build_dir)/$(project).elf : $(objs)
	@ echo "[+] Linking all objects into $@..."
	@ $(ld) -o $@ -r $(c_objs) $(cpp_objs) $(asm_objs)

# Code compilation/assembly.
$(asm_build)/%.d : $(asm_src_dir)/%.s
	@ echo "[+] Assembling $<..."
	@ mkdir -p $(asm_build)
	@ $(as) $(as_flags) -c $< -o $@
$(c_build)/%.o : $(c_src_dir)/%.c
	@ echo "[+] Compiling $<..."
	@ mkdir -p $(c_build) 
	@ $(gcc) $(c_flags) -I$(incl_dir) -I$(incl_dir)/swan -I$(incl_dir)/NitroKernel -c $< -o $@
$(c_build)/%.o : $(c_src_dir)/%.cpp
	@ echo "[+] Compiling $<..."
	@ mkdir -p $(c_build) 
	@ $(gcc) $(c_flags) -I$(incl_dir) -I$(incl_dir)/swan -I$(incl_dir)/NitroKernel -c $< -o $@

make_narcs: make_personal_data
	@ echo "[+] Updating NARCs..."
	@ # TODO: Make a bit cleaner.
	@ python3 tools/NARCUpdater.py build/$(rom_code)
	@ echo "[+] Making icons..."
	@ python vfs/graphics/make.py
	@ $(knarc) -d $(game_base)/narcs/a/0/0/7 -p $(romfs)/a/0/0/7
make_personal_data: $(c_build)/Personal.o
	@ echo "[+] Making Personal ARC..."
	@ $(o2narc) $< $(romfs)/a/0/1/6

make_tools:
	@ echo [+] Building blz...
	@ gcc -o tools/blz/blz tools/blz/blz.c
	@ echo [+] Building knarc...
	@ make --silent -C tools/knarc
	@ echo [+] Building nitrogfx...
	@ make --silent -C tools/nitrogfx
	@ echo [+] Building o2narc...
	@ make --silent -C tools/o2narc

clean: 
	rm -rf $(project).nds
	rm -rf $(build_dir)