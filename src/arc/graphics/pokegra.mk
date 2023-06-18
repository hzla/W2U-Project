POKEGRA_ROOT_DIR     	 := $(arc_dir)/graphics/pokemon
POKEGRA_ICONS_DIR	 	 := $(POKEGRA_ROOT_DIR)/icons
POKEGRA_SPRITES_DIR  	 := $(POKEGRA_ROOT_DIR)/sprites
POKEGRA_SPRITES_BUILD	 := $(build_dir)/pokegra

POKEGRA_SPR_TARGET   	 := $(romfs)/a/0/0/4
POKEGRA_ICONS_TARGET 	 := $(romfs)/a/0/0/7

$(POKEGRA_SPRITES_BUILD)/%.ncgr : %.png
	$(nitrogfx) $^ $@ 

$(POKEGRA_SPRITES_BUILD)/%.ncer : %.ncer
	cp $@ $^

$(POKEGRA_SPRITES_BUILD)/%.nanr : %.nanr
	cp $@ $^

$(POKEGRA_SPRITES_BUILD)/%.bin : %.bin
	cp $@ $^

$(POKEGRA_SPRITES_BUILD)/%.nmcr : %.nmcr
	cp $@ $^

$(POKEGRA_SPRITES_BUILD)/%.nmar : %.nmar
	cp $@ $^