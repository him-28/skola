.PHONY: all clean

all: sondy.pdf

%.pdf: %.tex
	pdflatex $<
	pdflatex $<

clean:
	rm -f *.log *.out *.aux *.pdf
