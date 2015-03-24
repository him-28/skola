.PHONY: all clean

FIGURES = gap.pdf SiTiO2-eps.pdf compare.pdf near-gap-eps.pdf HfO2-eps-overview.pdf CH30deconv.pdf

all: $(FIGURES)

%.pdf: %.gpi
	gnuplot $< > $@

gap.pdf: gap.txt

clean:
	rm -f *~ $(FIGURES)
