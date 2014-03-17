.PHONY: all clean

all: povrchova_energie.pdf

%.pdf: %.tex
	pdflatex $<
	pdflatex $<

clean:
	rm -f *.log *.out *.aux *.pdf
