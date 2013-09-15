all: sondy.pdf 

%.pdf: %.tex %.aux
	pdflatex %.tex

%.aux: %.tex
	pdflatex %.tex

clean:
	rm -rf *.aux *.out *.log sondy.pdf *~
	

