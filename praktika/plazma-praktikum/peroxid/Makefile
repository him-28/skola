.PHONY: all clean

all: peroxid.pdf 

%.pdf: %.tex schema.pdf
	pdflatex $<
	pdflatex $<

%.pdf: %.svg
	inkscape --without-gui --export-pdf=$@ $<

clean:
	rm -rf *.aux *.out *.log peroxid.pdf *~
	

