all: townsend.pdf 

%.pdf: %.tex %.aux
	pdflatex $<

%.aux: %.tex
	pdflatex $<

clean:
	rm -rf *.aux *.out *.log townsend.pdf *~
	

