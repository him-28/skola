.PHONY: all clean

all: zapoctove_priklady.pdf

%.pdf: %.tex
	pdflatex $<
	pdflatex $<

clean:
	rm -f *.log *.out *.aux *.pdf
