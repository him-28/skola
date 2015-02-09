.PHONY: all clean

all: ecr.pdf 

%.pdf: %.tex schema.pdf
	pdflatex $<
	pdflatex $<

%.pdf: %.svg
	inkscape --without-gui --export-pdf=$@ $<

clean:
	rm -rf *.aux *.out *.log ecr.pdf schema.pdf *~
