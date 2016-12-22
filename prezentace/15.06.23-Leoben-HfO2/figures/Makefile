.PHONY: all clean

FIGURES = gap.pdf am-HfO2.pdf c-HfO2.pdf m-HfO2.pdf m-HfO2-hf.pdf V-gap.pdf

all: $(FIGURES)

%.pdf: %.gpi
	gnuplot $< > $@

clean:
	rm -f *~ $(FIGURES)
