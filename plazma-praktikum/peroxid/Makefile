all: peroxid.pdf 

%.pdf: %.tex %.aux grafika
	pdflatex $<

%.aux: %.tex grafika
	pdflatex $<

grafika: schema.pdf

schema.pdf: schema.svg
	inkscape --without-gui --export-pdf=$@ $<

clean:
	rm -rf *.aux *.out *.log peroxid.pdf *~
	

