.PHONY: all clean

FIGURES = hydrogen.pdf thickness.pdf

all: $(FIGURES)

%.pdf: %.gpi
	gnuplot $< > $@

clean:
	rm -f *~ $(FIGURES)
