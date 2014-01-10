PROGRAMS = deconvolute H-table
.PHONY: all clean

all: $(PROGRAMS)

%: %.c
	gcc $@.c -o $@ -std=c99 -g	

clean:
	rm -f $(PROGRAMS)
