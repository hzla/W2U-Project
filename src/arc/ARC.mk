all_narcs : $(romfs)/a/0/1/6

$(romfs)/a/0/1/6: $(arc_dir)/pml/Personal.c
	@ $(gcc) $(c_flags) -I$(incl_dir) -I$(incl_dir)/swan -c $< -o $@