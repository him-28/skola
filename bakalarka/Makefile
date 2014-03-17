.PHONY = all clean

all:prace.pdf

prace.pdf: prace.tex prace.bbl
	pdflatex $<
	pdflatex $<

prace.bbl: prace.aux
	bibtex prace

prace.aux: prace.tex
	pdflatex $<

clean:
	rm -f *.out *.aux *.log *.toc *.bbl *.blg prace.pdf
