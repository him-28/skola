.PHONY: all clean

all: koncentrace.pdf 

%.pdf: %.tex
	pdflatex $<
	pdflatex $<

clean:
	rm -rf *.aux *.out *.log koncentrace.pdf *~
