POKEGRA_ROOT_DIR     	         := $(arc_dir)/graphics/pokemon
POKEGRA_ICONS_DIR	 	         := $(POKEGRA_ROOT_DIR)/icons
POKEGRA_SPRITES_DIR  	         := $(POKEGRA_ROOT_DIR)/sprites
POKEGRA_SPRITES_BUILD	         := $(build_dir)/pokegra_spr
POKEGRA_ICONS_BUILD	         	 := $(build_dir)/pokegra_icons

POKEGRA_FB_OBJ_CHAR	             := $(patsubst $(POKEGRA_SPRITES_DIR)/%.ncgr, $(POKEGRA_SPRITES_BUILD)/%.ncgr, $(wildcard $(POKEGRA_SPRITES_DIR)/*.ncgr))
POKEGRA_FB_OBJ_CELL	 	 	     := $(patsubst $(POKEGRA_SPRITES_DIR)/%.ncer, $(POKEGRA_SPRITES_BUILD)/%.ncer, $(wildcard $(POKEGRA_SPRITES_DIR)/*.ncer))
POKEGRA_FB_OBJ_ANIM	 	 	     := $(patsubst $(POKEGRA_SPRITES_DIR)/%.nanr, $(POKEGRA_SPRITES_BUILD)/%.nanr, $(wildcard $(POKEGRA_SPRITES_DIR)/*.nanr))
POKEGRA_FB_OBJ_MCELL_ANIM	     := $(patsubst $(POKEGRA_SPRITES_DIR)/%.nmar, $(POKEGRA_SPRITES_BUILD)/%.nmar, $(wildcard $(POKEGRA_SPRITES_DIR)/*.nmar))
POKEGRA_FB_OBJ_MCELL	 	     := $(patsubst $(POKEGRA_SPRITES_DIR)/%.nmcr, $(POKEGRA_SPRITES_BUILD)/%.nmcr, $(wildcard $(POKEGRA_SPRITES_DIR)/*.nmcr))
POKEGRA_FB_OBJ_BIN	 	         := $(patsubst $(POKEGRA_SPRITES_DIR)/%.bin, $(POKEGRA_SPRITES_BUILD)/%.bin, $(wildcard $(POKEGRA_SPRITES_DIR)/*.bin))
POKEGRA_FB_OBJ_PAL	 	         := $(patsubst $(POKEGRA_SPRITES_DIR)/%.nclr, $(POKEGRA_SPRITES_BUILD)/%.nclr, $(wildcard $(POKEGRA_SPRITES_DIR)/*.nclr))
POKEGRA_FB_OBJ			 	     := $(POKEGRA_FB_OBJ_CHAR) $(POKEGRA_FB_OBJ_CELL) $(POKEGRA_FB_OBJ_ANIM) $(POKEGRA_FB_OBJ_MCELL_ANIM) $(POKEGRA_FB_OBJ_MCELL) $(POKEGRA_FB_OBJ_BIN) $(POKEGRA_FB_OBJ_PAL)

POKEGRA_ICONS_OBJ_CHAR	         := $(patsubst $(POKEGRA_ICONS_DIR)/%.png, $(POKEGRA_ICONS_BUILD)/%.ncgr, $(wildcard $(POKEGRA_ICONS_DIR)/*.ncgr))
POKEGRA_ICONS_OBJ_CELL	 	 	 := $(patsubst $(POKEGRA_ICONS_DIR)/%.ncer, $(POKEGRA_ICONS_BUILD)/%.ncer, $(wildcard $(POKEGRA_ICONS_DIR)/*.ncer))
POKEGRA_ICONS_OBJ_ANIM	 	 	 := $(patsubst $(POKEGRA_ICONS_DIR)/%.nanr, $(POKEGRA_ICONS_BUILD)/%.nanr, $(wildcard $(POKEGRA_ICONS_DIR)/*.nanr))
POKEGRA_ICONS_OBJ_MCELL_ANIM	 := $(patsubst $(POKEGRA_ICONS_DIR)/%.nmcr, $(POKEGRA_ICONS_BUILD)/%.nmcr, $(wildcard $(POKEGRA_ICONS_DIR)/*.nmcr))
POKEGRA_ICONS_OBJ_MCELL	 	 	 := $(patsubst $(POKEGRA_ICONS_DIR)/%.nmcr, $(POKEGRA_ICONS_BUILD)/%.nmcr, $(wildcard $(POKEGRA_ICONS_DIR)/*.nmar))
POKEGRA_ICONS_OBJ_BIN	 	     := $(patsubst $(POKEGRA_ICONS_DIR)/%.bin, $(POKEGRA_ICONS_BUILD)/%.bin, $(wildcard $(POKEGRA_ICONS_DIR)/*.bin))
POKEGRA_ICONS_OBJ_PAL	 	     := $(patsubst $(POKEGRA_ICONS_DIR)/%.nclr, $(POKEGRA_ICONS_BUILD)/%.nclr, $(wildcard $(POKEGRA_ICONS_DIR)/*.nclr))
POKEGRA_ICONS_OBJ			 	 := $(POKEGRA_ICONS_OBJ_CHAR) $(POKEGRA_ICONS_OBJ_CELL) $(POKEGRA_ICONS_OBJ_ANIM) $(POKEGRA_ICONS_OBJ_MCELL_ANIM) $(POKEGRA_ICONS_OBJ_MCELL) $(POKEGRA_ICONS_OBJ_BIN) $(POKEGRA_ICONS_OBJ_PAL)

POKEGRA_FB_TARGET   	 	 	 := $(romfs)/a/0/0/4
POKEGRA_ICONS_TARGET 	 	 	 := $(romfs)/a/0/0/7

$(POKEGRA_FB_TARGET) : $(POKEGRA_FB_OBJ) $(game_base)
	$(knarc) -d $(POKEGRA_SPRITES_BUILD) -p $@

$(POKEGRA_ICONS_TARGET) : $(POKEGRA_ICONS_OBJ) $(game_base)
	$(knarc) -d $(POKEGRA_ICONS_BUILD) -p $@

# SPR
$(POKEGRA_SPRITES_BUILD)/%.ncgr : $(POKEGRA_SPRITES_DIR)/%.ncgr
	@ mkdir -p $(@D)
	cp $^ $@ 
	python3 $(lzcmp) $@ $@

$(POKEGRA_SPRITES_BUILD)/%.ncer : $(POKEGRA_SPRITES_DIR)/%.ncer
	@ mkdir -p $(@D)
	cp $^ $@ 

$(POKEGRA_SPRITES_BUILD)/%.nanr : $(POKEGRA_SPRITES_DIR)/%.nanr
	@ mkdir -p $(@D)
	cp $^ $@ 
	python3 $(lzcmp) $@ $@

$(POKEGRA_SPRITES_BUILD)/%.bin : $(POKEGRA_SPRITES_DIR)/%.bin
	@ mkdir -p $(@D)
	cp $^ $@ 

$(POKEGRA_SPRITES_BUILD)/%.nmcr : $(POKEGRA_SPRITES_DIR)/%.nmcr
	@ mkdir -p $(@D)
	cp $^ $@ 

$(POKEGRA_SPRITES_BUILD)/%.nmar : $(POKEGRA_SPRITES_DIR)/%.nmar
	@ mkdir -p $(@D)
	cp $^ $@ 

$(POKEGRA_SPRITES_BUILD)/%.nclr : $(POKEGRA_SPRITES_DIR)/%.nclr
	@ mkdir -p $(@D)
	cp $^ $@ 

# ICO

$(POKEGRA_ICONS_BUILD)/%.ncgr : $(POKEGRA_ICONS_DIR)/%.png
	@ mkdir -p $(@D)
	cp $^ $@ 

$(POKEGRA_ICONS_BUILD)/%.ncer : $(POKEGRA_ICONS_DIR)/%.ncer
	@ mkdir -p $(@D)
	cp $^ $@ 

$(POKEGRA_ICONS_BUILD)/%.nanr : $(POKEGRA_ICONS_DIR)/%.nanr
	@ mkdir -p $(@D)
	cp $^ $@ 

$(POKEGRA_ICONS_BUILD)/%.bin : $(POKEGRA_ICONS_DIR)/%.bin
	@ mkdir -p $(@D)
	cp $^ $@ 

$(POKEGRA_ICONS_BUILD)/%.nmcr : $(POKEGRA_ICONS_DIR)/%.nmcr
	@ mkdir -p $(@D)
	cp $^ $@ 

$(POKEGRA_ICONS_BUILD)/%.nmar : $(POKEGRA_ICONS_DIR)/%.nmar
	@ mkdir -p $(@D)
	cp $^ $@ 

$(POKEGRA_ICONS_BUILD)/%.nclr : $(POKEGRA_ICONS_DIR)/%.nclr
	@ mkdir -p $(@D)
	cp $^ $@ 