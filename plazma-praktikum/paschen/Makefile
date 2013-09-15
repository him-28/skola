all: paschen.pdf 

%.pdf: %.tex %.aux grafika
	pdflatex $<

%.aux: %.tex grafika
	pdflatex $<

grafika: nakres1.pdf nakres2.pdf nakres3.pdf VA.pdf Graph1.pdf Graph2.pdf Graph3.pdf

nakres1.pdf: nakres1.svg
	inkscape --without-gui --export-pdf=$@ $<

nakres2.pdf: nakres2.svg
	inkscape --without-gui --export-pdf=$@ $<

nakres3.pdf: nakres3.svg
	inkscape --without-gui --export-pdf=$@ $<

VA.pdf: VA.svg
	inkscape --without-gui --export-pdf=$@ $<

clean:
	rm -rf *.aux *.out *.log paschen.pdf *~ nakres*.pdf VA.pdf 
