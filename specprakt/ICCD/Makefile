.PHONY: all clean

all: ICCD.pdf

%.pdf: %.tex
	pdflatex $<
	pdflatex $<

%.pdf: %.svg
	inkscape --without-gui --export-pdf=$@ $<

clean:
	rm -f *.log *.out *.aux ICCD.pdf
