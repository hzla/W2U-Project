# -------------------------------------------------------------------
# ARC Definitions
# -------------------------------------------------------------------

# ARC labels
TEXT_SYSTEM_ARC       := /a/0/0/2
TEXT_EVENTS_ARC       := /a/0/0/3
POKEGRA_SPRITES_ARC   := /a/0/0/4
POKEGRA_ICONS_ARC     := /a/0/0/7

PML_PERSONAL_ARC      := /a/0/1/6
PML_LEARNSETS_ARC     := /a/0/1/8
PML_EVOLUTION_ARC     := /a/0/1/9
PML_MOVES_ARC         := /a/0/2/1
PML_ITEMS_ARC         := /a/0/2/4
UI_GRAPHICS_ARC       := /a/0/8/2
UI2_GRAPHICS_ARC      := /a/1/2/5
ENCOUNTERS_ARC        := /a/1/2/7

# -------------------------------------------
# PML ARCs
PML_EVOLUTION_ROOT   := $(data_dir)/pml/evolutions
PML_LEARNSETS_ROOT   := $(data_dir)/pml/learnsets
PML_MOVES_ROOT       := $(data_dir)/pml/moves
PML_PERSONAL_ROOT    := $(data_dir)/pml/personal

# General ARCs
ENCOUNTERS_ROOT      := $(data_dir)/encounters
ITEMS_ROOT           := $(data_dir)/items
TEXT_SYSTEM_ROOT     := $(data_dir)/text/system
TEXT_EVENTS_ROOT     := $(data_dir)/text/events

# Graphics ARCs
BATTLE_GRAPHICS_ROOT := $(data_dir)/graphics/battle
HALL_OF_FAME_GRAPHICS_ROOT := $(data_dir)/graphics/hall_of_fame
POKEGRA_SPRITES_ROOT := $(data_dir)/graphics/pokegra/battle_sprites
POKEGRA_ICONS_ROOT := $(data_dir)/graphics/pokegra/icons
UI_GRAPHICS_ROOT := $(data_dir)/graphics/ui
UI2_GRAPHICS_ROOT := $(data_dir)/graphics/ui_2

# -------------------------------------------------------------------
# Targets 
# -------------------------------------------------------------------
ARCS := $(POKEGRA_ICONS_ARC) $(POKEGRA_SPRITES_ARC) $(ENCOUNTERS_ARC) $(TEXT_SYSTEM_ARC) $(TEXT_EVENTS_ARC) $(PML_ITEMS_ARC) $(PML_EVOLUTION_ARC) $(PML_PERSONAL_ARC) $(PML_LEARNSETS_ARC) $(PML_MOVES_ARC)
ARC_TARGETS := $(patsubst %, $(romfs)%, $(ARCS))

