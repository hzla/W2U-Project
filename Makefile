# Project specific
project 		:= White2Upgrade
rom_code 		:= IRDO

# Directory configuration.
build_dir 		 = build
game_base       := $(build_dir)/$(rom_code)
incl_dir 		:= include
pmc_res 		:= pmc

src_dir          = src
data_dir		:= data

exefs 	        := $(game_base)/exefs
romfs 	        := $(game_base)/romfs

# Targets
## Code
asm_src  		:= $(wildcard $(src_dir)/*.s)
asm_obj 		:= $(patsubst $(src_dir)/%.s, $(build_dir)/code/%.o, $(asm_src))
c_src  			:= $(wildcard $(src_dir)/*.c)
c_obj  			:= $(patsubst $(src_dir)/%.c, $(build_dir)/code/%.o, $(c_src))
cpp_src  		:= $(wildcard $(src_dir)/*.cpp)
cpp_obj  		:= $(patsubst $(src_dir)/%.cpp, $(build_dir)/code/%.o, $(cpp_src))
code_objs		:= $(asm_obj) $(c_obj) $(cpp_obj)

# Tools
as 	  			:= arm-none-eabi-as
blz				:= tools/blz/blz 
CTRMap			:= tools/CTRMap/CTRMap.jar
gcc 	  		:= arm-none-eabi-gcc
knarc			:= tools/knarc/knarc
ld				:= arm-none-eabi-ld
ndstool   		:= ndstool
nitrogfx		:= tools/nitrogfx/nitrogfx
o2narc			:= tools/o2narc/o2narc
python			:= python3

# mkdata tools
# TODO: Condense into mkdata & invoke.
mkdata			:= $(python) tools/mkdata/mkdata.py
mkenc			:= $(python) tools/mkenc/mkenc.py
mklz			:= $(python) tools/mklz/mklz.py
mkmsg			:= $(python) tools/mkmsg/mkmsg.py
mky9			:= $(python) tools/mky9/mky9.py

# Flags
as_flags := -mthumb -march=armv5t -r
c_flags  := -mthumb -mno-thumb-interwork -march=armv5t -mno-long-calls -Wall -Wextra -Os -fira-loop-pressure -fipa-pta 

.PHONY: all clean

# ROM build.
all: $(project).nds
	@ echo "[!] Done!"

include $(data_dir)/Makefile.mk

$(project).nds: $(ARC_TARGETS) $(romfs)/patches/$(project).dll
	@ echo "[+] Copying build NARCs..."
	# cp $(build_dir)/system_text.arc $(romfs)/a/0/0/2
	# cp $(build_dir)/pokegra_fb.arc $(romfs)/a/0/0/4
	# cp $(build_dir)/pokegra_icons.arc $(romfs)/a/0/0/7
	# cp $(build_dir)/battle_assets.arc $(romfs)/a/0/1/1
	# cp $(build_dir)/ui_assets.arc $(romfs)/a/0/8/2
	# cp $(build_dir)/ui_assets2.arc $(romfs)/a/1/2/5
	# cp $(build_dir)/hall_of_fame_assets.arc $(romfs)/a/2/1/3

	# $(knarc) -d $(build_dir)/Personal -u $(build_dir)/Personal.arc
	# cp $(arc_dir)/pml/RegionalDex.bin $(build_dir)/Personal/Personal_00000826.bin
	# $(knarc) -d $(build_dir)/Personal -p $(build_dir)/Personal.arc
	# rm -rf $(build_dir)/Personal
	# cp $(build_dir)/Personal.arc $(romfs)/a/0/1/6

	# cp $(build_dir)/Learnsets.arc $(romfs)/a/0/1/8
	# cp $(build_dir)/Evolutions.arc $(romfs)/a/0/1/9
	# cp $(build_dir)/Children.arc $(romfs)/a/0/2/0
	# cp $(build_dir)/Moves.arc $(romfs)/a/0/2/1
	# cp $(build_dir)/Items.arc $(romfs)/a/0/2/4

	cp $(src_dir)/type_chart.bin $(romfs)/type_chart.bin

	@ echo "[+] Making $@..."
	$(ndstool) -c $@ -9 $(exefs)/ARM9.bin -7 $(exefs)/ARM7.bin -9i $(exefs)/ARM9i.bin -7i $(exefs)/ARM7i.bin -y9 $(exefs)/ARM9OVT.bin -y7 $(exefs)/ARM7OVT.bin -d $(romfs) -y $(exefs)/overlay -t $(exefs)/banner.bin -h $(exefs)/header.bin

$(romfs)/patches/$(project).dll: $(build_dir)/$(project).elf 
	@ mkdir -p $(romfs)/patches
	@ # java -cp $(CTRMap) rpm.cli.MAP2ESDB --map $(pmc_res)/Symbols.map --thmfile $(pmc_res)/SegmentRegisters.txt --output $(pmc_res)/ESDB.yml
	@ echo "[+] Creating DLL $@..."
	@ java -cp $(CTRMap) rpm.cli.RPMTool -i $< --fourcc DLXF -o $@ --esdb $(pmc_res)/ESDB.yml --generate-relocations

$(build_dir)/$(project).elf : $(code_objs)
	@ echo "[+] Linking all objects into $@..."
	@ $(ld) -o $@ -r $(code_objs)

# Code compilation/assembly.
$(build_dir)/code/%.o : $(src_dir)/%.s
	@ echo "[+] Assembling $<..."
	@ mkdir -p $(@D)
	@ $(as) $(as_flags) -c $< -o $@

$(build_dir)/code/%.o : $(src_dir)/%.c
	@ echo "[+] Compiling $<..."
	@ mkdir -p $(@D)
	@ $(gcc) $(c_flags) -I$(incl_dir) -I$(incl_dir)/swan -I$(incl_dir)/NitroKernel -c $< -o $@

$(build_dir)/code/%.o : $(src_dir)/%.cpp
	@ echo "[+] Compiling $<..."
	@ mkdir -p $(@D)
	@ $(gcc) $(c_flags) -I$(incl_dir) -I$(incl_dir)/swan -I$(incl_dir)/NitroKernel -c $< -o $@
	
# Extraction of the base game content.
base: 
	@ mkdir -p $(exefs)
	@ mkdir -p $(romfs)
	@ echo "[+] Extracting game to $(game_base)..."
	@ $(ndstool) -x $(rom_code).nds -9 $(exefs)/ARM9.bin -7 $(exefs)/ARM7.bin -9i $(exefs)/ARM9i.bin -7i $(exefs)/ARM7i.bin -y9 $(exefs)/ARM9OVT.bin -y7 $(exefs)/ARM7OVT.bin -d $(romfs) -y $(exefs)/overlay -t $(exefs)/banner.bin -h $(exefs)/header.bin
	
	@ echo "[+] Decompressing all overlays..."
	@ $(blz) -d $(exefs)/overlay/*

	@ echo "[+] Installing PMC..."
	@ cp pmc/ARM9PMC.bin $(exefs)/ARM9.bin # Replace ARM9 with PMC ARM9
	@ cp pmc/OVL344.bin $(exefs)/overlay/overlay_0344.bin # Replace with PMC Overlay 344
	@ $(mky9) data/overlay_table.yml $(exefs)/ARM9OVT.bin
	@ mkdir -p $(romfs)/data/codeinjection
	@ cp -r pmc/RPMSYM-PMC.rpm $(romfs)/data/codeinjection # Copy PMC SYM-0

# Tool building.
tools : $(blz) $(nitrogfx) $(knarc) $(o2narc)

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

# Cleanup.
clean: 
	rm -rf $(project).nds
	rm -rf $(build_dir)
	rm -rf $(nitrogfx)
	rm -rf $(blz)
	rm -rf $(knarc)
	rm -rf $(o2narc)