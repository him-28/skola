.PHONY: all clean

FIGURES = compare.pdf all-eps.pdf monoclinic-eps.pdf monoclinic-eps2.pdf DOS.pdf SiTiO2-n.pdf XPS.pdf

all: $(FIGURES)

%.pdf: %.gpi
	gnuplot $< > $@

gap.pdf: gap.txt

clean:
	rm -f *~ $(FIGURES)
