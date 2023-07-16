arcs : $(romfs)/a/0/0/4 $(romfs)/a/0/0/7 $(romfs)/a/0/1/6 $(romfs)/a/0/1/8 $(romfs)/a/0/1/9 $(romfs)/a/0/2/0 $(romfs)/a/0/2/1 $(romfs)/a/0/2/4

$(romfs)/a/0/1/6: $(arc_dir)/pml/Personal.c $(game_base) 
	$(gcc) $(c_flags) -I$(incl_dir) -I$(incl_dir)/swan -c $< -o $(build_dir)/Personal.o
	@ rm -rf $@
	@ $(o2narc) $(build_dir)/Personal.o $@

$(romfs)/a/0/1/8: $(arc_dir)/pml/Learnsets.c $(game_base) 
	$(gcc) $(c_flags) -I$(incl_dir) -I$(incl_dir)/swan -c $< -o $(build_dir)/Learnsets.o
	@ rm -rf $@
	@ $(o2narc) $(build_dir)/Learnsets.o $@

$(romfs)/a/0/1/9: $(arc_dir)/pml/Evolutions.c $(game_base) 
	$(gcc) $(c_flags) -I$(incl_dir) -I$(incl_dir)/swan -c $< -o $(build_dir)/Evolutions.o
	@ rm -rf $@
	@ $(o2narc) $(build_dir)/Evolutions.o $@

$(romfs)/a/0/2/0: $(arc_dir)/pml/Children.c $(game_base) 
	$(gcc) $(c_flags) -I$(incl_dir) -I$(incl_dir)/swan -c $< -o $(build_dir)/Children.o
	@ rm -rf $@
	@ $(o2narc) $(build_dir)/Children.o $@

$(romfs)/a/0/2/1: $(arc_dir)/pml/Moves.c $(game_base) 
	$(gcc) $(c_flags) -I$(incl_dir) -I$(incl_dir)/swan -c $< -o $(build_dir)/Moves.o
	@ rm -rf $@
	@ $(o2narc) $(build_dir)/Moves.o $@

$(romfs)/a/0/2/4: $(arc_dir)/pml/Items.c $(game_base) 
	$(gcc) $(c_flags) -I$(incl_dir) -I$(incl_dir)/swan -c $< -o $(build_dir)/Items.o
	@ rm -rf $@
	@ $(o2narc) $(build_dir)/Items.o $@
	

include $(arc_dir)/graphics/pokegra.mk	