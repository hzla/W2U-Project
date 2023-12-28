$(build_dir)$(POKEGRA_SPRITES_ARC)/%.lz : $(POKEGRA_SPRITES_ROOT)/%.png
	@ mkdir -p $(@D)
	$(nitrogfx) $^ $*.ncgr -mwidth 4 -mheight 8
	mv $*.ncgr $@
	python3 $(mklz) $@ $@

$(build_dir)$(POKEGRA_SPRITES_ARC)/%.lz : $(POKEGRA_SPRITES_ROOT)/%.nanr
	@ mkdir -p $(@D)
	cp $^ $@ 
	python3 $(mklz) $@ $@

$(build_dir)$(POKEGRA_SPRITES_ARC)/%.bin : $(POKEGRA_SPRITES_ROOT)/%.bin
	@ mkdir -p $(@D)
	cp $^ $@ 

$(build_dir)$(POKEGRA_SPRITES_ARC)/%.nmcr : $(POKEGRA_SPRITES_ROOT)/%.nmcr
	@ mkdir -p $(@D)
	cp $^ $@ 

$(build_dir)$(POKEGRA_SPRITES_ARC)/%.nmar : $(POKEGRA_SPRITES_ROOT)/%.nmar
	@ mkdir -p $(@D)
	cp $^ $@

$(build_dir)$(POKEGRA_SPRITES_ARC)/%.ncer : $(POKEGRA_SPRITES_ROOT)/%.ncer
	@ mkdir -p $(@D)
	cp $^ $@