.PHONY: all clean

FIGURES = all.pdf anatase-XRD.pdf SiTiO2-eps.pdf compare.pdf gap.pdf

all: $(FIGURES)

%.pdf: %.gpi
	gnuplot $< > $@

clean:
	rm -f *~ $(FIGURES)
