.PHONY: all clean figures

all: prezentace.pdf

%.pdf: %.tex
	pdflatex $<
	pdflatex $<

prezentace.pdf: figures

figures:
	$(MAKE) -C $@

clean:
	rm -f *.pdf *.aux *.toc *.log *~ *.out *.snm *.nav
	$(MAKE) -C figures $@
