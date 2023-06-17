$(romfs)/a/0/1/6: $(arc_dir)/pml/Personal.c
	@ $(gcc) $(c_flags) -I$(incl_dir) -I$(incl_dir)/swan -c $< -o $(build_dir)/Personal.o
	@ $(o2narc) $(build_dir)/Personal.o $@

$(romfs)/a/0/1/8: $(arc_dir)/pml/Learnsets.c
	@ $(gcc) $(c_flags) -I$(incl_dir) -I$(incl_dir)/swan -c $< -o $(build_dir)/Learnsets.o
	@ $(o2narc) $(build_dir)/Learnsets.o $@

$(romfs)/a/0/1/9: $(arc_dir)/pml/Evolutions.c
	@ $(gcc) $(c_flags) -I$(incl_dir) -I$(incl_dir)/swan -c $< -o $(build_dir)/Evolutions.o
	@ $(o2narc) $(build_dir)/Evolutions.o $@

$(romfs)/a/0/2/0: $(arc_dir)/pml/Children.c
	@ $(gcc) $(c_flags) -I$(incl_dir) -I$(incl_dir)/swan -c $< -o $(build_dir)/Children.o
	@ $(o2narc) $(build_dir)/Children.o $@

$(romfs)/a/0/2/1: $(arc_dir)/pml/Moves.c
	@ $(gcc) $(c_flags) -I$(incl_dir) -I$(incl_dir)/swan -c $< -o $(build_dir)/Moves.o
	@ $(o2narc) $(build_dir)/Moves.o $@

$(romfs)/a/0/2/4: $(arc_dir)/pml/Items.c
	@ $(gcc) $(c_flags) -I$(incl_dir) -I$(incl_dir)/swan -c $< -o $(build_dir)/Items.o
	@ $(o2narc) $(build_dir)/Items.o $@

	