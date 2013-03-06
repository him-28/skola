all: pdffinal

pdffinal: pdfdraft2
	pdflatex diplomka.tex

pdfdraft2: bibtex
	pdflatex diplomka.tex

grafika: grafika/DLCDOS.pdf grafika/layerscheme.pdf

grafika/DLCDOS.pdf:
	inkscape --without-gui --export-pdf=grafika/DLCDOS.pdf grafika/DLCDOS.svg
grafika/layerscheme.pdf:
	inkscape --without-gui --export-pdf=grafika/layerscheme.pdf grafika/layerscheme.svg

bibtex: pdfdraft
	bibtex diplomka

pdfdraft: grafika
	pdflatex diplomka.tex

clean:
	rm grafika/DLCDOS.pdf grafika/layerscheme.pdf diplomka.aux diplomka.bbl diplomka.log diplomka.out diplomka.idx diplomka.blg diplomka.toc diplomka.pdf
