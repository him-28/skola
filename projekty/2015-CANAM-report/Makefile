.PHONY: all clean figures

all: CANAM-report.pdf

%.pdf: %.tex %.bbl
	pdflatex $<
	pdflatex $<

%.bbl: %.aux bib-db.bib
	bibtex $(patsubst %.bbl, %, $@)

%.aux: %.tex figures
	pdflatex $<

figures:
	$(MAKE) -C $@

clean:
	rm -f *.aux *.log *.out *~ *.pdf *.bbl *.blg
	$(MAKE) -C figures $@
