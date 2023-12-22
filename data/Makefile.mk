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
ARCS := $(ENCOUNTERS_ARC) $(TEXT_SYSTEM_ARC) $(TEXT_EVENTS_ARC) $(PML_ITEMS_ARC) $(PML_EVOLUTION_ARC) $(PML_PERSONAL_ARC) $(PML_LEARNSETS_ARC) $(PML_MOVES_ARC)
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

# This is for all graphics to .bin conversions
%.bin : %.png
	$(nitrogfx) $^ $*.ncgr -mwidth 4 -mheight 8
	mv $*.ncgr $@

# # PML ARC root.
# PML_ARC_TARGETS     := $(patsubst $(arc_dir)/pml/%.c, $(build_dir)/%.arc, $(wildcard $(ARC_PML_ROOT_FILES)/*))

# ARC_POKEGRA_ICON_FILES	:= $(arc_dir)/pokegra_icons
# POKEGRA_ICON_SPRITES_NTR := $(patsubst %.png, %.bin, $(wildcard $(ARC_POKEGRA_ICON_FILES)/*))

# ASSET_ARC_TARGETS := $(patsubst $(arc_dir)/%, $(build_dir)/%.arc, $(wildcard $(filter-out $(ARC_PML_ROOT_FILES), $(arc_dir)/*)))
# ARC_TARGETS 	  := $(PML_ARC_TARGETS) $(ASSET_ARC_TARGETS)

# # other rules

# # o2narc rules
# $(build_dir)/%.arc : $(arc_dir)/pml/%.c
# 	$(gcc) $(c_flags) -I$(incl_dir) -I$(incl_dir)/swan -c $< -o $(build_dir)/$*.o
# 	@ rm -rf $@
# 	@ $(o2narc) $(build_dir)/$*.o $@
