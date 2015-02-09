all: sondy.pdf 

%.pdf: %.tex
	pdflatex $<
	pdflatex $<

clean:
	rm -rf *.aux *.out *.log sondy.pdf *~
	

