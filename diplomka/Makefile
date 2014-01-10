SUBDIRS = grafika grafy programy tabulky
.PHONY: all clean $(SUBDIRS)

all: diplomkafinal

diplomkafinal: diplomka.pdf
	pdflatex diplomka.tex

diplomka.pdf: diplomka.aux diplomka.bbl
	pdflatex diplomka.tex

$(SUBDIRS): 
	make -C $@

grafy: programy

tabulky: programy

diplomka.bbl: diplomka.aux
	bibtex diplomka

diplomka.aux: grafika grafy tabulky
	pdflatex diplomka.tex

clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir $@; \
	done
	rm -f diplomka.aux diplomka.bbl diplomka.log diplomka.out diplomka.idx diplomka.blg diplomka.toc diplomka.pdf tabulky/H-table.tex
