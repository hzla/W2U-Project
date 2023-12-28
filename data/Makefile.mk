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
ITEMS_ARC             := /a/0/2/4
UI_GRAPHICS_ARC       := /a/0/8/2
TRDATA_ARC 			  := /a/0/9/1
TRPOKE_ARC 			  := /a/0/9/2
UI2_GRAPHICS_ARC      := /a/1/2/5
ENCOUNTERS_ARC        := /a/1/2/7

# -------------------------------------------------------------------
# Data Directories
# -------------------------------------------------------------------
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
TRAINER_DATA_ROOT    := $(data_dir)/trainers

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
ARCS := $(POKEGRA_ICONS_ARC) $(POKEGRA_SPRITES_ARC) $(ENCOUNTERS_ARC) $(TEXT_SYSTEM_ARC) $(ITEMS_ARC) $(PML_EVOLUTION_ARC) $(PML_PERSONAL_ARC) $(PML_LEARNSETS_ARC) $(PML_MOVES_ARC) $(TRDATA_ARC) $(TRPOKE_ARC)
ARC_TARGETS := $(patsubst %, $(romfs)%, $(ARCS))

# Generic
ENCOUNTER_FILES                  := $(patsubst $(ENCOUNTERS_ROOT)/%.yml, $(build_dir)$(ENCOUNTERS_ARC)/%.bin, $(wildcard $(ENCOUNTERS_ROOT)/*))
ITEMS_FILES                      := $(patsubst $(ITEMS_ROOT)/%.yml, $(build_dir)/$(ITEMS_ARC)/%.bin, $(wildcard $(ITEMS_ROOT)/*))
TEXT_SYSTEM_FILES                := $(patsubst $(TEXT_SYSTEM_ROOT)/%.bin, $(build_dir)/$(TEXT_SYSTEM_ARC)/%.bin, $(wildcard $(TEXT_SYSTEM_ROOT)/*))
TEXT_EVENTS_FILES                := $(patsubst $(TEXT_EVENTS_ROOT)/%.bin, $(build_dir)/$(TEXT_EVENTS_ARC)/%.bin, $(wildcard $(TEXT_EVENTS_ROOT)/*))
TRDATA_FILES   	                 := $(patsubst $(TRAINER_DATA_ROOT)/%.yml, $(build_dir)$(TRDATA_ARC)/%.bin, $(wildcard $(TRAINER_DATA_ROOT)/*))
TRPOKE_FILES                     := $(patsubst $(TRAINER_DATA_ROOT)/%.yml, $(build_dir)$(TRPOKE_ARC)/%.bin, $(wildcard $(TRAINER_DATA_ROOT)/*))

# PML
PML_PERSONAL_FILES 				 := $(patsubst $(PML_PERSONAL_ROOT)/%.yml, $(build_dir)/$(PML_PERSONAL_ARC)/%.bin, $(wildcard $(PML_PERSONAL_ROOT)/*))
EVOLUTION_FILES    				 := $(patsubst $(PML_EVOLUTION_ROOT)/%.yml, $(build_dir)/$(PML_EVOLUTION_ARC)/%.bin, $(wildcard $(PML_EVOLUTION_ROOT)/*))
LEARNSETS_FILES    				 := $(patsubst $(PML_LEARNSETS_ROOT)/%.yml, $(build_dir)/$(PML_LEARNSETS_ARC)/%.bin, $(wildcard $(PML_LEARNSETS_ROOT)/*))
MOVES_FILES        				 := $(patsubst $(PML_MOVES_ROOT)/%.yml, $(build_dir)/$(PML_MOVES_ARC)/%.bin, $(wildcard $(PML_MOVES_ROOT)/*))

# Graphics
POKEGRA_SPRITES_CHAR	         := $(patsubst $(POKEGRA_SPRITES_ROOT)/%.png, $(build_dir)$(POKEGRA_SPRITES_ARC)/%.lz, $(wildcard $(POKEGRA_SPRITES_ROOT)/*.png))
POKEGRA_SPRITES_CELL	 	 	 := $(patsubst $(POKEGRA_SPRITES_ROOT)/%.ncer, $(build_dir)$(POKEGRA_SPRITES_ARC)/%.ncer, $(wildcard $(POKEGRA_SPRITES_ROOT)/*.ncer))
POKEGRA_SPRITES_ANIM	 	 	 := $(patsubst $(POKEGRA_SPRITES_ROOT)/%.nanr, $(build_dir)$(POKEGRA_SPRITES_ARC)/%.lz, $(wildcard $(POKEGRA_SPRITES_ROOT)/*.nanr))
POKEGRA_SPRITES_MCELL_ANIM	     := $(patsubst $(POKEGRA_SPRITES_ROOT)/%.nmar, $(build_dir)$(POKEGRA_SPRITES_ARC)/%.nmar, $(wildcard $(POKEGRA_SPRITES_ROOT)/*.nmar))
POKEGRA_SPRITES_MCELL	 	     := $(patsubst $(POKEGRA_SPRITES_ROOT)/%.nmcr, $(build_dir)$(POKEGRA_SPRITES_ARC)/%.nmcr, $(wildcard $(POKEGRA_SPRITES_ROOT)/*.nmcr))
POKEGRA_SPRITES_BIN	 	         := $(patsubst $(POKEGRA_SPRITES_ROOT)/%.bin, $(build_dir)$(POKEGRA_SPRITES_ARC)/%.bin, $(wildcard $(POKEGRA_SPRITES_ROOT)/*.bin))
POKEGRA_SPRITES_PAL	 	         := $(patsubst $(POKEGRA_SPRITES_ROOT)/%.pal, $(build_dir)$(POKEGRA_SPRITES_ARC)/%.nclr, $(wildcard $(POKEGRA_SPRITES_ROOT)/*.pal))
POKEGRA_SPRITES			 	     := $(POKEGRA_SPRITES_CHAR) $(POKEGRA_SPRITES_CELL) $(POKEGRA_SPRITES_ANIM) $(POKEGRA_SPRITES_MCELL_ANIM) $(POKEGRA_SPRITES_MCELL) $(POKEGRA_SPRITES_BIN) $(POKEGRA_SPRITES_PAL)

POKEGRA_ICONS_CHAR	             := $(patsubst $(POKEGRA_ICONS_ROOT)/%.png, $(build_dir)$(POKEGRA_ICONS_ARC)/%.ncgr, $(wildcard $(POKEGRA_ICONS_ROOT)/*.png))
POKEGRA_ICONS_CELL	 	 	     := $(patsubst $(POKEGRA_ICONS_ROOT)/%.ncer, $(build_dir)$(POKEGRA_ICONS_ARC)/%.ncer, $(wildcard $(POKEGRA_ICONS_ROOT)/*.ncer))
POKEGRA_ICONS_ANIM	 	 	     := $(patsubst $(POKEGRA_ICONS_ROOT)/%.nanr, $(build_dir)$(POKEGRA_ICONS_ARC)/%.nanr, $(wildcard $(POKEGRA_ICONS_ROOT)/*.nanr))
POKEGRA_ICONS_MCELL_ANIM	     := $(patsubst $(POKEGRA_ICONS_ROOT)/%.nmar, $(build_dir)$(POKEGRA_ICONS_ARC)/%.nmar, $(wildcard $(POKEGRA_ICONS_ROOT)/*.nmar))
POKEGRA_ICONS_MCELL	 	     	 := $(patsubst $(POKEGRA_ICONS_ROOT)/%.nmcr, $(build_dir)$(POKEGRA_ICONS_ARC)/%.nmcr, $(wildcard $(POKEGRA_ICONS_ROOT)/*.nmcr))
POKEGRA_ICONS_BIN	 	         := $(patsubst $(POKEGRA_ICONS_ROOT)/%.bin, $(build_dir)$(POKEGRA_ICONS_ARC)/%.bin, $(wildcard $(POKEGRA_ICONS_ROOT)/*.bin))
POKEGRA_ICONS_PAL	 	         := $(patsubst $(POKEGRA_ICONS_ROOT)/%.nclr, $(build_dir)$(POKEGRA_ICONS_ARC)/%.nclr, $(wildcard $(POKEGRA_ICONS_ROOT)/*.nclr))
POKEGRA_ICONS			 	     := $(POKEGRA_ICONS_CHAR) $(POKEGRA_ICONS_CELL) $(POKEGRA_ICONS_ANIM) $(POKEGRA_ICONS_MCELL_ANIM) $(POKEGRA_ICONS_MCELL) $(POKEGRA_ICONS_BIN) $(POKEGRA_ICONS_PAL)

# -------------------------------------------------------------------
# Rules
# -------------------------------------------------------------------
# knarc
$(romfs)% : $(build_dir)%
	$(knarc) -d $^ -p $@
	
# Encounter ARC
## Builds the ARC.
$(build_dir)$(ENCOUNTERS_ARC) : $(ENCOUNTER_FILES)
## Builds the files in the ARC.
$(build_dir)$(ENCOUNTERS_ARC)/%.bin : $(ENCOUNTERS_ROOT)/%.yml
	mkdir -p $(dir $@)
	$(mkenc) $^ $@

# Items ARC
## Builds the ARC.
$(build_dir)$(ITEMS_ARC) : $(ITEMS_FILES)
## Builds the files in the ARC.
$(build_dir)/$(ITEMS_ARC)/%.bin : $(ITEMS_ROOT)/%.yml
	mkdir -p $(dir $@)
	$(mkdata) generic $^ $@ format items

# Text System ARC
## Builds the ARC.
$(build_dir)$(TEXT_SYSTEM_ARC) : $(TEXT_SYSTEM_FILES)
## Builds the files in the ARC.
$(build_dir)/$(TEXT_SYSTEM_ARC)/%.bin : $(TEXT_SYSTEM_ROOT)/%.bin
	mkdir -p $(dir $@)
	cp $^ $@

# # Text Events ARC
# ## Builds the ARC.
# $(build_dir)$(TEXT_EVENTS_ARC) : $(TEXT_EVENTS_FILES)
# ## Builds the files in the ARC.
# $(build_dir)/$(TEXT_EVENTS_ARC)/%.bin : $(TEXT_EVENTS_ROOT)/%.bin
# 	mkdir -p $(dir $@)
# 	cp $^ $@

# Personal ARC
## Builds the ARC.
$(build_dir)$(PML_PERSONAL_ARC) : $(PML_PERSONAL_FILES)
## Builds the files in the ARC.
$(build_dir)/$(PML_PERSONAL_ARC)/%.bin : $(PML_PERSONAL_ROOT)/%.yml
	mkdir -p $(dir $@)
	$(mkdata) generic $^ $@ format personal

# Evolutions ARC
## Builds the ARC.
$(build_dir)$(PML_EVOLUTION_ARC) : $(EVOLUTION_FILES)
## Builds the files in the ARC.
$(build_dir)/$(PML_EVOLUTION_ARC)/%.bin : $(PML_EVOLUTION_ROOT)/%.yml
	mkdir -p $(dir $@)
	$(mkdata) generic $^ $@ format evolutions

# Learnsets ARC
## Builds the ARC.
$(build_dir)$(PML_LEARNSETS_ARC) : $(LEARNSETS_FILES)
## Builds the files in the ARC.
$(build_dir)/$(PML_LEARNSETS_ARC)/%.bin : $(PML_LEARNSETS_ROOT)/%.yml
	mkdir -p $(dir $@)
	$(mkdata) generic $^ $@ format learnsets

# Moves ARC
## Builds the ARC.
$(build_dir)$(PML_MOVES_ARC) : $(MOVES_FILES)
## Builds the files in the ARC.
$(build_dir)/$(PML_MOVES_ARC)/%.bin : $(PML_MOVES_ROOT)/%.yml
	mkdir -p $(dir $@)
	$(mkdata) generic $^ $@ format moves

# Trainer Data ARC
## Builds the ARC.
$(build_dir)$(TRDATA_ARC) : $(TRDATA_FILES)
## Builds the files in the ARC.
$(build_dir)$(TRDATA_ARC)/%.bin : $(TRAINER_DATA_ROOT)/%.yml
	mkdir -p $(dir $@)
	$(mktrainer) $^ $@ output_type trdata

# Trainer Pokemon ARC
## Builds the ARC.
$(build_dir)$(TRPOKE_ARC) : $(TRPOKE_FILES)
## Builds the files in the ARC.
$(build_dir)$(TRPOKE_ARC)/%.bin : $(TRAINER_DATA_ROOT)/%.yml
	mkdir -p $(dir $@)
	$(mktrainer) $^ $@ output_type trpoke

# UI Graphics ARCs
# These should be temporary.
$(build_dir)$(UI_GRAPHICS_ARC) : $(UI_GRAPHICS_ROOT)
$(build_dir)$(UI2_GRAPHICS_ARC) : $(UI2_GRAPHICS_ROOT)

# pokegra ARCs
## Builds the ARCs.
$(build_dir)$(POKEGRA_SPRITES_ARC) : $(POKEGRA_SPRITES)
$(build_dir)$(POKEGRA_ICONS_ARC) : $(POKEGRA_ICONS)
## Builds the files in the ARCs.
### Sprite rules for pokegra battle sprites.
include data/pokegra_sprites.mk
### Sprite rules for pokegra icons.
include data/pokegra_icons.mk
