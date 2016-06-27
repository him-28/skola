.PHONY: all clean figures

all: talk.pdf

%.pdf: %.tex
	pdflatex $<
	pdflatex $<

talk.pdf: figures

figures:
	$(MAKE) -C $@

clean:
	rm -f *.pdf *.aux *.toc *.log *~ *.out *.snm *.nav
	$(MAKE) -C figures $@
