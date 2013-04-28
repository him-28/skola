all: pdffinal

pdffinal: pdfdraft2
	pdflatex diplomka.tex

pdfdraft2: bibtex
	pdflatex diplomka.tex

grafika: grafika/DLCDOS.pdf grafika/layerscheme.pdf grafika/reaktor.pdf grafika/dlcgrowth.pdf grafika/dlcgrowthH.pdf

grafika/DLCDOS.pdf:
	inkscape --without-gui --export-pdf=grafika/DLCDOS.pdf grafika/DLCDOS.svg
grafika/layerscheme.pdf:
	inkscape --without-gui --export-pdf=grafika/layerscheme.pdf grafika/layerscheme.svg
grafika/reaktor.pdf:
	inkscape --without-gui --export-pdf=grafika/reaktor.pdf grafika/reaktor.svg
grafika/dlcgrowth.pdf:
	inkscape --without-gui --export-pdf=grafika/dlcgrowth.pdf grafika/dlcgrowth.svg
grafika/dlcgrowthH.pdf:
	inkscape --without-gui --export-pdf=grafika/dlcgrowthH.pdf grafika/dlcgrowthH.svg

programy/deconvolute:
	gcc programy/deconvolute.c -o programy/deconvolute -std=c99

grafy: programy/deconvolute grafy/CH30Adeconv.pdf grafy/CH88Adeconv.pdf grafy/CH90Adeconv.pdf grafy/CH83Adeconv.pdf grafy/R-multifit.pdf grafy/T-multifit.pdf grafy/T-detail-multifit.pdf

grafy/CH30Adeconv.pdf:
	programy/deconvolute vysledky/out-multifit 1 | gnuplot > grafy/CH30Adeconv.pdf
grafy/CH88Adeconv.pdf:
	programy/deconvolute vysledky/out-multifit 2 | gnuplot > grafy/CH88Adeconv.pdf
grafy/CH90Adeconv.pdf:
	programy/deconvolute vysledky/out-multifit 3 | gnuplot > grafy/CH90Adeconv.pdf
grafy/CH83Adeconv.pdf:
	programy/deconvolute vysledky/out-multifit 4 | gnuplot > grafy/CH83Adeconv.pdf
grafy/R-multifit.pdf:
	gnuplot grafy/R-multifit.gpi > grafy/R-multifit.pdf
grafy/T-multifit.pdf:
	gnuplot grafy/T-multifit.gpi > grafy/T-multifit.pdf
grafy/T-detail-multifit.pdf:
	gnuplot grafy/T-detail-multifit.gpi > grafy/T-detail-multifit.pdf

bibtex: pdfdraft
	bibtex diplomka

pdfdraft: grafika grafy
	pdflatex diplomka.tex

clean:
	rm grafika/DLCDOS.pdf grafika/layerscheme.pdf grafika/reaktor.pdf grafika/dlcgrowth.pdf grafika/dlcgrowthH.pdf diplomka.aux diplomka.bbl diplomka.log diplomka.out diplomka.idx diplomka.blg diplomka.toc diplomka.pdf programy/deconvolute grafy/CH30Adeconv.pdf grafy/CH88Adeconv.pdf grafy/CH90Adeconv.pdf grafy/CH83Adeconv.pdf grafy/T-multifit.pdf grafy/R-multifit.pdf grafy/T-detail-multifit.pdf