# Generic
ENCOUNTER_FILES   := $(patsubst $(ENCOUNTERS_ROOT)/%.yml, $(build_dir)/$(ENCOUNTERS_ROOT)/%.bin, $(wildcard $(ENCOUNTERS_ROOT)/*))
ITEMS_FILES       := $(patsubst $(ITEMS_ROOT)/%.yml, $(build_dir)/$(ITEMS_ROOT)/%.bin, $(wildcard $(ITEMS_ROOT)/*))
TEXT_SYSTEM_FILES := $(patsubst $(TEXT_SYSTEM_ROOT)/%.bin, $(build_dir)/$(TEXT_SYSTEM_ROOT)/%.bin, $(wildcard $(TEXT_SYSTEM_ROOT)/*))
TEXT_EVENTS_FILES := $(patsubst $(TEXT_EVENTS_ROOT)/%.bin, $(build_dir)/$(TEXT_EVENTS_ROOT)/%.bin, $(wildcard $(TEXT_EVENTS_ROOT)/*))

# PML
PERSONAL_FILES := $(patsubst $(PML_PERSONAL_ROOT)/%.yml, $(build_dir)/$(PML_PERSONAL_ROOT)/%.bin, $(wildcard $(PML_PERSONAL_ROOT)/*))
EVOLUTION_FILES := $(patsubst $(PML_EVOLUTION_ROOT)/%.yml, $(build_dir)/$(PML_EVOLUTION_ROOT)/%.bin, $(wildcard $(PML_EVOLUTION_ROOT)/*))
LEARNSETS_FILES := $(patsubst $(PML_LEARNSETS_ROOT)/%.yml, $(build_dir)/$(PML_LEARNSETS_ROOT)/%.bin, $(wildcard $(PML_LEARNSETS_ROOT)/*))
MOVES_FILES := $(patsubst $(PML_MOVES_ROOT)/%.yml, $(build_dir)/$(PML_MOVES_ROOT)/%.bin, $(wildcard $(PML_MOVES_ROOT)/*))

# Graphics
POKEGRA_SPRITES_CHAR	         := $(patsubst $(POKEGRA_SPRITES_ROOT)/%.png, $(build_dir)/$(POKEGRA_SPRITES_ROOT)/%.lz, $(wildcard $(POKEGRA_SPRITES_ROOT)/*.png))
POKEGRA_SPRITES_CELL	 	 	 := $(patsubst $(POKEGRA_SPRITES_ROOT)/%.ncer, $(build_dir)/$(POKEGRA_SPRITES_ROOT)/%.ncer, $(wildcard $(POKEGRA_SPRITES_ROOT)/*.ncer))
POKEGRA_SPRITES_ANIM	 	 	 := $(patsubst $(POKEGRA_SPRITES_ROOT)/%.nanr, $(build_dir)/$(POKEGRA_SPRITES_ROOT)/%.lz, $(wildcard $(POKEGRA_SPRITES_ROOT)/*.nanr))
POKEGRA_SPRITES_MCELL_ANIM	     := $(patsubst $(POKEGRA_SPRITES_ROOT)/%.nmar, $(build_dir)/$(POKEGRA_SPRITES_ROOT)/%.nmar, $(wildcard $(POKEGRA_SPRITES_ROOT)/*.nmar))
POKEGRA_SPRITES_MCELL	 	     := $(patsubst $(POKEGRA_SPRITES_ROOT)/%.nmcr, $(build_dir)/$(POKEGRA_SPRITES_ROOT)/%.nmcr, $(wildcard $(POKEGRA_SPRITES_ROOT)/*.nmcr))
POKEGRA_SPRITES_BIN	 	         := $(patsubst $(POKEGRA_SPRITES_ROOT)/%.bin, $(build_dir)/$(POKEGRA_SPRITES_ROOT)/%.bin, $(wildcard $(POKEGRA_SPRITES_ROOT)/*.bin))
POKEGRA_SPRITES_PAL	 	         := $(patsubst $(POKEGRA_SPRITES_ROOT)/%.pal, $(build_dir)/$(POKEGRA_SPRITES_ROOT)/%.nclr, $(wildcard $(POKEGRA_SPRITES_ROOT)/*.pal))
POKEGRA_SPRITES			 	     := $(POKEGRA_SPRITES_CHAR) $(POKEGRA_SPRITES_CELL) $(POKEGRA_SPRITES_ANIM) $(POKEGRA_SPRITES_MCELL_ANIM) $(POKEGRA_SPRITES_MCELL) $(POKEGRA_SPRITES_BIN) $(POKEGRA_SPRITES_PAL)

POKEGRA_ICONS_CHAR	             := $(patsubst $(POKEGRA_ICONS_ROOT)/%.png, $(build_dir)/$(POKEGRA_ICONS_ROOT)/%.ncgr, $(wildcard $(POKEGRA_ICONS_ROOT)/*.png))
POKEGRA_ICONS_CELL	 	 	     := $(patsubst $(POKEGRA_ICONS_ROOT)/%.ncer, $(build_dir)/$(POKEGRA_ICONS_ROOT)/%.ncer, $(wildcard $(POKEGRA_ICONS_ROOT)/*.ncer))
POKEGRA_ICONS_ANIM	 	 	     := $(patsubst $(POKEGRA_ICONS_ROOT)/%.nanr, $(build_dir)/$(POKEGRA_ICONS_ROOT)/%.nanr, $(wildcard $(POKEGRA_ICONS_ROOT)/*.nanr))
POKEGRA_ICONS_MCELL_ANIM	     := $(patsubst $(POKEGRA_ICONS_ROOT)/%.nmar, $(build_dir)/$(POKEGRA_ICONS_ROOT)/%.nmar, $(wildcard $(POKEGRA_ICONS_ROOT)/*.nmar))
POKEGRA_ICONS_MCELL	 	     	 := $(patsubst $(POKEGRA_ICONS_ROOT)/%.nmcr, $(build_dir)/$(POKEGRA_ICONS_ROOT)/%.nmcr, $(wildcard $(POKEGRA_ICONS_ROOT)/*.nmcr))
POKEGRA_ICONS_BIN	 	         := $(patsubst $(POKEGRA_ICONS_ROOT)/%.bin, $(build_dir)/$(POKEGRA_ICONS_ROOT)/%.bin, $(wildcard $(POKEGRA_ICONS_ROOT)/*.bin))
POKEGRA_ICONS_PAL	 	         := $(patsubst $(POKEGRA_ICONS_ROOT)/%.pal, $(build_dir)/$(POKEGRA_ICONS_ROOT)/%.nclr, $(wildcard $(POKEGRA_ICONS_ROOT)/*.pal))
POKEGRA_ICONS			 	     := $(POKEGRA_ICONS_CHAR) $(POKEGRA_ICONS_CELL) $(POKEGRA_ICONS_ANIM) $(POKEGRA_ICONS_MCELL_ANIM) $(POKEGRA_ICONS_MCELL) $(POKEGRA_ICONS_BIN) $(POKEGRA_ICONS_PAL)

# -------------------------------------------------------------------
# Rules
# -------------------------------------------------------------------
# Generic ARC rules
# Encounter ARC
$(build_dir)/$(ENCOUNTERS_ROOT)/%.bin : $(ENCOUNTERS_ROOT)/%.yml
	mkdir -p $(build_dir)/$(ENCOUNTERS_ROOT)
	$(mkenc) $^ $@
$(romfs)$(ENCOUNTERS_ARC) : $(ENCOUNTER_FILES)
	$(knarc) -d $(build_dir)/$(ENCOUNTERS_ROOT) -p $@

# Items ARC
$(build_dir)/$(ITEMS_ROOT)/%.bin : $(ITEMS_ROOT)/%.yml
	mkdir -p $(build_dir)/$(ITEMS_ROOT)
	$(mkdata) $^ items $@
$(romfs)$(PML_ITEMS_ARC) : $(ITEMS_FILES)
	$(knarc) -d $(build_dir)/$(ITEMS_ROOT) -p $@

# Text System ARC
$(build_dir)/$(TEXT_SYSTEM_ROOT)/%.bin : $(TEXT_SYSTEM_ROOT)/%.bin
	mkdir -p $(build_dir)/$(TEXT_SYSTEM_ROOT)
	cp $^ $@
$(romfs)$(TEXT_SYSTEM_ARC) : $(TEXT_SYSTEM_FILES)
	$(knarc) -d $(build_dir)/$(TEXT_SYSTEM_ROOT) -p $@

# Text Events ARC
$(build_dir)/$(TEXT_EVENTS_ROOT)/%.bin : $(TEXT_EVENTS_ROOT)/%.bin
	mkdir -p $(build_dir)/$(TEXT_EVENTS_ROOT)
	cp $^ $@
$(romfs)$(TEXT_EVENTS_ARC) : $(TEXT_EVENTS_FILES)
	$(knarc) -d $(build_dir)/$(TEXT_EVENTS_ROOT) -p $@

# PML ARC Rules
# Personal ARC
$(build_dir)/$(PML_PERSONAL_ROOT)/%.bin : $(PML_PERSONAL_ROOT)/%.yml
	mkdir -p $(build_dir)/$(PML_PERSONAL_ROOT)
	$(mkdata) $^ personal $@
$(romfs)$(PML_PERSONAL_ARC) : $(PERSONAL_FILES)
	$(knarc) -d $(build_dir)/$(PML_PERSONAL_ROOT) -p $@

# Evolutions ARC
$(build_dir)/$(PML_EVOLUTION_ROOT)/%.bin : $(PML_EVOLUTION_ROOT)/%.yml
	mkdir -p $(build_dir)/$(PML_EVOLUTION_ROOT)
	$(mkdata) $^ evolutions $@
$(romfs)$(PML_EVOLUTION_ARC) : $(EVOLUTION_FILES)
	$(knarc) -d $(build_dir)/$(PML_EVOLUTION_ROOT) -p $@

# Learnsets ARC
$(build_dir)/$(PML_LEARNSETS_ROOT)/%.bin : $(PML_LEARNSETS_ROOT)/%.yml
	mkdir -p $(build_dir)/$(PML_LEARNSETS_ROOT)
	$(mkdata) $^ learnsets $@
$(romfs)$(PML_LEARNSETS_ARC) : $(LEARNSETS_FILES)
	$(knarc) -d $(build_dir)/$(PML_LEARNSETS_ROOT) -p $@

# Moves ARC
$(build_dir)/$(PML_MOVES_ROOT)/%.bin : $(PML_MOVES_ROOT)/%.yml
	mkdir -p $(build_dir)/$(PML_MOVES_ROOT)
	$(mkdata) $^ moves $@
$(romfs)$(PML_MOVES_ARC) : $(MOVES_FILES)
	$(knarc) -d $(build_dir)/$(PML_MOVES_ROOT) -p $@

# UI Graphics ARCs
# These should be temporary.
$(romfs)$(UI_GRAPHICS_ARC) : $(UI_GRAPHICS_ROOT)
	$(knarc) -d $^ -p $@
$(romfs)$(UI2_GRAPHICS_ARC) : $(UI2_GRAPHICS_ROOT)
	$(knarc) -d $^ -p $@

# pokegra sprite rules
$(romfs)$(POKEGRA_SPRITES_ARC) : $(POKEGRA_SPRITES)
	$(knarc) -d $(build_dir)/$(POKEGRA_SPRITES_ROOT) -p $@

$(romfs)$(POKEGRA_ICONS_ARC) : $(POKEGRA_ICONS)
	$(knarc) -d $(build_dir)/$(POKEGRA_ICONS_ROOT) -p $@

$(build_dir)/%.lz : %.png
	@ mkdir -p $(@D)
	$(nitrogfx) $^ $*.ncgr -mwidth 4 -mheight 8
	mv $*.ncgr $@
	python3 $(lzcmp) $@ $@

$(build_dir)/%.ncgr : %.png
	@ mkdir -p $(@D)
	$(nitrogfx) $^ $@ -mwidth 4 -mheight 8

$(build_dir)/%.lz : %.nanr
	@ mkdir -p $(@D)
	cp $^ $@ 
	python3 $(lzcmp) $@ $@

$(build_dir)/%.nanr : %.nanr
	@ mkdir -p $(@D)
	cp $^ $@ 

$(build_dir)/%.nclr : %.pal
	@ mkdir -p $(@D)
	$(nitrogfx) -palette $^ $@

$(build_dir)/%.ncer : %.ncer
	@ mkdir -p $(@D)
	cp $^ $@ 

$(build_dir)/%.bin : %.bin
	@ mkdir -p $(@D)
	cp $^ $@ 

$(build_dir)/%.nmcr : %.nmcr
	@ mkdir -p $(@D)
	cp $^ $@ 

$(build_dir)/%.nmar : %.nmar
	@ mkdir -p $(@D)
	cp $^ $@ 
	
