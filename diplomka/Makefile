all: DLCDOS.pdf pdffinal

pdffinal: DLCDOS.pdf bibtex
	pdflatex diplomka.tex

DLCDOS.pdf:
	inkscape --without-gui --export-pdf=grafika/DLCDOS.pdf grafika/DLCDOS.svg

bibtex: pdfdraft
	bibtex diplomka

pdfdraft: DLCDOS.pdf
	pdflatex diplomka.tex

clean:
	rm grafika/DLCDOS.pdf diplomka.aux diplomka.bbl diplomka.log diplomka.out diplomka.idx diplomka.blg diplomka.toc
