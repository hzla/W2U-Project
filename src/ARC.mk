# PML ARC root.
ARC_PML_ROOT_FILES 	:= $(arc_dir)/pml
PML_ARC_TARGETS     := $(patsubst $(arc_dir)/pml/%.c, $(build_dir)/%.arc, $(wildcard $(ARC_PML_ROOT_FILES)/*))

ARC_POKEGRA_ICON_FILES	:= $(arc_dir)/pokegra_icons
POKEGRA_ICON_SPRITES_NTR := $(patsubst %.png, %.bin, $(wildcard $(ARC_POKEGRA_ICON_FILES)/*))

ASSET_ARC_TARGETS := $(patsubst $(arc_dir)/%, $(build_dir)/%.arc, $(wildcard $(filter-out $(ARC_PML_ROOT_FILES), $(arc_dir)/*)))
ARC_TARGETS 	  := $(PML_ARC_TARGETS) $(ASSET_ARC_TARGETS)

# other rules
%.bin : %.png
	$(nitrogfx) $^ $*.ncgr -mwidth 4 -mheight 8
	mv $*.ncgr $@

# o2narc rules
$(build_dir)/%.arc : $(arc_dir)/pml/%.c
	$(gcc) $(c_flags) -I$(incl_dir) -I$(incl_dir)/swan -c $< -o $(build_dir)/$*.o
	@ rm -rf $@
	@ $(o2narc) $(build_dir)/$*.o $@

$(build_dir)/%.arc : $(arc_dir)/%
	$(knarc) -d $< -p $@
