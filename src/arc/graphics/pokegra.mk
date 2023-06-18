POKEGRA_ROOT_DIR     	 := $(arc_dir)/graphics/pokemon
POKEGRA_ICONS_DIR	 	 := $(POKEGRA_ROOT_DIR)/icons
POKEGRA_SPRITES_DIR  	 := $(POKEGRA_ROOT_DIR)/sprites
POKEGRA_SPRITES_BUILD	 := $(build_dir)/pokegra

POKEGRA_OBJ_SPR	         := $(patsubst $(POKEGRA_SPRITES_DIR)/%.png, $(POKEGRA_SPRITES_BUILD)/%.ncgr, $(wildcard $(POKEGRA_SPRITES_DIR)/*.png))
POKEGRA_OBJ_CELL	 	 := $(patsubst $(POKEGRA_SPRITES_DIR)/%.ncer, $(POKEGRA_SPRITES_BUILD)/%.ncer, $(wildcard $(POKEGRA_SPRITES_DIR)/*.ncer))
POKEGRA_OBJ_ANIM	 	 := $(patsubst $(POKEGRA_SPRITES_DIR)/%.nanr, $(POKEGRA_SPRITES_BUILD)/%.nanr, $(wildcard $(POKEGRA_SPRITES_DIR)/*.nanr))
POKEGRA_OBJ_MCELL_ANIM	 := $(patsubst $(POKEGRA_SPRITES_DIR)/%.nmcr, $(POKEGRA_SPRITES_BUILD)/%.nmcr, $(wildcard $(POKEGRA_SPRITES_DIR)/*.nmcr))
POKEGRA_OBJ_MCELL	 	 := $(patsubst $(POKEGRA_SPRITES_DIR)/%.nmcr, $(POKEGRA_SPRITES_BUILD)/%.nmcr, $(wildcard $(POKEGRA_SPRITES_DIR)/*.nmar))
POKEGRA_OBJ_BIN	 	     := $(patsubst $(POKEGRA_SPRITES_DIR)/%.bin, $(POKEGRA_SPRITES_BUILD)/%.bin, $(wildcard $(POKEGRA_SPRITES_DIR)/*.bin))
POKEGRA_OBJ_BIN	 	     := $(patsubst $(POKEGRA_SPRITES_DIR)/%.pal, $(POKEGRA_SPRITES_BUILD)/%.nclr, $(wildcard $(POKEGRA_SPRITES_DIR)/*.pal))
POKEGRA_SPR_OBJ			 := $(POKEGRA_OBJ_SPR) $(POKEGRA_OBJ_CELL) $(POKEGRA_OBJ_ANIM) $(POKEGRA_OBJ_MCELL_ANIM) $(POKEGRA_OBJ_MCELL) $(POKEGRA_OBJ_BIN)

POKEGRA_SPR_TARGET   	 := $(romfs)/a/0/0/4
POKEGRA_ICONS_TARGET 	 := $(romfs)/a/0/0/7

$(POKEGRA_SPR_TARGET) : $(POKEGRA_SPR_OBJ)

$(POKEGRA_SPRITES_BUILD)/%.ncgr : $(POKEGRA_SPRITES_DIR)/%.png
	@ mkdir -p $(@D)
	$(nitrogfx) $^ $@ 

$(POKEGRA_SPRITES_BUILD)/%.ncer : $(POKEGRA_SPRITES_DIR)/%.ncer
	@ mkdir -p $(@D)
	cp $^ $@ 

$(POKEGRA_SPRITES_BUILD)/%.nanr : $(POKEGRA_SPRITES_DIR)/%.nanr
	@ mkdir -p $(@D)
	cp $^ $@ 

$(POKEGRA_SPRITES_BUILD)/%.bin : $(POKEGRA_SPRITES_DIR)/%.bin
	@ mkdir -p $(@D)
	cp $^ $@ 

$(POKEGRA_SPRITES_BUILD)/%.nmcr : $(POKEGRA_SPRITES_DIR)/%.nmcr
	@ mkdir -p $(@D)
	cp $^ $@ 

$(POKEGRA_SPRITES_BUILD)/%.nmar : $(POKEGRA_SPRITES_DIR)/%.nmar
	@ mkdir -p $(@D)
	cp $^ $@ 

$(POKEGRA_SPRITES_BUILD)/%.nclr : $(POKEGRA_SPRITES_DIR)/%.pal
	@ mkdir -p $(@D)
	$(nitrogfx) $^ $@ 