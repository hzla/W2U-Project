$(build_dir)$(POKEGRA_ICONS_ARC)/%.ncgr : $(POKEGRA_ICONS_ROOT)/%.png
	@ mkdir -p $(@D)
	$(nitrogfx) $^ $@ -mwidth 4 -mheight 8

$(build_dir)$(POKEGRA_ICONS_ARC)/%.nanr : $(POKEGRA_ICONS_ROOT)/%.nanr
	@ mkdir -p $(@D)
	cp $^ $@ 

$(build_dir)$(POKEGRA_ICONS_ARC)/%.bin : $(POKEGRA_ICONS_ROOT)/%.bin
	@ mkdir -p $(@D)
	cp $^ $@ 

$(build_dir)$(POKEGRA_ICONS_ARC)/%.nmcr : $(POKEGRA_ICONS_ROOT)/%.nmcr
	@ mkdir -p $(@D)
	cp $^ $@ 

$(build_dir)$(POKEGRA_ICONS_ARC)/%.nmar : $(POKEGRA_ICONS_ROOT)/%.nmar
	@ mkdir -p $(@D)
	cp $^ $@

$(build_dir)$(POKEGRA_ICONS_ARC)/%.ncer : $(POKEGRA_ICONS_ROOT)/%.ncer
	@ mkdir -p $(@D)
	cp $^ $@

$(build_dir)$(POKEGRA_ICONS_ARC)/%.nclr : $(POKEGRA_ICONS_ROOT)/%.nclr
	@ mkdir -p $(@D)
	cp $^ $@