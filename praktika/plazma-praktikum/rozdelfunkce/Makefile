all: rfunc.pdf 

%.pdf: %.tex
	pdflatex $<
	pdflatex $<

clean:
	rm -rf *.aux *.out *.log rfunc.pdf *~
