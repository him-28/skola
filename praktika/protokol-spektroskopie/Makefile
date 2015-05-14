.PHONY: all clean

all: protokol.pdf

%.pdf: %.tex
	pdflatex $<
	pdflatex $<

clean:
	rm -f *.log *.out *.aux *.pdf
