all: ecr.pdf 

%.pdf: %.tex %.aux
	pdflatex $<

%.aux: %.tex grafika
	pdflatex $<

grafika: schema.pdf

schema.pdf: schema.svg
	inkscape --without-gui --export-pdf=$@ $<

clean:
	rm -rf *.aux *.out *.log ecr.pdf schema.pdf *~
