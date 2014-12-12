.PHONY: all clean

FIGURES = gap.pdf gap-overview.pdf

all: $(FIGURES)

%.pdf: %.gpi
	gnuplot $< > $@

clean:
	rm -f *~ $(FIGURES)
