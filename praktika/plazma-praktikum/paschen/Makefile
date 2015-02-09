.PHONY: all clean

GRAFIKA = nakres1.pdf nakres2.pdf nakres3.pdf VA.pdf Graph1.pdf Graph2.pdf Graph3.pdf

all: paschen.pdf

%.pdf: %.tex $(GRAFIKA)
	pdflatex $<
	pdflatex $<

%.pdf: %.svg
	inkscape --without-gui --export-pdf=$@ $<

clean:
	rm -rf *.aux *.out *.log paschen.pdf *~ nakres*.pdf VA.pdf 
