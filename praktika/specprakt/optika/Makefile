PROGRAMS = programs/ellipsometry programs/R-fit-simple programs/R-fit-with-absorption programs/R-compute

.PHONY: all clean

all: optika.pdf

optika.pdf: optika.tex schema.pdf $(PROGRAMS)
	pdflatex $<
	pdflatex $<

%.pdf: %.svg
	inkscape --without-gui --export-pdf=$@ $<

%: %.c
	$(CC) -lm -lgsl -o $@ $<

clean:
	rm -f *.log *.out *.aux *.pdf $(PROGRAMS)
