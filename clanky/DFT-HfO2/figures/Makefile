.PHONY: all clean

FIGURES = 

all: $(FIGURES)

%.pdf: %.gpi
	gnuplot $< > $@

clean:
	rm -f *~ $(FIGURES)
