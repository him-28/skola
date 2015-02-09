all: townsend.pdf 

%.pdf: %.tex
	pdflatex $<
	pdflatex $<

clean:
	rm -rf *.aux *.out *.log townsend.pdf *~
	

